/*
头文件：#include <string.h>

定义函数：void * memchr(const void *s, char c, size_t n);

函数说明：memchr()从头开始搜寻s 所指的内存内容前n 个字节，直到发现第一个值为c 的字节，则返回指向该字节的指针。

返回值：如果找到指定的字节则返回该字节的指针，否则返回0。

*/

#include <string.h>
#include <stdio.h>

int main()
{
    char *s = "0123456789012345678901234567890";
    char *p = NULL;
    p = memchr(s, '5', 10);
    printf("%s\n", p);
}

