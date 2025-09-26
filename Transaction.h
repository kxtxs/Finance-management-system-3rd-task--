#pragma once
// Ensures this header file is included only once during compilation,
// preventing redefinition of structures and classes.

#include <string>
// Include std::string for storing wallet names and transaction categories

#include <ctime>
// Include time_t and functions for date and time manipulation

enum class WalletType { DEBIT, CREDIT };
// Enumeration WalletType to define the type of wallet:
// DEBIT – regular debit wallet
// CREDIT – credit card with a limit

struct Transaction {
    // Structure Transaction to store information about a single transaction

    std::string category;
    // Category of the expense/deposit (e.g., "Groceries", "Transport", or "Deposit")

    double amount;
    // Amount of the transaction

    time_t date;
    // Date and time of the transaction (time_t, seconds since 1970-01-01)

    bool isExpense;
    // true – transaction is an expense
    // false – transaction is a deposit

    std::string walletName;
    // Name of the wallet this transaction belongs to

    Transaction() = default;
    // Default constructor, does not initialize fields explicitly
    // Used to create empty Transaction objects

    Transaction(const std::string& wname, const std::string& cat, double amt, bool expense)
        : category(cat), amount(amt), date(time(nullptr)), isExpense(expense), walletName(wname) {
        // Constructor for quick creation of a transaction
        // wname – wallet name
        // cat – transaction category
        // amt – transaction amount
        // expense – whether it is an expense
        // date is automatically set to the current time (time(nullptr))
    }
};
