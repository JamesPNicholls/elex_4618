#include <iostream>
#include "main.h"

void add_Student(student_Info &new_Student)
{
	std::cout << "\nAdding Student\n";

	std::cout << " Student Number: ";
	std::cin >> new_Student.student_Num;

	std::cout << " Lab Grade: ";
	std::cin >> new_Student.lab_Grade;

	std::cout << " Quiz Grade: ";
	std::cin >> new_Student.quiz_Grade;

	std::cout << " Midterm Grade: ";
	std::cin >> new_Student.midterm_Grade;

	std::cout << " Final Exam Grade: ";
	std::cin >> new_Student.finalExam_Grade;
	std::cout << "\n";
}
void edit_Student()
{

}
void print_Menu()
{
	std::cout << "*****************************************\n";
	std::cout << " ELEX4618 Grade System, by STUDENT NAME  \n";
	std::cout << "*****************************************\n";
	std::cout << "(A)dd student\n";
	std::cout << "(E)dit student\n";
	std::cout << "(P)rint grade\n";
	std::cout << "(Q)uit\n";
}
void print_Grades()
{

}