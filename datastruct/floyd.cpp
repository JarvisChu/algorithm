/*
 *  展示Floyd算法，求任意两点之间的最短距离
 * 
 *  Floyd 算法的核心思想：
 *  e[i][j] 表示顶点到j的最短距离，初始时就是 weight[i][j]
 *  然后依次加入顶点，进行中转，如果中转后更小，则更新
 *  
 *  比如：
 *  加入顶点1，如果e[i][j] > e[i][1] + e[1][j], 则更新 e[i][j] = e[i][1] + e[1][j]，
 *  然后再加入顶点2，同上处理。直到加入了所有的顶点，结束
 * 
 *  Floyd 每次能求出指定的任意两个点的最短路径
 *  Floyd 求所有顶点之间的最短路径，复杂度也是O(n^3)
 *  Floyd 求任意指定两点之间的最短路径，复杂度是 O(n^3), n来自不断把所有顶点当做中转顶点。
 * 
 *  Dijkstra 每次能求出源点v到其它所有顶点的最短距离
 *  Dijkstra 求所有顶点之间的最短路径，则需要对每个顶点做一次Dijkstra，复杂度为O(n^3)
 *  Dijkstra 求任意指定两点之间的最短路径，也需要对起点做一次Dijkstra, 算法复杂度也是 O(n^3)
 * 
 *  附录：参考链接 https://www.cnblogs.com/wangyuliang/p/9216365.html
 */

#include <stdio.h>
#include <stdlib.h>

#define N 6
#define MAX_VALUE 9999

int e[N][N];  //e[i][j] 表示顶点到j的最短距离

// 图
typedef struct Graph {
    int weight[N][N]; // 保存邻接矩阵信息
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

// 计算所有顶点之间的最短路径
void Floyd(){

    // 初始化
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            e[i][j] = graph.weight[i][j];
        }
    }

    // 依次加入顶点
    for(int v=0; v<N;v++){

        // 重新计算任意两点之间的最小距离
       for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                // if(i != j)  //过滤掉自身到自身的距离
                if(e[i][j] > e[i][v] + e[v][j]){ // 判断通过v中转是否更近
                    e[i][j] = e[i][v] + e[v][j];
                }
            }
       }
    }

    // 输出结果
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            printf("%d -> %d = %d\n", i,j,e[i][j]);
        }
    }
}

// 计算顶点from 到 顶点to 之间的最短路径
void Floyd(int from, int to){
    Floyd();
    printf("from:%d -> to:%d = %d\n",from, to, e[from][to]);
}

int main()
{
    CreateGraph();
    Floyd();

    printf("-------\n");
    Floyd(0,4);


    return 0;
}
