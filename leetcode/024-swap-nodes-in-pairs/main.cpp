/*
 * https://leetcode.com/problems/swap-nodes-in-pairs
 * 题目：给定一个链表，将链表中相邻的元素，两两交换。如输入为[1,2,3,4] 输出[2,1,4,3]
 * 思路：
 *     增加一个虚拟的链表头，然后从表头开始，只要后面存在两个节点，就交换。最终返回虚拟表头的next 即可
 */
#include <iostream>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    explicit ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// Accepted 3 ms Beats 54.35%
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode* virtualHead = new ListNode(0, head);
        ListNode* p = virtualHead;
        while(p->next && p->next->next){
            // swap p->next and p->next->next;
            ListNode* tmp1 = p->next;
            ListNode* tmp2 = p->next->next;
            p->next = tmp2;
            tmp1->next = tmp2->next;
            tmp2->next = tmp1;

            p = p->next->next;
        }

        return virtualHead->next;
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

    //auto list1 = fromVector({1,4,5,6});
    auto list1 = fromVector({});
    auto ret = s.swapPairs(list1);
    PrintList(ret);


    return 0;
}