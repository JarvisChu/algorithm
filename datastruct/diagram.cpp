/*****************************************************************
 *功  能：利用邻接表存储图，实现其递归与非递归的深度遍历和广度遍历
 *作  者：JarvisChu
 *时  间：2011-04-30
 *****************************************************************/
#include <iostream>
#include <string>
#include <stack>
#include <queue>

using namespace std;

//#define _RECURSION_TRAVERSE    //递归遍历(将下一行注释，此行不注释)
#define _NON_RECURSION_TRAVERSE  //非递归遍历(节点本身有isVisited域)(将上一行注释，此行不注释)

#define MAX_VERTEX_NUM 20        //最大顶点数


/*弧节点的结构，即每个顶点后面的单链表中的节点结构*/
typedef struct ArcNode{
    int adjvex;               //该弧所指向的顶点的位置
    struct ArcNode* nextArc;  //下一条弧
    string info;              //该弧所携带的信息
}ArcNode;

#ifdef  _NON_RECURSION_TRAVERSE
/*每个顶点的节点结构,非递归时使用*/
typedef struct VNode{
    bool isVisited;
    string data;           //顶点的数据
    ArcNode* fristArc;     //指向该顶点所接的单链表的第一个弧节点
}VNode,AdjList[MAX_VERTEX_NUM];
#endif

#ifdef  _RECURSION_TRAVERSE
/*每个顶点的节点结构，递归时使用*/
typedef struct VNode{
    string data;                  //顶点的数据
    ArcNode* fristArc;            //指向该顶点所接的单链表的第一个弧节点
}VNode,AdjList[MAX_VERTEX_NUM];
#endif

/*图的结构*/
typedef struct{
    AdjList vertices;           //顶点数组
    int vexNum;                 //顶点数
    int arcNum;                 //弧数
    int kind;                   //种类
}Graph;

/*初始化有向图*/
bool InitDiGraph(Graph* pGraph){
    pGraph->kind = 0;                    //有向图
    pGraph->vexNum = 5;
    pGraph->arcNum = 5;

    pGraph->vertices[0].data = "V0";     //顶点V0的邻接表
#ifdef _NON_RECURSION_TRAVERSE
    pGraph->vertices[0].isVisited = false;
#endif
    ArcNode* node = new ArcNode();
    node->adjvex = 1;
    node->info = "V0-->V1";
    node->nextArc = NULL;
    ArcNode* node1 = new ArcNode();
    node1->adjvex = 2;
    node1->info = "V0-->V2";
    node1->nextArc = NULL;
    node->nextArc = node1;
    pGraph->vertices[0].fristArc = node;

    pGraph->vertices[1].data = "V1";          //顶点V1的邻接表
 #ifdef _NON_RECURSION_TRAVERSE
    pGraph->vertices[1].isVisited = false;
 #endif
    pGraph->vertices[1].fristArc = NULL;

    pGraph->vertices[2].data = "V2";          //顶点V2的邻接表
#ifdef _NON_RECURSION_TRAVERSE
    pGraph->vertices[2].isVisited = false;
 #endif
    node = new ArcNode();
    node->adjvex = 3;
    node->info = "V2-->V3";
    node->nextArc = NULL;
    pGraph->vertices[2].fristArc = node;

    pGraph->vertices[3].data = "V3";         //顶点V3的邻接表
 #ifdef _NON_RECURSION_TRAVERSE
    pGraph->vertices[3].isVisited = false;
 #endif
    node = new ArcNode();
    node->adjvex = 0;
    node->info = "V3-->V0";
    node->nextArc = NULL;
    node1 = new ArcNode();
    node1->adjvex = 4;
    node1->info = "V3-->V4";
    node1->nextArc = NULL;
    node->nextArc = node1;
    pGraph->vertices[3].fristArc = node;

    pGraph->vertices[4].data = "V4";         //顶点V4的邻接表
 #ifdef _NON_RECURSION_TRAVERSE
    pGraph->vertices[4].isVisited = false;
 #endif
    pGraph->vertices[4].fristArc = NULL;

    return true;
}

/*显示有向图*/
bool DisplayDiGraph(Graph diGraph){
    cout<<"*******************图信息********************"<<endl;
    cout<<"图种类为："<<diGraph.kind<<endl;
    cout<<"顶点数为："<<diGraph.vexNum<<endl;
    cout<<"弧数为："<<diGraph.arcNum<<endl<<endl;
    cout<<"邻接表结构如下"<<endl;
    ArcNode* node = NULL;
    for(int i=0;i<diGraph.vexNum;i++){
        cout<<diGraph.vertices[i].data<<":";
        node = diGraph.vertices[i].fristArc;
        while(node != NULL){
            cout<<"("<<node->adjvex<<","<<node->info<<") ; ";
            node = node->nextArc;
        }
        cout<<endl;
    }
    return true;
}

