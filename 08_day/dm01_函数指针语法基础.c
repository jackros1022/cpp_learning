#define  _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//����ָ�� 
//����һ�� �������� 
//����һ�� ����ָ������
//����һ�� ����ָ�� , ����ָ��һ����������ڵ�ַ

//����ָ��
//����һ�� ��������
//����һ�� ����ָ������
//����һ��  ����ָ�����, ����ָ��һ������....


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

//int (*myArrayVar)[10]; //������һ������ ����ָ��һ������ 
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
	int a[10]; //��һ�����Ͷ���һ������ 
	//��������
	{
		typedef int (MyArrayType)[10];

		MyArrayType array; //int a[10];
		array[0] = 1;
		printf("%d \n", array[0]);
	}

	//����ָ������
	{
		typedef int (*MyPointArrayType)[10]; //

		MyPointArrayType  pointArray;
		pointArray = &a; //��Ϊָ��һ������, ���� �����һ�������С ��Ԫ
		(*pointArray)[0] = 10;
		pointArray ++; //+1 xiang
		printf("a[0]: %d \n", a[0]);

		//int mybuf[10][30]; //mybuf====> ����һ������ָ�� mybuf+1 �����30����Ԫ
		//mybuf + 1; (*(*(a+i))+j )
	}

	////����һ��  ����ָ�����, ����ָ��һ������....
	{
	
		int (*myArrayVar)[10]; //������һ������ ����ָ��һ������ 
		myArrayVar = &a;

		(*myArrayVar)[2] = 30;
		printf("a[2]: %d \n", a[2]);

		{
			int b = 10;
			int *p = &b;
		}
		
	}


	//��ά��������������
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

	//û���ڴ� ������ָ�밡 .....
	int (*myPArray)[10] = NULL; //������һ��ָ��

	myPArray = &a;
	(*myPArray)[3] = 10;

	system("pause");

}