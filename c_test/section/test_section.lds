
SECTIONS
{
    _init_start = .;
    .myinit : { KEEP(*(.myinit)) }
    _init_end = .;

}

INSERT AFTER .text