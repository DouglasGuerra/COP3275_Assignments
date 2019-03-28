#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 10000
#define MAX_WORDS_IN_WORD_ARRAY 20
#define NULL_CHARACTER 0
#define STRMCP_EQUAL 0
#define INVALID -1

#define WITH_LAST_NAME true
#define WITHOUT_LAST_NAME false

#define QUERY_COMMAND_INDEX 0

typedef struct{
    char data[MAX_STRING_LENGTH];
    int length;
} Word_t;

typedef struct{
    Word_t words[MAX_WORDS_IN_WORD_ARRAY];
    int size;
} WordArray_t;

typedef struct{
    _Bool enrolled;
    _Bool graded;
    int grade;
} SystemEntry_t;

typedef struct{
    Word_t firstName;
    Word_t lastName;
    int studentId;
} Student_t;

typedef struct{
    Word_t name;
    int courseId;
} Course_t;

/******************************************************
* Functions for word manipulation
******************************************************/
void Clear_Word(Word_t *word){
    memset(word->data, 0, MAX_STRING_LENGTH);
    word->length = 0;
}

void Clear_WordArray(WordArray_t *wordArray){
    int i;
    for(i = 0; i < MAX_WORDS_IN_WORD_ARRAY; i++)
        Clear_Word(&wordArray->words[i]);
}

void Copy_Word(Word_t *target, Word_t source){
    int i;
    for(i = 0; i < source.length; i++)
        target->data[i] = source.data[i];
}

void Append_Word(Word_t *target, Word_t source){
    int i;
    for(i = 0; i < source.length; i++)
        target->data[target->length++] = source.data[i];
}

void Append_Char(Word_t *target, const char source){
    target->data[target->length++] = source;
}

void Splice_Word(WordArray_t *splicedWords, Word_t inputWord){
    int storeIndex = 0, dataIndex = 0;
    char word[MAX_STRING_LENGTH];
    Clear_WordArray(splicedWords);

    int index;
    for(index = 0; index < inputWord.length; index++){
        if(inputWord.data[index] == ' '){
            if(dataIndex > 0) splicedWords->words[storeIndex++].length = dataIndex;
            dataIndex = 0;
        }
        else{
            splicedWords->words[storeIndex].data[dataIndex++] = inputWord.data[index];
        }
    }
    if(dataIndex > 0) splicedWords->words[storeIndex++].length = dataIndex;
    splicedWords->size = storeIndex;
}

Word_t Merge_Words(int startIndex, int stopIndex, WordArray_t *wordArray){
    Word_t mergedWord;
    Clear_Word(&mergedWord);

    int index;
    for(index = startIndex; index <= stopIndex; index++){
        Append_Word(&mergedWord, wordArray->words[index]);
        if(index != stopIndex) Append_Char(&mergedWord, ' ');
    }
    return mergedWord;
}

void Convert_WordToLowercase(Word_t *inputWord){
    int diff = 'A' - 'a';
    int index;
    for(index = 0; index < inputWord->length; index++){
        if(inputWord->data[index] >= 'A' && inputWord->data[index] <= 'Z')
            inputWord->data[index] -= diff;
    }
}

int Convert_WordToInt(Word_t *inputWord){
    int number = 0;
    int index;
    for(index = 0; index < inputWord->length; index++){
        if(inputWord->data[index] >= '0' && inputWord->data[index] <= '9'){
            number *= 10;
            number += (int)inputWord->data[index] - '0';
        }
    }
    return number;
}

void Print_Word(Word_t word){
    printf("data: %s\tlength: %d\n", word.data, word.length);
}

void Print_WordArray(WordArray_t words){
    int i;
    for(i = 0; i < words.size; i++) Print_Word(words.words[i]);
}

/*****************************************************
* Functions for I/O
******************************************************/
void Get_NextUserInput(Word_t *word){
    Clear_Word(word);
    char readInChar;

    scanf(" %c", &readInChar);
    while(readInChar != '\n' && word->length < MAX_WORDS_IN_WORD_ARRAY){
        word->data[word->length] = readInChar;
        word->length = word->length + 1;
        scanf("%c", &readInChar);
    }

    Convert_WordToLowercase(word);
}

/*****************************************************
* Functions for students structure
*****************************************************/
void Init_Students(int size, Student_t students[size]){
    int index;
    for(index = 0; index < size; index++){
        Clear_Word(&students[index].firstName);
        Clear_Word(&students[index].lastName);
        students[index].studentId = 0;
    }
}

