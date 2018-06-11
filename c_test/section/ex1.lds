SECTIONS
{
      LOCALmem 0x1f0000 : 
      {
  
      *(LOCALmem)
      }

    GLOBALmem 0xff0000 : 
    {
    *(GLOBALmem)
    }

}

INSERT AFTER .rodata