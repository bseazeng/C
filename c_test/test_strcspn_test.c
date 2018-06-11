/*
头文件：#inclued<string.h>

strcspn() 用来计算字符串 str 中连续有几个字符都不属于字符串 accept，其原型为：
    int strcspn(char *str, char *accept);

【参数说明】str、accept为要进行查找的两个字符串。

strcspn() 从字符串 str 的开头计算连续的字符，而这些字符都完全不在字符串 accept 中。简单地说，若 strcspn() 返回的数值为 n，则代表字符串 str 开头连续有 n 个字符都不含字符串 accept 中的字符。

【返回值】返回字符串 str 开头连续不含字符串 accept 内的字符数目。

注意：如果 str 中的字符都没有在 accept 中出现，那么将返回 atr 的长度；检索的字符是区分大小写的。

提示：函数 strspn() 的含义与 strcspn() 相反，可以对比学习。

*/
#include<stdio.h>
#include <stdlib.h>
#include<string.h>
int main()
{
	char* s1 = "http://c.biancheng.net/cpp/u/biaozhunku/";
	char* s2 = "c is good";
	int n = strcspn(s1,s2);
	printf("The first char both in s1 and s2 is :%c\n",s1[n]);	
	printf("The position in s1 is: %d\n",n);
	return 0;
}

