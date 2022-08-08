#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getch.h>
#include "tools.h"
#include "menu.h"
#include "teacher.h"
#include "sign.h"
#include "readandstore.h"
#include "operation.h"

void teacher(void)
{
	printf("欢迎您，老师\n");
	anykey_continue();		//按任意键继续
	int num = 0;			//定义变量接收登录的学生的结构体在数组中的位置
	num = sign_in(2);		//	调用登录函数，登录成功则返回这个帐号在数组中的位置
	if(num == -1) return;	//	如果没有找到帐号或者登录失败则返回-1
	first_log(2,num);		//	判断该帐号是否初次登录，是则强制修改密码
	for(;;)
	{
		switch(menu3())		//	教师的可选操作菜单
		{
			case '1':	add_inform(1);			break;		//添加学生信息
			case '2':	del_inform(1);			break;		//删除学生信息
			case '3':	check_stu();			break;		//查询学生信息
			case '4':	modify_stu();			break;		//修改学生信息
			case '5':	input_score();			break;		//录入学生成绩
			case '6':	reset_code(1);			break;		//重置学生密码
			case '7':	show_inschool(1);		break;		//显示在校学生信息
			case '8':	show_leaveschool(1);	break;		//显示退学学生信息
			case '9':	change_password(2,num);	break;		//修改密码
			case 'A':	unlock(1);				break;		//解锁学生帐号
			case 'B':	return;
		}
	}
}
	//查询学生信息
void check_stu(void)
{
	system("clear");
	char check[25];			//定义数组接收输入的信息
	printf("请输入你要查找信息的方式：\n如果不想继续，按‘esc’退出\n");		//有两种方式实现查找学生功能
	puts("1、按学号查找");
	puts("2、按姓名查找");
	if(1==whether_exit())	return;
	switch(getch())
	{
		case '1':
			puts("请输入需要查找的学号");
			if(-1==input(1,check))	return;		//1为判断学号，调用输入函数，如果输入学号不为8位则重新输入直至格式正确
			for(int i=0;i<STU;i++)
			{
				if(!strcmp(stup[i].id,check))	//在所有学生信息中查找教师输入学号，找到后显示信息
				{
					system("clear");
					printf("姓名：%s\n性别：%s\n学号：%s\n在校状态：%s\n语文成绩：%.2f\n数学成绩：%.2f\n英语成绩：%.2f\n",
						stup[i].name,
						stup[i].sex,
						stup[i].id,
						1 == stup[i].situation?"在校":"退学",
						stup[i].chinese,
						stup[i].math,stup[i].english);
					anykey_continue();
					return;
				}
			}
			puts("查无此人");			//所有学生中没找到该学生提示信息
			anykey_continue();
			return;
		case '2':
			system("clear");
			puts("请输入姓名");
			if(-1==input(2,check))	return;		//调用输入函数，如果输入姓名字节超过20位则重新输入直至格式正确
			for(int i=0;i<STU;i++)
			{
				system("clear");
				if(!strcmp(stup[i].name,check))		//在所有学生信息中查找教师输入姓名，找到后显示信息
				{
					printf("姓名：%s\n性别：%s\n学号：%s\n在校状态：%s\n语文成绩：%.2f\n数学成绩：%.2f\n英语成绩：%.2f\n",
						stup[i].name,
						stup[i].sex,stup[i].id,
						1 == stup[i].situation?"在校":"退学",
						stup[i].chinese,
						stup[i].math,
						stup[i].english);
					anykey_continue();
					return;
				}
			}
		puts("查无此人");			//所有学生中没找到该学生提示信息
		anykey_continue();
		return;
	}
}

