/*
 *  展示prim算法，求最小生成树
 * 
 *  Prim 算法是通过选择 顶点 的方式来找到最小生成树，适合求 边稠密的图 的最小生成树
 *  Prim 算法的时间复杂度是 O(n^2) ，
 *    - 每次选一个顶点，共 N 个顶点，这里是 第一个 n
 *    - 选择每个顶点时，需要遍历 顶点的最小距离， 这里是 第二个 n
 * 
 *  图：采用邻接矩阵存储
 *  两个顶点集合：In 和 Out，
 *    In 保存所有当前已经加入到最小生成树的结点
 *    Out 保存所有当前还没有加入到最小生成树的结点
 *  求最小生成树的过程，就是不断从 Out 集合中选出到 In 距离最近的顶点，加入In
 *  
 *  算法步骤：
 *  1. 初始化: In为空，所有顶点都在Out中，然后将 任意某个顶点 v 加入到 In
 *  2. 更新Out中所有顶点信息，对于顶点 i:
 *     其距离 In 中最近的顶点 closest[i] = v，
 *     其距离值 cost[i] = weigth[x][v]
 *  3. 循环 N - 1 次，每次选出一个Out的顶点加入到 In， 步骤如下：
 *     3.1. 遍历 Out， 选出 cost 最新的顶点 min 
 *     3.2. 将 min 加入到 In 中
 *     3.3. 更新Out中所有顶点的信息，如果顶点 i 到 min 的距离更近，即 cost[i] > weigth[i][min]，则
 *          closest[i] = min
 *          cost[i] = weigth[i][min]
 *  4. 结束
 *  
 */

#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

#define N 6
#define MAX_VALUE 9999

int cost[N];        //
int closest[N];     //
int in[N];          // 顶点是否在 In 集合中


// 图
typedef struct Graph {
    int weight[N][N]; // 保存邻接矩阵信息
    string vetex[N];  // 保存顶点名称
}Graph;

Graph graph;

/*
          V0
      /   |    \       6  1  5        无向图，数字为每条边上的权重，即距离。
   V1  -  V2  -  V3     5   5
    \   /    \   /    3  6  4  2
     V4   -    V5         6

*/

// 初始化
void CreateGraph(){
    graph.vetex[0] = "V0";
    graph.vetex[1] = "V1";
    graph.vetex[2] = "V2";
    graph.vetex[3] = "V3";
    graph.vetex[4] = "V4";
    graph.vetex[5] = "V5";

    for(int i=0;i<N;i++) {
        for(int j=0; j <N; j++){
            graph.weight[i][j] = MAX_VALUE; // MAX_VALUE 表示不可达
        }
    }

    graph.weight[0][1] = 6;
    graph.weight[0][2] = 1;
    graph.weight[0][3] = 5;

    graph.weight[1][0] = 6;
    graph.weight[1][2] = 5;
    graph.weight[1][4] = 3;

    graph.weight[2][0] = 1;
    graph.weight[2][1] = 5;
    graph.weight[2][3] = 5;
    graph.weight[2][4] = 6;
    graph.weight[2][5] = 4;
    graph.weight[2][3] = 5;

    graph.weight[3][0] = 5;
    graph.weight[3][2] = 5;
    graph.weight[3][5] = 2;

    graph.weight[4][1] = 3;
    graph.weight[4][2] = 6;
    graph.weight[4][5] = 6;

    graph.weight[5][2] = 4;
    graph.weight[5][3] = 2;
    graph.weight[5][4] = 6;
}

// Prim 算法
void Prim(){

    // 1. 初始化: In为空，所有顶点都在Out中，然后将 任意某个顶点 v 加入到 In
    for(int i=0;i<N;i++) in[i] = 0; //
    in[0] = 1;                      // 将顶点 0 加入到 In

    // 2. 更新Out中所有顶点信息
    for(int i = 1; i < N; i++){
        closest[i] = 0;               // 距离 0 最近
        cost[i] = graph.weight[i][0]; // 
    }

    // 3. 循环 N - 1 次，每次选出一个Out的顶点加入到 In
    for(int i = 1; i < N; i ++){

        // 3.1. 遍历 Out， 选出 cost 最新的顶点 min
        int min = -1;
        for(int j = 0; j < N; j++){
            if(in[j] == 0 && (min == -1 || cost[j] <= cost[min] )) {
                min = j;
            }
        }

        // 3.2. 将 min 加入到 In 中
        in[min] = 1; 
        printf("step%d: %s -> %s, cost=%d\n", i, graph.vetex[ closest[min] ].c_str(), graph.vetex[min].c_str(), cost[min]);

        // 3.3. 更新Out中所有顶点的信息
        for(int j = 0; j < N; j++){
            if(in[j] == 0 && cost[j] > graph.weight[j][min]) { // 如果顶点 j 到 min 的距离更近，则更新
                cost[j] = graph.weight[j][min];
                closest[j] = min;
            }
        }
    }

    // 输出最终的总距离（权重）
    cost[0] = 0;
    int total = 0;
    for(int i=0; i<N; i++){
        total += cost[i];
    }
    printf("Total cost: %d\n", total);
}

int main()
{
    CreateGraph();
    Prim();
    return 0;
}
