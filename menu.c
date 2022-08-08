#include <stdio.h>
#include <stdlib.h>
#include <getch.h>
#include "menu.h"

int menu1(void)
{
	system("clear");
	puts("————欢迎使用天才大学人员管理系统————");
	puts("————————请选择您的身份——————");
	puts("1、学生");
	puts("2、老师");
	puts("3、校长");
	puts("4、退出系统");
	printf("请选择:");
	char cmd=getch();
	stdin->_IO_read_ptr = stdin->_IO_read_end;
	printf("%c\n",cmd);		//回显
	return cmd;
}

int menu2(void)
{
	system("clear");
	puts("————同学你好，请选择你的操作————");
	puts("1、查询成绩");
	puts("2、查看个人信息");
	puts("3、修改密码");
	puts("4、退出登录");
	printf("请选择:");
	char cmd=getch();
	stdin->_IO_read_ptr = stdin->_IO_read_end;
	printf("%c\n",cmd);		//回显
	return cmd;
}

int menu3(void)
{
	system("clear");
	puts("————老师你好，请选择你的操作————");
	puts("1、添加学生");
	puts("2、删除学生");
	puts("3、查找学生");
	puts("4、修改学生信息");
	puts("5、录入学生成绩");
	puts("6、重置学生密码");
	puts("7、显示在校学生信息");
	puts("8、显示退学学生信息");
	puts("9、修改密码");
	puts("A、解锁学生帐号");
	puts("B、退出登录");
	printf("请选择:");
	char cmd=getch();
	stdin->_IO_read_ptr = stdin->_IO_read_end;
	printf("%c\n",cmd);		//回显
	return cmd;
}

int menu4(void)
{
	system("clear");
	puts("————校长你好，请选择你的操作————");
	puts("1、添加教师信息");
	puts("2、删除教师信息");
	puts("3、显示在职教师信息");
	puts("4、显示离职教师信息");
	puts("5、重置教师密码");
	puts("6、解锁教师帐号");
	puts("7、重置校长密码");
	puts("8、退出登录");
	printf("请选择:");
	char cmd=getch();
	stdin->_IO_read_ptr = stdin->_IO_read_end;
	printf("%c\n",cmd);		//回显
	return cmd;
}


