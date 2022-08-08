#include <unistd.h>
#include "menu.h"
#include "tools.h"
#include "sign.h"
#include "headmaster.h"
#include "readandstore.h"
#include "operation.h"

void headmaster(void)
{
	printf("欢迎您，校长\n");
	anykey_continue();
	int num = 0;
	num=sign_in(3);
	if(num == -1) return;		//	如果没有找到帐号或者登录失败或者输入esc则返回-1
	first_log(3,0);
	for(;;)
	{
		switch(menu4())
			{
				case '1':	add_inform(2);			break;	//添加教师信息
				case '2':	del_inform(2);			break;	//删除教师信息
				case '3':	show_inschool(2);		break;	//显示在职教师信息
				case '4':	show_leaveschool(2);	break;	//显示离职教师信息
				case '5':	reset_code(2);			break;	//重置教师密码
				case '6':	unlock(2);				break;	//解锁老师帐号
				case '7':	reset_code(3);			break;	//重置校长密码
				case '8':	return;
			} 
	}
}

