#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> UsernamesInUse;
vector<string> Names;
vector<string> Passwords;

double accountNumber = 100000000;

class Transaction {
private:
    string description;
    double amount;

public:
    Transaction(const string& desc, double amt) : description(desc), amount(amt) {}

    string getDescription() const { return description; }
    double getAmount() const { return amount; }
};

class Account {
private:
    string accountType;
    int accnum;
    double amount;
    vector<Transaction> transactions;

public:
    Account(int accountnum, const string& type, double paisa) : accnum(accountnum), accountType(type), amount(paisa) {}

    void deposit(double deposit);
    void withdraw(double withdraw);
    void getStatement() const;
    int getAccNum() const { return accnum; }
    double getAmount() const { return amount; }
    string getAccType() const { return accountType; }
};

class User {
private:
    string username;
    vector<Account> accounts;

public:
    User(const string& uname) : username(uname) {}

    void addAccount(const Account& account) { accounts.push_back(account); }
    int getNumberOfAccounts() const { return accounts.size(); }
    int getAccountNumber(int index) const { return accounts[index].getAccNum(); }
    string getAccountType(int index) const { return accounts[index].getAccType(); }
    void showAccounts() const;
    void showAccountStatement(int index) const { accounts[index].getStatement(); }
    double getAccountBalance(int index) const { return accounts[index].getAmount(); }
    void depositInAccount(int index, double amt) { accounts[index].deposit(amt); }
    void withdrawFromAccount(int index, double amt) { accounts[index].withdraw(amt); }
};

void Account::deposit(double deposit) {
    amount += deposit;
    transactions.emplace_back("Deposit", deposit);
}

void Account::withdraw(double withdraw) {
    if (withdraw > amount) {
        cout << "Invalid withdrawal: Insufficient funds" << endl;
    } else {
        amount -= withdraw;
        transactions.emplace_back("Withdrawal", withdraw);
    }
}

void Account::getStatement() const {
    if (transactions.empty()) {
        cout << "No transactions yet." << endl;
        return;
    }
    for (const auto& transaction : transactions) {
        cout << transaction.getDescription() << ": " << transaction.getAmount() << endl;
    }
}

void User::showAccounts() const {
    cout << "You have the following accounts:" << endl;
    for (int i = 0; i < accounts.size(); ++i) {
        cout << (i + 1) << ". " << accounts[i].getAccNum() << " (" << accounts[i].getAccType() << ")" << endl;
    }
}

vector<User> Users;

void showHome();
void registerUser();
void loginUser();
void managerLogin();
int findUserIndex(const string& username);

int main() {
    showHome();
    return 0;
}

void showHome() {
    while (true) {
        int choice;
        cout << "\n\t\t==========================================" << endl;
        cout << "\t\t  WELCOME TO PRASUN'S BANK OF INDIA" << endl;
        cout << "\t\t==========================================" << endl;
        cout << "1. Register" << endl;
        cout << "2. Account Holder Login" << endl;
        cout << "3. Branch Manager Login" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: registerUser(); break;
            case 2: loginUser(); break;
            case 3: managerLogin(); break;
            case 0: cout << "Thank you for using our service!" << endl; return;
            default: cout << "Invalid choice! Try again." << endl;
        }
    }
}

void registerUser() {
    string username, name, password;

    cout << "Enter your Username: ";
    cin >> username;

    if (findUserIndex(username) != -1) {
        cout << "Sorry, Username is already in use." << endl;
        return;
    }

    cout << "Enter your Name: ";
    cin >> name;

    cout << "Enter your Password: ";
    cin >> password;

    UsernamesInUse.push_back(username);
    Names.push_back(name);
    Passwords.push_back(password);
    Users.emplace_back(username);

    cout << "Registration successful!" << endl;
}

