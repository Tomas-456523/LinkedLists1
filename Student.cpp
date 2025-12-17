//implementation file for students

#include "Student.h"
#include <cstring>

Student::Student(char* firstname, char* lastname, int _id, float _gpa) {
    strcpy(firstName, firstname);
    strcpy(lastName, lastname);
    id = _id;
    gpa = _gpa;
}
char* Student::getName(int which) {
    if (!which) {
        return firstName;
    }
    return lastName;
}
int Student::getID() {
    return id;
}
float Student::getGPA() {
    return gpa;
}
Student::~Student() {
    
}
