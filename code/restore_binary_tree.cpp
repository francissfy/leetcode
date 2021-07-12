#include <iostream>
#include <vector>
#include <deque>

using namespace std;

/**
 * 输入某二叉树的前序遍历和中序遍历的结果，请重建该二叉树。
 * 假设输入的前序遍历和中序遍历的结果中都不含重复的数字
 * 
 * Solution:
 * 没啥好弄的, 但是OJ里不用做手动的内存管理 不然会报错
 * 但是要注意Vector里push_back造成的引用与指针失效的问题
*/

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* helper(const vector<int>& preorder, const vector<int>& inorder, 
                     const int& pre_start, const int& pre_end, 
                     const int& in_start, const int& in_end) {
        // single node
        if (pre_start == pre_end) {
            auto new_node = new TreeNode(preorder[pre_start]);
            return new_node;
        }
        if (pre_start > pre_end) return nullptr;

        // find top node
        int top_offset = 0;
        while (inorder[top_offset + in_start] != preorder[pre_start]) ++top_offset;
        
        TreeNode* top_node = new TreeNode(preorder[pre_start]);

        // 
        top_node->left = helper(preorder, inorder, pre_start+1, pre_start+top_offset, in_start, in_start+top_offset-1);
        top_node->right = helper(preorder, inorder, pre_start+top_offset+1, pre_end, in_start+top_offset+1, in_end);

        return top_node;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return helper(preorder, inorder, 0, static_cast<int>(preorder.size()-1), 0, static_cast<int>(inorder.size()-1));
    }
};

int main(int argc, const char* argv[]) {
    auto preorder = vector<int>({3,9,20,15,7});
    auto inorder = vector<int>({9,3,15,20,7});

    auto sol = Solution();
    TreeNode* root = sol.buildTree(preorder, inorder);
    // print, bfs
    auto bfs = deque<TreeNode*>();
    bfs.push_back(root);
    while (!bfs.empty()) {
        TreeNode* node = bfs.front();
        bfs.pop_front();
        if (node == nullptr) continue;
        cout << node->val << ", ";
        bfs.push_back(node->left);
        bfs.push_back(node->right);
    }
    cout << endl;

    return 0;
}

