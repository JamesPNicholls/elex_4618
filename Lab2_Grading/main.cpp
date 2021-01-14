// Lab2_Grading.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string.h>
#include <fstream>
#include <regex>
#include "main.h"
#include "CStudent.h"
#include "CCourse.h"


/*
* Things to add:
*   (DONE) fix the spacing with /t, thanks aman
*   (DONE) string instead of char array                                            
*   (DONE) add size checking and start char are A01/A00 for student_number
*   (DOne) add bounds for all grades need to be between 0.0 and 100.0
*   (DOne) replace number_of_student with the size function
*   (Done) Move the functions and structs into a class
*   (Done) add delete_student() fnc
*        
*   add load_Class() fnc
*       store the vector stored in the file
*   add save_Class() fnc
*       store the vector type CStudent
* 
*/

using namespace std;
int main()
{
    CCourse new_Course_Class;
    //Generated the first empty class

    string command; //var used to track the key press and decide what function to run 

    while(1)
    {
        new_Course_Class.print_Menu(); //Prints menu showing the commands
        cout << "Choose commands: ";
        cin >> command;//waits for input command

        if (regex_match(command, regex(COMMAND_MASK_REGEX) ) ) // rejects any unwanted characters for command prompt
        {
            if (regex_match(command, regex("[aA]"))) //add student
            {
                new_Course_Class.add_Student();
            }//add student


            else if (regex_match(command, regex("[eE]"))) // edit student
            {
                int temp_student_num;
                cout << " Student to Edit: ";
                cin >> temp_student_num;
                if (temp_student_num >= new_Course_Class.get_Size_of_Vector())//check to see if a valid student is selected
                {
                    cout << " Student does not exist\n\n";
                }
                else
                {
                    new_Course_Class.edit_Student(temp_student_num);
                }
            }// edit student

            else if (regex_match(command, regex("[dD]"))) // delete student
            {
                int temp;
                cout << " Student to delete: ";
                cin >> temp;

                if (temp >= new_Course_Class.get_Size_of_Vector())
                {
                    cout << " Student does not exist\n\n";
                }
                else
                {
                    new_Course_Class.delete_student(temp);
                }                
            }//delete student


            else if (regex_match(command, regex("[pP]")))// Print Grades
            {
                new_Course_Class.print_Grades();//print each of the students stored in the 'new_student' 
                cout << "\n";
            }// Print Grades

            else if (regex_match(command, regex("[sS]")))// Save student vector
            {
                new_Course_Class.save_Class();
            }

            else if (regex_match(command, regex("[lL]")))// Load Student Vector
            {
                new_Course_Class.load_Class();
            }

            else if (regex_match(command, regex("[qQ]"))) // Quit Application
            {
                return 0;
            }//quit
        }        
        else
        {
            cout << "\tNot a recognized command\n\n";
        }

    }//while(1)
}