#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getch.h>
#include <stdbool.h>
#include "tools.h"
#include "readandstore.h"
#include "operation.h"


	//修改密码
void change_password(int role,int num)
{
	char old_password[8] = {};
	if (role == 1)
	{
		for(;;)
		{	
			printf("请输入原密码：");
			if(-1==input(4,old_password))	return;
			if (0 == strcmp(old_password,stup[num].password))
			{
				printf("请输入新密码：");
				if(-1==input(4,stup[num].password))	return;
				printf("修改成功！\n");
				sleep(1);
				return;
			}
			else 
			{
				printf("输入错误！\n");
				sleep(1);
			}
		}
	}
	else if(role == 2)
	{
		for(;;)
		{	
			printf("请输入原密码：");
			if(-1==input(4,old_password))	return;
			if (0 == strcmp(old_password,teap[num].password))
			{
				printf("请输入新密码：");
				if(-1==input(4,stup[num].password))	return;
				printf("修改成功！\n");
				sleep(1);
				return;
			}
			else printf("输入错误！\n");
		}
	}
}
	//添加信息
void add_inform(int n)
{
	if (n ==1)
	{
		puts("请选择录入信息的方式:");
		puts("1、单个录入");
		puts("2、批量录入");
		switch(getch())
		{
			case '1':
			{
				for (int i=0; i<STU; i++)
				{
					if (strcmp(max_id,stup[i].id)<0)
					{
						strcpy(max_id,stup[i].id);
					}
				}
				
				for (int i=0; i<STU; i++)
				{
					if (stup[i].situation == '\0')
					{
						
						//	输入姓名
						char check[25] = {};//	存储输入的字符串
						printf("请输入学生姓名:\n");
						if(-1==input(2,check))	return;//	判断输入字符串长度是否合法
						strcpy(stup[i].name,check);//	确认长度后存储入结构体
						
						//	输入性别部分
						char sex[6] = {};//	存储输入的字符串
						printf("请输入学生性别（男/女）:\n");
						if(-1==input(3,sex))	return;	
						strcpy(stup[i].sex,sex);//	存储性别
						
						//为结构体内其他成员赋值
						strcpy(stup[i].password,"000000");//	设置默认密码
						stup[i].situation=1;//	设置为在职状态
						stup[i].account=1;//	设置帐号为未锁定
						stup[i].is_first_sign=1;//	设置为首次登录
						
						for (int j=0; j<9; j++)
							stup[i].id[j] = max_id[j];//	存储学号
						max_id[7] ++;
						
						for (int j=7;j>0;j--)
						{
							if (!(max_id[j] >= '0' && max_id[j] <= '9'))
							{
								max_id[j-1]++;
								max_id[j] = '0';
							}
						}
						printf("添加成功！\n");
						sleep(1);
						return;
					}
				}
			}
			case '2': 
				system("clear");
				read_infomation(2);
		}
	}
	else if(n == 2)
	{
		for (int i=0; i<TEA; i++)
		{
			if (teap[i].situation == '\0')
			{
				//	输入姓名部分
				char check[25] = {};//	存储输入的字符串
				printf("请输入教师姓名:\n");
				if(-1==input(2,check))	return;		//	判断输入字符串长度是否合法
				strcpy(teap[i].name,check);	//	确认长度后存储入结构体
				
				//	输入性别部分
				char sex[6] = {};//	存储输入的字符串
				printf("请输入教师性别（男/女）:\n");
				if(-1==input(3,sex))	return;
				strcpy(teap[i].sex,sex);//	存储性别
				
				//输入工号部分
				char id[20] = {};
				printf("请输入工号：\n");
				if(-1==input(1,id))	return;
				while(-1 != id_find(2,id))
				{
					printf("工号已存在，请重新输入\n");
					clean_arr(id,4);//	清空性别数组
					if(-1==input(1,id))	return;
				}
				strcpy(teap[i].id,id);//	存储工号
				
				strcpy(teap[i].password,"000000");//	设置默认密码
				teap[i].situation=1;//	设置为在职状态
				teap[i].account=1;//	设置帐号为未锁定
				teap[i].is_first_sign=1;//	设置为首次登录
				printf("添加成功！\n");
				sleep(1);
				return;
			}
		}
	}
}
	
 // 删除信息
