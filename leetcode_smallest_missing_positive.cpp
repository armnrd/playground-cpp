//
// Created by Arindam on 24/09/2024.
//

#include <vector>
#include <print>

using std::vector;

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        for (int proc_idx = 0; proc_idx < nums.size(); proc_idx++) {
            if (nums[proc_idx] > 0 && nums[proc_idx] <= nums.size()) {
                if (nums[proc_idx] != proc_idx + 1) {
                    auto new_idx = nums[proc_idx] - 1;
                    nums[proc_idx] = -1;
                    while (nums[new_idx] != new_idx + 1) {
                        auto new_val = nums[new_idx];
                        nums[new_idx] = new_idx + 1;
                        if (new_val > 0 && new_val <= nums.size()) {
                            new_idx = new_val - 1;
                        } else {
                            break;
                        }
                    }
                }
            } else {
                nums[proc_idx] = -1;
            }
        }
        int scan_idx = 0;
        while (scan_idx < nums.size()) {
            if (nums[scan_idx] == -1) {
                break;
            }
            scan_idx++;
        }
        return scan_idx + 1;
    }
};

int main() {
    Solution s;
    vector<int> nums {1, 2, 0, 3};
    std::print("{}", s.firstMissingPositive(nums));
    return 0;
}
