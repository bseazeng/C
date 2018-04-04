/******************************************************************************

                  版权所有 (C), 2001-2011, 神州数码网络有限公司

 ******************************************************************************
  文 件 名   : tree.h
  版 本 号   : 初稿
  作    者   : bseazeng
  生成日期   : 2018年2月25日 星期日
  最近修改   :
  功能描述   : tree.c 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2018年2月25日 星期日
    作    者   : bseazeng
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TREE_H__
#define __TREE_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/*
节点
*/
struct STRUCT_TreeNode
{
	unsigned long long node_index;//节点编号
	unsigned long long node_magic;//节点魔数，用来判断树是否为特殊树(满二叉或完全二叉)
	void *data;//节点数据
	struct STRUCT_TreeNode *lchild;//左子节点
	struct STRUCT_TreeNode *rchild;//右子节点
	struct STRUCT_TreeNode *parent;//父节点

	void FUN_InitNode( struct STRUCT_TreeNode ** node );//初始化节点
	void FUN_AddLeftNode( struct STRUCT_TreeNode ** node, struct STRUCT_TreeNode 
	*leftnode);//添加左节点

	void FUN_AddRightNode( struct STRUCT_TreeNode ** node, struct STRUCT_TreeNode 
	*leftnode);//添加右节点
	
};
/*
树(Tree)是n(n>=0)个节点的有限集。
在任意一棵空树中:
	(1)有且有一个特定的称为根(Root)的节点；
	(2)当n>1时，其余节点可分为m(m>0)个互不相交的有限集T1,T2,T3,...,Tm，
	其中每个集合体本身又是一棵，并且称为根的子树(SubTree)
*/
struct STRUCT_Tree
{
	unsigned long long node_number; //树的节点个数
	
	unsigned long long depth;//树的深度
	
	struct STRUCT_TreeNode *nods;//树的节点
	
	void FUN_InitTree( struct STRUCT_Tree *tree );//初始化树tree为空
	
	void FUN_DestoryTree( struct STRUCT_Tree *tree );//删除tree树
	
	unsigned long long FUN_CreateTree( struct STRUCT_Tree *tree, char *filename );//通过配置文件filename创建树
	
	unsigned int FUN_IsEmptyTree( struct STRUCT_Tree *tree );//判读树tree是否为空
	
	unsigned long long FUN_GetDepthTree( struct STRUCT_Tree *tree );//获得树tree的深度

	struct STRUCT_TreeNode * FUN_GetRoot( struct STRUCT_Tree *tree );//获得树的根节点

	struct STRUCT_TreeNode * FUN_GetNode( struct STRUCT_Tree *tree, unsigned long long node_index );//获得编号node_index的节点

	unsigned long long FUN_SetNode( struct STRUCT_Tree *tree, unsigned long long node_index, struct STRUCT_TreeNode *node );//设置编号node_index的节点

	struct STRUCT_Tree * FUN_GetChildTree( struct STRUCT_Tree *tree, unsigned long long node_index 
	) ;//获得子树

	struct STRUCT_Tree * FUN_SetChildTree( struct STRUCT_Tree *tree, unsigned long long node_index ,struct STRUCT_Tree 
*child_tree	) ;//获得子树
	
};	

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __TREE_H__ */
