#pragma once
#ifndef MAIN_H
#define MAIN_H

#define CLASS_SIZE 100  // size of the class used to generate the struct of students

#define LAB_COEFF       4
#define FINAL_COEFF     3
#define QUIZ_COEFF      1
#define MIDTERM_COEFF   2
#define WEIGHT_DIVISOR  10

#define GRADE_MASK_REGEX        "[0-9]+[.]?[0-9]*"
#define COMMAND_MASK_REGEX      "[a-zA-Z]"
#define STUDENT_NUM_MASK_REGEX  "[aA][0][0-1][0-9]{6}" 

struct student_Info {
    std::string     student_Num;
    float           lab_Grade;
    float           quiz_Grade;
    float           midterm_Grade;
    float           finalExam_Grade;
};
	
class CStudent
{
public:
    void add_Student();
    void edit_Student(int student_Index);

    void print_Grades();
    void print_Menu();

    float final_grade(uint8_t vector_Index);

    bool verify_Grade(std::string current_Grade_Value);
    bool is_StudentNum_Valid(std::string student_Num);

private:
    std::vector <student_Info> student_Vector;
};

//void delete_student();
//void load_Class()
//void save_Class()
#endif // !MAIN_H