//修改学生信息
void modify_stu(void)
{
	system("clear");
	printf("请输入需要修改信息的学生学号\n");		//修改学生信息需提供学生学号
	char check[12]={};		//定义数组接收输入的学号
	if(-1==input(1,check))	return;		//调用输入函数，如果输入学号不为8位则重新输入直至格式正确
	for(int i=0;i<STU;i++)
	{
		if(!strcmp(stup[i].id,check))		//在所有学生中查找该学生，找到后先显示学生信息
		{
			system("clear");
			printf("姓名：%s\n性别：%s\n学号：%s\n在校状态：%s\n语文成绩：%.2f\n数学成绩：%.2f\n英语成绩：%.2f\n",
			stup[i].name,
			stup[i].sex,
			stup[i].id,
			stup[i].situation==1?"在校":"退学",
			stup[i].chinese,
			stup[i].math,
			stup[i].english);
			
			puts("请选择需要修改的信息");		//选择要修改的内容
			puts("1、姓名");
			puts("2、性别");
			puts("3、语文成绩");
			puts("4、数学成绩");
			puts("5、英语成绩");
			stdin->_IO_read_ptr = stdin->_IO_read_end;	//清空输入缓冲区
			switch(getch())					//更改各项信息
			{
				case '1':
					//	输入姓名
					printf("请输入学生姓名:\n");
					char check[25] = {};//	存储输入的字符串
					if(-1==input(2,check))	return;//	判断输入字符串长度是否合法
					strcpy(stup[i].name,check);//	确认长度后存储入结构体
					break;
				case '2':
					//	输入性别部分
					printf("请输入学生性别（男/女）:\n");
					char sex[6] = {};//	存储输入的字符串
					if(-1==input(3,check))	return;
					strcpy(stup[i].sex,sex);//	存储性别
					break;
				case '3':
					puts("请输入更改后的语文成绩");
					do{
						scanf("%6f",&stup[i].chinese);
						if(stup[i].chinese<0||stup[i].chinese>150)
						puts("成绩输入有误，请重新输入\n如果不想继续输入，按‘esc’退出\n");
						else break;
						if(1==whether_exit())	return;
					}while(1);
					break;
				case '4':
					puts("请输入更改后的数学成绩");
					do{
						scanf("%6f",&stup[i].math);
						if(stup[i].math<0||stup[i].math>150)
						puts("成绩输入有误，请重新输入\n如果不想继续输入，按‘esc’退出");
						else break;
						if(1==whether_exit())	return;
					}while(1);
					break;
				case '5':
					puts("请输入更改后的英语成绩");
					do{
						scanf("%6f",&stup[i].english);
						if(stup[i].english<0||stup[i].english>150)
						puts("成绩输入有误，请重新输入\n如果不想继续输入，按‘esc’退出");
						else break;
					}while(1);
					break;
				default :return;
			}
			puts("修改成功");		
			anykey_continue();
			return;
		}
	}
	puts("查无此人");			//所有学生中没找到该学生提示信息
	anykey_continue();
	return;
}
	
			
	//录入成绩
void input_score(void)
{ 
	
	system("clear");
	char check[12]={};		//定义数组接收需要录入成绩的学生学号
	puts("请选择录入成绩的模式");		//有两种方式录入成绩
	puts("1、单个录入");
	puts("2、批量录入");
	switch(getch())
	{
		case '1':
			system("clear");
			puts("请输入需要录入成绩的学生学号");
			if(-1==input(1,check))	return;		//调用输入函数，如果输入学号不为8位则重新输入直至格式正确
			for(int i=0;i<STU;i++)
			{
				if(!strcmp(stup[i].id,check))		//在所有学生中找到相应同学位置，并录入各科成绩
				{
					system("clear");
					puts("请分别录入语文、数学、英语成绩");
					scanf("%6f %6f %6f",&stup[i].chinese,&stup[i].math,&stup[i].english);
					puts("录入成功");
					printf("%.2f %.2f %.2f\n",stup[i].chinese,stup[i].math,stup[i].english);
					anykey_continue();
					return;
				}
			}
			puts("查无此人");
			anykey_continue();
			return;
		
		case '2': 
			system("clear");
			read_infomation(1);
	} 
	anykey_continue();
	return;
}
