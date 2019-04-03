#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS_IN_QUERY 30
#define MAX_QUERY_LENGTH 500
#define MAX_COURSE_NAME_LENGTH 200
#define MAX_STUDENT_NAME_LENGTH 50
#define MAX_COMMAND_LENGTH 50

#define STRCMP_EQUAL 0
#define NULL_CHARACTER '\0'
#define INVALID -1

typedef struct{
    bool enrolled;
    int grade;
} Entry_t;

typedef struct{
    char firstName[MAX_STUDENT_NAME_LENGTH];
    char lastName[MAX_STUDENT_NAME_LENGTH];
} Student_t;

typedef struct{
    char name[MAX_COURSE_NAME_LENGTH];
    int topGrade;
} Course_t;

// Global variable holding the values for management system
int numStudents, numCourses;

/****************************************************************
* String helper functions
*****************************************************************/
void ConvertToLowercase(char *string){
    size_t index;
    for(index = 0; index < strlen(string); index++)
        string[index] = tolower(string[index]);
}

int GetIndexOfSpacesInString(const char *string, int wordIndexArray[]){
    int storeIndex = 0;
    size_t index;
    for(index = 0; index < strlen(string); index++)
        if(string[index] == ' ') wordIndexArray[storeIndex++] = index;

    return storeIndex;
}

void GetWordInString(const char *string, int startIndex, int endIndex, char *targetString){
    int storeIndex = 0;
    size_t index;
    for(index = (size_t)startIndex; index < (size_t)endIndex && index < strlen(string); index++)
        targetString[storeIndex++] = string[index];
}

int ConvertWordInStringToInt(const char *string, int startIndex, int endIndex){
    int num = 0;
    size_t i;
    for(i = (size_t)startIndex; i < (size_t)endIndex && i < strlen(string); i++){
        if(!isdigit(string[i])) return INVALID;
        num *= 10;
        num += (int)string[i] - (int)'0';
    }
    return num;
}

void ClearString(char *string){
    memset(string, NULL_CHARACTER, strlen(string));
}

/*********************************************************************************
* Functions for the student data structure
*********************************************************************************/
void Init_Students(Student_t students[]){
    int i;
    for(i = 0; i < numStudents; i++){
        memset(students[i].firstName, NULL_CHARACTER, MAX_STUDENT_NAME_LENGTH);
        memset(students[i].lastName, NULL_CHARACTER, MAX_STUDENT_NAME_LENGTH);
        scanf("%s", students[i].firstName);
        scanf("%s", students[i].lastName);
        ConvertToLowercase(students[i].firstName);
        ConvertToLowercase(students[i].lastName);
    }
}

int Get_StudentIndex(Student_t students[], const char *firstName, const char *lastName){
    int i;
    for(i = 0; i < numStudents; i++){
        bool sameFirstName = (strcmp(students[i].firstName, firstName) == STRCMP_EQUAL);
        bool sameLastName = (strcmp(students[i].lastName, lastName) == STRCMP_EQUAL);
        if(sameFirstName && sameLastName) return i;
    }
    return INVALID;
}

int Print_StudentsWithLastName(Student_t students[], const char *lastName){
    bool foundStudent = false;
    int i, storeIndex = 0;
    for(i = 0; i < numStudents; i++){
        if(strcmp(students[i].lastName, lastName) == STRCMP_EQUAL){
            if(!foundStudent){
                printf("%s", students[i].firstName);
                foundStudent = true;
            }
            else printf(", %s", students[i].firstName);
        }
    }

    if(!foundStudent) printf("N/A");
    printf("\n");
}

void Print_Students(Student_t students[]){
    int i;
    for(i = 0; i < numStudents; i++){
        printf("first name: %s, last name: %s,\n", students[i].firstName, students[i].lastName);
    }
}

/*********************************************************************************
* Functions for the courses data structure
*********************************************************************************/
void Init_Courses(Course_t courses[]){
    int i;
    for(i = 0; i < numCourses; i++){
        memset(courses[i].name, NULL_CHARACTER, MAX_COURSE_NAME_LENGTH);
        courses[i].topGrade = 0;
        scanf(" %[^\n]", courses[i].name);
        ConvertToLowercase(courses[i].name);
    }
}

int Get_CourseIndex(Course_t courses[], const char *courseName){
    int i;
    for(i = 0; i < numCourses; i++){
        if(strcmp(courseName, courses[i].name) == STRCMP_EQUAL) return i;
    }
    return INVALID;
}

