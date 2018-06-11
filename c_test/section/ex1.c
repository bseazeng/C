#include <stdio.h>
int localmemory0 __attribute__((section("LOCALmem"))) = 0;
int localmemory1 __attribute__((section("LOCALmem"))) = 0;
int globalmemory __attribute__((section("GLOBALmem"))) = 0;

int main (int argc, char *argv[])
{
    localmemory0 = 0x456;
    localmemory1 = 0x123;

    globalmemory = localmemory0 + localmemory1;
}