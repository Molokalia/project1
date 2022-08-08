#ifndef TOOLS_H
#define	TOOLS_H

#include <stdbool.h>

#define STU 1000
#define TEA 50

typedef struct Teacher
{
	char name[20];			//	姓名
	char sex[4];			//	性别，直接存储中文字符串
	char id[9];				//	工号，也是登录帐号
	char password[11];		//	密码
	char situation;			//	工作状态：离职-1/在职1
	char account;			//	帐号状态：未锁定1/锁定-1
	char is_first_sign;		//	是否首次登录，是1,不是-1		
}tea;

typedef struct Student
{	
	char name[20];			//	姓名
	char sex[4];			//	性别，直接存储中文字符串
	char id[9];				//	学号，也是登录帐号
	char password[11];		//	密码
	char situation;			//	工作状态：在校1/退学-1
	char account;			//	帐号状态：未锁定1/锁定-1
	char is_first_sign;		//	首次登录: 是1/否-1
	float chinese;			//	语文成绩
	float math;				//	数学成绩
	float english;			//	英语成绩
}stu;

typedef struct headmaster
{
	char name[20];
	char id[9];
	char password[7];
	char is_first_sign;
}head;

extern stu* stup;
extern tea* teap;
extern head hea;
extern stu* stup1;
extern char max_id[9];

void input_password(char str[]);
bool return_to_pre(void);
void msg_show(const char* msg,float sec);
void anykey_continue(void);
int id_find(int role,char* str);
void clean_arr(char arr[],int len);
int whether_exit(void);
int input(int role,char *check);

#endif//TOOLS_H
