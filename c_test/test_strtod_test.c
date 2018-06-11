/*
头文件：#include <stdlib.h>

函数 strtod() 用来将字符串转换成双精度浮点数(double)，其原型为：
double strtod (const char* str, char** endptr);

【参数说明】str 为要转换的字符串，endstr 为第一个不能转换的字符的指针。

【函数说明】strtod() 函数会扫描参数str字符串，跳过前面的空白字符（例如空格，tab缩进等，可以通过 isspace() 函数来检测），直到遇上数字或正负符号才开始做转换，到出现非数字或字符串结束时('\0')才结束转换，并将结果返回。参数 str 字符串可包含正负号、小数点或E(e)来表示指数部分。如123. 456 或123e-2。

若endptr 不为NULL，则会将遇到的不符合条件而终止的字符指针由 endptr 传回；若 endptr 为 NULL，则表示该参数无效，或不使用该参数。

【返回值】返回转换后的浮点型数；若不能转换或字符串为空，则返回 0.0。

温馨提示：ANSI C 规范定义了 stof()、atoi()、atol()、strtod()、strtol()、strtoul() 共6个可以将字符串转换为数字的函数，大家可以对比学习；使用 strtod(str, NULL) 与使用 atof() 结果相同。另外在 C99 / C++11 规范中又新增了5个函数，分别是 atoll()、strtof()、strtold()、strtoll()、strtoull()，在此不做介绍，请大家自行学习。

*/

#include <stdio.h>
#include <stdlib.h>
void printChinese(const char*content)
{
	if ( NULL == content )
	{
	    return;
	}
	int len = strlen(content);
	int i = 0;
	for(i=0;i<len;i++)
	{
		
	}
}
int main(void)
{
	char szOrbits[] = "365.24 29.53";
	char* pEnd = NULL;
	double d1 = 0;
	double d2 = 0;
	d1 = strtod (szOrbits, &pEnd);
	d2 = strtod (pEnd, NULL);
	printChinese("月球每年绕地球运行\n");
	printf ("月球每年绕地球运行 %.2f 周。\n", d1/d2);
	return 0;
}