void Update_TopGrade(Course_t courses[], int courseIndex, int grade){
    if(grade >= courses[courseIndex].topGrade)
        courses[courseIndex].topGrade = grade;
}

int Get_CourseTopGrade(Course_t courses[], int courseIndex){
    if(courseIndex != INVALID)
        return courses[courseIndex].topGrade;
}

void Print_Courses(Course_t courses[]){
    int i;
    for(i = 0; i < numCourses; i++)
        printf("course name: %s, top grade: %d\n", courses[i].name, courses[i].topGrade);
}

/*********************************************************************************
* Functions for the management system
*********************************************************************************/
void Init_System(Entry_t managementSystem[numCourses][numStudents]){
    int i, j;
    for(i = 0; i < numCourses; i++){
        for(j = 0; j < numStudents; j++){
            managementSystem[i][j].enrolled = false;
            managementSystem[i][j].grade = INVALID;
        }
    }
}

void Enroll_Student(Entry_t managementSystem[numCourses][numStudents], int courseIndex, int studentIndex){
    if(courseIndex != INVALID && studentIndex != INVALID){
        if(!managementSystem[courseIndex][studentIndex].enrolled){
            managementSystem[courseIndex][studentIndex].enrolled = true;
            managementSystem[courseIndex][studentIndex].grade = INVALID;
        }
    }
}

void Unenroll_Student(Entry_t managementSystem[numCourses][numStudents], int courseIndex, int studentIndex){
    if(courseIndex != INVALID && studentIndex != INVALID){
        if(managementSystem[courseIndex][studentIndex].enrolled){
            managementSystem[courseIndex][studentIndex].enrolled = false;
            managementSystem[courseIndex][studentIndex].grade = INVALID;
        }
    }
}

void Grade_Student(Entry_t managementSystem[numCourses][numStudents], int courseIndex, int studentIndex, int grade){
    if(courseIndex != INVALID && studentIndex != INVALID){
        if(managementSystem[courseIndex][studentIndex].enrolled)
           managementSystem[courseIndex][studentIndex].grade = grade;
    }
}

void Print_CourseAvg(Entry_t studentSystem[numCourses][numStudents], int courseIndex){
    int totalGrade = 0, studentCount = 0;
    if(courseIndex != INVALID){
        int studentIndex;
        for(studentIndex = 0; studentIndex < numStudents; studentIndex++){
            if(studentSystem[courseIndex][studentIndex].enrolled && studentSystem[courseIndex][studentIndex].grade != INVALID){
                totalGrade += studentSystem[courseIndex][studentIndex].grade;
                studentCount++;
            }
        }
    }

    if(studentCount == 0) printf("0\n");
    else printf("%0.2f\n", (float)totalGrade / (float) studentCount);
}

float Print_StudentAvg(Entry_t studentSystem[numCourses][numStudents], int studentIndex){
    int totalGrade = 0, courseCount = 0;
    if(studentIndex != INVALID){
        int courseIndex;
        for(courseIndex = 0; courseIndex < numCourses; courseIndex++){
            if(studentSystem[courseIndex][studentIndex].enrolled && studentSystem[courseIndex][studentIndex].grade != INVALID){
                totalGrade += studentSystem[courseIndex][studentIndex].grade;
                courseCount++;
            }
        }
    }

    if(courseCount == 0) printf("0\n");
    else printf("%0.2f\n", (float)totalGrade / (float) courseCount);
}

void Print_NumStudentsEnrolled(Entry_t studentSystem[numCourses][numStudents], int courseIndex){
    int count = 0;
    if(courseIndex != INVALID){
        int studentIndex;
        for(studentIndex = 0; studentIndex < numStudents; studentIndex++){
            if(studentSystem[courseIndex][studentIndex].enrolled) count++;
        }
    }
    printf("%d\n", count);
}

void Print_CoursesEnrolled(Entry_t studentSystem[numCourses][numStudents], Course_t courses[], int studentIndex){
    bool foundCourse = false;
    int courseIndex;
    if(studentIndex != INVALID){
        for(courseIndex = 0; courseIndex < numCourses; courseIndex++){
            if(studentSystem[courseIndex][studentIndex].enrolled){
                if(!foundCourse){
                    printf("%s", courses[courseIndex].name);
                    foundCourse = true;
                }
                else printf(", %s", courses[courseIndex].name);
            }
        }
    }

    if(!foundCourse) printf("N/A");
    printf("\n");
}

