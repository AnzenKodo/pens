# studentlog
A modern student management system.

## Getting Started

### Requirements
- [git](https://git-scm.com/)
- [Python](https://python.org)
- [pip](https://pip.pypa.io/en/stable/installation/)

### Installing
- Fist [Fork](https://github.com/AnzenKodo/studentlog/fork) the repo.
- Clone the forked repo & go the cloned repo.
```bash
git clone https://github.com/<your_username>/studentlog.git
cd studentlog
```
- Create `.env` file and Add following environment variables in it:
```env
DATABASE_URL=postgres://username:name@domain.com/collage
TWILIO_ACCOUNT_SID=****************************
TWILIO_AUTH_TOKEN=********************************
TWILIO_PHONE_NO=+111111111111
ADMIN_NAME=username
ADMIN_PASSWORD=password
```
- Run project:
```bash
python ./setup.py
```
