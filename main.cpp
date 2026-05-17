#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

struct Transaction {
    string type;
    double amount;
    string category;
};

class FinanceTracker {
private:
    double balance;
    vector<Transaction> history;
    const string fileName = "data.txt";

    void loadFromFile() {
        ifstream file(fileName);
        if (file.is_open()) {
            file >> balance;
            Transaction temp;
            while (file >> temp.type >> temp.amount >> temp.category) {
                history.push_back(temp);
            }
            file.close();
        }
    }

    void saveToFile() {
        ofstream file(fileName);
        if (file.is_open()) {
            file << balance << endl;
            for (const auto& t : history) {
                file << t.type << " " << t.amount << " " << t.category << endl;
            }
            file.close();
        }
    }

public:
    FinanceTracker() : balance(0.0) {
        loadFromFile(); 
    }

    void addIncome(double amt, string cat) {
        balance += amt;
        history.push_back({"Income", amt, cat});
        saveToFile();
        cout << "\n[+] Success: Income added!" << endl;
    }

    void addExpense(double amt, string cat) {
        if (amt > balance) {
            cout << "\n[!] Error: Insufficient balance! (Current: $" << balance << ")" << endl;
        } else {
            balance -= amt;
            history.push_back({"Expense", amt, cat});
            saveToFile();
            cout << "\n[-] Success: Expense recorded!" << endl;
        }
    }

    void showReport() {
        cout << "\n================================";
        cout << "\n      FINANCIAL REPORT          ";
        cout << "\n================================";
        cout << "\nCURRENT BALANCE : $" << fixed << setprecision(2) << balance;
        cout << "\n--------------------------------";
        cout << "\nType\tAmount\tCategory";
        cout << "\n----\t------\t--------";
        for (const auto& t : history) {
            cout << "\n" << t.type << "\t$" << t.amount << "\t" << t.category;
        }
        cout << "\n================================\n";
    }
};

int main() {
    FinanceTracker myWallet;
    int choice;
    double amount;
    string category;

    while (true) {
        cout << "\n--- MONEY TRACKER PRO ---";
        cout << "\n1. Add Income";
        cout << "\n2. Add Expense";
        cout << "\n3. View Report";
        cout << "\n0. Exit & Save";
        cout << "\nEnter Choice: ";
        cin >> choice;

        if (choice == 0) break;

        switch (choice) {
            case 1:
                cout << "Enter Income Amount: "; cin >> amount;
                cout << "Enter Category: "; cin >> category;
                myWallet.addIncome(amount, category);
                break;
            case 2:
                cout << "Enter Expense Amount: "; cin >> amount;
                cout << "Enter Category: "; cin >> category;
                myWallet.addExpense(amount, category);
                break;
            case 3:
                myWallet.showReport();
                break;
            default:
                cout << "Invalid choice!\n";
        }
    }

    cout << "Data saved successfully!\n";
    return 0;
}