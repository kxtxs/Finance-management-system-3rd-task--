#pragma once
// Prevents multiple inclusions of this header file.
// If this header is already included, it will not be included again.
// Alternative to traditional include guards (#ifndef ... #define ... #endif)

#include "Transaction.h" 
// Include Transaction.h because Wallet stores a list of transactions.
// Transaction.h contains the Transaction struct and the WalletType enum.

#include <string>  
// Include std::string to store wallet names and transaction categories.

#include <vector>  
// Include std::vector to store a dynamic list of transactions.

class Wallet {
    // Declaration of the Wallet class, representing a wallet or credit card.
    // The class encapsulates data (balance, transactions) and provides methods to work with them.

private:  // private section
    std::string name;
    // Name of the wallet/card. Used to identify the wallet.

    WalletType type;
    // Type of wallet: DEBIT (regular) or CREDIT (credit card).
    // WalletType is defined in Transaction.h as an enum class.

    double balance;
    // Current balance of the wallet.
    // For DEBIT: money available; for CREDIT: current debt.

    double creditLimit;
    // Maximum allowed credit limit (only for credit cards).
    // For DEBIT wallets, it is usually 0.

    std::vector<Transaction> transactions;
    // List of all transactions (deposits and expenses) for this wallet.
    // Transaction contains date, amount, category, and type (expense/deposit).

public:  // public section — accessible from outside
    Wallet(const std::string& n, WalletType t, double creditLim = 0.0);
    // Wallet constructor.
    // n — name, t — type, creditLim — credit limit (default 0.0).
    // Initializes balance = 0 and transactions as an empty vector.

    const std::string& getName() const;
    // Getter: returns the wallet name.
    // 'const' after the function means the method does not modify the object.

    WalletType getType() const;
    // Getter: returns the wallet type (DEBIT or CREDIT).

    double getBalance() const;
    // Getter: returns the current wallet balance.

    double getCreditLimit() const;
    // Getter: returns the credit limit.

    const std::vector<Transaction>& getTransactions() const;
    // Getter: returns a const reference to the vector of transactions.
    // Using const reference allows reading transactions without copying.

    void deposit(double amt);
    // Method to add money to the wallet.
    // amt — deposit amount.
    // Adds a Deposit-type transaction and increases the balance.

    bool spend(double amt, const std::string& category);
    // Method to spend money from the wallet.
    // amt — expense amount, category — expense category.
    // For DEBIT: if balance < amt → returns false.
    // For CREDIT: balance cannot go below -creditLimit.
    // Adds an Expense-type transaction.
};
