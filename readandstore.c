#include <stdio.h>
#include <string.h>
#include "tools.h"
#include "student.h"
#include "teacher.h"
#include "headmaster.h"
#include "readandstore.h"

//	从文件中读取数据
void read_out(void)
{
		//打开文件
		FILE* fp1 = fopen("student.txt","r");
		if(NULL == fp1)
		{
			perror("fopen");
			return;
		}
		FILE* fp2 = fopen("teacher.txt","r");	
		if(NULL == fp2)
		{
			perror("fopen");
			return;
		}
		FILE* fp3 = fopen("headmaster.txt","r");	
		if(NULL == fp3)
		{
			perror("fopen");
			return;
		}
		
			//读取数据
		for(int i=0; i<STU; i++)
		{
			f_scanf(1,i,fp1);
		}
		for(int i=0; i<TEA; i++)
		{
			f_scanf(2,i,fp2);
		}
		f_scanf(3,0,fp3);
	
		//关闭文件，指针置空	
		fclose(fp1);
		fp1 = NULL;
		fclose(fp2);
		fp2 = NULL;
		fclose(fp3);
		fp3 = NULL;
		return;
}

void store_in(void)
{
	//打开文件
	FILE* fp1 = fopen("student.txt","w");
	if(NULL == fp1)
	{
		perror("fopen");
		return;
	}
	FILE* fp2 = fopen("teacher.txt","w");
	if(NULL == fp2)
	{
		perror("fopen");
		return;
	}
	FILE* fp3 = fopen("headmaster.txt","w");	
	if(NULL == fp3)
	{
		perror("fopen");
		return;
	}	
	
	for(int i=0; i<STU; i++)
	{	
		//	向文件中写入信息
		if(0 != stup[i].situation)
			f_printf(1, i, fp1);
	}
	for(int i=0; i<TEA; i++)
	{	
		if(teap[i].situation)
			f_printf(2, i, fp2);
	}
	f_printf(3,0,fp3);
		
	//关闭文件，指针置空	
	fclose(fp1);
	fp1 = NULL;
	fclose(fp2);
	fp2 = NULL;
	fclose(fp3);
	fp3 = NULL;
	return;
}
//从文件中读取信息
void f_scanf(int role,int num,FILE* fp)
{
	if(1 == role)
	{
		fscanf(fp,"%s\t%s\t%s\t%s\t%hhd\t%hhd\t%hhd\t%f\t%f\t%f",
		stup[num].name,
		stup[num].sex,
		stup[num].id,
		stup[num].password,
		&stup[num].situation,
		&stup[num].account,
		&stup[num].is_first_sign,
		&stup[num].chinese,
		&stup[num].math,
		&stup[num].english);
		for (int i=0; i<6; i++)
			stup[num].password[i] +=i;
		if (stup[num].situation != 0)
		{
			for (int i=0; i<8;i++) 
			stup[num].id[i] = max_id[i];
			max_id[7] ++;
			for (int j=7;j>0;j--)
			{
				if (!(max_id[j] >= '0' && max_id[j] <= '9'))
				{
					max_id[j-1]++;
					max_id[j] = '0';
				}
			}
		}
	}
	if(2 == role)
	{
		fscanf(fp,"%s\t%s\t%s\t%s\t%hhd\t%hhd\t%hhd",
		teap[num].name,
		teap[num].sex,
		teap[num].id,
		teap[num].password,
		&teap[num].situation,
		&teap[num].account,
		&teap[num].is_first_sign);
		for (int i=0; i<6; i++)
			teap[num].password[i] +=i;
	}
	if(3 == role)
	{
		fscanf(fp,"%s\t%s\t%s\t%hhd",
		hea.name,
		hea.id,
		hea.password,
		&hea.is_first_sign);
		for (int i=0; i<6; i++)
			hea.password[i] +=i;
	}
}

