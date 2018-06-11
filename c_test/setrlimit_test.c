/******************************************************************************

                  版权所有 (C), 2016-2200, 个人bsea

 ******************************************************************************
  文 件 名   : setrlimit_test.c
  版 本 号   : 初稿
  作    者   : bseazeng
  生成日期   : Tuesday, April 19, 2016
  最近修改   :
  功能描述   : setrlimit方法测试用例
  函数列表   :
  修改历史   :
  1.日    期   : Tuesday, April 19, 2016
    作    者   : bseazeng
    修改内容   : 创建文件

#include <sys/resource.h>
int getrlimit(int resource, struct rlimit *rlp);
int setrlimit(int resource, const struct rlimit *rlp);

******************************************************************************/