void del_inform(int n)
{
	int flag = 0;        	//定义变量存储是否找到数据
	char id1[11] = {};       //定义数组存储第一次输入的学号/工号
	char id2[11] = {};       //定义数组存储第二次输入的学号/工号
	if (n == 1)        		//如果需要删除学生信息
	{
		printf("请输入学生学号：");     //提示输入学生学号
		if(-1==input(1,id1))	return;     //将学生学号存储在数组内
		for (int i=0; i<STU; i++)     //遍历学生数组
		{
			flag = 0;
			for (int j=0; j<9; j++)     //从低位到高位比较数组的值
			{
				if (stup[i].id[j] !=id1[j])   //若输入的学号和原学号不相等
				flag = 1;    //flag值置为1
			}
			if (flag == 0)      //如果学号与输入学号相等
			{
				printf("请再次输入学生学号：");   //提示再次输入学号
				if(-1==input(1,id2))	return;    //将学生学号存储在数组内
				if (!strcmp(id1, id2))    //如果两次输入相同
				{
					stup[i].situation =-1;   //将学生在校状态设置为离校
					printf("删除成功！\n");   //提示删除成功
					sleep(1);    //延时函数，用于延时显示
					return;     //删除完成，返回函数
				}
				else      //如果两次输入不相同
				{
					printf("输入错误！\n");   //提示输入错误
					sleep(1);    //延时函数，用于延时显示
					return;     //功能完成，返回函数
				}
			}
		}
		if (flag == 1)       //如果一直没有找到
		{
			printf("未找到！\n");     //提示未找到
			sleep(1);      //延时函数，用于延时显示
			return;       //功能完成，返回显示
		}
	}
	if (n == 2)        //如果需要删除老师信息
	{
		printf("输入教师工号：");     //提示输入老师工号
		if(-1==input(1,id1))	return;     //将老师工号存储在数组内
		for (int i=0; i<TEA; i++)     //遍历老师数组
		{
			flag = 0;
			for (int j=0; j<9; j++)     //从低位到高位比较数组的值
			{
				if (teap[i].id[j] !=id1[j])   //若输入的工号和原工号不相等
				flag = 1;    //flag值置为1
			}
			if (flag == 0)      //如果工号与输入工号相等
			{
				printf("请再次输入老师工号：");   //提示再次输入工号
				if(-1==input(1,id2))	return;   //将老师工号存储在数组内
				if (!strcmp(id1, id2))    //如果两次输入相同
				{
					teap[i].situation =-1;   //将老师的在校状态设置为离职
					printf("删除成功！\n");   //提示删除成功
					sleep(1);    //延时函数，用于延时显示
					return;     //删除完成，返回函数
				}
				 else      //如果两次输入不相同
				{
					printf("输入错误！\n");   //提示输入错误
					sleep(1);    //延时函数，用于延时显示
					return;     //功能完成，返回函数
				}
			}
		}
		if (flag == 1)       //如果一直没有找到
		{
			printf("未找到！\n");     //提示未找到
			sleep(1);      //延时函数，用于延时显示
			return;       //功能完成，返回显示
		} 
	}
}

 //重置密码
