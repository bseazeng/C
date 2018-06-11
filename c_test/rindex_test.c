/*
头文件：#include <string.h>

定义函数：char * rindex(const char *s, int c);

函数说明：rindex()用来找出参数s 字符串中最后一个出现的参数c 地址，然后将该字符出现的地址返回。字符串结束字符(NULL)也视为字符串一部分。

返回值：如果找到指定的字符则返回该字符所在的地址，否则返回0。

*/
#include <stdio.h>
#include <string.h>

int main(void)
{
	char *s = "0123456789012345678901234567890";
	char *p = NULL;
	p = rindex(s, '5');
	if(NULL != p)
		printf("%s\n", p);

	return 0;
}

