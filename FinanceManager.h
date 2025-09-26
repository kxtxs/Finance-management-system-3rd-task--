#pragma once
// Prevents multiple inclusions of this file. Alternative to traditional include guards.

#include "Wallet.h"
#include "Transaction.h"
// Include the Wallet and Transaction classes we defined earlier.

#include <vector>
#include <string>
#include <utility>
// Standard libraries:
// vector – to store the list of wallets
// string – for working with strings
// utility – for std::pair (used in topCategories)

class FinanceManager {
private:
    std::vector<Wallet> wallets;
    // Vector of wallets managed by the FinanceManager

    static time_t nowTime();
    static time_t periodStartDays(int days);
    static std::string formatTime(time_t t);
    // Static helper functions for working with time:
    // nowTime() – returns the current time
    // periodStartDays(days) – returns the start of the period in seconds ago
    // formatTime(t) – formats time_t into a readable date string

public:
    bool addWallet(const std::string& name, WalletType type, double creditLimit = 0.0);
    // Adds a new wallet. Returns false if a wallet with the same name already exists.

    Wallet* getWallet(const std::string& name);
    // Returns a pointer to a wallet by name, or nullptr if not found.

    const std::vector<Wallet>& getAllWallets() const;
    // Returns the list of all wallets (for const access).

    void depositToWallet(const std::string& name, double amt);
    // Deposit money into a specific wallet.

    void spendFromWallet(const std::string& name, double amt, const std::string& category);
    // Spend money from a wallet and add an expense transaction.

    void showAllTransactions(int days = 0) const;
    // Displays all transactions for the last "days" days.
    // If days = 0, shows all transactions.

    void saveReportToFile(const std::string& filename, int days = 0) const;
    // Saves a report of transactions to a file.

    std::vector<Transaction> collectTransactions(int days = 0) const;
    // Collects all transactions for a given period into a vector.

    std::vector<Transaction> topExpenses(int days = 0, int topN = 3) const;
    // Returns the topN largest expenses for a given period.

    std::vector<std::pair<std::string, double>> topCategories(int days = 0, int topN = 3) const;
    // Returns the topN categories with the highest total expenses for a given period.

    void saveTopExpensesToFile(const std::string& filename, int days = 0, int topN = 3) const;
    // Saves the top expenses to a file.

    void saveTopCategoriesToFile(const std::string& filename, int days = 0, int topN = 3) const;
    // Saves the top categories to a file.

    void printTopExpensesConsole(int days = 0, int topN = 3) const;
    // Prints the top expenses to the console.

    void printTopCategoriesConsole(int days = 0, int topN = 3) const;
    // Prints the top categories to the console.
};
