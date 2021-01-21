#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <regex>
#include "main.h"
#include "CStudent.h"
#include "CCourse.h"

using namespace std;

void CCourse::add_Student()
{
	CStudent student_Info_Class; //generates the new class of type CStudent
	string current_Grade_Type; 
	
	cout << "\nAdding Student\n";

	//-------------Student Number-------------------
	cout << " Student Number: ";
	cin	 >> student_Info_Class.student_Num;

	while ( is_StudentNum_Valid(student_Info_Class.student_Num) == false)
	{
		cout << "\tInvalid Student Number Please Try again: ";
		cin >> student_Info_Class.student_Num;
	}

	//----------Lab Grade ---------------------------
	cout << " Lab Grade: ";
	cin  >> current_Grade_Type;

	while (!is_Grade_Valid(current_Grade_Type))// Loops until a valid grade is entered
	{
		cout << "\tInvalid Grade Please Try again: ";
		cin >> current_Grade_Type;
	}
	student_Info_Class.lab_Grade = stof(current_Grade_Type);//sets the input to the grade in the struct

	//----------Quiz Grade ---------------------------
	cout << " Quiz Grade: ";
	cin >> current_Grade_Type;

	while (!is_Grade_Valid(current_Grade_Type))
	{
		cout << "\tInvalid Grade Please Try again: ";
		cin >> current_Grade_Type;
	}
	student_Info_Class.quiz_Grade = stof(current_Grade_Type);

	//----------Midterm Grade ---------------------------
	cout << " Midterm Grade: ";
	cin >> current_Grade_Type;

	while (!is_Grade_Valid(current_Grade_Type))
	{
		cout << "\tInvalid Grade Please Try again: ";
		cin >> current_Grade_Type;
	}
	student_Info_Class.midterm_Grade = stof(current_Grade_Type);

	//----------Final Exam Grade ---------------------------
	cout << " Final Exam Grade: ";
	cin >> current_Grade_Type;

	while (!is_Grade_Valid(current_Grade_Type))
	{
		cout << "\tInvalid Grade Please Try again: ";
		cin >> current_Grade_Type;
	}
	student_Info_Class.finalExam_Grade = stof(current_Grade_Type);
	cout << "\n";

	student_Class_Vector.push_back(student_Info_Class); //stores the temp CClass in the vector
}//void add_Student(student_Info &new_Student)

void CCourse::edit_Student(int student_Index)
{
	string current_Grade_Type; //decided to make this a string because it made all of the error checking a lot easier 

	cout << "Editing Student\n";

	//-------------Student Number-------------------
	cout << " Student Number: ";
	cin >> student_Class_Vector.at(student_Index).student_Num;

	while (!is_StudentNum_Valid(student_Class_Vector.at(student_Index).student_Num))
	{
		cout << "\tInvalid Student Number Please Try again: ";
		cin >> student_Class_Vector.at(student_Index).student_Num;
	}

	//----------Lab Grade ---------------------------
	cout << " Lab Grade: ";
	cin >> current_Grade_Type;

	while (!is_Grade_Valid(current_Grade_Type))// Loops until a valid grade is entered
	{
		cout << "\tInvalid Grade Please Try again: ";
		cin >> current_Grade_Type;
	}
	student_Class_Vector.at(student_Index).lab_Grade = stof(current_Grade_Type);//sets the input to the grade in the struct

	//----------Quiz Grade ---------------------------
	cout << " Quiz Grade: ";
	cin >> current_Grade_Type;

	while (!is_Grade_Valid(current_Grade_Type))
	{
		cout << "\tInvalid Grade Please Try again: ";
		cin >> current_Grade_Type;
	}
	student_Class_Vector.at(student_Index).quiz_Grade = stof(current_Grade_Type);

	//----------Midterm Grade ---------------------------
	cout << " Midterm Grade: ";
	cin >> current_Grade_Type;

	while (!is_Grade_Valid(current_Grade_Type))
	{
		cout << "\tInvalid Grade Please Try again: ";
		cin >> current_Grade_Type;
	}
	student_Class_Vector.at(student_Index).midterm_Grade = stof(current_Grade_Type);

	//----------Final Exam Grade ---------------------------
	cout << " Final Exam Grade: ";
	cin >> current_Grade_Type;

	while (!is_Grade_Valid(current_Grade_Type))
	{
		cout << "\tInvalid Grade Please Try again: ";
		cin >> current_Grade_Type;
	}
	student_Class_Vector.at(student_Index).finalExam_Grade = stof(current_Grade_Type);
	cout << "\n";

}//void edit_Student(student_Info &new_Student)

void CCourse::delete_student(int student_Index)
{
	student_Class_Vector.erase(student_Class_Vector.begin() + student_Index);	
}

