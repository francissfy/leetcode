#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <bitset>

using namespace std;

/**
 * 给定由若干 0 和 1 组成的矩阵 matrix，从中选出任意数量的列并翻转其上的 每个 单元格。翻转后，单元格的值从 0 变成 1，或者从 1 变为 0 。
 * 回经过一些翻转后，行与行之间所有值都相等的最大行数。
 * 
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode-cn.com/problems/flip-columns-for-maximum-number-of-equal-rows
 * 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 * 
 * Solution:
 * 每两行要么相同要么相反
 * vector<bool> + hash
 * or
 * 用bit变化编码每一行
*/

class Solution {
public:
    int maxEqualRowsAfterFlips(vector<vector<int>>& matrix) {
        size_t row_size = matrix[0].size();
        auto buffer = vector<bool>(row_size, false);
        auto hv2num = unordered_map<size_t, int>();
        auto hash_fn = hash<vector<bool>>();

        for (const vector<int>& row: matrix) {
            // convert vec to int pattern
            buffer.assign(row_size, false);
            for (size_t i=0; i<row.size(); i++) {
                buffer[i] = (row[i] == 1);
            }
            size_t hash_v = hash_fn(buffer);
            buffer.flip();
            size_t rev_hash_v = hash_fn(buffer);

            if (hv2num.find(hash_v) != hv2num.end()) {
                hv2num[hash_v] += 1;
            } else {
                hv2num[hash_v] = 1;
            }
            if (hv2num.find(rev_hash_v) != hv2num.end()) {
                hv2num[rev_hash_v] += 1;
            } else {
                hv2num[rev_hash_v] = 1;
            }
        }
        int max_rows = 0;
        for (auto p: hv2num) {
            max_rows = max(max_rows, p.second);
        }
        return max_rows;
    }
};

int main(int argc, const char* argv[]) {
    auto sol = Solution();
    auto data = vector<vector<int>>({   
                                        {0, 1},
                                        {1, 0}
                                    });
    int ans = sol.maxEqualRowsAfterFlips(data);
    cout << "ans: " << ans << endl;
    return 0;
}