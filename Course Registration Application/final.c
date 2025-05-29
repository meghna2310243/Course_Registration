#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINE_LENGTH 1000
#define MAX_COURSES 100
#define MAX_CHOICE 50
#define MAX_LENGTH 100
#define MAX_STUDENTS 100
#define MAX_COURSE 26
#define MAX_CHOICES 5
#define MIN_COURSES 4
#define MAX_LINE_LENGTHS 1024
#define MAX_NAME_LENGTH 100

struct StudentDetails{
    int serialNo;
    char name[MAX_LINE_LENGTH];
    char studentID[MAX_LINE_LENGTH];
    char prerequisites[MAX_LINE_LENGTH];
    float cgpa;
    int attendance;
    float rankingScore;
    int ranking;
    int choices[MAX_CHOICES];
    int course_allocated[MAX_CHOICES];
    int num_choices;
    int allocated_course[MAX_CHOICES];
    int course_specific_rank[MAX_COURSES];
};

struct Course1 {
    int sno;
    char name[MAX_LINE_LENGTH];
    char code[MAX_LINE_LENGTH];
    char faculty_id[MAX_LINE_LENGTH];
    int available_seats;
    int total_seats;
};

// Structure for login-related student information
struct LoginStudent {
    char name[MAX_LENGTH];
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
};

// Struct to store course details
struct Course {
    int sno;
    char name[MAX_LINE_LENGTH];
    char courseID[MAX_LINE_LENGTH];
    char facultyID[MAX_LINE_LENGTH];
    int credits;
    char prerequisite[MAX_LINE_LENGTH];
};

// Struct to store course details
struct Course2 {
    int sno;
    char name[MAX_LINE_LENGTH];
    char courseID[MAX_LINE_LENGTH];
    char facultyID[MAX_LINE_LENGTH];
    int seatsAvailable;
};

// Struct to store student details
struct Student {
    char name[MAX_LINE_LENGTH];
    int allottedCourses[MAX_COURSES];
    int numCourses;
    int waitlistedCourses[MAX_COURSES];
    int numWaitlistedCourses;
};

// Struct to store final accepted courses for a student
struct AcceptedCourses {
    char name[MAX_LINE_LENGTH];
    int acceptedCourses[MAX_COURSES];
    int numAcceptedCourses;
};

struct Course3 {
    int sno;
    char name[MAX_LINE_LENGTH];
    char courseID[MAX_LINE_LENGTH];
    char facultyID[MAX_LINE_LENGTH];
    int seatsAvailable;
};

// Struct to store student details
struct Student3 {
    char name[MAX_LINE_LENGTH];
    int waitlistedCourses[MAX_COURSES];
    int numWaitlistedCourses;
};

struct Course4 {
    int sno;
    char course_name[MAX_LINE_LENGTHS];
    char course_id[MAX_LINE_LENGTHS];
    char faculty_id[MAX_LINE_LENGTHS];
};

struct Student4 {
    char name[MAX_LINE_LENGTHS];
    int allocated_courses[MAX_COURSES];
    int num_allocated_courses;
};

struct Course5 {
    int sno;
    char course_name[MAX_LINE_LENGTHS];
    char course_id[MAX_LINE_LENGTHS];
    char faculty_id[MAX_LINE_LENGTHS];
};

struct Course6 {
    int sno;
    char name[50];
    char courseID[10];
    int recommendationPercentage;
};

// Function prototypes
void registerUser();
int loginUser();
int usernameExists(const char *username);
void parse_course(char *line, struct Course *course);
void display_courses(struct Course *courses, int num_courses);
int check_prerequisites(struct Course course, char *completedCourses);
void choiceFilling(struct Course *courses, int num_courses);
void parse_student(char *line, struct StudentDetails *student);
void calculate_ranking_score(struct StudentDetails *students, int num_students);
int compare_students(const void *a, const void *b);
void parse_courses(char *line, struct Course1 *course);
void update_choices(struct StudentDetails *students, int num_students);
void reduce_available_seats(struct Course1 *courses, int num_courses, int course_code);
struct Course1* find_course_by_sno(struct Course1 *courses, int num_courses, int sno);
void rank_students_for_courses(struct StudentDetails *students, int num_students, struct Course1 *courses, int num_courses);
int allotment();
int count_lines_in_choicelist();
void loadCourses(struct Course2 *courses, int *num_courses);
void loadChoiceList(struct Student *students, int *num_students);
void loadWaitlist(struct Student *students, int num_students);
void displayStudentCourses(struct Student student, struct Course2 *courses, int num_courses);
void updateSeats(struct Course2 *courses, int num_courses, int courseID, int change);
void printFinalAllottedCourses(struct AcceptedCourses acceptedCourses, struct Course2 *courses, int num_courses, struct Student student);
void updateRemainingSeatsFile(struct Course2 *courses, int num_courses);
void appendFinalAllottedCourses(struct AcceptedCourses acceptedCourses);
int hasCompletedWithdrawal(char *studentName);
int withdraw();
int countLinesInFinalAllotment();
void loadCourses3(struct Course3 *courses, int *num_courses);
void loadWaitlist3(struct Student3 *students, int *num_students);
void processWaitlist3(struct Student3 *students, int num_students, struct Course3 *courses, int num_courses, int successfulAllocations[MAX_STUDENTS][MAX_COURSES]);
void updateRemainingSeatsFile3(struct Course3 *courses, int num_courses);
void appendFinalAllottedCourses3(const char *studentName, int courseID);
void updateWaitlistFile3(struct Student3 *students, int num_students);
void writeSuccessfulWaitlist3(const struct Student3 *students, int num_students, const int successfulAllocations[][MAX_COURSES]);
void ensureMinimumCourses3();
int waitlist();
int readCourses(struct Course4 courses[]);
int readFinalAllotment(struct Student4 students[]);
void printStudentCourseDetails(struct Course4 courses[], int num_courses, struct Student4 students[], int num_students);
int printfinal();
int readCourses5(struct Course5 courses[]);
struct Course5 *findCourseBySno5(struct Course5 courses[], int num_courses, int sno);
void printCourseDetails5(int sno, struct Course5 *course);
void printStudentWaitlistDetails5(struct Course5 courses[], int num_courses);
int printwaitlist();
void printTop5Recommendations();

// Random course IDs to be used for filling up to 4 courses
int randomCourseIDs[] = {1, 2, 3, 4, 5, 6};
int randomCourseCount = 6;

