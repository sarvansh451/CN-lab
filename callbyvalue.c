#include <stdio.h>
#include <string.h>

struct dob {
    int day;
    int month;
    int year;
};

struct student_info {
    int roll_no;
    char name[50];
    float CGPA;
    struct dob age;
};

// Function to print student info using call-by-value
void printStudentInfoByValue(struct student_info student) {
    printf("\nUsing call-by-value:\n");
    printf("Roll No: %d\n", student.roll_no);
    printf("Name: %s\n", student.name);
    printf("CGPA: %.2f\n", student.CGPA);
    printf("DOB: %02d-%02d-%04d\n", student.age.day, student.age.month, student.age.year);
}

// Function to print student info using call-by-address
void printStudentInfoByAddress(struct student_info *student) {
    printf("\nUsing call-by-address:\n");
    printf("Roll No: %d\n", student->roll_no);
    printf("Name: %s\n", student->name);
    printf("CGPA: %.2f\n", student->CGPA);
    printf("DOB: %02d-%02d-%04d\n", student->age.day, student->age.month, student->age.year);
}

int main() {
    struct student_info student;

    // Assign values to the structure members
    student.roll_no = 1;
    strcpy(student.name, "John Doe");
    student.CGPA = 3.75;
    student.age.day = 15;
    student.age.month = 8;
    student.age.year = 2000;

    // Print using call-by-value
    printStudentInfoByValue(student);

    // Print using call-by-address
    printStudentInfoByAddress(&student);

    return 0;
}

