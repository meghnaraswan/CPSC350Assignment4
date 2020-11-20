#include "Window.hpp"
#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

//Window

//default constructor
Window::Window(){
    idleTime = 0; // window idle time 
    remainingServiceTime = 0; //means window is available
}

//destructor
Window::~Window(){
}

//isAvailable function determins if the window is available
bool Window::isAvailable(){
    return (remainingServiceTime == 0); //is available if the remianing service time is 0
}

//toString function to output information for Window class
string Window::toString(){
    return "Win (Idle Time: " + to_string(this->idleTime) + ", " + "remainingServiceTime: " + to_string(this->remainingServiceTime) + ")";
}

//moveToNextTime function decrements the remaining service time or increments the idle time depending on whether the student is occupying this window or not
void Window::moveToNextTime() {
    if(remainingServiceTime > 0) { //if the remaining service time is greater than 0 (meaning student is occupying the windw) then the remainingServiceTime will decrement as each tick time goes by
        remainingServiceTime--;
    } else { //otherwise, the window's idle time will increase (meaning no student is occupying this window)
        idleTime++;
    }
}

//assignStudentToWindow function assigns the remaining service time of the window with the service time of the student
void Window::assignStudentToWindow(Student s){ 
    remainingServiceTime = s.serviceTime;
}
