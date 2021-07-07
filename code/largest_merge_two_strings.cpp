#include <iostream>
#include <string>

using namespace std;

/**
 * You are given two strings word1 and word2. You want to construct a string merge in the following way: while either word1 or word2 are non-empty, choose one of the following options:
 * If word1 is non-empty, append the first character in word1 to merge and delete it from word1.
 * For example, if word1 = "abc" and merge = "dv", then after choosing this operation, word1 = "bc" and merge = "dva".
 * If word2 is non-empty, append the first character in word2 to merge and delete it from word2.
 * For example, if word2 = "abc" and merge = "", then after choosing this operation, word2 = "bc" and merge = "a".
 * Return the lexicographically largest merge you can construct.
 * A string a is lexicographically larger than a string b (of the same length) if in the first position where a and b differ, a has a character strictly larger than the corresponding character in b. For example, "abcd" is lexicographically larger than "abcc" because the first position they differ is at the fourth character, and d is greater than c.
 * 
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode-cn.com/problems/largest-merge-of-two-strings
 * 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 * 
 * Solution:
 * 用std string compare会快一点
*/

class Solution {
public:
    string largestMerge(string word1, string word2) {
        string ret;
        int l1 = 0;
        int l2 = 0;
        while (l1 < word1.size() && l2 < word2.size()) {
            if (word1[l1] > word2[l2]) {
                ret.push_back(word1[l1++]);
            } else if (word1[l1] < word2[l2]) {
                ret.push_back(word2[l2++]);
            } else {
                // compare
            #ifdef method1
                int tmpl1 = l1;
                int tmpl2 = l2;
                bool l1ltl2;
                while (tmpl1 < word1.size() && tmpl2 < word2.size()) {
                    if (word1[tmpl1] == word2[tmpl2]) {
                        ++tmpl2;
                        ++tmpl1;
                    } else {
                        l1ltl2 = (word1[tmpl1] > word2[tmpl2]);
                        break;
                    }
                }
                if (tmpl2 >= word2.size() || tmpl1 >= word1.size()) {
                    l1ltl2 = (tmpl1 < word1.size());
                }
                // op
                if (l1ltl2) {
                    ret.push_back(word1[l1++]);
                } else {
                    ret.push_back(word2[l2++]);
                }
            #else
                // faster
                int l1ltl2 = word1.compare(l1, word1.size()-l1, word2, l2, word2.size()-l2);
                if (l1ltl2 > 0) {
                    ret.push_back(word1[l1++]);
                } else {
                    ret.push_back(word2[l2++]);
                }
            #endif
            }
        }
        while (l1 < word1.size()) {
            ret.push_back(word1[l1++]);
        }
        while (l2 < word2.size()) {
            ret.push_back(word2[l2++]);
        }
        return ret;
    }
};

int main(int argc, const char* argv[]) {
    string word1 = "guguuuuuuuuuuuuuuguguuuuguug";
    string word2 = "gguggggggguuggguugggggg";
    auto sol = Solution();
    string ret = sol.largestMerge(word1, word2);
    cout << "ans: " << ret << endl;
    cout << "rig: " << "guguuuuuuuuuuuuuuguguuuuguugguggggggguuggguuggggggg" << endl;
}