void reset_code(int role)
{
	system("clear");
	char id_s[11]={};	//定义数组接收帐号
	puts("请输入帐号");  
	if(-1==input(1,id_s))	return;	//确定帐号为8位
	stdin->_IO_read_ptr = stdin->_IO_read_end;
	if(role == 1) 	//学生
	{
		for(int i=0;i<STU;i++)
		{
			if(!strcmp(stup[i].id,id_s))	//在所有学生中查找该学生位置
			{
   				printf("%s %s\n",stup[i].name,stup[i].id);
   				puts("请确认是否重置密码（y/n）");
   				switch(getch())
   				{
    				case 'y':
						stup[i].is_first_sign=1;
						strcpy(stup[i].password,"000000");	//重置密码后密码为初始密码'000000',再次登录需强制修改密码
						puts("密码重置成功");
						anykey_continue();
						return;
					case 'n':
						anykey_continue();	//选择不重置结束函数
						return;
				}
			}
		}
		puts("查无此人");		//在所有学生中没找到该学生提示信息
		anykey_continue();	
		return;
	}
	if(role == 2) 	//重置密码对象为老师
	{
		for(int i=0;i<TEA;i++)
		{
			if(!strcmp(teap[i].id,id_s))
			{
   				printf("%s %s\n",teap[i].name,teap[i].id);
   				puts("请确认是否重置密码（y/n）");
   				switch(getch())
   				{
					case 'y':
						teap[i].is_first_sign=1;
						strcpy(teap[i].password,"000000");
						puts("密码重置成功");
						anykey_continue();
						return;
					case 'n':
						anykey_continue();
						return;
				}
			}
		}
		puts("查无此人");
		anykey_continue();
		return;
	}
	if(role == 3) 	//重置密码对象为老师
	{
		if(!strcmp(hea.id,id_s))
		{
   			printf("%s %s\n",hea.name,hea.id);		//在所有学生中没找到该学生提示信息
   			puts("请确认是否重置密码（y/n）");
   			switch(getch())
   			{
				case 'y':
					hea.is_first_sign=1;
					strcpy(hea.password,"000000");
					puts("密码重置成功");
					anykey_continue();
					return;
				case 'n':
					anykey_continue();
					return;
			}
   		}
		puts("查无此人");
		anykey_continue();
		return;
	}
}

	//	显示在校信息
void show_inschool(int role)
{
	printf("----------\n");
	if(1 == role)
	{	
		for(int i=0; i<STU; i++)
		{
			if(1 == stup[i].situation)
			{
				printf("%s %s %s\n",stup[i].name,stup[i].sex,stup[i].id);
			}
		}
		anykey_continue();
	}
	if(2 == role)
	{	
		for(int i=0; i<TEA; i++)
		{
			if(1 == teap[i].situation)
			{
				printf("%s %s %s\n",teap[i].name,teap[i].sex,teap[i].id);
			}
		}
		anykey_continue();
	}
}

	//显示离校信息
void show_leaveschool(int role)
{
	system("clear");
	if(1 == role)
	{	
		for(int i=0; i<STU; i++)
		{
			if(-1 == stup[i].situation)
			{
				printf("%s %s %s\n",stup[i].name,stup[i].sex,stup[i].id);
			}
		}
		anykey_continue();
	}
	if(2 == role)
	{	
		for(int i=0; i<TEA; i++)
		{
			if(-1 == teap[i].situation)
			{
				printf("%s %s %s\n",teap[i].name,teap[i].sex,teap[i].id);
			}
		}
		anykey_continue();
	}
}

	//解锁帐号
void unlock(int role)
{
	char check[11] = {};
	int num = 0;
	if(1 == role)
	{
		printf("请输入要解锁的id：\n");
		if(-1==input(1,check))	return;
		num = id_find(1,check);
		printf("请确认是否要解锁这个帐号(y/n)\n");
		stdin->_IO_read_ptr=stdin->_IO_read_end;
		switch(getch())
		{
			case 'y': 
				stup[num].account = 1;
				printf("解锁成功\n");
				anykey_continue();
				break;
			case 'n':
				anykey_continue();
				return;
		}
	}
	if(2 == role)
	{
		printf("请输入要解锁的id：\n");
		if(-1==input(1,check))	return;
		num = id_find(2,check);
		printf("请确认是否要解锁这个帐号(y/n)\n");
		stdin->_IO_read_ptr=stdin->_IO_read_end;
		switch(getch())
		{
			case 'y':
				teap[num].account = 1;	
				printf("解锁成功\n");
				anykey_continue();
				break;
			case 'n':
				anykey_continue();
				return;
		}
	}
}
