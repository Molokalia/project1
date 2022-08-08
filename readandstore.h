#ifndef READANDSTORE_H
#define READANDSTORE_H

#include <stdio.h>
#include <stdbool.h>
#include "student.h"
#include "teacher.h"
#include "headmaster.h"
#include "tools.h"

extern stu* stup;
extern tea* teap;
extern stu* stup1;
extern head hea;

void read_out(void);
void store_in(void);
void f_printf(int role, int num, FILE* fp);
void f_scanf(int role,int num,FILE* fp);
void read_infomation(int select);
bool is_continue(void);

#endif//READANDSTORE_H
