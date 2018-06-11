#include "server.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


#include "common.h"
#include "File.h"

MSG_HANDLE_ST stMsgHandleArray[]=
{
	{CMD_MSG_HEART,msgHandleHeart},
	{CMD_MSG_WRFIL,msgHandleWriteFile},
	{CMD_MSG_RDFIL,msgHandleReadFile}
};

/*****************************************************************************
 函 数 名  : msgHandleHeart
 功能描述  : 心跳处理
 输入参数  : void *arg
 输出参数  : 无
 返 回 值  : int
 
 修改历史      :
  1.日    期   : 2018年5月26日 星期六
    作    者   : bseazeng
    修改内容   : 新生成函数

*****************************************************************************/
int msgHandleHeart(void *arg)
{
	MSG_HANDLE_PARAM_ST *pstParam = (MSG_HANDLE_PARAM_ST*)arg;
	char send_buff[MSG_BUF_SIZE+1] = {0};

	if(NULL == pstParam )
	{
		CommonPrintf("pstParam is null\n");
		return RET_FAIL;
	}

	write(pstParam->sockFd,send_buff,strlen(send_buff));
	return RET_SUCCESS;
}

/*****************************************************************************
 函 数 名  : msgHandleWriteFile
 功能描述  : 写文件处理
 输入参数  : void*arg
 输出参数  : 无
 返 回 值  : int
 
 修改历史      :
  1.日    期   : 2018年5月26日 星期六
    作    者   : bseazeng
    修改内容   : 新生成函数

*****************************************************************************/
int msgHandleWriteFile(void*arg)
{
	MSG_HANDLE_PARAM_ST *pstParam = (MSG_HANDLE_PARAM_ST*)arg;
	char send_buff[MSG_BUF_SIZE+1] = {0};

	if(NULL == pstParam )
	{
		CommonPrintf("pstParam is null\n");
		return RET_FAIL;
	}

	write(pstParam->sockFd,send_buff,strlen(send_buff));
	return RET_SUCCESS;
}

/*****************************************************************************
 函 数 名  : msgHandleReadFile
 功能描述  : 读文件处理
 输入参数  : void*arg
 输出参数  : 无
 返 回 值  : int
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2018年5月26日 星期六
    作    者   : bseazeng
    修改内容   : 新生成函数

*****************************************************************************/

int msgHandleReadFile(void*arg)
{
	MSG_HANDLE_PARAM_ST *pstParam = (MSG_HANDLE_PARAM_ST*)arg;
	char send_buff[MSG_BUF_SIZE+1] = {0};

	if(NULL == pstParam )
	{
		CommonPrintf("pstParam is null\n");
		return RET_FAIL;
	}

	write(pstParam->sockFd,send_buff,strlen(send_buff));
	return RET_SUCCESS;
}



/*****************************************************************************
 函 数 名  : msgCheck
 功能描述  : check接收到消息的有效性
 输入参数  : int magic  消息魔数
             int cmdType
 输出参数  : 无
 返 回 值  : int
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2018年5月26日 星期六
    作    者   : bseazeng
    修改内容   : 新生成函数

*****************************************************************************/
int msgCheck( int magic, int cmdType )
{
	if(MSG_MAGIC != magic)
	{
		CommonPrintf("MSG_MAGIC[0x%x] != magic[0x%08x]\n",MSG_MAGIC,magic);
		return RET_FAIL;
	}

	if (CMD_TYPE > cmdType || cmdType > CMD_MSG_END )
	{
		CommonPrintf("cmdType[0x%x] is not from CMD_TYPE[0x%0x] to CMD_MSG_END[%0x%x] \n",cmdType,CMD_TYPE,CMD_MSG_END);
		return RET_FAIL;
	}
	
    return RET_SUCCESS;
}
/*****************************************************************************
 函 数 名  : handMsg
 功能描述  : 处理接受到的消息
 输入参数  : char *msg 需要处理的消息
            			 int msg_len
 输出参数  : 无
 返 回 值  : int
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2018年5月26日 星期六
    作    者   : bseazeng
    修改内容   : 新生成函数

*****************************************************************************/
int handMsg( char *msg, int msg_len , int sockFd)
{
	if ( NULL == msg )
	{
	    CommonPrintf("msg is null\n");
		return RET_FAIL;
	}
	int	iRet = 0;
	MSG_DATA_ST *pstMsg = (MSG_DATA_ST *)msg;
	if(RET_TRUE != msgCheck(pstMsg->magic,pstMsg->cmdType))
	{
	    CommonPrintf("msgCheck failed\n");
		return RET_FAIL;
	}

	MSG_HANDLE_PARAM_ST st;
	st.data = malloc(pstMsg->dataLen+1);
	memcpy(st.data,pstMsg->data,pstMsg->dataLen);
	st.data[pstMsg->dataLen] = '\0';
	st.dataLen= pstMsg->dataLen+1;
	st.sockFd	= sockFd;
	iRet = stMsgHandleArray[pstMsg->cmdType].cmdHandle((void*)&st);
	
	free(st.data);
	st.data = NULL;
	
	return iRet;
}

