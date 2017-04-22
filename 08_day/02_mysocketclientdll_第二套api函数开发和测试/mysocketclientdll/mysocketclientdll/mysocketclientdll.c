
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


//ͨ��ָ������������  �� �Ѷ�������� ˦���� ....
__declspec(dllexport) 
int socketclient_recv2(void *handle, unsigned char **  buf /*out*/, int *buflen) //�ڵײ���з����ڴ�
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

	tmpbuf = (unsigned char *)malloc(tmpHandle->len); //�ײ������ڴ�
	if (tmpbuf == NULL)
	{
		ret = -3;
		printf("func socketclient_recv() err :%d  (malloc(tmpHandle->len)  ) \n", ret);
		return ret;
	}
	memcpy(tmpbuf, tmpHandle->p, tmpHandle->len); //�ѿ������� �� �ײ�⿪�ٵ��ڴ���

	*buf  = tmpbuf; //*p p��ʵ�εĵ�ַ   //��Ӹ�ֵ  ��ָ����ڵ��������� 
	*buflen = tmpHandle->len; //��Ӹ�ֵ  ���ߵ����� �յ������ݵĳ���

	return ret;
}

__declspec(dllexport) 
int socketclient_Free2(void *p) //�ڵײ�������ڴ� ,��Ҫ ���õײ���api���������ͷ� 
{
	if (p == NULL)
	{
		return -1;
	}
	free(p);
	return 0;
}

__declspec(dllexport) 
int socketclient_destory2(void **handle /*in out*/) //�ͷ����ڴ��Ժ� ,�ٰ�ʵ���ó�null
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

	*handle = NULL; //*p p��ʵ�εĵ�ַ   //��Ӹ�ֵ  ��ָ����ڵ��������� 
	return 0;
}