void Fill_StudentsWithUserInput(int size, Student_t students[size]){
    Word_t inputWord;
    WordArray_t splicedInputWord;

    int index;
    for(index = 0; index < size; index++){
        Get_NextUserInput(&inputWord);
        Splice_Word(&splicedInputWord, inputWord);

        Copy_Word(&students[index].firstName, splicedInputWord.words[0]);
        Copy_Word(&students[index].lastName, splicedInputWord.words[1]);
        students[index].studentId = index;
    }
}

int Get_StudentId(int size, Student_t students[size], const char *firstName, const char *lastName){
    int index;
    for(index = 0; index < size; index++){
        _Bool sameFirstName = (strcmp(students[index].firstName.data, firstName) == STRMCP_EQUAL);
        _Bool sameLastName = (strcmp(students[index].lastName.data, lastName) == STRMCP_EQUAL);
        if(sameFirstName && sameLastName)
            return students[index].studentId;
    }
    return INVALID;
}

int Get_StudentsWithLastName(const char *lastName, int size, int studentIds[], Student_t students[]){
    int studentCount = 0;

    int index;
    for(index = 0; index < size; index++){
        _Bool IsSameLastName = (strcmp(students[index].lastName.data, lastName) == STRMCP_EQUAL);
        if(IsSameLastName){
            studentIds[studentCount++] = index;
        }
    }
    return studentCount;
}

void Print_StudentNamesWithId(int size, _Bool printLastName, int studentIds[], Student_t students[]){
    int index;
    for(index = 0; index < size; index++){
        if(index != 0) printf(", ");
        printf("%s", students[studentIds[index]].firstName.data);
        if(printLastName) printf(" %s", students[studentIds[index]].lastName.data);
    }
    printf("\n");
}

void Print_Students(int size, Student_t students[size]){
    printf("-------------------------------------------------------------\n");
    int i;
    for(i = 0; i < size; i++)
        printf("student name: %s %s\tid: %d\n", students[i].firstName.data, students[i].lastName.data, students[i].studentId);
    printf("\n");
}

/*****************************************************
* Functions for courses structure
*****************************************************/
void Init_Courses(int size, Course_t courses[size]){
    int index;
    for(index = 0; index < size; index++){
        Clear_Word(&courses[index].name);
        courses[index].courseId = 0;
    }
}

void Fill_CoursesWithUserInput(int size, Course_t courses[size]){
    Word_t inputWord;

    int index;
    for(index = 0; index < size; index++){
        Get_NextUserInput(&inputWord);

        Copy_Word(&courses[index].name, inputWord);
        courses[index].courseId = index;
    }
}

int Get_CourseId(int size, Course_t courses[size], const char *courseName){
    int index;
    for(index = 0; index < size; index++){
        if(strcmp(courses[index].name.data, courseName) == STRMCP_EQUAL)
            return courses[index].courseId;
    }
    return INVALID;
}

void Print_CourseNameWithId(int numCoursesToPrint, int courseIds[], Course_t courses[]){
    int index;
    for(index = 0; index < numCoursesToPrint; index++){
        if(index != 0) printf(", ");
        printf("%s", courses[courseIds[index]].name.data);
    }
    printf("\n");
}

void Print_Courses(int size, Course_t courses[size]){
    printf("-------------------------------------------------------------\n");
    int i;
    for(i = 0; i < size; i++)
        printf("course name: %s\tid: %d\n", courses[i].name.data, courses[i].courseId);
    printf("\n");
}

/*****************************************************
* Functions for courses structure
*****************************************************/
void Init_ManagementSystem(int numCourses, int numStudents, SystemEntry_t managementSystem[numCourses][numStudents]){
    int courseIndex, studentIndex;
    for(courseIndex = 0; courseIndex < numCourses; courseIndex++){
        for(studentIndex = 0; studentIndex < numStudents; studentIndex++){
            managementSystem[courseIndex][studentIndex].enrolled = false;
            managementSystem[courseIndex][studentIndex].graded = false;
            managementSystem[courseIndex][studentIndex].grade = 0;
        }
    }
}

_Bool Is_ValidId(int id, int maxId){
    if(id >= 0 && id < maxId) return true;
    else return false;
}