int main() {
    printf("\033[1;97m\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\033[0m");
    printf("\033[101m\033[1;97m\n\t\t WELCOME TO COURSE REGISTRATION PORTAL! \033[0m\n");
    int choice;
    int login_choice;
    char another;
    char completedCourses[MAX_LINE_LENGTH] = "";
    char prerequisiteIds[MAX_LINE_LENGTH] = ""; // Variable to store prerequisite IDs
    int login;
    int choiceno;
    int allottno;
    int result1;
    int result2;
    int result3;
    int final;
    int pw;
    int flag=0;

    FILE *coursesFile = fopen("Courses.csv", "r");
    if (!coursesFile) {
        printf("Error opening Courses file.\n");
        return 1;
    }

    struct Course courses[MAX_COURSES];
    int num_courses = 0;

    char line[MAX_LINE_LENGTH];
    fgets(line, sizeof(line), coursesFile); // Skip header line

    // Read and parse each line of the Courses file
    while (fgets(line, sizeof(line), coursesFile) && num_courses < MAX_COURSES) {
        parse_course(line, &courses[num_courses]);
        num_courses++;
    }

    fclose(coursesFile);

    do {
        printf("\033[1;97m\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\033[0m");
        printf("\033[1;34m\nMAIN MENU:\033[0m");
        printf("\033[1;33m\n1. Enter\n2. Exit\n\033[0m");
        printf("\nEnter your CHOICE: ");
        scanf("%d", &choice);
        getchar();

        if (choice == 1) {
            login=loginUser();
            if(login==1){
            do {
                printf("\033[1;33m\n1. Choice Filling\n2. Check Seat Allotment Status\n3. Exit\n\033[0m");
                printf("\nEnter your CHOICE: ");
                scanf("%d", &login_choice);
                getchar();
            
                switch (login_choice) {
                    case 1:
                        printf("\n\t\t\033[103m\033[30m CHOICE FILLING PORTAL \033[0m\n\n");
                        choiceFilling(courses, num_courses);
                        break;
                    case 2:
                        printf("\n\t\t\033[103m\033[30m SEAT ALLOTTMENT STATUS \033[0m\n\n");
                        if(flag==1 || flag==2)
                        {
                            result2=withdraw();
                            flag=2;
                        }
                        else if(flag==3)
                        {
                            pw=printwaitlist();
                        }
                        else{
                        printf("\033[1;31mSeat allotment is not done yet.\n\033[0m");
                        }
                        break;
                    case 3:
                        printf("\033[1;31mLogging out...\n\033[0m");
                        choiceno=count_lines_in_choicelist();
                        if((choiceno)>=10 && flag==0)
                        {
                            result1=allotment();
                            flag=1;
                        }
                        choiceno=count_lines_in_choicelist();
                        allottno=countLinesInFinalAllotment();
                        if(allottno>=choiceno && flag==2)
                        {
                            result3=waitlist();
                            flag=3;
                        }
                        break;
                    default:
                        printf("\033[1;31mInvalid choice\n\033[0m");
                }
            } while (login_choice != 3);}
        } else if (choice == 2) {
            printf("\033[1;31mExiting...\n\033[0m");
            final=printfinal();
            
        } else {
            printf("\033[1;31mInvalid choice\n\033[0m");
        }
    } while (choice != 2);

    return 0;
}

void parse_student(char *line, struct StudentDetails *student) {
    sscanf(line, "%d,%[^,],%[^,],%[^,],%f,%d",
           &student->serialNo, student->name, student->studentID, student->prerequisites, &student->cgpa, &student->attendance);
}

void calculate_ranking_score(struct StudentDetails *students, int num_students) {
    for (int i = 0; i < num_students; i++) {
        students[i].rankingScore = 0.8 * students[i].cgpa + 0.2 * students[i].attendance;
    }
}

int compare_students(const void *a, const void *b) {
    const struct StudentDetails *studentA = (const struct StudentDetails *)a;
    const struct StudentDetails *studentB = (const struct StudentDetails *)b;
    if (studentA->rankingScore < studentB->rankingScore) {
        return 1; // Return 1 for descending order (highest first)
    } else if (studentA->rankingScore > studentB->rankingScore) {
        return -1; // Return -1 for descending order (highest first)
    }
    return 0;
}

void parse_courses(char *line, struct Course1 *course) {
    sscanf(line, "%d,%[^,],%[^,],%[^,],%d", &course->sno, course->name, course->code, course->faculty_id, &course->available_seats);
    course->total_seats = course->available_seats;
}

void update_choices(struct StudentDetails *students, int num_students) {
    FILE *fp_choicelist = fopen("choicelist.csv", "r");
    if (fp_choicelist == NULL) {
        fprintf(stderr, "Error opening choicelist.csv\n");
        return;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, fp_choicelist)) {
        line[strcspn(line, "\n")] = '\0';

        char name[MAX_LINE_LENGTH];
        int choices[MAX_CHOICES];
        sscanf(line, "%[^,],%d,%d,%d,%d,%d", name, &choices[0], &choices[1], &choices[2], &choices[3], &choices[4]);

        for (int i = 0; i < num_students; i++) {
            if (strcmp(name, students[i].name) == 0) {
                memcpy(students[i].choices, choices, sizeof(choices));
                students[i].num_choices = MAX_CHOICES;
                break;
            }
        }
    }

    fclose(fp_choicelist);
}

void reduce_available_seats(struct Course1 *courses, int num_courses, int course_code) {
    for (int i = 0; i < num_courses; i++) {
        if (courses[i].sno == course_code) {
            courses[i].available_seats--;
            break;
        }
    }
}

struct Course1* find_course_by_sno(struct Course1 *courses, int num_courses, int sno) {
    for (int i = 0; i < num_courses; i++) {
        if (courses[i].sno == sno) {
            return &courses[i];
        }
    }
    return NULL;
}

void rank_students_for_courses(struct StudentDetails *students, int num_students, struct Course1 *courses, int num_courses) {
    for (int i = 0; i < num_courses; i++) {
        int course_code = courses[i].sno;

        struct StudentDetails *course_students[MAX_STUDENTS];
        int num_course_students = 0;
        for (int j = 0; j < num_students; j++) {
            for (int k = 0; k < students[j].num_choices; k++) {
                if (students[j].choices[k] == course_code) {
                    course_students[num_course_students++] = &students[j];
                    break;
                }
            }
        }

        qsort(course_students, num_course_students, sizeof(struct StudentDetails *), compare_students);

        for (int j = 0; j < num_course_students; j++) {
            course_students[j]->course_specific_rank[i] = j + 1;
        }
    }
}



void parse_course(char *line, struct Course *course) {
    sscanf(line, "%d,%[^,],%[^,],%[^,],%d,%[^\n]",
           &course->sno, course->name, course->courseID, course->facultyID, &course->credits, course->prerequisite);
}


void display_courses(struct Course *courses, int num_courses) {
    printf("\033[1;97mS.No\tCOURSE NAME\t\tCOURSE ID\tFACULTY ID\tCREDITS\tPREREQUISITE\n\033[0m");
    for (int i = 0; i < num_courses; i++) {
        printf("%d\t%-20s\t%-10s\t%-10s\t%d\t%s\n", courses[i].sno, courses[i].name, courses[i].courseID,
               courses[i].facultyID, courses[i].credits, courses[i].prerequisite);
    }
}

