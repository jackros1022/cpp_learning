
#define  _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


typedef struct _Sck_Handle
{
	char	version[16];
	char	ip[16];
	int		port;
	unsigned char *p;
	int			len;

	char		*p2 ;
}Sck_Handle;

//socket客户端环境初始化
__declspec(dllexport)  //把动态库的环境 给抛出, 让别人使用
int socketclient_init(void **handle)
{
	int			ret = 0;
	Sck_Handle	*tmpHandle = NULL;

	if (handle == NULL)
	{
		ret = -1;
		printf("func socketclient_init() err :%d  check handle == NULL err \n", ret);
		return ret;
	}

	tmpHandle = (Sck_Handle *)malloc(sizeof(Sck_Handle));
	if (tmpHandle == NULL)
	{
		ret = -2;
		printf("func socketclient_init() err :%d  malloc err \n", ret);
		return ret;
	}

	memset(tmpHandle, 0, sizeof(Sck_Handle));
	strcpy(tmpHandle->version, "1.0.0.1");
	strcpy(tmpHandle->ip, "192.168.12.12");
	tmpHandle->port = 8081;
	
	//间接赋值
	*handle = tmpHandle;
	return ret;
}

//socket报文发送
__declspec(dllexport)
int socketclient_send(void *handle, unsigned char *buf, int buflen)
{
	int			ret = 0;
	Sck_Handle	*tmpHandle = NULL;

	if (handle == NULL ||  buf==NULL || buflen <=0 )
	{
		ret = -2;
		printf("func socketclient_send() err :%d  (handle == NULL ||  buf==NULL || buflen <=0 ) \n", ret);
		return ret;
	}
	
	tmpHandle = (Sck_Handle *)handle;
	tmpHandle->len = buflen;
	tmpHandle->p = (unsigned char * )malloc(buflen);
	if (tmpHandle->p  == NULL)
	{
		ret = -2;
		printf("func socketclient_send() err :%d  malloc len:%d \n", ret, buflen);
		return ret;
	}
	memcpy(tmpHandle->p, buf, buflen); //数据的缓存到内存

	return ret;
}


//socket报文接受
__declspec(dllexport)
int socketclient_recv(void *handle, unsigned char *buf, int *buflen)
{
	int			ret = 0;
	Sck_Handle	*tmpHandle = NULL;

	if (handle == NULL ||  buf==NULL || buflen==NULL )
	{
		ret = -2;
		printf("func socketclient_recv() err :%d  (handle == NULL ||  buf==NULL || buflen==NULL ) \n", ret);
		return ret;
	}
	tmpHandle = (Sck_Handle *)handle;

	memcpy(buf, tmpHandle->p, tmpHandle->len);
	*buflen = tmpHandle->len; //间接赋值  告诉调用者 收到的数据的长度

	return ret;
}


//socket环境释放
__declspec(dllexport)
int socketclient_destory(void *handle)
{
	int			ret = 0;
	Sck_Handle	*tmpHandle = NULL;

	if (handle == NULL)
	{
		return -1;
	}

	tmpHandle = (Sck_Handle *)handle;
	if (tmpHandle->p != NULL)
	{
		free(tmpHandle->p); //释放结构体 成员域的 指针所指向的内存空间
	}
	free(tmpHandle); //释放结构体内存
	return 0;
}

//////////////////////////////////////////////////////////////////////////

__declspec(dllexport) 
int socketclient_init2(void **handle /*out*/)
{
	return socketclient_init(handle);
}

__declspec(dllexport) 
int socketclient_send2(void *handle/*in*/, unsigned char *buf, int buflen)
{
	return socketclient_send(handle, buf, buflen);
}


//通过指针做函数参数  把 把多个运算结果 甩出来 ....
__declspec(dllexport) 
int socketclient_recv2(void *handle, unsigned char **  buf /*out*/, int *buflen) //在底层库中分配内存
{
	int			ret = 0;
	Sck_Handle	*tmpHandle = NULL;

	unsigned char *tmpbuf = NULL;

	
	if (handle == NULL ||  buf==NULL || buflen==NULL )
	{
		ret = -2;
		printf("func socketclient_recv() err :%d  (handle == NULL ||  buf==NULL || buflen==NULL ) \n", ret);
		return ret;
	}
	tmpHandle = (Sck_Handle *)handle;

	tmpbuf = (unsigned char *)malloc(tmpHandle->len); //底层库分配内存
	if (tmpbuf == NULL)
	{
		ret = -3;
		printf("func socketclient_recv() err :%d  (malloc(tmpHandle->len)  ) \n", ret);
		return ret;
	}
	memcpy(tmpbuf, tmpHandle->p, tmpHandle->len); //把拷贝数据 到 底层库开辟的内存中

	*buf  = tmpbuf; //*p p是实参的地址   //间接赋值  是指针存在的做大意义 
	*buflen = tmpHandle->len; //间接赋值  告诉调用者 收到的数据的长度

	return ret;
}

__declspec(dllexport) 
int socketclient_Free2(void *p) //在底层库分配的内存 ,需要 调用底层库的api函数进行释放 
{
	if (p == NULL)
	{
		return -1;
	}
	free(p);
	return 0;
}

__declspec(dllexport) 
int socketclient_destory2(void **handle /*in out*/) //释放完内存以后 ,再把实参置成null
{
	Sck_Handle	*tmpHandle = NULL;

	if (handle == NULL)
	{
		return -1;
	}
	tmpHandle = *handle;

	if (tmpHandle != NULL)
	{
		if (tmpHandle->p != NULL) free(tmpHandle->p); //bombing modify bug 20150327
		free(tmpHandle);
	}

	*handle = NULL; //*p p是实参的地址   //间接赋值  是指针存在的做大意义 
	return 0;
}