void Print_TopStudentsInCourse(Entry_t studentSystem[numCourses][numStudents], Student_t students[], int courseIndex, int topGrade){
    bool foundStudent = false;
    int storeIndex = 0;
    if(courseIndex != INVALID){
        int studentIndex;
        for(studentIndex = 0; studentIndex < numStudents; studentIndex++){
            if(studentSystem[courseIndex][studentIndex].grade >= topGrade){
                if(!foundStudent){
                    printf("%s %s", students[studentIndex].firstName, students[studentIndex].lastName);
                    foundStudent = true;
                }
                else printf(", %s %s", students[studentIndex].firstName, students[studentIndex].lastName);
            }
        }
    }

    if(!foundStudent) printf("N/A");
    printf("\n");
}

void Print_StudentsInMutualCourses(Entry_t studentSystem[numCourses][numStudents], Student_t students[], int studentIndex){
    bool foundStudent = false;;
    int storeIndex = 0;
    if(studentIndex != INVALID){
        int courseIndex, index;
        for(index = 0; index < numStudents; index++){
            if(index == studentIndex) continue;
            int mutualCourses = 0;
            for(courseIndex = 0; courseIndex < numCourses; courseIndex++){
                if(studentSystem[courseIndex][studentIndex].enrolled && studentSystem[courseIndex][index].enrolled)
                    mutualCourses++;
            }

            if(mutualCourses >= 2){
                if(!foundStudent){
                    printf("%s %s", students[index].firstName, students[index].lastName);
                    foundStudent = true;
                }
                else printf(", %s %s", students[index].firstName, students[index].lastName);
            }
        }
    }

    if(!foundStudent) printf("N/A");
    printf("\n");
}

void Print_System(Entry_t managementSystem[numCourses][numStudents]){
    int i,j;
    for(i = 0; i < numCourses; i++){
        for(j = 0; j < numStudents; j++)
            printf("enrolled: %d, grade: %d\t", managementSystem[i][j].enrolled, managementSystem[i][j].grade);
        printf("\n");
    }
}