int check_prerequisites(struct Course course, char *completedCourses) {
    char *token;
    char prerequisiteIDs[MAX_LINE_LENGTH];
    strcpy(prerequisiteIDs, course.prerequisite);

    token = strtok(prerequisiteIDs, ",");
    while (token != NULL) {
        if (strstr(completedCourses, token) == NULL) {
            return 0; 
        }
        token = strtok(NULL, ",");
    }

    return 1; 
}

void registerUser() {
    struct LoginStudent newStudent;
    FILE *file;

    file = fopen("Login.csv", "a");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    printf("Enter Name: ");
    fgets(newStudent.name, MAX_LENGTH, stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = '\0';

    printf("Enter Username: ");
    fgets(newStudent.username, MAX_LENGTH, stdin);
    newStudent.username[strcspn(newStudent.username, "\n")] = '\0'; 

    if (usernameExists(newStudent.username)) {
        printf("Username already exists. Please try again with a different username.\n");
        fclose(file);
        return;
    }

    printf("Enter Password: ");
    fgets(newStudent.password, MAX_LENGTH, stdin);
    newStudent.password[strcspn(newStudent.password, "\n")] = '\0'; 

    fseek(file, 0, SEEK_END);
    if (ftell(file) > 0) {
        fprintf(file, "\n");
    }

    fprintf(file, "%s,%s,%s", newStudent.name, newStudent.username, newStudent.password);

    printf("Registration Successful!\n");

    fclose(file);
}

int loginUser() 
{
    struct LoginStudent student;
    char enteredUsername[MAX_LENGTH];
    char enteredPassword[MAX_LENGTH];
    FILE *file;

    file = fopen("Login.csv", "r");
    if (file == NULL) {
        perror("Error opening file");
    }

    printf("Enter Username: ");
    fgets(enteredUsername, MAX_LENGTH, stdin);
    enteredUsername[strcspn(enteredUsername, "\n")] = '\0'; 
    printf("Enter Password: ");
    fgets(enteredPassword, MAX_LENGTH, stdin);
    enteredPassword[strcspn(enteredPassword, "\n")] = '\0';

    char line[3 * MAX_LENGTH];
    int found = 0;

    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",");
        if (token != NULL) {
            strcpy(student.name, token); 
            token = strtok(NULL, ",");
            if (token != NULL) {
                strcpy(student.username, token);
                token = strtok(NULL, ",");
                if (token != NULL) {
                    strcpy(student.password, token);
                    // Remove newline character from password
                    student.password[strcspn(student.password, "\n")] = '\0'; 
                }
            }
        }

        if (strcmp(enteredUsername, student.username) == 0 && strcmp(enteredPassword, student.password) == 0) {
            found = 1;
            break;
        }
    }

    if (found) {
        printf("\033[1;97m\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\033[0m");
        printf("\033[1;97m\nWelcome %s!\n\033[0m", student.name); 
        return 1;
    } else {
        printf("\033[1;31mLogin Failed!\n\033[0m");
    }

    
    fclose(file);
}

int usernameExists(const char *username) 
{
    struct LoginStudent student;
    FILE *file = fopen("Login.csv", "r");
    if (file == NULL) {
        return 0; 
    }

    char line[3 * MAX_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",");
        if (token != NULL) {
           
            token = strtok(NULL, ",");
            if (token != NULL) {
                strcpy(student.username, token);
            }
        }

        if (strcmp(username, student.username) == 0) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

void choiceFilling(struct Course *courses, int num_courses) {
    FILE *choiceFile;
    char another = 'Y';
    char completedCourses[MAX_LINE_LENGTH] = "";
    char prerequisiteIds[MAX_LINE_LENGTH] = ""; 
    struct LoginStudent student;
    char enteredUsername[MAX_LENGTH];
    char enteredPassword[MAX_LENGTH];
    int choiceflag;

    FILE *file = fopen("Login.csv", "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    printf("Enter Username: ");
    fgets(enteredUsername, MAX_LENGTH, stdin);
    enteredUsername[strcspn(enteredUsername, "\n")] = '\0'; 

    printf("Enter Password: ");
    fgets(enteredPassword, MAX_LENGTH, stdin);
    enteredPassword[strcspn(enteredPassword, "\n")] = '\0'; 

    char line[3 * MAX_LENGTH];
    int found = 0;

    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",");
        if (token != NULL) {
            strcpy(student.name, token);
            token = strtok(NULL, ",");
            if (token != NULL) {
                strcpy(student.username, token);
                token = strtok(NULL, ",");
                if (token != NULL) {
                    strcpy(student.password, token);
                    student.password[strcspn(student.password, "\n")] = '\0'; 
                }
            }
        }

        if (strcmp(enteredUsername, student.username) == 0 && strcmp(enteredPassword, student.password) == 0) {
            found = 1;
            break;
        }
    }

    fclose(file);

    if (found) {
        printf("\033[1;97m\nWelcome %s!\n\n\033[0m", student.name);
        choiceFile = fopen("choicelist.csv", "r");
        if (choiceFile != NULL) {
            while (fgets(line, sizeof(line), choiceFile)) {
                char *token = strtok(line, ",");
                if (token != NULL && strcmp(token, student.name) == 0) {
                    printf("\033[1;31mYou have completed the choice filling process.\n\033[0m");
                    fclose(choiceFile);
                    return;
                }
            }
            fclose(choiceFile);
        }

        printf("\033[1;34mTOP 5 RECOMMENDATIONS:\n\033[0m");
        printTop5Recommendations();
        printf("\n");

        printf("\033[1;34mAVAILABLE COURSES:\n\033[0m");
        display_courses(courses, num_courses);

        while (another == 'Y' || another == 'y') {
            choiceflag=0;
            struct Course choices[MAX_CHOICE];
            int num_choices = 0;
            int total_credits = 0;

            printf("\nEnter the course IDs of all the courses you have completed: ");
            fgets(completedCourses, sizeof(completedCourses), stdin);
            if (completedCourses[strlen(completedCourses) - 1] == '\n') {
                completedCourses[strlen(completedCourses) - 1] = '\0';
            }

            strcpy(prerequisiteIds, completedCourses);

            while (1) {
                printf("\nHow many courses do you want to choose? (4 to 6): ");
                scanf("%d", &num_choices);

                if (num_choices < 4 || num_choices > 6) {
                    printf("\033[1;31mInvalid number of courses. Please enter a number between 4 and 6.\n\033[0m");
                    continue;
                }

                total_credits = 0;

                for (int i = 0; i < num_choices; i++) {
                    printf("\nEnter the S.No of COURSE %d: ", i + 1);
                    int selected_sno;
                    scanf("%d", &selected_sno);

                    if (selected_sno < 1 || selected_sno > num_courses) {
                        printf("\033[1;31mInvalid S.No. Please enter a valid S.No.\n\033[0m");
                        i--; // Decrement i to allow re-entry of current course
                        continue;
                    }

                    // Check if the course ID is already selected
                    int already_selected = 0;
                    for (int j = 0; j < i; j++) {
                        if (choices[j].sno == selected_sno) {
                            printf("\033[1;31mCourse with S.No %d is already selected.\n\033[0m", selected_sno);
                            already_selected = 1;
                            break;
                        }
                    }
                    if (already_selected) {
                        continue;
                    }

                    for (int j = 0; j < i; j++) {
                        if (strcmp(choices[j].courseID, courses[selected_sno - 1].courseID) == 0) {
                            printf("\033[1;31mCourse with Course ID %s is already selected.\n\033[0m", courses[selected_sno - 1].courseID);
                            i--; 
                            already_selected = 1;
                            break;
                        }
                    }
                    if (already_selected) {
                        continue;
                    }

                    if (!check_prerequisites(courses[selected_sno - 1], prerequisiteIds)) {
                        printf("\033[1;31mYou have not completed the prerequisites for this course.\n\033[0m");
                        i--;
                        continue;
                    }

                    choices[i] = courses[selected_sno - 1];
                    total_credits += choices[i].credits;

                    char removeOption;
                    printf("Continue or remove this course (C/R)? ");
                    scanf(" %c", &removeOption);
                    if (removeOption == 'R' || removeOption == 'r') {
                        i--;
                        printf("Course removed.\n");
                        continue;
                    }
                }

                printf("\033[1;34m\nSELECTED COURSES:\n\033[1;97m");
                display_courses(choices, num_choices);
                printf("\033[1;97mTotal credits: %d\n\033[0m", total_credits);
                choiceflag=1;

                char confirm;
                printf("\nDo you want to confirm your choices? (Y/N): ");
                scanf(" %c", &confirm);
                if (confirm == 'Y' || confirm == 'y') {
                    if (total_credits < 10 || total_credits > 20) {
                        printf("\033[1;31mError: Total credits must be between 10 and 20. Please choose again.\n\033[0m");
                        choiceflag=0;
                        break; 
                    }
                    break;
                }
            }

            printf("\nDo you want to fill choices again? (Y/N): ");
            scanf(" %c", &another);
            if(another=='Y'){choiceflag=0;}
            getchar(); 
            if(choiceflag==1){
            choiceFile = fopen("choicelist.csv", "a");
            if (choiceFile == NULL) {
                perror("Error opening choicelist.csv");
                return;
            }

            fprintf(choiceFile, "%s,", student.name);
            for (int i = 0; i < num_choices; i++) {
                fprintf(choiceFile, "%d", choices[i].sno);
                if (i < num_choices - 1) {
                    fprintf(choiceFile, ",");
                }
            }
            fprintf(choiceFile, "\n");
            fclose(choiceFile);}

            
        }
    } else {
        printf("\033[1;31mLogin failed.\n\033[0m");
    }
}

