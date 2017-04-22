



//written by  wangbaoming1999@163.com
//
/*
下面定义了一套socket客户端发送报文接受报文的api接口
请写出这套接口api的调用方法
*/

/*
//这是一套动态库，实现了客户端和服务器端报文的发送。。
是客户端api函数
*/

#ifndef _INC_MYSOCKETCLIENT_H__
#define _INC_MYSOCKETCLIENT_H__

#ifdef  __cplusplus
extern "C" {
#endif

//1 数据类型的封装
//2 handle的概念:  底层库的内存资源,记录着函数运行的上下文信息..
//3 底层库提供的是一种机制, 而不是满足某一个人的策略 

//完成发送报文的时候,进行数据加密
//int EncData(unsigned char *in, int inlen, unsigned char *out, int outlen);
//int DecData(unsigned char *in, int inlen, unsigned char *out, int outlen);

//完成发送报文的时候,进行数据加密
//定义函数指针类型  通过函数指针类型 来约定 厂商 去实现 加密解密函数的原型
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
int socketclient_recv2(void *handle, unsigned char **buf /*out*/, int *buflen); //在底层库中分配内存

int socketclient_Free2(void *p); //在底层库分配的内存 ,需要 调用底层库的api函数进行释放 

int socketclient_destory2(void **handle /*in out*/); //释放完内存以后 ,再把实参置成null


#ifdef  __cplusplus
}
#endif

#endif  /* _INC_MYSOCKETCLIENT_H__ */


