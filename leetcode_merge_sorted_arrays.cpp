//
// Created by Arindam on 24/09/2024.
//

#include <vector>
#include <print>
#include <algorithm>
#include <random>

using std::vector;

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n, vector<int>& merged) {
        int l = m +  n;
        int i = 0, j = 0, k = 0;
        while (i < l) {
            if (j == m) {
                while (i < l) {
                    merged[i] = nums2[k];
                    i++;
                    k++;
                }
            } else if (k == n) {
                while (i < l) {
                    merged[i] = nums1[j];
                    i++;
                    j++;
                }
            } else if (nums1[j] <= nums2[k]) {
                merged[i] = nums1[j];
                i++;
                j++;
            } else {
                merged[i] = nums2[k];
                i++;
                k++;
            }
        }

    }
};

int main() {
    Solution s;

    // Random number generator setup
    std::random_device rd;   // Seed generator
    std::mt19937 gen(rd());  // Mersenne Twister RNG
    std::uniform_int_distribution<> dist(1, 100);  // Range [1, 10000]

    vector<int> nums1(10), nums2(10), merged(20);
    // Populate the vectors with random positive integers
    for (int& num : nums1) {
        num = dist(gen);  // Assign a random number to each element
    }
    for (int& num : nums2) {
        num = dist(gen);  // Assign a random number to each element
    }
    std::sort(nums1.begin(), nums1.end());
    std::sort(nums2.begin(), nums2.end());
    s.merge(nums1, 10, nums2, 10, merged);

    std::print("{{ ");
    for (int& num : merged) {
        std::print("{} ", num);
    }
    std::print("}}\n");

    return 0;
}