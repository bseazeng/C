objs:=map_normalfile1 map_normalfile2 sysconfig_test isascii_test index_test gcvt_test rindex_test\
      strcasecmp_test strdup_test strchr_test strcspn_test strtod_test getpagesize_test memchr_test\
      kill_test errno_test
CC=gcc
all:
	for i in $(objs); do $(CC) -o $$i $$i.c; done 
	for i in $(objs); do echo $$i; done 
clean:
	for i in $(objs); do rm $$i;done
	rm *.o