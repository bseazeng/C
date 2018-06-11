/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ���������������޹�˾

 ******************************************************************************
  �� �� ��   : File.c
  �� �� ��   : ����
  ��    ��   : bseazeng
  ��������   : 2018��5��26�� ������
  ����޸�   :
  ��������   : �ļ���������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2018��5��26�� ������
    ��    ��   : bseazeng
    �޸�����   : �����ļ�

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
	
	pst->dataSegLen = dataSegLen; //����Ƭ���ȼ�1�����һ��Ϊ������
	return RET_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : initFile
 ��������  : ���ļ�
 �������  : char *filename
             int *fd
             int mode
 �������  : ��
 �� �� ֵ  : int
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2018��5��26�� ������
    ��    ��   : bseazeng
    �޸�����   : �����ɺ���

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
 �� �� ��  : getFileLen
 ��������  : ��ȡ�ļ���С
 �������  : void *arg
 �������  : ��
 �� �� ֵ  : int
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2018��5��26�� ������
    ��    ��   : bseazeng
    �޸�����   : �����ɺ���

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
 �� �� ��  : readFile2
 ��������  : ��ȡ�ļ�
 �������  : void *arg
 �������  : ��
 �� �� ֵ  : int
 �޸���ʷ      :
  1.��    ��   : 2018��5��26�� ������
    ��    ��   : bseazeng
    �޸�����   : �����ɺ���

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
 �� �� ��  : readFile
 ��������  : ��ȡ�ļ�
 �������  : void *arg
 �������  : ��
 �� �� ֵ  : int
 �޸���ʷ      :
  1.��    ��   : 2018��5��26�� ������
    ��    ��   : bseazeng
    �޸�����   : �����ɺ���

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
 �� �� ��  : writeFile
 ��������  :д���ļ�
 �������  : void *arg
 �������  : ��
 �� �� ֵ  : int
 �޸���ʷ      :
  1.��    ��   : 2018��5��26�� ������
    ��    ��   : bseazeng
    �޸�����   : �����ɺ���

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
 �� �� ��  : printFileParamST
 ��������  : ��ʾ�ļ������ṹ
 �������  : void *arg
 �������  : ��
 �� �� ֵ  : void
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2018��5��26�� ������
    ��    ��   : bseazeng
    �޸�����   : �����ɺ���

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

