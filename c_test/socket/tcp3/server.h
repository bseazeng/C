/******************************************************************************

                  版权所有 (C), 2016-2200, 个人bsea

 ******************************************************************************
  文 件 名   : server.h
  版 本 号   : 初稿
  作    者   : bseazeng
  生成日期   : Sunday, April 17, 2016
  最近修改   :
  功能描述   : server.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : Sunday, April 17, 2016
    作    者   : bseazeng
    修改内容   : 创建文件

******************************************************************************/

#ifndef __SERVER_H__
#define __SERVER_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
#include <pthread.h>

#define SERVER_PORT		(50001)
#define MSG_BUF_SIZE 	(1024)


typedef struct pthread_param_st_
{
    pthread_t *pid;
    struct sockaddr_in *server_addr;
    struct sockaddr_in *clientAddr;
    
}PTHREAD_PARAM_ST;

typedef int (*handle)(void *arg);
typedef struct init_handle_st
{
	const char *name;
	handle init_func;
}INIT_HANDLE_ST;

#define MSG_MAGIC		(0xaabbccdd)
#define CMD_TYPE		(0x00000000)
#define CMD_MSG_HEART	(CMD_TYPE+0)
#define CMD_MSG_WRFIL	(CMD_TYPE+1)	//写文件
#define CMD_MSG_RDFIL	(CMD_TYPE+2)	//读文件
#define CMD_MSG_END		(CMD_TYPE+4096) //命令字结束



/*接收到的消息*/
typedef struct msg_data_st_
{
	int		magic;
	int		cmdType;
	int	 	dataLen;
	char	data[0];//可变数组长度
}MSG_DATA_ST;


/*传送给消息处理函数的参数结构*/
typedef struct MSG_HANDLE_PARAM_ST
{
      int sockFd; 	//
	  int dataLen;	//消息体长度
	  char *data;	//消息体
	  
}MSG_HANDLE_PARAM_ST;

typedef struct msg_handle_st_
{
	int cmdType;
	handle cmdHandle;
}MSG_HANDLE_ST;


int msgHandleHeart(void *arg);
int msgHandleWriteFile(void*arg);
int msgHandleReadFile(void*arg);





#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __SERVER_H__ */
