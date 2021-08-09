#include <iostream>
#include <vector>

using namespace std;

/**
 * 给你一个整数数组 arr 。
 * 现需要从数组中取三个下标 i、j 和 k ，其中 (0 <= i < j <= k < arr.length) 。
 * 
 * a 和 b 定义如下：
 * a = arr[i] ^ arr[i + 1] ^ ... ^ arr[j - 1]
 * b = arr[j] ^ arr[j + 1] ^ ... ^ arr[k]
 * 注意：^ 表示 按位异或 操作。
 * 
 * 请返回能够令 a == b 成立的三元组 (i, j , k) 的数目。
 * 
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode-cn.com/problems/count-triplets-that-can-form-two-arrays-of-equal-xor
 * 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 * 
 * Solution:
 * DP
 * a xor b == 0
*/

class Solution {
public:
    int countTriplets(vector<int>& arr) {
        int len = static_cast<int>(arr.size());
        // auto r = vector<int>(len, 0);
        int r[300];
        int count = 0;
        // dp, init first line
        r[0] = arr[0];
        for (int k=1; k<len; ++k) {
            r[k] = r[k-1] xor arr[k];
            if (r[k] == 0) count += (k);
        };
        // start from second line
        for (int i=1; i<(len-1); ++i) {
            for (int k=(i+1); k<len; ++k) {
                r[k] = r[k] xor arr[i-1];
                if (r[k] == 0) count += (k-i);
            }
        }
        return count;
    }
};

int main(int argc, const char* argv[]) {
    auto sol = Solution();
    auto arr = vector<int>({1, 1, 1, 1, 1});
    int res = sol.countTriplets(arr);
    cout << "ans: " << res << endl;
    return 0;
}