#ifdef _NON_RECURSION_TRAVERSE
/*深度优先非递归遍历有向图,利用栈*/
bool Depth_First_Traverse(Graph* pDiGraph){
    for(int i=0;i<pDiGraph->vexNum;i++){                  //初始化，全为false
        pDiGraph->vertices[i].isVisited = false;
    }
    VNode* vnode;
    stack<VNode*> TraverseStack;                         //用stack实现非递归遍历算法
    TraverseStack.push(&(pDiGraph->vertices[0]));        //第一个节点入栈

    while(!TraverseStack.empty()){
        vnode = (VNode*)TraverseStack.top();              //获得栈顶节点
        vnode->isVisited = true;
        cout<<"遍历："<<vnode->data<<endl;
        TraverseStack.pop();
        ArcNode* node = vnode->fristArc;
        while(node != NULL){
            if(!(pDiGraph->vertices[node->adjvex]).isVisited){
                TraverseStack.push(&(pDiGraph->vertices[node->adjvex]));  //入栈
            }
            node = node->nextArc;
        }
    }
    return true;
}
#endif

#ifdef _RECURSION_TRAVERSE
/*深度优先递归遍历时，用来遍历每一个顶点*/
bool DFT(Graph* pDiGraph,bool* visited,int i){
    if(!visited[i]){
        visited[i] = true;                                //标志该顶点已被访问了
        cout<<"遍历："<<pDiGraph->vertices[i].data<<endl;
        ArcNode* node = pDiGraph->vertices[i].fristArc;   //遍历其临街单链表
        while(node != NULL){
            DFT(pDiGraph,visited,node->adjvex);
            node = node->nextArc;
        }
    }
    return true;
}

/*深度优先递归遍历有向图*/
bool Depth_First_Traverse(Graph* pDiGraph){
    int size = pDiGraph->vexNum;                          //顶点数目
    bool* visited = new bool[size];                       //访问标志数组
    for(int i = 0;i < size;i++){                          //初始化，全为false
        visited[i] = false;
    }
    for(int i = 0;i<size;i++){                            //
            DFT(pDiGraph,visited,i);
    }
    delete[] visited;
    return true;
}
#endif

#ifdef _NON_RECURSION_TRAVERSE
/*广度优先非递归遍历有向图，利用队列*/
bool Breadth_First_Traverse(Graph* pDiGraph){
    for(int i=0;i<pDiGraph->vexNum;i++){                  //初始化，全为false
        pDiGraph->vertices[i].isVisited = false;
    }
    VNode* vnode;
    queue<VNode*> TraverseQueue;                          //用queue实现非递归遍历算法
    TraverseQueue.push(&(pDiGraph->vertices[0]));         //第一个节点入队

    while(!TraverseQueue.empty()){
        vnode = (VNode*)TraverseQueue.front();            //获得队首节点
        vnode->isVisited = true;
        cout<<"遍历："<<vnode->data<<endl;
        TraverseQueue.pop();
        ArcNode* node = vnode->fristArc;
        while(node != NULL){
            if(!(pDiGraph->vertices[node->adjvex]).isVisited){
                TraverseQueue.push(&(pDiGraph->vertices[node->adjvex]));   //入队
            }
            node = node->nextArc;
        }
    }
    return true;
}
#endif

#ifdef _RECURSION_TRAVERSE
/*广度优先递归遍历时，用来遍历每一个顶点*/
bool BFT(Graph* pDiGraph,bool* visited,int i){
    if(!visited[i]){
        visited[i] = true;                               //标志该顶点已被访问了
        cout<<"遍历："<<pDiGraph->vertices[i].data<<endl;
        ArcNode* node = pDiGraph->vertices[i].fristArc;  //遍历其临街单链表
        while(node != NULL){
            if(!pDiGraph->vertices[node->adjvex].isVisited){
                pDiGraph->vertices[node->adjvex].isVisited = true;
                cout<<"遍历："<<pDiGraph->vertices[node->adjvex].data<<endl;
            }
            node = node->nextArc;
 //       BFT(pDiGraph,visited,node->adjvex);
        }
        BFT(pDiGraph,visited,node->adjvex);
    }
    return true;
}
/*广度优先递归遍历有向图*/
bool Breadth_First_Traverse(Graph* pDiGraph){
    int size = pDiGraph->vexNum;                      //顶点数目
    bool* visited = new bool[size];                   //访问标志数组
    for(int i = 0;i < size;i++){                      //初始化，全为false
        visited[i] = false;
    }
    for(int i = 0;i<size;i++){                        //
            BFT(pDiGraph,visited,i);
    }
    delete[] visited;
}
#endif



int main()
{
    Graph diGraph;                //有向图
    Graph udiGraph;               //无向图

    InitDiGraph(&diGraph);        //初始化有向图，构建

    DisplayDiGraph(diGraph);      //显示该有向图

    cout<<endl<<"***************深度优先遍历结果***********"<<endl;
    Depth_First_Traverse(&diGraph);                               //深度优先遍历

    cout<<endl<<"***************广度优先遍历结果***********"<<endl;
    Breadth_First_Traverse(&diGraph);                             //广度优先遍历


    return 0;
}
