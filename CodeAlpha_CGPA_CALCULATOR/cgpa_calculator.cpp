#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cctype>
#include <limits>

using namespace std;

struct Course {
    string name;
    string letterGrade;
    int credits;
    double gradePoint;
};

double getGradePoint(string grade) {
    for (auto &c : grade) c = toupper(c); // Convert to uppercase to handle lowercase inputs
    if (grade == "S") return 10.0;
    else if (grade == "A") return 9.0;
    else if (grade == "B") return 8.0;
    else if (grade == "C") return 7.0;
    else if (grade == "D") return 6.0;
    else if (grade == "E") return 5.0;
    else if (grade == "F") return 0.0;
    else return -1.0; // Invalid grade
}

int main() {
    int numCourses;
    vector<Course> courses;
    int currentTotalCredits = 0;
    double currentTotalGradePoints = 0.0;

    cout << "=======================================\n";
    cout << "         GPA & CGPA Calculator         \n";
    cout << "        (S-F 10-Point System)          \n";
    cout << "=======================================\n\n";

    // Input validation for number of courses
    cout << "Enter the number of courses taken this semester: ";
    while (!(cin >> numCourses) || numCourses <= 0) {
        cout << "Invalid input. Please enter a valid positive number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard bad input
    }
    // 1. Take input for each course
    for (int i = 0; i < numCourses; ++i) {
        Course c;
        cout << "\n--- Course " << (i + 1) << " ---\n";
        cout << "Course Name (e.g., CS 101): ";
        cin >> ws; 
        getline(cin, c.name); 
        // Input validation for credit hours
        cout << "Credit Hours (e.g., 3): ";
        while (!(cin >> c.credits) || c.credits < 0) {
            cout << "Invalid input. Please enter a valid number for credits: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        // Loop until a valid grade is entered
        while (true) {
            cout << "Letter Grade (S, A, B, C, D, E, F): ";
            cin >> c.letterGrade;
            c.gradePoint = getGradePoint(c.letterGrade);
            
            if (c.gradePoint != -1.0) {
                break;
            }
            cout << "Invalid grade entered. Please use S, A, B, C, D, E, or F.\n";
        }
        // 2. Calculate total credits and grade points for the semester
        currentTotalCredits += c.credits;
        currentTotalGradePoints += (c.gradePoint * c.credits);
        courses.push_back(c);
    }
    // 3. Compute the GPA for the current semester
    double semesterGPA = 0.0;
    if (currentTotalCredits > 0) {
        semesterGPA = currentTotalGradePoints / currentTotalCredits;
    }
    // 4. Compute overall CGPA
    char hasPrevious;
    double previousCGPA = 0.0;
    int previousCredits = 0;
    double overallCGPA = semesterGPA;
    cout << "\nDo you have previous semesters to include for overall CGPA? (y/n): ";
    cin >> hasPrevious;
    if (toupper(hasPrevious) == 'Y') {
        cout << "Enter your previous cumulative GPA (CGPA, out of 10): ";
        while (!(cin >> previousCGPA) || previousCGPA < 0.0 || previousCGPA > 10.0) {
            cout << "Invalid input. Enter a valid CGPA between 0 and 10: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "Enter the total credit hours earned prior to this semester: ";
        while (!(cin >> previousCredits) || previousCredits < 0) {
            cout << "Invalid input. Enter a valid positive number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        double totalOverallGradePoints = (previousCGPA * previousCredits) + currentTotalGradePoints;
        int totalOverallCredits = previousCredits + currentTotalCredits;
        if (totalOverallCredits > 0) {
            overallCGPA = totalOverallGradePoints / totalOverallCredits;
        }
    }
    // 5. Display individual course grades and final results
    cout << "\n\n=======================================\n";
    cout << "            SEMESTER SUMMARY           \n";
    cout << "=======================================\n";
    cout << left << setw(20) << "Course" << setw(10) << "Credits" << setw(10) << "Grade" << "Grade Points" << endl;
    cout << "---------------------------------------\n";
    for (const auto& c : courses) {
        cout << left << setw(20) << c.name 
             << setw(10) << c.credits 
             << setw(10) << c.letterGrade 
             << fixed << setprecision(2) << (c.gradePoint * c.credits) << endl;
    }
    cout << "---------------------------------------\n";
    cout << left << setw(20) << "TOTAL" 
         << setw(10) << currentTotalCredits 
         << setw(10) << "" 
         << fixed << setprecision(2) << currentTotalGradePoints << endl;
    cout << "\n=======================================\n";
    cout << "Current Semester GPA : " << fixed << setprecision(2) << semesterGPA << " / 10.00" << endl;
    cout << "Overall CGPA         : " << fixed << setprecision(2) << overallCGPA << " / 10.00" << endl;
    cout << "=======================================\n";
    return 0;
}