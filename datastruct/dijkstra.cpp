/*
 *  展示dijkstra算法，求单源最短路径
 * 
 *  dijkstra 算法的时间复杂度是 O(n^2) 
 *  - 遍历n顶点，每次选择一个顶点。 第一个 n
 *  - 遍历dist，第二个 n
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

// Dijkstra 算法
void Dijkstra(int v){  // v 是源点
    
    //1. 初始化，
    for(int i=0;i<N;i++){
        dist[i] = graph.weight[v][i]; //  v 到其它顶点的距离就是 weigth[v][i]
        in[v] = 0;                    //  所有顶点都不在集合中
    } 

    //2. v 加入到集合
    in[v] = 1;

    for(int i=1;i<N;i++){
        // 遍历，选出当前里v0最近的顶点
        int minIdx = -1;
        int minValue = MAX_VALUE;
        for(int j=0;j<N;j++){
            if(in[j] == 0){
                if(dist[j] < minValue){
                    minIdx = j;
                    minValue = dist[j];
                }
            }

        }

        // 将顶点 minIdx 加入到集合
        in[minIdx] = 1;
        printf("add %d, dist=%d\n", minIdx, minValue);

        // 更新dist
        for(int j=0;j<N;j++){
            if(in[j] == 0){
                if( dist[j] > (dist[minIdx] + graph.weight[minIdx][j]  )) {
                    dist[j] = dist[minIdx] + graph.weight[minIdx][j];
                }
            }
        }

    }

    // 输出结果
    for(int i = 0;i< N;i++){
        printf(" dist[%d] = %d \n", i, dist[i]);
    }
}

int main()
{
    CreateGraph();
    Dijkstra(0);
    return 0;
}