int allotment() {
    FILE *studentsFile = fopen("Students.csv", "r");
    if (!studentsFile) {
        printf("Error opening Students file.\n");
        return 1;
    }

    struct StudentDetails students[MAX_STUDENTS];
    int num_students = 0;

    char line[MAX_LINE_LENGTH];
    fgets(line, sizeof(line), studentsFile);
    while (fgets(line, sizeof(line), studentsFile) && num_students < MAX_STUDENTS) {
        parse_student(line, &students[num_students]);
        num_students++;
    }
    fclose(studentsFile);

    calculate_ranking_score(students, num_students);

    qsort(students, num_students, sizeof(struct StudentDetails), compare_students);
    for (int i = 0; i < num_students; i++) {
        students[i].ranking = i + 1;
    }

    update_choices(students, num_students);

    FILE *coursesFile = fopen("seats.csv", "r");
    if (coursesFile == NULL) {
        fprintf(stderr, "Error opening seats.csv\n");
        return 1;
    }

    struct Course1 courses[MAX_COURSE];
    int num_courses = 0;
    fgets(line, sizeof(line), coursesFile); // Read header line
    while (fgets(line, sizeof(line), coursesFile) && num_courses < MAX_COURSE) {
        parse_courses(line, &courses[num_courses++]);
    }
    fclose(coursesFile);

    for (int i = 0; i < num_students; i++) {
        struct StudentDetails *student = &students[i];
        for (int j = 0; j < student->num_choices; j++) {
            struct Course1 *course = find_course_by_sno(courses, num_courses, student->choices[j]);
            if (course && course->available_seats > 0) {
                reduce_available_seats(courses, num_courses, course->sno);
                student->allocated_course[j] = course->sno;
                student->course_allocated[j] = 1;
            }
        }
    }

    FILE *allotmentFile = fopen("allotmentlist.csv", "w");
    if (allotmentFile == NULL) {
        fprintf(stderr, "Error creating allotmentlist.csv\n");
        return 1;
    }

    fprintf(allotmentFile, "Name,Allocated Courses\n");
    for (int i = 0; i < num_students; i++) {
        struct StudentDetails *student = &students[i];
        fprintf(allotmentFile, "%s", student->name);
        for (int j = 0; j < student->num_choices; j++) {
            if (student->course_allocated[j] == 1) {
                fprintf(allotmentFile, ",%d", student->allocated_course[j]);
                if (j < student->num_choices - 1) {
                    fprintf(allotmentFile, "");
                }
            }
        }
        fprintf(allotmentFile, "\n");
    }
    fclose(allotmentFile);

    FILE *remainingSeatsFile = fopen("remaining_seats.csv", "w");
    if (remainingSeatsFile == NULL) {
        fprintf(stderr, "Error creating remainingseats.csv\n");
        return 1;
    }

    fprintf(remainingSeatsFile, "S.No,Course Name,Course Code,Faculty ID,Remaining Seats\n");
    for (int i = 0; i < num_courses; i++) {
        struct Course1 *course = &courses[i];
        fprintf(remainingSeatsFile, "%d,%s,%s,%s,%d\n", course->sno, course->name, course->code, course->faculty_id, course->available_seats);
    }
    fclose(remainingSeatsFile);

    FILE *waitlistFile = fopen("waitlist.csv", "w");
    if (waitlistFile == NULL) {
        fprintf(stderr, "Error creating waitlist.csv\n");
        return 1;
    }

    fprintf(waitlistFile, "Name,Waitlisted Courses\n");
    for (int i = 0; i < num_students; i++) {
        struct StudentDetails *student = &students[i];
        int waitlisted = 0;
        for (int j = 0; j < student->num_choices; j++) {
            struct Course1 *course = find_course_by_sno(courses, num_courses, student->choices[j]);
            if (course && student->course_specific_rank[course->sno - 1] <= (course->total_seats / 10 + 1) && student->course_allocated[j] != 1) {
                if (!waitlisted) {
                    fprintf(waitlistFile, "%s", student->name);
                    waitlisted = 1;
                }
                fprintf(waitlistFile, ",%d", student->choices[j]);
                if (j < student->num_choices - 1) {
                    fprintf(waitlistFile, "");
                }
            }
        }
        if (waitlisted) {
            fprintf(waitlistFile, "\n");
        }
    }
    fclose(waitlistFile);

    FILE *ranklistFile = fopen("ranklist.csv", "w");
    if (!ranklistFile) {
        printf("Error opening ranklist file.\n");
        return 1;
    }

    fprintf(ranklistFile, "Rank,S.No,Name,Student ID,Prerequisites,CGPA,Attendance,Ranking Score\n");
    for (int i = 0; i < num_students; i++) {
        fprintf(ranklistFile, "%d,%d,%s,%s,%s,%.2f,%d,%.2f\n", students[i].ranking, students[i].serialNo, students[i].name,
                students[i].studentID, students[i].prerequisites, students[i].cgpa, students[i].attendance, students[i].rankingScore);
    }
    fclose(ranklistFile);

    return 0;
}

