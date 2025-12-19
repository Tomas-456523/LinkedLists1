/* Tomas Carranza Echaniz
*  12/19/2025
*  This program is a cyclical student database that uses linked lists. It is for showcasing the functionality of the
*  Node.h and Node.cpp files. You can ADD a new student, which will be added after the current node. You can DELETE
*  the student, which will move you to the next student. You can go to the NEXT student, and PRINT the student's data.
*  You can also PRINT ALL the students at once, or print the AVERAGE of all their GPAs. You can also ask for HELP,
*  which will print all the valid commands, or QUIT the program.
*/

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

//capitalizes the given charray for easier command interpretation
void AllCaps(char* word) {
    for (int i = 0; i < strlen(word); i++) { //sets all the characters to a capitalized unsigned version of the char (unsigned because some systems sign the chars)
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

//creates a new student and a new node pointing to it, which is inserted after the given node
void addNode(Node*& current) {
    char name[255]; //the name to be split into the first and last name
    char firstname[255];
    char lastname[255];
    int id;
    float gpa;
    
    ///get the student's first and last names
    cout << "\nEnter full name for new student.";
    bool continuing = true; //continues until valid input is given
    while (continuing) {
        cout << "\n> ";
        cin.getline(name, 255);
        if (cin) { //end loop if input was valid
            continuing = false;
        } else { //error message
            cout << "\nName too long.";
        }
        CinIgnoreAll(); //clear any faulty or extra input given
    } //splits the name into the first and last name
    ParseName(&name[0], &firstname[0], &lastname[0]);
    
    //get the student's id
    cout << "\nEnter " << firstname << "'s student ID.";
    continuing = true; //continues until valid input is given
    while (continuing) {
        cout << "\n> ";
        cin >> id; //gets the id integer
        if (cin) { //end loop if input was valid
            continuing = false;
        } else { //otherwise give error message
            cout << "\nID must be an integer.";
        }
        CinIgnoreAll(true); //removes the newline character or invalid input
    }
    
    cout << "\nEnter " << firstname << "'s GPA.";
    continuing = true; //continues until valid input is given
    while (continuing) {
        cout << "\n> ";
        cin >> gpa; //gets the gpa float
        if (cin) { //end loop if valid input was given
            continuing = false;
        } else { //error message otherwise
            cout << "\nGPA must be a float.";
        }
        CinIgnoreAll(true); //removes the newline character of invalid input
    }
    
    //creates a new student using the given data
    Student* student = new Student(&firstname[0], &lastname[0], id, gpa);
    //create a new node pointing to the new student
    Node* node = new Node(student);
    
    if (current == NULL) { //if there are no nodes yet, the node points to itself
        current = node;
        node->setNext(node);
    } else { //otherwise, we make the node point to the node after current, and put it after the current node
        node->setNext(current->getNext());
        current->setNext(node);
    }
    
    cout << "\nSuccessfully added " << firstname; //success message
    if (current->getNext() != current) { //if it isn't the only node, we print which node we put it after (current)
        cout << " after " << current->getStudent()->getName(0);
    }
    cout << "!"; //exclamation mark!
}

//prints the given student (with option to put the data in a new line)
void printStudent(Student* student, bool newline = true) {
    if (newline) { //prints the new line if we need to
        cout << "\n";
    } //prints all the student's data
    cout << student->getName(0) << " " << student->getName(1) << " (" << student->getID() << ") - GPA of " << student->getGPA();
}

//set the current node to the one after it
void goNext(Node*& current) {
    if (current == NULL) { //can't go to the next node if there are no nodes so we print error message and return
        cout << "\nThere are currently no students. (type ADD for add)";
        return;
    } //move to the next node
    current = current->getNext();
    cout << "\nCurrent student: "; //prints the new current student's data
    printStudent(current->getStudent(), false);
}

//deletes the current node, and bridges the gap created as a result
void deleteNode(Node*& current) {
    if (current == NULL) { //can't delete students if there's no students so we give error message and return
        cout << "\nThere are no students to delete. (type ADD for add)";
        return;
    } //finds the node before the current one, starting with the current one (faster than starting with the next one in case of only one node)
    Node* previous = current;
    while (previous->getNext() != current) { //goes through the node loop until we find the node pointing to the current one; that is the previous node
        previous = previous->getNext();
    }
    
    cout << "\nSuccessfully deleted " << current->getStudent()->getName(0) << "!"; //success message
    if (current == current->getNext()) { //if there's only one node, it's pointing to itself, and we just nullify the current node since there will be no more nodes to point to
        current = NULL;
    } else {
        goNext(current); //goes to the next node, printing the new current node's data in the process
    }
    Node* todel = previous->getNext(); //gets the node to delete, so that we can get the node after it AND delete the node without losing access to it
    previous->setNext(todel->getNext()); //bridges the gap caused by deleting the node; previous node now points to the node after the one that got deleted
    delete todel; //deletes the node
    if (current == NULL) { //prints if we deleted the last node/student combo
        cout << "\nThere are no students left.";
    }
}

//prints the given student's data, so the user can see the student again without going all the way around the node loop
void analyze(Node* current) {
    if (current == NULL) { //print error message and return if there are no nodes/students with data to print
        cout << "\nThere are no students to print. (type ADD for add)";
        return;
    } //prints the current node's student's data
    printStudent(current->getStudent());
}

//prints the average gpa of all the students
void average(Node* current) {
    if (current == NULL) { //print error message and return if there are no students with GPAs to average
        cout << "\nThere are no students with GPAs to average. (type ADD for add)";
        return;
    } //gets the starting node so we know when we've gone all the way around
    Node* init = current;
    float sum = 0; //all the GPAs summed up
    int i = 0; //how many nodes we've checked so far
    do { //add to the average until we get to the one before current (do loop at least once, so we ignore the starting node the first time)
        sum += current->getStudent()->getGPA();
        current = current->getNext(); //move to the next node
        i++; //add one to the node counter
    } while (current != init);
    //print the sum over the count (average formula) with up to two decimal points of precision
    cout << "\nAverage GPA: " << fixed << setprecision(2) << sum/i;
}

//print all the students' data
void printAll(Node* current) {
    if (current == NULL) { //print error message and return if there are no students to print
        cout << "\nThere are no students to print. (type ADD for add)";
        return;
    }
    cout << "\nStudents:";
    Node* init = current; //gets the starting node so we know when we've gone all the way around
    do { //print the student's data until we get to the first node (loop at least once so we ignore the first node initially, otherwise nothing would print)
        printStudent(current->getStudent());
        current = current->getNext(); //move to the next node
    } while (current != init);
}

//the main player loop
int main() {
    Node* current = NULL; //the current node, starts with no nodes
    
    //welcome message with instructions
    cout << "\nWelcome to STUDENT LIST 2: ELECTRIC BOOGALOO!\nYou are on a quest to make a weird cyclical student database.\nType HELP for help.\n\nThere are currently no students. (type ADD for add)";
    
    //continues until continuing is falsified (by typing QUIT)
    bool continuing = true;
    while (continuing) {
        char command[255]; //the command that the user inputs into
        
        cout << "\n> "; //thing for the player to type after
        
        cin.getline(command, 255); //gets the player input, up to 255 characters
        
        AllCaps(&command[0]); //capitalizes the command for easier interpretation
        
        //calls function corresponding to the given command word
        if (!strcmp(command, "ADD")) { //add student
            addNode(current);
        } else if (!strcmp(command, "DELETE")) { //delete current student
            deleteNode(current);
        } else if (!strcmp(command, "NEXT")) { //go to next student
            goNext(current);
        } else if (!strcmp(command, "PRINT")) { //print current student
            analyze(current);
        } else if (!strcmp(command, "PRINT ALL")) { //print all students
            printAll(current);
        } else if (!strcmp(command, "AVERAGE")) { //print average gpa of all students
            average(current);
        } else if (!strcmp(command, "HELP")) { //print all valid command words
            cout << "\nYour command words are:\nADD\nDELETE\nNEXT\nPRINT\nPRINT ALL\nAVERAGE\nHELP\nQUIT";
        } else if (!strcmp(command, "QUIT")) { //quit the program
            continuing = false; //leave the main player loop
        } else { //give error message if the user typed something unacceptable
            cout << "\nInvalid command \"" << command << "\". (type HELP for help)";
        }
        
        CinIgnoreAll(); //ignore any invalid or extra input that may have been typed this time
    }

    //prints a goodbye for proper manners
    cout <<"\nHasta la vista, baby.\n";

    if (current == NULL) { //skip deletion stuff if there's nothing to deallocate
        return 0;
    }

    Node* start = current; //gets the start node so we know when we're back here
    Node* previous; //the node before the one currently being checked, we need this so we can get the next node from the current one while still deleting it

    do { //deallocates all the nodes, which in turn delete their corresponding students. Run at least once, so the loop doesn't end immediately by seeing that current is init
        previous = current; //set previous to the current one and move current forward to the next node
        current = current->getNext();
        delete previous; //delete the previous node
    } while (current != start); //end when we reach the starting node pointer again
}
