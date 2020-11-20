#ifndef Queue_hpp
#define Queue_hpp

#include <stdio.h>
#include "DoublyLinkedList.hpp"

using namespace std;

template <class T> //template to operate on generic types
class Queue {
    public:
        Queue(); //default constructor
        ~Queue(); //destructor
        
        //functions
        void insert(const T&); //enqueue
        T remove(); //dequeue
        T* peek();
        T* peekNext();
        bool isEmpty();
        unsigned int getSize();
        void print();
    
    private:
        //attributes
        DoublyLinkedList<T> myLinkedList;
};

#endif /* Queue_hpp */

