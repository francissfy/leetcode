#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

/**
 * 编写代码，移除未排序链表中的重复节点。保留最开始出现的节点。
 * 
 * Solution:
 * 
*/

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* removeDuplicateNodes(ListNode* head) {
        if (head == nullptr) return head;
        
        auto val_set = unordered_set<int>();
        auto ptr = head;

        val_set.insert(ptr->val);
        while (ptr->next != nullptr) {
            const int& v = ptr->next->val;
            if (val_set.find(v) == val_set.end()) {
                // no repeat
                val_set.insert(v);
                ptr = ptr->next;
            } else {
                ptr->next = ptr->next->next;
            }
        }
        return head;
    }
};

int main(int argc, const char* argv[]) {
    auto test_list = vector<int>({1, 1, 1, 2, 2});
    auto test_case = vector<ListNode>();
    for (const int& v: test_list) {
        test_case.push_back(ListNode(v));
    }
    for (size_t i=0; i<test_case.size(); ++i) {
        if (i == test_case.size()-1) {
            test_case[i].next = nullptr;
        } else {
            test_case[i].next = &test_case[i+1];
        }
    }

    ListNode* head = &test_case[0];

    auto sol = Solution();
    auto ptr = sol.removeDuplicateNodes(head);
    auto iter_ptr = ptr;
    while (iter_ptr != nullptr) {
        cout << iter_ptr->val << ", ";
        iter_ptr = iter_ptr->next;
    }
    cout << endl;
    return 0;
}