//向文件中写入信息
void f_printf(int role, int num, FILE* fp)
{
	if(1 == role)
	{
		for (int i=0; i<6; i++)
			stup[num].password[i] -=i;
		fprintf(fp,"%s\t%s\t%s\t%s\t%hhd\t%hhd\t%hhd\t%f\t%f\t%f\n",
		stup[num].name,
		stup[num].sex,
		stup[num].id,
		stup[num].password,
		stup[num].situation,
		stup[num].account,
		stup[num].is_first_sign,
		stup[num].chinese,
		stup[num].math,
		stup[num].english);
	}
	else if(2 == role)
	{
		for (int i=0; i<6; i++)
			teap[num].password[i] -=i;
		fprintf(fp,"%s\t%s\t%s\t%s\t%hhd\t%hhd\t%hhd\n",
		teap[num].name,
		teap[num].sex,
		teap[num].id,
		teap[num].password,
		teap[num].situation,
		teap[num].account,
		teap[num].is_first_sign);
	}
	if(3 == role)
	{
		for (int i=0; i<6; i++)
			hea.password[i] -=i;
		fprintf(fp,"%s\t%s\t%s\t%hhd",
		hea.name,
		hea.id,
		hea.password,
		hea.is_first_sign);
	}
}

/*批量录入时读取学生信息或成绩
参数select选择读入信息的模式
1为录入成绩，2为录入个人信息
无返回值*/
void read_infomation(int select)
{
	char str[512] = {};	//	存储文件路径
	int flag = 1,cnt = 0,num = 0;//	flag用于存储fscanf的返回值，cnt为结构体数组下标，num为需要录入学生的数量
	msg_show("请输入要录入信息的文件路径\n",0);
	msg_show("例：/home/kz1/C_prj/score.txt\n",1.5);//	显示提示信息
	stdin->_IO_read_ptr = stdin->_IO_read_end;
	scanf("%s",str);	//	接收文件路径
	for(;;)
	{
		msg_show("请输入要录入信息的学生数量(最大为1000)\n",0);
		scanf("%d",&num);	//	接收录入学生的数量
		if(0 > num || STU < num)//	判断数量的合法性
		{
			printf("批量录入上限为%d,请重新输入\n",STU);
		}
		else break;
	}
	//以只读方式打开文件
	FILE* fp = fopen(str,"r");
	if(NULL == fp)
	{
		perror("fopen");
		return;
	}
	
	if(1 == select)	//	录入成绩
	{
		while(num--)
		{
			flag = fscanf(fp,"%s %f %f %f",	//	读取学号与三科成绩
			stup1[cnt].id,
			&stup1[cnt].chinese,
			&stup1[cnt].math,
			&stup1[cnt].english);
			cnt++;	//	读取到的学生数量+1
		}
		for(int i=0; i<=cnt; i++)
		{
			num = id_find(1,stup1[i].id);	//	查找有没有这个学号，找到的话返回下标，失败返回-1
			if(-1 == num)//	返回-1时不录入这个成绩并询问是否继续
			{
				printf("未找到id为%s的学生，导入失败\n",stup1[i].id);
				printf("是否继续导入其余学生信息？(是请输入y，否请输入n)\n");
				if(0 == is_continue())//	判断接收到的字符
				{
					fclose(fp);
					fp = NULL;
					return;
				}
			}
			else
			{
				stup[num].chinese = stup1[i].chinese;
				stup[num].math = stup1[i].math;
				stup[num].english = stup1[i].english;
			}
		}
	}
	else if(2 == select)	//	录入个人信息
	{
		while(num--)//	从文件中读取信息
		{
			char str[9] = {};
			flag = fscanf(fp,"%s %s",
			stup1[cnt].name,
			stup1[cnt].sex);//	接收姓名和性别
			
			stup1[cnt].situation = 1;//	设置为在校状态
			strcpy(stup1[cnt].id,str);//	存储学号
			if(!stup1[cnt].sex[0])	cnt--;
			cnt++;
			
		}
		
		//	将读取出的信息存入结构体数组
		for(int i=0; i<STU && cnt>0; i++)
		{
			if(0 == stup[i].situation)
			{
				for (int j=7;j>0;j--)
				{
					if (!(max_id[j] >= '0' && max_id[j] <= '9'))
					{
						max_id[j-1]++;
						max_id[j] = '0';
					}
				}
				strcpy(stup[i].name,stup1[cnt-1].name);
				strcpy(stup[i].sex,stup1[cnt-1].sex);
				strcpy(stup[i].id,max_id);
				strcpy(stup[i].password,"000000");
				stup[i].situation = stup1[cnt-1].situation;
				stup[i].account=1;
				stup[i].is_first_sign=1;
				
				cnt--;			//	待存储的学生数-1
				max_id[7]++;	//	学号末位增加1
			}
		}			
	}
	msg_show("录入成功！\n",1.5);
	fclose(fp);
	fp = NULL;
	return;
}
