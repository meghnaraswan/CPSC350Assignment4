#include "DoublyLinkedList.hpp"

#include <iostream>
#include "Student.hpp"
#include "Window.hpp"

using namespace std;

//Doubly Linked List

//default constructor
template <class T>
ListNode<T>::ListNode(){}

//overloaded constructor
template <class T>
ListNode<T>::ListNode(const T& d){
    data = d;
    next = NULL;
    prev = NULL;
}

//destructor
template <class T>
ListNode<T>::~ListNode(){
}

//default constructor
template <class T>
DoublyLinkedList<T>::DoublyLinkedList(){
    front = NULL;
    back = NULL;
    size = 0;
}

//destructor
template <class T>
DoublyLinkedList<T>::~DoublyLinkedList(){
}

//insertFront function inserts a datatype (object or int in this case) to the front of the linked list
template <class T>
void DoublyLinkedList<T>::insertFront(const T& d){
    ListNode<T> *node = new ListNode<T>(d);
    if(size == 0) { //if the size of the list is 0, the back is the node
        back = node;
    } else { //else the next node is the front
        front->prev = node;
        node->next = front;
    }
    front = node; //the front is the node
    ++size; //increment the size of the list
}

//insertBack function inserts a datatype (object or int in this case) to the back of the linked list
template <class T>
void DoublyLinkedList<T>::insertBack(const T& d){
    ListNode<T> *node = new ListNode<T>(d);
    if(size == 0){ //if the size of the list is 0, the front is the node
        front = node;
    } else { //else the previous node is the back
        back->next = node;
        node->prev = back;
    }
    back = node; //the back is the node
    ++size; //increment the size of the list
}

//removeFront function removes a datatype (object or int in this case) from the front of the linked list
template <class T>
T DoublyLinkedList<T>::removeFront(){ 
    ListNode<T> *node = front;
    if(front->next == NULL){ //is the next node points to NULL, the back is NULL
        back = NULL;
    }
    else{ //else the previous node will point to NULL as the front is removed
        front->next->prev = NULL;
    }
    front = front -> next; //the next node will be assigned as the front
    --size; //decrement the size of the list
    node->next = 0; //the next node will point to NULL (since it's in the front)
    T temp = node->data; //data will be stored in a temp variable with generic datatype
    delete node;
    return temp;
}

//print function prints the DoublyLinkedList info
template <class T>
void DoublyLinkedList<T>::print(){
    cout << "DLL size: " + to_string(this->size) << endl;
    ListNode<T> *curr = front;
    int count = 0;
    while(curr != NULL){ //while the current node is not NULL, the current node will move to the next node
        curr = curr->next;
        count ++; //increment count (show size of linked list)
    }
}

//isEmpty function will determine if the list is empty if the size is 0
template <class T>
bool DoublyLinkedList<T>::isEmpty() {
    return (size==0) ;
}

//getSize function will determine the size of the list
template <class T>
unsigned int DoublyLinkedList<T>::getSize() {
    return size;
}

//getFront function will return the data of the front node
template <class T>
T& DoublyLinkedList<T>::getFront() { 
    return front->data;
}

//setCurrentToFront function will set the current value to the front of the list
template <class T>
void DoublyLinkedList<T>::setCurrentToFront() {
    current = front;
}

//getCurrent function will return the current node of the list
template <class T>
ListNode<T>* DoublyLinkedList<T>::getCurrent() {
    ListNode<T>* retPtr = current;
    if (current)
        current = current->next;
    return retPtr;
}

//this is to explicitly instantiate the template
template class DoublyLinkedList<Student>;
template class DoublyLinkedList<Window>;
template class DoublyLinkedList<int>;