int count_lines_in_choicelist() {
    const char *filename = "choicelist.csv";
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return -1; // Return -1 to indicate error
    }

    int lines = 0;
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            lines++;
        }
    }

    fclose(file);
    return lines;
}

// Function to load courses from the seats.csv file
void loadCourses(struct Course2 *courses, int *num_courses) {
    FILE *file = fopen("remaining_seats.csv", "r");
    if (!file) {
        printf("Error opening seats file.\n");
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    fgets(line, sizeof(line), file); // Skip header line

    while (fscanf(file, "%d,%[^,],%[^,],%[^,],%d\n", &courses[*num_courses].sno, courses[*num_courses].name, courses[*num_courses].courseID,
               courses[*num_courses].facultyID, &courses[*num_courses].seatsAvailable) != EOF) {
        (*num_courses)++;
    }

    fclose(file);
}

// Function to load choice list from the choicelist.csv file
void loadChoiceList(struct Student *students, int *num_students) {
    FILE *file = fopen("allotmentlist.csv", "r");
    if (!file) {
        printf("Error opening choice list file.\n");
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) && *num_students < MAX_STUDENTS) {
        char *token = strtok(line, ",");
        strcpy(students[*num_students].name, token);

        int courseIndex = 0;
        while ((token = strtok(NULL, ",")) != NULL) {
            students[*num_students].allottedCourses[courseIndex++] = atoi(token);
        }
        students[*num_students].numCourses = courseIndex;
        students[*num_students].numWaitlistedCourses = 0; // Initialize waitlisted courses count
        (*num_students)++;
    }

    fclose(file);
}

// Function to load waitlisted courses from the waitlist.csv file
void loadWaitlist(struct Student *students, int num_students) {
    FILE *file = fopen("waitlist.csv", "r");
    if (!file) {
        printf("Error opening waitlist file.\n");
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",");
        char studentName[MAX_LINE_LENGTH];
        strcpy(studentName, token);

        // Find the student by name
        for (int i = 0; i < num_students; i++) {
            if (strcmp(students[i].name, studentName) == 0) {
                int courseIndex = 0;
                while ((token = strtok(NULL, ",")) != NULL) {
                    students[i].waitlistedCourses[courseIndex++] = atoi(token);
                }
                students[i].numWaitlistedCourses = courseIndex;
                break;
            }
        }
    }

    fclose(file);
}

// Function to display allotted courses and waitlisted courses for a student
void displayStudentCourses(struct Student student, struct Course2 *courses, int num_courses) {
    printf("\033[1;97mStudent: %s\n\033[0m", student.name);
    printf("\033[1;34m\nALLOTTED COURSES:\n\033[0m");
    for (int i = 0; i < student.numCourses; i++) {
        int courseID = student.allottedCourses[i];
        for (int j = 0; j < num_courses; j++) {
            if (courses[j].sno == courseID) {
                printf("%d\t%-20s\t%-10s\t%-10s\n", courses[j].sno, courses[j].name, courses[j].courseID,
                       courses[j].facultyID);
            }
        }
    }

    if (student.numWaitlistedCourses > 0) {
        printf("\nWaitlisted courses:\n");
        for (int i = 0; i < student.numWaitlistedCourses; i++) {
            int courseID = student.waitlistedCourses[i];
            for (int j = 0; j < num_courses; j++) {
                if (courses[j].sno == courseID) {
                    printf("%d\t%-20s\t%-10s\t%-10s\n", courses[j].sno, courses[j].name, courses[j].courseID,
                           courses[j].facultyID);
                }
            }
        }
        printf("\n");
    }
}

// Function to update seats available for a course
void updateSeats(struct Course2 *courses, int num_courses, int courseID, int change) {
    for (int i = 0; i < num_courses; i++) {
        if (courses[i].sno == courseID) {
            courses[i].seatsAvailable += change;
            break;
        }
    }
}

// Function to print final allotted courses for a student
void printFinalAllottedCourses(struct AcceptedCourses acceptedCourses, struct Course2 *courses, int num_courses, struct Student student) {
    for (int i = 0; i < acceptedCourses.numAcceptedCourses; i++) {
        int courseID = acceptedCourses.acceptedCourses[i];
        for (int j = 0; j < num_courses; j++) {
            if (courses[j].sno == courseID) {
                printf("%d\t%-20s\t%-10s\t%-10s\n", courses[j].sno, courses[j].name, courses[j].courseID,
                       courses[j].facultyID);
            }
        }
    }

    // Print waitlisted courses
    if (student.numWaitlistedCourses > 0) {
        printf("\nWaitlisted courses:\n");
        for (int i = 0; i < student.numWaitlistedCourses; i++) {
            int courseID = student.waitlistedCourses[i];
            for (int j = 0; j < num_courses; j++) {
                if (courses[j].sno == courseID) {
                    printf("%d\t%-20s\t%-10s\t%-10s\n", courses[j].sno, courses[j].name, courses[j].courseID,
                           courses[j].facultyID);
                }
            }
        }
    }
}

// Function to update the remaining_seats.csv file
void updateRemainingSeatsFile(struct Course2 *courses, int num_courses) {
    FILE *seatsFile = fopen("remaining_seats.csv", "w");
    if (!seatsFile) {
        printf("Error opening seats file for writing.\n");
        exit(1);
    }

    fprintf(seatsFile, "S.No,Course Name,Course ID,Faculty ID,Seats Available\n");
    for (int i = 0; i < num_courses; i++) {
        fprintf(seatsFile, "%d,%s,%s,%s,%d\n", courses[i].sno, courses[i].name, courses[i].courseID,
                courses[i].facultyID, courses[i].seatsAvailable);
    }

    fclose(seatsFile);
}

