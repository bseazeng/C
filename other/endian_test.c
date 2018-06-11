#include <stdio.h>
/*
所谓的大端模式（Big-endian），是指数据的高字节，保存在内存的低地址中，而数据的低字节，保存在内存的高地址中，这样的存储模式有点儿类似于把数据当作字符串顺序处理：地址由小向大增加，而数据从高位往低位放；

所谓的小端模式（Little-endian），是指数据的高字节保存在内存的高地址中，而数据的低字节保存在内存的低地址中，这种存储模式将地址的高低和数据位权有效地结合起来，高地址部分权值高，低地址部分权值低，和我们的逻辑方法一致。
*/
union   
{  
    int number;  
    char s;  
}test;  

void func1()
{
    //地址s和number是相同的。
    
    printf("address of number:%p\n",&(test.number));
    printf("address of s:%p\n",&(test.s));
    
    test.number=0x01000002; 
    printf("s=0x%x\n",test.s);
    if( 0x01 == test.s )
        printf("system is big endian\n");
    else
        printf("system is little endian\n");
}
int main(int argc, char *argv[])
{
    int a=0x12345678;
    char b[sizeof(a)]={0};
    int i=0;
    for(i=0;i<sizeof(int);++i)
    {
        b[i]=((char*)(&a))[i];
        printf("address[%p] b[%d]: 0x%x\n",&b[i],i,b[i]);
    }
    
    printf("--------------\n");
    func1();
    return 0;
}

   