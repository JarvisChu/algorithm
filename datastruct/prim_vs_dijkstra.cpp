/*
 *  展示prim 和 Dijstra 的异同
 *  
 *  1. 作用不同
 *  Prim 是计算最小生成树的算法，比如为N个村庄修路，怎么修花销最少。
 *  Dijkstra 是计算最短路径的算法，比如从a村庄走到其他任意村庄的距离。
 * 
 *  2. dist 意义不同
 *  Prim     中 dist[i] 表示顶点i 到 集合 的最短距离
 *  Dijkstra 中 dist[i] 表示源点到顶点i的最短距离
 * 
 *  3. 更新不同
 *  Prim     If dist[i] > weight[i][min], 则 dist[i] = weight[i][min]； 即 i 到 顶点min的距离更新，则更新
 *  Dijkstra If dist[j] >  dist[min] + weight[min][j]，则 dist[j] = dist[min] + weight[min][j]；即源点通过min中转到i的距离更近，则更新
 * 
 *  算法的步骤，几乎完全相同 （仅仅有几行代码不同而已）
 *  1. 初始化: 集合为空
 *  2. 加入第一个顶点： Prim 顶点 0, Dijkstra 源点v
 *  3. 初始化 dist
 *  4. N-1 选顶点加入集合
 *     - 选dist最小值 min
 *     - 顶点min加入结合
 *     - 更新dist
 *  5. 输出结果，结束
 */

#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

#define N 6
#define MAX_VALUE 9999

int in[N];          // 顶点是否在 In 集合中
int dist[N];        // 保存源点 到 每个顶点的最短距离


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

    // 初始化: 集合为空
    for(int i=0;i<N;i++) in[i] = 0;

    // 加入第一个顶点： 顶点 0
    in[0] = 1;

    // 初始化 dist
    for(int i = 1; i < N; i++){
        dist[i] = graph.weight[i][0]; // 集合外的顶点到 集合的最短距离就是到 顶点0的距离（因为集合中就一个顶点 0）
    }

    // 循环 N - 1 次，每次选出一个顶点加入到集合
    for(int i = 1; i < N; i ++){

        // 选出集合外，dist最小的顶点min
        int min = -1;
        int minValue = MAX_VALUE;
        for(int j = 0; j < N; j++){
            if(in[j] == 0 && dist[j] < minValue ) {
                min = j;
                minValue = dist[j];
            }
        }

        // 将 min 加入到 集合
        in[min] = 1; 
        printf("step%d: %s -> %s, cost=%d\n", i, graph.vetex[ dist[min] ].c_str(), graph.vetex[min].c_str(), dist[min]);

        // 更新 dist
        for(int j = 0; j < N; j++){
            if(in[j] == 0 && dist[j] > graph.weight[j][min]) { // 如果顶点 j 到 min 的距离更近，则更新
                dist[j] = graph.weight[j][min];
            }
        }
    }

    // 输出结果
    dist[0] = 0;
    int total = 0;
    for(int i=0; i<N; i++){
        total += dist[i];
    }
    printf("Total cost: %d\n", total);
}

void Dijkstra(int v){

    // 初始化: 集合为空
    for(int i=0;i<N;i++) in[i] = 0;

    // 加入第一个顶点： 源点 v
    in[v] = 1;

    // 初始化 dist
    for(int i = 0; i < N; i++){
        dist[i] = graph.weight[v][i]; // 源点到每个顶点的距离，就是 weigth[v][i]
    }

    // 循环 N - 1 次，每次选出一个顶点加入到集合
    for(int i = 1; i < N; i ++){

        // 选出集合外，dist最小的顶点min
        int min = -1;
        int minValue = MAX_VALUE;
        for(int j = 0; j < N; j++){
            if(in[j] == 0 && dist[j] < minValue ) {
                min = j;
                minValue = dist[j];
            }
        }

        // 将 min 加入到 集合
        in[min] = 1; 
        printf("add %d, dist=%d\n", min, minValue);

        // 更新 dist
        for(int j = 0; j < N; j++){
            if(in[j] == 0 && dist[j] > (dist[min] + graph.weight[min][j]) ) { // 如果源点通过min中转到j的距离更近，则更新
                dist[j] = dist[min] + graph.weight[min][j];
            }
        }
    }

    // 输出结果
    for(int i=0; i<N; i++){
        printf(" dist[%d] = %d \n", i, dist[i]);
    }
}

int main()
{
    CreateGraph();
    printf(" ------  Prim     ------\n");
    Prim();
    printf(" ------  Dijkstra ------\n");
    Dijkstra(0);

    return 0;
}
