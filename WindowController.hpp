//
//  WindowController.hpp
//  FirstCPP
//
//  Created by iMan on 11/17/20.
//  Copyright © 2020 iMan. All rights reserved.
//

#ifndef WindowController_hpp
#define WindowController_hpp

#include <stdio.h>
#include <string>
#include "Window.hpp"
#include "Student.hpp"
#include "DoublyLinkedList.hpp"

using namespace std;


class WindowController {
    public:
        WindowController(); //overloaded constructor
        WindowController(int num_windows); //default constructor
        ~WindowController(); //destructor
        
        //functions
        void initialize(int num_windows);
        bool assignStudentToWindow(Student s);
        bool allWindowsAreAvailable();
        void moveToNextTime();
        void print();
        void sortbyIdleTime();
        double meanWindowIdleTime();
        int longestWindowIdleTime();
        int numWindowsIdleForFiveMins();
    
        //attributes
        DoublyLinkedList<Window> wDLL;

};

#endif /* WindowController_hpp */

