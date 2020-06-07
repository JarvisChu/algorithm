// 单链表逆序

// 题目：https://leetcode.com/problems/reverse-linked-list/
// 分析：http://zhujiangtao.com/?p=1267

#include <stdio.h>
#include <stdlib.h>

// Definition for singly-linked list.
 struct ListNode {
    int val;
    struct ListNode *next;
};


// 递归
struct ListNode* reverseList1(struct ListNode* head){
    if (head->next == NULL) return head;

    struct ListNode* first = head;  // (first, last) 是已经逆序的部分，first->xx->last
    struct ListNode* last = head;
    
    // 遍历链表，往前插入
    struct ListNode* p = head->next; 
    last->next = NULL;

    while(p != NULL) {
        // first->xxx->head, 插入p，变为 p->first->xx->head

        struct ListNode* pNext = p->next; // 先记录p->next 
        p->next = first;
        first = p;

        p = pNext;
    }

    return first;
}

 struct ListNode* reverseList2(struct ListNode* head) {
        struct ListNode *pre = malloc(sizeof(struct ListNode));
        struct ListNode *cur = head;
        pre -> next = head;
        while (cur && cur -> next) {
            struct ListNode* temp = pre -> next;
            pre -> next = cur -> next;
            cur -> next = cur -> next -> next;
            pre -> next -> next = temp;
        }
        return pre -> next;
}

struct ListNode* reverseList3(struct ListNode* head) {                                       
    if (head == NULL || head->next == NULL) return head; 
    
    struct ListNode* prev = NULL;
    while (head != NULL) {
        struct ListNode* temp = head;
    head = head->next;
        temp->next = prev;
        prev = temp;

        
    }
    return prev;
}

struct ListNode* reverseList(struct ListNode* head) {                                       
    if (head == NULL || head->next == NULL) return head;
    struct ListNode* node = reverseList(head->next);
    if (head->next->next == NULL) printf("NULL\n");
    head->next->next = head; // head->next 就是 node所逆序链表的最后一个元素
    head->next = NULL;
    return node;
}

int main()
{
    struct ListNode* head = malloc(sizeof(struct ListNode));
    head->val = 1;
    head->next = NULL;

    struct ListNode* p1 = malloc(sizeof(struct ListNode));
    p1->val = 2;
    p1->next = NULL;
    head->next = p1;

    struct ListNode* p2 = malloc(sizeof(struct ListNode));
    p2->val = 3;
    p2->next = NULL;
    //p1->next = p2;

    struct ListNode* p3 = malloc(sizeof(struct ListNode));
    p3->val = 4;
    p3->next = NULL;
    p2->next = p3;

    struct ListNode* p4 = malloc(sizeof(struct ListNode));
    p4->val = 5;
    p4->next = NULL;
    p3->next = p4;

    struct ListNode* p = reverseList(head);

    while(p != NULL) {
        printf("%d ", p->val);
        p = p->next;
    }


    return 0;
}