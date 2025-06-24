# 🏦 Prasun's Bank of India - CLI Banking System

## Overview
This project is a **Command Line Interface (CLI) based Banking System** developed in **C++** using **Object-Oriented Programming (OOP)** principles.  
It allows **account holders** to manage their bank accounts, perform transactions, and view statements. It also includes a **branch manager module** with administrative privileges.

## Features
✅ User Registration & Login  
✅ Multiple Account Management (Savings, Checking/Current)  
✅ Deposit and Withdrawal Operations  
✅ Transaction Statements for Each Account  
✅ Password Management for Account Holders  
✅ Branch Manager Login with Admin Controls  
✅ Secure Credential Verification  
✅ Modular, Scalable, and Optimized Code Structure

## How to Run
1. Ensure you have a C++ compiler (like `g++`) installed.
2. Compile the program:
   ```bash
   g++ -o banking_system banking_system.cpp
   ```
3. Run the program:
   ```bash
   ./banking_system
   ```

## Functionalities

### For Users:
- **Register:** Create a unique username and password.
- **Login:** Secure access to personal accounts.
- **Create Account:** Open Savings or Checking/Current accounts.
- **Deposit/Withdraw:** Add or remove funds.
- **Balance Check:** View current balance.
- **Transaction Statement:** View deposit and withdrawal history.
- **Password Change:** Update login password.

### For Branch Manager:
- **View All Users:** See all users and their accounts.
- **View Account Statement:** Check transactions of any account.

## Technologies Used
- **Language:** C++
- **Paradigm:** Object-Oriented Programming (OOP)
- **Interface:** Command Line

## Future Enhancements
- File-based data storage (persistent user data)
- Interest calculation for savings accounts
- Transaction timestamps
- User-friendly CLI improvements
- Enhanced security with encrypted passwords

## Project Structure
- `User`: Handles user accounts and authentication.
- `Account`: Manages account operations and transactions.
- `Transaction`: Records each deposit and withdrawal.
- `Admin`: Grants privileged access to managers.