SECTIONS
{
    .myinit ALIGN(4) : { KEEP(*(.myinit)) }
    PROVIDE(_init_start = ADDR(.myinit));
    PROVIDE(_init_end = ADDR(.myinit)+SIZEOF(.myinit));

}
INSERT BEFORE .bss