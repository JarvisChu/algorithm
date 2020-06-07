/*
 *  插入排序
 *  - 直接插入排序
 *  - 折半插入排序
 *  - 2-路插入排序
 *  - 表插入排序
 * 
 *  选择排序
 *  - 简单选择排序
 *  - 堆排序
 * 
 *  交换排序
 *  - 冒泡排序
 *  - 快速排序
 *  
 *  归并排序
 *  - 二路归并
 *  - 多路归并
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N 100

void Swap(int& a, int& b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

void RandomArray(int Array[], int size)
{
    srand(time(NULL));

    for(int i=0;i<size;i++){
        Array[i] = (rand() % 100) + 1;
    } 

    return;
}

void PrintArray(int Array[], int size) 
{
    printf("Array: ");
    for(int i=0;i<size;i++){
        printf("%-4d", Array[i]);
    }
    printf("\n");
}

// 直插 （从小到大）
void InsertSort(int Array[], int size)
{
    // 从第二个元素开始，即 Array[1] 开始，往前插入
    for(int i = 1; i < size; i++){

        int elem = Array[i];

        // 从前一个位置开始，凡是大于当前值的，都往后移一位
        int j = i-1;    
        while(Array[j] > elem && j >= 0){
            Array[j+1] = Array[j];
            j--;
        }

        // 移动结束，j是不能移动的，j+1是空出来的， 所以 j+1 就是elem的位置
        Array[j+1] = elem;
    }
}


// 折半插入 （从小到大）
void BinarySort(int Array[], int size)
{
    // 从第二个元素开始，即 Array[1] 开始，往前折半插入
    for (int i = 1; i < size; i++){
        int elem = Array[i];
        int low = 0;
        int high = i -1;

        while(low <= high) {
            int mid = (low + high) / 2;
            if( Array[mid] > elem ) high = mid - 1;
            else low = mid + 1;
        }

        // high+1 就是应该插入的位置
        for(int j=i-1; j>= high+1; j--){
            Array[j+1] = Array[j];
        }

        Array[high + 1] = elem;
    }
}

// 二路插入 （从小到大）
// 本质就是一个循环队列，具体原理如下
// 1. 分配一个和原数组相同大小的新数组，
// 2. 初始时：赋值原数组第0个元素到新数组，然后 head 和 tail 都指向第0个元素
//    新数组始终是有序的，head指向当前最小，tail指向当前最大
// 3. 从第 1 个元素 往后遍历原数组，将每个元素插入到新数组，插入方法如下：
//   - 如果比head小，放到head前面，head--
//   - 如果比tail大，放到tail后面，tail++
//   - 中间值，则通过直插算法，插入到 head 和 tail 之间
// 循环队列的操作和普通队列基本一致，就是每次 + - 时，要 (+ size) % size
void TwoWaySort(int Array[], int size)
{
    int tmp[N] = {0};  // head -> tail 依次增大
    int head = 0;
    int tail = 0;
    tmp[0] = Array[0];

    for(int i = 1; i < size; i++){

        // 比 tmp中最大的元素都大，直接放到tail+1位置
        if(Array[i] >= tmp[tail]){
            tail = (tail + 1 + size) % size;
            tmp[tail] = Array[i];
        }

        // 比 tmp中最小的元素都小，直接放到tail+1位置
        else if(Array[i] < tmp[head]){
            head = (head - 1 + size) % size;
            tmp[head] = Array[i];
        }

        // 中间位置
        else{
            // 从 tail 开始，往前直插即可
            int j = (tail + 1 + size) % size; // tail + 1 是空的，依次往后移

            while(tmp[ ((j-1) + size) % size ] > Array[i]){
                // j <- j-1
                tmp[j] = tmp[ (j-1 + size) % size ];
                j = (j - 1 + size) % size;
            }

            // j 就是插入位置
            tmp[j] = Array[i];

            tail = (tail + 1 + size) % size;
        }
    }

    // 将tmp复制到Array
    for(int i = 0; i < size; i++){
        Array[i] = tmp[head];
        head = (head + 1 + size) % size;
    }
}

// 简单选择 （从小到大）
void SelectSort(int Array[], int size)
{
    for(int i = 0; i < size; i++){
        // 选择一个最小值，和 i 交换

        int min = i;
        for(int j = i + 1; j < size; j ++){
            if (Array[j] < Array[min]){
                min = j;
            }
        }

        if(min != i){
            Swap(Array[i], Array[min]);
        }
    }
}

// 调整：大顶堆，对顶点v进行调整
void Adjust(int Array[], int size, int v)
{
    if(v < 0) return;

    int left = 2 * v + 1;  // 左孩子
    int right = 2 * v + 2;  // 右孩子

    // 没有孩子
    if( left > size-1 ) return;

    // 只有左孩子
    if( right > size-1 ){
        if(Array[v] >= Array[left] ) return;  // 比左孩子大，无需调整

        Swap(Array[v], Array[left]);// 比左孩子小，交换，继续调整
        Adjust(Array, size, left);
        return;
    }

    // 有两个孩子

    // 选出两个孩子中较大的
    int child = left;
    if (Array[left] < Array[right]){
        child = right;
    }

    // 比左右孩子都大，无需调整
    if( Array[v] > Array[child]) return;

    Swap(Array[v], Array[child]);
    Adjust(Array, size, child);
    return;
}

// 建堆
// 就是从最后一个非叶子结点，往前不断调整的过程
void BuildHeap(int Array[], int size)
{
    for(int i = (size / 2) - 1  ; i>=0; i--){
        Adjust(Array, size, i);
    }
}

// 堆排序
// 每次将堆顶 和 最后一个元素对换，然后对新的堆顶进行筛选。刷选时，换到最后的元素都不参与
void HeapSort(int Array[], int size)
{
    for(int i=size-1; i >= 1; i-- ){
        Swap(Array[i], Array[0]);
        Adjust(Array, i, 0);  // 注意这里是 i，因为挪到后面的元素，不参与调整了
    }
}

//冒泡排序
void BubbleSort(int Array[], int size)
{
    // 冒泡 size 趟
    for(int i=1;i < size; i++) {

        // 每一趟 冒一个最大的到最后
        for(int j=0; j < size-i; j++) {
            if( Array[j] > Array[j+1] ){
                Swap(Array[j], Array[j+1]);
            }
        }
    }
}

int Partition(int Array[], int low, int high)
{
    int pivot = Array[low];

    while(low < high){   // low=high时，就一个元素，不用交换

        // 从high 开始找一个比pivot小的，放到 low
        while(Array[high] >= pivot && low < high) high --;
        Array[low] = Array[high];

        // 从low开始，找一个比pivot大的，放到high
        while(Array[low] <= pivot && low < high) low ++;
        Array[high] = Array[low];
    }

    Array[low] = pivot;

    return low;
}

// 快速排序
void QuickSort(int Array[], int low, int high)
{
    if(low < high){
        int pivotLoc = Partition(Array, low, high);
        QuickSort(Array, low, pivotLoc-1);
        QuickSort(Array, pivotLoc+1, high);
    }
}

// 合并有序数组 Merge Array[low, mid] and Array[mid+1, high] int Array[low,high]
void Merge(int Array[], int low, int mid, int high)
{
    int tmp[N] = {0};
    int size = high - low + 1;

    int k1 = low;
    int k2 = mid+1;
    int i = 0;
    while(k1 <= mid && k2 <= high){
        if(Array[k1] < Array[k2] ) tmp[i++] = Array[k1++];
        else                       tmp[i++] = Array[k2++];
    }

    while(k1 <= mid) tmp[i++] = Array[k1++]; 
    while(k2 <= high) tmp[i++] = Array[k2++]; 
    
    // Copy
    for(int i=0, k=low; i <= size-1; i++){
        Array[k++] = tmp[i];
    }
}

// 二路归并
void TwoWayMergeSort(int Array[], int low, int high)
{
    // 没有或者只有一个元素，直接返回
    if (low >= high) return;

    // 两个元素，直接比较大小，进行交换
    if (low == high -1 ){
        if(Array[low] > Array[high]){
            Swap(Array[low], Array[high]);
        }
        return;
    }

    // 平分成上下两部分，分别递归排序
    int mid = (low+high) / 2;
    TwoWayMergeSort(Array, low, mid);
    TwoWayMergeSort(Array, mid+1, high);

    // 将上下两部分有序数组，合并成一个新数组 Merge Array[low, mid] and Array[mid+1, high]
    Merge(Array,low, mid, high);
}


int main()
{
    int Array[N] = {0};
    int size = 10;

    printf("-----InsertSort----\n");
    RandomArray(Array,size);
    PrintArray(Array,size);
    InsertSort(Array,size);
    PrintArray(Array,size);

    printf("-----BinarySort-----\n");
    RandomArray(Array,size);
    PrintArray(Array,size);
    BinarySort(Array,size);
    PrintArray(Array,size);

    printf("-----TwoWaySort-----\n");
    RandomArray(Array,size);
    PrintArray(Array,size);
    TwoWaySort(Array,size);
    PrintArray(Array,size);

    printf("-----SelectSort-----\n");
    RandomArray(Array,size);
    PrintArray(Array,size);
    SelectSort(Array,size);
    PrintArray(Array,size);

    printf("-----HeapSort-----\n");
    RandomArray(Array,size);
    PrintArray(Array,size);
    BuildHeap(Array,size);
    PrintArray(Array,size);
    HeapSort(Array,size);
    PrintArray(Array,size);

    printf("-----QuickSort-----\n");
    RandomArray(Array,size);
    PrintArray(Array,size);
    QuickSort(Array,0,size-1);
    PrintArray(Array,size);    

    printf("-----BubbleSort-----\n");
    RandomArray(Array,size);
    PrintArray(Array,size);
    BubbleSort(Array,size);
    PrintArray(Array,size); 

    printf("-----TwoWayMergeSort-----\n");
    RandomArray(Array,size);
    PrintArray(Array,size);
    TwoWayMergeSort(Array,0,size-1);
    PrintArray(Array,size); 
    return 0;
}