/* 消息处理函数 */
void *recvNetHandel(void *arg)
{
	int 	clientFd				= *(int*)arg;
	char    buffer[MSG_BUF_SIZE+1]	= {0};
	int     recvLen					= 0 ;
	int		iret					= 0;//函数执行返回
	CommonPrintf("recvNetHandel [%d]...\n",clientFd);         
	
    while(1)
    {
       
        memset(buffer,0,MSG_BUF_SIZE+1);
        recvLen = recv(clientFd, buffer, MSG_BUF_SIZE, 0);
        if(0 > recvLen)
        {
            CommonPrintf("recv failed\n");
            continue;
        }
		
		CommonPrintf("From socket[%d] recv [%d] bytes data\n",clientFd,recvLen);
		
		buffer[MSG_BUF_SIZE]='\0';
		iret = handMsg(buffer,recvLen,clientFd);
		if(RET_SUCCESS != iret )
		{
			CommonPrintf("handMsg failed\n");
		}
		usleep(1);
    }        
}


int contrlHandle(void*arg)
{
	return 0;
}
int serverHandle(void *arg)
{
	struct sockaddr_in server_addr;
	struct sockaddr_in clientAddr;
	int 	addr_len		  = sizeof(clientAddr);
	int 	client			  = 0;	
	int 	serverSocket	 = 0;

	pid_t	child_pid		  = 0;

	if(0>(serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)))
	{
		CommonPrintf("socket failed\n");
		return RET_FAIL;
	}
	
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	setsockopt(serverSocket,SOL_SOCKET ,SO_REUSEADDR,(const char*)&server_addr,sizeof(server_addr));
	
	if(0 > bind(serverSocket, (struct sockaddr *)&server_addr, sizeof(server_addr)))
	{
		CommonPrintf("connect failed");
		return RET_FAIL;
	}

	if( 0> listen(serverSocket, 5)) 
	{
		CommonPrintf("listen failed");
		return RET_FAIL;
	}
	
	while(1)
	{
		CommonPrintf("Listening on port: %d\n", SERVER_PORT);
		client = accept(serverSocket, (struct sockaddr*)&clientAddr, (socklen_t*)&addr_len);
		if(client < 0)
		{
			CommonPrintf("listen failed");
			continue;
		}
		
		CommonPrintf("IP: %s\n", inet_ntoa(clientAddr.sin_addr));
		CommonPrintf("Port:%d\n", htons(clientAddr.sin_port));
		
		pthread_t pid;
		pthread_create(&pid,NULL,recvNetHandel,(void*)&client);
		pthread_join(pid,NULL);
	}

}

INIT_HANDLE_ST initArray[]=
{
	{"contrl_handle",contrlHandle},
	{"server_handle",serverHandle}
};

int main(int argc, char *argv[])
{	
    int i = 0;
	int iret = 0;
	
	FILE_PARAM_ST st;
	st.filename="file.c";
	getFileLen((void*)&st);
	printFileParamST((void*)&st);

	initFile(&st,"server.c",O_RDONLY,0777);
	mallocFile(&st,"server.c",st.dataLen,1024);
	readFile((void*)&st);
	printFileParamST((void*)&st);

	FILE_PARAM_ST st_new;
	st_new.dataLen = st.dataLen;
	initFile(&st_new,"server_new.c",O_CREAT|O_RDWR,0777,1024);
	
	mallocFile(&st_new,"server_new.c",st.dataLen,1024);
	//printf("st.data:%s\n",st.data);
	memcpy(st_new.data,st.data,st.dataLen);
	writeFile((void*)&st_new);
	printFileParamST((void*)&st_new);
	#if 0
	for(i=0;i<sizeof(initArray)/sizeof(initArray[0]);i++)
	{
		CommonPrintf("running [%s]\n",initArray[i].name);
		iret = initArray[i].init_func(NULL);
		if (RET_SUCCESS != iret)
		{
			CommonPrintf("run [%s] failed\n",initArray[i].name);
			break;
		}
	}
	#endif

	return RET_SUCCESS;
}

