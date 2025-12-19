//implementation file for nodes

#include "Node.h"
#include "Student.h"

Node::Node(Student* _student) {
    student = _student;
}
void Node::setNext(Node* next) {
    nextNode = next;
}
Student* Node::getStudent() {
    return student;
}
Node* Node::getNext() {
    return nextNode;
}
Node::~Node() {
    delete student;
}
