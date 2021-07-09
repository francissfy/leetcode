#include <cstdint>
#include <iostream>
#include <cmath>

using namespace std;

/**
 * 给你一个整数 n，请你判断该整数是否是 2 的幂次方。如果是，返回 true ；否则，返回 false 。
 * 如果存在一个整数 x 使得 n == 2x ，则认为 n 是 2 的幂次方。
 * 
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode-cn.com/problems/power-of-two
 * 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/

class Solution {
public:
    bool isPowerOfTwo(int n) {
        if (n < 1) return false;
        uint8_t tmp = 0;
        for (uint8_t i=0; i<32; ++i) {
            tmp += (n>>i)&0b1;
        }
        return tmp == 1;
    }
};

int main(int argc, const char* argv[]) {
    auto sol = Solution();
    int t = int(-256);
    cout << "ans: " << sol.isPowerOfTwo(t) << endl;
    return 0;
}