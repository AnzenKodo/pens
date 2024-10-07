import json
import ast
import os
from datetime import date, datetime

from flask import Flask, render_template, request, flash, redirect, url_for, make_response, render_template_string
from flask_login import LoginManager, login_user, UserMixin, login_required, current_user, logout_user
from flask_minify import Minify

from dotenv import load_dotenv
import smtplib

from db import Db

load_dotenv()
config = json.load(open("static/manifest.json"))

app = Flask(__name__)
app.config['SECRET_KEY'] = os.getenv("FLASK_SECRET_KEY")

db = Db()
class UserDB(UserMixin):
	def __init__(self, id, is_admin=False):
		if is_admin or id == "admin":
			self.name = os.getenv("ADMIN_NAME")
			self.password = os.getenv("ADMIN_PASSWORD")
			self.is_admin = True
			self.id = "admin"
			self.subjects = [sub[0] for sub in db.getSubjects()]
		else:
			teacher = db.getTeacher(id)
			self.id = teacher[0]
			self.name = teacher[1]
			self.subjects = sorted(teacher[3].split(", "))
			self.phone_no = teacher[0]
			self.password = teacher[2]
			self.is_admin = False

login_manager = LoginManager()
login_manager.init_app(app)

@login_manager.user_loader
def load_user(id):
	return UserDB(id)

@app.route("/logout")
@login_required
def logout():
	logout_user()
	return redirect(url_for('login'))

@login_manager.unauthorized_handler
@app.errorhandler(404)
@app.route("/404")
def not_found(e):
	flash('404 Page Not Found')
	return redirect(url_for('index'))

@app.route('/', methods=['GET', 'POST'])
def index():
	if current_user.is_authenticated:
		if current_user.is_admin:
			return redirect(url_for('admin'))
		else:
			return redirect(url_for('teacher'))
	return redirect(url_for('login'))

@app.route('/login', methods=['GET', 'POST'])
def login():
	if current_user.is_authenticated:
		return redirect(url_for('index'))
	else:
		return render_template("login.html", config=config)

@app.route('/login/teacher', methods=['GET', 'POST'])
def login_teacher():
	phone_no = request.form.get('phone_no')
	password = request.form.get('password')
	db_password = db.getTeacherPassword(phone_no)
	
	if db_password == None or db_password != password:
		flash('Please check your login details and try again.')
		return redirect(url_for('login'))
	else:
		login_user(UserDB(phone_no), remember=True)
		return redirect(url_for('teacher'))

@app.route('/login/admin', methods=['GET', 'POST'])
def login_admin():
	name = request.form.get('username')
	password = request.form.get('password')

	if name == os.getenv("ADMIN_NAME") and password == os.getenv("ADMIN_PASSWORD"):
		login_user(UserDB("", True), remember=True)
		return redirect(url_for('admin'))
	else:
		flash('Please check your login details and try again.')
		return redirect(url_for('login')) 

@app.route('/student')
def student():
	gr_no = request.args.get("gr_no")
	if gr_no:
		student = db.getStudentWitoutSem(gr_no)
		if student:
			return render_template(
				"/student/index.html", 
				config=config,
				student=student,
				results=db.getAttendanceForStdView(gr_no, student[0]),
				values=[0]
			)
		else:
			flash('Student Not Found. Please check the GR Number you have entered.')
			return redirect(url_for('login'))
	else:
		flash('Student Not Found. Please check the GR Number you have entered.')
		return redirect(url_for('login')) 

@app.route('/teacher', methods=['GET', 'POST', 'PUT', 'DELETE'])
@login_required
def teacher():
	if current_user.is_admin:
		return redirect(url_for('not_found'))
	
	subject = request.args.get("subject") or current_user.subjects[0]

	if not request.method == "GET":
		if not subject in current_user.subjects:
			return 500

		gr_no = request.args.get("gr_no")
		if request.method == "PUT":
			print(subject)
			db.addAttendanceToDate(current_user.phone_no, gr_no, subject)
		if request.method == "DELETE":
			db.removeAttendanceToDate(gr_no, subject)

	return render_template("/teacher/index.html", 
		config=config, 
		teacher=current_user,
		students=db.getStudentsWithAttendance(subject),
		subject=subject,
		date=datetime.strftime(date.today(), "%d %B %Y, %A")
	)