int main(){

    // Getting inputs regarding size
    scanf("%d", &numStudents);
    scanf("%d", &numCourses);

    // Initializing instance of students and courses
    Student_t students[numStudents];
    Init_Students(students);

    Course_t courses[numCourses];
    Init_Courses(courses);

    // Initializing instance of student management system
    Entry_t managementSystem[numCourses][numStudents];
    Init_System(managementSystem);

    // Print_Students(students);
    // Print_Courses(courses);
    // Print_System(managementSystem);

    // Variables used to store data relevant to the user queries
    char query[MAX_QUERY_LENGTH] = { NULL_CHARACTER };
    char command[MAX_COMMAND_LENGTH] = { NULL_CHARACTER };
    char studentFirstName[MAX_STUDENT_NAME_LENGTH] = { NULL_CHARACTER };
    char studentLastName[MAX_STUDENT_NAME_LENGTH] = { NULL_CHARACTER };
    char courseName[MAX_COURSE_NAME_LENGTH] = { NULL_CHARACTER };
    int querySpaceIndexes[MAX_WORDS_IN_QUERY];
    int querySpaceCount;

    do{
        scanf(" %[^\n]", query);
        ConvertToLowercase(query);
        querySpaceCount = GetIndexOfSpacesInString(query, querySpaceIndexes);

        // Getting the command from query
        if(querySpaceCount >= 1) GetWordInString(query, 0, querySpaceIndexes[0], command);

        bool quitCommand = (strcmp("quit", command) == STRCMP_EQUAL);
        bool enrollCommand = (strcmp("enroll", command) == STRCMP_EQUAL);
        bool unenrollCommand = (strcmp("unenroll", command) == STRCMP_EQUAL);
        bool gradeCommand = (strcmp("grade", command) == STRCMP_EQUAL);
        bool aveCommand = (strcmp("ave", command) == STRCMP_EQUAL || strcmp("ave", query) == STRCMP_EQUAL);
        bool gpaCommand = (strcmp("gpa", command) == STRCMP_EQUAL || strcmp("gpa", query) == STRCMP_EQUAL);
        bool countCommand = (strcmp("count", command) == STRCMP_EQUAL || strcmp("count", query) == STRCMP_EQUAL);
        bool topStudentCommand = (strcmp("topstudent", command) == STRCMP_EQUAL || strcmp("topstudent", query) == STRCMP_EQUAL);
        bool findMutualCommand = (strcmp("findmutual", command) == STRCMP_EQUAL || strcmp("findmutual", query) == STRCMP_EQUAL);
        bool listCoursesCommand = (strcmp("listcourses", command) == STRCMP_EQUAL || strcmp("listcourses", query) == STRCMP_EQUAL);
        bool findFirstNamesCommand = (strcmp("findfirstnames", command) == STRCMP_EQUAL || strcmp("findfirstnames", query) == STRCMP_EQUAL);

        if(quitCommand) break;
        if(enrollCommand || unenrollCommand){
            if(querySpaceCount >= 2) GetWordInString(query, querySpaceIndexes[0]+1, querySpaceIndexes[1], studentFirstName);
            if(querySpaceCount >= 3) GetWordInString(query, querySpaceIndexes[1]+1, querySpaceIndexes[2], studentLastName);
            if(querySpaceCount >= 3) GetWordInString(query, querySpaceIndexes[2]+1, (int)strlen(query), courseName);

            int studentIndex = Get_StudentIndex(students, studentFirstName, studentLastName);
            int courseIndex = Get_CourseIndex(courses, courseName);

            if(enrollCommand) Enroll_Student(managementSystem, courseIndex, studentIndex);
            if(unenrollCommand) Unenroll_Student(managementSystem, courseIndex, studentIndex);
        }
        else if(gradeCommand){
            if(querySpaceCount >= 2) GetWordInString(query, querySpaceIndexes[0]+1, querySpaceIndexes[1], studentFirstName);
            if(querySpaceCount >= 3) GetWordInString(query, querySpaceIndexes[1]+1, querySpaceIndexes[2], studentLastName);
            if(querySpaceCount >= 3) GetWordInString(query, querySpaceIndexes[2]+1, querySpaceIndexes[querySpaceCount-1], courseName);
            int grade = ConvertWordInStringToInt(query, querySpaceIndexes[querySpaceCount-1]+1, (int)strlen(query));

            int studentIndex = Get_StudentIndex(students, studentFirstName, studentLastName);
            int courseIndex = Get_CourseIndex(courses, courseName);

            Grade_Student(managementSystem, courseIndex, studentIndex, grade);
        }
        else if(aveCommand || countCommand || topStudentCommand){
            if(querySpaceCount >= 1) GetWordInString(query, querySpaceIndexes[0]+1, (int)strlen(query), courseName);
            int courseIndex = Get_CourseIndex(courses, courseName);

            if(aveCommand) Print_CourseAvg(managementSystem, courseIndex);
            if(countCommand) Print_NumStudentsEnrolled(managementSystem, courseIndex);
            if(topStudentCommand) Print_TopStudentsInCourse(managementSystem, students, courseIndex, Get_CourseTopGrade(courses, courseIndex));
        }
        else if(gpaCommand || listCoursesCommand || findMutualCommand){
            if(querySpaceCount >= 2) GetWordInString(query, querySpaceIndexes[0]+1, querySpaceIndexes[1], studentFirstName);
            if(querySpaceCount >= 2) GetWordInString(query, querySpaceIndexes[1]+1, (int) strlen(query), studentLastName);
            int studentIndex = Get_StudentIndex(students, studentFirstName, studentLastName);

            if(gpaCommand) Print_StudentAvg(managementSystem, studentIndex);
            if(findMutualCommand) Print_StudentsInMutualCourses(managementSystem, students, studentIndex);
            if(listCoursesCommand) Print_CoursesEnrolled(managementSystem, courses, studentIndex);
        }
        else if(findFirstNamesCommand){
            if(querySpaceCount >= 1) GetWordInString(query, querySpaceIndexes[0]+1, (int) strlen(query), studentLastName);
            Print_StudentsWithLastName(students, studentLastName);
        }

        // Print_System(managementSystem);

        // Clearing strings to not have dangling data
        ClearString(command);
        ClearString(studentFirstName);
        ClearString(studentLastName);
        ClearString(courseName);

    } while(strcmp("quit", query) != STRCMP_EQUAL);

    return 0;
}
