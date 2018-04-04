#include <stdio.h>

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

   