#define  _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>



//=====> 函数指针做函数参数的思想精华:
// 调用者任务的人  和 实现任务的人  解耦合

int myadd(int a, int b)
{
	int c = 0;
	c = a +b;
	return c;
}

int myadd2(int a, int b)  //子任务 
{
	int c = 0;
	c = a +b;
	printf("func myadd2() do \n");
	return c;
}

int myadd3(int a, int b) //子任务 
{
	int c = 0;
	c = a +b;
	printf("func myadd3() do \n");
	return c;
}

int myadd4(int a, int b) //子任务 
{
	int c = 0;
	c = a +b;
	printf("func myadd4() do \n");
	return c;
}


//我的框架 10:19分  //
// int (*myFuncVar)(int a, int b) 
int myMianOp(  int (*myFuncVar)(int a, int b)   )
{
	myFuncVar(10, 20);  //间接的调用 myadd函数
	return 0;
}
void main()
{
	//函数指针变量 
	//int (*myFuncVar)(int a, int b) ; //定义一个指针变量  指向一个函数类型
	//myFuncVar = myadd;
	//myFuncVar(1, 2);

	myMianOp( myadd) ;	//调用者

	myMianOp( myadd2) ; //调用者

	myMianOp( myadd3) ; //调用者
	myMianOp( myadd4) ; //调用者

	//

	printf("hello...\n");
	system("pause");
	return ;
}