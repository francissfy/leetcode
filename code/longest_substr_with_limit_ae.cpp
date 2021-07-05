#include <vector>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <deque>

using namespace std;

/**
 * 给你一个整数数组 nums ，和一个表示限制的整数 limit，请你返回最长连续子数组的长度，该子数组中的任意两个元素之间的绝对差必须小于或者等于 limit
 * 如果不存在满足条件的子数组，则返回 0
 * 
 * Solution:
 * 单调队列+滑窗
 * https://www.jianshu.com/p/e59d51e1eef5
*/

class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        int longest_subs = 0;
        
        // maintain max value
        deque<int> des_deque = deque<int>({});
        // maintain min value
        deque<int> inc_deque = deque<int>({});

        int ridx = 0;
        int lidx = 0;

        while (ridx < static_cast<int>(nums.size())){
            // add element to deque
            while (!des_deque.empty() && nums[des_deque.back()]<nums[ridx]) {des_deque.pop_back();}
            des_deque.push_back(ridx);

            while (!inc_deque.empty() && nums[inc_deque.back()]>nums[ridx]) {inc_deque.pop_back();}
            inc_deque.push_back(ridx);

            // satisfy limit?
            while (nums[des_deque.front()] - nums[inc_deque.front()] > limit) {
                ++lidx;
                if (!des_deque.empty() && des_deque.front() < lidx) {des_deque.pop_front();}
                if (!inc_deque.empty() && inc_deque.front() < lidx) {inc_deque.pop_front();}
            }
            longest_subs = max(longest_subs, ridx-lidx+1);
            ++ridx;
        }
        return longest_subs;
    }
};

int main(int argc, const char* argv[]) {
    vector<int> data = vector<int>({1, 8, 6, 10});
    Solution sol = Solution();
    int ans = sol.longestSubarray(data, 8);
    cout << "answer is: " << ans << endl;
    return 0;
} 
