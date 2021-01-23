#pragma once

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

