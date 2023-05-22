/*
 * https://leetcode.com/problems/reverse-nodes-in-k-group/
 * 题目：给定一个链表，将链表中每K个相邻的元素作为一组，每组内做逆序。 只能使用 O(1) 个额外空间
 *     如输入为 [1,2,3,4]，K=2， 输出[2,1,4,3]
 *       输入为 [1,2,3,4,5]，K=3， 输出[3,2,1,4,5]
 * 思路：
 *     和上一题（024-swap-nodes-in-pairs）基本相同，上一题是每组2个元素，这一题是每组K个元素
 *     增加一个虚拟的链表头，然后从表头开始，只要后面存在K个节点，就逆序。最终返回虚拟表头的next 即可
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


// Accept 24 ms Beats 8.4%
// 思路：每选 K 个节点做逆序
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if(k <= 1) return head;

        ListNode* virtualHead = new ListNode(0, head);
        ListNode* p = virtualHead;

        while(1){
            // 判断当前节点后面够不够 K 个元素
            int i = 0;
            ListNode* p1 = p;
            while(p1->next && i < k) { i++; p1 = p1->next;}
            if(i < k) break;

            // 够K个，则将 p->next 到 p1 这一段链表逆序，采用头插算法即可
            ListNode* tmp1 = p1->next;
            ListNode* p2 = p->next;      // 从 p->next 本来就在 p 后面，不用头插，从它后面一个元素开始头插
            while(p2->next != tmp1){ // p2->next 是需要头插的节点
                // 先将 p2->next 从链表中摘出来
                ListNode* tmp2 = p2->next;
                p2->next = p2->next->next;

                // 再将 p2->next 即 tmp2 插入到 p 后面
                tmp2->next = p->next;
                p->next = tmp2;
            }

            // 插入结束后，p2 == p1
            // 将 p 移动到 p2 即可
            p = p2;
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

    auto list1 = fromVector({1,2,3,4,5,6});
    int k = 1;
    //auto list1 = fromVector({});
    auto ret = s.reverseKGroup(list1,k);
    PrintList(ret);


    return 0;
}