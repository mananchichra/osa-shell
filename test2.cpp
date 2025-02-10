#include <iostream>
#include <vector>
using namespace std;

class Customer {
private:
    string name;
    string email;
    vector<string> orderHistory;
    double totalSpent;

public:
    Customer(string n, string e) : name(n), email(e), totalSpent(0) {}

    void placeOrder(string order, double price) {
        orderHistory.push_back(order);
        totalSpent += price;
    }

    void printOrderHistory() {
        cout << "Order History for " << name << ":\n";
        for (const string &order : orderHistory) {
            cout << "- " << order << endl;
        }

        if (totalSpent > 500) {
            cout << "Eligible for 10% discount.\n";
        } else if (totalSpent > 1000) {
            cout << "Eligible for 20% discount.\n";
        }
    }

    double calculateDiscount() {
        if (totalSpent > 1000) return totalSpent * 0.2;
        if (totalSpent > 500) return totalSpent * 0.1;
        return 0;
    }
};
