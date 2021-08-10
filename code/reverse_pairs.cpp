#include <vector>
#include <iostream>

using namespace std;

/**
 * 给定一个数组 nums ，如果 i < j 且 nums[i] > 2*nums[j] 我们就将 (i, j) 称作一个重要翻转对。
 * 你需要返回给定数组中的重要翻转对的数量。
 * 
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode-cn.com/problems/reverse-pairs
 * 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 * 
 * Solution:
 * Merge-Sort + binary search
 * 时间跟内存好像还是很大的样子
 * 
*/

#define CAST_LONG(num) static_cast<long>(num)

class Solution {
public:
    // return the total number of reverse pair in range [l, r)
    int merge_sort(vector<int>& nums, const int& l, const int& r) {
        if (l >= r-1) return 0;
        int m = (l+r)/2;
        int ret = merge_sort(nums, l, m) + merge_sort(nums, m, r);
        // count the pair with ends in [l, m) and [m, r)
        int i=l;
        int j;
        while (i<m) {
            long nums_i = CAST_LONG(nums[i]);
            // some condition will not happen
            if (nums_i <= 2*CAST_LONG(nums[m])) {
                ++i;
                continue;
            }
            // binary search
            int s=m, e=r;
            while (s<e-1) {
                int t = (s+e)/2;
                if (nums_i > 2*CAST_LONG(nums[t])) s=t;
                else e=t;
            }
            ret += (s-m+1);
            ++i;
        }
        // merge pair of [l, m) [m, r)
        vector<int> sort_tmp = vector<int>(r-l);
        int s=0;
        i=l; j=m;
        while (i<m && j<r) {
            if (nums[i] < nums[j]) sort_tmp[s++] = nums[i++];
            else sort_tmp[s++] = nums[j++];
        }
        while (i<m) sort_tmp[s++] = nums[i++];
        while (j<r) sort_tmp[s++] = nums[j++];
        memcpy(nums.data()+l, sort_tmp.data(), sizeof(int)*(r-l));
        return ret;
    }

    int reversePairs(vector<int>& nums) {
        return merge_sort(nums, 0, static_cast<int>(nums.size()));
    }
};

int main(const int argc, const char* argv[]) {
    auto s = vector<int>({4});
    auto sol = Solution();
    cout << "ans: " << sol.reversePairs(s) << endl;
    return 0;
}