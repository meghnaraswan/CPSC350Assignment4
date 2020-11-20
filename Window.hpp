#ifndef Window_hpp
#define Window_hpp
//#include "DoublyLinkedList.hpp"

#include <stdio.h>
#include <string>
#include "Student.hpp"

using namespace std;

class Window {
    public:
        Window(); //default constructor
        ~Window(); //destructor
        
        //attributes
        int idleTime;
        int remainingServiceTime;

        //functions
        bool isAvailable();
        void moveToNextTime();
        string toString();
        void assignStudentToWindow(Student s);
};

#endif /* Window_hpp */
