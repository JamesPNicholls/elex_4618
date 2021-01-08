#pragma once
#ifndef MAIN_H
#define MAIN_H

#define CLASS_SIZE 100  // size of the class used to generate the struct of students
#define ZERO_STUDENT 0  // 

#define LAB_COEFF       4
#define FINAL_COEFF     3
#define QUIZ_COEFF      1
#define MIDTERM_COEFF   2
#define WEIGHT_DIVISOR  10

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


