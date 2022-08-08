#include <stdio.h>
#include <stdlib.h>
#include <getch.h>
#include "student.h"
#include "tools.h"
#include "menu.h"
#include "sign.h"
#include "operation.h"
#include "readandstore.h"

void student(void)
{
	printf("欢迎您，同学\n");
	anykey_continue();			//按任意键继续

	int num = 0;				//定义变量接收登录的学生的结构体在数组中的位置
	num = sign_in(1);			//	调用登录函数，登录成功则返回这个帐号在数组中的位置
	if(num == -1) return;		//	如果没有找到帐号或者登录失败则返回-1
	first_log(1,num);			//	判断该帐号是否初次登录，是则强制修改密码
	
	for(;;)
	{
		switch(menu2())			//	教师的可选操作菜单
		{
			case '1':	check_results(num);		break;	//查询成绩
			case '2':	check_inform(num);		break;	//查看个人信息
			case '3':	change_password(1,num);	break;	//修改密码
			case '4':	return;
		}
	}
}

//查询成绩
void check_results(int n)
{
	int cnt=0;							//定义变量计算总学生数
	float sum_chinese=0,avg_chinese=0;	//	定义变量：各科总成绩、平均成绩
	float sum_math=0,avg_math=0;
	float sum_english=0,avg_english=0;
	
	system("clear");
	puts("你的个人成绩为：");
	printf("语文：%6.2f 数学：%6.2f 英语：%6.2f\n",
		stup[n].chinese,
		stup[n].math,
		stup[n].english);//先显示个人各科成绩
		
	while(stup[cnt].situation==1)	cnt++;		//	通过在校学生计总学生数
	
	for(int i=0;i<cnt-1;i++)	//对各科成绩由高到底排序
	{
		if(stup[i].situation==1)
		{
			for(int j=i+1;j<cnt;j++)
			{
				if(stup[i].chinese<stup[j].chinese)
					stup[i].chinese=stup[j].chinese;
				if(stup[i].math<stup[j].math)
					stup[i].math=stup[j].math;
				if(stup[i].english<stup[j].english)
					stup[i].english=stup[j].english;
			}	
		}	
	}
	
	puts("各科成绩排名:");
	puts("语文      数学      英语");
	
	for(int i=0;i<cnt;i++)		//由高到底显示各科成绩，格式为显示6个字符宽度，保留2位小数点
	{
		printf("%6.2f   %6.2f   %6.2f\n",stup[i].chinese,stup[i].math,stup[i].english);
		sum_chinese+=stup[i].chinese;
		sum_math+=stup[i].math;
		sum_english+=stup[i].english;		//计算各科成绩总和
	}
	
	avg_chinese=sum_chinese/cnt;
	avg_math=sum_math/cnt;		//计算各科成绩平均值
	avg_english=sum_english/cnt;
	
	printf("各科成绩最高分：\n语文：%.2f 数学：%.2f 英语：%.2f\n",
		stup[0].chinese,
		stup[0].math,		//显示各科成绩最高分、最低分、平均分
		stup[0].english);
		
	printf("各科成绩最低分：\n语文：%.2f 数学：%.2f 英语：%.2f\n",
		stup[cnt-1].chinese,
		stup[cnt-1].math,
		stup[cnt-1].english);
		
	printf("各科成绩平均分：\n语文：%.2f 数学：%.2f 英语：%.2f\n",
		avg_chinese,
		avg_math,
		avg_english);
	
	anykey_continue();
}

	//查询个人信息	i为学生所在位置
void check_inform(int i)
{
	system("clear");
	printf("姓名：%s \n性别：%s \n学号：%s \n在校状态：%s\n",
	stup[i].name,
	stup[i].sex,
	stup[i].id,
	1 == stup[i].situation ? "在校" : "退学");
	
	anykey_continue();
}
