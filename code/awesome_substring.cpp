#include <string>
#include <algorithm>
#include <unordered_map>
#include <iostream>

using namespace std;

/**
 * Given a string s. An awesome substring is a non-empty substring of s such that we can make any number of swaps in order to make it palindrome.
 * Return the length of the maximum length awesome substring of s.
 * 
 * Solution:
 * https://blog.csdn.net/qq_38650028/article/details/107898638
*/

class Solution {
private:
// NOTE init with {{0, -1}}!
unordered_map<int, int> mask2idx = unordered_map<int, int>({{0, -1}});

public:
    int longestAwesome(string s) {
        int longest_subs = 0;
        int mask = 0;
        for (int i=0; i<s.length(); ++i) {
            const char& c = s[i];
            mask = mask xor (1 << (c - '0'));
            if (mask2idx.find(mask) == mask2idx.end()) {
                mask2idx[mask] = i;
            } else {
                // find the same mask, find the longest length
                longest_subs = max(i-mask2idx[mask], longest_subs);
            }
            // check whether only one bit is 1
            for (int j=0; j<10; ++j) {
                int tmp_mask = mask xor (1<<j);
                if (mask2idx.find(tmp_mask) != mask2idx.end()) {
                    longest_subs = max(i-mask2idx[tmp_mask], longest_subs);
                }
            }
        }
        return longest_subs;
    }
};

int main(int argc, const char* argv[]) {
    Solution solution = Solution();
    string input = string("32424134567898543456787654345678643456784323456784345675");
    int ans = solution.longestAwesome(input);
    cout << "answer is: " << ans << endl;
}