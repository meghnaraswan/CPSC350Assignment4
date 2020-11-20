#include "Student.hpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Student

//default constructor
Student::Student(){
    arrivalTime = 0; //student arrival time (what time student arrives in the queue)
    serviceTime = 0; //student service time (how much time student will take at a window)
    waitTime = 0; //student wait time (how long student will have to wait in the queue)
}

//overloaded constructor
Student::Student(int aT, int sT){
    arrivalTime = aT;
    serviceTime = sT;
    waitTime = 0;
}

//destructor
Student::~Student(){
}

//toString function to output information for Student class
string Student::toString(){
    return "Student (Arrival Time: " + to_string(this->arrivalTime) + ", Service Time: " + to_string(this->serviceTime)  + ", Wait Time: " + to_string(this->waitTime) + ")";
}
