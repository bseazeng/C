/*
头文件：#include <unistd.h>

定义函数：size_t getpagesize(void);

函数说明：返回一分页的大小，单位为字节(byte)。此为系统的分页大小，不一定会和硬件分页大小相同。

返回值：内存分页大小。

附加说明：在 Intel x86 上其返回值应为4096bytes。

*/
#include <unistd.h>
#include <stdio.h>
int main()
{
	printf("page size = %d byte\n", getpagesize());
}

