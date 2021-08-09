#include <vector>
#include <iostream>

using namespace std;

/**
 * 给定一个非负整数数组 A，返回一个数组，在该数组中， A 的所有偶数元素之后跟着所有奇数元素。
 * 你可以返回满足此条件的任何数组作为答案。
 * 
 * 直接sawp
*/

class Solution {
public:
    vector<int> sortArrayByParity(vector<int>& nums) {
        auto ret = nums;
        int i = 0;
        int len = static_cast<int>(nums.size());
        int j = len - 1;
        int tmp;
        while (true) {
            while (i<len && ret[i] % 2 == 0) ++i;
            while (j>=0 && ret[j] % 2 == 1) --j;
            if (i >= j) break;
            tmp = ret[i];
            ret[i] = ret[j];
            ret[j] = tmp;
        }
        return ret;
    }
};

int main(const int argc, const char* argv[]) {
    auto nums = vector<int>({3, 4, 8});
    auto sol = Solution();
    auto ans = sol.sortArrayByParity(nums);
    for (const int& e: ans) {
        cout << e << ',';
    }
    cout << endl;
    return 0;
}