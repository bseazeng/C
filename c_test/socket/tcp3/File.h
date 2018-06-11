/******************************************************************************

                  版权所有 (C), 2001-2011, 神州数码网络有限公司

 ******************************************************************************
  文 件 名   : File.h
  版 本 号   : 初稿
  作    者   : bseazeng
  生成日期   : 2018年5月26日 星期六
  最近修改   :
  功能描述   : File.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2018年5月26日 星期六
    作    者   : bseazeng
    修改内容   : 创建文件

******************************************************************************/

#ifndef __FILE_H__
#define __FILE_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

typedef struct file_param_st_
{
	char *filename;//保持数据的文件名
	char *data;//数据
	char *dataSeg;
	int  dataSegLen;//操作数据片长度
	int  dataLen;//数据总长度
	int  dataOffset; //数据当前偏移量
	int  fd;  //文件描述符
	int  flags; //打开或创建模式
	int  mode; //文件权限
	int  filename_len;//文件名长度
	
}FILE_PARAM_ST;



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __FILE_H__ */
