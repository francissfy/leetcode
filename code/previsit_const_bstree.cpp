#include <iostream>
#include <vector>
#include <deque>

using namespace std;

/**
 * 返回与给定前序遍历 preorder 相匹配的二叉搜索树（binary search tree）的根结点。
 * 
 * (回想一下，二叉搜索树是二叉树的一种，其每个节点都满足以下规则，对于 node.left 的任何后代，值总 < node.val，
 * 而 node.right 的任何后代，值总 > node.val。此外，前序遍历首先显示节点 node 的值，然后遍历 node.left，接着遍历 node.right。）
 * 题目保证，对于给定的测试用例，总能找到满足要求的二叉搜索树。
 * 
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode-cn.com/problems/construct-binary-search-tree-from-preorder-traversal
 * 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 * 
 * Solution:
 * 没啥特别的 速度100% 不过这个内存占的蛮大的
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
    TreeNode* helper(const vector<int>& preorder, const int& s, const int& e) {
        if (s >= e) return nullptr; // no node
        if (s+1 == e) return new TreeNode(preorder[s]);
        // split
        int p = s+1;
        while (p<e && preorder[p] < preorder[s]) ++p;
        auto lt = helper(preorder, s+1, p);
        auto rt = helper(preorder, p, e);
        auto root = new TreeNode(preorder[s], lt, rt);
        return root;
    }
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        return helper(preorder, 0, static_cast<int>(preorder.size()));
    }
};

void bfs(TreeNode* root) {
    deque<TreeNode*> deck;
    deck.push_back(root);
    while (!deck.empty()) {
        TreeNode* f = deck.front();
        deck.pop_front();
        if (f == nullptr) {
            cout << "null,";
        } else {
            cout << f->val << ',';
            // don't print leaf node's children
            if (f->left != nullptr || f->right != nullptr) {
                deck.push_back(f->left);
                deck.push_back(f->right);
            }
        }
    }
    cout << endl;
}

int main(int argc, const char* argv[]) {
    vector<int> preorder = {8,5,1,7,10,12};
    auto sol = Solution();
    TreeNode* root = sol.bstFromPreorder(preorder);
    bfs(root);
    return 0;
}