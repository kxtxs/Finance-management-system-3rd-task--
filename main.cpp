#include <iostream>  // library for input/output (cout, cin)
#include <string>    // library for working with strings (std::string)
#include <limits>    // for numeric_limits (to clear input buffer)
#include "FinanceManager.h" // our custom header with the FinanceManager class

using namespace std; // so we can write cout, string without std::

/**
 * Function to choose the period (day, week, month, all time).
 * Returns the number of days (1, 7, 30, or 0 for "all time").
 */
int choosePeriodDays() {
    cout << "\nChoose period:\n1) Day\n2) Week\n3) Month\n0) All time\nYour choice: ";
    int ch;
    // if user entered a non-number → clear input and return 0
    if (!(cin >> ch)) {
        cin.clear(); // reset stream state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer
        return 0;
    }
    // clear buffer after input (to remove leftover input)
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // convert choice to number of days
    switch (ch) {
    case 1: return 1;   // day
    case 2: return 7;   // week
    case 3: return 30;  // month
    default: return 0;  // everything else → "all time"
    }
}

int main() {
    ios::sync_with_stdio(false); // disable synchronization with C library for faster IO
    cin.tie(nullptr);            // untie cin from cout to prevent automatic flush before each input

    FinanceManager fm; // create an object of our class to manage finances
    cout << "=== Personal Finance Management System ===\n"; // print header

    // Add example wallets/cards (can be removed or changed)
    fm.addWallet("Cash", WalletType::DEBIT);          // regular wallet
    fm.addWallet("VISA_Card", WalletType::DEBIT);     // debit card
    fm.addWallet("Credit_MC", WalletType::CREDIT, 1000.0); // credit card with 1000 limit

    // main program loop (menu)
    while (true) {
        // print menu
        cout << "\n--- MENU ---\n";
        cout << "1. Add wallet/card\n";
        cout << "2. Deposit to wallet/card\n";
        cout << "3. Add expense\n";
        cout << "4. Show all transactions (by period)\n";
        cout << "5. Show TOP-3 expenses (week/month)\n";
        cout << "6. Show TOP-3 categories (week/month)\n";
        cout << "7. Save report to file\n";
        cout << "8. Save TOP-3 expenses to file (week/month)\n";
        cout << "9. Save TOP-3 categories to file (week/month)\n";
        cout << "0. Exit\n";
        cout << "Choice: ";

        int choice;
        // if user entered invalid input (e.g., letters instead of a number)
        if (!(cin >> choice)) {
            cin.clear(); // clear stream state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer
            cout << "Invalid input\n";
            continue; // return to the start of the loop
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer after input

        if (choice == 0) break; // if user chooses "0" → exit program

        // ============= 1. ADD WALLET / CARD ==================
        if (choice == 1) {
            string name;
            cout << "Enter wallet/card name: ";
            getline(cin, name); // read name (getline allows spaces)
            cout << "Type (1=DEBIT, 2=CREDIT): ";
            int t; cin >> t; cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (t == 1) {
                // add debit wallet
                if (fm.addWallet(name, WalletType::DEBIT)) cout << "DEBIT wallet added\n";
                else cout << "Wallet with this name already exists\n";
            }
            else {
                // add credit wallet (ask for limit)
                double lim;
                cout << "Enter credit limit (e.g. 1000): ";
                cin >> lim;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (fm.addWallet(name, WalletType::CREDIT, lim)) cout << "CREDIT card added\n";
                else cout << "Wallet with this name already exists\n";
            }
        }

        // ============= 2. DEPOSIT TO WALLET ==================
        else if (choice == 2) {
            string name; double amt;
            cout << "Wallet/card name to deposit into: "; getline(cin, name);
            cout << "Deposit amount: "; cin >> amt; cin.ignore(numeric_limits<streamsize>::max(), '\n');
            fm.depositToWallet(name, amt); // call FinanceManager method
        }

        // ============= 3. ADD EXPENSE ==================
        else if (choice == 3) {
            string name, cat; double amt;
            cout << "Wallet/card name for expense: "; getline(cin, name);
            cout << "Expense amount: "; cin >> amt; cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Expense category (e.g. Groceries, Transport): "; getline(cin, cat);
            fm.spendFromWallet(name, amt, cat); // call FinanceManager method
        }

        // ============= 4. SHOW ALL TRANSACTIONS ==================
        else if (choice == 4) {
            int days = choosePeriodDays(); // choose period
            fm.showAllTransactions(days); // print all transactions
        }

        // ============= 5. TOP-3 EXPENSES ==================
        else if (choice == 5) {
            cout << "1) Week  2) Month  0) All time\nYour choice: ";
            int ch; cin >> ch; cin.ignore(numeric_limits<streamsize>::max(), '\n');
            int days = (ch == 1 ? 7 : (ch == 2 ? 30 : 0)); // convert choice to days
            fm.printTopExpensesConsole(days, 3); // print TOP-3 expenses
        }

        // ============= 6. TOP-3 CATEGORIES ==================
        else if (choice == 6) {
            cout << "1) Week  2) Month  0) All time\nYour choice: ";
            int ch; cin >> ch; cin.ignore(numeric_limits<streamsize>::max(), '\n');
            int days = (ch == 1 ? 7 : (ch == 2 ? 30 : 0));
            fm.printTopCategoriesConsole(days, 3); // print TOP-3 expense categories
        }

        // ============= 7. SAVE REPORT TO FILE ==================
        else if (choice == 7) {
            int days = choosePeriodDays();
            string filename;
            cout << "Filename for report (e.g. report.txt): ";
            getline(cin, filename);
            fm.saveReportToFile(filename, days); // save report to file
        }

        // ============= 8. SAVE TOP-3 EXPENSES TO FILE ==================
        else if (choice == 8) {
            cout << "1) Week  2) Month  0) All time\nYour choice: ";
            int ch; cin >> ch; cin.ignore(numeric_limits<streamsize>::max(), '\n');
            int days = (ch == 1 ? 7 : (ch == 2 ? 30 : 0));
            string filename;
            cout << "Filename for TOP expenses (e.g. top_exp.txt): ";
            getline(cin, filename);
            fm.saveTopExpensesToFile(filename, days, 3);
        }

        // ============= 9. SAVE TOP-3 CATEGORIES TO FILE ==================
        else if (choice == 9) {
            cout << "1) Week  2) Month  0) All time\nYour choice: ";
            int ch; cin >> ch; cin.ignore(numeric_limits<streamsize>::max(), '\n');
            int days = (ch == 1 ? 7 : (ch == 2 ? 30 : 0));
            string filename;
            cout << "Filename for TOP categories (e.g. top_cat.txt): ";
            getline(cin, filename);
            fm.saveTopCategoriesToFile(filename, days, 3);
        }

        // if choice is invalid
        else {
            cout << "Unknown command\n";
        }
    }

    cout << "Thank you! Goodbye.\n"; // final message before exiting
    return 0; // program termination
}
