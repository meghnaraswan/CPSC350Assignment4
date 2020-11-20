//#include "Queue.hpp"
#include "DoublyLinkedList.hpp"
#include "Student.hpp"
#include "Window.hpp"
#include "Queue.hpp"
#include "WindowController.hpp"

#include <stdio.h>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

//Simulation

class Simulation{
public:
    
    Simulation(); //default constructor
    ~Simulation(); //destructor

    //attrubutes
    DoublyLinkedList<int> sFinalDLL;
    Queue<Student> sQueue;
    WindowController wc;
    
    //functions
    void initialize(string file);
    void run();
    void print();
    void printWaitTimeDLL();
    void finalOutput();
    void sortWaitTime();
    double meanStudentWaitTime();
    double medianStudentWaitTime();
    int longestStudentWaitTime();
    int numStudentsWaitOverTenMins();

};

//default constructor
Simulation::Simulation(){
    this->sFinalDLL = DoublyLinkedList<int>();
    this->wc = WindowController();
    this->sQueue = Queue<Student>();
}

//destructor
Simulation::~Simulation(){
}

//print function prints information about the Window Controller, Student Queue, and the Final Wait Time List
void Simulation::print(){
    cout << "Window Controller:" << endl;
    this->wc.print();
    cout << "Student Queue:" << endl;
    this->sQueue.print();
    cout << "Final Wait Time List:" << endl;
    this->printWaitTimeDLL();
}

//meanStudentWaitTime function claculates for the mean wait time of all students
double Simulation::meanStudentWaitTime(){
    double sumSWT = 0.0; //initialize the sum
    sFinalDLL.setCurrentToFront();
    ListNode<int>* curr = NULL;
    while ((curr = sFinalDLL.getCurrent()) != NULL) { //iterating through linked list
        sumSWT += curr->data; //sum will keep adding the wait time of each student in the while loop
    }
    return (double)sumSWT/(double)sFinalDLL.getSize(); //overall sum divides by the size of the list will return the mean value
}

//printWaitTimeDLL function prints wait time of each student
void Simulation::printWaitTimeDLL(){
//    cout << "printWaitTimeDLL()" << endl ;
    sFinalDLL.setCurrentToFront();
    ListNode<int>* curr = NULL;
    while ((curr = sFinalDLL.getCurrent()) != NULL) {
        cout << curr->data << endl; //print student wait time data
    }
}

//sortWaitTime function will sort the wait time data of the student in the linked list
void Simulation::sortWaitTime(){
    ListNode<int> *curr = NULL;
    ListNode<int> *next = NULL;
    sFinalDLL.setCurrentToFront();
    for(int i = 0; i < sFinalDLL.getSize()-1; i++) { //iterate through 0 to the size-1 of the linked list
        curr = sFinalDLL.getCurrent();
        next = curr;
        while((next = next->next) != NULL) { //while each value after the next value of the current value is not NULL
            if(curr->data < next->data) { //if the current data (wait time) is less than the next data (wait time) then swap the student objects in the linked list (linked list will be in reverse order in descending order of idle time)
                int temp = curr->data;
                curr->data = next->data;
                next->data = temp;
            }
        }
    }
//    cout << "after sortWaitTime" << endl ;
    printWaitTimeDLL();
}

//medianStudentWaitTime function use the sort function to search for the middle of the list to find the median
double Simulation::medianStudentWaitTime(){
    double ret_val = 0.0; //initialize to 0.0
    ListNode<int> *curr = NULL;
    sFinalDLL.setCurrentToFront();
    bool isOdd = (sFinalDLL.getSize()%2 == 1); //the list size is odd if the entire size's modulus is 1
    for(int i = 0; i < int(sFinalDLL.getSize()/2); i++) { //move the pointer to center
        curr = sFinalDLL.getCurrent(); //the last value (middle of the list) is the current value
    }
    if(isOdd) { //if list size is odd, the current value is the median
        ret_val = curr->data;
    } else { //if list size is even, the current value and the next value will be added and then divided by 2 to find the median
        ret_val = curr->data;
        ret_val += curr->next->data;
        ret_val = ret_val/2;
    }
    return ret_val;
}

//longestStudentWaitTime function will pick the longest wait time from the linked list from the front of the linked list since the list is in descending order
int Simulation::longestStudentWaitTime(){
    sFinalDLL.setCurrentToFront();
    return sFinalDLL.getCurrent()->data; //get the data from the first node of the linked list
}

//numStudentsWaitOverTenMins function will find the number of students that were wating over 10 minutes
int Simulation::numStudentsWaitOverTenMins(){
    int numOverTenMins = 0;
    sFinalDLL.setCurrentToFront();
    ListNode<int>* curr = NULL;
    while ((curr = sFinalDLL.getCurrent()) != NULL) { //iterating through linked list
        if (curr->data <= 10) { //if the current student's idle time is less than or equal to 10 minutes, break
            break;
        }
        numOverTenMins++; //increment numOverTenMins as statements break from loop
    }
    return numOverTenMins;
}