void Enroll_StudentInCourse(int courseId, int studentId, int numCourses, int numStudents, SystemEntry_t managementSystem[numCourses][numStudents]){
    if(Is_ValidId(courseId, numCourses) && Is_ValidId(studentId, numStudents)){
        if(!managementSystem[courseId][studentId].enrolled){
            managementSystem[courseId][studentId].enrolled = true;
            managementSystem[courseId][studentId].graded = false;
            managementSystem[courseId][studentId].grade = 0;
        }
    }
}

void UnEnroll_StudentInCourse(int courseId, int studentId, int numCourses, int numStudents, SystemEntry_t managementSystem[numCourses][numStudents]){
    if(Is_ValidId(courseId, numCourses) && Is_ValidId(studentId, numStudents)){
        managementSystem[courseId][studentId].enrolled = false;
        managementSystem[courseId][studentId].graded = false;
        managementSystem[courseId][studentId].grade = 0;
    }
}

void Grade_StudentInCourse(int courseGrade, int courseId, int studentId, int numCourses, int numStudents, SystemEntry_t managementSystem[numCourses][numStudents]){
    if(Is_ValidId(courseId, numCourses) && Is_ValidId(studentId, numStudents)){
        if(managementSystem[courseId][studentId].enrolled){
            managementSystem[courseId][studentId].graded = true;
            managementSystem[courseId][studentId].grade = courseGrade;
        }
    }
}

float Get_CourseGradeAverage(int courseId, int numCourses, int numStudents, SystemEntry_t managementSystem[numCourses][numStudents]){
    float avg = INVALID;
    int numOfStudents = 0, totalGrade = 0;

    if(Is_ValidId(courseId, numCourses)){
        int studentIndex;
        for(studentIndex = 0; studentIndex < numStudents; studentIndex++){
            if(managementSystem[courseId][studentIndex].graded){
                totalGrade += managementSystem[courseId][studentIndex].grade;
                numOfStudents++;
            }
        }
    }

    if(numOfStudents > 0) avg = (float) totalGrade / (float) numOfStudents;
    return avg;
}

float Get_StudentGpa(int studentId, int numCourses, int numStudents, SystemEntry_t managementSystem[numCourses][numStudents]){
    float avg = INVALID;
    int numOfCourses = 0, totalGrade = 0;

    if(Is_ValidId(studentId, numStudents)){
        int courseIndex;
        for(courseIndex = 0; courseIndex < numCourses; courseIndex++){
            if(managementSystem[courseIndex][studentId].graded){
                totalGrade += managementSystem[courseIndex][studentId].grade;
                numOfCourses++;
            }
        }
    }

    if(numOfCourses > 0) avg = (float)totalGrade / (float)numOfCourses;
    return avg;
}

int Get_TopGpaInCourse(int courseId, int numCourses, int numStudents, SystemEntry_t managementSystem[numCourses][numStudents]){
    int topGpa = 0, studentCount = 0;

    if(Is_ValidId(courseId, numCourses)){
        int studentIndex;
        for(studentIndex = 0; studentIndex < numStudents; studentIndex++){
            if(managementSystem[courseId][studentIndex].graded){
                studentCount++;
                if(managementSystem[courseId][studentIndex].grade > topGpa)
                    topGpa = managementSystem[courseId][studentIndex].grade;
            }
        }
    }

    if(studentCount > 0) return topGpa;
    else return INVALID;
}

int Get_TopStudentsInCourse(int courseId, int numCourses, int numStudents, int studentIds[], SystemEntry_t managementSystem[numCourses][numStudents]){
    int topGpa = Get_TopGpaInCourse(courseId, numCourses, numStudents, managementSystem);
    int studentCount = 0;

    if(topGpa != INVALID && Is_ValidId(courseId, numCourses)){
        int studentIndex;
        for(studentIndex = 0; studentIndex < numStudents; studentIndex++){
            if(managementSystem[courseId][studentIndex].graded && managementSystem[courseId][studentIndex].grade >= topGpa){
                studentIds[studentCount++] = studentIndex;
            }
        }
    }

    return studentCount;
}

int Get_CoursesStudentIsEnrolledIn(int studentId, int numCourses, int numStudents, int courseIds[], SystemEntry_t managementSystem[numCourses][numStudents]){
    int courses = 0;

    if(Is_ValidId(studentId, numStudents)){
        int courseIndex;
        for(courseIndex = 0; courseIndex < numCourses; courseIndex++){
            if(managementSystem[courseIndex][studentId].enrolled){
                courseIds[courses++] = courseIndex;
            }
        }
    }

    return courses;
}

