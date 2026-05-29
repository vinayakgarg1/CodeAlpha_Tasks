#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

// 1. Transaction Class (Struct used for simplicity as it only holds data)
struct Transaction {
    string type;
    double amount;
    double resultingBalance;
};

// 2. Account Class
class Account {
private:
    int accountNumber;
    double balance;
    vector<Transaction> transactionHistory;

public:
    Account(int accNum = 0) : accountNumber(accNum), balance(0.0) {}
    int getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            transactionHistory.push_back({"Deposit", amount, balance});
            cout << "[SUCCESS] Deposited Rs" << fixed << setprecision(2) << amount << " successfully.\n";
        } else cout << "[ERROR] Deposit amount must be positive.\n";
    }

    bool withdraw(double amount) {
        if (amount > 0 && balance >= amount) {
            balance -= amount;
            transactionHistory.push_back({"Withdrawal", amount, balance});
            cout << "[SUCCESS] Withdrew Rs" << fixed << setprecision(2) << amount << " successfully.\n";
            return true;
        } else if (amount <= 0) cout << "[ERROR] Withdrawal amount must be positive.\n";
        else cout << "[ERROR] Insufficient funds.\n";
        return false;
    }

    // Helper for transfers so it records properly in the history
    void recordTransfer(string type, double amount) {
        if (type == "Transfer Out") balance -= amount;
        else if (type == "Transfer In") balance += amount;
        transactionHistory.push_back({type, amount, balance});
    }

    void displayHistory() const {
        if (transactionHistory.empty()) {
            cout << "No recent transactions.\n";
            return;
        }
        cout << left << setw(15) << "Type" << setw(15) << "Amount" << "Balance" << endl;
        cout << "-------------------------------------------\n";
        for (const auto& t : transactionHistory) {
            cout << left << setw(15) << t.type 
                 << "Rs" << setw(14) << fixed << setprecision(2) << t.amount 
                 << "Rs" << t.resultingBalance << endl;
        }
    }
};

// 3. Customer Class
class Customer {
private:
    string name;
    int customerID;
    Account account;

public:
    Customer(string n, int id, int accNum) : name(n), customerID(id), account(accNum) {}

    string getName() const { return name; }
    int getID() const { return customerID; }
    Account& getAccount() { return account; } // Returns reference to allow modifications
};

// Global Data and Helpers
vector<Customer> customers;
int nextCustomerID = 1;
int nextAccountNumber = 1001;

// Helper function to find a customer by their account number
Customer* findCustomerByAccount(int accNum) {
    for (auto& c : customers) {
        if (c.getAccount().getAccountNumber() == accNum) {
            return &c;
        }
    }
    return nullptr;
}

// Menu Functions
void createAccount() {
    string name;
    cout << "\n--- CREATE NEW ACCOUNT ---\n";
    cout << "Enter customer name: ";
    cin >> ws; // Clear leading whitespace
    getline(cin, name);

    Customer newCustomer(name, nextCustomerID++, nextAccountNumber++);
    customers.push_back(newCustomer);

    cout << "[SUCCESS] Account created for " << name << ".\n";
    cout << "Your Account Number is: " << newCustomer.getAccount().getAccountNumber() << "\n";
}

void performDeposit() {
    int accNum;
    double amount;
    cout << "\n--- DEPOSIT FUNDS ---\n";
    cout << "Enter Account Number: ";
    cin >> accNum;

    Customer* cust = findCustomerByAccount(accNum);
    if (cust) {
        cout << "Enter amount to deposit: Rs";
        cin >> amount;
        cust->getAccount().deposit(amount);
    } else cout << "[ERROR] Account not found.\n";
}

void performWithdrawal() {
    int accNum;
    double amount;
    cout << "\n--- WITHDRAW FUNDS ---\n";
    cout << "Enter Account Number: ";
    cin >> accNum;

    Customer* cust = findCustomerByAccount(accNum);
    if (cust) {
        cout << "Enter amount to withdraw: Rs";
        cin >> amount;
        cust->getAccount().withdraw(amount);
    } else cout << "[ERROR] Account not found.\n";
}

void performTransfer() {
    int fromAcc, toAcc;
    double amount;
    cout << "\n--- TRANSFER FUNDS ---\n";
    cout << "Enter Your Account Number: ";
    cin >> fromAcc;
    cout << "Enter Destination Account Number: ";
    cin >> toAcc;

    Customer* sender = findCustomerByAccount(fromAcc);
    Customer* receiver = findCustomerByAccount(toAcc);

    if (sender && receiver && sender != receiver) {
        cout << "Enter amount to transfer: Rs";
        cin >> amount;
        if (amount > 0 && sender->getAccount().getBalance() >= amount) {
            sender->getAccount().recordTransfer("Transfer Out", amount);
            receiver->getAccount().recordTransfer("Transfer In", amount);
            cout << "[SUCCESS] Successfully transferred Rs" << amount << " to account " << toAcc << ".\n";
        } else cout << "[ERROR] Insufficient funds or invalid amount.\n";
    } else cout << "[ERROR] Invalid account numbers provided.\n";
}

void viewAccountDetails() {
    int accNum;
    cout << "\n--- ACCOUNT DETAILS & HISTORY ---\n";
    cout << "Enter Account Number: ";
    cin >> accNum;
    Customer* cust = findCustomerByAccount(accNum);
    if (cust) {
        cout << "\nCustomer Name  : " << cust->getName() << "\n";
        cout << "Customer ID    : " << cust->getID() << "\n";
        cout << "Account Number : " << cust->getAccount().getAccountNumber() << "\n";
        cout << "Current Balance: Rs" << fixed << setprecision(2) << cust->getAccount().getBalance() << "\n\n";
        cout << "--- Transaction History ---\n";
        cust->getAccount().displayHistory();
    } else cout << "[ERROR] Account not found.\n";
}

int main() {
    int choice;
    while (true) {
        cout << "\n=======================================\n";
        cout << "            BANKING SYSTEM             \n";
        cout << "=======================================\n";
        cout << "1. Create New Account\n";
        cout << "2. Deposit Funds\n";
        cout << "3. Withdraw Funds\n";
        cout << "4. Transfer Funds\n";
        cout << "5. View Account Details & History\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        switch (choice) {
            case 1: createAccount(); break;
            case 2: performDeposit(); break;
            case 3: performWithdrawal(); break;
            case 4: performTransfer(); break;
            case 5: viewAccountDetails(); break;
            case 6: 
                cout << "Thank you for using the Banking System. Goodbye!\n"; 
                return 0;
            default: cout << "[ERROR] Invalid choice. Please select 1-6.\n";
        }
    }
    return 0;
}