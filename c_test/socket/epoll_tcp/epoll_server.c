/******************************************************************************

                  ��Ȩ���� (C), 2016-2200, ����bsea

 ******************************************************************************
  �� �� ��   : epoll_server.c
  �� �� ��   : ����
  ��    ��   : bseazeng
  ��������   : Monday, May 2, 2016
  ����޸�   :
  ��������   : a tcp socket server with epoll
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : Monday, May 2, 2016
    ��    ��   : bseazeng
    �޸�����   : �����ļ�

******************************************************************************/
#include "epoll_server.h"
/*
gcc -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -I${ORACLE_HOME}/rdbms/public -I${ORACLE_HOME}/rdbms/demo -L${ORACLE_HOME}/lib -lclntsh  -pthread -o epoll_server epoll_server.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <arpa/inet.h>
//#include <openssl/engines/ssl.h>
//#include <openssl/err.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <sys/time.h>
#include <sys/resource.h>

 

//#include "oci_api.h"

 

#define MAXBUF 1024
#define MAXEPOLLSIZE 10000

/*
setnonblocking - ���þ��Ϊ��������ʽ
*/
int setnonblocking(int sockfd)
{
    if (fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFD, 0)|O_NONBLOCK) == -1) {
        return -1;
    }
    return 0;
}

