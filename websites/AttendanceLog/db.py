#!/usr/bin/env python

import sqlite3
from datetime import date, timedelta, datetime

from itertools import chain
from pylightxl import readxl

DATABASE_NAME = "data/attendance.db"
CREATE_TABLE_QUARY = ""

def col_index(sheet, name):
	return sheet.row(row=1).index(name) + 1

def row_index(sheet, col_name, row_name):
	try:
		return sheet.col(col=col_index(sheet, col_name)).index(row_name) + 1
	except ValueError:
		return None

class Db():
	def __init__(self):
		with open('data/teachers.xlsx', 'rb') as f:
			self.ts = readxl(f).ws(ws='Sheet1')
		with open('data/students.xlsx', 'rb') as f:
			self.sb = readxl(f)

	def sqlWrite(self, quary):
		with sqlite3.connect(DATABASE_NAME) as con:
			cur = con.cursor()
			cur.execute(quary)
			con.commit()

	def sqlGet(self, quary):
		with sqlite3.connect(DATABASE_NAME) as con:
			cur = con.cursor()
			res = cur.execute(quary)
			return res.fetchone()

	def sqlGetAll(self, quary):
		with sqlite3.connect(DATABASE_NAME) as con:
			cur = con.cursor()
			res = cur.execute(quary)
			return res.fetchall()

	def sqlCreateTable(self, sem):
		self.sqlWrite(f"""CREATE TABLE 
			IF NOT EXISTS 
			s{sem}(time, teacher_phone_no, gr_no, subject)""")

	def getAttendance(self, sem, gr_no, time, subject):
		self.sqlCreateTable(sem)
		return self.sqlGetAll(f"""
			SELECT * FROM s{sem}
			WHERE gr_no = '{gr_no}'
			AND time = '{time}'
			AND subject = '{subject}'
		""")

	def getAttendanceAllSub(self, sem, gr_no):
		self.sqlCreateTable(sem)
		return self.sqlGetAll(f"""
			SELECT * FROM s{sem}
			WHERE gr_no = '{gr_no}'
		""")

	def getAttendanceAllSubAtTime(self, sem, gr_no, time):
		self.sqlCreateTable(sem)
		return self.sqlGetAll(f"""
			SELECT * FROM s{sem}
			WHERE gr_no = '{gr_no}'
			AND time = '{time}'
		""")

	def getAttendanceTotal(self, sem, gr_no, subject):
		self.sqlCreateTable(sem)
		return self.sqlGetAll(f"""
			SELECT * FROM s{sem}
			WHERE gr_no = '{gr_no}'
			AND subject = '{subject}'
		""")

	def getAttendanceCount(self, stds, days):
		new_stds = []
		for std in stds:
			minus = datetime.now() - timedelta(days)
			if datetime.strptime(std[0], "%Y-%m-%d") > minus:
				new_stds.append(std)

		return new_stds

	def getAttendanceMaxCount(self, stds, days = 0):
		if days:
			stds = self.getAttendanceCount(stds, days)

		gr_nos = [std[2] for std in stds]

		if not gr_nos:
			return 0

		return max([gr_nos.count(gr_no) for gr_no in gr_nos])

	def getStudentsAttendanceTotal(self, sem, subject):
		self.sqlCreateTable(sem)
		stds = []
		if subject == "Total":
			stds = self.sqlGetAll(f"""
				SELECT * FROM s{sem}
			""")
		else:
			stds = self.sqlGetAll(f"""
				SELECT * FROM s{sem}
				WHERE subject = '{subject}'
			""")

		return {
			"week": self.getAttendanceMaxCount(stds, 7),
			"month": self.getAttendanceMaxCount(stds, 30),
			"quarter": self.getAttendanceMaxCount(stds, 91),
			"total": self.getAttendanceMaxCount(stds)
		}

	def getStudentsWithAttendance(self, subject, pass_sem = 0, gr_no = 0, time = date.today()):
		sem = pass_sem or self.getSemBySubject(subject)

		stds = []
		if gr_no == 0:
			stds = self.getStudents(sem)
		else:
			stds = [self.getStudent(gr_no, sem)]

		li = []
		if pass_sem == 0:
			for std in stds:
				li.append({
					"info": std, 
					"result": {
						"today": len(self.getAttendance(sem, std[1], time, subject)),
						"total": len(self.getAttendanceTotal(sem, std[1], subject))
					}
				})
			return li

		for std in stds:
			if subject == "Total":
				total_std = self.getAttendanceAllSub(sem, std[1])
				li.append({
					"info": std,
					"result": {
						"week": len(self.getAttendanceCount(total_std, 7)),
						"month": len(self.getAttendanceCount(total_std, 39)),
						"quarter": len(self.getAttendanceCount(total_std, 91)),
						"total": len(total_std)
					}
				})
			else:
				total_std = self.getAttendanceTotal(sem, std[1], subject)
				li.append({
					"info": std, 
					"result": {
						"today": len(self.getAttendance(sem, std[1], time, subject)),
						"week": len(self.getAttendanceCount(total_std, 7)),
						"month": len(self.getAttendanceCount(total_std, 30)),
						"quarter": len(self.getAttendanceCount(total_std, 91)),
						"total": len(total_std)
					}
				})

		return li

	def getAttendanceForStdView(self, gr_no, sem):
		subjects = self.getSubjectsBySem(sem)
		res = {}

		for subject in subjects:
			total_std = self.getAttendanceTotal(sem, gr_no, subject)
			dash_index = subject.find("-") + 1
			subject_name = subject[dash_index:]
			res[subject_name] = {
				"today": len(self.getAttendance(sem, gr_no, date.today(), subject)),
				"week": len(self.getAttendanceCount(total_std, 7)),
				"month": len(self.getAttendanceCount(total_std, 30)),
				"quarter": len(self.getAttendanceCount(total_std, 91)),
				"total": len(total_std),
				"subject_total": self.getStudentsAttendanceTotal(sem, subject),
			}

		total_std = self.getAttendanceAllSub(sem, gr_no)
		res["Total"] = {
			"today": len(self.getAttendanceAllSubAtTime(sem, gr_no, date.today())),
			"week": len(total_std),
			"month": len(self.getAttendanceCount(total_std, 7)),
			"quarter": len(self.getAttendanceCount(total_std, 30)),
			"total": len(self.getAttendanceCount(total_std, 91)),
			"class_total": self.getStudentsAttendanceTotal(sem, "Total"),
		}

		return res

	def addAttendanceToDate(self, teacher_phone_no, gr_no, subject, pass_sem = 0, time = date.today()):
		if subject == "Total" or not subject:
			return

		sem = pass_sem or self.getSemBySubject(subject)

		self.sqlCreateTable(sem)
		self.sqlWrite(f"""
			INSERT INTO s{sem}(time, teacher_phone_no, gr_no, subject)
			VALUES ('{time}', '{teacher_phone_no}', '{gr_no}', '{subject}')
		""")

	def removeAttendanceToDate(self, gr_no, subject, pass_sem = 0, time = date.today()):
		if subject == "Total" or not subject:
			return

		sem = pass_sem or self.getSemBySubject(subject)

		rowid = self.sqlGet(f"""
			SELECT rowid FROM s{sem}
			WHERE time = '{time}'
			AND gr_no = '{gr_no}'
			AND subject = '{subject}'
		""")

		if rowid:
			return self.sqlWrite(f"""
				DELETE FROM s{sem}
				WHERE rowid = {rowid[0]}
			""")

	def getSems(self):
		return self.sb.ws_names

	def getSemBySubject(self, subject):
		self.sb.ws_names
		dash_index = subject.find("-")
		sub_sem = subject[:dash_index]

		for sem in self.sb.ws_names:
			if sem == sub_sem:
				return sem

	def getStudent(self, gr_no, sem):
		sem_st = self.sb.ws(sem)
		return sem_st.row(row=row_index(sem_st, "gr_no", gr_no))

	def getStudentWitoutSem(self, gr_no):
		for sem in self.sb.ws_names:
			sem_st = self.sb.ws(sem)
			index = row_index(sem_st, "gr_no", gr_no)
			if index:
				std = sem_st.row(row=index)
				return [sem] + std

	def getStudents(self, sem):
		return sorted(list(self.sb.ws(sem).rows)[1:])

	def getTeacher(self, phone_no):
		return self.ts.row(row=row_index(self.ts, "phone_no", phone_no))

	def getTeacherPassword(self, phone_no):
		return self.ts.index(
			row=row_index(self.ts, "phone_no", phone_no), 
			col=col_index(self.ts, "password")
		)

	def getTeachers(self):
		return sorted(list(self.ts.rows)[1:])

	def getSubjects(self):
		subjects = self.ts.col(col=col_index(self.ts, "subjects"))[1:]
		subjects = [subject.split(", ") for subject in subjects]
		subjects = sorted(set(chain.from_iterable(subjects)))
		return subjects

	def getSubjectsBySem(self, sem):
		d = {}
		for sub in self.getSubjects():
			if sub.find(f"{sem}-") + 1:
				dash_index = sub.find("-") + 1
				d[sub] = sub[dash_index:]

		return d

# db = Db()
# print(db.getStudentsWithAttendance("3-HHGW", "Semester 3", "JXEUKA"))