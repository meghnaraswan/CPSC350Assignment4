//
//  WindowController.cpp
//  FirstCPP
//
//  Created by iMan on 11/17/20.
//  Copyright © 2020 iMan. All rights reserved.
//

#include "WindowController.hpp"
#include "DoublyLinkedList.hpp"
#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

//Window Controller

//default constructor
WindowController::WindowController(){
    this->wDLL = DoublyLinkedList<Window>(); //Doubly Linked List of Windows
}

//overloaded constructor
WindowController::WindowController(int num_windows){
    this->wDLL = DoublyLinkedList<Window>();
    for (int i = 0 ; i < num_windows; i++ ) { //for loop for inserting each window into the linked list
        this->wDLL.insertBack(Window());
    }
}

//destructor
WindowController::~WindowController(){
}

//initialize function inserts each window into the linked
void WindowController::initialize(int num_windows){
    for (int i = 0 ; i < num_windows; i++) {
        this->wDLL.insertBack(Window());
    }
}

//assignStudentToWindow function will return a boolean to assign a student to a window
bool WindowController::assignStudentToWindow(Student s){
    bool ret_val = false;
    ListNode<Window>* curr = NULL;
    wDLL.setCurrentToFront();
    while ((curr = wDLL.getCurrent()) != NULL) { // return true if assigned to a window else return false if no avialable window
        if (curr->data.isAvailable()){
            curr->data.assignStudentToWindow(s); //call assignStudentToWindow from Window class
            ret_val = true;
            break;
        }
    }
    return ret_val;
}

//moveToNextTime function will update either the idle time or the remaining service time of the window as the tick time increases
void WindowController::moveToNextTime(){
    ListNode<Window>* curr = NULL;
    wDLL.setCurrentToFront();
    while ((curr = wDLL.getCurrent()) != NULL) {
        curr->data.moveToNextTime(); //call moveToNextTime from Window class (refers to current window)
    }
}

// pring function prints the Window Controller info
void WindowController::print(){
    cout << "WindowController::print()" << endl;
    cout << "Number of Windows: " << wDLL.getSize() << endl;
    wDLL.setCurrentToFront();
    ListNode<Window> *curr = wDLL.getCurrent();
    int count = 0;
    while(curr != NULL){
        cout << to_string(count) << ". " << curr->data.toString() << endl; //output data of each window wile iterating through list
        curr = curr->next;
        count ++;
    }
}

//allWindowsAreAvailable function wll return a boolean of whether all windows are available
bool WindowController::allWindowsAreAvailable(){
    bool ret_val = true;
    ListNode<Window>* curr = NULL;
    wDLL.setCurrentToFront();
    while ((curr = wDLL.getCurrent()) != NULL) { //checks each window in the list to see if the window is available or not
        if (! curr->data.isAvailable()){
            ret_val = false; //if at least one window is not available, function will return false
            break;
        }
    }
    return ret_val;
}

//sortbyIdleTime function will sort the idle time data of the window in the linked list
void WindowController::sortbyIdleTime(){
    this->wDLL.print();
    ListNode<Window> *curr = NULL;
    ListNode<Window> *next = NULL;
    this->wDLL.setCurrentToFront();
    for(int i = 0; i < wDLL.getSize()-1; i++) { //iterate through 0 to the size-1 of the linked list
        curr = this->wDLL.getCurrent();
        next = curr;
        while((next = next->next) != NULL) { //while each value after the next value of the current value is not NULL
            if(curr->data.idleTime < next->data.idleTime) { //if the current data (idle time) is less than the next data (idle time) then swap the window objects in the linked list (linked list will be in reverse order in descending order of idle time)
                Window temp = curr->data;
                curr->data = next->data;
                next->data = temp;
            }
        }
    }
    wDLL.print();
}

//longestWindowIdleTime function will pick the longest idle time from the linked list from the front of the linked list since the list is in descending order
int WindowController::longestWindowIdleTime(){
    wDLL.setCurrentToFront();
    return wDLL.getCurrent()->data.idleTime; //get the data from the first node of the linked list
}

//numWindowsIdleForFiveMins function will find the number of windows that were idle over 5 minutes
int WindowController::numWindowsIdleForFiveMins(){
    int numOverFiveMins = 0;
    wDLL.setCurrentToFront();
    ListNode<Window>* curr = NULL;
    while ((curr = wDLL.getCurrent()) != NULL) { //iterating through linked list
        if (curr->data.idleTime <= 5) { //if the current window's idle time is less than or equal to 5 minutes, break
            break;
        }
        numOverFiveMins++; //increment numOverFiveMins as statements break from loop
    }
    return numOverFiveMins;
}

//meanWindowIdleTime function claculates for the mean idle time of all windows
double WindowController::meanWindowIdleTime(){
    double sumWIT = 0.0; //initialize the sum
    wDLL.setCurrentToFront();
    ListNode<Window>* curr = NULL;
    while ((curr = wDLL.getCurrent()) != NULL) { //iterating through linked list
        sumWIT += curr->data.idleTime; //sum will keep adding the idle time of each window in the while loop
    }
    return (double)sumWIT/(double)wDLL.getSize(); //overall sum divides by the size of the list will return the mean value
}
