#ifndef Student_hpp
#define Student_hpp

#include <stdio.h>
#include <string>
//#include "DoublyLinkedList.hpp"
using namespace std;


class Student {
    public:
        Student(); //default constructor
        Student(int arrivalTime, int serviceTime); //overloaded constructor
        ~Student(); //destructor
        
        //functions
        string toString();

        //attributes
        int arrivalTime;
        int serviceTime;
        int waitTime = 0;
 };

#endif /* Student_hpp */
