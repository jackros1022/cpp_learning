
#define  _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "mysocketclient.h"

int Hw_EncData(unsigned char *in, int inlen, unsigned char *out, int *outlen)
{
	printf("func Hw_EncData begin....\n ");
	strcpy((char *)out, "123456789");
	*outlen = 9;

	printf("func Hw_EncData end....\n ");
	return 0;
}
//	//设置 加密函数入口地址  回调函数的入口地址
//ret = socketclient_SetEncCallback(&handle, Hw_EncData); 

//把加密函数的入口地址 提前 塞入到动态库中 
//
void main()
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

	//
	ret = socketclient_SetEncDataCallback(handle, Hw_EncData);
	if (ret != 0)
	{
		printf("func socketclient_SetEncDataCallback() err:%d \n ", ret);
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


void main03()
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
	//ret = socketclient_send(handle /*in*/, buf /*in*/,  buflen /*in*/);
	ret = socketclient_sendAndEnc1(handle, buf, buflen, Hw_EncData);
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






void main02()
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


