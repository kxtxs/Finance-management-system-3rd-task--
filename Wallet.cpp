#include "Wallet.h"
// Include the Wallet.h header to implement the Wallet class methods.

Wallet::Wallet(const std::string& n, WalletType t, double creditLim)
    : name(n), type(t), balance(0.0), creditLimit(creditLim) {
    // Wallet class constructor
    // Initialization using member initializer list:
    // name = n, type = t, balance = 0, creditLimit = creditLim
    // transactions is automatically created empty (default constructor of vector)
}

const std::string& Wallet::getName() const { return name; }
// Getter method for wallet name
// const after the method means it does not modify the object

WalletType Wallet::getType() const { return type; }
// Getter for wallet type (DEBIT or CREDIT)

double Wallet::getBalance() const { return balance; }
// Getter for the current wallet balance

double Wallet::getCreditLimit() const { return creditLimit; }
// Getter for the wallet's credit limit

const std::vector<Transaction>& Wallet::getTransactions() const { return transactions; }
// Getter for the list of transactions
// Returns a const reference to avoid copying and prevent modification

void Wallet::deposit(double amt) {
    // Method to deposit money into the wallet
    if (amt <= 0) return;
    // Check: if amount ≤ 0, do nothing
    balance += amt;
    // Increase balance by deposit amount
    transactions.emplace_back(name, "Deposit", amt, false);
    // Add a transaction to the transactions vector:
    // walletName = name, category = "Deposit", amount = amt, isExpense = false
}

bool Wallet::spend(double amt, const std::string& category) {
    // Method to spend money from the wallet
    if (amt <= 0) return false;
    // Check: negative or zero expenses are not allowed

    if (type == WalletType::DEBIT) {
        // If the wallet is DEBIT type
        if (amt > balance) return false;
        // Do not allow spending more than the balance
        balance -= amt;
        // Decrease the balance
        transactions.emplace_back(name, category, amt, true);
        // Add a transaction to the vector: this is an expense (isExpense = true)
        return true;
        // Operation successful
    }
    else { // CREDIT
        // If the wallet is CREDIT type
        if (balance - amt < -creditLimit) return false;
        // Check: the balance after spending cannot exceed the credit limit
        balance -= amt;
        // Decrease balance (may become negative if credit is used)
        transactions.emplace_back(name, category, amt, true);
        // Add a transaction to the vector
        return true;
        // Operation successful
    }
}
