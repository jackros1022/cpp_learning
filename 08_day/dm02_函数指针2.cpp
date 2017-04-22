#define  _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


//函数指针 
//声明一个 函数类型 
//声明一个 函数指针类型
//定义一个 函数指针 , 用来指向一个函数的入口地址

int myadd(int a, int b)
{
	int c = 0;
	c = a + b;
	return c;
}

void main22()
{
	myadd(1, 2);// 函数名称代表函数的入口地址 就是一个函数指针 myadd 
				// 直接调用
	//声明一个 函数类型 
	{
		typedef int (MyFuncType)(int a, int b); //数据类型, 本质 :固定大小内存块的别名
		MyFuncType  *myFuncVar = NULL;
		myFuncVar = myadd;

		myFuncVar(3, 4); //间接调用

	}


	//声明一个 函数指针类型
	{
		typedef int (*MyPFuncType)(int a, int b); //类型  C编译器不会分配内存

		MyPFuncType  myPFunc = NULL;
		myPFunc = myadd;
		myPFunc = &myadd; //C的版本兼容性 问题 
		myPFunc(5, 6);
	}
	////定义一个 函数指针 , 用来指向一个函数的入口地址

	 int (*MyPFuncType)(int a, int b); //定义了个指针变量 // 分配内存

	 MyPFuncType = myadd;
	 MyPFuncType(10, 20);


	printf("hello...\n");
	system("pause");
	return ;
}