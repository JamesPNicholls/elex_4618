#include <iostream>
#include <iomanip>
#include <string.h>
#include <regex>
#include "main.h"
using namespace std;

//------------CStudent Member Functions---------------
void CStudent::add_Student()
{
	student_Info student_Info_Struct; //generates the new struct
	string current_Grade_Type; //decided to make this a string because it made all of the error checking a lot easier 
	
	cout << "\nAdding Student\n";

	//-------------Student Number-------------------
	cout << " Student Number: ";
	cin >> student_Info_Struct.student_Num;
	while (!is_StudentNum_Valid(student_Info_Struct.student_Num))
	{
		cout << "\tInvalid Student Number Please Try again: ";
		cin >> student_Info_Struct.student_Num;
	}

	//----------Lab Grade ---------------------------
	cout << " Lab Grade: ";
	cin >> current_Grade_Type;
	while (!verify_Grade(current_Grade_Type))// Loops until a valid grade is entered
	{
		cout << "\tInvalid Grade Please Try again: ";
		cin >> current_Grade_Type;
	}
	student_Info_Struct.lab_Grade = stof(current_Grade_Type);//sets the input to the grade in the struct

	//----------Quiz Grade ---------------------------
	cout << " Quiz Grade: ";
	cin >> current_Grade_Type;
	while (!verify_Grade(current_Grade_Type))
	{
		cout << "\tInvalid Grade Please Try again: ";
		cin >> current_Grade_Type;
	}
	student_Info_Struct.quiz_Grade = stof(current_Grade_Type);

	//----------Midterm Grade ---------------------------
	cout << " Midterm Grade: ";
	cin >> current_Grade_Type;
	while (!verify_Grade(current_Grade_Type))
	{
		cout << "\tInvalid Grade Please Try again: ";
		cin >> current_Grade_Type;
	}
	student_Info_Struct.midterm_Grade = stof(current_Grade_Type);

	//----------Final Exam Grade ---------------------------
	cout << " Final Exam Grade: ";
	cin >> current_Grade_Type;
	while (!verify_Grade(current_Grade_Type))
	{
		cout << "\tInvalid Grade Please Try again: ";
		cin >> current_Grade_Type;
	}
	student_Info_Struct.finalExam_Grade = stof(current_Grade_Type);
	cout << "\n";

	student_Vector.push_back(student_Info_Struct); //Places the populated struct at the end of the vector
}//void add_Student(student_Info &new_Student)

void CStudent::edit_Student(int student_Index)
{
	string current_Grade_Type; //decided to make this a string because it made all of the error checking a lot easier 

	cout << "Editing Student\n";

	//-------------Student Number-------------------
	cout << " Student Number: ";
	cin >> student_Vector.at(student_Index).student_Num;
	while (!is_StudentNum_Valid(student_Vector.at(student_Index).student_Num))
	{
		cout << "\tInvalid Student Number Please Try again: ";
		cin >> student_Vector.at(student_Index).student_Num;
	}

	//----------Lab Grade ---------------------------
	cout << " Lab Grade: ";
	cin >> current_Grade_Type;
	while (!verify_Grade(current_Grade_Type))// Loops until a valid grade is entered
	{
		cout << "\tInvalid Grade Please Try again: ";
		cin >> current_Grade_Type;
	}
	student_Vector.at(student_Index).lab_Grade = stof(current_Grade_Type);//sets the input to the grade in the struct

	//----------Quiz Grade ---------------------------
	cout << " Quiz Grade: ";
	cin >> current_Grade_Type;
	while (!verify_Grade(current_Grade_Type))
	{
		cout << "\tInvalid Grade Please Try again: ";
		cin >> current_Grade_Type;
	}
	student_Vector.at(student_Index).quiz_Grade = stof(current_Grade_Type);

	//----------Midterm Grade ---------------------------
	cout << " Midterm Grade: ";
	cin >> current_Grade_Type;
	while (!verify_Grade(current_Grade_Type))
	{
		cout << "\tInvalid Grade Please Try again: ";
		cin >> current_Grade_Type;
	}
	student_Vector.at(student_Index).midterm_Grade = stof(current_Grade_Type);

	//----------Final Exam Grade ---------------------------
	cout << " Final Exam Grade: ";
	cin >> current_Grade_Type;
	while (!verify_Grade(current_Grade_Type))
	{
		cout << "\tInvalid Grade Please Try again: ";
		cin >> current_Grade_Type;
	}
	student_Vector.at(student_Index).finalExam_Grade = stof(current_Grade_Type);
	cout << "\n";

}//void edit_Student(student_Info &new_Student)

