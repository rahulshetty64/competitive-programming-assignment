#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

// ==============================
// Transaction Class
// ==============================
class Transaction {
public:
    int id;
    string category;
    double amount;

    Transaction(int i, string c, double a) {
        id = i;
        category = c;
        amount = a;
    }

    void saveToFile() {
        ofstream file("transactions.txt", ios::app);
        file << id << " " << category << " " << amount << endl;
        file.close();
    }
};

// ==============================
// FraudDetector Class
// ==============================
class FraudDetector {
private:
    vector<Transaction> transactions;

public:
    void loadTransactions() {
        transactions.clear();
        ifstream file("transactions.txt");
        int id;
        string category;
        double amount;

        while (file >> id >> category >> amount) {
            transactions.push_back(Transaction(id, category, amount));
        }
        file.close();
    }

    void displayTransactions() {
        if (transactions.empty()) {
            cout << "\nNo transactions found.\n";
            return;
        }

        cout << "\n------------------ TRANSACTION HISTORY ------------------\n";
        cout << left << setw(10) << "ID"
             << setw(15) << "Category"
             << setw(10) << "Amount\n";
        cout << "---------------------------------------------------------\n";

        for (auto &t : transactions) {
            cout << left << setw(10) << t.id
                 << setw(15) << t.category
                 << "₹" << t.amount << endl;
        }
    }

    double calculateAverage() {
        if (transactions.empty()) return 0;

        double sum = 0;
        for (auto &t : transactions)
            sum += t.amount;

        return sum / transactions.size();
    }

    void detectFraud() {
        if (transactions.size() < 3) {
            cout << "\nNot enough data to analyze fraud.\n";
            return;
        }

        double avg = calculateAverage();
        double threshold = avg * 2.5;

        cout << "\n--------- FRAUD ANALYSIS REPORT ---------\n";
        cout << "Average Spending: ₹" << avg << endl;
        cout << "Fraud Threshold : ₹" << threshold << "\n\n";

        bool fraudFound = false;

        for (auto &t : transactions) {
            if (t.amount > threshold) {
                cout << "⚠️  Suspicious Transaction Detected!\n";
                cout << "   ID       : " << t.id << endl;
                cout << "   Category : " << t.category << endl;
                cout << "   Amount   : ₹" << t.amount << "\n\n";
                fraudFound = true;
            }
        }

        if (!fraudFound)
            cout << "No suspicious transactions detected.\n";
    }
};

// ==============================
// Main Menu
// ==============================
int main() {
    FraudDetector detector;
    int choice;

    cout << "\n===========================================\n";
    cout << "   PERSONAL FINANCE FRAUD DETECTOR SYSTEM\n";
    cout << "===========================================\n";

    do {
        cout << "\nWhat would you like to do?\n";
        cout << "1. Add a new transaction\n";
        cout << "2. View transaction history\n";
        cout << "3. Run fraud detection\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int id;
            string category;
            double amount;

            cout << "\nEnter Transaction ID: ";
            cin >> id;
            cout << "Enter Category (Food/Travel/Shopping/etc): ";
            cin >> category;
            cout << "Enter Amount: ₹";
            cin >> amount;

            Transaction t(id, category, amount);
            t.saveToFile();

            cout << "\nTransaction saved successfully.\n";
        }
        else if (choice == 2) {
            detector.loadTransactions();
            detector.displayTransactions();
        }
        else if (choice == 3) {
            detector.loadTransactions();
            detector.detectFraud();
        }
        else if (choice == 4) {
            cout << "\nExiting system. Stay financially safe!\n";
        }
        else {
            cout << "\nInvalid choice. Try again.\n";
        }

    } while (choice != 4);

    return 0;
}