/*
handle_message - ����ÿ�� socket �ϵ���Ϣ�շ�
*/
int handle_message(int new_fd)
{
    char buf[MAXBUF + 1];
    char sendbuf[MAXBUF+1];
    int len;
    /* ��ʼ����ÿ���������ϵ������շ� */
    bzero(buf, MAXBUF + 1);
    /* ���տͻ��˵���Ϣ */
    len = recv(new_fd, buf, MAXBUF, 0);
    if (len > 0)
	{

        printf
            ("%d������Ϣ�ɹ�:'%s'����%d���ֽڵ�����/n",
             new_fd, buf, len);
    }
    else 
	{
        if (len < 0)
        {
            printf("��Ϣ����ʧ�ܣ����������%d��������Ϣ��'%s'/n", errno, strerror(errno));
        }
		else
		{
			printf ("�ͻ���%d�˳�!/n",new_fd);
		}
    
        //close(new_fd);
        return -1;
    }
    /* ����ÿ���������ϵ������շ����� */
    return len;
}
/************���ڱ��ĵ�********************************************
*filename: epoll-server.c
*purpose: ��ʾepoll��������socket���ӵķ���
*wrote by: zhoulifa(zhoulifa@163.com) ������(http://zhoulifa.bokee.com)
Linux������ Linux֪ʶ������ SOHO�� ������ ���ó�C����
*date time:2007-01-31 21:00
*Note: �κ��˿������⸴�ƴ��벢������Щ�ĵ�����Ȼ���������ҵ��;
* ������ѭGPL
*Thanks to:Google
*Hope:ϣ��Խ��Խ����˹����Լ���������Ϊ��ѧ������չ����
* �Ƽ�վ�ھ��˵ļ���Ͻ������죡��л�п�Դǰ���Ĺ��ף�
*********************************************************************/
int main(int argc, char **argv)
{
    int listener = 0;
	int new_fd   = 0;
	int nfds     = 0;
	int n         = 0;
	int ret      = 0;
    struct epoll_event ev;
    int kdpfd, curfds;
    socklen_t len;
    struct sockaddr_in my_addr, their_addr;
    unsigned int myport, lisnum;
    struct epoll_event events[MAXEPOLLSIZE];
    struct rlimit rt;

    if (argc>1)
    {
        myport = atoi(argv[1]);
    }
    else
    {
        myport = 1234;
    }

    if (argc>2)
    {
        lisnum = atoi(argv[2]);
    }
    else
    {
        lisnum = 10;
    }

    /* ����ÿ�����������򿪵�����ļ��� */
    rt.rlim_max = rt.rlim_cur = MAXEPOLLSIZE;
    if (setrlimit(RLIMIT_NOFILE, &rt) == -1) 
	{
        perror("setrlimit");
        exit(1);
    }
    else 
	{
		printf("����ϵͳ��Դ�����ɹ���/n");
	}
		

    /* ���� socket ���� */
    if ((listener = socket(PF_INET, SOCK_STREAM, 0)) == -1) 
	{
        perror("socket");
        exit(1);
    } 
	else
	{
		printf("socket �����ɹ���/n");
	}       

    /*����socket���ԣ��˿ڿ�������*/
    int opt=SO_REUSEADDR;
    setsockopt(listener,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

    /*����socketΪ������ģʽ*/
    setnonblocking(listener);

    bzero(&my_addr, sizeof(my_addr));
    my_addr.sin_family = PF_INET;
    my_addr.sin_port = htons(myport);
    if (3 < argc)
    {
        my_addr.sin_addr.s_addr = inet_addr(argv[3]);
    }
    else
    {
        my_addr.sin_addr.s_addr = INADDR_ANY;
    }

    if (-1 == bind  (listener, (struct sockaddr *) &my_addr, sizeof(struct sockaddr))) 
    {
        perror("bind");
        exit(1);
    } 
	else
	{
        printf("IP ��ַ�Ͷ˿ڰ󶨳ɹ�/n");
	}

    if (listen(listener, lisnum) == -1) 
	{
        perror("listen");
        exit(1);
    } 
	else
	{
		printf("��������ɹ���/n");
	}
        

    /* ���� epoll ������Ѽ��� socket ���뵽 epoll ������ */
    kdpfd = epoll_create(MAXEPOLLSIZE);
    len = sizeof(struct sockaddr_in);
    ev.events = EPOLLIN | EPOLLET;
    ev.data.fd = listener;
    if (epoll_ctl(kdpfd, EPOLL_CTL_ADD, listener, &ev) < 0) 
	{
        fprintf(stderr, "epoll set insertion error: fd=%d/n", listener);
        return -1;
    } 
	else
	{
    	printf("���� socket ���� epoll �ɹ���/n");
	}
    curfds = 1;
    while (1) 
	{
        /* �ȴ����¼����� */
        nfds = epoll_wait(kdpfd, events, curfds, -1);
        if (nfds == -1) 
		{
            perror("epoll_wait");
            break;
        }
        /* ���������¼� */
        for (n = 0; n < nfds; ++n) 
		{
            if (events[n].data.fd == listener) 
			{
                new_fd = accept(listener, (struct sockaddr *) &their_addr, &len);
                if (new_fd < 0)
				{
                    perror("accept");
                    continue;
                } 
				else
				{				
					printf("�����������ڣ� %s:%d�� ����� socket Ϊ:%d/n", inet_ntoa(their_addr.sin_addr), ntohs(their_addr.sin_port), new_fd);
				}
                   
                setnonblocking(new_fd);
                ev.events = EPOLLIN | EPOLLET;
                ev.data.fd = new_fd;
                if (epoll_ctl(kdpfd, EPOLL_CTL_ADD, new_fd, &ev) < 0) 
				{
                    fprintf(stderr, "�� socket '%d' ���� epoll ʧ�ܣ�%s/n",
                            new_fd, strerror(errno));
                    return -1;
                }
                curfds++;
            }
			else 
			{
                ret = handle_message(events[n].data.fd);
                if (ret < 1 && errno != 11) 
				{
                    if(epoll_ctl(kdpfd, EPOLL_CTL_DEL, events[n].data.fd, &ev) < 0)
		            {
		             fprintf(stderr, "�� socket '%d' �� epoll ɾ��ʧ�ܣ�%s/n",events[n].data.fd, strerror(errno));
		            }
                    curfds--;
     				close(events[n].data.fd);
	           }
            }
        }
    }
    close(listener);
    return 0;
}

 
