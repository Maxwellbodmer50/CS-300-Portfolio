/*
 * main.cpp
 *
 *  Created on: Apr 19, 2026
 *      Author: Maxwell Bodmer
 */




#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#include <string>
#include <cctype>

using namespace std;

struct Course {
    string id;
    string title;
    vector<string> prereqs;
};

map<string, Course> courses;

string toUpper(string str) {
    for (size_t i = 0; i < str.length(); i++) {
        str[i] = toupper(str[i]);
    }
    return str;
}

void loadCourses() {
    string filename;
    cout << "What is the name of the file? ";
    cin >> filename;

    ifstream file(filename.c_str());

    if (!file.is_open()) {
        cout << "Error: Could not open file." << endl;
        return;
    }

    courses.clear();

    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        Course course;

        getline(ss, course.id, ',');
        getline(ss, course.title, ',');

        course.id = toUpper(course.id);

        while (getline(ss, token, ',')) {
            token = toUpper(token);
            course.prereqs.push_back(token);
        }

        courses[course.id] = course;
    }

    file.close();
    cout << "Data loaded successfully." << endl;
}

void printCourseList() {
    cout << "Here is a sample schedule:" << endl;

    map<string, Course>::iterator it;

    for (it = courses.begin(); it != courses.end(); ++it) {
        cout << it->second.id << ", " << it->second.title << endl;
    }
}

void printCourse() {
    string courseId;

    cout << "What course do you want to know about? ";
    cin >> courseId;

    courseId = toUpper(courseId);

    if (courses.find(courseId) == courses.end()) {
        cout << "Course not found." << endl;
        return;
    }

    Course c = courses[courseId];

    cout << c.id << ", " << c.title << endl;
    cout << "Prerequisites: ";

    if (c.prereqs.empty()) {
        cout << "None";
    } else {
        for (size_t i = 0; i < c.prereqs.size(); i++) {
            cout << c.prereqs[i];

            if (i + 1 < c.prereqs.size()) {
                cout << ", ";
            }
        }
    }

    cout << endl;
}

int main() {
    int choice = 0;

    cout << "Welcome to the course planner." << endl;

    while (choice != 9) {
        cout << endl;
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << "What would you like to do? ";

        cin >> choice;

        switch (choice) {
            case 1:
                loadCourses();
                break;

            case 2:
                printCourseList();
                break;

            case 3:
                printCourse();
                break;

            case 9:
                cout << "Thank you for using the course planner!" << endl;
                break;

            default:
                cout << choice << " is not a valid option." << endl;
                break;
        }
    }

    return 0;
}
