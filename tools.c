#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getch.h>
#include <stdbool.h>
#include "tools.h"
#include "readandstore.h"
#include "operation.h"

stu* stup = NULL;	//	存放学生信息
tea* teap = NULL;	//	存放教师信息
stu* stup1 = NULL;	//	存放成绩信息
head hea;
char max_id[9] = "10000000";

//	判断是否继续
bool is_continue(void)
{
	for(;;)
	{
		if('y' == getch())
		{
			return true;
		}
		else if('n' == getch())
		{
			return false;
		}
		else
		{
			continue;
		}
	}
}

//	判断字符是不是字母或数字
bool is_num_letter(char str)
{
	if((str>47 && str<58) || (str>64 && str<91) || (str>96 && str<123))
		return true;
	else
		return false;
}

//	输入时不直接显示密码
void input_password(char* str)
{
	system("clear");
	printf("请输入密码:\n");
	for(int i=0; i<256; i++)	//	最多存储256个字符
	{
		stdin->_IO_read_ptr = stdin->_IO_read_end;
		if(str[i] = getch())	// 获取字符
		{
			if(is_num_letter(str[i]))	//	判断是不是字符或数字	
			{
				printf("*");
			}
			else if(10 == str[i])	//	判断收到回车键则结束输入
			{
				printf("\n");
				str[i] = 0;
				break;
			}
			else if(127 == str[i])	//	判断收到回车键则消除一格并且
			{
				str[i] = 0;
				str[i-1] = 0;
				i  -= 2;
				printf("\b \b");
			}
			else
			{
				str[i] = 0;
				i--;
				continue;
			}
		}
	}
	stdin->_IO_read_ptr = stdin->_IO_read_end;
}

//	打印提示信息
void msg_show(const char* msg,float sec)
{
	printf("%s",msg);
	fflush(stdout);		//	清空输出缓冲区
	usleep(sec*1000000);//睡眠sec秒
}

//	按任意键继续函数
void anykey_continue(void)
{
	puts("请按任意键继续...");
	stdin->_IO_read_ptr = stdin->_IO_read_end;
	getch();
}

//	清空数组
void clean_arr(char arr[],int len)
{
	for(int i=0; i<len; i++)
	{
		arr[len] = 0;
	}
}

//	在数组中查找id,str为要查找的id的首地址，role为角色选择，1为学生，2为教师
int id_find(int role,char* str)
{
	if(1 == role)	//	学生
	{
		for(int i=0; i<STU; i++)
		{
			if(0 == strcmp(str,stup[i].id))
			{
				return i;	//	返回对应id的位置
			}
		}
		return -1;		//	未找到id
	}
	else if(2 == role)	//	教师
	{
		for(int i=0; i<TEA; i++)
		{
			if(0 == strcmp(str,teap[i].id))
			{
				return i;
			}
		}
		return -1;
	}
	else if(3 == role)
	{
		return strcmp(str,hea.id) ? -1 : 0;
	}
	else
	{
		printf("输入信息有误，请检查\n");
		return -1;
	}
}

int whether_exit(void)
{
	stdin->_IO_read_ptr = stdin->_IO_read_end;
	if (getch() == 27)
	return 1;
}

/*
判断姓名与工号或学号是否合法
role=1表示学生，role = 2表示老师
check为需要检查的字符串首地址
*/
int input(int role,char *check)
{
	 if(role==1)	//	判断工号
	 {
	  	do{
        	fgets(check,11,stdin);
           	if(strlen(check)!=9)
           	{
             	 puts("输入有误，请重新输入8位有效帐号,如果不想继续输入，请输入‘esc’退出");
             	 stdin->_IO_read_ptr = stdin->_IO_read_end;
             	 if(whether_exit()==1)	return -1;
           	}
           	else 
          	{
          		for(int i=0;i<12;i++)
          		{
          			if(check[i]=='\n')
          			{
          				check[i]='\0';
          				break;
          			}	
          		}
          		break;
          	}		
       }while(1);

	 }
	 if(role==2)	//	判断姓名
	 {
	 	do{
            fgets(check,25,stdin);
            if(strlen(check)>21)
            {
                puts("输入有误，请重新输入,如果不想继续输入，请输入‘esc’退出");
                stdin->_IO_read_ptr = stdin->_IO_read_end;
                if(whether_exit()==1)	return -1;
            }
          	else 
          	{
          		for(int i=0;i<25;i++)
          		{
          			if(check[i]=='\n')
          			{
          				check[i]='\0';
          				break;
          			}	
          		}
          		break;
          	}		
        }while(1);
	 }
	 
	 if(role==3)	//	判断性别
	 {
	  	do{
           	fgets(check,6,stdin);           
          	for(int i=0;i<6;i++)
          	{
          		if(check[i]=='\n')
          		{
          			check[i]='\0';
          			break;
          		}	
          	}
          	if(strcmp(check,"男") != 0 && strcmp(check,"女") != 0)//	判断性别输入是否合法
			{
				printf("性别格式错误！请重新输入学生性别(男/女):\n如果不想继续输入，请输入‘esc’退出\n");
				stdin->_IO_read_ptr = stdin->_IO_read_end;
				if(whether_exit()==1)	return -1;
			}
			else break;		
       }while(1);
	}
	if(role==4)	//	判断密码
	 {
	 	do{
            fgets(check,9,stdin);
            if(strlen(check)!=7)
            {
                puts("密码输入有误，请重新输入6位密码,如果不想继续输入，请输入‘esc’退出");
                stdin->_IO_read_ptr = stdin->_IO_read_end;
                if(whether_exit()==1)	return -1;
            }
           else 
          	{
          		for(int i=0;i<9;i++)
          		{
          			if(check[i]=='\n')
          			{
          				check[i]='\0';
          				break;
          			}	
          		}
          		break;
          	}		
        }while(1);
	 }
}
