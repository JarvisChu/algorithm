/*
 *  各种查找算法
 * 
 *  静态查找表：Static Search Table, 只query，无增删
 *  动态查找表：Dynamic Search Table, 会有增删
 * 
 *  查找的性能分析
 *  平均查找长度（Average Search Length）, 
 * 
 *  ASL = Sum ( Pi * Ci ); i = [1, n];    Pi 表示第i元素被查找的概率， Ci 表示第i元素查找到时要进行的比较的次数
 *  如果所有元素的P相同，顺序查找，则 ASL = Sum(n-i+1) / n = (n+1)/2 ; i = [1, n];
 *  即 等概率的顺序查找, 查找成功时的 ASL = (n+1)/2 
 *  顺序查找，查找失败时的 ASL = n 
 * 
 *  有序表的查找
 *  1) 二分查找, Binary Search, ASL 约等于 log(n+1) - 1
 *  
 *  静态查找树
 *  每个元素的查找概率不同
 * 
 *  1）次优查找树的构造算法
 *  元素 e0 ... e(n-1)，对应的概率依次是 p0 ... p(n-1)。 构造方法如下
 *  1，选出一个 i， 使得 | Sum(p[0,i)) - Sum( p[i+1, n) ) | 最小。即左右两边的概率累计和 相差的最小
 *  2. i 作为root, 再分别对 e[0,i) 和  e[i+1, i) 做1相同的处理
 * 
 *  其中，概率的累积和 可以事先全部算出来。Si = S(i-1) + pi 
 *  
 * 
 */

#include <stdio.h>
#include <stdlib.h>


#define MAX_ARRAY_SIZE 100
#define N 8
typedef int ElemType;                                   //元素类型
 
// 静态查找表的顺序存储结构
typedef struct{
    ElemType elem[MAX_ARRAY_SIZE];
    int length;
}SSTable;

// 初始化静态查找表 - 已从小到大排好序
void InitOrderedSSTable(SSTable* pSSTable){
    pSSTable->length = N; //实际的元素个数
    for(int i = 0; i < N; i++ ){
        pSSTable->elem[i] = i;//
    }
}

///////////////////////////////////////////////////////////////
// BinarySearch 二分查找
// 返回值：e的位置，-1 表示没有找到
int BinarySearch(SSTable t, ElemType e){
    int low = 0;
    int high = t.length-1;

    while(low <= high){
        int mid = (low + high) / 2;
        if(t.elem[mid] == e) {
            return mid;
        }

        if(t.elem[mid] > e){
            high = mid -1;
        }else{
            low = mid + 1;
        }
    }

    return -1;
}

///////////////////////////////////////////////////////////////
// Nearly Optimal Search Tree 次优查找树

typedef struct NearOptimalSearchNode{
    int data;          // 保存元素的index
    NearOptimalSearchNode* pLChild;
    NearOptimalSearchNode* pRChild;
}NearOptimalSearchNode;

typedef struct NearOptimalSearchTree{
    NearOptimalSearchNode* root;
}NearOptimalSearchTree;

typedef struct{
    char elem[MAX_ARRAY_SIZE];
    float weight[MAX_ARRAY_SIZE];
    int length;
}SSWTable;


float abs(float a){
    if ( a < 0 ) return -a;
    return a;
}

void Display(NearOptimalSearchNode* root){
    if(root == NULL) return;

    printf("%d ", root->data);
    Display(root->pLChild);
    Display(root->pRChild);
}

void NOS(NearOptimalSearchNode* root, float sw[], int low, int high){

    // 寻找使得左右两边 权重累加值 的差值最小的元素min
    float min_d = sw[high] - sw[low]; // 初始化差值 设为最大
    int min = low;                    //

    for(int i=low+1; i<=high; i ++){

        float d = abs( (sw[high] - sw[i]) - ( sw[i-1] - sw[low-1]));
        if (d < min_d){
            min = i;
            min_d = d;
        }
    } 

    // 以 min 为root
    root->data = min;
    root->pLChild = NULL;
    root->pRChild = NULL;

    // 分别对左右两段 递归构造

    if( low < min){
        root->pLChild = (NearOptimalSearchNode*) malloc(sizeof(NearOptimalSearchNode));
        NOS(root->pLChild, sw, low, min-1);
    }

    if(high > min){
        root->pRChild = (NearOptimalSearchNode*) malloc(sizeof(NearOptimalSearchNode));
        NOS(root->pRChild, sw, min+1, high);
    }
}

// 构造次优查找树
NearOptimalSearchTree* CreateNearlyOptimalSearchTree(SSWTable table){

    // 计算权重累加值
    float sw[MAX_ARRAY_SIZE] = {0};
    for(int i = 0; i < table.length; i++){
        if(i == 0) sw[i] = table.weight[i];
        else sw[i] = sw[i-1] + table.weight[i];
    }

    // 递归构造次优二叉树
    NearOptimalSearchTree* tree = (NearOptimalSearchTree*) malloc(sizeof(NearOptimalSearchTree));
    tree->root = (NearOptimalSearchNode*) malloc(sizeof(NearOptimalSearchNode));
    NOS(tree->root, sw, 0, table.length-1);

    return tree;
}

int NearlyOptimalSearch(SSWTable table, char data, NearOptimalSearchNode* root){
    if(root == NULL) return -1;

    if( table.elem[ root->data  ] == data ){
        return root->data;
    }

    int ret = NearlyOptimalSearch(table, data, root->pLChild);
    if (ret >= 0) return ret;

    return NearlyOptimalSearch(table, data, root->pRChild);
}




int main()
{

/*    SSTable table;
    InitOrderedSSTable(&table);
    printf("%d\n", BinarySearch(table, 3));
    printf("%d\n", BinarySearch(table, 4));
*/
    SSWTable wt;
    float w[9] = {1,1,2,5,3,4,4,3,5};
    char e[9] = {'A','B','C','D','E','F','G','H','I'};
    for(int i = 0; i < 9; i++ ) {
        wt.elem[i] = e[i];
        wt.weight[i] = w[i];
    }
    wt.length = 9;
    
    // 构造次优查找树
    NearOptimalSearchTree* tree = CreateNearlyOptimalSearchTree(wt);
    Display(tree->root);

    // 通过次优查找树，进行查找
    printf("\n%d\n", NearlyOptimalSearch(wt, 'A', tree->root));
    printf("%d\n", NearlyOptimalSearch(wt, 'C', tree->root));
    printf("%d\n", NearlyOptimalSearch(wt, 'I', tree->root));

    return 0;
}
