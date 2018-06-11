/******************************************************************************

                  版权所有 (C), 2001-2011, 神州数码网络有限公司

 ******************************************************************************
  文 件 名   : File.c
  版 本 号   : 初稿
  作    者   : bseazeng
  生成日期   : 2018年5月26日 星期六
  最近修改   :
  功能描述   : 文件操作函数
  函数列表   :
  修改历史   :
  1.日    期   : 2018年5月26日 星期六
    作    者   : bseazeng
    修改内容   : 创建文件

******************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>

#include "common.h"
#include "File.h"

int mallocFile(void *fileParam,char* filename,int dataLen, int dataSegLen)
{

	if  ( NULL == fileParam )
	{
	    CommonPrintf("file_param is null\n");
		return RET_FAIL;
	}
	FILE_PARAM_ST *pst = (FILE_PARAM_ST*)fileParam;

	if ( 0 > pst->filename_len )
	{
	    CommonPrintf("pst->filename_len is less than 0\n");
		return RET_FAIL;
	}
	pst->filename = malloc(pst->filename_len+1);
	if ( NULL  == pst->filename)
	{
	    CommonPrintf("malloc failed,errno[%d]:%s\n",errno,strerror(errno));
		return RET_FAIL;
	}	
	memcpy(pst->filename,filename,pst->filename_len);	
	pst->filename[pst->filename_len] = '\0';
	

	pst->dataLen = dataLen;
	if ( 0 > pst->dataLen )
	{
	    CommonPrintf("pst->dataLen is less than 0\n");
		return RET_FAIL;
	}
	pst->data = malloc(pst->dataLen);
	if ( NULL  == pst->data)
	{
	    CommonPrintf("malloc failed,errno[%d]:%s\n",errno,strerror(errno));
		return RET_FAIL;
	}
	
	pst->dataSegLen = dataSegLen; //数据片长度加1，最后一个为结束符
	return RET_SUCCESS;
}

/*****************************************************************************
 函 数 名  : initFile
 功能描述  : 打开文件
 输入参数  : char *filename
             int *fd
             int mode
 输出参数  : 无
 返 回 值  : int
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2018年5月26日 星期六
    作    者   : bseazeng
    修改内容   : 新生成函数

*****************************************************************************/
int initFile( void *file_param, char *filname,int flags, int mode)
{
	
    if ( NULL == filname )
    {
        CommonPrintf("filname is null\n");
		return RET_FAIL;
    }
	if  ( NULL == file_param )
	{
	    CommonPrintf("file_param is null\n");
		return RET_FAIL;
	}
	
	FILE_PARAM_ST *pst = (FILE_PARAM_ST*)file_param;
	
	pst->fd= open(filname,flags,mode);
	if ( 0 > pst->fd )
	{
	    CommonPrintf("open failed\n");
		return RET_FAIL;
	}

	pst->filename_len = strlen(filname);	

	pst->dataOffset = 0;
	
	return RET_SUCCESS;
	
}

/*****************************************************************************
 函 数 名  : getFileLen
 功能描述  : 获取文件大小
 输入参数  : void *arg
 输出参数  : 无
 返 回 值  : int
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2018年5月26日 星期六
    作    者   : bseazeng
    修改内容   : 新生成函数

*****************************************************************************/
int getFileLen( void *arg )
{
    FILE_PARAM_ST *pst = (FILE_PARAM_ST *)arg;
	struct stat st;
	int iRet = 0;

	if ( NULL == pst )
	{
	    CommonPrintf("pst is null\n");
		return RET_FAIL;
	}

	iRet = stat(pst->filename,&st);

	pst->dataLen = st.st_size;
	return st.st_size;
	
}

/*****************************************************************************
 函 数 名  : readFile2
 功能描述  : 读取文件
 输入参数  : void *arg
 输出参数  : 无
 返 回 值  : int
 修改历史      :
  1.日    期   : 2018年5月26日 星期六
    作    者   : bseazeng
    修改内容   : 新生成函数

*****************************************************************************/
int readFile2( void *arg )
{
    FILE_PARAM_ST *pst = (FILE_PARAM_ST*)arg;

	if ( NULL == pst )
	{
	    CommonPrintf("pst is null \n");
		return RET_FAIL;
	}

	if ( 0 > pst->dataLen )
	{
	    CommonPrintf("pst->dataLen is less than 0\n");
		return RET_FAIL;
	}
	
	pst->dataOffset = 0;
	int rlen = 0;
	while( pst->dataOffset + pst->dataSegLen < pst->dataLen )
	{
		rlen = read(pst->fd, &(pst->data[pst->dataOffset]),pst->dataSegLen);
		if ( rlen !=  pst->dataSegLen )
		{
		    CommonPrintf("read failed\n");
			return RET_FAIL;
		}
		
		pst->dataOffset += pst->dataSegLen;
		usleep(1);
	}
	
	rlen = read(pst->fd, &(pst->data[pst->dataOffset]), pst->dataLen%pst->dataSegLen);
	CommonPrintf("len[%d] data:%s\n",rlen,&(pst->data[pst->dataOffset]));
	pst->dataOffset += rlen;

	if ( pst->dataOffset != pst->dataLen )
	{
	    CommonPrintf("read file [%s],dataLen [%d],dataOffset [%d] failed\n",pst->filename,pst->dataLen,pst->dataOffset);
		return RET_FAIL;
	}

	pst->dataOffset = 0;
	CommonPrintf("read file [%s],size [%d] success\n",pst->filename,pst->dataLen);
	return RET_SUCCESS;
	
}


