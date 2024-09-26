//
// Created by Arindam on 25/09/2024.
//

#include <print>
#include <limits>

class Solution {
public:
    int mySqrt(int x) {
        switch (x) {
            case 0:
                return 0;
            case 1:
                return 1;
            case 2:
                return 1;
            case 3:
                return 1;
            case 4:
                return 2;
        }
        int v = x;
        int r = 0;

        int search_start = 1, search_end, search_cand;
        uint64_t square, square1;
        if (x > 2000) {
            while (v >>= 1) {
                r++;
            }
            r = r / 2 - 1;
            search_end = x >> r;
        } else {
            search_end = x;
        }
        while (true) {
            search_cand = (search_start + search_end) / 2;
            square = static_cast<uint64_t>(search_cand) * search_cand;
            square1 = static_cast<uint64_t>(search_cand + 1) * (search_cand + 1);
            if (square <= x) {
                if (square == x || square1 > x) {
                    return search_cand;
                }
                search_start = search_cand + 1;
            } else {
                search_end = search_cand - 1;
            }
        }
    }
};

int main() {
    Solution s;
    std::print("{}", s.mySqrt(INT_MAX));

    return 0;
}