
#define  _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//��ɷ��ͱ��ĵ�ʱ��,�������ݼ���
//int EncData(unsigned char *in, int inlen, unsigned char *out, int outlen);

//int DecData(unsigned char *in, int inlen, unsigned char *out, int outlen);



//��ɷ��ͱ��ĵ�ʱ��,�������ݼ���
//���庯��ָ������  ͨ������ָ������ ��Լ�� ���� ȥʵ�� ���ܽ��ܺ�����ԭ��
typedef int (*EncData)(unsigned char *in, int inlen, unsigned char *out, int *outlen);

typedef int (*DecData)(unsigned char *in, int inlen, unsigned char *out, int *outlen);



typedef struct _Sck_Handle
{
	char	version[16];
	char	ip[16];
	int		port;
	unsigned char *p;
	int			len;

	char		*p2 ;

	EncData  Hw_EncData;

}Sck_Handle;

int  socketclient_SetEncDataCallback(void *handle, EncData Hw_EncData)
{
	int ret = 0;
	Sck_Handle	*tmpHandle = NULL;
	if (handle == NULL || Hw_EncData==NULL)
	{
		ret = -1;
		printf("func socketclient_SetEncDataCallback() err :%d  check handle == NULL err \n", ret);
		return ret;
	}
	tmpHandle = (Sck_Handle *)handle;
	tmpHandle->Hw_EncData = Hw_EncData;//��ǰ�ѻص���������ڵ�ַ ���浽 ���handle ��������

	return 0;
}

int socketclient_sendAndEnc1(void *handle, unsigned char *buf, int buflen, EncData encDataCallback)
{
	int		ret = 0;
	unsigned char cryptbuf[4096];
	int				cryptbuflen = 4096;

	Sck_Handle	*tmpHandle = NULL;
	if (handle == NULL || buf==NULL || encDataCallback==NULL)
	{
		ret = -1;
		printf("func socketclient_sendAndEnc1() err :%d  check handle == NULL err \n", ret);
		return ret;
	}
	ret = encDataCallback(buf, buflen, cryptbuf, &cryptbuflen) ; //��ӵĵ��������� 
	if (ret != 0)
	{
		ret = -2;
		printf("func socketclient_sendAndEnc1() err :%d  check handle == NULL err \n", ret);
		return ret;
	}

	tmpHandle = (Sck_Handle *)handle;
	tmpHandle->len = cryptbuflen;

	tmpHandle->p = (unsigned char *)malloc(cryptbuflen);
	if (tmpHandle->p == NULL) 
	{
		ret = -3;
		printf("func socketclient_sendAndEnc1() err :%d  mallocerr \n", ret);
		return ret;
	}

	//�Ѽ��ܵ�����  ���浽 �ڴ���
	memcpy(tmpHandle->p, cryptbuf, cryptbuflen);
	
	return 0;
}

int socketclient_sendAndEnc2(void *handle, unsigned char *buf, int buflen,
	int (*EncData)(unsigned char *in, int inlen, unsigned char *out, int *outlen) )
{
	return 0;
}

//socket�ͻ��˻�����ʼ�� //�Ѷ�̬��Ļ��� ���׳�, �ñ���ʹ��
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

	if (tmpHandle->Hw_EncData != NULL) //��������˼��ܺ��� ���ͱ���֮ǰ �ȶ����ݽ��м���
	{
		unsigned char crypdata[4096];
		int cryptdatalen = 4096;
		ret = tmpHandle->Hw_EncData(buf, buflen,crypdata,  &cryptdatalen);
		if (ret != 0)
		{
			printf("func Hw_EncData() err :%d  \n", ret);
			return ret;
		}

		tmpHandle->len = cryptdatalen;
		tmpHandle->p = (unsigned char *)malloc(cryptdatalen);
		if (tmpHandle->p == NULL)
		{
			ret = -1;
			printf("func Hw_EncData() err :%d malloc err \n", ret);
			return ret;
		}
		memcpy(tmpHandle->p, crypdata, cryptdatalen); //��������
	}
	else
	{
		tmpHandle->len = buflen;
		tmpHandle->p = (unsigned char * )malloc(buflen);
		if (tmpHandle->p  == NULL)
		{
			ret = -2;
			printf("func socketclient_send() err :%d  malloc len:%d \n", ret, buflen);
			return ret;
		}
		memcpy(tmpHandle->p, buf, buflen); //���ݵĻ��浽�ڴ�

	}

	return ret;
}


//socket���Ľ���
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

 
int socketclient_init2(void **handle /*out*/)
{
	return socketclient_init(handle);
}

 
int socketclient_send2(void *handle/*in*/, unsigned char *buf, int buflen)
{
	return socketclient_send(handle, buf, buflen);
}


//ͨ��ָ������������  �� �Ѷ�������� ˦���� ....
 
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

 
int socketclient_Free2(void *p) //�ڵײ�������ڴ� ,��Ҫ ���õײ���api���������ͷ� 
{
	if (p == NULL)
	{
		return -1;
	}
	free(p);
	return 0;
}

 
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



