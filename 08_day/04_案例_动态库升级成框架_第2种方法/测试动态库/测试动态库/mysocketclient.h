



//written by  wangbaoming1999@163.com
//
/*
���涨����һ��socket�ͻ��˷��ͱ��Ľ��ܱ��ĵ�api�ӿ�
��д�����׽ӿ�api�ĵ��÷���
*/

/*
//����һ�׶�̬�⣬ʵ���˿ͻ��˺ͷ������˱��ĵķ��͡���
�ǿͻ���api����
*/

#ifndef _INC_MYSOCKETCLIENT_H__
#define _INC_MYSOCKETCLIENT_H__

#ifdef  __cplusplus
extern "C" {
#endif

//1 �������͵ķ�װ
//2 handle�ĸ���:  �ײ����ڴ���Դ,��¼�ź������е���������Ϣ..
//3 �ײ���ṩ����һ�ֻ���, ����������ĳһ���˵Ĳ��� 

//��ɷ��ͱ��ĵ�ʱ��,�������ݼ���
//int EncData(unsigned char *in, int inlen, unsigned char *out, int outlen);
//int DecData(unsigned char *in, int inlen, unsigned char *out, int outlen);

//��ɷ��ͱ��ĵ�ʱ��,�������ݼ���
//���庯��ָ������  ͨ������ָ������ ��Լ�� ���� ȥʵ�� ���ܽ��ܺ�����ԭ��
typedef int (*EncData)(unsigned char *in, int inlen, unsigned char *out, int *outlen);
typedef int (*DecData)(unsigned char *in, int inlen, unsigned char *out, int *outlen);

int  socketclient_SetEncDataCallback(void *handle, EncData Hw_EncData); //new
int socketclient_init(void **handle);
int socketclient_send(void *handle, unsigned char *buf, int buflen);

int socketclient_sendAndEnc1(void *handle, unsigned char *buf, int buflen, EncData encDataCallback);

int socketclient_sendAndEnc2(void *handle, unsigned char *buf, int buflen,
					int (*EncData)(unsigned char *in, int inlen, unsigned char *out, int *outlen)
	);

int socketclient_recv(void *handle, unsigned char *buf, int *buflen);
int socketclient_destory(void *handle);




//////////////////////////////////////////////////////////////////////////

int socketclient_init2(void **handle /*out*/);
int socketclient_send2(void *handle/*in*/, unsigned char *buf, int buflen);
int socketclient_recv2(void *handle, unsigned char **buf /*out*/, int *buflen); //�ڵײ���з����ڴ�

int socketclient_Free2(void *p); //�ڵײ�������ڴ� ,��Ҫ ���õײ���api���������ͷ� 

int socketclient_destory2(void **handle /*in out*/); //�ͷ����ڴ��Ժ� ,�ٰ�ʵ���ó�null


#ifdef  __cplusplus
}
#endif

#endif  /* _INC_MYSOCKETCLIENT_H__ */


