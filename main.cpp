#include <iostream>
#include <limits>
#include <cstring>
#include <iomanip>
#include "Student.h"
#include "Node.h"
using namespace std;

//for ignoring faulty input and extra characters, functionality taken from my previous projects
void CinIgnoreAll(bool force = false) {
    if (!cin || force) { //only go if input is faulty, otherwise forces the user to input an extra enter
        cin.clear(); //clears error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ignores all characters up until a new line
    }
}

void AllCaps(char* word) {
    for (int i = 0; i < strlen(word); i++) {
        word[i] = toupper(word[i]);
    }
}

//takes the full name charray and splits it into first name and last name, functionality taken from my Zuul
void ParseName(char* full, char* first, char* last) {
    int i = 0; //the current char we're checking
    while (full[i] != ' ' && full[i] != '\0') {
        first[i] = full[i]; //puts the character in the first name portion
        i++; //advances the check position
    }
    first[i] = '\0'; //caps the end of the first name with a null terminator
    if (full[i] == '\0') { //return and set the last name to blank if we're at the end of the full name
        strcpy(last,"");
        return;
    }
    i++; //skip the space
    int j = i; //i - j == the current position for the last name
    while (full[i] != '\0') { //sets the last name to the rest of the full name
        last[i - j] = full[i];
        i++; //increment the checking position
    }
    last[i - j] = '\0'; //null terminates the last name
}

void addNode(Node*& current) {
    char name[255];
    char firstname[255];
    char lastname[255];
    int id;
    float gpa;
    
    cout << "\nEnter full name for new student.";
    bool continuing = true;
    while (continuing) {
        cout << "\n> ";
        cin.getline(name, 255);
        if (cin) {
            continuing = false;
        } else {
            cout << "\nName too long.";
        }
        CinIgnoreAll();
    }
    ParseName(&name[0], &firstname[0], &lastname[0]);
    
    cout << "\nEnter " << firstname << "'s student ID.";
    continuing = true;
    while (continuing) {
        cout << "\n> ";
        cin >> id;
        if (cin) {
            continuing = false;
        } else {
            cout << "\nID must be an integer.";
        }
        CinIgnoreAll(true);
    }
    
    cout << "\nEnter " << firstname << "'s GPA.";
    continuing = true;
    while (continuing) {
        cout << "\n> ";
        cin >> gpa;
        if (cin) {
            continuing = false;
        } else {
            cout << "\nGPA must be a float.";
        }
        CinIgnoreAll(true);
    }
    
    Student* student = new Student(&firstname[0], &lastname[0], id, gpa);
    Node* node = new Node(student);
    
    if (current == NULL) {
        current = node;
        node->setNext(node);
    } else {
        node->setNext(current->getNext());
        current->setNext(node);
    }
    
    cout << "Successfully added " << firstname << " after " << current->getStudent()->getName(1) << "!";
}

void goNext(Node*& current) {
    if (current == NULL) {
        cout << "\nThere are currently no students. (type ADD for add)";
        return;
    }
    current = current->getNext();
    Student* student = current->getStudent();
    cout << "\nCurrent student: " << student->getName(1) << " " << student->getName(2) << " (" << student->getID() << ")";
}

void deleteNode(Node*& current) {
    if (current == NULL) {
        cout << "\nThere are no students to delete. (type ADD for add)";
        return;
    }
    Node* todel = current;
    while (current->getNext() != todel) {
        current = current->getNext();
    }
    current->setNext(todel->getNext());
    cout << "\nSuccessfully deleted " << todel->getStudent()->getName(1) << "!";
    if (current == todel) {
        current = NULL;
    }
    delete todel;
    goNext(current);
}

void analyze(Node* current) {
    if (current == NULL) {
        cout << "\nThere are no students to analyze. (type ADD for add)";
        return;
    }
    Student* student = current->getStudent();
    cout << student->getName(1) << " " << student->getName(2) << " (" << student->getID() << ") - GPA of " << student->getGPA();
}

void average(Node* current) {
    if (current == NULL) {
        cout << "\nThere are no students. (type ADD for add)";
        return;
    }
    Node* init = current;
    float avg = current->getStudent()->getGPA();
    current = current->getNext();
    while (current != init) {
        avg += current->getStudent()->getGPA();
        current = current->getNext();
    }
    cout << "Average GPA: " << fixed << setprecision(2) << avg;
}

int main() {
    bool continuing = true;
    
    Node* current = NULL;
    
    cout << "\nWelcome to STUDENT LIST 2: ELECTRIC BOOGALOO!\nYou are on a quest to make a weird cyclical student database.\nType HELP for help.\n\nThere are currently no students. (type ADD for add)";
    while (continuing) {
        char command[255];
        
        cout << "\n> ";
        
        cin.getline(command, 255);
        
        AllCaps(&command[0]);
        
        if (!strcmp(command, "ADD")) {
            addNode(current);
        } else if (!strcmp(command, "DELETE")) {
            
        } else if (!strcmp(command, "NEXT")) {
            goNext(current);
        } else if (!strcmp(command, "ANALYZE")) {
            analyze(current);
        } else if (!strcmp(command, "AVERAGE")) {
            average(current);
        } else if (!strcmp(command, "HELP")) {
            cout << "\nYour command words are:\nADD\nDELETE\nNEXT\nANALYZE\nAVERAGE\nHELP\nQUIT";
        } else if (!strcmp(command, "QUIT")) {
            continuing = false;
        } else {
            cout << "\nInvalid command \"" << command << "\". (type HELP for help)";
        }
        
        CinIgnoreAll();
    }
    
    cout <<"\nHasta la vista, baby.\n";
}
