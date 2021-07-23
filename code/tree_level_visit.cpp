#include <iostream>
#include <vector>
#include <deque>

using namespace std;

/**
 * 给你一个二叉树，请你返回其按 层序遍历 得到的节点值。 （即逐层地，从左到右访问所有节点）。
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
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ret;
        if (root == nullptr) return ret;
        deque<TreeNode*> deck;
        deck.push_back(root);
        deck.push_back(nullptr);
        ret.push_back(vector<int>());
        while (!deck.empty()) {
            auto f = deck.front();
            deck.pop_front();
            if (f == nullptr) {
                // enter new level
                if (deck.empty()) break;
                ret.push_back(vector<int>());
                deck.push_back(nullptr);
            } else {
                ret[ret.size()-1].push_back(f->val);
                if (f->left != nullptr) deck.push_back(f->left);
                if (f->right != nullptr) deck.push_back(f->right);
            }
        }
        return ret;
    }
};


int main(int argc, const char* argv[]) {
    // reconstruct from bfs
    #define null 0
    vector<TreeNode*> tree_nodes;
    auto bfs_init = vector<int>({3});
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

    auto sol = Solution();
    auto res = sol.levelOrder(root);
    for (const vector<int>& v: res) {
        cout << '[';
        for (const int& e: v) {
            cout << e << ',';
        }
        cout << ']' << endl;
    }
    return 0;
}