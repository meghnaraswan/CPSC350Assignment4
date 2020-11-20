#include "Queue.hpp"
#include <iostream>
#include "Student.hpp"

using namespace std;

//Queue

//default constructor
template <class T>
Queue<T>::Queue(){
    myLinkedList = DoublyLinkedList<Student>();
}

//destructor
template <class T>
Queue<T>::~Queue(){
}

//insert function inserts a node to the queue
template <class T>
void Queue<T>::insert(const T& d){
    myLinkedList.insertBack(d);
}

//remove function removes the first node in the queue
template <class T>
T Queue<T>::remove(){ 
    return myLinkedList.removeFront();
}

//peek function returns the front value of the queue
template <class T>
T* Queue<T>::peek(){
    myLinkedList.setCurrentToFront();
    return &(myLinkedList.getFront());
}

//peekNext function returns the node behind the current (front) node
template <class T>
T* Queue<T>::peekNext(){ 
    return &(myLinkedList.getCurrent()->next->data);
}

//isEmpty function checks to see whether the queue is empty
template <class T>
bool Queue<T>::isEmpty(){
    return myLinkedList.isEmpty();
}

//getSize function returns the size of the queue
template <class T>
unsigned int Queue<T>::getSize(){
    return myLinkedList.getSize();
}

//print function prints the information of the queue queue
template <class T>
void Queue<T>::print() {
    cout << "Queue<T>::print()" << endl;
    myLinkedList.print();
}

//queue will only contain datatype Student
template class Queue<Student>;
