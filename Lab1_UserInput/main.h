#pragma once
#ifndef MAIN_H
#define MAIN_H

#define CLASS_SIZE 100  // size of the class used to generate the struct of students
#define ZERO_STUDENT 0  // 

struct student_Info {
    char    student_Num[9]; //
    float   lab_Grade;
    float   quiz_Grade;
    float   midterm_Grade;
    float   finalExam_Grade;
};

void add_Student(student_Info &new_Student);
void edit_Student(student_Info &new_Student);
void print_Grades(student_Info &new_Student, int current_student);
void print_Menu();
float final_grade(student_Info& new_Student);

#endif // !MAIN_H


