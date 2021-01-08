// Lab1_UserInput : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "main.h"


int main()
{
    struct student_Info {
        char student_Num[9];
        float lab_Grade;
        float quiz_Grade;
        float midterm_Grade;
        float finalExam_Grade;
    };
    
    struct student_Info *number_of_students[CLASS_SIZE];//creates an array of 100 pointers to struct of type 'student_info'
    
    std::cout << "Hello World!\n";
}