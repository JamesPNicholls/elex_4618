#include <iostream>
#include <iomanip>
#include <string.h>
#include <regex>
#include "main.h"

void add_Student(student_Info &new_Student)
{
	std::string current_Grade_Type; //decided to make this a string because it made all of the error checking a lot easier 
	
	std::cout << "\nAdding Student\n";

	std::cout << " Student Number: ";	
	std::cin >> new_Student.student_Num;

	//passes in the new student number and loops until a valid student number is submitted
	while (!is_StudentNum_Valid(new_Student.student_Num))
	{
		std::cout << "\tInvalid Student Number Please Try again: ";
		std::cin >> new_Student.student_Num;
		std::cin.clear();
		std::cin.ignore(100, '\n');
	}

	std::cout << " Lab Grade: ";
	std::cin >> current_Grade_Type;
	while (!verify_Grade(current_Grade_Type))// Loops until a valid grade is entered
	{
		std::cout << "\tInvalid Grade Please Try again: ";
		std::cin  >> current_Grade_Type;
	}
	new_Student.lab_Grade = std::stof(current_Grade_Type);//sets the input to the grade in the struct

	std::cout << " Quiz Grade: ";
	std::cin >> current_Grade_Type;	
	while (!verify_Grade(current_Grade_Type))
	{
		std::cout << "\tInvalid Grade Please Try again: ";
		std::cin >> current_Grade_Type;
	}
	new_Student.quiz_Grade = std::stof(current_Grade_Type);


	std::cout << " Midterm Grade: ";
	std::cin >> current_Grade_Type;
	while (!verify_Grade(current_Grade_Type))
	{
		std::cout << "\tInvalid Grade Please Try again: ";
		std::cin >> current_Grade_Type;
	}
	new_Student.midterm_Grade = std::stof(current_Grade_Type);


	std::cout << " Final Exam Grade: ";
	std::cin >> current_Grade_Type;
	while (!verify_Grade(current_Grade_Type))
	{
		std::cout << "\tInvalid Grade Please Try again: ";
		std::cin >> current_Grade_Type;
	}
	new_Student.finalExam_Grade = std::stof(current_Grade_Type);
	std::cout << "\n";

}//void add_Student(student_Info &new_Student)

void edit_Student(student_Info &new_Student)
{
	std::cout << "\nEditing Student\n";

	std::cout << " Student Number: ";
	std::cin  >> new_Student.student_Num;


	std::cout << " Lab Grade: ";
	std::cin  >> new_Student.lab_Grade;


	std::cout << " Quiz Grade: ";
	std::cin  >> new_Student.quiz_Grade;


	std::cout << " Midterm Grade: ";
	std::cin  >> new_Student.midterm_Grade;


	std::cout << " Final Exam Grade: ";
	std::cin  >> new_Student.finalExam_Grade;
	std::cout << "\n";

}//void edit_Student(student_Info &new_Student)

void print_Menu()
{
	std::cout << "*****************************************\n";
	std::cout << " ELEX4618 Grade System, by James Nicholls  \n";
	std::cout << "*****************************************\n";
	std::cout << "(A)dd student\n";
	std::cout << "(E)dit student\n";
	std::cout << "(P)rint grade\n";
	std::cout << "(Q)uit\n";
}//void print_Menu()

void print_Grades(student_Info &new_Student, int current_student)
{
	//Set cout to Fixed mode
	std::cout << std::fixed;

	std::cout << " # Student\tLab\tQuiz\tMidterm\t\tFinal Exam\tFinal Grade\n";
	std::cout << " " << current_student;
	std::cout << " " <<  new_Student.student_Num;
	std::cout << "\t" << std::setprecision(1) << new_Student.lab_Grade;
	std::cout << "\t" << std::setprecision(1) << new_Student.quiz_Grade;
	std::cout << "\t" << std::setprecision(1) << new_Student.midterm_Grade;
	std::cout << "\t\t" << std::setprecision(1) << new_Student.finalExam_Grade;
	std::cout << "\t\t" << std::setprecision(1) << final_grade(new_Student) << "\n\n";
}//void print_Grades(student_Info &new_Student, uint8_t current_student)

float final_grade(student_Info& new_Student)
{
	float quiz			= new_Student.quiz_Grade;       //10%
	float final_mark	= new_Student.finalExam_Grade;  //30%
	float lab			= new_Student.lab_Grade;		//40%
	float midterm		= new_Student.midterm_Grade;    //20%

	float overall = (quiz * QUIZ_COEFF + final_mark * FINAL_COEFF + lab * LAB_COEFF + midterm * MIDTERM_COEFF)/WEIGHT_DIVISOR; //Takes the weighted average of the grades
	return overall;
}//float final_grade(student_Info& new_Student)


//I could have used regex for this function as well but i already had it working with the string manips
bool is_StudentNum_Valid(std::string student_Num)
{
	bool is_student_Num_Good = false; //assumes the number is bad
								
	if (student_Num.size() != 9)
	{
		return is_student_Num_Good;
	}

	std::string first_Three_Char = student_Num.substr(0, 2);//takes the first 3 char of student_Num
	
	//checks to see if the first 3 characters of student_Num are A01, A00, a01 or a00
	if (first_Three_Char.compare("A01") || first_Three_Char.compare("A00") || first_Three_Char.compare("a00") || first_Three_Char.compare("a01"))
	{
		is_student_Num_Good = true;
	}

	return is_student_Num_Good;

}//bool is_StudentNum_Valid(std::string student_Num)

bool verify_Grade(std::string current_Grade_Value)
{	
	bool grade_is_valid = false;

	std::string regex_Grade = "[0-1]*[0-9]*[0-9][.]*[0-9]*"; //there is probably a more concise way to write this
	float grade_As_Float = std::stof(current_Grade_Value);//converts the sting to a float for making sure the number is in bounds

	if (std::regex_match(current_Grade_Value, std::regex(regex_Grade)))// Gate to reject all invalid characters
	{

		if (grade_As_Float > 100.0 || grade_As_Float < 0.0)//Checks to see if the grade is in bounds
		{
			grade_is_valid = false;
		}
		else
		{
			grade_is_valid = true; // only returns true if the input has no invalid characters and is between 0 and 100
		}
	}
	else
	{
		grade_is_valid = false;
	}

	return grade_is_valid;
}
