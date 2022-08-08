#ifndef OPERATION_H
#define OPERATION_H

#include <stdbool.h>
#include "student.h"
#include "teacher.h"
#include "headmaster.h"

extern stu* stup;
extern stu* stup1;
extern tea* teap;
extern head hea;

void change_password();
void add_inform(int n);
void del_inform(int n);
void reset_code(int role);
void show_inschool(int role);
void show_leaveschool(int role);
void unlock(int role);

#endif//OPERATION_H
