#include <iostream>
#include "main.h"

void add_Student(student_Info &new_Student)
{
	std::cout << "\nAdding Student\n";

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
	std::cout << " ELEX4618 Grade System, by STUDENT NAME  \n";
	std::cout << "*****************************************\n";
	std::cout << "(A)dd student\n";
	std::cout << "(E)dit student\n";
	std::cout << "(P)rint grade\n";
	std::cout << "(Q)uit\n";
}//void print_Menu()

void print_Grades(student_Info &new_Student, int current_student)
{
	std::cout << " #	Student	Lab	Quiz	Midterm		Final Exam	Final Grade\n";
	std::cout << " " << current_student;
	std::cout << "	"<<  new_Student.student_Num;
	std::cout << "	" << new_Student.lab_Grade;
	std::cout << "	" << new_Student.quiz_Grade;
	std::cout << "	" << new_Student.midterm_Grade;
	std::cout << "		" << new_Student.finalExam_Grade;
	std::cout << "		" << final_grade(new_Student) << "\n\n";
}//void print_Grades(student_Info &new_Student, uint8_t current_student)

float final_grade(student_Info& new_Student)
{
	float quiz			= new_Student.quiz_Grade;       //10%
	float final_mark	= new_Student.finalExam_Grade;  //30%
	float lab			= new_Student.lab_Grade;		//40%
	float midterm		= new_Student.midterm_Grade;    //20%

	float overall = (quiz * 1 / 10 + final_mark * 3 / 10 + lab * 4 / 10 + midterm * 2 / 10);
	return overall;
}
