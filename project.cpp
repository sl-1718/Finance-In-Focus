#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include <cctype>
using namespace std;

// Constants
const int MAX_USERS = 10;
const int MAX_COURSES = 10;
const int MAX_SEMESTERS = 8;
const int MAX_STUDENTS = 20;

// Global variables
string usersList[MAX_USERS];
string passwordsList[MAX_USERS];
string courseCodes[MAX_SEMESTERS][MAX_COURSES];
string courseNames[MAX_SEMESTERS][MAX_COURSES];
int creditHours[MAX_SEMESTERS][MAX_COURSES];
string studentNames[MAX_STUDENTS];
string studentRegNos[MAX_STUDENTS];
string studentCourses[MAX_STUDENTS][MAX_COURSES];

int courseIdx = 0;
int userIdx = 0;
int studentIdx = 0;
int currentCourseSemesterIdx;
int currentCourseIdx;

const char* COURSE_FILE = "Courses.txt";
const char* USER_FILE = "Users.txt";
const char* STUDENT_FILE = "Student.txt";

ofstream courseFileOut, userFileOut, studentFileOut;
ifstream courseFileIn, userFileIn, studentFileIn;

// Function declarations
void startError();
bool isValidCourseCode(string courseCode);
bool isValidCourseName(string courseName);
bool isValidCreditHours(int creditHours);
bool isValidSemester(int semester);
void addCourse(string code, string name, int credit, int semester);
bool findCourseCode(string code);
void updateCourse(string code, string name, int credit, int semester);
void deleteCourse(string code);
void viewAllCourses();
void viewSemesterCourses(int semester);
bool saveCourses();
bool ifFileExists(const char* fileName);
bool loadCourses();
bool loadUsers();
bool validateUsers(string name, string password);
void loginScreen();
void addStudent(string name, string regNo);
bool findStudent(string regNo);
void updateStudent(string name, string regNo);
void deleteStudent(string regNo);
void registerCourse(string regNo, string courseCode);
void unregisterCourse(string regNo, string courseCode);
bool isValidRegistrationNumber(string regNo);
bool isValidStudentName(string name);
bool saveStudents();
bool loadStudents();
void displayMenu();

void startError() {
    if (cin.fail()) {
        system("CLS");
        cout << "ERROR -- You did not enter an integer" << endl;
        cin.clear();
        cin.ignore();
    }
}

bool isValidCourseCode(string courseCode) {
    return courseCode.length() == 5 &&
           isalpha(courseCode[0]) && isalpha(courseCode[1]) &&
           isdigit(courseCode[2]) && isdigit(courseCode[3]) && isdigit(courseCode[4]);
}

bool isValidCourseName(string courseName) {
    if (courseName.length() > 50) return false;
    for (char c : courseName) {
        if (!isspace(c) && !isalpha(c)) return false;
    }
    return true;
}

bool isValidCreditHours(int creditHours) {
    return creditHours > 0 && creditHours <= 3;
}

bool isValidSemester(int semester) {
    return semester > 0 && semester <= MAX_SEMESTERS;
}

void addCourse(string code, string name, int credit, int semester) {
    int idx = courseIdx++;
    courseCodes[semester - 1][idx] = code;
    courseNames[semester - 1][idx] = name;
    creditHours[semester - 1][idx] = credit;
    cout << "Course Added Successfully" << endl;
}

bool findCourseCode(string code) {
    for (int i = 0; i < MAX_SEMESTERS; ++i) {
        for (int j = 0; j < MAX_COURSES; ++j) {
            if (code == courseCodes[i][j]) {
                currentCourseSemesterIdx = i;
                currentCourseIdx = j;
                return true;
            }
        }
    }
    return false;
}

void updateCourse(string code, string name, int credit, int semester) {
    int semIdx = currentCourseSemesterIdx;
    int idx = currentCourseIdx;
    courseCodes[semIdx][idx] = "";
    courseNames[semIdx][idx] = "";
    creditHours[semIdx][idx] = 0;
    addCourse(code, name, credit, semester);
    cout << "Course has been edited successfully" << endl;
}

void deleteCourse(string code) {
    if (findCourseCode(code)) {
        int semIdx = currentCourseSemesterIdx;
        int idx = currentCourseIdx;
        courseCodes[semIdx][idx] = "";
        courseNames[semIdx][idx] = "";
        creditHours[semIdx][idx] = 0;
        cout << "Course deleted successfully" << endl;
    }
}

void viewAllCourses() {
    cout << setw(15) << "Course Code" << setw(35) << "Name" << setw(50) << "Credit Hours" << setw(15) << "Semester" << endl;
    for (int i = 0; i < MAX_SEMESTERS; ++i) {
        for (int j = 0; j < MAX_COURSES; ++j) {
            if (courseCodes[i][j] != "") {
                cout << setw(9) << courseCodes[i][j] << setw(45) << courseNames[i][j] << setw(38) << creditHours[i][j] << setw(18) << i + 1 << endl;
            }
        }
    }
}