/*****************************************************************************
 函 数 名  : readFile
 功能描述  : 读取文件
 输入参数  : void *arg
 输出参数  : 无
 返 回 值  : int
 修改历史      :
  1.日    期   : 2018年5月26日 星期六
    作    者   : bseazeng
    修改内容   : 新生成函数

*****************************************************************************/
int readFile( void *arg )
{
    FILE_PARAM_ST *pst = (FILE_PARAM_ST*)arg;

	if ( NULL == pst )
	{
	    CommonPrintf("pst is null \n");
		return RET_FAIL;
	}

	if ( 0 > pst->dataLen )
	{
	    CommonPrintf("pst->dataLen is less than 0\n");
		return RET_FAIL;
	}
	
	pst->dataOffset = 0;
	int rlen = 0;
	while( 0 < (rlen = read(pst->fd, &(pst->data[pst->dataOffset]),pst->dataSegLen) ))
	{
		pst->dataOffset += rlen;
	}
	
	pst->dataLen = pst->dataOffset;
	if ( pst->dataOffset != pst->dataLen )
	{
	    CommonPrintf("read file [%s],dataLen [%d],dataOffset [%d] failed\n",pst->filename,pst->dataLen,pst->dataOffset);
		return RET_FAIL;
	}

	pst->dataOffset = 0;
	CommonPrintf("read file [%s],size [%d] success\n",pst->filename,pst->dataLen);
	return RET_SUCCESS;
	
}


/*****************************************************************************
 函 数 名  : writeFile
 功能描述  :写入文件
 输入参数  : void *arg
 输出参数  : 无
 返 回 值  : int
 修改历史      :
  1.日    期   : 2018年5月26日 星期六
    作    者   : bseazeng
    修改内容   : 新生成函数

*****************************************************************************/
int writeFile( void *arg )
{
    FILE_PARAM_ST *pst = (FILE_PARAM_ST*)arg;

	if ( NULL == pst )
	{
	    CommonPrintf("pst is null \n");
		return RET_FAIL;
	}

	if ( 0 > pst->dataLen )
	{
	    CommonPrintf("pst->dataLen is less than 0\n");
		return RET_FAIL;
	}
	
	pst->dataOffset = 0;
	int wlen = 0;
	while( pst->dataOffset + pst->dataSegLen < pst->dataLen )
	{
		wlen = write(pst->fd,pst->data + pst->dataOffset,pst->dataSegLen);
		if ( wlen != pst->dataSegLen )
		{
		    CommonPrintf("write failed\n");
			return RET_FAIL;
		}
		pst->dataOffset += pst->dataSegLen;
	}

	wlen = write(pst->fd, pst->data + pst->dataOffset, pst->dataLen%pst->dataSegLen);
	pst->dataOffset += wlen;

	if ( pst->dataOffset != pst->dataLen )
	{
	    CommonPrintf("write file [%s],dataLen [%d],dataOffset [%d] failed\n",pst->filename,pst->dataLen,pst->dataOffset);
	}

	//printf("data:%s\n",pst->data);
	CommonPrintf("write file [%s],size [%d] success\n",pst->filename,pst->dataLen);
	
	return RET_SUCCESS;
	
}



/*****************************************************************************
 函 数 名  : printFileParamST
 功能描述  : 显示文件参数结构
 输入参数  : void *arg
 输出参数  : 无
 返 回 值  : void
 调用函数  : 
 被调函数  : 
 
 修改历史      :
  1.日    期   : 2018年5月26日 星期六
    作    者   : bseazeng
    修改内容   : 新生成函数

*****************************************************************************/
void printFileParamST( void *arg )
{
    FILE_PARAM_ST *pst = (FILE_PARAM_ST*)arg;

	if ( NULL == pst )
	{
	    CommonPrintf("pst is null\n");
		return;
	}

	CommonPrintf("display File Param Struct:\n");
	if ( NULL !=  pst->filename)
	{
	    printf("pst->filename:    [%s]\n",pst->filename);
		printf("pst->dataLen :    [%d]\n",pst->dataLen);
		printf("pst->dataSegment: [%d]\n",pst->dataSegLen);
	}

	
}

