/*
* This file implements a system to keep track of students, courses and enrollments
* Assignemnt pdf has more detail on the system to implement
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_STRING_LENGTH 100
#define MAX_WORDS_IN_STRING 100
#define MAX_STUDENTS_ENROLLED 100

#define STRMCP_EQUAL 0

typedef struct{
    char firstName[MAX_STRING_LENGTH];
    char lastName[MAX_STRING_LENGTH];
    int gpa;
} Student_t;

typedef struct{
    Student_t studentsEnrolled[MAX_STUDENTS_ENROLLED];
    char name[MAX_STRING_LENGTH];
    float averageGPA;
    int numOfStudents;
} Course_t;

typedef struct{
    char data[MAX_STRING_LENGTH];
    int length;
} Word_t;

/***************************************************************************
* I/O functions
****************************************************************************/
int Get_NextLine(char string[]){
    char readInChar;
    int index = 0;

    scanf(" %c", &readInChar);
    while(readInChar != '\n'){
        string[index++] = readInChar;
        scanf("%c", &readInChar);
    }

    return index;
}

int Get_WordsInString(Word_t words[], char string[], int stringLength){
    int wordIndex = 0, wordDataStoreIndex = 0;
    char word[MAX_STRING_LENGTH];

    int i;
    for(i = 0; i < stringLength; i++){
        if(string[i] == ' '){
            words[wordIndex].length = wordDataStoreIndex;
            wordDataStoreIndex = 0;
            wordIndex += 1;
        }
        else{
            words[wordIndex].data[wordDataStoreIndex++] = string[i];
        }
    }
    if(wordDataStoreIndex > 0) words[wordIndex++].length = wordDataStoreIndex;

    return wordIndex;
}

void Print_Words(Word_t words[], int size){
    printf("----------------------- Printing words --------------------------\n");
    int i;
    for(i = 0; i < size; i++){
        printf("%s\t%d\n", words[i].data, words[i].length);
    }
}

/***************************************************************************
* Functions to handle student data structure
***************************************************************************/
void Init_Students(Student_t students[], int numStudents){
    int i;
    for(i = 0; i < numStudents; i++){
        memset(students[i].firstName, 0, MAX_STRING_LENGTH);
        memset(students[i].lastName, 0, MAX_STRING_LENGTH);
        students[i].gpa = 0;
    }
}

void Insert_StudentName(Student_t *student, const Word_t studentFirstAndLastName[]){
    int i;
    for(i = 0; i < studentFirstAndLastName[0].length; i++){
        student->firstName[i] = studentFirstAndLastName[0].data[i];
    }

    for(i = 0; i < studentFirstAndLastName[1].length; i++){
        student->lastName[i] = studentFirstAndLastName[1].data[i];
    }
}

void Insert_Student(Student_t students[], int numStudents){
    int i;
    for(i = 0; i < numStudents; i++){
        char studentName[MAX_STRING_LENGTH] = { 0 };
        Word_t studentFirstAndLastName[2] = { 0 };
        int length = Get_NextLine(studentName);
        Get_WordsInString(studentFirstAndLastName, studentName, length);
        Insert_StudentName(&students[i], studentFirstAndLastName);
    }
}

void Print_Students(const Student_t students[], int numStudents){
    printf("--------------------- Printing students -------------------------\n");
    int i;
    for(i = 0; i < numStudents; i++){
        printf("name: %s %s, gpa: %d\n", students[i].firstName, students[i].lastName, students[i].gpa);
    }
}

/***************************************************************************
* Functions to handle course data structure
***************************************************************************/
void Init_Courses(Course_t courses[], int numCourses){
    int i;
    for(i = 0; i < numCourses; i++){
        Init_Students(courses[i].studentsEnrolled, MAX_STUDENTS_ENROLLED);
        memset(courses[i].name, 0, MAX_STRING_LENGTH);
        courses[i].averageGPA = 0;
        courses[i].numOfStudents = 0;
    }
}

void Insert_CourseName(Course_t *course, const char name[], const int courseNameLength){
    int i;
    for(i = 0; i < courseNameLength; i++){
        course->name[i] = name[i];
    }
}

void Insert_Course(Course_t courses[], int numCourses){
    int i;
    for(i = 0; i < numCourses; i++){
        char courseName[MAX_STRING_LENGTH] = { 0 };
        int length = Get_NextLine(courseName);
        Insert_CourseName(&courses[i], courseName, length);
    }
}

void Print_Courses(Course_t courses[], int numCourses){
    printf("------------------- printing courses ------------------- \n");
    int i;
    for(i = 0; i < numCourses; i++){
        printf("name: %s, gpa: %f, num students: %d\n", courses[i].name, courses[i].averageGPA, courses[i].numOfStudents);
        Print_Students(courses[i].studentsEnrolled, courses[i].numOfStudents);
    }
}

int main(){

    int numStudents, numCourses;
    scanf("%d %d", &numStudents, &numCourses);

    Student_t students[numStudents];
    Course_t courses[numCourses];

    Init_Students(students, numStudents);
    Insert_Student(students, numStudents);
    Print_Students(students, numStudents);

    Init_Courses(courses, numCourses);
    Insert_Course(courses, numCourses);
    Print_Courses(courses, numCourses);

    while(1){
        char userInput[MAX_STRING_LENGTH] = { 0 };
        Word_t wordsInInput[MAX_WORDS_IN_STRING] = { 0 };
        int length = Get_NextLine(userInput);
        int wordCount = Get_WordsInString(wordsInInput, userInput, length);
        Print_Words(wordsInInput, wordCount);

        char *command = wordsInInput[0].data;
        if(strcmp("quit", command) == STRMCP_EQUAL) break;
        else if(strcmp("enroll", command) == STRMCP_EQUAL) printf("enroll\n");
        else if(strcmp("unenroll", command) == STRMCP_EQUAL) printf("unenroll\n");
        else if(strcmp("grade", command) == STRMCP_EQUAL) printf("grade\n");
        else if(strcmp("ave", command) == STRMCP_EQUAL) printf("ave\n");
        else if(strcmp("gpa", command) == STRMCP_EQUAL) printf("gpa\n");
        else if(strcmp("count", command) == STRMCP_EQUAL) printf("count\n");
        else if(strcmp("topstudent", command) == STRMCP_EQUAL) printf("topstudent\n");
        else if(strcmp("findmutual", command) == STRMCP_EQUAL) printf("findmutual\n");
        else if(strcmp("listcourses", command) == STRMCP_EQUAL) printf("listcourses\n");
        else if(strcmp("findfirstnames", command) == STRMCP_EQUAL) printf("findfirstnames\n");
    }


    return 0;
}
