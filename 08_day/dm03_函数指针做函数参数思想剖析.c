#define  _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>



//=====> ����ָ��������������˼�뾫��:
// �������������  �� ʵ���������  �����

int myadd(int a, int b)
{
	int c = 0;
	c = a +b;
	return c;
}

int myadd2(int a, int b)  //������ 
{
	int c = 0;
	c = a +b;
	printf("func myadd2() do \n");
	return c;
}

int myadd3(int a, int b) //������ 
{
	int c = 0;
	c = a +b;
	printf("func myadd3() do \n");
	return c;
}

int myadd4(int a, int b) //������ 
{
	int c = 0;
	c = a +b;
	printf("func myadd4() do \n");
	return c;
}


//�ҵĿ�� 10:19��  //
// int (*myFuncVar)(int a, int b) 
int myMianOp(  int (*myFuncVar)(int a, int b)   )
{
	myFuncVar(10, 20);  //��ӵĵ��� myadd����
	return 0;
}
void main()
{
	//����ָ����� 
	//int (*myFuncVar)(int a, int b) ; //����һ��ָ�����  ָ��һ����������
	//myFuncVar = myadd;
	//myFuncVar(1, 2);

	myMianOp( myadd) ;	//������

	myMianOp( myadd2) ; //������

	myMianOp( myadd3) ; //������
	myMianOp( myadd4) ; //������

	//

	printf("hello...\n");
	system("pause");
	return ;
}