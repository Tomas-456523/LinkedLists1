//header file for nodes

#ifndef NODE
#define NODE

class Student;

class Node {
public:
    Node(Student* _student);
    ~Node();
    
    void setNext(Node* next);
    
    Student* getStudent();
    Node* getNext();
private:
    Node* nextNode;
    Student* student;
};
#endif
