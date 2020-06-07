/*
 * 二叉排序树 Binary Sort Tree
 * 左子树小于根， 右子树都大于根
 * 用于动态查找
 * 
 * 中序遍历就可以得到一个有序的序列
 * 
 * 插入
 * 很简单，中序遍历的过程
 * 
 * 删除
 * - 叶子直接删：如果被删节点是叶子节点，直接删除即可
 * - 单孩直接代：如果被删节点只有一个孩子，直接使用其孩子替代其位置即可
 * - 中序前驱代：指被删节点有两个孩子，此时有两种处理方式，
 * 假设： p 是要删除的结点，f 是p的父结点
 * (1)  p的左孩子作为f的左孩子， f->lchild = p->lchild;   
 *      p的右孩子作为 其中序遍历前驱的右孩子
 * (2) 用p的中序遍历直接前驱代替p,  然后再删除其直接前驱（递归）
 */

#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;                                   //元素类型

typedef struct Node{
    ElemType data;
    Node* lchild;
    Node* rchild;
}Node;

typedef struct BinarySortTree{
    Node* root;
}BinarySortTree;


void Display(Node* root){
    if(root == NULL) return;
    Display(root->lchild);
    printf("%d ", root->data);
    Display(root->rchild);
}

// 插入 - 中序遍历
Node* Insert(Node* root, ElemType data){
    if(root == NULL){
        root = (Node*)malloc(sizeof(Node));
        root->data = data;
        root->lchild = root->rchild = NULL;
        return root;
    }

    // 相等，已经存在，不用插入
    if(data == root->data){
    }

    // 小于，插入到左子树
    else if(data < root->data){
        root->lchild = Insert(root->lchild,data);
        return root;
    }

    // 大于，插入到右子树
    else if(data > root->data){
        root->rchild = Insert(root->rchild,data);
    }

    return root;
}

// 查找，找到返回p, 否则返回NULL
Node* Search(Node* root, ElemType data){
    return NULL;
}


// 删除 root 结点
Node* Delete(Node* root, ElemType data){
    if(root == NULL) return NULL;

    // 没有左孩子
    if(root->lchild == NULL){
        // 直接用右孩子替代
        Node* p = root;
        root = root->rchild;  // 将root直接指向右孩子
        free(p);
    }

    // 没有右孩子
    else if(root->rchild == NULL){
        // 直接用左孩子替代
        Node* p = root;
        root = root->lchild;  // 将root直接指向左孩子
        free(p);
    }

    // 有两个孩子
    else{

        // 找到中序遍历的前驱（在左孩子的树中）
        Node* parent = root;         // 指向 pre的parent
        Node* pre = root->lchild;    // 指向 root的前驱
        
        while(pre->rchild != NULL) { // root的前驱，肯定是最后一个右孩子，不断遍历找
            parent = pre;
            pre = pre->rchild;
        }

        // 找到，pre就是前驱，parent 就是前驱的父结点

        // 用前驱覆盖root
        root->data = pre->data;

        // 删除前驱

        if(root == parent){ // 前驱就是 左孩子， 直接 root的左孩子 指向前驱的左孩子即可
            parent->lchild = pre->lchild; //
        }else{              // 前驱在 左孩子的右子树中，前驱结点是父结点parent的右孩子，且前驱本身必然没有右孩子，直接将parent的右孩子 指向 前驱的左孩子即可
            parent->rchild = pre->lchild;
        }

        free(pre);
    }
    return root;
}

// DeleteBST
Node* DeleteBST(Node* root, ElemType data){
    if(root == NULL) return NULL;

    if (root->data == data) {
        printf("find delete\n");
        root = Delete(root, data);    // 删除结点root
    }

    else if(data < root->data){
        root->lchild = DeleteBST(root->lchild, data); // 递归，从左子树中删除
    }

    else if(data > root->data){
        root->rchild = DeleteBST(root->rchild, data); // 递归，从右子树中删除
    }

    return root;
}


int main()
{
    BinarySortTree tree;
    tree.root = NULL;
    tree.root = Insert(tree.root, 45);
    tree.root = Insert(tree.root, 24);
    tree.root = Insert(tree.root, 53);
    tree.root = Insert(tree.root, 12);
    tree.root = Insert(tree.root, 24);
    tree.root = Insert(tree.root, 90);
    tree.root = Insert(tree.root, 90);
    tree.root = Insert(tree.root, 25);


    Display(tree.root);

    tree.root = DeleteBST(tree.root, 24);

    printf("\nafter delete 24: ");
    Display(tree.root); 

    return 0;
}