void CStudent::delete_student()
{

}

void CStudent::print_Menu()
{
	cout << "************************************************\n";
	cout << " ELEX4618 Grade System(pt.2), by James Nicholls \n";
	cout << "************************************************\n";
	cout << "(A)dd student\n";
	cout << "(E)dit student\n";
	cout << "(P)rint grade\n";
	cout << "(Q)uit\n";
}//void print_Menu()

void CStudent::print_Grades()
{
	cout << fixed;
	for (int vector_Index = 0; vector_Index < student_Vector.size(); vector_Index++)
	{	
		cout << " # Student\tLab\tQuiz\tMidterm\t\tFinal Exam\tFinal Grade\n";
		cout << " "		<<							vector_Index + 1;
		cout << " "		<<							student_Vector[vector_Index].student_Num;
		cout << "\t"	<<		setprecision(1) <<	student_Vector[vector_Index].lab_Grade;
		cout << "\t"	<<		setprecision(1) <<	student_Vector[vector_Index].quiz_Grade;
		cout << "\t"	<<		setprecision(1) <<	student_Vector[vector_Index].midterm_Grade;
		cout << "\t\t"	<<		setprecision(1) <<	student_Vector[vector_Index].finalExam_Grade;
		cout << "\t\t"	<<		setprecision(1) <<	final_grade(vector_Index) << "\n\n";
	}

}//void print_Grades(student_Info &new_Student, uint8_t current_student)

float CStudent::final_grade(uint8_t vector_Index)
{
	float quiz			= student_Vector[vector_Index].quiz_Grade;       //10%
	float final_mark	= student_Vector[vector_Index].finalExam_Grade;  //30%
	float lab			= student_Vector[vector_Index].lab_Grade;		 //40%
	float midterm		= student_Vector[vector_Index].midterm_Grade;    //20%

	float overall = (quiz * QUIZ_COEFF + final_mark * FINAL_COEFF + lab * LAB_COEFF + midterm * MIDTERM_COEFF)/WEIGHT_DIVISOR; //Takes the weighted average of the grades
	return overall;
}//float final_grade(student_Info& new_Student)

bool CStudent::is_StudentNum_Valid(string student_Num)
{
	bool is_student_Num_Good = false; //assumes the number is bad
								
	if (student_Num.size() != 9) // returns false if the number is the wrong size
	{
		is_student_Num_Good = false;
	}
	else
	{
		if (regex_match(student_Num, regex(STUDENT_NUM_MASK_REGEX)))
		{
			is_student_Num_Good = true;
		}
	}

	return is_student_Num_Good;
}//bool is_StudentNum_Valid(string student_Num)

bool CStudent::verify_Grade(string current_Grade_Value)
{	
	bool grade_is_valid = false;

	string regex_Grade = GRADE_MASK_REGEX; //there is probably a more concise way to write this
	

	if (regex_match(current_Grade_Value, regex(regex_Grade)))// Gate to reject all invalid characters
	{
		float grade_As_Float = stof(current_Grade_Value);//converts the sting to a float for making sure the number is in bounds
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
}//bool verify_Grade(string current_Grade_Value)

//-----------CCourse Member Functions------------------
void CCourse::load_Class()
{

}

void CCourse::save_Class()
{

}