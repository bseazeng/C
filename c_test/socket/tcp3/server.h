/******************************************************************************

                  ��Ȩ���� (C), 2016-2200, ����bsea

 ******************************************************************************
  �� �� ��   : server.h
  �� �� ��   : ����
  ��    ��   : bseazeng
  ��������   : Sunday, April 17, 2016
  ����޸�   :
  ��������   : server.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : Sunday, April 17, 2016
    ��    ��   : bseazeng
    �޸�����   : �����ļ�

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
#define CMD_MSG_WRFIL	(CMD_TYPE+1)	//д�ļ�
#define CMD_MSG_RDFIL	(CMD_TYPE+2)	//���ļ�
#define CMD_MSG_END		(CMD_TYPE+4096) //�����ֽ���



/*���յ�����Ϣ*/
typedef struct msg_data_st_
{
	int		magic;
	int		cmdType;
	int	 	dataLen;
	char	data[0];//�ɱ����鳤��
}MSG_DATA_ST;


/*���͸���Ϣ�������Ĳ����ṹ*/
typedef struct MSG_HANDLE_PARAM_ST
{
      int sockFd; 	//
	  int dataLen;	//��Ϣ�峤��
	  char *data;	//��Ϣ��
	  
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
