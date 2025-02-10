#include <iostream>
#include <vector>
using namespace std;

class Student {
private:
    string name;
    int age;
    vector<int> grades;

public:
    Student(string n, int a) : name(n), age(a) {}

    void addGrade(int grade) {
        grades.push_back(grade);
    }

    void printGrades() {
        cout << "Grades of " << name << ": ";
        for (int g : grades) {
            cout << g << " ";
        }
        cout << endl;
    }

    // **God Object**: Manages grades and performance calculation
    double calculateAverage() {
        if (grades.empty()) return 0.0;
        int sum = 0;
        for (int g : grades) {
            sum += g;
        }
        return (double)sum / grades.size();
    }

    string getPerformance() {
        double avg = calculateAverage();
        if (avg > 90) return "Excellent";
        else if (avg > 75) return "Good";
        else return "Needs Improvement";
    }

    // **Shotgun Surgery**: If grading logic changes, multiple methods need updating
    bool isEligibleForScholarship() {
        return calculateAverage() > 85;
    }

    // **Feature Envy**: This logic should be in a separate Scholarship class
    void printScholarshipStatus() {
        cout << name << " is " << (isEligibleForScholarship() ? "eligible" : "not eligible") << " for a scholarship.\n";
    }
};
