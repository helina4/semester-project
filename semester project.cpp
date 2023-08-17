#include <iostream>
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class Student {
    char name[50];
    int rollNo;
    char branch[20];
    int semester;
    float cgpa;

public:
    void getDetails() {
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Roll Number: ";
        cin >> rollNo;
        cout << "Enter Branch: ";
        cin >> branch;
        cout << "Enter Semester: ";
        cin >> semester;
        cout << "Enter CGPA: ";
        cin >> cgpa;
    }

    void displayDetails() {
        cout << "Name: " << name << endl;
        cout << "Roll Number: " << rollNo << endl;
        cout << "Branch: " << branch << endl;
        cout << "Semester: " << semester << endl;
        cout << "CGPA: " << cgpa << endl;
    }

    int getRollNo() {
        return rollNo;
    }
};

void addStudent() {
    ofstream outFile("students.dat", ios::binary | ios::app);
    Student s;
    s.getDetails();
    outFile.write((char*)&s, sizeof(s));
    outFile.close();
}

void displayAllStudents() {
    ifstream inFile("students.dat", ios::binary);
    Student s;
    while (inFile.read((char*)&s, sizeof(s))) {
        s.displayDetails();
        cout << endl;
    }
    inFile.close();
}

void searchStudent() {
    int rollNo;
    cout << "Enter Roll Number to Search: ";
    cin >> rollNo;

    ifstream inFile("students.dat", ios::binary);
    Student s;
    bool found = false;
    while (inFile.read((char*)&s, sizeof(s))) {
        if (s.getRollNo() == rollNo) {
            s.displayDetails();
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Student Not Found!" << endl;
    }
    inFile.close();
}

void deleteStudent() {
    int rollNo;
    cout << "Enter Roll Number to Delete: ";
    cin >> rollNo;

    ifstream inFile("students.dat", ios::binary);
    ofstream outFile("temp.dat", ios::binary);
    Student s;
    bool found = false;
    while (inFile.read((char*)&s, sizeof(s))) {
        if (s.getRollNo() != rollNo) {
            outFile.write((char*)&s, sizeof(s));
        }
        else {
            found = true;
        }
    }
    if (!found) {
        cout << "Student Not Found!" << endl;
    }
    else {
        cout << "Student Deleted Successfully!" << endl;
    }
    inFile.close();
    outFile.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");
}

void menu() {
    int choice;
    do {
        cout << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Display All Students" << endl;
        cout << "3. Search Student" << endl;
        cout << "4. Delete Student" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayAllStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
                break;
            default:
                cout << "Invalid Choice!" << endl;
                break;
        }
    } while (choice != 5);
}

int main() {
    menu();
    return 0;
}
