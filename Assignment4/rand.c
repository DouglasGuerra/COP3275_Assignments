#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS_IN_QUERY 30
#define MAX_QUERY_LENGTH 500
#define MAX_COURSE_NAME_LENGTH 200
#define MAX_STUDENT_NAME_LENGTH 50

#define NULL_CHARACTER '\0'
#define INVALID -1
#define STRCMP_EQUAL 0

#define PRINT_LAST_NAME true
#define DO_NOT_PRINT_LAST_NAME false

typedef struct{
    int grade;
    bool enrolled;
} SystemEntry_t;

typedef struct{
    char name[MAX_COURSE_NAME_LENGTH];
} Course_t;

typedef struct{
    char firstName[MAX_STUDENT_NAME_LENGTH];
    char lastName[MAX_STUDENT_NAME_LENGTH];
} Student_t;

// Global variables
int numStudents, numCourses;

/*****************************************************
* Helper functions
******************************************************/
void Clear_WordArray(int arraySize, int stringLength, char words[arraySize][stringLength]){
    int i;
    for(i = 0; i < arraySize; i++)
        memset(words[i], NULL_CHARACTER, stringLength);
}

void Print_WordArray(int arraySize, int stringLength, char words[arraySize][stringLength]){
    int i;
    for(i = 0; i < arraySize; i++) printf("%s\n", words[i]);
}

void Get_NextInput(int length, char *string){
    char readInChar;
    memset(string, NULL_CHARACTER, length);

    int i = 0;
    scanf(" %c", &readInChar);
    while(readInChar != '\n' && i < length){
        string[i++] = tolower(readInChar);
        scanf("%c", &readInChar);
    }
}

int Splice_String(const char *string, int maxWords, int stringLength, char words[maxWords][stringLength]){
    int storeIndex = 0, dataIndex = 0;
    Clear_WordArray(maxWords, stringLength, words);

    int i;
    for(i = 0; i < strlen(string); i++){
        if(storeIndex >= maxWords) break;
        if(string[i] == ' '){
            if(dataIndex > 0) storeIndex++;
            dataIndex = 0;
        }
        else words[storeIndex][dataIndex++] = string[i];
    }
    if(dataIndex > 0) storeIndex++;

    return storeIndex;
}

void Merge_String(int startIndex, int endIndex, int stringLength, char words[][stringLength], int targetStringLength, char *targetString){
    memset(targetString, NULL_CHARACTER, targetStringLength);

    int i;
    for(i = startIndex; i <= endIndex; i++){
        sprintf(targetString, "%s%s", targetString, words[i]);
        if(i != endIndex) sprintf(targetString, "%s%s", targetString, " ");
    }
}

int Convert_StringToInt(const char *string){
    int number = 0;
    int i;
    for(i = 0; i < strlen(string); i++){
        if(!isdigit(string[i])) return INVALID;
        number *= 10;
        number += (int)string[i] - '0';
    }
    return number;
}

/******************************************************
* Students data structure
*******************************************************/
void Init_Students(Student_t students[]){
    int i;
    for(i = 0; i < numStudents; i++){
        memset(students[i].firstName, NULL_CHARACTER, MAX_STUDENT_NAME_LENGTH);
        memset(students[i].lastName, NULL_CHARACTER, MAX_STUDENT_NAME_LENGTH);
    }
}

