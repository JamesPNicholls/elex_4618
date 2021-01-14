#pragma once
#ifndef MAIN_H
#define MAIN_H

#define LAB_COEFF       4
#define FINAL_COEFF     3
#define QUIZ_COEFF      1
#define MIDTERM_COEFF   2
#define WEIGHT_DIVISOR  10

#define GRADE_MASK_REGEX        "[0-9]+[.]?[0-9]*"
#define COMMAND_MASK_REGEX      "[a-zA-Z]"
#define STUDENT_NUM_MASK_REGEX  "[aA][0][0-1][0-9]{6}" 

class CStudent
{
public:
    std::string     student_Num;
    float           lab_Grade;
    float           quiz_Grade;
    float           midterm_Grade;
    float           finalExam_Grade;
};

class CCourse
{
public:
    void add_Student();
    void edit_Student(int student_Index);
    void delete_student(int student_Index);

    void print_Grades();
    void print_Menu();

    void load_Class();
    void save_Class();

    int get_Size_of_Vector();

private:
    std::vector <CStudent> student_Class_Vector;
    float final_grade(uint8_t vector_Index);
    bool is_Grade_Valid(std::string current_Grade_Value);
    bool is_StudentNum_Valid(std::string student_Num);
};


#endif // !MAIN_H


