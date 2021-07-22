#include <vector>
#include <deque>

using namespace std;

/**
 * 给定一个 N 叉树，返回其节点值的 后序遍历 。
 * N 叉树 在输入中按层序遍历进行序列化表示，每组子节点由空值 null 分隔
 * 
 * Solution:
 * deque 
*/

// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;
    Node() {}
    Node(int _val) {val = _val;}
    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

class Solution {
public:
    vector<int> postorder(Node* root) {
        vector<int> res;
        if (root == nullptr) return res;
        deque<Node*> deck;
        deck.push_back(root);
        while (!deck.empty()) {
            Node* f = deck.front();
            if (f->children.empty()) {
                res.push_back(f->val);
                deck.pop_front();
            }
            deck.insert(deck.begin(), f->children.cbegin(), f->children.cend());
            f->children.clear();
        }
        return res;
    }
};

int main(int argc, const char* argv[]) {

}