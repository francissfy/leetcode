#include <iostream>

using namespace std;

/**
 * 出这题case的脑子肯定有点毛病
 * 
 * Solution:
 * 用long
*/

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    bool visit(TreeNode* node, long max_value, long min_value) {
        // make sure every node in this tree in range (min, max)
        if (node == nullptr) return true;
        if (node->val >= max_value || node->val <= min_value) return false;
        // check left, right
        return visit(node->left, node->val, min_value) && visit(node->right, max_value, node->val);
    }

    bool isValidBST(TreeNode* root) {
        return visit(root, LONG_MAX, LONG_MIN);
    }
};

int main(int argc, const char* argv[]) {
    auto n1 = TreeNode(2147483647);
    auto n2 = TreeNode(2147483647);
    n1.left = &n2;

    auto sol = Solution();
    cout << "ans: " << sol.isValidBST(&n1) << endl;
    return 0;
}