void CCourse::print_Menu()
{
	cout << "************************************************\n";
	cout << " ELEX4618 Grade System(pt.2), by James Nicholls \n";
	cout << "************************************************\n";
	cout << "(A)dd student\n";
	cout << "(E)dit student\n";
	cout << "(D)elete student\n";
	cout << "(P)rint grade\n";
	cout << "(Q)uit\n";
	cout << "(S)ave Class\n";
	cout << "(L)oad Class\n";
}//void print_Menu()

void CCourse::print_Grades()
{
	cout << fixed;
	for (int vector_Index = 0; vector_Index < student_Class_Vector.size(); vector_Index++)
	{	
		cout << " # Student\tLab\tQuiz\tMidterm\t\tFinal Exam\tFinal Grade\n";
		cout << " "		<<							vector_Index;
		cout << " "		<<							student_Class_Vector[vector_Index].student_Num;
		cout << "\t"	<<		setprecision(1) <<	student_Class_Vector[vector_Index].lab_Grade;
		cout << "\t"	<<		setprecision(1) <<	student_Class_Vector[vector_Index].quiz_Grade;
		cout << "\t"	<<		setprecision(1) <<	student_Class_Vector[vector_Index].midterm_Grade;
		cout << "\t\t"	<<		setprecision(1) <<	student_Class_Vector[vector_Index].finalExam_Grade;
		cout << "\t\t"	<<		setprecision(1) <<	final_grade(vector_Index) << "\n\n";
	}

}//void print_Grades(student_Info &new_Student, uint8_t current_student)

// Like all great developers, Im not entirely sure how this works but it does
// Shamelessly stolen from:  https://stackoverflow.com/questions/28492517/write-and-load-vector-of-structs-in-a-binary-file-c
// For both load_Class() and save_Class()
void CCourse::load_Class()
{
	string file_Name;
	cout << "Class_Name: ####\n";
	cout << "> ";
	cin >> file_Name;
	file_Name = "./" + file_Name;
	


	ifstream in_Stream(file_Name, ios::out );
	
	if (in_Stream.is_open())
	{
		string class_Size;
		string temp;
		CStudent temp_Class;
		
		student_Class_Vector.clear();//out with the old in with the new
		
		getline(in_Stream, class_Size);
		for (int i = 0; i < stof(class_Size); i++)
		{
			getline(in_Stream, temp);
			temp_Class.student_Num = temp;

			getline(in_Stream, temp);
			temp_Class.finalExam_Grade = stof(temp);

			getline(in_Stream, temp);
			temp_Class.lab_Grade = stof(temp);

			getline(in_Stream, temp);
			temp_Class.midterm_Grade = stof(temp);

			getline(in_Stream, temp);
			temp_Class.quiz_Grade = stof(temp);
			
			student_Class_Vector.push_back(temp_Class);
		} 
	}
	else
	{
		cout << "  File not found...\n\n";
	}
}

void CCourse::save_Class()
{	
	string file_Name;
	cout << "Class Name: ####.txt\n";
	cout << "> ";
	cin >> file_Name;
	file_Name = "./" + file_Name;
	ofstream out_Stream(file_Name, std::ios::out);

	if( out_Stream.is_open())
	{
		out_Stream << student_Class_Vector.size() << "\n"; //stores the for interation use in load_Class();
		for (int i = 0; i < student_Class_Vector.size(); i++)
		{			
			out_Stream << student_Class_Vector.at(i).student_Num		<< "\n";
			out_Stream << student_Class_Vector.at(i).finalExam_Grade	<< "\n";
			out_Stream << student_Class_Vector.at(i).finalExam_Grade	<< "\n";
			out_Stream << student_Class_Vector.at(i).midterm_Grade		<< "\n";
			out_Stream << student_Class_Vector.at(i).quiz_Grade			<< "\n";
		}
	}
	else
	{
		cout << "  File not found...\n\n";
	}
}//void CCourse::save_Class()

int CCourse::get_Size_of_Vector()
{
	return student_Class_Vector.size();
}//int CCourse::get_Size_of_Vector()

float CCourse::final_grade(uint8_t vector_Index)
{
	float quiz			= student_Class_Vector[vector_Index].quiz_Grade;		//10%
	float final_mark	= student_Class_Vector[vector_Index].finalExam_Grade;   //30%
	float lab			= student_Class_Vector[vector_Index].lab_Grade;			//40%
	float midterm		= student_Class_Vector[vector_Index].midterm_Grade;		//20%

	float overall = (quiz * QUIZ_COEFF + final_mark * FINAL_COEFF + lab * LAB_COEFF + midterm * MIDTERM_COEFF) / WEIGHT_DIVISOR; //Takes the weighted average of the grades
	return overall;
}//float final_grade(student_Info& new_Student)

bool CCourse::is_StudentNum_Valid(string student_Num)
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

bool CCourse::is_Grade_Valid(string current_Grade_Value)
{
	bool grade_is_valid = false;

	if (regex_match(current_Grade_Value, regex(GRADE_MASK_REGEX)))// Gate to reject all invalid characters
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
}//bool is_Grade_Valid(string current_Grade_Value)
