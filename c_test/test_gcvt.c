/*
头文件：#include <stdlib.h>

定义函数：char *gcvt(double number, size_t ndigits, char *buf);

函数说明：gcvt()用来将参数number 转换成ASCII 码字符串，参数ndigits 表示显示的位数。gcvt()与ecvt()和fcvt()不同的地方在于，gcvt()所转换后的字符串包含小数点或正负符号。若转换成功，转换后的字符串会放在参数buf 指针所指的空间。

*/


#include <stdlib.h>
#include <stdio.h>
int main(void)
{
    char str[25];
    double num;
    int sig = 5; /* significant digits */
    /* a regular number */
    num = 9.876;
    gcvt(num, sig, str);
     
	printf("string = %s\n", str);
    /* a negative number */
    num = -123.4567;
    gcvt(num, sig, str);
     
	printf("string = %s\n", str);
    /* scientific notation */
    num = 0.678e5;
    gcvt(num, sig, str);
     
	printf("string = %s\n", str);
    return(0);
}
 