void viewSemesterCourses(int semester) {
    cout << setw(15) << "Course Code" << setw(35) << "Name" << setw(50) << "Credit Hours" << endl;
    for (int i = 0; i < MAX_COURSES; ++i) {
        if (courseCodes[semester - 1][i] != "") {
            cout << setw(15) << courseCodes[semester - 1][i] << setw(35) << courseNames[semester - 1][i] << setw(50) << creditHours[semester - 1][i] << endl;
        }
    }
}

bool saveCourses() {
    courseFileOut.open(COURSE_FILE);
    for (int i = 0; i < MAX_SEMESTERS; ++i) {
        for (int j = 0; j < MAX_COURSES; ++j) {
            if (courseCodes[i][j] != "") {
                courseFileOut << courseCodes[i][j] << "," << courseNames[i][j] << "," << creditHours[i][j] << "," << i + 1 << endl;
            }
        }
    }
    courseFileOut.close();
    return true;
}

bool ifFileExists(const char* fileName) {
    ifstream ifile(fileName);
    return (bool)ifile;
}

bool loadCourses() {
    if (!ifFileExists(COURSE_FILE)) {
        cout << "File does not exist. No need to load course info" << endl;
        return false;
    }

    courseFileIn.open(COURSE_FILE);
    string line, crscd, crsnm, crdh, smstr;
    int intchr, intsmst;
    while (getline(courseFileIn, line)) {
        stringstream crdss, smstss;
        stringstream input_stringstream(line);
        getline(input_stringstream, crscd, ',');
        getline(input_stringstream, crsnm, ',');
        getline(input_stringstream, crdh, ',');
        crdss << crdh;
        crdss >> intchr;
        getline(input_stringstream, smstr, ',');
        smstss << smstr;
        smstss >> intsmst;
        courseCodes[intsmst - 1][courseIdx] = crscd;
        courseNames[intsmst - 1][courseIdx] = crsnm;
        creditHours[intsmst - 1][courseIdx] = intchr;
        courseIdx++;
    }
    courseFileIn.close();
    cout << "Courses Loaded Successfully" << endl;
    return true;
}

bool loadUsers() {
    if (!ifFileExists(USER_FILE)) {
        cout << "Sorry, we are unable to run the program, as user data does not exist." << endl;
        return false;
    }

    userFileIn.open(USER_FILE);
    string line, parsed;
    while (getline(userFileIn, line)) {
        stringstream input_stringstream(line);
        getline(input_stringstream, parsed, ',');
        usersList[userIdx] = parsed;
        getline(input_stringstream, parsed, ',');
        passwordsList[userIdx] = parsed;
        userIdx++;
    }
    userFileIn.close();
    cout << "Users Loaded Successfully" << endl;
    return true;
}

bool validateUsers(string name, string password) {
    for (int i = 0; i < MAX_USERS; ++i) {
        if (usersList[i] == name && passwordsList[i] == password) {
            return true;
        }
    }
    return false;
}

void loginScreen() {
    bool result = false;
    cout << "** WELCOME to University Learning Management System **" << endl;
    cout << "Dear User, current software is intended for authorized users only." << endl;
    cout << "Login to the system to get access." << endl;

    while (!result) {
        string username, password;
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;

        result = validateUsers(username, password);
        if (result) {
            system("CLS");
            cout << "Welcome, you have successfully logged into the system" << endl;
        } else {
            system("CLS");
            cout << "Either username or password is incorrect. Please try again." << endl;
        }
    }
}

void addStudent(string name, string regNo) {
    int idx = studentIdx++;
    studentNames[idx] = name;
    studentRegNos[idx] = regNo;
    cout << "Student Added Successfully" << endl;
}

bool findStudent(string regNo) {
    for (int i = 0; i < MAX_STUDENTS; ++i) {
        if (regNo == studentRegNos[i]) {
            currentStudentIdx = i;
            return true;
        }
    }
    return false;
}

void updateStudent(string name, string regNo) {
    int idx = currentStudentIdx;
    studentNames[idx] = name;
    studentRegNos[idx] = regNo;
    cout << "Student has been edited successfully" << endl;
}

void deleteStudent(string regNo) {
    if (findStudent(regNo)) {
        int idx = currentStudentIdx;
        studentNames[idx] = "";
        studentRegNos[idx] = "";
        cout << "Student deleted successfully" << endl;
    }
}

void registerCourse(string regNo, string courseCode) {
    if (findStudent(regNo)) {
        int studentIdx = currentStudentIdx;
        for (int i = 0; i < MAX_COURSES; ++i) {
            if (studentCourses[studentIdx][i] == "") {
                studentCourses[studentIdx][i] = courseCode;
                cout << "Course registered successfully" << endl;
                return;
            }
        }
    } else {
        cout << "Student not found" << endl;
    }
}

void unregisterCourse(string regNo, string courseCode) {
    if (findStudent(regNo)) {
        int studentIdx = currentStudentIdx;
        for (int i = 0; i < MAX_COURSES; ++i) {
            if (studentCourses[studentIdx][i] == courseCode) {
                studentCourses[studentIdx][i] = "";
                cout << "Course unregistered successfully" << endl;
                return;
            }
        }
    } else {
        cout << "Student not found" << endl;
    }
}

