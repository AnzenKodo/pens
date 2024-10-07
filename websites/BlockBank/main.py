from flask import Flask, render_template, request, jsonify, redirect, url_for, flash
from flask_sqlalchemy import SQLAlchemy
from flask_login import LoginManager, UserMixin, login_user, login_required, logout_user, current_user
from werkzeug.security import generate_password_hash, check_password_hash
import hashlib
from datetime import datetime

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///blockchain_banking.db'
app.config['SECRET_KEY'] = 'your_secret_key_here'  # Change this to a random secret key
db = SQLAlchemy(app)
login_manager = LoginManager(app)
login_manager.login_view = 'login'

class User(UserMixin, db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(80), unique=True, nullable=False)
    password_hash = db.Column(db.String(120), nullable=False)

    def set_password(self, password):
        self.password_hash = generate_password_hash(password)

    def check_password(self, password):
        return check_password_hash(self.password_hash, password)

class Block(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    timestamp = db.Column(db.DateTime, nullable=False, default=datetime.utcnow)
    previous_hash = db.Column(db.String(64), nullable=False)
    nonce = db.Column(db.Integer, nullable=False)
    transactions = db.relationship('Transaction', backref='block', lazy=True)

    @property
    def hash(self):
        return calculate_hash(self)

class Transaction(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    sender = db.Column(db.String(80), nullable=False)
    receiver = db.Column(db.String(80), nullable=False)
    amount = db.Column(db.Float, nullable=False)
    sim_serial = db.Column(db.String(120), nullable=False)
    block_id = db.Column(db.Integer, db.ForeignKey('block.id'), nullable=True)

@login_manager.user_loader
def load_user(user_id):
    return User.query.get(int(user_id))

def calculate_hash(block):
    block_content = f"{block.id}{block.timestamp}{block.previous_hash}{block.nonce}"
    for transaction in block.transactions:
        block_content += f"{transaction.sender}{transaction.receiver}{transaction.amount}{transaction.sim_serial}"
    return hashlib.sha256(block_content.encode()).hexdigest()

@app.route('/')
@login_required
def index():
    return render_template('index.html')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        user = User.query.filter_by(username=username).first()
        if user and user.check_password(password):
            login_user(user)
            return redirect(url_for('index'))
        else:
            flash('Invalid username or password')
    return render_template('login.html')

@app.route('/logout')
@login_required
def logout():
    logout_user()
    return redirect(url_for('login'))

@app.route('/register', methods=['GET', 'POST'])
def register():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')

        if User.query.filter_by(username=username).first():
            flash('Username already exists')
        else:
            new_user = User(username=username)
            new_user.set_password(password)
            db.session.add(new_user)
            db.session.commit()
            flash('Registration successful')
            return redirect(url_for('login'))
    return render_template('register.html')

@app.route('/miner')
@login_required
def miner():
    return render_template('miner.html')

@app.route('/blockchain')
@login_required
def blockchain():
    return render_template('blockchain.html')

@app.route('/api/transaction', methods=['POST'])
@login_required
def make_transaction():
    data = request.json
    new_transaction = Transaction(
        sender=data['sender'],
        receiver=data['receiver'],
        amount=data['amount'],
        sim_serial=data['simSerial']  # Use the SIM serial from the form data
    )
    db.session.add(new_transaction)
    db.session.commit()
    return jsonify({'status': 'success'}), 200

@app.route('/api/transactions', methods=['GET'])
@login_required
def get_transactions():
    transactions = Transaction.query.all()
    return jsonify([{
        'sender': t.sender,
        'receiver': t.receiver,
        'amount': t.amount,
        'simSerial': t.sim_serial,
        'blockNumber': t.block.id if t.block else None
    } for t in transactions])

@app.route('/api/mine', methods=['POST'])
@login_required
def mine_block():
    last_block = Block.query.order_by(Block.id.desc()).first()
    previous_hash = last_block.hash if last_block else '0' * 64

    new_block = Block(previous_hash=previous_hash, nonce=0)
    db.session.add(new_block)

    unconfirmed_transactions = Transaction.query.filter_by(block_id=None).all()
    for transaction in unconfirmed_transactions:
        new_block.transactions.append(transaction)

    db.session.commit()

    while not new_block.hash.startswith('00'):
        new_block.nonce += 1
        db.session.commit()

    return jsonify({
        'status': 'success',
        'block_number': new_block.id,
        'timestamp': new_block.timestamp.isoformat(),
        'previous_hash': new_block.previous_hash,
        'hash': new_block.hash,
        'nonce': new_block.nonce,
        'transactions': len(new_block.transactions)
    }), 200

@app.route('/api/blockchain', methods=['GET'])
@login_required
def get_blockchain():
    blocks = Block.query.all()
    return jsonify([{
        'id': b.id,
        'timestamp': b.timestamp.isoformat(),
        'previous_hash': b.previous_hash,
        'hash': b.hash,
        'nonce': b.nonce,
        'transactions': len(b.transactions)
    } for b in blocks])

def init_db():
    with app.app_context():
        db.create_all()

if __name__ == '__main__':
    init_db()
    app.run(debug=True)
