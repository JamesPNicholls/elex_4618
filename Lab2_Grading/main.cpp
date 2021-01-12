// Lab2_Grading.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string.h>
#include <fstream>
#include <regex>
#include "main.h"

/*
* Things to add:
*   (DONE) fix the spacing with /t, thanks aman
*   (DONE) string instead of char array                                            
*   (DONE) add size checking and start char are A01/A00 for student_number
*   (DOne)add bounds for all grades need to be between 0.0 and 100.0
*   replace number_of_student with the size function
*   Move the functions and structs into a class
* 
*   add delete_student() fnc
*       delete a student in a class
*   add load_Class() fnc
*       load grades from a class
*       replace print grades?
*   add save_Class() fnc
*       store the grades of a class into text files7
* 
*   implement load/save/delete with text files
*/

using namespace std;
int number_of_student = 0; //replace with the size function
int main()
{
    struct student_Info new_Students[100];
    string command; //var used to track the key press and decide what function to run
 

    while(1)
    {
        print_Menu(); //Prints menu showing the commands
        cout << "Choose commands: ";
        cin >> command;//waits for input command

        if (regex_match(command, regex(COMMAND_MASK_REGEX) ) )
        {
            if (regex_match(command, regex("[aA]"))) //add student
            {
                add_Student(new_Students[number_of_student]);
                number_of_student++;
            }
            else if (regex_match(command, regex("[eA]"))) // edit student
            {
                int temp_student_num;
                cout << "Student to Edit: ";
                cin >> temp_student_num;
                if (temp_student_num >= number_of_student)//check to see if a valid student is selected
                {
                    cout << "Student does not exist\n\n";
                }
                else
                {
                    edit_Student(new_Students[temp_student_num]);
                }
            }
            else if (regex_match(command, regex("[pP]")))// Print Grades
            {
                for (int i = 0; i < number_of_student; i++)
                {
                    print_Grades(new_Students[i], i);//print each of the students stored in the 'new_student' array
                }
                cout << "\n";
            }
            else if (regex_match(command, regex("[qQ]"))) // Quit Application
            {
                return 0;
            }
        }        
        else
        {
            cout << "\tNot a recognized command\n\n";
        }

    }//while(1)
}