bool isValidRegistrationNumber(string regNo) {
    // Add your validation logic here
    return true;
}

bool isValidStudentName(string name) {
    // Add your validation logic here
    return true;
}

bool saveStudents() {
    studentFileOut.open(STUDENT_FILE);
    for (int i = 0; i < MAX_STUDENTS; ++i) {
        if (studentRegNos[i] != "") {
            studentFileOut << studentRegNos[i] << "," << studentNames[i] << endl;
        }
    }
    studentFileOut.close();
    return true;
}

bool loadStudents() {
    if (!ifFileExists(STUDENT_FILE)) {
        cout << "File does not exist. No need to load student info" << endl;
        return false;
    }

    studentFileIn.open(STUDENT_FILE);
    string line, name, regNo;
    while (getline(studentFileIn, line)) {
        stringstream input_stringstream(line);
        getline(input_stringstream, name, ',');
        getline(input_stringstream, regNo, ',');
        addStudent(name, regNo);
    }
    studentFileIn.close();
    cout << "Students Loaded Successfully" << endl;
    return true;
}

void displayMenu() {
    int choice;
    do {
        cout << "1. Add Course" << endl;
        cout << "2. Update Course" << endl;
        cout << "3. Delete Course" << endl;
        cout << "4. View All Courses" << endl;
        cout << "5. View Courses of a Semester" << endl;
        cout << "6. Add Student" << endl;
        cout << "7. Update Student" << endl;
        cout << "8. Delete Student" << endl;
        cout << "9. Register Course for Student" << endl;
        cout << "10. Unregister Course for Student" << endl;
        cout << "11. Save & Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        startError();
        system("CLS");

        string code, name, regNo;
        int credit, semester;

        switch (choice) {
            case 1:
                cout << "Enter course code: ";
                cin >> code;
                if (!isValidCourseCode(code)) {
                    cout << "Invalid course code." << endl;
                    break;
                }
                cout << "Enter course name: ";
                cin.ignore();
                getline(cin, name);
                if (!isValidCourseName(name)) {
                    cout << "Invalid course name." << endl;
                    break;
                }
                cout << "Enter credit hours: ";
                cin >> credit;
                if (!isValidCreditHours(credit)) {
                    cout << "Invalid credit hours." << endl;
                    break;
                }
                cout << "Enter semester: ";
                cin >> semester;
                if (!isValidSemester(semester)) {
                    cout << "Invalid semester." << endl;
                    break;
                }
                addCourse(code, name, credit, semester);
                break;
            case 2:
                cout << "Enter course code to update: ";
                cin >> code;
                if (findCourseCode(code)) {
                    cout << "Enter new course code: ";
                    cin >> code;
                    if (!isValidCourseCode(code)) {
                        cout << "Invalid course code." << endl;
                        break;
                    }
                    cout << "Enter new course name: ";
                    cin.ignore();
                    getline(cin, name);
                    if (!isValidCourseName(name)) {
                        cout << "Invalid course name." << endl;
                        break;
                    }
                    cout << "Enter new credit hours: ";
                    cin >> credit;
                    if (!isValidCreditHours(credit)) {
                        cout << "Invalid credit hours." << endl;
                        break;
                    }
                    cout << "Enter new semester: ";
                    cin >> semester;
                    if (!isValidSemester(semester)) {
                        cout << "Invalid semester." << endl;
                        break;
                    }
                    updateCourse(code, name, credit, semester);
                } else {
                    cout << "Course not found." << endl;
                }
                break;
            case 3:
                cout << "Enter course code to delete: ";
                cin >> code;
                deleteCourse(code);
                break;
            case 4:
                viewAllCourses();
                break;
            case 5:
                cout << "Enter semester: ";
                cin >> semester;
                viewSemesterCourses(semester);
                break;
            case 6:
                cout << "Enter student name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter registration number: ";
                cin >> regNo;
                addStudent(name, regNo);
                break;
            case 7:
                cout << "Enter registration number to update: ";
                cin >> regNo;
                if (findStudent(regNo)) {
                    cout << "Enter new name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter new registration number: ";
                    cin >> regNo;
                    updateStudent(name, regNo);
                } else {
                    cout << "Student not found." << endl;
                }
                break;
            case 8:
                cout << "Enter registration number to delete: ";
                cin >> regNo;
                deleteStudent(regNo);
                break;
            case 9:
                cout << "Enter student registration number: ";
                cin >> regNo;
                cout << "Enter course code to register: ";
                cin >> code;
                registerCourse(regNo, code);
                break;
            case 10:
                cout << "Enter student registration number: ";
                cin >> regNo;
                cout << "Enter course code to unregister: ";
                cin >> code;
                unregisterCourse(regNo, code);
                break;
            case 11:
                saveCourses();
                saveStudents();
                cout << "Data saved. Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 11);
}

int main() {
    loadCourses();
    loadUsers();
    loginScreen();
    displayMenu();
    return 0;
}
