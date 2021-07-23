#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * 有时候人们会用重复写一些字母来表示额外的感受，比如 "hello" -> "heeellooo", "hi" -> "hiii"。
 * 我们将相邻字母都相同的一串字符定义为相同字母组，例如："h", "eee", "ll", "ooo"。
 * 对于一个给定的字符串 S ，如果另一个单词能够通过将一些字母组扩张从而使其和 S 相同，
 * 我们将这个单词定义为可扩张的（stretchy）。扩张操作定义如下：选择一个字母组（包含字母 c ），然后往其中添加相同的字母 c 使其长度达到 3 或以上。
 * 
 * 例如，以 "hello" 为例，我们可以对字母组 "o" 扩张得到 "hellooo"，但是无法以同样的方法得到 "helloo" 因为字母组 "oo" 长度小于 3。
 * 此外，我们可以进行另一种扩张 "ll" -> "lllll" 以获得 "helllllooo"。如果 S = "helllllooo"，那么查询词 "hello" 是可扩张的，
 * 因为可以对它执行这两种扩张操作使得 query = "hello" -> "hellooo" -> "helllllooo" = S。
 * 
 * 输入一组查询单词，输出其中可扩张的单词数量。
 * 
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode-cn.com/problems/expressive-words
 * 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 * 
 * Solution:
 * 注意循环中的边界条件
*/

class Solution {
public:
    int expressiveWords(string s, vector<string>& words) {
        char pattern[100];
        uint8_t cidx = 0;
        uint8_t min_appr[100];
        uint8_t max_appr[100];
        // get pattern
        uint8_t sidx = 0;
        uint8_t eidx = 0;
        uint8_t slen = static_cast<uint8_t>(s.length());
        while (sidx < slen) {
            while (s[eidx] == s[sidx] && eidx < slen) eidx++;
            pattern[cidx] = s[sidx];
            max_appr[cidx] = eidx-sidx;
            min_appr[cidx] = max_appr[cidx] >= 3? 1:max_appr[cidx];
            cidx++;
            sidx = eidx;
        }
        for (uint8_t i=0; i<cidx; ++i) {
            cout << pattern[i] << '{' << int(min_appr[i]) << ',' << int(max_appr[i]) << '}' << endl;
        }
        
        int ret = 0;
        for (const string& w: words) {
            // do matching
            uint8_t widx = 0;
            sidx = 0;
            slen = static_cast<uint8_t>(w.length());
            bool ismatch = true;
            while (sidx < slen) {
                if (w[sidx] != pattern[widx]) {
                    ismatch = false;
                    break;
                };    // word not the same
                eidx = sidx;
                while (w[eidx] == w[sidx] && eidx<slen) ++eidx;
                if ((eidx-sidx) < min_appr[widx] || (eidx-sidx) > max_appr[widx]) {
                    ismatch = false;
                    break;
                };     // apperance not match
                sidx = eidx;
                ++widx;
            }
            ismatch &= (widx == cidx);
            ret += (ismatch? 1:0);
        }
        return ret;
    }
};

int main(int argc, const char* argv[]) {
    string S = "heeellooo";
    vector<string> words = {"heeelloooworld"};
    auto sol = Solution();
    int res = sol.expressiveWords(S, words);
    cout << "ans: " << res << endl;
    return 0;
}