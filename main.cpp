
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <stdexcept>

using namespace std;

class Transaction {
private:
    string type;
    double amount;
    string category;
    string description;
    string date;

public:
    Transaction(string t, double a, string c,
                string d, string dt)
        : type(t), amount(a), category(c),
          description(d), date(dt) {}

    string getType() const { return type; }
    double getAmount() const { return amount; }
    string getCategory() const { return category; }
    string getDescription() const { return description; }
    string getDate() const { return date; }

    void display() const {
        cout << left << setw(12) << type
             << setw(12) << fixed << setprecision(2)
             << amount
             << setw(16) << category
             << setw(16) << date
             << description << '\n';
    }
};

class ExpenseTracker {
private:
    vector<Transaction> transactions;
    double budget;
    const string transactionFile = "transactions.txt";
    const string budgetFile = "budget.txt";

    string cleanField(string value) {
        for (char &ch : value) {
            if (ch == '|')
                ch = '/';
        }
        return value;
    }

    void loadTransactions() {
        ifstream file(transactionFile);
        string line;

        while (getline(file, line)) {
            stringstream ss(line);
            string type, amountText, category;
            string description, date;

            if (getline(ss, type, '|') &&
                getline(ss, amountText, '|') &&
                getline(ss, category, '|') &&
                getline(ss, description, '|') &&
                getline(ss, date)) {
                try {
                    double amount = stod(amountText);

                    if (amount > 0) {
                        transactions.emplace_back(
                            type, amount, category,
                            description, date);
                    }
                } catch (const exception &) {
                    // Ignore invalid stored records.
                }
            }
        }
    }

    void saveTransactions() const {
        ofstream file(transactionFile);

        if (!file) {
            cout << "Error saving transactions!\n";
            return;
        }

        for (const auto &t : transactions) {
            file << t.getType() << '|'
                 << t.getAmount() << '|'
                 << t.getCategory() << '|'
                 << t.getDescription() << '|'
                 << t.getDate() << '\n';
        }
    }

    void loadBudget() {
        ifstream file(budgetFile);

        if (!(file >> budget) || budget < 0)
            budget = 0;
    }

    void saveBudget() const {
        ofstream file(budgetFile);

        if (file)
            file << budget;
        else
            cout << "Error saving budget!\n";
    }

    double readPositiveAmount() {
        double amount;

        while (true) {
            cout << "Enter amount (greater than 0): ";

            if (cin >> amount && amount > 0) {
                cin.ignore(numeric_limits<streamsize>::max(),
                           '\n');
                return amount;
            }

            cout << "Invalid amount. Try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),
                       '\n');
        }
    }

public:
    ExpenseTracker() : budget(0) {
        loadTransactions();
        loadBudget();
    }

    void addTransaction(const string &type) {
        double amount = readPositiveAmount();
        string category, description, date;

        cout << "Enter category (Food/Travel/Shopping/"
                "Education/Other): ";
        getline(cin, category);

        cout << "Enter description: ";
        getline(cin, description);

        cout << "Enter date (DD-MM-YYYY): ";
        getline(cin, date);

        if (category.empty() || description.empty()
            || date.empty()) {
            cout << "Fields cannot be empty. "
                    "Transaction cancelled.\n";
            return;
        }

        transactions.emplace_back(
            type, amount, cleanField(category),
            cleanField(description), cleanField(date));

        saveTransactions();

        cout << type << " recorded successfully!\n";

        if (budget > 0 && getTotalExpenses() > budget) {
            cout << "Warning: Your spending budget "
                    "has been exceeded!\n";
        }
    }

    void showTransactions() const {
        if (transactions.empty()) {
            cout << "No transactions recorded yet.\n";
            return;
        }

        cout << "\n--- TRANSACTION HISTORY ---\n";
        cout << left << setw(12) << "Type"
             << setw(12) << "Amount"
             << setw(16) << "Category"
             << setw(16) << "Date"
             << "Description\n";

        for (const auto &t : transactions)
            t.display();
    }

    double getTotalIncome() const {
        double total = 0;

        for (const auto &t : transactions) {
            if (t.getType() == "Income")
                total += t.getAmount();
        }

        return total;
    }

    double getTotalExpenses() const {
        double total = 0;

        for (const auto &t : transactions) {
            if (t.getType() == "Expense")
                total += t.getAmount();
        }

        return total;
    }

    void showSummary() const {
        double income = getTotalIncome();
        double expenses = getTotalExpenses();

        cout << fixed << setprecision(2);
        cout << "\n--- FINANCIAL SUMMARY ---\n";
        cout << "Total Income:   Rs. " << income << '\n';
        cout << "Total Expenses: Rs. " << expenses << '\n';
        cout << "Balance:        Rs. "
             << income - expenses << '\n';

        if (budget > 0) {
            cout << "Spending Budget: Rs. " << budget << '\n';
            cout << "Budget Remaining: Rs. "
                 << budget - expenses << '\n';

            if (expenses > budget)
                cout << "Status: Budget exceeded!\n";
            else
                cout << "Status: Within budget.\n";
        }
    }

    void searchCategory() const {
        string category;
        bool found = false;

        cout << "Enter category to search: ";
        getline(cin, category);

        for (const auto &t : transactions) {
            if (t.getCategory() == category) {
                if (!found) {
                    cout << "\nMatching transactions:\n";
                    found = true;
                }

                t.display();
            }
        }

        if (!found)
            cout << "No transactions found in this category.\n";
    }

    void setBudget() {
        cout << "Set spending budget.\n";
        budget = readPositiveAmount();
        saveBudget();

        cout << "Budget saved successfully!\n";

        if (getTotalExpenses() > budget)
            cout << "Warning: Existing expenses exceed "
                    "your new budget!\n";
    }
};

int main() {
    ExpenseTracker tracker;
    int choice;

    do {
        cout << "\n================================\n";
        cout << "      SMART EXPENSE TRACKER\n";
        cout << "================================\n";
        cout << "1. Add Income\n";
        cout << "2. Add Expense\n";
        cout << "3. View All Transactions\n";
        cout << "4. View Financial Summary\n";
        cout << "5. Search by Category\n";
        cout << "6. Set Spending Budget\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),
                       '\n');
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                tracker.addTransaction("Income");
                break;

            case 2:
                tracker.addTransaction("Expense");
                break;

            case 3:
                tracker.showTransactions();
                break;

            case 4:
                tracker.showSummary();
                break;

            case 5:
                tracker.searchCategory();
                break;

            case 6:
                tracker.setBudget();
                break;

            case 7:
                cout << "Thank you for using "
                        "Smart Expense Tracker!\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 7);

    return 0;
}