void loginUser() {
    string username, password;
    cout << "Enter your Username: ";
    cin >> username;

    int userIndex = findUserIndex(username);
    if (userIndex == -1) {
        cout << "Username not found." << endl;
        return;
    }

    cout << "Enter your Password: ";
    cin >> password;

    if (Passwords[userIndex] != password) {
        cout << "Invalid Password." << endl;
        return;
    }

    char choice;
    while (true) {
        cout << "\nOptions: " << endl;
        cout << "N. Create a New Account" << endl;
        cout << "B. Check Account Balance" << endl;
        cout << "S. Get Account Statement" << endl;
        cout << "D. Deposit Money" << endl;
        cout << "W. Withdraw Money" << endl;
        cout << "P. Change Password" << endl;
        cout << "E. Exit to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 'N' || choice == 'n') {
            int accType;
            double initialDeposit;

            cout << "1. Savings Account\n2. Checking/Current Account\nEnter your choice: ";
            cin >> accType;

            cout << "Enter starting balance: ";
            cin >> initialDeposit;

            if (initialDeposit < 1000) {
                cout << "Insufficient initial deposit (minimum 1000 required)." << endl;
                continue;
            }

            string type = (accType == 1) ? "Savings" : "Checking/Current";
            Users[userIndex].addAccount(Account(accountNumber++, type, initialDeposit));
            cout << "Account created successfully!" << endl;

        } else if (choice == 'B' || choice == 'b') {
            Users[userIndex].showAccounts();
            int accNum;
            cout << "Enter Account Number: ";
            cin >> accNum;

            bool found = false;
            for (int i = 0; i < Users[userIndex].getNumberOfAccounts(); ++i) {
                if (Users[userIndex].getAccountNumber(i) == accNum) {
                    cout << "Current Balance: " << Users[userIndex].getAccountBalance(i) << endl;
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Account not found." << endl;

        } else if (choice == 'S' || choice == 's') {
            Users[userIndex].showAccounts();
            int accNum;
            cout << "Enter Account Number: ";
            cin >> accNum;

            bool found = false;
            for (int i = 0; i < Users[userIndex].getNumberOfAccounts(); ++i) {
                if (Users[userIndex].getAccountNumber(i) == accNum) {
                    Users[userIndex].showAccountStatement(i);
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Account not found." << endl;

        } else if (choice == 'D' || choice == 'd') {
            Users[userIndex].showAccounts();
            int accNum;
            double amount;
            cout << "Enter Account Number: ";
            cin >> accNum;
            cout << "Enter deposit amount: ";
            cin >> amount;

            bool found = false;
            for (int i = 0; i < Users[userIndex].getNumberOfAccounts(); ++i) {
                if (Users[userIndex].getAccountNumber(i) == accNum) {
                    Users[userIndex].depositInAccount(i, amount);
                    cout << "Deposit successful." << endl;
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Account not found." << endl;

        } else if (choice == 'W' || choice == 'w') {
            Users[userIndex].showAccounts();
            int accNum;
            double amount;
            cout << "Enter Account Number: ";
            cin >> accNum;
            cout << "Enter withdrawal amount: ";
            cin >> amount;

            bool found = false;
            for (int i = 0; i < Users[userIndex].getNumberOfAccounts(); ++i) {
                if (Users[userIndex].getAccountNumber(i) == accNum) {
                    Users[userIndex].withdrawFromAccount(i, amount);
                    cout << "Withdrawal attempted." << endl;
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Account not found." << endl;

        } else if (choice == 'P' || choice == 'p') {
            cout << "Enter new password: ";
            cin >> Passwords[userIndex];
            cout << "Password changed successfully." << endl;

        } else if (choice == 'E' || choice == 'e') {
            break;

        } else {
            cout << "Invalid choice." << endl;
        }
    }
}

void managerLogin() {
    string username, password;
    cout << "Enter Admin Username: ";
    cin >> username;

    if (username != "ADMIN123") {
        cout << "INVALID USERNAME!" << endl;
        return;
    }

    cout << "Enter Admin Password: ";
    cin >> password;

    if (password != "ADMIN123") {
        cout << "INVALID CREDENTIALS" << endl;
        return;
    }

    int choice;
    cout << "1. View all users and their accounts" << endl;
    cout << "2. Get statement of an account" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        for (size_t i = 0; i < Users.size(); ++i) {
            cout << UsernamesInUse[i] << endl;
            Users[i].showAccounts();
            cout << endl;
        }
    } else if (choice == 2) {
        string username;
        cout << "Enter account username: ";
        cin >> username;

        int userIndex = findUserIndex(username);
        if (userIndex == -1) {
            cout << "USERNAME NOT FOUND" << endl;
            return;
        }

        Users[userIndex].showAccounts();
        int accNum;
        cout << "Enter Account Number: ";
        cin >> accNum;

        bool found = false;
        for (int i = 0; i < Users[userIndex].getNumberOfAccounts(); ++i) {
            if (Users[userIndex].getAccountNumber(i) == accNum) {
                Users[userIndex].showAccountStatement(i);
                found = true;
                break;
            }
        }
        if (!found) cout << "Account not found." << endl;

    } else {
        cout << "Invalid choice." << endl;
    }
}

int findUserIndex(const string& username) {
    for (size_t i = 0; i < UsernamesInUse.size(); ++i) {
        if (UsernamesInUse[i] == username) return i;
    }
    return -1;
}
