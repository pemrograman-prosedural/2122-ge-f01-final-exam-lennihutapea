#ifndef DORM_H
#define DORM_H

#include "gender.h"

/**
 * @brief define your structure, enums, globally accessible variables, and function prototypes here.
 * The actual function implementation should be defined in the corresponding source file.
 *
 */

typedef struct dorm_t
{
  char name[20];
  unsigned short capacity;
  gender_t gender;
  unsigned short residents_num;
} Dorm;

Dorm create_dorm ( char *_name, unsigned short _capacity, gender_t _gender );
short findDormIdx ( char* _name, Dorm *list, int length );
void print_dorm ( Dorm dorm_to_print );
void printDormDetails ( Dorm dorm_to_print );

#endif
