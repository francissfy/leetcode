#include <iostream>

using namespace std;

/**
 * 给你一个整数 n ，请你判断 n 是否为 丑数 。如果是，返回 true ；否则，返回 false 。
 * 丑数 就是只包含质因数 2、3 和/或 5 的正整数。
 * 
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode-cn.com/problems/ugly-number
 * 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 * 
 * Solution:
 * 没啥好solve的
*/

class Solution {
public:
    bool isUgly(int n) {
        if (n<1) return false;
        int t = n;
        while (t%2 == 0) t /= 2;
        while (t%3 == 0) t /= 3;
        while (t%5 == 0) t /= 5;
        return t == 1;
    }
};

int main(int argc, const char* argv[]) {
    auto sol = Solution();
    cout << "ans: " << sol.isUgly(0) << endl;
    return 0;
}