// Function to append final allotted courses to finalallottment.csv
void appendFinalAllottedCourses(struct AcceptedCourses acceptedCourses) {
    FILE *file = fopen("finalallottment.csv", "a");
    if (!file) {
        printf("Error opening final allotment file.\n");
        return;
    }
    fprintf(file, "%s", acceptedCourses.name);
    for (int i = 0; i < acceptedCourses.numAcceptedCourses; i++) {
        fprintf(file, ",%d", acceptedCourses.acceptedCourses[i]);
    }
    fprintf(file, "\n");

    fclose(file);
}

int withdraw() {
    struct Course2 courses[MAX_COURSES];
    int num_courses = 0;
    struct Student students[MAX_STUDENTS];
    int num_students = 0;

    // Load data
    loadCourses(courses, &num_courses);
    loadChoiceList(students, &num_students);
    loadWaitlist(students, num_students);

    char studentName[MAX_LINE_LENGTH];
    int foundStudent = 0;

    // Ask for student name
    printf("Enter student name: ");
    scanf(" %[^\n]", studentName);

    // Check if the student has already completed the withdrawal process
    if (hasCompletedWithdrawal(studentName)) {
        printf("\033[1;31mYou have already completed the withdrawal process. You can only do this once.\n\033[0m");
        return 0;
    }

    // Find the student by name
    for (int i = 0; i < num_students; i++) {
        if (strcmp(students[i].name, studentName) == 0) {
            foundStudent = 1;
            printf("\nProcessing Student:\n");
            displayStudentCourses(students[i], courses, num_courses);

            struct AcceptedCourses acceptedCourses;
            strcpy(acceptedCourses.name, students[i].name);
            acceptedCourses.numAcceptedCourses = 0;

            int declineCount = 0;
            for (int j = 0; j < students[i].numCourses; j++) {
                int courseID = students[i].allottedCourses[j];
                for (int k = 0; k < num_courses; k++) {
                    if (courses[k].sno == courseID) {
                        printf("Do you want to accept the course %s (Y/N)? ", courses[k].name);
                        char choice;
                        scanf(" %c", &choice);
                        if(choice!='N' && choice!='Y' && choice!='y' && choice!='n')
                        {printf("\033[1;31mInvalid charater (choose Y/N)\n\033[0m");}
                        else{
                        if ((choice == 'N' || choice == 'n') && declineCount >= students[i].numCourses - MIN_COURSES) {
                            printf("\033[1;31mError: You can only decline up to %d course(s) [Minimum 4 courses].\n\033[0m", students[i].numCourses - MIN_COURSES);
                            j--; // Repeat for the same course
                            continue;
                        }
                        if (choice == 'Y' || choice == 'y') {
                            acceptedCourses.acceptedCourses[acceptedCourses.numAcceptedCourses++] = courseID;
                        } else if (choice == 'N' || choice == 'n') {
                            courses[k].seatsAvailable += 1; // Increase seats by 1 if declined
                            declineCount++;
                        }}
                    }
                }
            }

            // Print final allotted course list and waitlisted courses
            printf("\033[1;32m\nFINAL ALLOTTED COURSES:\n\033[0m");
            printFinalAllottedCourses(acceptedCourses, courses, num_courses, students[i]);

            // Append final allotted courses to finalallottment.csv
            appendFinalAllottedCourses(acceptedCourses);

            printf("\033[1;32m\nCongratulations! Courses have been successfully chosen!\n\n\033[0m");

            break; // Exit loop after processing the student
        }
    }

    if (!foundStudent) {
        printf("\033[1;31mStudent with name '%s' not found.\n\033[0m", studentName);
    }

    // Update remaining_seats.csv file
    updateRemainingSeatsFile(courses, num_courses);

    return 0;
}

// Function to check if the student has already completed the withdrawal process
int hasCompletedWithdrawal(char *studentName) {
    FILE *file = fopen("finalallottment.csv", "r");
    if (!file) {
        return 0; // If the file doesn't exist, the student hasn't completed the process
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",");
        if (strcmp(token, studentName) == 0) {
            fclose(file);
            return 1; // Student found in the file
        }
    }

    fclose(file);
    return 0; // Student not found in the file
}

int countLinesInFinalAllotment() {
    const char *filename = "finalallottment.csv";
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file: %s\n", filename);
        return -1; // Return -1 to indicate error
    }

    int lineCount = 0;
    char buffer[1024]; // Buffer to read each line

    // Count lines in the file
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        lineCount++;
    }

    fclose(file);
    return lineCount;
}

