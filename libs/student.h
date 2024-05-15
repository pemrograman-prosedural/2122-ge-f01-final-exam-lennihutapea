#ifndef STUDENT_H
#define STUDENT_H

#include "dorm.h"
#include "gender.h"

/**
 * @brief define your structure, enums, globally accessible variables, and function prototypes here.
 * The actual function implementation should be defined in the corresponding source file.
 *
 */

typedef struct student_t
{
    char id[12];
    char name[40];
    char year[5];
    gender_t gender;
    Dorm *dorm;
} Student;

Student create_student ( char *_id, char *_name, char *_year, gender_t _gender );
short findStudentIdx ( char *_id, Student *list, int length );
void printStudent ( Student student_to_print );
void assign ( Student *student_, Dorm *dorm_ );
void unassign ( Student *student_, Dorm* dorm_ );
void moveStudent ( Student *migrant, Dorm *newResidence , Dorm *oldResidence );
void printStudentDetails ( Student student_to_print );
void emptyDorm ( Dorm* residence, Student** potentialResidents, unsigned short totalPR );

#endif
