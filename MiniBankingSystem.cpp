
// Mini Banking System
// This program simulates a file based banking system
// Features: Account creation, deposit, withdrawal, balance inquiry, and listing all accounts
// Data is stored in a file using object oriented programming. 

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <ctime>
#include <sstream>


using namespace std;


// Account class

class Account {
private:
    string accountNo; 
    string ownerName; 
    double balance; 

public:
    // Constructor
    Account(string no, string name, double initialBalance = 0.0)
        : accountNo(no), ownerName(name), balance(initialBalance) {
    }

    // Destructor: 

    ~Account() {}

    // Getter methods
    string getAccountNo() const { return accountNo; }
    string getOwnerName() const { return ownerName; }
    double getBalance() const { return balance; }

    // Deposit money
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << amount << " TL deposited. New balance: " << balance << " TL\n";
        }
        else {
            cout << "Invalid amount!\n";
        }
    }

    // Withdraw money

    bool withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << amount << " TL withdrawn. New balance: " << balance << " TL\n";
            return true;
        }
        else {
            cout << "Insufficient balance or invalid amount!\n";
            return false;
        }
    }
};

// Bank class: Manages accounts and file operations
class Bank {
private:
    vector<Account> accounts; 
    string fileName; 
    static int accountCounter; 

    // Load accounts from file

    void loadAccounts() {
        ifstream file(fileName);
        if (!file.is_open()) {
            cout << "File could not be opened: " << fileName << ". A new file will be created.\n";
            return;
        }
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string no, name;
            double balance;
            ss >> no;
            getline(ss >> ws, name, '"');
            ss >> balance;
            Account account(no, name, balance);
            accounts.push_back(account);
        }
        file.close();
    }

    // Save accounts to file
    void saveAccounts() {
        ofstream file(fileName);
        if (!file.is_open()) {
            cout << "File could not be written: " << fileName << endl;
            return;
        }
        for (const Account& account : accounts) {
            file << account.getAccountNo() << " \"" << account.getOwnerName() << "\" " << account.getBalance() << "\n";
        }
        file.close();
    }

public:
    // Constructor  (loads accounts)
    Bank(string file = "accounts.txt") : fileName(file) {
        loadAccounts();
    }

    // Destructor  (Saves accounts to file)
    ~Bank() {
        saveAccounts();
    }

    // Create a new account
    void createAccount(string name) {
        string accountNo = to_string(time(nullptr)) + "_" + to_string(accountCounter++); // Unique account number
        Account newAccount(accountNo, name, 0.0);
        accounts.push_back(newAccount);
        saveAccounts();
        cout << "Account created. Account No: " << accountNo << "\n";
    }

    // Find account by account number
    Account* findAccount(string accountNo) {
        for (Account& account : accounts) {
            if (account.getAccountNo() == accountNo) {
                return &account;
            }
        }
        return nullptr;
    }

    // Deposit money to account
    void deposit(string accountNo, double amount) {
        Account* account = findAccount(accountNo);
        if (account) {
            account->deposit(amount);
            saveAccounts();
        }
        else {
            cout << "Account not found!\n";
        }
    }

    // Withdraw money from account
    void withdraw(string accountNo, double amount) {
        Account* account = findAccount(accountNo);
        if (account) {
            if (account->withdraw(amount)) {
                saveAccounts();
            }
        }
        else {
            cout << "Account not found!\n";
        }
    }

    // Display account balance
    void displayBalance(string accountNo) {
        Account* account = findAccount(accountNo);
        if (account) {
            cout << "Account No: " << account->getAccountNo()
                << ", Owner: " << account->getOwnerName()
                << ", Balance: " << account->getBalance() << " TL\n";
        }
        else {
            cout << "Account not found!\n";
        }
    }

    // List all accounts
    void listAllAccounts() {
        if (accounts.empty()) {
            cout << "No accounts registered!\n";
            return;
        }
        cout << "\nAll Accounts:\n";
        for (const Account& account : accounts) {
            cout << "Account No: " << account.getAccountNo()
                << ", Owner: " << account.getOwnerName()
                << ", Balance: " << account.getBalance() << " TL\n";
        }
    }
};

// Static counter definition
int Bank::accountCounter = 0;

// Get integer input from user
int getIntInput(string message) {
    int number;
    while (true) {
        cout << message;
        cin >> number;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input! Please enter an integer.\n";
        }
        else {
            cin.ignore(1000, '\n');
            return number;
        }
    }
}

// This code taken input from user(of double type)


double getDoubleInput(string message) {
    double number;
    while (true) {
        cout << message;
        cin >> number;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input! Please enter a number.\n";
        }
        else {
            cin.ignore(1000, '\n');
            return number;
        }
    }
}

// Main menu and user interface

int main() {
    Bank bank;
    string accountNo, name;
    int choice;

    while (true) {
        cout << "\nMini Banking System\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Display Balance\n";
        cout << "5. List All Accounts\n";
        cout << "6. Exit\n";
        choice = getIntInput("Your choice: ");

        if (choice == 6) break;

        switch (choice) {
        case 1:
            cout << "Enter account owner's name: ";
            getline(cin, name);
            bank.createAccount(name);
            break;
        case 2:
            cout << "Enter account number: ";
            getline(cin, accountNo);
            bank.deposit(accountNo, getDoubleInput("Enter amount to deposit: "));
            break;
        case 3:
            cout << "Enter account number: ";
            getline(cin, accountNo);
            bank.withdraw(accountNo, getDoubleInput("Enter amount to withdraw: "));
            break;
        case 4:
            cout << "Enter account number: ";
            getline(cin, accountNo);
            bank.displayBalance(accountNo);
            break;
        case 5:
            bank.listAllAccounts();
            break;
        default:
            cout << "Invalid choice!\n";
        }
    }
    return 0;
}














































