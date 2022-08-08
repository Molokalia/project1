#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "tools.h"
#include "sign.h"
#include "readandstore.h"

//	登录函数，返回登录的学生的结构体在数组中的位置
int sign_in(int role)
{	
	int num = 0,index = 0;
	//	判断帐号输入是否正确
	num = judge_id(role);
	if(-1 == num)
	{
		return -1;	//	输入的帐号不正确
	}				//	帐号无误则继续进行后续的判断
	
	if((1 == role && -1 == stup[num].account) || (2 == role && -1 == teap[num].account))
	{
		printf("帐号已锁定,请找上级解锁\n");
		anykey_continue();
		return -1;
	}
	
	//	判断密码输入是否正确
	index = judge_password(role,num);
	if(-1 == index) return -1;	//	密码错误，帐号被锁定
	else return num;	//	密码正确
}

//	判断帐号是否正确，正确返回对应位置，错误返回-1
int judge_id(int role)
{
	int num = 0;
	//	用数组接收输入的帐号
	char str1[20] = {};		
	while(1)
	{	
		system("clear");
		printf("请输入帐号：\n");
		if(-1==input(1,str1))	return -1;		//按了esc返回-1
		num = id_find(role,str1);	//	查找有无这个帐号
		if(3 != role && (1 != stup[num].situation || 1 != teap[num].situation))
		{
			puts("您已无法登录");
			sleep(1);
			return -1;
		}
		if(-1 == num)	//	未查找到此帐号或已经退学
		{
			printf("请检查输入的帐号是否正确！\n");
			anykey_continue();
			system("clear");
			return -1;
		}
		else return num;	//	找到则返回对应结构体的位置
	}
}

//	判断密码是否正确，正确返回对应位置，错误返回-1
int judge_password(int role,int num)
{
	char str[256] = {};//	接收字符串
	int cnt = 3;
	while(cnt--)	//	只有三次输入错误的机会
	{
		input_password(str);	//	接收密码
		if(6 != strlen(str))	//	判断长度
		{
			printf("请正确输入6位密码！\n不想继续输入按‘esc退出’\n");
			if(1==whether_exit())	return -1;
			system("clear");
			clean_arr(str,sizeof(str));//	清空数组
			cnt++;
			continue;
		}
		if(1 == role)		//学生操作
		{
			if(0 == strcmp(stup[num].password,str)) //	验证密码是否一致
			{
				printf("登录成功！\n");
				sleep(2);
				system("clear");
				return num;		//	返回下标
			}
			else
			{
				printf("密码错误，还剩%d次机会\n不想继续输入按‘esc退出\n",cnt);	//	错误则提示信息
				if(1==whether_exit())	return -1;
				system("clear");
				clean_arr(str,sizeof(str));//	清空数组
			}
		}
		else if(2 == role)
		{
			if(0 == strcmp(teap[num].password,str)) //	验证密码是否一致
			{
				printf("登录成功！\n");
				sleep(2);
				system("clear");
				return num;
			}
			else
			{
				printf("密码错误，还剩%d次机会\n不想继续输入按‘esc退出\n",cnt);//	错误则提示信息
				if(1==whether_exit())	return -1;
				system("clear");	
				clean_arr(str,sizeof(str));//	清空数组
			}
		}
		else if(3 == role)
		{
			if(0 == strcmp(hea.password,str))//	验证密码是否一致
			{
				printf("登录成功！\n");
				sleep(2);
				system("clear");
				return num;
			}
			else
			{
				printf("密码错误\n不想继续输入按‘esc退出\n");//	错误则提示信息
				if(1==whether_exit())	return -1;
				system("clear");
				clean_arr(str,sizeof(str));
				cnt++;	//	返还次数，校长没有输错的次数限制
			}
		}
	}
	if(1 == role) stup[num].account = -1;	//	输错3次则锁定帐号
	else if(2 == role) teap[num].account = -1;
	printf("密码错误三次，帐号已锁定\n");
	anykey_continue();
	system("clear");
	return -1;
}

//首次登录1/-1
void first_log(int role,int num)
{
	if(1 == role)//学生操作
	{
		if(1 == stup[num].is_first_sign)//判断是否首次登录
		{
			force_mod_pass(1,num);	//首次登录强制修改密码
			return;
		}
		else return;
	}
	else if(2 == role)//学生操作
	{
		if(1 == teap[num].is_first_sign)//判断是否首次登录
		{
			force_mod_pass(2,num);//首次登录强制修改密码
			return;
		}
	}
	else if(3 == role)//学生操作
	{
		if(1 == hea.is_first_sign)//判断是否首次登录
		{
			force_mod_pass(3,num);//首次登录强制修改密码
			return;
		}
		else return;
	}
}

//	强制修改密码
void force_mod_pass(int role,int num)
{
	char str1[9] = {},str2[9] = {};	//	存储两次输入的密码
	system("clear");
	printf("首次登录请修改密码\n");	
	for(;;)
	{	
		printf("请输入6位数字作为新密码：\n");
		if(-1==input(4,str1))	return;
		if(0 == strcmp(str1,"000000"))		//	不能与默认密码相同
		{
			printf("密码不能和默认密码相同！\n");
			anykey_continue();
			system("clear");
			continue;
		}
		printf("请再次输入密码：\n");
		if(-1==input(4,str2))	return;
		if(0 != strcmp(str1,str2))	//	两次输入的密码应该一致
		{
			printf("输入有误，请重新输入\n");
			anykey_continue();
			system("clear");
		}
		else
		{
			if(1 == role)
			{ 
				strcpy(stup[num].password,str2);	//	保存新密码
				stup[num].is_first_sign = -1;	//	改变首次登录的标志，-1表示不是首次登录
			}
			else if(2 == role) 
			{
				strcpy(teap[num].password,str2);//	保存新密码
				teap[num].is_first_sign = -1;//	改变首次登录的标志，-1表示不是首次登录
			}
			else if(3 == role)
			{
				strcpy(hea.password,str2);//	保存新密码
				hea.is_first_sign = -1;//	改变首次登录的标志，-1表示不是首次登录
			}
			return;
		}
	}
}
