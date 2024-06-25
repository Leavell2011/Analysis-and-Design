#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

class Course {
public:
    string courseNumber;
    string courseName;
    vector<string> prerequisites;

    Course() {}

    Course(string courseNumber, string courseName, vector<string> prerequisites) {
        this->courseNumber = courseNumber;
        this->courseName = courseName;
        this->prerequisites = prerequisites;
    }
};
unordered_map<string, Course> loadCourses(string filename) {
    unordered_map<string, Course> courses;
    ifstream file(filename);
    string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            stringstream ss(line);
            string courseNumber, courseName, prerequisite;
            vector<string> prerequisites;

            getline(ss, courseNumber, ',');
            getline(ss, courseName, ',');

            while (getline(ss, prerequisite, ',')) {
                prerequisites.push_back(prerequisite);
            }

            Course course(courseNumber, courseName, prerequisites);
            courses[courseNumber] = course;
        }
        file.close();
    }
    else {
        cout << "Unable to open file." << endl;
    }

    return courses;
}
void displayMenu() {
    cout << "1. Load Data Structure." << endl;
    cout << "2. Print Course List." << endl;
    cout << "3. Print Course." << endl;
    cout << "9. Exit" << endl;
}

void printCourseList(const unordered_map<string, Course>& courses) {
    vector<string> courseNumbers;

    for (const auto& pair : courses) {
        courseNumbers.push_back(pair.first);
    }

    sort(courseNumbers.begin(), courseNumbers.end());

    for (const auto& courseNumber : courseNumbers) {
        cout << courseNumber << ", " << courses.at(courseNumber).courseName << endl;
    }
}

void printCourseInfo(const unordered_map<string, Course>& courses, const string& courseNumber) {
    if (courses.find(courseNumber) != courses.end()) {
        const Course& course = courses.at(courseNumber);
        cout << course.courseNumber << ", " << course.courseName << endl;

        if (!course.prerequisites.empty()) {
            cout << "Prerequisites: ";
            for (const auto& prereq : course.prerequisites) {
                cout << prereq << ", ";
            }
            cout << endl;
        }
        else {
            cout << "No prerequisites." << endl;
        }
    }
    else {
        cout << "Course not found." << endl;
    }
}
int main() {
    unordered_map<string, Course> courses;
    int choice;
    string filename;
    string courseNumber;

    cout << "Welcome to the course planner." << endl;

    while (true) {
        displayMenu();
        cout << "What would you like to do? ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter the file name to load: ";
            cin >> filename;
            courses = loadCourses(filename);
            cout << "Data loaded successfully." << endl;
            break;
        case 2:
            printCourseList(courses);
            break;
        case 3:
            cout << "What course do you want to know about? ";
            cin >> courseNumber;
            transform(courseNumber.begin(), courseNumber.end(), courseNumber.begin(), ::toupper);
            printCourseInfo(courses, courseNumber);
            break;
        case 9:
            cout << "Thank you for using the course planner!" << endl;
            return 0;
        default:
            cout << choice << " is not a valid option." << endl;
        }
    }

    return 0;
}


