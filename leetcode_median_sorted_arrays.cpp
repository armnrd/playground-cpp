#include <cstdio>
#include <vector>

using std::vector;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // select array with larger median
        auto nums_lrg = nums1, nums_sml = nums2;
        if ((nums1[(nums1.size() - 1) / 2] > nums2[(nums2.size() - 1) / 2])) { // nums1 has larger median
            nums_lrg = nums1;
        } else { // nums2 has median >= median of nums1
            nums_lrg = nums2;
        }
        auto size_lrg = nums_lrg.size(), size_sml = nums_sml.size();
        auto merged_even = (size_sml + size_lrg) % 2 == 0;
        auto cov_idx_target = (size_sml + size_lrg - 1) / 2; // the target for the end index of elements covered by the selection
        vector<int>::size_type sel_idx_start = 0, sel_idx_end = size_lrg - 1, sel_idx = (sel_idx_start + sel_idx_end) / 2;

        // see if using just one array is sufficient
        if (nums_lrg[0] >= nums_sml.back()) { // nums_sml and nums_lrg are consecutive
            if (cov_idx_target <= size_sml - 1) { // median is in nums_sml
                return 0;
            } else { // median is in nums_lrg
                sel_idx = cov_idx_target - size_sml;
            }
        } else {
            // condition: more than median and less than end in small array, and less than median and more than start in large array
            // main search logic
            while (true) {
                // in case of repeating elements, can the chosen element in nums_lrg be the median?
                auto cov_idx_sml_target = (cov_idx_target + 1) - (sel_idx + 1) - 1;
                if (cov_idx_sml_target >= size_sml - 1) { // all elements in nums_sml to be included
                    if (cov_idx_sml_target == size_sml - 1 && nums_sml[cov_idx_sml_target] <= nums_lrg[sel_idx]) { // nums_lrg[sel_idx] is the median
                        break;
                    } else { //sel_idx is too large
                        sel_idx_end = sel_idx - 1;
                    }
                } else if (nums_sml[cov_idx_sml_target] <= nums_lrg[sel_idx]) {
                    if (nums_sml[cov_idx_sml_target + 1] >= nums_lrg[sel_idx]) { // nums_lrg[sel_idx] is the median
                        break;
                    } else { // nums_sml[cov_idx_sml_target + 1] is strictly smaller; need to pick smaller sel_idx;
                        sel_idx_end = sel_idx - 1;
                    }
                } else if (nums_sml[cov_idx_sml_target] > nums_lrg[sel_idx]) { // nums_sml[cov_idx_sml_target] strictly larger; need to pick larger sel_idx;
                    sel_idx_start = sel_idx + 1;
                }
                sel_idx = (sel_idx_start + sel_idx_end) / 2;
            }
        }

        if (merged_even) {
            // return average of values at sel_idx an sel_idx + 1
            return (static_cast<double> (nums_lrg[sel_idx]) + nums_lrg[sel_idx + 1]) / 2;
        } else {
            return nums_lrg[sel_idx];
        }
    }
};

int main() {
    Solution s;
    vector<int> nums1 {0, 1, 2}, nums2 {3, 5, 7};
    auto median = s.findMedianSortedArrays(nums1, nums2);
    printf("%f", median);
    return 0;
}
