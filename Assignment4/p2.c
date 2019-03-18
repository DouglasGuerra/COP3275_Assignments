/*
* This file implements a system to keep track of students, courses and enrollments
* Assignemnt pdf has more detail on the system to implement
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_USER_INPUT 25
#define MAX_STRING_LENGTH 100
#define MAX_STUDENTS 100

typedef struct{
    char firstName[MAX_STRING_LENGTH];
    char lastName[MAX_STRING_LENGTH];
    int gpa;
} Student_t;

typedef struct{
    char name[MAX_STRING_LENGTH];
    Student_t studentsEnrolled[MAX_STUDENTS];
    float averageGPA;
    int numOfStudents;
} Course_t;

/******************************************************************
* Helper functions
******************************************************************/
void Clear_String(char *string, int size){
    int i;
    for(i = 0; i < size; i++) string[i] = 0;
}

void Clear_Strings(int arrSize, int stringLength, char arr[arrSize][stringLength]){
    int i;
    for(i = 0; i < arrSize; i++) Clear_String(arr[i], stringLength);
}

/******************************************************************
* Functions to handle students in the system
******************************************************************/
void Init_StudentsInSystem(Student_t students[], int numOfStudents){
    int i;
    for(i = 0; i < numOfStudents; i++){
        Student_t student;
        Clear_String(student.firstName, MAX_STRING_LENGTH);
        Clear_String(student.lastName, MAX_STRING_LENGTH);
        students[i] = student;
    }
}

void Load_StudentsIntoSystem(Student_t students[], int numOfStudents){
    int i;
    for(i = 0; i < numOfStudents; i++){
        char tempChar;
        int foundSpace = false;
        scanf(" %c", &tempChar);
        while(tempChar != '\n'){
            if(tempChar == ' ') foundSpace = true;
            else if(!foundSpace) sprintf(students[i].firstName, "%s%c", students[i].firstName, tempChar);
            else sprintf(students[i].lastName, "%s%c", students[i].lastName, tempChar);
            scanf("%c", &tempChar);
        }
    }
}

void PrintStudents(Student_t students[], int numOfStudents){
    printf("\n-------------------- printing students ------------------\n");
    int i;
    for(i = 0; i < numOfStudents; i++){
        printf("%s, %s\n", students[i].firstName, students[i].lastName);
    }
}

/******************************************************************
* Functions to handle courses in the system
******************************************************************/
void Init_CoursesInSystem(Course_t courses[], int numOfCourses){
    int index;
    for(index = 0; index < numOfCourses; index++){
        Course_t course;
        Init_StudentsInSystem(course.studentsEnrolled, MAX_STUDENTS);
        Clear_String(course.name, MAX_STRING_LENGTH);
        course.averageGPA = 0;
        course.numOfStudents = 0;
        courses[index] = course;
    }
}

void Load_CoursesIntoSystem(Course_t courses[], int numOfCourses){
    int i;
    for(i = 0; i < numOfCourses; i++){
        char tempChar;
        scanf(" %c", &tempChar);
        while(tempChar != '\n'){
            sprintf(courses[i].name, "%s%c", courses[i].name, tempChar);
            scanf("%c", &tempChar);
        }
    }
}

int Get_CourseIndex(Course_t courses[], const char *course, int numOfCourses){
    int i;
    for(i = 0; i < numOfCourses; i++){
        if(strcmp(courses[i].name, course) == 0) return i;
    }
    return -1;
}

void Add_StudentToCourse(Course_t courses[], Student_t student, const char *course, int numOfCourses){
    int courseIndex = Get_CourseIndex(courses, course, numOfCourses) != -1;
    if(courseIndex != -1){
        Course_t course = courses[courseIndex];
        course.studentsEnrolled[course.numOfStudents] = student;
        course.numOfStudents++;
    }
}

void PrintCourses(Course_t courses[], int numOfCourses){
    printf("\n---------------- printing course --------------------\n");
    int i;
    for(i = 0; i < numOfCourses; i++){
        printf("%s\t%f\n", courses[i].name, courses[i].averageGPA);
        printf("\nstudents: \n");
        int j;
        for(j = 0; j < courses[i].numOfStudents; j++){
            printf("%s\n", courses[i].studentsEnrolled[j].firstName);
        }
    }
}

/*****************************************************************
* Functions to handle menu entries
******************************************************************/
void ReadInUserInputIntoArray(int arrSize, int stringLength, char arr[arrSize][stringLength]){
    int storeIndex = 0;
    char tempChar;
    char word[MAX_STRING_LENGTH];

    Clear_String(word, MAX_STRING_LENGTH);

    scanf(" %c", &tempChar);
    while(tempChar != '\n'){
        if(tempChar == ' '){
            sprintf(arr[storeIndex], "%s", word);
            storeIndex++;
            Clear_String(word, MAX_STRING_LENGTH);
        }
        else{
            sprintf(word, "%s%c", word, tempChar);
        }
        scanf("%c", &tempChar);
    }
    sprintf(arr[storeIndex], "%s", word);
}

/******************************************************************
* Main code
******************************************************************/
int main(){

    int numStudents, numCourses;
    scanf("%d", &numStudents);
    scanf("%d", &numCourses);

    // Loading students into the system
    Student_t students[numStudents];
    Init_StudentsInSystem(students, numStudents);
    Load_StudentsIntoSystem(students, numStudents);
    PrintStudents(students, numStudents);

    // Loading courses into the system
    Course_t courses[numCourses];
    Init_CoursesInSystem(courses, numCourses);
    Load_CoursesIntoSystem(courses, numCourses);
    PrintCourses(courses, numCourses);

    // Menu
    char userInput[MAX_USER_INPUT][MAX_STRING_LENGTH];
    Clear_Strings(MAX_USER_INPUT, MAX_STRING_LENGTH, userInput);

    while(1){
        ReadInUserInputIntoArray(MAX_USER_INPUT, MAX_STRING_LENGTH,userInput);
        char *command = userInput[0];

        if(strcmp(command, "enroll") == 0) printf("enroll\n");
        if(strcmp(command, "unenroll") == 0) printf("unenroll\n");
        if(strcmp(command, "grade") == 0) printf("grade\n");
        if(strcmp(command, "ave") == 0) printf("ave\n");
        if(strcmp(command, "gpa") == 0) printf("gpa\n");
        if(strcmp(command, "count") == 0) printf("count\n");
        if(strcmp(command, "topstudent") == 0) printf("topstudent\n");
        if(strcmp(command, "findmutual") == 0) printf("findmutual\n");
        if(strcmp(command, "listcourses") == 0) printf("listcourses\n");
        if(strcmp(command, "findfirstnames") == 0) printf("firstnames\n");
        if(strcmp(command, "quit") == 0) break;
    }

}
