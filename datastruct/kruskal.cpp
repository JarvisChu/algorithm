/*
 *  展示kruskal算法，求最小生成树
 *  时间复杂度是 O(eloge)  e 是图的边数量，所以适合求 边稀疏的图 的最小生成树
 * 
 *  不断选择 权重最小 且能连接两个不同连通分量 的边，将其加入到最小生成树中
 *  
 * 
 *  算法步骤：
 *  1. 初始化:
 *     1.1 将所有的边，放到Edges中待选，并且按照weigth值排序，同时属性in设为false，表示还不在最小生成树中
 *     1.2 初始化所有顶点都在 各自的连通分量中
 *  2. 不断选边，直到所有顶点都在一个连通分量中
 *     2.1 选择一个weigth值最小的边，其不在最小生成树中，且 边的两个顶点 在两个不同连通分量中
 *     2.2 将该边的 in 设置为 true，加入到最小生成树中
 *     2.3 更新这个边 连接起来的两个联通分量，将其合并成一个连通分量
 *     2.4 如果当前连通分量的个数 == 1， 结束
 *  3. 结束
 *  
 */

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

#define N 6

// 边
typedef struct Edge{
    int from;    // 起始的顶点
    int to;      // 结束的顶点
    int weight;  // 权重
    bool in;     // 是否已经加入到最小生成树中
}Edge;

std::vector<Edge> Edges; // 还未加入到最小生成树的所有边
int cc[N];               // 保存每个顶点 的连通分量编号，初始时每个顶点的连通分量编号和顶点编号相同。cc=ConnectedComponent=连通分量
int ccCnt;               // 保存当前连通分量的个数。（其实可以直接遍历 cc 来获取，但是为了更高效，直接使用一个ccCnt 来记录）


// 图
/*
          V0
      /   |    \       6  1  5        无向图，数字为每条边上的权重，即距离。
   V1  -  V2  -  V3     5   5
    \   /    \   /    3  6  4  2
     V4   -    V5         6

*/


void PutEdge(int from, int to, int weight){
    Edge e;
    e.from = from;
    e.to = to;
    e.weight=weight;
    e.in = false;
    Edges.push_back(e);
}

// 按 权重 递增排序
void InitEdges(){
    PutEdge(0,2,1);
    PutEdge(3,5,2);
    PutEdge(1,4,3);
    PutEdge(2,5,4);
    PutEdge(2,3,5);
    PutEdge(0,3,5);
    PutEdge(1,2,5);
    PutEdge(2,4,6);
    PutEdge(4,5,6);
    PutEdge(0,1,6);
}

// Kruskal 算法
void Kruskal(){

    // 1. 初始化
    // 1.1 将所有的边，放到Edges中待选，并且按照weigth值排序
    InitEdges();
    // 1.2 将所有的顶点，分别放到一个连通分量中
    for(int i=0;i<N;i++){
        cc[i] = i;         // 顶点i 放到 连通分量 i 中
    }
    ccCnt = N;

    int totalWeight = 0;

    // 2. 开始选边
    for(int i = 0; i < Edges.size(); i++) {
        // 判断 LeftEdges[i].from 和 LeftEdges[i].to 是否在同一个连通分量中
        // 如果 在同一个连通分量中，则跳过，否则选中

        if( Edges[i].in == false && cc[ Edges[i].from ] != cc[ Edges[i].to ] ) {
            //选中
            printf("Select Edge : %d -> %d weight=%d\n", Edges[i].from, Edges[i].to, Edges[i].weight);    
            Edges[i].in = true;   // 边加入到 最小生成树
            for(int v=0;v<N;v++){ // 合并连通分量
                if(cc[v] == cc[ Edges[i].to ]){
                    cc[v] = cc[ Edges[i].from ];
                }
            }
            ccCnt --;

            totalWeight += Edges[i].weight;
            if (ccCnt == 1) break;  // 所有的顶点 已经合并到一个连通分量中，停止选边        
        }
    }

    // 输出最终的总距离（权重）
    printf("Total cost: %d\n", totalWeight);
}

int main()
{
    Kruskal();
    return 0;
}
