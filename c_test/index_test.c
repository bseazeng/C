/*
头文件：#include <string.h>

定义函数：char * index(const char *s, int c);
函数说明：index()用来找出参数s 字符串中第一个出现的参数c 地址，然后将该字符出现的地址返回。字符串结束字符(NULL)也视为字符串一部分。

*/

#include <string.h>
#include <stdio.h>
int main(void )
{
    char *s = "0123456789012345678901234567890";
    char *p;
    p = index(s, '5');
    printf("%s\n", p);
}