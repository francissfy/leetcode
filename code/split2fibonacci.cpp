#include <iostream>
#include <vector>
#include <string>

using namespace std;

/**
 * 给定一个数字字符串 S，比如 S = "123456579"，我们可以将它分成斐波那契式的序列 [123, 456, 579]。
 * 形式上，斐波那契式序列是一个非负整数列表 F，且满足：
 * 0 <= F[i] <= 2^31 - 1，（也就是说，每个整数都符合 32 位有符号整数类型）；
 * F.length >= 3；
 * 对于所有的0 <= i < F.length - 2，都有 F[i] + F[i+1] = F[i+2] 成立。
 * 另外，请注意，将字符串拆分成小块时，每个块的数字一定不要以零开头，除非这个块是数字 0 本身。
 * 
 * 返回从 S 拆分出来的任意一组斐波那契式的序列块，如果不能拆分则返回 []。
 * 
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode-cn.com/problems/split-array-into-fibonacci-sequence
 * 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 * 
 * Solution:
 * 不要相信默认内存排布与初始化
 * SIGNED INT/LONG OVERFLOW!!!
 * 回溯算法
*/

class Solution {
public:
    bool is_prefix(const string& nums, const int cidx, const long long prefix, int& prefix_length) {
        int nums_len = static_cast<int>(nums.size());

        constexpr int rev_digits_buf_size = 32;
        static int rev_digits_buf[rev_digits_buf_size];
        // count number of digits
        int digits_count = 0;
        long long tmp = prefix;
        // special case, 0
        if (prefix == 0) {
            digits_count=1;
            rev_digits_buf[0] = 0;
        }
        while (tmp>0) {
            rev_digits_buf[digits_count] = tmp%10;
            tmp /= 10;
            ++digits_count;
        }
        prefix_length = digits_count;
        // validate with nums string
        if (cidx+digits_count > nums_len) return false;
        bool is_prefix = true;
        for (int i=0; i<digits_count; ++i) {
            const int& target = rev_digits_buf[digits_count-1-i];
            is_prefix &= (target == (nums[cidx+i]-'0'));
            if (!is_prefix) break;
        }
        return is_prefix;
    }

    bool dfs(const string& nums, const int cidx, vector<int>& ans) {
        int numlen = static_cast<int>(nums.size());
        int anslen = static_cast<int>(ans.size());
        if (cidx >= numlen) return true;

        long long tmp_sum = static_cast<long>(ans[anslen-2]) + static_cast<long>(ans[anslen-1]);
        // check for int32max
        if (tmp_sum > INT32_MAX) return false;
        // check for prefix
        int tmp_sum_digits;
        bool is_pre = is_prefix(nums, cidx, tmp_sum, tmp_sum_digits);
        if (is_pre) {
            // is prefix, recursive
            ans.push_back(static_cast<int>(tmp_sum));
            return dfs(nums, cidx+tmp_sum_digits, ans);
        }
        return false;
    }

    long mystoi(const string& nums, const int& sidx, const int& len) {
        long ret = 0;
        for(int i=0; i<len; ++i) {
            ret = ret*10 + (nums[sidx+i]-'0');
            if (ret>=INT32_MAX) return INT32_MAX;
        }
        return ret;
    }

    vector<int> splitIntoFibonacci(string num) {
        int numlen = static_cast<int>(num.size());
        auto ans = vector<int>();
        for (int i=1; i<2*numlen/3; ++i) {
            for (int j=1; j<= (2*numlen/3-i); ++j) {
                // not begin with 0
                if (num[0] == '0' && i>1) continue;
                if (num[i] == '0' && j>1) continue;

                long l1 = mystoi(num, 0, i);
                long l2 = mystoi(num, i, j);
                if (l1 >= INT32_MAX || l2 >= INT32_MAX) continue;

                ans.push_back(static_cast<int>(l1));
                ans.push_back(static_cast<int>(l2));
                bool ret = dfs(num, i+j, ans);
                if (ret) {
                    return ans;
                } else {
                    ans.clear();
                }
            }
        }
        return ans;
    }
};

int main(const int argc, const char* argv[]) {
    string s = "539834657215398346785398346991079669377161950407626991734534318677529701785098211336528511";
    auto sol = Solution();
    vector<int> ans = sol.splitIntoFibonacci(s);
    cout << '[';
    for (const int& e: ans) cout << e << ',';
    cout << "]\n";
    return 0;
}