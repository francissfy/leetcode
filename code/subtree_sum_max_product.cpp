#include <iostream>
#include <vector>
#include <deque>
#include <unordered_map>

using namespace std;

/**
 * 给你一棵二叉树，它的根为 root 。请你删除 1 条边，使二叉树分裂成两棵子树，且它们子树和的乘积尽可能大。
 * 由于答案可能会很大，请你将结果对 10^9 + 7 取模后再返回。
 * 
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode-cn.com/problems/maximum-product-of-splitted-binary-tree
 * 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 * 
 * Solution:
 * 没啥好solve的
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
    int subtree_sum(TreeNode* node, vector<int>& node_sum) {
        if (node == nullptr) return 0;
        int s = node->val + subtree_sum(node->left, node_sum) + subtree_sum(node->right, node_sum);
        node_sum.push_back(s); 
        return s;
    }

    int maxProduct(TreeNode* root) {
        vector<int> node_sum;
        size_t total_sum = static_cast<size_t>(subtree_sum(root, node_sum));

        size_t max_product = 0;
        for (const auto& p: node_sum) {
            size_t prod = static_cast<size_t>(p) * (total_sum - static_cast<size_t>(p));
            max_product = max_product>prod? max_product:prod;
        }

        return max_product % (static_cast<int>(1e9+7));
    }
};

int main(int argc, const char* argv[]) {
    // reconstruct from bfs
    vector<TreeNode*> tree_nodes;
    auto bfs_init = vector<int>({1,0,2,3,4,0,0,5,6});
    for (const int& v: bfs_init) {
        tree_nodes.push_back(v == 0? nullptr:new TreeNode(v));   
    }
    // link children
    int pnode = 0;
    int cnode = 1;
    int num_nodes = static_cast<int>(tree_nodes.size());
    while (cnode < num_nodes) {
        tree_nodes[pnode]->left = tree_nodes[cnode++];
        if (cnode >= num_nodes) break;
        tree_nodes[pnode]->right = tree_nodes[cnode++];
        if (cnode >= num_nodes) break;
        ++pnode;
        while (tree_nodes[pnode] == nullptr) ++pnode;
    }
    TreeNode* root = tree_nodes[0];

    // bfs print
    deque<TreeNode*> bfs_deque;
    bfs_deque.push_back(root);
    while (!bfs_deque.empty()) {
        TreeNode* n = bfs_deque.front();
        bfs_deque.pop_front();
        if (n == nullptr) {
            cout << "null, ";
            continue;
        }
        cout << n->val << ", ";
        bfs_deque.push_back(n->left);
        bfs_deque.push_back(n->right);
    }
    cout << endl;

    auto sol = Solution();
    int ans = sol.maxProduct(root);

    cout << "ans: " << ans << endl;

    for (TreeNode* ptr: tree_nodes) {
        delete ptr;
    }
    return 0;
}
