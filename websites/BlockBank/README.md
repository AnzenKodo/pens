# BlockBank

Blockchain Technology for Secured Transactions in Banking Customers who use internet banking have the flexibility to manage their assets sometimes when and wherever they choose. Any web-based transactions will, in any instance, be vulnerable to privacy risks. The current system makes use of two-way validation factors (OTP), which are easily cracked by cybercriminals, causing customers to have their personal information invaded without having access to the aggressor's recognised evidence. As a result, in this research, we suggest a flexible SIM sequential-based check approach to safeguard mobile transactions using a waiter-side secure platform built on the Blockchain. The customer's record has the supporter character module (sim) serial number, and if a gate crasher tries to initiate a transaction from another sim, there is a mix-up of the login credentials, at which point the system communicates the intrusive location information to the bank. The bank then sends an email to the subscribed customer alerting them to the peculiarities of the intruder. There is no risk of a gate crasher initiating the transaction from another device because the mobile sim chronicle number is unique to the sim and isn't literally very distanced, eliminating the concerns associated with OTP. By verifying the updated markings throughout the transaction and calculating the contract for transaction confirmation, the Ethereum Blockchain breakthrough provides server-side information base security. For reliable financial exchange, blockchain-based security is mathematically validated.

## Pre-Requisite

- Install [Python](https://python.org) on your system.
- Install `pip` package manager.
- Install `git` to clone repo.
- Clone the repo:
  ```
  git clone https://github.com/AnzenKodo/BlockBank
  cd BlockBank
  ```
- Initialize virtual environment python:
  ```sh
  python -m venv venv
  ```
- Add to source:
  - Windows
    - CMD 
      ```cmd
      ./venv/Script/activate
      ```
    - Powershell
      ```ps
      ./venv/Script/activate.ps1
      ```
  - Linux
    ```sh
    source ./venv/bin/activate
    ```
- Install required packages:
  ```
  pip install -r requirements.txt
  ```
## Running the program

```python
python main.py
```
