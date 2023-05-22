/*
 * https://leetcode.com/problems/merge-k-sorted-lists/
 * 题目：给定 k 个递增排序的链表，将其合并为一个递增的链表
 * 思路：
 *     记住每个链表的当前位置，然后依次比较
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

// Accepted 1147 ms 5.3%
// 思路：使用一个数组记住每个子链表的当前位置，每次从子链表中选择一个最小的，加入到最终合并的链表中
//      这里面存在重复比较：每一轮从所有子链表中找最小的时候，其实除了上一轮被找出的最小的值，剩下的在上一轮已经比较过了
//      所以这个算法效率不高
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode* head = nullptr; // 保存最终合并的链表表头
        ListNode* p = nullptr;    // 指向最终合并的链表的当前位置
        vector<ListNode*> vp;     // 保存每个链表的当前位置指针, vp[0] 代表第 0 个子链表的当前位置
        for(int i = 0; i < lists.size(); i++ ){  // 初始时指向子链表的表头
            vp.push_back(lists[i]);
        }

        while(1){
            // 从 所有子链表的当前位置中找到值最小的，加入到最终合并的链表中
            int min_idx = -1; // invalid position
            int min_val = 0;
            for(int i = 0; i < vp.size(); i++){
                if(vp[i] != nullptr){
                    if( min_idx < 0 || vp[i]->val < min_val){
                        min_idx = i;
                        min_val = vp[i]->val;
                    }
                }
            }

            // 找不到最小值了，说明遍历结束了
            if(min_idx < 0) break;

            // 找到了最小值，则把该值放入到最终合并的链表中，再把该子链表后移一位
            if(head == nullptr){
                head = p = vp[min_idx];
                vp[min_idx] = vp[min_idx]->next;
            }else{
                p->next = vp[min_idx];
                p = p->next;
                vp[min_idx] = vp[min_idx]->next;
            }
        }

        return head;
    }
};

// Accepted 132 ms Beats 26.64%
// 思路2：将依次将剩余的每个子链表插入到首个子链表中
class Solution2 {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.empty()) return nullptr;

        ListNode* head = lists[0];              // head 保存最终合并的链表表头，初始时指向首个子链表
        for(int i = 1; i < lists.size(); i++){  // 依次将剩余的子链表插入到首个子链表中
            head = merge(head, lists[i]);
        }

        return head;
    }


    // 将 list2 合并到 list1 中，并返回合并后的链表头
    ListNode* merge(ListNode* list1, ListNode* list2){
        if(list1 == nullptr) return list2;
        if(list2 == nullptr) return list1;

        ListNode* head = new ListNode(INT16_MIN); // 构建一个新的节点，其next指向list1，方便统一处理
        head->next = list1;

        ListNode* p1 = head;
        ListNode* p2 = list2;
        while(p2){
            while(p1->next && p1->next->val <= p2->val) p1 = p1->next;

            if(p1->next == nullptr){
                // 说明 p1 中元素都比 p2 小，则将p2 放到 list1 的末尾
                ListNode* tmp1 = p2->next;
                p1->next = p2;
                p1->next->next = nullptr;
                p2 = tmp1;
            }else{
                // 插入到p1的next
                ListNode* tmp = p1->next;
                ListNode* tmp1 = p2->next;
                p1->next = p2;
                p1->next->next = tmp;
                p2 = tmp1;
            }

        }
        return head->next;
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
    Solution2 s;

    // [1,4,5],[1,3,4],[2,6]
    auto list1 = fromVector({1,4,5});
    auto list2 = fromVector({1,3,4});
    auto list3 = fromVector({0});

    std::vector<ListNode*> vec = {list1, list2, list3};

    auto ret = s.mergeKLists(vec);
    PrintList(ret);


    return 0;
}