@app.route('/admin', methods=['GET', 'POST', 'PUT', 'DELETE'])
@login_required
def admin():
	if not current_user.is_admin:
		return redirect(url_for('not_found'))

	sems=db.getSems()
	selected_sem = request.form.get('selected_sem') or request.cookies.get('selected_sem', sems[0])

	first_sub=""
	subs=db.getSubjectsBySem(selected_sem)
	if subs:
		first_sub=list(subs.keys())[0]

	selected_subject = request.cookies.get('selected_subject', first_sub)

	selected_date = str(date.today())
	template_address = "/admin/index.html"

	if not request.method == "GET":
		selected_date = request.form.get('selected_date', selected_date)
		template_address = "/admin/table.html"
		gr_no = request.args.get("gr_no")
		selected_subject = request.form.get('selected_subject', first_sub)
		if not selected_subject in subs and not selected_subject == "Total" and not subs == {}:
			return "Wrong subject passed", 500

		if request.method == "PUT":
			db.addAttendanceToDate("admin", gr_no, selected_subject, selected_sem, selected_date)
		if request.method == "DELETE":
			db.removeAttendanceToDate(gr_no, selected_subject, selected_sem, selected_date)

	res = make_response(render_template(
		template_address,
		config=config,
		sems=sems,
		selected_sem=selected_sem,
		selected_date=selected_date,
		students=db.getStudentsWithAttendance(selected_subject, selected_sem, 0, selected_date),
		students_total=db.getStudentsAttendanceTotal(selected_sem, selected_subject),
		cookies=dict(request.cookies) | dict(request.form),
		subs=subs,
		selected_subject=selected_subject,
	))

	if request.method == "POST":
		for key, value in dict(request.form).items():
			res.set_cookie(key, value)

		res.set_cookie('selected_date', selected_date)
		res.set_cookie('selected_sem', selected_sem)
		res.set_cookie('selected_subject', selected_subject)
	return res

@app.route('/admin/email/<gr_nos>', methods=['POST', 'GET'])
@login_required
def admin_email(gr_nos):
	if not current_user.is_admin:
		return 500
	selected_sem = request.form.get('selected_sem')
	email_message = request.form.get('email_message')
	email_subject = request.form.get('email_subject')
	message_log = ""

	for gr_no in gr_nos.split(","):
		student = db.getStudent(gr_no, selected_sem)
		if not student[4]:
			message_log += f"<a href='mailto:{student[4]}'>{student[4]} →</a> <strong style='color: red;'>E-Mail not found on server side!</strong>"
			continue

		message = email_message.replace("{name}", student[2])
		message = message.replace("{roll_no}", str(student[0]))
		message = message.replace("{link}", url_for("student", _external=True)+"?gr_no="+gr_no)
		send_message = "\r\n".join([
			f"From: {config['name']}",
			f"To: {student[4]}",
			f"Subject: {email_subject}",
			"",
			message
		])

		try:
			server = smtplib.SMTP("smtp.gmail.com", 587)
			server.ehlo()
			server.starttls()
			server.login(os.getenv("EMAIL_ADDRESS"), os.getenv("EMAIL_PASSWORD"))
			server.sendmail(os.getenv("EMAIL_ADDRESS"), student[4], send_message)
			server.close()

			message_log += f"<a href='mailto:{student[4]}'>{student[4]} →</a> {message} \n\n"
		except:
			message_log += f"<a href='mailto:{student[4]}'>{student[4]} →</a> <strong style='color: red;'>Failed to send the E-Mail.</strong> \n\n"

	return f"""<p>E-Mail has been sent to following addresses with following message:</p>
	<pre style="margin-top: 0.5rem;
		text-wrap: wrap;
			height: 20em;
			overflow-x: overlay;
			border: 1px solid;
			border-radius: 10px 0px 0px 10px;
			padding: 1em">{message_log}</pre>
	<form method="dialog" style="text-align: right">
			<button>Close</button>
	</form>    
	"""

if __name__ == '__main__':
	app.debug = False
	if app.debug == True:
		app.config['TEMPLATES_AUTO_RELOAD'] = True
		app.config['EXPLAIN_TEMPLATE_LOADING'] = True
		app.config["FLASK_RUN_EXTRA_FILES"] = "data/"
	else:
		Minify(app=app)
		import logging
		logging.basicConfig(filename='logs/info.log',level=logging.NOTSET)
		logging.basicConfig(filename='logs/warning.log',level=logging.WARNING)
		logging.basicConfig(filename='logs/error.log',level=logging.ERROR)
	app.run()