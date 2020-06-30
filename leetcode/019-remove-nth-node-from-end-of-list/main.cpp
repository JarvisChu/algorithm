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

    // 思路2，增加一个头结点，统一处理逻辑
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

void print(ListNode * head) {
    while(head != nullptr) {
        cout << head->val << ", " ;
        head = head->next;
    }
    cout<<endl;
}

int main()
{
    Solution s;
    ListNode* node5 = new ListNode(5,nullptr);
    ListNode* node4 = new ListNode(4,node5);
    ListNode* node3 = new ListNode(3,node4);
    ListNode* node2 = new ListNode(2,node3);
    ListNode* node1 = new ListNode(1,node2);
    print(node5);

    ListNode* p = s.removeNthFromEnd(node1, 1);
    print(p);





}