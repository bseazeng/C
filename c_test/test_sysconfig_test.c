/******************************************************************************

                  版权所有 (C), 2016-2200, 个人bsea

 ******************************************************************************
  文 件 名   : sysconfig_test.c
  版 本 号   : 初稿
  作    者   : bseazeng
  生成日期   : Tuesday, April 19, 2016
  最近修改   :
  功能描述   : 函数sysconfig使用举例
  函数列表   :
              main
  修改历史   :
  1.日    期   : Tuesday, April 19, 2016
    作    者   : bseazeng
    修改内容   : 创建文件

******************************************************************************/
#include <stdio.h>
#include <unistd.h>
#define ONE_MB (1024 * 1024)
int main (void)
{
	long num_procs  = 0;
	long page_size  = 0;
	long num_pages  = 0;
	long free_pages = 0;
	long long mem;
	long long free_mem;
	num_procs = sysconf (_SC_NPROCESSORS_CONF);
	printf ("CPU NUM : %ld\n", num_procs);
	page_size = sysconf (_SC_PAGESIZE);
	printf ("sys page unit: %ld K\n", page_size / 1024 );
	num_pages = sysconf (_SC_PHYS_PAGES);
	printf ("sys physical page num: %ld \n", num_pages);
	free_pages = sysconf (_SC_AVPHYS_PAGES);
	printf ("sys free physical page num: %ld\n", free_pages);
	mem = (long long) ((long long)num_pages * (long long)page_size);
	mem /= ONE_MB;
	free_mem = (long long)free_pages * (long long)page_size;
	free_mem /= ONE_MB;
	printf ("total mem: %lld MB \nfree mem: %lld MB\n", mem, free_mem);

	long open_max = sysconf(_SC_OPEN_MAX);  
 	printf("one process can open :%ld file number\n", open_max);    
	return (0);
}

