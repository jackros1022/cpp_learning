
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

//socket�ͻ��˻�����ʼ��
__declspec(dllexport)  //�Ѷ�̬��Ļ��� ���׳�, �ñ���ʹ��
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
	
	//��Ӹ�ֵ
	*handle = tmpHandle;
	return ret;
}

//socket���ķ���
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
	memcpy(tmpHandle->p, buf, buflen); //���ݵĻ��浽�ڴ�

	return ret;
}


//socket���Ľ���
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
	*buflen = tmpHandle->len; //��Ӹ�ֵ  ���ߵ����� �յ������ݵĳ���

	return ret;
}


//socket�����ͷ�
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
		free(tmpHandle->p); //�ͷŽṹ�� ��Ա��� ָ����ָ����ڴ�ռ�
	}
	free(tmpHandle); //�ͷŽṹ���ڴ�
	return 0;
}


