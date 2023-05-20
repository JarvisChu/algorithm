// https://leetcode.com/problems/merge-two-sorted-lists/
// 题目：将两个给定的递增排序的链表合并成一个链表
// 思路：
//   使用一个临时的Head, 然后用两个指针分别遍历比较即可

#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// Accepted 8ms Beats 69.35%
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* head = nullptr; // 指向合并后的链表表头
        ListNode* pm = nullptr;   // 用于合并
        ListNode* p1 = list1;
        ListNode* p2 = list2;

        while(p1 && p2){
            if(p1->val < p2->val) {
                if(!head) { head = p1; pm = head;}
                else{ pm->next = p1; pm = pm->next;}
                p1 = p1->next;
            }else{
                if(!head) { head = p2; pm = head;}
                else{ pm->next = p2; pm = pm->next;}
                p2 = p2->next;
            }
        }

        if(p1){
            if(!head) { head = p1;}
            else{ pm->next = p1;}
        }

        if(p2){
            if(!head) { head = p2;}
            else{ pm->next = p2;}
        }

        return head;
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
    auto list1 = fromVector({1,2,4});
    auto list2 = fromVector({1,3,4});
    auto ret = s.mergeTwoLists(list1, list2);
    PrintList(ret);

    return 0;
}