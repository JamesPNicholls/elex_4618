// Lab1_UserInput : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include "main.h"

int number_of_student = 0;
int main()
{
    struct student_Info new_Students[100];
    uint8_t command; //var used to track the key press and decide what function to run

    while (1)
    {
        print_Menu(); //Prints menu showing the commands
        std::cout << "Choose commands: ";
        std::cin >> command;//waits for input command

        if(command == 'a' || command == 'A') //add student
        {
            add_Student( new_Students[number_of_student]);
            number_of_student++;
        }
        else if(command == 'e' || command == 'E') // edit student
        {
            uint8_t temp_student_num;
            std::cout << "Student to Edit: ";
            std::cin >> temp_student_num;
            if (temp_student_num < number_of_student)
            {
                std::cout << "Student does not exist\n\n";
            }
            else
            {
                edit_Student(new_Students[temp_student_num]);
                break;
            }            
        }
        else if (command == 'p' || command == 'P') // Print Grades
        {
            for ( int i = 0; i < number_of_student; i++)
            {
                print_Grades(new_Students[ZERO_STUDENT], i);
            }
               
        }
        else if (command == 'q' || command == 'Q') // Quit Application
        {
            return 0;
        }
        else
        {
            std::cout << "Not a recognized command\n";
        }
    }
}