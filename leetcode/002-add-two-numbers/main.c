/*
2. Add Two Numbers

You are given two non-empty linked lists representing two non-negative integers. 
The digits are stored in reverse order and each of their nodes contain a single digit. 
Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Example:
    Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
    Output: 7 -> 0 -> 8
    Explanation: 342 + 465 = 807.
*/

#include <stdio.h>
#include <stdlib.h>

/*
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    struct ListNode *next;
};

// 注意的点
// 数字可能非常大，不是int或long 能表示的，所以必须按位进行比较

void display(struct ListNode* l) 
{
    struct ListNode* p = l;
    while(p != NULL ) {
        printf("%d ", p->val);
        p = p->next;
    }
    printf("\n");
}


// Accepted, 12 ms
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2){
    struct ListNode* ret =  NULL; //(struct ListNode*)malloc(sizeof(struct ListNode));
    struct ListNode* p = ret; 

    int carry = 0; // 进位

    // 累加两个链表的每一位
    while(l1 != NULL && l2 != NULL) {
        int val = l1->val + l2->val + carry;
        int digit = val % 10;
        carry = val / 10;

        if (ret == NULL) {
            ret = p = (struct ListNode*)malloc(sizeof(struct ListNode));
            p->val = digit;
            p->next = NULL;
        }else {
            struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
            node->val = digit;
            node->next = NULL;
            p->next = node;
            p = p->next;
        }
        l1 = l1->next;
        l2 = l2->next;
    }

    // remain 指向剩余的链表
    struct ListNode* remain = l1;
    if (l1 == NULL) {
        remain = l2;
    }

    // 如果有剩余，则补上剩余的位数
    while(remain != NULL) {
        int val = remain->val + carry;
        int digit = val % 10;
        carry = val / 10;

        if (ret == NULL) {
            ret = p = (struct ListNode*)malloc(sizeof(struct ListNode));
            p->val = digit;
            p->next = NULL;
        }else {
            struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
            node->val = digit;
            node->next = NULL;
            p->next = node;
            p = p->next;
        }
        remain = remain->next;
    }      

    // 链表已经比较完，如果有进位，补上进位
    if (remain == NULL && carry) {

        struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
        node->val = carry;
        node->next = NULL;
        p->next = node;

        return ret;
    }

    return ret;
}

int main()
{
    struct ListNode* l1 = (struct ListNode*)malloc(sizeof(struct ListNode));
    l1->val = 1; //2;
    l1->next = NULL;

/*    struct ListNode* l1_node2 = (struct ListNode*)malloc(sizeof(struct ListNode));
    l1_node2->val = 8; //4;
    l1_node2->next = NULL;
    l1->next = l1_node2;

    struct ListNode* l1_node3 = (struct ListNode*)malloc(sizeof(struct ListNode));
    l1_node3->val = 3;
    l1_node3->next = NULL;
    l1_node2->next = l1_node3;
*/
    struct ListNode* l2 = (struct ListNode*)malloc(sizeof(struct ListNode));
    l2->val = 9; // 5;
    l2->next = NULL;

    struct ListNode* l2_node2 = (struct ListNode*)malloc(sizeof(struct ListNode));
    l2_node2->val = 9;
    l2_node2->next = NULL;
    l2->next = l2_node2;
/*
    struct ListNode* l2_node3 = (struct ListNode*)malloc(sizeof(struct ListNode));
    l2_node3->val = 4;
    l2_node3->next = NULL;
    l2_node2->next = l2_node3;
*/
    
    struct ListNode* ret =   addTwoNumbers(l1, l2);
    
    display(ret);

    return 0;
}