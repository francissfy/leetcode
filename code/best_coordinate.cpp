#include <vector>
#include <iostream>
#include <set>
#include <map>

using namespace std;

/**
 * 给你一个数组 towers 和一个整数 radius ，数组中包含一些网络信号塔，
 * 其中 towers[i] = [xi, yi, qi] 表示第 i 个网络信号塔的坐标是 (xi, yi) 且信号强度参数为 qi 。
 * 所有坐标都是在  X-Y 坐标系内的 整数 坐标。两个坐标之间的距离用 欧几里得距离 计算。
 * 整数 radius 表示一个塔 能到达 的 最远距离 。如果一个坐标跟塔的距离在 radius 以内，那么该塔的信号可以到达该坐标。
 * 在这个范围以外信号会很微弱，所以 radius 以外的距离该塔是 不能到达的 。
 * 
 * 如果第 i 个塔能到达 (x, y) ，那么该塔在此处的信号为 [qi/(1+d)]，其中 d 是塔跟此坐标的距离。
 * 一个坐标的 网络信号 是所有 能到达 该坐标的塔的信号强度之和。
 * 请你返回 网络信号 最大的整数坐标点。如果有多个坐标网络信号一样大，请你返回字典序最小的一个坐标。
 * 
 * 注意：
 * 
 * 坐标 (x1, y1) 字典序比另一个坐标 (x2, y2) 小：要么 x1 < x2 ，要么 x1 == x2 且 y1 < y2 。
 * [val] 表示小于等于 val 的最大整数（向下取整函数）。
 * 
 * 来源：力扣（LeetCode）
 * 链接：https://leetcode-cn.com/problems/coordinate-with-maximum-network-quality
 * 著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 * 
 * Solution:
 * 貌似直接遍历就好了 不用先确定范围 不然耗时反而比较长
*/

class Solution {
public:
    vector<int> bestCoordinate(vector<vector<int>>& towers, int radius) {
        auto point2power = map<pair<int, int>, int>();
        // calculate the range towers can cover
        for (size_t i=0; i<towers.size(); ++i) {
            const vector<int>& tow = towers[i];
            // iter through grid
            const int& tx = tow[0];
            const int& ty = tow[1];
            for (int x=tx-radius; x<=tx+radius; ++x) {
                for (int y=ty-radius; y<=ty+radius; ++y) {
                    // calcualate distance
                    double d = sqrt(static_cast<double>((x-tx)*(x-tx)+(y-ty)*(y-ty)));
                    if (d>radius) continue;
                    // calculate signal power
                    int spower = static_cast<int>(static_cast<double>(tow[2])/(1.0+d));
                    // add to point set
                    auto p = pair<int, int>({x, y});
                    if (point2power.find(p) != point2power.end()) {
                        point2power[p] += spower;
                    } else {
                        point2power[p] = spower;
                    }
                }
            }
        }

        auto ret = pair<int, int>({0, 0});
        int max_signal = 0;
        for (auto iter=point2power.begin(); iter != point2power.end(); ++iter) {
            const auto& ppair = *iter;
            // cout << "(" << get<0>(ppair.first) << ", " << get<1>(ppair.first) << "), power: " << ppair.second << endl;

            if (ppair.second > max_signal) {
                max_signal = ppair.second;
                ret = ppair.first;
            } else if (ppair.second == max_signal && max_signal>0) ret = min(ret, ppair.first);
        }
        return vector<int>({get<0>(ret), get<1>(ret)});
    }
};

int main(const int argc, const char* argv[]) {
    auto ps = vector<vector<int>>({{42, 0, 0}});
    auto sol = Solution();
    auto ans = sol.bestCoordinate(ps, 7);
    cout << "x: " << ans[0] << ", y: " << ans[1] << endl;
    return 0;
}