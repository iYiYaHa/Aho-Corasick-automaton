#ifndef _RED_BLACK_TREE_H_
#define _RED_BLACK_TREE_H_

#define RED        0    // ��ɫ�ڵ�
#define BLACK    1    // ��ɫ�ڵ�

typedef int Type;
typedef struct TreeNodeACA * ValType;
typedef struct Queue Queue;
// ������Ľڵ�
typedef struct RBTreeNode {
	unsigned char color;        // ��ɫ(RED �� BLACK)
	Type   key;                    // �ؼ���(��ֵ)
	ValType val;				// ֵ
	struct RBTreeNode *left;    // ����
	struct RBTreeNode *right;    // �Һ���
	struct RBTreeNode *parent;    // �����
}Node, *RBTree;

// ������ĸ�
typedef struct rb_root {
	Node *node;
}RBRoot;

// ���������������"������ĸ�"��
RBRoot* create_rbtree();

// ���ٺ����
void destroy_rbtree(RBRoot *root);

// �������뵽������С�����ɹ�������0��ʧ�ܷ���-1��
int insert_rbtree(RBRoot *root, Type key, ValType val);

// ɾ�����(keyΪ�ڵ��ֵ)
void delete_rbtree(RBRoot *root, Type key);

// ǰ�����"�����"
void preorder_rbtree(RBRoot *root);
// �������"�����"
void inorder_rbtree(RBRoot *root);
// �������"�����"
void postorder_rbtree(RBRoot *root);

// (�ݹ�ʵ��)����"�����"�м�ֵΪkey�Ľڵ㡣�ҵ��Ļ�������0�����򣬷���-1��
ValType rbtree_search(RBRoot *root, Type key);

// (�ǵݹ�ʵ��)����"�����"�м�ֵΪkey�Ľڵ㡣�ҵ��Ļ�������0�����򣬷���-1��
ValType iterative_rbtree_search(RBRoot *root, Type key);

// ������С����ֵ(��ֵ���浽val��)���ҵ��Ļ�������0�����򷵻�-1��
int rbtree_minimum(RBRoot *root, int *val);
// ����������ֵ(��ֵ���浽val��)���ҵ��Ļ�������0�����򷵻�-1��
int rbtree_maximum(RBRoot *root, int *val);

// ��ӡ�����
void print_rbtree(RBRoot *root);

// ������Ҷ�ӽڵ�������
Queue *put_all_nodes_in_queue(RBRoot *root, Queue *queue);

// �������������Ҷ�ӽڵ�������
void _pre_order_put_in_queue(RBTree tree, Queue *queue);
#endif