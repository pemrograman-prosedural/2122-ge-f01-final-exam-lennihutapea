// 12S23023 - Lenni Febriyani
// 12S23031 - Matthew Pangihutan

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./libs/dorm.h"
#include "./libs/student.h"

int main(int _argc, char **_argv)
{
    Dorm* LEFT = (Dorm*) malloc(sizeof(Dorm));
    if (LEFT == NULL) {
        fprintf(stderr, "Failed to allocate memory for LEFT\n");
        return 1;
    }
    strcpy(LEFT->name,"left");
    LEFT->capacity = 10;
    LEFT->gender = GENDER_FEMALE;
    LEFT->residents_num = 0;
    Dorm *dorms = (Dorm*) malloc(sizeof(Dorm));
    if (dorms == NULL) {
        fprintf(stderr, "Failed to allocate memory for dorms\n");
        free(LEFT);
        return 1;
    }
    Student *students = (Student*) malloc(sizeof(Student));
    if (students == NULL) {
        fprintf(stderr, "Failed to allocate memory for students\n");
        free(dorms);
        free(LEFT);
        return 1;
    }
    unsigned short totalDorm = 0;
    unsigned short totalStudent = 0;
    char line[255];
    char delim[2] = "#";

    while ( 1 ) {
        line[0] = '\0';
        fgets(line, 255, stdin);
        fflush(stdin);
        /* declared in scope level --> temporary
           but the result remains */
        {
            int len = strlen(line);
            for (short a = 0; a < len; a++) {
                if(line[a] == '\r' || line[a] == '\n') {
                    for(short b = a; b < len; b++) { line[b] = line[b + 1]; }
                    len--;
                    a--;
                }
            }
        }

        if ( strcmp(line, "---") == 0 ) break;
        else if ( strcmp(line, "student-print-all") == 0 ) {
            for (short i=0; i<totalStudent; i++) {
                printStudent(students[i]);
            }
        }
        else if ( strcmp(line, "dorm-print-all") == 0 ) {
            for (short i=0; i<totalDorm; i++) {
                print_dorm(dorms[i]);
            }
        }
        else if ( strcmp(line, "student-print-all-detail") == 0 ) {
            for (short i=0; i<totalStudent; i++) {
                printStudentDetails(students[i]);
            }
            
        }
        else if ( strcmp(line, "dorm-print-all-detail") == 0 ) {
            for (short i=0; i<totalDorm; i++) {
                printDormDetails(dorms[i]);
            }
        }

        else {
            char *token = strtok(line, delim);
            if ( strcmp(token, "student-add") == 0 ) {
                token = strtok(NULL, delim); char *_id = token;
                token = strtok(NULL, delim); char *_name = token;
                token = strtok(NULL, delim); char *_year = token;
                token = strtok(NULL, delim);
                if ( totalStudent > 0 ) {
                    students = (Student*) realloc(students, (totalStudent+1) * sizeof(Student));
                }
                if ( strcmp(token, "male") == 0 ) {
                    students[totalStudent] = create_student(_id, _name, _year, GENDER_MALE);
                    totalStudent++;
                }
                else if ( strcmp(token, "female") == 0 ) {
                    students[totalStudent] = create_student(_id, _name, _year, GENDER_FEMALE);
                    totalStudent++;
                }
            }
            else if ( strcmp(token, "dorm-add") == 0 ) {
                token = strtok(NULL, delim); char *_name = token;
                token = strtok(NULL, delim); unsigned short _capacity = atoi(token);
                token = strtok(NULL, delim);
                if ( totalDorm > 0 ) {
                    dorms = (Dorm*) realloc(dorms, (totalDorm+1) * sizeof(Dorm));
                }
                if ( strcmp(token, "male") == 0 ) {
                    dorms[totalDorm] = create_dorm(_name, _capacity, GENDER_MALE);
                    totalDorm++;
                }
                else if ( strcmp(token, "female") == 0 ) {
                    dorms[totalDorm] = create_dorm(_name, _capacity, GENDER_FEMALE);
                    totalDorm++;
                }
            }
            else if ( strcmp(token, "assign-student") == 0 ) {
                token = strtok(NULL, delim); char *_id = token;
                token = strtok(NULL, delim); char *dorm_name = token;
                short studentIdx = findStudentIdx(_id, students, totalStudent);
                short dormIdx = findDormIdx(dorm_name, dorms, totalDorm);
                if ( studentIdx>=0 && dormIdx>=0 ) {
                    assign(&students[studentIdx], &dorms[dormIdx]);
                }
            }
            else if ( strcmp(token, "move-student") == 0 ) {
                token = strtok(NULL, delim); char *_id = token;
                token = strtok(NULL, delim); char *dorm_name = token;
                short studentIdx = findStudentIdx(_id, students, totalStudent);
                short newDormIdx = findDormIdx(dorm_name, dorms, totalDorm);
                char *_name = students[studentIdx].dorm->name;
                if (_name != NULL) {
                    short oldDormIdx = findDormIdx( _name, dorms, totalDorm );

                    if ( studentIdx>=0 && newDormIdx>=0 && oldDormIdx>=0 ) {
                        moveStudent(&students[studentIdx], &dorms[newDormIdx] , &dorms[oldDormIdx]);
                    }
                } else {
                    assign(&students[studentIdx], &dorms[newDormIdx]);
                }
            }
            else if ( strcmp(token, "dorm-empty") == 0 ) {
                token = strtok(NULL, delim);
                char *dorm_name = token;
                short target = findDormIdx(dorm_name, dorms, totalDorm);
                // emptyDorm(&dorms[target], &students, totalStudent);
                for (short i=0; i<totalStudent; i++) {
                    if (students[i].dorm != NULL) {     /* MENGHINDARI STRING COMPARATION DGN NULL */
                        if ( strcmp(students[i].dorm->name, dorm_name) == 0 ) {
                            unassign(&students[i], &dorms[target]);
                        }
                    }
                }
            }
            else if ( strcmp(token, "student-leave") == 0 ) {
                token = strtok(NULL, delim);
                short studentIdx = findStudentIdx(token, students, totalStudent);
                short dormIdx = findDormIdx(students->dorm->name, dorms, totalDorm);
                unassign(&students[studentIdx], &dorms[dormIdx]);
                students[studentIdx].dorm = LEFT;
            }
        }
    }
    
    free(dorms);
    free(students);
    free(LEFT);
    
    return 0;
}
