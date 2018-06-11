/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ���������������޹�˾

 ******************************************************************************
  �� �� ��   : File.h
  �� �� ��   : ����
  ��    ��   : bseazeng
  ��������   : 2018��5��26�� ������
  ����޸�   :
  ��������   : File.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2018��5��26�� ������
    ��    ��   : bseazeng
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __FILE_H__
#define __FILE_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

typedef struct file_param_st_
{
	char *filename;//�������ݵ��ļ���
	char *data;//����
	char *dataSeg;
	int  dataSegLen;//��������Ƭ����
	int  dataLen;//�����ܳ���
	int  dataOffset; //���ݵ�ǰƫ����
	int  fd;  //�ļ�������
	int  flags; //�򿪻򴴽�ģʽ
	int  mode; //�ļ�Ȩ��
	int  filename_len;//�ļ�������
	
}FILE_PARAM_ST;



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __FILE_H__ */
