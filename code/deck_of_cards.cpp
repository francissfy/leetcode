#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

/**
 * In a deck of cards, each card has an integer written on it.
 * Return true if and only if you can choose X >= 2 such that it is possible to split the entire deck into 1 or more groups of cards, where:
 * 
 * Each group has exactly X cards.
 * All the cards in each group have the same integer.
 * 
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode-cn.com/problems/x-of-a-kind-in-a-deck-of-cards
 * 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 * 
 * Solution:
 * GCD of appearances
*/

class Solution {
public:
    int gcd(const int& a, const int& b) {
        if (b == 0) return a;
        return gcd(b, a%b);
    }
    bool hasGroupsSizeX(vector<int>& deck) {
        auto digit2times = unordered_map<int, int>();
        for (const auto& v: deck) {
            if (digit2times.find(v) == digit2times.end()){
                digit2times[v] = 1;
            } else {
                digit2times[v] += 1;
            }
        }
        int gcdv = 0;
        for (auto& p: digit2times) {
            if (gcdv == 0) gcdv = get<1>(p);
            else gcdv = gcd(gcdv, get<1>(p));
        }
        return gcdv >= 2;
    }
};