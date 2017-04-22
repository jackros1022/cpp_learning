#define  _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//函数指针 
//声明一个 函数类型 
//声明一个 函数指针类型
//定义一个 函数指针 , 用来指向一个函数的入口地址

//数组指针
//声明一个 数组类型
//声明一个 数组指针类型
//定义一个  数组指针变量, 用来指针一个数组....


void printfA1(char a[10][30] )
{
	int i = 0;
	for (i=0; i<10; i++)
	{
		printf("%s \n", a[i]);
	}
}
void printfA2(char a[][30] ) //char buf[30]
{
	int i = 0;
	for (i=0; i<10; i++)
	{
		printf("%s \n", a[i]);
	}
}

//int (*myArrayVar)[10]; //定义了一个变量 用来指向一个数组 
void printfA3(char (*a)[30] , int num)
{
	int i = 0;
	for (i=0; i<num; i++)
	{
		printf("%s \n", a[i]);
	}
}

void main11()
{
	int a[10]; //用一个类型定义一个数组 
	//数组类型
	{
		typedef int (MyArrayType)[10];

		MyArrayType array; //int a[10];
		array[0] = 1;
		printf("%d \n", array[0]);
	}

	//数组指针类型
	{
		typedef int (*MyPointArrayType)[10]; //

		MyPointArrayType  pointArray;
		pointArray = &a; //因为指向一个数组, 本质 向后跳一个数组大小 单元
		(*pointArray)[0] = 10;
		pointArray ++; //+1 xiang
		printf("a[0]: %d \n", a[0]);

		//int mybuf[10][30]; //mybuf====> 就是一个数组指针 mybuf+1 向后跳30个单元
		//mybuf + 1; (*(*(a+i))+j )
	}

	////定义一个  数组指针变量, 用来指针一个数组....
	{
	
		int (*myArrayVar)[10]; //定义了一个变量 用来指向一个数组 
		myArrayVar = &a;

		(*myArrayVar)[2] = 30;
		printf("a[2]: %d \n", a[2]);

		{
			int b = 10;
			int *p = &b;
		}
		
	}


	//二维数组做函数参数
	{
		char a[10][30] = {"aaaaa", "bbbbbb", "cccccccc"};
		printfA3(a, 3);

	}


	printf("hello...\n");
	system("pause");
	return ;
}

void main12()
{
	int a[10];

	//没有内存 哪来的指针啊 .....
	int (*myPArray)[10] = NULL; //定义了一个指针

	myPArray = &a;
	(*myPArray)[3] = 10;

	system("pause");

}