#ifndef __student_h__
#define __student_h__

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char surname[50];
    char init[3];
    char sex;
    int school_num;
    char medal;
    char zachet;
    int matan;
    int infa;
    int rus;
    int summary;
} Student;

#endif
