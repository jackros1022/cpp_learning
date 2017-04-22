
#define  _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "mysocketclient.h"



void main()
{
	unsigned char buf[1024];
	int buflen ;

	//unsigned char out[1024];
	//int outlen ;

	unsigned char *pout = NULL;
	int outlen ;

	void *handle  = NULL;
	int ret = 0;


	strcpy((char *)buf, "aaaaaaaaaffffffffdddddddd");
	buflen = 9;

	//客户端初始化 获取handle上下
	ret = socketclient_init2(&handle /*out*/); 
	if (ret != 0)
	{
		printf("func socketclient_init2() err:%d \n ", ret);
		goto End;
	}

	//客户端发报文
	ret = socketclient_send2(handle /*in*/, buf /*in*/,  buflen /*in*/);
	if (ret != 0)
	{
		printf("func socketclient_send2() err:%d \n ", ret);
		goto End;
	}

	//客户端收报文
	ret = socketclient_recv2(handle /*in*/, &pout /*in*/, &outlen/*in out*/);
	if (ret != 0)
	{
		printf("func socketclient_recv() err:%d \n ", ret);
		goto End;
	}

	//if (pout != NULL) free(pout);
	socketclient_Free2(pout); //在底层库分配的内存 ,需要 调用底层库的api函数进行释放 


End:
	//客户端释放资源
	ret = socketclient_destory2(&handle/*in*/); //把handle所指的内存释放 2 把handle重新赋值成NULL


	printf("hello...\n");
	system("pause");
	printf("hello...\n");
	system("pause");
	return ;
}

void main01()
{
	unsigned char buf[1024];
	int buflen ;

	unsigned char out[1024];
	int outlen ;

	void *handle  = NULL;
	int ret = 0;


	strcpy((char *)buf, "aaaaaaaaaffffffffdddddddd");
	buflen = 9;

	//客户端初始化 获取handle上下
	ret = socketclient_init(&handle /*out*/); 
	if (ret != 0)
	{
		printf("func socketclient_init() err:%d \n ", ret);
		goto End;
	}

	//客户端发报文
	ret = socketclient_send(handle /*in*/, buf /*in*/,  buflen /*in*/);
	if (ret != 0)
	{
		printf("func socketclient_send() err:%d \n ", ret);
		goto End;
	}

	//客户端收报文
	ret = socketclient_recv(handle /*in*/, out /*in*/, &outlen/*in out*/);
	if (ret != 0)
	{
		printf("func socketclient_recv() err:%d \n ", ret);
		goto End;
	}

End:
	//客户端释放资源
	ret = socketclient_destory(handle/*in*/);

	printf("hello...\n");
	system("pause");
	printf("hello...\n");
	system("pause");
	return ;
}


