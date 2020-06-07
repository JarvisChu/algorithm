/*
 *  展示拓扑排序算法
 *  > https://www.cnblogs.com/en-heng/p/5085690.html
 *  
 *  有向无环图，按照顶点出现的前后顺序排序。即如果存在边（u,v）, 则排序时，u一定要在v前面
 *  
 *  算法： 两种方式，indegree 和  dfs
 * 
 *  (1) indegree 
 *      找到入度为0的顶点，从图中删除，同时删除其出边。如此，每次找入度为0的顶点，同上操作
 *      > 动画 https://www.cs.usfca.edu/~galles/visualization/TopoSortIndegree.html
 *  (2) DFS
 *      深度优先遍历，最先返回的顶点，即出度为0的顶点，也就是拓扑排序的最后一个顶点。 按照退栈的顺序，就是拓扑排序的逆序。
 *      > 动画 https://www.cs.usfca.edu/~galles/visualization/TopoSortDFS.html
 *  
 */

#include <stdio.h>
#include <stdlib.h>
#include <stack>

using namespace std;

#define N 6

// 有向无环图
typedef struct DAG {
    int weight[N][N]; // 保存邻接矩阵信息，1表示有边，0表示无边
}DAG;

DAG graph;

/*

  A  ---> B ---> C  ---> E       F
  |               |
  |               |
  |  --->  D  <---

  顶点序号：A=0，B=1，C=2. D=3，E=4，F=5
*/



// 初始化
void CreateGraph(){

    for(int i=0;i<N;i++) {
        for(int j=0; j <N; j++){
            graph.weight[i][j] = 0; // 0 表示无边
        }
    }

    graph.weight[0][1] = 1; // 1 表示有边
    graph.weight[0][3] = 1;
    graph.weight[1][2] = 1;
    graph.weight[2][3] = 1;
    graph.weight[2][4] = 1;
}

//-----------------------------------------------------------------------------
// TopoSort - Indegree

int indegree[N];              // 保存所有顶点的入度
std::stack<int> zeroIndegree; // 保存所有入度为0 的顶点序号。 其实可以每次都遍历indegree来得到，但为了更高效，直接栈保存
void TopoSort_Indegree(){

    // 初始化所有顶点的入度
    for(int i=0; i<N; i++) indegree[i] = 0;

    // 遍历，确定所有顶点的入度
    for(int i=0; i<N; i++){
        for(int j=0;j<N; j++){
            if( graph.weight[i][j] == 1 ){
                indegree[j] ++;
            }
        }
    }

    // 入度为0的顶点加入栈
    for(int i=0; i<N; i++) {
        //printf("%d\n", indegree[i]);
        if (indegree[i] == 0) {
            zeroIndegree.push(i);
        }
    }

    // 不断删除入度为0的顶点，更新它指向的所有顶点的入度
    while( ! zeroIndegree.empty() ){

        int v = zeroIndegree.top();
        zeroIndegree.pop();
        printf("%d ", v);

        for(int i=0;i<N;i++){
            if( graph.weight[v][i] == 1){  // 存在边 (v, i)，则减少i的入度
                indegree[i] --;
                if(indegree[i] == 0) zeroIndegree.push(i);
            }
        }
    }
    
}

//-----------------------------------------------------------------------------
// TopoSort - DFS

std::stack<int> vetexs;    // 退栈时保存顶点，最后依次pop输出，即拓扑排序
void DFS(int* visited, int idx){
    if(visited[idx] == 1) return;

    for(int i=0;i<N;i++){ // 这里如果使用邻接表，更高效，不用遍历图，直接使用当前顶点的弧即可
        if(graph.weight[idx][i] == 1 ){
            DFS(visited, i);
        }
    }

    vetexs.push(idx);
    visited[idx] = 1;
    return;
}

void TopoSort_DFS(){
    int visited[N] = {0};

    for(int i=0;i<N;i++){
        DFS(visited, i);
    }

    while(!vetexs.empty()){
        int v = vetexs.top();
        vetexs.pop();
        printf("%d ", v);
    }
}

int main()
{
    CreateGraph();
    TopoSort_Indegree();
    printf("\n --- \n");
    TopoSort_DFS();
    return 0;
}
