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
#define INVALID -1

typedef struct{
    char firstName[MAX_STRING_LENGTH];
    char lastName[MAX_STRING_LENGTH];
    int grade;
} Student_t;

typedef struct{
    Student_t studentsEnrolled[MAX_STUDENTS_ENROLLED];
    char name[MAX_STRING_LENGTH];
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

void Copy_String(char targetString[], char stringData[], int stringLength){
    int i;
    for(i = 0; i < stringLength; i++){
        targetString[i] = stringData[i];
    }
}

void Merge_WordsToString(Word_t words[], int startIndex, int stopIndex, char targetString[]){
    int i, j, storeIndex = 0;
    for(i = startIndex; i <= stopIndex; i++){
        for(j = 0; j < words[i].length; j++){
            targetString[storeIndex++] = words[i].data[j];
        }
        if(i != stopIndex) targetString[storeIndex++] = ' ';
    }
}

int Convert_StringToInteger(char *string, int stringLength){
    int i, num = 0;
    for(i = 0; i < stringLength; i++){
        num *= 10;
        num += (string[i] - '0');
    }

    return num;
}

/***************************************************************************
* Functions to handle student data structure
***************************************************************************/
void Init_Students(Student_t students[], int numStudents){
    int i;
    for(i = 0; i < numStudents; i++){
        memset(students[i].firstName, 0, MAX_STRING_LENGTH);
        memset(students[i].lastName, 0, MAX_STRING_LENGTH);
        students[i].grade = INVALID;
    }
}

void Init_StudentsWithUserInput(Student_t students[], int numStudents){
    Init_Students(students, numStudents);

    int i;
    for(i = 0; i < numStudents; i++){
        char studentName[MAX_STRING_LENGTH] = { 0 };
        Word_t studentFirstAndLastName[2] = { 0 };
        int length = Get_NextLine(studentName);
        Get_WordsInString(studentFirstAndLastName, studentName, length);
        Copy_String(students[i].firstName, studentFirstAndLastName[0].data, studentFirstAndLastName[0].length);
        Copy_String(students[i].lastName, studentFirstAndLastName[1].data, studentFirstAndLastName[1].length);
    }
}

int Get_StudentIndex(Student_t students[], int numStudents, const char *firstName, const char *lastName){
    int i;
    for(i = 0; i < numStudents; i++){
        if(strcmp(students[i].firstName, firstName) == STRMCP_EQUAL && strcmp(students[i].lastName, lastName) == STRMCP_EQUAL){
            return i;
        }
    }
    return INVALID;
}

int Get_TopStudentIndex(Student_t students[], int numStudents){
    int topStudentIndex = INVALID, topStudentGrade = INVALID;

    int i;
    for(i = 0; i < numStudents; i++){
        if(students[i].grade > topStudentGrade) topStudentIndex = i;
    }

    return topStudentIndex;
}

void Get_StudentNameAtIndex(Student_t students[], int studentIndex, char studentName[][MAX_STRING_LENGTH]){
    Copy_String(studentName[0], students[studentIndex].firstName, MAX_STRING_LENGTH);
    Copy_String(studentName[1], students[studentIndex].lastName, MAX_STRING_LENGTH);
}

void Update_StudentGrade(Student_t students[], int studentIndex, int grade){
    students[studentIndex].grade = grade;
}

void Add_Student(Student_t students[], int storeIndex, char *firstName, int firstNameLength, char *lastName, int lastNameLength){
    Student_t student = { 0 };
    Copy_String(student.firstName, firstName, firstNameLength);
    Copy_String(student.lastName, lastName, lastNameLength);
    student.grade = INVALID;
    students[storeIndex] = student;
}

void Remove_Student(Student_t students[], int numStudents, int studentIndex){
    Student_t student = { 0, 0, INVALID };
    int i;
    for(i = studentIndex+1; i < numStudents; i++){
        students[i-1] = students[i];
    }
    students[numStudents-1] = student;
}

void Print_Students(const Student_t students[], int numStudents){
    int i;
    for(i = 0; i < numStudents; i++){
        printf("name: %s %s, grade: %d\n", students[i].firstName, students[i].lastName, students[i].grade);
    }
}

/***************************************************************************
* Functions to handle course data structure
***************************************************************************/
void Init_CoursesWithUserInput(Course_t courses[], int numCourses){
    int i;
    for(i = 0; i < numCourses; i++){
        Init_Students(courses[i].studentsEnrolled, MAX_STUDENTS_ENROLLED);

        memset(courses[i].name, 0, MAX_STRING_LENGTH);
        char courseName[MAX_STRING_LENGTH] = { 0 };

        int length = Get_NextLine(courseName);
        Copy_String(courses[i].name, courseName, length);
        courses[i].numOfStudents = 0;
    }
}

int Get_CourseIndex(const Course_t courses[], int numCourses, const char *courseName){
    int courseIndex;
    for(courseIndex = 0; courseIndex < numCourses; courseIndex++){
        if(strcmp(courses[courseIndex].name, courseName) == STRMCP_EQUAL){
            return courseIndex;
        }
    }
    return INVALID;
}

_Bool IsStudentEnrolledInCourse(const Course_t courses[], int courseIndex, const char *studentFirstName, const char *studentLastName){
    Course_t course = courses[courseIndex];
    int studentIndex;
    for(studentIndex = 0; studentIndex < course.numOfStudents; studentIndex++){
        Student_t student = course.studentsEnrolled[studentIndex];
        if(strcmp(student.firstName, studentFirstName) == STRMCP_EQUAL && strcmp(student.lastName, studentLastName) == STRMCP_EQUAL){
            return true;
        }
    }

    return false;
}

void Enroll_StudentInCourse(Course_t courses[], int courseIndex, Word_t studentFirstName, Word_t studentLastName){
    Course_t course = courses[courseIndex];
    Add_Student(course.studentsEnrolled, course.numOfStudents, studentFirstName.data, studentFirstName.length, studentLastName.data, studentLastName.length);
    course.numOfStudents++;
    courses[courseIndex] = course;
}

void UnEnroll_StudentInCourse(Course_t courses[], int courseIndex, Word_t studentFirstName, Word_t studentLastName){
    Course_t course = courses[courseIndex];
    int studentIndex = Get_StudentIndex(course.studentsEnrolled, course.numOfStudents, studentFirstName.data, studentLastName.data);
    Remove_Student(course.studentsEnrolled, course.numOfStudents, studentIndex);
    course.numOfStudents--;
    courses[courseIndex] = course;
}

void Update_StudentGradeInCourse(Course_t courses[], int courseIndex, Word_t studentFirstName, Word_t studentLastName, int grade){
    Course_t course = courses[courseIndex];
    int studentIndex = Get_StudentIndex(course.studentsEnrolled, course.numOfStudents, studentFirstName.data, studentLastName.data);
    Update_StudentGrade(course.studentsEnrolled, studentIndex, grade);
    courses[courseIndex] = course;
}

float Calculate_CourseAverage(Course_t courses[], int courseIndex){
    Course_t course = courses[courseIndex];
    float average = 0;

    int i;
    for(i = 0; i < course.numOfStudents; i++){
        int grade = course.studentsEnrolled[i].grade;
        if(grade != INVALID) average += grade;
    }

    average = average / (float) course.numOfStudents;
    return average;
}

int Get_NumberOfStudentsInCourse(Course_t courses[], int courseIndex){
    return courses[courseIndex].numOfStudents;
}

_Bool Get_TopStudentInCourse(Course_t courses[], int courseIndex, char topStudentName[][MAX_STRING_LENGTH]){
    Course_t course = courses[courseIndex];
    int topStudentIndex = Get_TopStudentIndex(course.studentsEnrolled, course.numOfStudents);
    if(topStudentIndex == INVALID) return false;
    else{
        Get_StudentNameAtIndex(course.studentsEnrolled, topStudentIndex, topStudentName);
        return true;
    }
}

void Print_Courses(const Course_t courses[], int numCourses){
    printf("------------------- printing courses ------------------- \n");
    int i;
    for(i = 0; i < numCourses; i++){
        printf("name: %s, num students: %d\n", courses[i].name, courses[i].numOfStudents);
        Print_Students(courses[i].studentsEnrolled, courses[i].numOfStudents);
    }
}

/********************************************************************************
* Functions to manage the queries
*********************************************************************************/
void EnrollStudent(Course_t courses[], int numCourses, Word_t inputWords[], int numWords){
    Word_t studentFirstName = inputWords[1];
    Word_t studentLastName = inputWords[2];
    char courseName[MAX_STRING_LENGTH] = { 0 };
    Merge_WordsToString(inputWords, 3, numWords-1, courseName);

    printf("enrolling: student name: %s %s\tcourse name: %s\n", studentFirstName.data, studentLastName.data, courseName);
    int courseIndex = Get_CourseIndex(courses, numCourses, courseName);

    if(courseIndex == INVALID) return;
    else if(IsStudentEnrolledInCourse(courses, courseIndex, studentFirstName.data, studentLastName.data)) return;
    else Enroll_StudentInCourse(courses, courseIndex, studentFirstName, studentLastName);
}

void UnEnrollStudent(Course_t courses[], int numCourses, Word_t inputWords[], int numWords){
    Word_t studentFirstName = inputWords[1];
    Word_t studentLastName = inputWords[2];
    char courseName[MAX_STRING_LENGTH] = { 0 };
    Merge_WordsToString(inputWords, 3, numWords-1, courseName);

    printf("unenrolling: student name: %s %s\tcourse name: %s\n", studentFirstName.data, studentLastName.data, courseName);
    int courseIndex = Get_CourseIndex(courses, numCourses, courseName);
    if(courseIndex == INVALID) return;
    else if(!IsStudentEnrolledInCourse(courses, courseIndex, studentFirstName.data, studentLastName.data)) return;
    else UnEnroll_StudentInCourse(courses, courseIndex, studentFirstName, studentLastName);
}

void GradeStudent(Course_t courses[], int numCourses, Word_t inputWords[], int numWords){
    Word_t studentFirstName = inputWords[1];
    Word_t studentLastName = inputWords[2];
    char courseName[MAX_STRING_LENGTH] = { 0 };
    Merge_WordsToString(inputWords, 3, numWords-2, courseName);
    int studentGrade = Convert_StringToInteger(inputWords[numWords-1].data, inputWords[numWords-1].length);

    printf("grade: student name: %s %s\tcourse name: %s\tgrade: %d\n", studentFirstName.data, studentLastName.data, courseName, studentGrade);
    int courseIndex = Get_CourseIndex(courses, numCourses, courseName);
    if(courseIndex == INVALID) return;
    else if(!IsStudentEnrolledInCourse(courses, courseIndex, studentFirstName.data, studentLastName.data)) return;
    else Update_StudentGradeInCourse(courses, courseIndex, studentFirstName, studentLastName, studentGrade);
}

float CourseAverage(Course_t courses[], int numCourses, Word_t inputWords[], int numWords){
    char courseName[MAX_STRING_LENGTH] = { 0 };
    Merge_WordsToString(inputWords, 1, numWords-1, courseName);

    printf("average: course name: %s\n", courseName);
    int courseIndex = Get_CourseIndex(courses, numCourses, courseName);
    if(courseIndex == INVALID) return 0;
    else return Calculate_CourseAverage(courses, courseIndex);
}

int CourseEnrollmentCount(Course_t courses[], int numCourses, Word_t inputWords[], int numWords){
    char courseName[MAX_STRING_LENGTH] = { 0 };
    Merge_WordsToString(inputWords, 1, numWords-1, courseName);

    printf("course enrollment count: course name: %s\n", courseName);
    int courseIndex = Get_CourseIndex(courses, numCourses, courseName);
    if(courseIndex == INVALID) return 0;
    else return Get_NumberOfStudentsInCourse(courses, courseIndex);
}

_Bool TopStudentInCourse(Course_t courses[], int numCourses, Word_t inputWords[], int numWords, char topStudentName[][MAX_STRING_LENGTH]){
    char courseName[MAX_STRING_LENGTH] = { 0 };
    Merge_WordsToString(inputWords, 1, numWords-1, courseName);

    printf("top student: course name: %s\n", courseName);
    int courseIndex = Get_CourseIndex(courses, numCourses, courseName);
    if(courseIndex == INVALID) return false;
    else return Get_TopStudentInCourse(courses, courseIndex, topStudentName);
}

int main(){

    int numStudents, numCourses;
    scanf("%d %d", &numStudents, &numCourses);

    Student_t students[numStudents];
    Course_t courses[numCourses];

    Init_StudentsWithUserInput(students, numStudents);
    // Print_Students(students, numStudents);

    Init_CoursesWithUserInput(courses, numCourses);
    // Print_Courses(courses, numCourses);

    while(1){
        char userInput[MAX_STRING_LENGTH] = { 0 };
        Word_t wordsInInput[MAX_WORDS_IN_STRING] = { 0 };
        int length = Get_NextLine(userInput);
        int wordCount = Get_WordsInString(wordsInInput, userInput, length);
        // Print_Words(wordsInInput, wordCount);

        char *command = wordsInInput[0].data;
        if(strcmp("quit", command) == STRMCP_EQUAL)
            break;
        else if(strcmp("enroll", command) == STRMCP_EQUAL){
            EnrollStudent(courses, numCourses, wordsInInput, wordCount);
        }
        else if(strcmp("unenroll", command) == STRMCP_EQUAL){
            UnEnrollStudent(courses, numCourses, wordsInInput, wordCount);
        }
        else if(strcmp("grade", command) == STRMCP_EQUAL){
            GradeStudent(courses, numCourses, wordsInInput, wordCount);
        }
        else if(strcmp("ave", command) == STRMCP_EQUAL){
            float averageGPA = CourseAverage(courses, numCourses, wordsInInput, wordCount);
            printf("%.2f\n", averageGPA);
        }
        else if(strcmp("gpa", command) == STRMCP_EQUAL) printf("gpa\n");
        else if(strcmp("count", command) == STRMCP_EQUAL){
            int numOfEnrollments = CourseEnrollmentCount(courses, numCourses, wordsInInput, wordCount);
            printf("%d\n", numOfEnrollments);
        }
        else if(strcmp("topstudent", command) == STRMCP_EQUAL){
            char topStudentName[2][MAX_STRING_LENGTH];  // Array stores first and last name
            if(TopStudentInCourse(courses, numCourses, wordsInInput, wordCount, topStudentName)) printf("%s %s\n", topStudentName[0], topStudentName[1]);
            else printf("N/A\n");
        }
        else if(strcmp("findmutual", command) == STRMCP_EQUAL) printf("findmutual\n");
        else if(strcmp("listcourses", command) == STRMCP_EQUAL) printf("listcourses\n");
        else if(strcmp("findfirstnames", command) == STRMCP_EQUAL) printf("findfirstnames\n");

        Print_Courses(courses, numCourses);
    }


    return 0;
}
