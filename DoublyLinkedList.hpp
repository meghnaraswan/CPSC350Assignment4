#ifndef DoublyLinkedList_hpp
#define DoublyLinkedList_hpp

#include <stdio.h>


template <class T> //template to operate on generic types
class ListNode{
    public:
        ListNode(); //default constructor
        ListNode(const T&); //overloaded constructor
        ~ListNode(); //destructor
    
        //attributes
        T data;
        ListNode<T> *next;
        ListNode<T> *prev;
};

template <class T> //template to operate on generic types
class DoublyLinkedList{
    private:
        //attributes
        ListNode<T> *front;
        ListNode<T> *back;
        unsigned int size;
        ListNode<T> *current;
    
    public:
        DoublyLinkedList(); //default constructor
        ~DoublyLinkedList(); //destructor
    
        //functions 
        void insertFront(const T&);
        void insertBack(const T&);
        T removeFront();
        T& removeBack();
        void print();
        bool isEmpty();
        unsigned int getSize();
        void setCurrentToFront();
        ListNode<T>* getCurrent();
        T& getFront();
};

#endif /* DoublyLinkedList_hpp */