//run function will run the simulation of adding students in the queue, remove students from queue as they are assigned to the respective window, and calculate the wait time for the students
void Simulation::run(){
//    cout << "Simulation::run()" << endl;
    int tickTime = 0;
    while(!(sQueue.isEmpty() && wc.allWindowsAreAvailable())){ //while the queue is not empty and the windows are not all available (room isn't empty)
        Student *ps = sQueue.peek(); //student object calls peek function from Queue
        while(ps != NULL) { //while the queue is not NULL
            if(tickTime >= ps->arrivalTime){ // time to assign this student to window
//                cout << tickTime  << "," << ps->arrivalTime<< endl;
                if(wc.assignStudentToWindow(*ps)) { // window avaialbe, can assign
                    Student s2 = sQueue.remove();
//                    cout << "Assigned: " << s2.toString() << endl;
                    this->sFinalDLL.insertFront(s2.waitTime); //insert wait time to student linked list
                    ps = sQueue.peek(); //peek queue
                } else { // no window avaialbe at this tickTime, cannot assign
                    ps->waitTime++; //increment wait time as no window is yet available
//                    cout << ps->toString() << endl;
                    ps = sQueue.peekNext(); //peek next to current object
                    //                    break;
                }
            } else { //if(s.arrivalTime > tickTime) (it's not time to move student to window)
//                cout << "Done for this tickTime:" << tickTime << "," << ps->arrivalTime << endl;
                break; // student arrival time is late than the ticktime
            }
        } //break loop if queue is empty and windows are all availbale (room is empty)
        ++tickTime; //add tick time
        wc.moveToNextTime(); //increase idle time and decrease remaining service time accordingly
//        cout << tickTime << endl;
//        if (tickTime >= 50) break;
    }
    return;
}

//finalOutput function outputs all of the wait time and idle time info
void Simulation::finalOutput() {
    this->sortWaitTime(); //call sortWaitTime function
    
    cout << "+------------------------------------+" << endl;
    cout << "+-------- Student Stats -------------+" << endl;
    cout << "+------------------------------------+" << endl;
    cout << "Mean Student Wait Time:" << this->meanStudentWaitTime() << endl;
    cout << "Median Student Wait Time:" << this->medianStudentWaitTime() << endl;
    cout << "Longest Student Wait Time:" << this->longestStudentWaitTime() << endl;
    cout << "Student Wait Time Over 10 Minutes:" << this->numStudentsWaitOverTenMins() << endl;
    cout << endl;

    cout << "+------------------------------------+" << endl;
    cout << "+-------- Window Stats --------------+" << endl;
    cout << "+------------------------------------+" << endl;
    cout << "Mean Window Idle Time:" <<  wc.meanWindowIdleTime() << endl;
    cout << "Longest Window Idle Time:" << wc.longestWindowIdleTime() << endl;
    cout << "Window Idle Time Over 5 Minutes:" << wc.numWindowsIdleForFiveMins() << endl;
    cout << endl;
}

//initialize function will evaluat the numbers in the given file
void Simulation::initialize(string userFileName) {
//    cout << "Simulation::initialize()" << endl;
    std::fstream newfile; //fstream is a stream class to both read and write from/to files.
    newfile.open(userFileName, std::ios::in); //open a file to perform read operation using file object
    int numOpenWindows = 0;
    int lineCount = 0;
    if (newfile.is_open()){ //shows if the stream is associated with the file
        string line;
        while(getline(newfile, line)){ //read data from file object and put it into string.
            ++lineCount; //increasing line count by 1 after reading though the next file
            if(lineCount == 1){ // this is window count
                numOpenWindows = stoi(line); //convert string to int
                this->wc.initialize(numOpenWindows); //call initialize function from window class to
            } else { // this is for student info
                int studentArrivalTime = stoi(line); //convert string to int
                getline(newfile, line); //read data from file object and put it into string.
                ++lineCount;
                int numStudentsArriveAtSameTime = stoi(line); //convert string to int
                for (int i = 0 ; i<numStudentsArriveAtSameTime; i++ ) { // this for each students service time
                    getline(newfile, line); //read data from file object and put it into string.
                    ++lineCount;
                    int serviceTime = stoi(line); //convert string to int
                    sQueue.insert(Student(studentArrivalTime, serviceTime));
                }
            }
        }
        newfile.close(); //close the file object.
    } else {
        cout << "Unable to open file: " + userFileName << endl;
    }
    return;
}

int main (int argc, char **argv) {
    string userFileName; //user file name variable
    if (argc < 2) { //if the arguments on the command line are less than 2 (meaning the user did not add the file name), then return an error
        cout << "You did not add a file name";
        return 0; //exit
    } else { //else, userFileName is the commandline user input
        userFileName = argv[1];
    }
    Simulation sim = Simulation();
//    sim.initialize("/home/FirstCPP/RegistrarOfficeSimulation/registrar.test.sim.1.txt");
    sim.initialize(userFileName);
//    sim.print();
    sim.run();
//    sim.print();

    sim.finalOutput();
    return 0;
}
    
