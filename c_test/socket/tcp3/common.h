#ifndef __COMMON_H__
#define __COMMON_H__

#define RET_SUCCESS (0)
#define RET_FAIL    (-1)
#define RET_TRUE    (1)
#define RET_FALSE   (0)

#define COMMON_DEBUG 1

#ifdef COMMON_DEBUG
#define CommonPrintf(fmt,arg...) \
do\
{\
    printf("[%*s][%*d]\t"fmt"\n",-32,__FILE__,-8,__LINE__,##arg);\
}while(0)
#else
#define CommonPrintf printf





#endif
#endif
