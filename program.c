#include <stdlib.h>
#include "program.h"
#include "tools.h"
#include "readandstore.h"
#include "teacher.h"
#include "student.h"
#include "headmaster.h"
#include "menu.h"

void init(void)				//	初始化程序
{
	stup = calloc(STU,sizeof(stu));	//	申请内存
	teap = calloc(TEA,sizeof(tea));
	stup1 = calloc(STU,sizeof(stu));
	read_out();
}

void start_process(void)	//	主要程序
{
	for(;;)
	{
		switch(menu1())
		{
			case '1':	
				student();		break;	//	学生操作部分
			case '2':	
				teacher();		break;	//	教师操作部分
			case '3':	
				headmaster();	break;	//	校长部分
			case '4':
				return ;
		}
	}
}

void end_process(void)		//	结束程序
{
	store_in();	//	存储信息
	free(stup);	//	释放内存
	free(stup1);
	free(teap);
	stup = NULL;//	指针置空
	teap = NULL;
	stup1 = NULL;
	return;
}