int Get_StudentsInTheSameCourse(int studentId, int numCourses, int numStudents, int studentIds[], SystemEntry_t managementSystem[numCourses][numStudents]){
    int students = 0;
    _Bool studentIdsFound[numStudents];

    if(Is_ValidId(studentId, numStudents)){
        int courseIndex, studentIndex;
        for(courseIndex = 0; courseIndex < numCourses; courseIndex++){
            for(studentIndex = 0; studentIndex < numStudents; studentIndex++){
                _Bool IsSameStudent = (studentId == studentIndex);
                _Bool StudentIsEnrolledInCourse = (managementSystem[courseIndex][studentId].enrolled);
                _Bool OtherStudentIsEnrolledInCourse = (managementSystem[courseIndex][studentIndex].enrolled);
                _Bool OtherStudentIsAlreadyStored = (studentIdsFound[studentIndex]);

                if(!IsSameStudent && !OtherStudentIsAlreadyStored && StudentIsEnrolledInCourse && OtherStudentIsEnrolledInCourse){
                    studentIds[students++] = studentIndex;
                    studentIdsFound[studentIndex] = true;
                }
            }
        }
    }

    return students;
}

int Get_NumOfStudentsEnrolledInCourse(int courseId, int numCourses, int numStudents, SystemEntry_t managementSystem[numCourses][numStudents]){
    int numStudentsEnrolled = 0;

    if(Is_ValidId(courseId, numCourses)){
        int studentIndex;
        for(studentIndex = 0; studentIndex < numStudents; studentIndex++){
            if(managementSystem[courseId][studentIndex].enrolled) numStudentsEnrolled++;
        }
    }

    return numStudentsEnrolled;
}

void Print_ManagementSystem(int rowSize, int colSize, SystemEntry_t managementSystem[rowSize][colSize]){
    printf("-------------------------------------------------------------\n");
    int rowIndex, colIndex;
    for(rowIndex = 0; rowIndex < rowSize; rowIndex++){
        for(colIndex = 0; colIndex < colSize; colIndex++){
            printf("%d %d\t", managementSystem[rowIndex][colIndex].enrolled, managementSystem[rowIndex][colIndex].grade);
        }
        printf("\n");
    }
    printf("\n");
}

