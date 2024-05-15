#include "student.h"
#include <stdio.h>
#include <string.h>

/**
 * @brief Define the complete function definition here. Be sure to enlist the prototype of each function
 * defined here in the corresponding header file.
 *
 */

Student create_student ( char *_id, char *_name, char *_year, gender_t _gender )
{
    Student student_;

    strcpy( student_.id, _id );
    strcpy( student_.name, _name );
    strcpy( student_.year, _year );
    student_.gender = _gender;
    student_.dorm   = NULL;

    return student_;
}

void printStudent ( Student student_to_print )
{
    if ( strcmp(student_to_print.name, "") != 0 ) {
        printf( "%s|%s|%s", student_to_print.id,
                            student_to_print.name,
                            student_to_print.year );

        switch ( student_to_print.gender )
        {
            case GENDER_MALE:
                puts("|male");
                break;
            
            case GENDER_FEMALE:
                puts("|female");
                break;
        }
    }
    fflush(stdout);
}

short findStudentIdx ( char *_id, Student *list, int length ) {
    for ( short i=0; i<length; i++ ) {
        if ( strcmp(list[i].id, _id) == 0 )
            return i;
    }

    return -1;
}

void assign ( Student *student_, Dorm *dorm_ )
{
    if ( student_->gender == dorm_->gender && dorm_->residents_num < dorm_->capacity )
    {
        student_->dorm = dorm_;
        dorm_->residents_num++;
    }
    else {
        student_->dorm = NULL;
    }
}

void unassign ( Student *student_, Dorm* dorm_ )
{
    if ( student_->dorm == dorm_ ) {
        student_->dorm = NULL;
        dorm_->residents_num--;
    }
}

void moveStudent ( Student *migrant, Dorm *newResidence , Dorm *oldResidence )
{
    if ( migrant->dorm != NULL ) {
        unassign ( migrant, oldResidence );
    }
    assign ( migrant, newResidence );
}

void printStudentDetails ( Student student_to_print )
{
    if ( strcmp(student_to_print.name, "") != 0 ) {
        printf( "%s|%s|%s", student_to_print.id,
                            student_to_print.name,
                            student_to_print.year );

        switch ( student_to_print.gender ) {
            case GENDER_MALE:
                ( student_to_print.dorm != NULL ) ?
                    printf("|male|%s\n", student_to_print.dorm->name) : printf("|male|unassigned\n");
                break;
            
            case GENDER_FEMALE:
                ( student_to_print.dorm != NULL ) ?
                    printf("|female|%s\n", student_to_print.dorm->name) : printf("|female|unassigned\n");
                break;
        }
    }
    fflush( stdout );
}

void emptyDorm ( Dorm* residence, Student** potentialResidents, unsigned short totalPR )
{
    for (size_t i=0; i<totalPR; i++) {
        if (potentialResidents[i]->dorm != NULL) {
            if (potentialResidents[i]->dorm == residence)
                unassign(potentialResidents[i], residence);
        }
    }
}