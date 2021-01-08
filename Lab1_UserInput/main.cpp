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
        std::cout << "Choose commands: \n";
        std::cin >> command;//waits for input command

        if(command == 'a' || command == 'A') //add student
        {
            add_Student( new_Students[number_of_student]);
            number_of_student++;
        }
        else if(command == 'e' || command == 'E') // edit student
        {
            edit_Student();
        }
        else if (command == 'p' || command == 'P') // Print Grades
        {
             print_Grades();
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