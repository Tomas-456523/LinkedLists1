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
        word[i] = toupper((unsigned char)word[i]);
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
    
    cout << "\nSuccessfully added " << firstname;
    if (current->getNext() != current) {
        cout << " after " << current->getStudent()->getName(0);
    }
    cout << "!";
}

void printStudent(Student* student, bool newline = true) {
    if (newline) {
        cout << "\n";
    }
    cout << student->getName(0) << " " << student->getName(1) << " (" << student->getID() << ") - GPA of " << student->getGPA();
}

void goNext(Node*& current) {
    if (current == NULL) {
        cout << "\nThere are currently no students. (type ADD for add)";
        return;
    }
    current = current->getNext();
    cout << "\nCurrent student: ";
    printStudent(current->getStudent(), false);
}

void deleteNode(Node*& current) {
    if (current == NULL) {
        cout << "\nThere are no students to delete. (type ADD for add)";
        return;
    }
    Node* previous = current;
    while (previous->getNext() != current) {
        previous = previous->getNext();
    }
    
    cout << "\nSuccessfully deleted " << current->getStudent()->getName(0) << "!";
    if (current == current->getNext()) {
        current = NULL;
    } else {
        goNext(current);
    }
    Node* todel = previous->getNext();
    previous->setNext(todel->getNext());
    delete todel;
    if (current == NULL) {
        cout << "\nThere are no students left.";
    }
}

void analyze(Node* current) {
    if (current == NULL) {
        cout << "\nThere are no students to print. (type ADD for add)";
        return;
    }
    printStudent(current->getStudent());
}

void average(Node* current) {
    if (current == NULL) {
        cout << "\nThere are no students with GPAs to average. (type ADD for add)";
        return;
    }
    Node* init = current;
    float avg = 0;
    int i = 0;
    do {
        avg += current->getStudent()->getGPA();
        current = current->getNext();
        i++;
    } while (current != init);
    cout << "\nAverage GPA: " << fixed << setprecision(2) << avg/i;
}

void printAll(Node* current) {
    if (current == NULL) {
        cout << "\nThere are no students to print. (type ADD for add)";
        return;
    }
    cout << "Students:";
    Node* init = current;
    do {
        printStudent(current->getStudent());
        current = current->getNext();
    } while (current != init);
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
            deleteNode(current);
        } else if (!strcmp(command, "NEXT")) {
            goNext(current);
        } else if (!strcmp(command, "PRINT")) {
            analyze(current);
        } else if (!strcmp(command, "PRINT ALL")) {
            printAll(current);
        } else if (!strcmp(command, "AVERAGE")) {
            average(current);
        } else if (!strcmp(command, "HELP")) {
            cout << "\nYour command words are:\nADD\nDELETE\nNEXT\nPRINT\nPRINT ALL\nAVERAGE\nHELP\nQUIT";
        } else if (!strcmp(command, "QUIT")) {
            continuing = false;
        } else {
            cout << "\nInvalid command \"" << command << "\". (type HELP for help)";
        }
        
        CinIgnoreAll();
    }

    cout <<"\nHasta la vista, baby.\n";

    if (current == NULL) {
        return 0;
    }

    Node* start = current;
    Node* previous;

    do {
        previous = current;
        current = current->getNext();
        delete previous;
    } while (current != start);
}
