#include <iostream>
#include <vector>
#include <deque>

using namespace std;

/**
 * 满二叉树是一类二叉树，其中每个结点恰好有 0 或 2 个子结点。
 * 返回包含 N 个结点的所有可能满二叉树的列表。 答案的每个元素都是一个可能树的根结点。
 * 答案中每个树的每个结点都必须有 node.val=0。
 * 你可以按任何顺序返回树的最终列表。
 * 
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode-cn.com/problems/all-possible-full-binary-trees
 * 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 * 
 * Solution:
 * 递归+缓存结果
*/

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    vector<vector<TreeNode*>> buffer;
    vector<TreeNode*> allPossibleFBT(int n) {
        if (buffer.size() == 0) {
            buffer.resize(n);
        }

        vector<TreeNode*>& res = buffer[n/2];
        if (res.size() > 0) return res;
        if (n%2 == 0) return res;
        if (n == 1) {
            res.push_back(new TreeNode(0));
            return res;   
        }
        for (int i=1; i<n-1; i+=2) {
            auto s1 = allPossibleFBT(i);
            auto s2 = allPossibleFBT(n-1-i);
            for (TreeNode* l1: s1) {
                for (TreeNode* l2: s2) {
                    auto head = new TreeNode(0, l1, l2);
                    res.push_back(head);
                }
            }
        }
        return res;
    }
};

void bfs(TreeNode* root) {
    auto deck = deque<TreeNode*>();
    deck.push_back(root);
    cout << '[';
    while (!deck.empty()) {
        TreeNode* front = deck.front();
        deck.pop_front();
        if (front == nullptr) {
            cout << "null";
        } else {
            cout << front->val;
            deck.push_back(front->left);
            deck.push_back(front->right);
        }
        cout << ',';
    }
    cout << ']' << endl;
}

int main(int argc, const char* argv[]) {
    auto sol = Solution();
    int N = 6;
    auto res = sol.allPossibleFBT(N);
    for (TreeNode* s: res) {
        bfs(s);
    }
}