/*
 *  Huffman Tree 的构造和 Huffman 编码的生成
 */

#include <stdio.h>
#include <stdlib.h>
#include <stack>

using namespace std;


typedef char TElemType;

typedef struct Node{
    TElemType e;
    int weigth;
    int lchild, rchild, parent;  // 初始化为 -1
}Node;

typedef struct HuffmanTree{
    Node* root;
}HuffmanTree;

typedef struct Data {
    TElemType e;
    int weigth;
}Data;


// 生成Huffman Tree, 并且得到 Huffman Code
void CreateHuffmanTree(HuffmanTree* tree, Data data[], int cnt){
    if (tree == NULL || data == NULL || cnt == 0) return;

    // 构建huffman tree
    Node* huffmanNodes = (Node*)malloc( (2 * cnt - 1) * sizeof(Node));
    for(int i = 0; i< cnt; i++ ){
        huffmanNodes[i].e = data[i].e;
        huffmanNodes[i].weigth = data[i].weigth;
        huffmanNodes[i].lchild = huffmanNodes[i].rchild = huffmanNodes[i].parent = -1;
    }
    for (int i = cnt; i < (2*cnt -1); i ++ ){
        huffmanNodes[i].weigth = -1;
        huffmanNodes[i].lchild = huffmanNodes[i].rchild = huffmanNodes[i].parent = -1;
    }

    int index = cnt;
    while(true){

        int min = -1, subMin = -1; // 找出两个最新的权值
        for(int i = 0; i < (2 * cnt - 1) ; i++){
            if (huffmanNodes[i].weigth == -1) continue;

            if(min == -1){
                min = i;
                continue;
            }

            if (subMin == -1){
                if(huffmanNodes[i].weigth >huffmanNodes[min].weigth ) subMin = i;
                else{ subMin = min; min = i;}
                continue;
            }

            if(huffmanNodes[i].weigth < huffmanNodes[min].weigth){
                subMin = min;
                min = i;  
            }else if( huffmanNodes[i].weigth < huffmanNodes[subMin].weigth ){
                subMin = i;
            } 
        }

        // 如果找不到两个最小值，说明已经生成完毕，跳出循环
        if (min == -1 || subMin == -1) {
            break;
        }

        // 合并两个最小的值
        huffmanNodes[index].weigth = huffmanNodes[min].weigth + huffmanNodes[subMin].weigth;
        huffmanNodes[index].lchild = min;
        huffmanNodes[index].rchild = subMin;
        printf("merge [%d,%c,%d] and [%d,%c,%d] into [%d,%c,%d] \n", min, huffmanNodes[min].e, huffmanNodes[min].weigth,
                                                            subMin, huffmanNodes[subMin].e, huffmanNodes[subMin].weigth,
                                                               index, huffmanNodes[index].e, huffmanNodes[index].weigth
        );
        huffmanNodes[min].weigth = huffmanNodes[subMin].weigth = -1;
        huffmanNodes[min].parent = huffmanNodes[subMin].parent = index;


        index ++;
    }

    // 构建 huffman 编码
    // 从叶子往根节点回溯，

    for (int i = 0;i < cnt; i++){
        std::stack<int> stk;

        int cur = i;
        while(true ){
            int parent = huffmanNodes[cur].parent;
            if(parent == -1 ){
                break;
            }

            if (huffmanNodes[parent].lchild == cur){
                stk.push(0);
            }else{
                stk.push(1);
            }

            cur = parent;
        }

        printf("%c: ", huffmanNodes[i].e);
        while(!stk.empty()){
            printf("%d",stk.top());
            stk.pop();
        }
        printf("\n");
    }

    return;
}




int main()
{

    Data data[8];
    data[0].e = 'A';
    data[0].weigth = 5;
    data[1].e = 'B';
    data[1].weigth = 30;
    data[2].e = 'C';
    data[2].weigth = 7;
    data[3].e = 'D';
    data[3].weigth = 8;
    data[4].e = 'E';
    data[4].weigth = 14;
    data[5].e = 'F';
    data[5].weigth = 22;
    data[6].e = 'G';
    data[6].weigth = 3;
    data[7].e = 'H';
    data[7].weigth = 11;

    HuffmanTree tree;
    CreateHuffmanTree(&tree, data, 8);

    return 0;
}
