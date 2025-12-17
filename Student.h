//header file for students

#ifndef STUDENT
#define STUDENT

class Student {
public:
    Student(char* firstname, char* lastname, int _id, float _gpa);
    ~Student();
    
    char* getName(int which);
    int getID();
    float getGPA();
private:
    char firstName[255];
    char lastName[255];
    int id;
    float gpa;
};
#endif
