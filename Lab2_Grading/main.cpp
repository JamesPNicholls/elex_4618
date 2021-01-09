// Lab2_Grading.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string.h>
#include "main.h"

/*
* Things to add:
*   (DONE)fix the spacing with /t thanks aman
*   (DONE) string instead of char array                                            
*   add size checking and start char are A01/A00 for student_number
*   add bounds for all grades need to be between 0.0 and 100.0
*   replace number_of_student with the size function
* 
*   add delete_student() fnc
*   add load_lass() fnc
*   add save_Class() fnc
*       implement load/save/delete with text files
*/


int number_of_student = 0; //replace with the size function
int main()
{
    struct student_Info new_Students[100];
    uint8_t command; //var used to track the key press and decide what function to run

    while(1)
    {
        print_Menu(); //Prints menu showing the commands
        std::cout << "Choose commands: ";
        std::cin >> command;//waits for input command
        if (command == 'a' || command == 'A') //add student
        {
            add_Student(new_Students[number_of_student]);
            number_of_student++;
        }
        else if (command == 'e' || command == 'E') // edit student
        {
            int temp_student_num;
            std::cout << "Student to Edit: ";
            std::cin >> temp_student_num;
            if (temp_student_num >= number_of_student)//check to see if a valid student is selected
            {
                std::cout << "Student does not exist\n\n";
            }
            else
            {
                edit_Student(new_Students[temp_student_num]);
            }
        }
        else if (command == 'p' || command == 'P') // Print Grades
        {
            for (int i = 0; i < number_of_student; i++)
            {
                print_Grades(new_Students[i], i);//print each of the students stored in the 'new_student' array
            }
            std::cout << "\n";
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