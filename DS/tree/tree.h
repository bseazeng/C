/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ���������������޹�˾

 ******************************************************************************
  �� �� ��   : tree.h
  �� �� ��   : ����
  ��    ��   : bseazeng
  ��������   : 2018��2��25�� ������
  ����޸�   :
  ��������   : tree.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2018��2��25�� ������
    ��    ��   : bseazeng
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __TREE_H__
#define __TREE_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/*
�ڵ�
*/
struct STRUCT_TreeNode
{
	unsigned long long node_index;//�ڵ���
	unsigned long long node_magic;//�ڵ�ħ���������ж����Ƿ�Ϊ������(���������ȫ����)
	void *data;//�ڵ�����
	struct STRUCT_TreeNode *lchild;//���ӽڵ�
	struct STRUCT_TreeNode *rchild;//���ӽڵ�
	struct STRUCT_TreeNode *parent;//���ڵ�

	void FUN_InitNode( struct STRUCT_TreeNode ** node );//��ʼ���ڵ�
	void FUN_AddLeftNode( struct STRUCT_TreeNode ** node, struct STRUCT_TreeNode 
	*leftnode);//�����ڵ�

	void FUN_AddRightNode( struct STRUCT_TreeNode ** node, struct STRUCT_TreeNode 
	*leftnode);//����ҽڵ�
	
};
/*
��(Tree)��n(n>=0)���ڵ�����޼���
������һ�ÿ�����:
	(1)������һ���ض��ĳ�Ϊ��(Root)�Ľڵ㣻
	(2)��n>1ʱ������ڵ�ɷ�Ϊm(m>0)�������ཻ�����޼�T1,T2,T3,...,Tm��
	����ÿ�������屾������һ�ã����ҳ�Ϊ��������(SubTree)
*/
struct STRUCT_Tree
{
	unsigned long long node_number; //���Ľڵ����
	
	unsigned long long depth;//�������
	
	struct STRUCT_TreeNode *nods;//���Ľڵ�
	
	void FUN_InitTree( struct STRUCT_Tree *tree );//��ʼ����treeΪ��
	
	void FUN_DestoryTree( struct STRUCT_Tree *tree );//ɾ��tree��
	
	unsigned long long FUN_CreateTree( struct STRUCT_Tree *tree, char *filename );//ͨ�������ļ�filename������
	
	unsigned int FUN_IsEmptyTree( struct STRUCT_Tree *tree );//�ж���tree�Ƿ�Ϊ��
	
	unsigned long long FUN_GetDepthTree( struct STRUCT_Tree *tree );//�����tree�����

	struct STRUCT_TreeNode * FUN_GetRoot( struct STRUCT_Tree *tree );//������ĸ��ڵ�

	struct STRUCT_TreeNode * FUN_GetNode( struct STRUCT_Tree *tree, unsigned long long node_index );//��ñ��node_index�Ľڵ�

	unsigned long long FUN_SetNode( struct STRUCT_Tree *tree, unsigned long long node_index, struct STRUCT_TreeNode *node );//���ñ��node_index�Ľڵ�

	struct STRUCT_Tree * FUN_GetChildTree( struct STRUCT_Tree *tree, unsigned long long node_index 
	) ;//�������

	struct STRUCT_Tree * FUN_SetChildTree( struct STRUCT_Tree *tree, unsigned long long node_index ,struct STRUCT_Tree 
*child_tree	) ;//�������
	
};	

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __TREE_H__ */