// Function to load courses from the remaining_seats.csv file
void loadCourses3(struct Course3 *courses, int *num_courses) {
    FILE *file = fopen("remaining_seats.csv", "r");
    if (!file) {
        printf("Error opening remaining_seats.csv file.\n");
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    fgets(line, sizeof(line), file); // Skip header line

    while (fscanf(file, "%d,%[^,],%[^,],%[^,],%d\n", &courses[*num_courses].sno, courses[*num_courses].name, courses[*num_courses].courseID,
               courses[*num_courses].facultyID, &courses[*num_courses].seatsAvailable) != EOF) {
        (*num_courses)++;
    }

    fclose(file);
}

// Function to load waitlist from the waitlist.csv file
void loadWaitlist3(struct Student3 *students, int *num_students) {
    FILE *file = fopen("waitlist.csv", "r");
    if (!file) {
        printf("Error opening waitlist.csv file.\n");
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    fgets(line, sizeof(line), file); // Read header line

    while (fgets(line, sizeof(line), file) && *num_students < MAX_STUDENTS) {
        char *token = strtok(line, ",");
        strcpy(students[*num_students].name, token);

        int courseIndex = 0;
        while ((token = strtok(NULL, ",")) != NULL) {
            students[*num_students].waitlistedCourses[courseIndex++] = atoi(token);
        }
        students[*num_students].numWaitlistedCourses = courseIndex;
        (*num_students)++;
    }

    fclose(file);
}

// Function to process waitlist and allocate courses if seats are available
void processWaitlist3(struct Student3 *students, int num_students, struct Course3 *courses, int num_courses, int successfulAllocations[MAX_STUDENTS][MAX_COURSES]) {
    for (int i = 0; i < num_students; i++) {
        for (int j = 0; j < students[i].numWaitlistedCourses; j++) {
            int courseID = students[i].waitlistedCourses[j];
            for (int k = 0; k < num_courses; k++) {
                if (courses[k].sno == courseID && courses[k].seatsAvailable > 0) {
                    // Allocate the course
                    courses[k].seatsAvailable--;

                    // Append to final allotment
                    appendFinalAllottedCourses3(students[i].name, courseID);

                    // Track successful allocation
                    successfulAllocations[i][j] = courseID;

                    // Remove the course from waitlist
                    students[i].waitlistedCourses[j] = -1;  // Mark as processed
                    break;
                }
            }
        }
    }
}

// Function to update the remaining_seats.csv file
void updateRemainingSeatsFile3(struct Course3 *courses, int num_courses) {
    FILE *seatsFile = fopen("remaining_seats.csv", "w");
    if (!seatsFile) {
        printf("Error opening remaining_seats.csv file for writing.\n");
        exit(1);
    }

    fprintf(seatsFile, "S.No,Course Name,Course ID,Faculty ID,Seats Available\n");
    for (int i = 0; i < num_courses; i++) {
        fprintf(seatsFile, "%d,%s,%s,%s,%d\n", courses[i].sno, courses[i].name, courses[i].courseID,
                courses[i].facultyID, courses[i].seatsAvailable);
    }

    fclose(seatsFile);
}

// Function to append final allotted courses to finalallottment.csv
void appendFinalAllottedCourses3(const char *studentName, int courseID) {
    FILE *file = fopen("finalallottment.csv", "r");
    FILE *tempFile = fopen("temp.csv", "w");
    if (!file || !tempFile) {
        printf("Error opening finalallottment.csv or temp.csv file.\n");
        if (file) fclose(file);
        if (tempFile) fclose(tempFile);
        return;
    }

    // Check if student already has an entry
    char line[MAX_LINE_LENGTH];
    int found = 0;
    while (fgets(line, sizeof(line), file)) {
        char tempLine[MAX_LINE_LENGTH];
        strcpy(tempLine, line);

        char *token = strtok(line, ",");
        if (strcmp(token, studentName) == 0) {
            found = 1;
            fprintf(tempFile, "%s,%d\n", strtok(tempLine, "\n"), courseID);
        } else {
            fprintf(tempFile, "%s", tempLine);
        }
    }

    if (!found) {
        fprintf(tempFile, "%s,%d\n", studentName, courseID);
    }

    fclose(file);
    fclose(tempFile);

    remove("finalallottment.csv");
    rename("temp.csv", "finalallottment.csv");
}

// Function to update the waitlist.csv file
void updateWaitlistFile3(struct Student3 *students, int num_students) {
    FILE *file = fopen("waitlist.csv", "w");
    if (!file) {
        printf("Error opening waitlist.csv file for writing.\n");
        exit(1);
    }

    fprintf(file, "Name,Waitlisted Courses\n");
    for (int i = 0; i < num_students; i++) {
        fprintf(file, "%s", students[i].name);
        int first = 1;
        for (int j = 0; j < students[i].numWaitlistedCourses; j++) {
            if (students[i].waitlistedCourses[j] != -1) {  // Not processed
                if (first) {
                    fprintf(file, ",");
                    first = 0;
                } else {
                    fprintf(file, ",");
                }
                fprintf(file, "%d", students[i].waitlistedCourses[j]);
            }
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

// Function to write successful waitlist allocations to successfulwaitlist.csv
void writeSuccessfulWaitlist3(const struct Student3 *students, int num_students, const int successfulAllocations[][MAX_COURSES]) {
    FILE *file = fopen("successfulwaitlist.csv", "w");
    if (!file) {
        printf("Error opening successfulwaitlist.csv file for writing.\n");
        exit(1);
    }

    fprintf(file, "Name,Successful Allotted Waitlisted Courses\n");
    for (int i = 0; i < num_students; i++) {
        int hasAllocations = 0;
        fprintf(file, "%s,", students[i].name);
        for (int j = 0; j < students[i].numWaitlistedCourses; j++) {
            if (successfulAllocations[i][j] > 0) {
                if (hasAllocations) {
                    fprintf(file, ",");
                } else {
                    hasAllocations = 1;
                }
                fprintf(file, "%d", successfulAllocations[i][j]);
            }
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

// Function to ensure each student has at least 4 courses
void ensureMinimumCourses3() {
    FILE *file = fopen("finalallottment.csv", "r");
    FILE *tempFile = fopen("temp.csv", "w");
    FILE *successFile = fopen("successfulwaitlist.csv", "r+");

    if (!file || !tempFile || !successFile) {
        printf("Error opening finalallottment.csv, temp.csv or successfulwaitlist.csv file.\n");
        if (file) fclose(file);
        if (tempFile) fclose(tempFile);
        if (successFile) fclose(successFile);
        return;
    }

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file)) {
        char tempLine[MAX_LINE_LENGTH];
        strcpy(tempLine, line);

        char *token = strtok(line, ",");
        char *studentName = token;

        int courseCount = 0;
        while ((token = strtok(NULL, ",")) != NULL) {
            courseCount++;
        }

        fprintf(tempFile, "%s", strtok(tempLine, "\n"));
        if (courseCount < 4) {
            for (int i = courseCount; i < 4; i++) {
                int randomIndex = rand() % randomCourseCount;
                int randomCourse = randomCourseIDs[randomIndex];

                fprintf(tempFile, ",%d", randomCourse);

            }
        }
        fprintf(tempFile, "\n");
    }

    fclose(file);
    fclose(tempFile);
    fclose(successFile);

    remove("finalallottment.csv");
    rename("temp.csv", "finalallottment.csv");
}


int waitlist() {
    struct Course3 courses[MAX_COURSES];
    int num_courses = 0;
    struct Student3 waitlistedStudents[MAX_STUDENTS];
    int num_waitlistedStudents = 0;

    // Initialize random number generator
    srand(time(0));

    // Load courses and waitlist data
    loadCourses3(courses, &num_courses);
    loadWaitlist3(waitlistedStudents, &num_waitlistedStudents);

    // Process waitlist and track successful allocations
    int successfulAllocations[MAX_STUDENTS][MAX_COURSES] = {0};
    processWaitlist3(waitlistedStudents, num_waitlistedStudents, courses, num_courses, successfulAllocations);

    // Update remaining seats file
    updateRemainingSeatsFile3(courses, num_courses);

    // Update waitlist file
    updateWaitlistFile3(waitlistedStudents, num_waitlistedStudents);

    // Write successful waitlist allocations to a new file
    writeSuccessfulWaitlist3(waitlistedStudents, num_waitlistedStudents, successfulAllocations);

    // Ensure each student has at least 4 courses
    ensureMinimumCourses3();

    return 0;
}

int readCourses(struct Course4 courses[]) {
    const char *filename = "Courses.csv";
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file: %s\n", filename);
        return -1; // Return -1 to indicate error
    }

    char line[MAX_LINE_LENGTHS];
    int count = 0;
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",");
        if (token) {
            courses[count].sno = atoi(token);
            token = strtok(NULL, ",");
            if (token) strncpy(courses[count].course_name, token, sizeof(courses[count].course_name));
            token = strtok(NULL, ",");
            if (token) strncpy(courses[count].course_id, token, sizeof(courses[count].course_id));
            token = strtok(NULL, ",");
            if (token) strncpy(courses[count].faculty_id, token, sizeof(courses[count].faculty_id));
            count++;
        }
    }

    fclose(file);
    return count;
}

int readFinalAllotment(struct Student4 students[]) {
    const char *filename = "finalallottment.csv";
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file: %s\n", filename);
        return -1; // Return -1 to indicate error
    }

    char line[MAX_LINE_LENGTHS];
    int count = 0;
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",");
        if (token) {
            strncpy(students[count].name, token, sizeof(students[count].name));
            students[count].num_allocated_courses = 0;
            token = strtok(NULL, ",");
            while (token) {
                students[count].allocated_courses[students[count].num_allocated_courses++] = atoi(token);
                token = strtok(NULL, ",");
            }
            count++;
        }
    }

    fclose(file);
    return count;
}

