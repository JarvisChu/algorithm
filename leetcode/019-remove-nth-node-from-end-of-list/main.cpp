/*
https://leetcode.com/problems/remove-nth-node-from-end-of-list/

19. Remove Nth Node From End of List

Given a linked list, remove the n-th node from the end of list and return its head.

Example:
    Given linked list: 1->2->3->4->5, and n = 2.
    After removing the second node from the end, the linked list becomes 1->2->3->5.

Note:
    Given n will always be valid.

Follow up:
    Could you do this in one pass?
*/

#include <iostream>
using namespace std;

// 思路
// 移除链表的倒数第n个结点
// 两个指针，p1 = p2 = head，
//         p1先往后走，如果p1走了n步，p2再开始走
//         这样，当p1指向最后一个节点时，p2指向的就是倒数第n个结点，移除p2即可


// Definition for singly-linked list.
struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
};
 
class Solution {
public:

    // 思路1： 正常思路
    ListNode* removeNthFromEnd1(ListNode* head, int n) {
        if(head == nullptr || n <= 0) return head; // invalid input
        

        ListNode *p1 = head;        // 往后移动，找到最后的结点  
        ListNode *p2 = head;        // 指向要删除的结点
        ListNode *pre_p2 = nullptr; // 指向要删除结点的前一个结点

        int dist = 0; // p1 和 p2 的距离
        while(p1->next != nullptr) {

            p1 = p1->next; // p1 向后移动一位
            dist ++;       // p1 和 p2的距离

            if (dist > (n-1) ) { // 如果距离超过了n-1，则p2也向后移动
                pre_p2 = p2;
                p2 = p2->next;
            }
        }

        // p2 是要删除的结点，pre_p2是p2的前驱
        if(dist < (n-1) ) {
            // 没有找到要删除的点
            return head;
        }

        if(dist == n-1) {
            // 删除头结点
            //cout<< head->next  <<endl;
            return head->next;
        }

        // 删除结点
        pre_p2->next = pre_p2->next->next;
        return head;
    }

    // 思路2，思路1的改进版本，p2 不是指向要删除的节点，而是直接指向要删除节点的前驱
    // 3ms Beats 82.58
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if(n <= 0) return head;

        ListNode* p1 = head; // 先往后走
        ListNode* p2 = head; // 指向要删除节点的前驱节点，p1 走 n+1 时，再往后走

        int dist = 0; // 刚开始，p1 和 p2 都指向头节点，两者距离为0
        while(p1){
            p1 = p1->next;
            dist++;
            if(dist > n+1){ // p1 先走 n+1 步之后，p2再继续跟着走
                p2 = p2->next;
            }
        }

        // 遍历完，有几种情况
        // (1) p2 一步未走，即 p2 == head，说明没有超过 n+1 步，此时
        //     (1.1) 刚好 n+1 步，则说明要删除的就是 head->next
        //     (1.2) 刚好 n 步，则说明要删除的就是 head
        //     (1.3) 少于 n 步，说明链表不够长，不用删
        // (2) p2 走动了，则删除 p2->next 即可
        if(p2 == head){
            if(dist == n + 1){ // (1.1) delete head->next
                head->next = head->next->next; // 不用判空，因为 dist 至少是2，说明链表长度至少是2
            }else if(dist == n) { // (1.2) delete head
                head = head->next;
            }
            //else if(dist < n){}  // (1.3) 不用删，直接 return head
            //else{} // dist 不可能 > n+1，因为dist 一旦 > n+1，p2 必然会走动
        }else {
            p2->next = p2->next->next; // 不用判空，因为 n >= 1 保证了p2后面至少有一个节点
        }

        return head;
    }


    // 思路3，增加一个头结点，统一处理逻辑
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if(head == nullptr || n <= 0) return head; // invalid input

        ListNode* new_head = new ListNode(-1, head); // 增加一个头结点
        ListNode *p1 = new_head;        // 往后移动，找到最后的结点  
        ListNode *p2 = new_head;        // 指向要删除的结点的前驱

        // p1 先往后走n步
        for(int i = 0 ; i < n; i++) {
            p1 = p1->next;
            if(p1 == nullptr) return head; // 
        }

        // p1 和 p2 同时往后走
        while(p1->next != nullptr) {
            p1 = p1->next;
            p2 = p2->next;
        }

        // 删除 p2的后驱即可
        p2->next = p2->next->next;
        return new_head->next;
    }
};

ListNode* fromVector(std::vector<int> vec){
    ListNode* head = nullptr;
    ListNode* p = nullptr;
    for(auto v:vec){
        ListNode* node = new ListNode(v);
        if(head == nullptr){
            head = node;
            p = head;
        }else{
            p->next = node;
            p = p->next;
        }
    }

    return head;
}

void PrintList(ListNode* head){
    cout << "[";
    while(head){
        cout << head->val;
        if(head->next) cout << ", ";
        head = head->next;
    }
    cout << "]" << endl;
}

int main()
{
    Solution s;

//    auto list = fromVector({1,2,3,4,5});
//    auto n = 2;

    auto list = fromVector({1});
    auto n = 1;

    PrintList(list);
    auto ret = s.removeNthFromEnd(list, n);
    PrintList(ret);


    return 0;
}