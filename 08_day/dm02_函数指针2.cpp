#define  _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


//����ָ�� 
//����һ�� �������� 
//����һ�� ����ָ������
//����һ�� ����ָ�� , ����ָ��һ����������ڵ�ַ

int myadd(int a, int b)
{
	int c = 0;
	c = a + b;
	return c;
}

void main22()
{
	myadd(1, 2);// �������ƴ���������ڵ�ַ ����һ������ָ�� myadd 
				// ֱ�ӵ���
	//����һ�� �������� 
	{
		typedef int (MyFuncType)(int a, int b); //��������, ���� :�̶���С�ڴ��ı���
		MyFuncType  *myFuncVar = NULL;
		myFuncVar = myadd;

		myFuncVar(3, 4); //��ӵ���

	}


	//����һ�� ����ָ������
	{
		typedef int (*MyPFuncType)(int a, int b); //����  C��������������ڴ�

		MyPFuncType  myPFunc = NULL;
		myPFunc = myadd;
		myPFunc = &myadd; //C�İ汾������ ���� 
		myPFunc(5, 6);
	}
	////����һ�� ����ָ�� , ����ָ��һ����������ڵ�ַ

	 int (*MyPFuncType)(int a, int b); //�����˸�ָ����� // �����ڴ�

	 MyPFuncType = myadd;
	 MyPFuncType(10, 20);


	printf("hello...\n");
	system("pause");
	return ;
}