void printStudentCourseDetails(struct Course4 courses[], int num_courses, struct Student4 students[], int num_students) {
    printf("\n\t\t\033[42m\033[1;97m FINAL COURSE ALLOTTMENT LIST \033[0m\n\n");
    for (int i = 0; i < num_students; i++) {
        printf("Student: %s\n", students[i].name);
        printf("-----------------------------------------------------------------\n");
        printf("| %-4s | %-30s | %-10s | %-10s |\n", "S.no", "Course Name", "Course ID", "Faculty ID");
        printf("-----------------------------------------------------------------\n");
        for (int j = 0; j < students[i].num_allocated_courses; j++) {
            int sno = students[i].allocated_courses[j];
            for (int k = 0; k < num_courses; k++) {
                if (courses[k].sno == sno) {
                    printf("| %-4d | %-30s | %-10s | %-10s |\n", courses[k].sno, courses[k].course_name, courses[k].course_id, courses[k].faculty_id);
                    break;
                }
            }
        }
        printf("-----------------------------------------------------------------\n");
        printf("\n");
    }
}

int printfinal() {
    struct Course4 courses[MAX_COURSES];
    struct Student4 students[MAX_STUDENTS];
    int num_courses = 0;
    int num_students = 0;

    num_courses = readCourses(courses);
    if (num_courses == -1) {
        return 1;
    }

    num_students = readFinalAllotment(students);
    if (num_students == -1) {
        return 1;
    }

    printStudentCourseDetails(courses, num_courses, students, num_students);

    return 0;
}

// Function to read courses from Courses.csv
int readCourses5(struct Course5 courses[]) {
    const char *filename = "Courses.csv";
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file: %s\n", filename);
        return -1;
    }

    char line[MAX_LINE_LENGTHS];
    int count = 0;
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",");
        if (token) {
            courses[count].sno = atoi(token);
            token = strtok(NULL, ",");
            if (token) strncpy(courses[count].course_name, token, sizeof(courses[count].course_name));
            token = strtok(NULL, ",");
            if (token) strncpy(courses[count].course_id, token, sizeof(courses[count].course_id));
            token = strtok(NULL, ",");
            if (token) strncpy(courses[count].faculty_id, token, sizeof(courses[count].faculty_id));
            count++;
        }
    }

    fclose(file);
    return count;
}

// Function to find course details by S.no
struct Course5 *findCourseBySno5(struct Course5 courses[], int num_courses, int sno) {
    for (int i = 0; i < num_courses; i++) {
        if (courses[i].sno == sno) {
            return &courses[i];
        }
    }
    return NULL;
}

// Function to print course details
void printCourseDetails5(int sno, struct Course5 *course) {
    if (course) {
        printf("%-8d %-25s %-15s %-10s\n", sno, course->course_name, course->course_id, course->faculty_id);
    }
}

// Function to read and print waitlist and successful waitlist details
void printStudentWaitlistDetails5(struct Course5 courses[], int num_courses) {
    char studentName[MAX_NAME_LENGTH];
    printf("Enter student name: ");
    fgets(studentName, sizeof(studentName), stdin);
    studentName[strcspn(studentName, "\n")] = 0; // Remove newline character

    const char *waitlistFile = "waitlist.csv";
    const char *successFile = "successfulwaitlist.csv";

    FILE *file = fopen(waitlistFile, "r");
    if (!file) {
        printf("Error opening file: %s\n", waitlistFile);
        return;
    }

    char line[MAX_LINE_LENGTHS];
    int found = 0;

    // Check waitlist.csv
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",");
        if (token && strcmp(token, studentName) == 0) {
            found = 1;
            printf("\033[1;34m\nUNALLOCATED COURSES:\n\033[0m");
            token = strtok(NULL, ",");
            while (token) {
                int sno = atoi(token);
                struct Course5 *course = findCourseBySno5(courses, num_courses, sno);
                printCourseDetails5(sno, course);
                token = strtok(NULL, ",");
            }
            break;
        }
    }
    fclose(file);

    // Check successfulwaitlist.csv
    file = fopen(successFile, "r");
    if (!file) {
        printf("Error opening file: %s\n", successFile);
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",");
        if (token && strcmp(token, studentName) == 0) {
            found = 1;
            printf("\033[1;34m\nALLOCATED WAITLISTED COURSES:\n\033[0m");
            token = strtok(NULL, ",");
            while (token) {
                int sno = atoi(token);
                struct Course5 *course = findCourseBySno5(courses, num_courses, sno);
                printCourseDetails5(sno, course);
                token = strtok(NULL, ",");
            }
            break;
        }
    }
    fclose(file);

    if (!found) {
        printf("No details found for student: %s\n", studentName);
    }
}

int printwaitlist() {
    struct Course5 courses[MAX_COURSES];
    int num_courses = readCourses5(courses);

    if (num_courses != -1) {
        printStudentWaitlistDetails5(courses, num_courses);
    }

    return 0;
}

void printTop5Recommendations() {
    struct Course6 courses[] = {
        {11, "Database Management", "CDBMS104", 99},
        {22, "Machine Learning", "EML108", 95},
        {8, "Data Structures", "CDS103", 90},
        {13, "Operating Systems", "COS105", 88},
        {19, "Web Development", "EWD107", 85}
    };

    int num_courses = sizeof(courses) / sizeof(courses[0]);

    printf("\033[1;97mS.no  COURSE NAME             COURSE ID   RECOMMENDATION PERCENTAGE\033[0m\n");
    for (int i = 0; i < num_courses; i++) {
        printf("%-5d %-23s %-10s %d%%\n", courses[i].sno, courses[i].name, courses[i].courseID, courses[i].recommendationPercentage);
    }
}