int main(){

    int numStudents, numCourses;
    scanf("%d", &numStudents);
    scanf("%d", &numCourses);

    Student_t students[numStudents];
    Course_t courses[numCourses];
    SystemEntry_t managementSystem[numCourses][numStudents];

    Init_Students(numStudents, students);
    Fill_StudentsWithUserInput(numStudents, students);
    // Print_Students(numStudents, students);

    Init_Courses(numCourses, courses);
    Fill_CoursesWithUserInput(numCourses, courses);
    // Print_Courses(numCourses, courses);

    Init_ManagementSystem(numCourses, numStudents, managementSystem);
    // Print_ManagementSystem(numCourses, numStudents, managementSystem);

    // printf("------------- starting menu ------------------------\n");
    Word_t userInput;
    WordArray_t splicedUserInput;
    while(1){
        Get_NextUserInput(&userInput);
        Splice_Word(&splicedUserInput, userInput);

        const char* command = splicedUserInput.words[QUERY_COMMAND_INDEX].data;
        _Bool quitCommand = (strcmp("quit", command) == STRMCP_EQUAL);
        _Bool enrollCommand = (strcmp("enroll", command) == STRMCP_EQUAL);
        _Bool unenrollCommand = (strcmp("unenroll", command) == STRMCP_EQUAL);
        _Bool gradeCommand = (strcmp("grade", command) == STRMCP_EQUAL);
        _Bool aveCommand = (strcmp("ave", command) == STRMCP_EQUAL);
        _Bool gpaCommand = (strcmp("gpa", command) == STRMCP_EQUAL);
        _Bool countCommand = (strcmp("count", command) == STRMCP_EQUAL);
        _Bool topStudentCommand = (strcmp("topstudent", command) == STRMCP_EQUAL);
        _Bool findMutualCommand = (strcmp("findmutual", command) == STRMCP_EQUAL);
        _Bool listCoursesCommand = (strcmp("listcourses", command) == STRMCP_EQUAL);
        _Bool findFirstNamesCommand = (strcmp("findfirstnames", command) == STRMCP_EQUAL);

        if(quitCommand)
            break;
        else if(enrollCommand || unenrollCommand){
            char *studentFirstName = splicedUserInput.words[1].data;
            char *studentLastName = splicedUserInput.words[2].data;
            int studentId = Get_StudentId(numStudents, students, studentFirstName, studentLastName);

            Word_t courseName = Merge_Words(3, splicedUserInput.size-1, &splicedUserInput);
            int courseId = Get_CourseId(numCourses, courses, courseName.data);

            if(enrollCommand)
                Enroll_StudentInCourse(courseId, studentId, numCourses, numStudents, managementSystem);
            if(unenrollCommand)
                UnEnroll_StudentInCourse(courseId, studentId, numCourses, numStudents, managementSystem);
        }
        else if(gradeCommand){
            char *studentFirstName = splicedUserInput.words[1].data;
            char *studentLastName = splicedUserInput.words[2].data;
            int studentId = Get_StudentId(numStudents, students, studentFirstName, studentLastName);

            Word_t courseName = Merge_Words(3, splicedUserInput.size-2, &splicedUserInput);
            int courseId = Get_CourseId(numCourses, courses, courseName.data);
            int grade = Convert_WordToInt(&splicedUserInput.words[splicedUserInput.size-1]);

            Grade_StudentInCourse(grade, courseId, studentId, numCourses, numStudents, managementSystem);
        }
        else if(aveCommand || countCommand || topStudentCommand){
            Word_t courseName = Merge_Words(1, splicedUserInput.size-1, &splicedUserInput);
            int courseId = Get_CourseId(numCourses, courses, courseName.data);

            if(aveCommand){
                float average = Get_CourseGradeAverage(courseId, numCourses, numStudents, managementSystem);
                if(average == INVALID) printf("N/A\n");
                else printf("%0.2f\n", average);
            }
            else if(countCommand){
                int numStudentsEnrolled = Get_NumOfStudentsEnrolledInCourse(courseId, numCourses, numStudents, managementSystem);
                printf("%d\n", numStudentsEnrolled);
            }
            else if(topStudentCommand){
                int topStudentsId[numStudents];
                int numTopStudents = Get_TopStudentsInCourse(courseId, numCourses, numStudents, topStudentsId, managementSystem);
                if(numTopStudents > 0) Print_StudentNamesWithId(numTopStudents, WITH_LAST_NAME, topStudentsId, students);
                else printf("N/A\n");
            }
        }
        else if(gpaCommand || findMutualCommand || listCoursesCommand){
            char *studentFirstName = splicedUserInput.words[1].data;
            char *studentLastName = splicedUserInput.words[2].data;
            int studentId = Get_StudentId(numStudents, students, studentFirstName, studentLastName);

            if(gpaCommand){
                float studentGpa = Get_StudentGpa(studentId, numCourses, numStudents, managementSystem);
                if(studentGpa == INVALID) printf("0\n");
                else printf("%0.2f\n", studentGpa);
            }
            else if(findMutualCommand){
                int mutualStudentsId[numStudents];
                int numMutualStudents = Get_StudentsInTheSameCourse(studentId, numCourses, numStudents, mutualStudentsId, managementSystem);
                if(numMutualStudents > 0) Print_StudentNamesWithId(numMutualStudents, WITH_LAST_NAME, mutualStudentsId, students);
                else printf("N/A\n");
            }
            else if(listCoursesCommand){
                int coursesId[numCourses];
                int numCoursesEnrolled = Get_CoursesStudentIsEnrolledIn(studentId, numCourses, numStudents, coursesId, managementSystem);
                if(numCoursesEnrolled > 0) Print_CourseNameWithId(numCoursesEnrolled, coursesId, courses);
                else printf("N/A\n");
            }
        }
        else if(findFirstNamesCommand){
            char *lastName = splicedUserInput.words[1].data;

            int studentsId[numStudents];
            int numStudentsWithSameName = Get_StudentsWithLastName(lastName, numStudents, studentsId, students);
            if(numStudentsWithSameName > 0) Print_StudentNamesWithId(numStudentsWithSameName, WITHOUT_LAST_NAME, studentsId, students);
            else printf("N/A\n");
        }

        // Print_ManagementSystem(numCourses, numStudents, managementSystem);
    }

    return 0;
}