void Fill_Students(Student_t students[]){
    char studentName[MAX_STUDENT_NAME_LENGTH];
    char splicedName[2][MAX_STUDENT_NAME_LENGTH];

    int i;
    for(i = 0; i < numStudents; i++){
        Get_NextInput(MAX_STUDENT_NAME_LENGTH, studentName);
        Splice_String(studentName, 2, MAX_STUDENT_NAME_LENGTH, splicedName);

        sprintf(students[i].firstName, "%s", splicedName[0]);
        sprintf(students[i].lastName, "%s", splicedName[1]);
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

int Get_StudentsWithLastName(Student_t students[], const char *lastName, int studentIds[]){
    memset(studentIds, 0, numStudents);
    int i, storeIndex = 0;
    for(i = 0; i < numStudents; i++){
        if(strcmp(students[i].lastName, lastName) == STRCMP_EQUAL)
            studentIds[storeIndex++] = i;
    }
    return storeIndex;
}

void Print_StudentsWithId(Student_t students[], int numIds, int studentIds[], bool printLastName){
    int i;
    for(i = 0; i < numIds; i++){
        if(i > 0) printf(", ");
        printf("%s", students[studentIds[i]].firstName);
        if(printLastName) printf(" %s", students[studentIds[i]].lastName);
    }
    printf("\n");
}

void Print_Students(Student_t students[]){
    printf("\n------------------------ Students -----------------------\n");
    int i;
    for(i = 0; i < numStudents; i++){
        printf("first name: %s, length: %lu\t", students[i].firstName, strlen(students[i].firstName));
        printf("last name: %s, length: %lu\n", students[i].lastName, strlen(students[i].lastName));
    }
    printf("-------------------------------------------------------\n");
}

/******************************************************
* Students data structure
*******************************************************/
void Init_Courses(Course_t courses[]){
    int i;
    for(i = 0; i < numCourses; i++)
        memset(courses[i].name, NULL_CHARACTER, MAX_COURSE_NAME_LENGTH);
}

void Fill_Courses(Course_t courses[]){
    char courseName[MAX_COURSE_NAME_LENGTH];

    int i;
    for(i = 0; i < numCourses; i++){
        Get_NextInput(MAX_COURSE_NAME_LENGTH, courseName);
        sprintf(courses[i].name, "%s", courseName);
    }
}

int Get_CourseIndex(Course_t courses[], const char *courseName){
    int i;
    for(i = 0; i < numCourses; i++){
        if(strcmp(courses[i].name, courseName) == STRCMP_EQUAL) return i;
    }
    return INVALID;
}

void Print_CoursesWithId(Course_t courses[], int numIds, int courseIds[]){
    int i;
    for(i = 0; i < numIds; i++){
        if(i > 0) printf(", ");
        printf("%s", courses[courseIds[i]].name);
    }
    printf("\n");
}

void Print_Courses(Course_t courses[]){
    printf("\n------------------------ Courses-----------------------\n");
    int i;
    for(i = 0; i < numCourses; i++)
        printf("name: %s, length: %lu\n", courses[i].name, strlen(courses[i].name));
    printf("-------------------------------------------------------\n");
}

/******************************************************
* Student Management System ( row => courses, col => students )
*******************************************************/
void Init_System(SystemEntry_t studentSystem[][numStudents]){
    int courseIndex, studentIndex;
    for(courseIndex = 0; courseIndex < numCourses; courseIndex++){
        for(studentIndex = 0; studentIndex < numStudents; studentIndex++){
            studentSystem[courseIndex][studentIndex].grade = INVALID;
            studentSystem[courseIndex][studentIndex].enrolled = false;
        }
    }
}

void Enroll_Student(SystemEntry_t studentSystem[][numStudents], int courseIndex, int studentIndex){
    if(courseIndex != INVALID && studentIndex != INVALID){
        studentSystem[courseIndex][studentIndex].grade = INVALID;
        studentSystem[courseIndex][studentIndex].enrolled = true;
    }
}

void UnEnroll_Student(SystemEntry_t studentSystem[][numStudents], int courseIndex, int studentIndex){
    if(courseIndex != INVALID && studentIndex != INVALID){
        studentSystem[courseIndex][studentIndex].grade = INVALID;
        studentSystem[courseIndex][studentIndex].enrolled = false;
    }
}

void Grade_Student(SystemEntry_t studentSystem[][numStudents], int courseIndex, int studentIndex, int grade){
    if(courseIndex != INVALID && studentIndex != INVALID){
        if(studentSystem[courseIndex][studentIndex].enrolled)
            studentSystem[courseIndex][studentIndex].grade = grade;
    }
}

float Get_CourseAvg(SystemEntry_t studentSystem[][numStudents], int courseIndex){
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

    if(studentCount == 0) return INVALID;
    else return ((float)totalGrade / (float) studentCount);
}

float Get_StudentAvg(SystemEntry_t studentSystem[][numStudents], int studentIndex){
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

    if(courseCount == 0) return INVALID;
    else return ((float)totalGrade / (float)courseCount);
}

int Get_NumStudentsEnrolled(SystemEntry_t studentSystem[][numStudents], int courseIndex){
    int count = 0;
    int studentIndex;
    for(studentIndex = 0; studentIndex < numStudents; studentIndex++){
        if(studentSystem[courseIndex][studentIndex].enrolled) count++;
    }

    return count;
}

int Get_CoursesEnrolled(SystemEntry_t studentSystem[][numStudents], int studentIndex, int courseIds[]){
    memset(courseIds, 0, numCourses);
    int courseIndex, storeIndex = 0;
    for(courseIndex = 0; courseIndex < numCourses; courseIndex++){
        if(studentSystem[courseIndex][studentIndex].enrolled)
            courseIds[storeIndex++] = courseIndex;
    }
    return storeIndex;
}

int Get_TopGradeInCourse(SystemEntry_t studentSystem[][numStudents], int courseIndex){
    int topGrade = 0;
    if(courseIndex != INVALID){
        int studentIndex;
        for(studentIndex = 0; studentIndex < numStudents; studentIndex++)
            if(studentSystem[courseIndex][studentIndex].grade > topGrade)
                topGrade = studentSystem[courseIndex][studentIndex].grade;
    }
    return topGrade;
}

int Get_TopStudentsInCourse(SystemEntry_t studentSystem[][numStudents], int courseIndex, int studentIds[]){
    memset(studentIds, 0, numStudents);
    int storeIndex = 0;
    int topGrade = Get_TopGradeInCourse(studentSystem, courseIndex);
    if(courseIndex != INVALID){
        int studentIndex;
        for(studentIndex = 0; studentIndex < numStudents; studentIndex++){
            if(studentSystem[courseIndex][studentIndex].grade >= topGrade)
                studentIds[storeIndex++] = studentIndex;
        }
    }

    return storeIndex;
}

int Get_StudentsInMutualCourses(SystemEntry_t studentSystem[][numStudents], int studentIndex, int studentIds[]){
    memset(studentIds, 0, numStudents);
    int storeIndex = 0;
    if(studentIndex != INVALID){
        int courseIndex, index;
        for(index = 0; index < numStudents; index++){
            int mutualCourses = 0;
            for(courseIndex = 0; courseIndex < numCourses; courseIndex++){
                bool sameStudent = (studentIndex == index);
                bool enrolledInSameCourse = (studentSystem[courseIndex][index].enrolled && studentSystem[courseIndex][index].enrolled);

                if(!sameStudent && enrolledInSameCourse) mutualCourses++;
            }

            if(mutualCourses >= 2) studentIds[storeIndex++] = index;
        }
    }
    return storeIndex;
}

void Print_System(SystemEntry_t studentSystem[][numStudents]){
    int courseIndex, studentIndex;
    for(courseIndex = 0; courseIndex < numCourses; courseIndex++){
        for(studentIndex = 0; studentIndex < numStudents; studentIndex++){
            printf("%d, ", studentSystem[courseIndex][studentIndex].grade);
            printf("%d\t", studentSystem[courseIndex][studentIndex].enrolled);
        }
        printf("\n");
    }
    printf("\n");
}

int main(){

    // Getting inputs regarding size
    scanf("%d", &numStudents);
    scanf("%d", &numCourses);
    // printf("%d %d\n", numStudents, numCourses);

    // Initializing a student structure
    Student_t students[numStudents];
    Init_Students(students);
    Fill_Students(students);
    // Print_Students(students);

    // Initializing a course structure
    Course_t courses[numCourses];
    Init_Courses(courses);
    Fill_Courses(courses);
    // Print_Courses(courses);

    // Initializing system
    SystemEntry_t studentSystem[numCourses][numStudents];
    Init_System(studentSystem);
    // Print_System(studentSystem);

    // Handling the queries
    char query[MAX_QUERY_LENGTH] = { NULL_CHARACTER };
    char splicedQuery[MAX_WORDS_IN_QUERY][MAX_QUERY_LENGTH] = { NULL_CHARACTER};

    do{
        Get_NextInput(MAX_QUERY_LENGTH, query);
        int wordCount = Splice_String(query, MAX_WORDS_IN_QUERY, MAX_QUERY_LENGTH, splicedQuery);

        char *command = splicedQuery[0];
        // printf("command: %s\n", command);

        bool enrollCommand = (strcmp("enroll", command) == STRCMP_EQUAL);
        bool unenrollCommand = (strcmp("unenroll", command) == STRCMP_EQUAL);
        bool gradeCommand = (strcmp("grade", command) == STRCMP_EQUAL);
        bool aveCommand = (strcmp("ave", command) == STRCMP_EQUAL);
        bool gpaCommand = (strcmp("gpa", command) == STRCMP_EQUAL);
        bool countCommand = (strcmp("count", command) == STRCMP_EQUAL);
        bool topStudentCommand = (strcmp("topstudent", command) == STRCMP_EQUAL);
        bool findMutualCommand = (strcmp("findmutual", command) == STRCMP_EQUAL);
        bool listCoursesCommand = (strcmp("listcourses", command) == STRCMP_EQUAL);
        bool findFirstNamesCommand = (strcmp("findfirstnames", command) == STRCMP_EQUAL);

        if((enrollCommand || unenrollCommand) && wordCount >= 4){
            char *firstName = splicedQuery[1];
            char *lastName = splicedQuery[2];
            char courseName[MAX_COURSE_NAME_LENGTH];
            Merge_String(3, wordCount-1, MAX_QUERY_LENGTH, splicedQuery, MAX_COURSE_NAME_LENGTH, courseName);

            int studentIndex = Get_StudentIndex(students, firstName, lastName);
            int courseIndex = Get_CourseIndex(courses, courseName);

            // printf("un/enroll: %s %s %s\n", firstName, lastName, courseName);
            // printf("un/enroll: %d %d\n", studentIndex, courseIndex);
            if(enrollCommand) Enroll_Student(studentSystem, courseIndex, studentIndex);
            if(unenrollCommand) UnEnroll_Student(studentSystem, courseIndex, studentIndex);
        }
        else if(gradeCommand && wordCount >= 5){
            char *firstName = splicedQuery[1];
            char *lastName = splicedQuery[2];
            char courseName[MAX_COURSE_NAME_LENGTH];
            Merge_String(3, wordCount-2, MAX_QUERY_LENGTH, splicedQuery, MAX_COURSE_NAME_LENGTH, courseName);

            int studentIndex = Get_StudentIndex(students, firstName, lastName);
            int courseIndex = Get_CourseIndex(courses, courseName);
            int grade = Convert_StringToInt(splicedQuery[wordCount-1]);

            // printf("grade: %s %s %s %d\n", firstName, lastName, courseName, grade);
            // printf("grade: %d %d\n", studentIndex, courseIndex);
            Grade_Student(studentSystem, courseIndex, studentIndex, grade);
        }
        else if((aveCommand || countCommand || topStudentCommand) && wordCount >= 2){
            char courseName[MAX_COURSE_NAME_LENGTH];
            Merge_String(1, wordCount-1, MAX_QUERY_LENGTH, splicedQuery, MAX_COURSE_NAME_LENGTH, courseName);
            int courseIndex = Get_CourseIndex(courses, courseName);

            // printf("ave, count, topstudent: %s\n", courseName);
            if(aveCommand){
                float courseAvg = Get_CourseAvg(studentSystem, courseIndex);
                if(courseAvg == INVALID) printf("0\n");
                else printf("%0.2f\n", courseAvg);
            }

            if(countCommand) printf("%d\n", Get_NumStudentsEnrolled(studentSystem, courseIndex));

            if(topStudentCommand){
                int topStudentIds[numStudents];
                int numTopStudents = Get_TopStudentsInCourse(studentSystem, courseIndex, topStudentIds);
                if(numTopStudents == 0) printf("N/A\n");
                else Print_StudentsWithId(students, numTopStudents, topStudentIds, PRINT_LAST_NAME);
            }
        }
        else if((gpaCommand || findMutualCommand || listCoursesCommand) && wordCount >= 3){
            char *firstName = splicedQuery[1];
            char *lastName = splicedQuery[2];

            int studentIndex = Get_StudentIndex(students, firstName, lastName);

            // printf("gpa, findmutual, listcourses: %s %s\n", firstName, lastName);
            if(gpaCommand){
                float studentGpa = Get_StudentAvg(studentSystem, studentIndex);
                if(studentGpa == INVALID) printf("0\n");
                else printf("%0.2f\n", studentGpa);
            }

            if(findMutualCommand){
                int mutualStudentIds[numStudents];
                int numMutualStudents = Get_StudentsInMutualCourses(studentSystem, studentIndex, mutualStudentIds);
                if(numMutualStudents == 0) printf("N/A\n");
                else Print_StudentsWithId(students, numMutualStudents, mutualStudentIds, PRINT_LAST_NAME);
            }

            if(listCoursesCommand){
                int courseIds[numCourses];
                int numEnrolledCourses = Get_CoursesEnrolled(studentSystem, studentIndex, courseIds);
                if(numEnrolledCourses == 0) printf("N/A\n");
                else Print_CoursesWithId(courses, numEnrolledCourses, courseIds);
            }
        }
        else if(findFirstNamesCommand && wordCount >= 2){
            char *lastName = splicedQuery[1];
            int studentIds[numStudents];
            int numStudentsWithLastName = Get_StudentsWithLastName(students, lastName, studentIds);
            if(numStudentsWithLastName == 0) printf("N/A\n");
            else Print_StudentsWithId(students, numStudentsWithLastName, studentIds, DO_NOT_PRINT_LAST_NAME);
        }

        // Print_System(studentSystem);
    } while(strcmp("quit", splicedQuery[0]) != STRCMP_EQUAL);


    return 0;
}
