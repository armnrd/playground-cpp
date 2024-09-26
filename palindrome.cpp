//
// Created by Arindam on 23/09/2024.
//

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Function to find the longest palindromic substring
string longest_palindrome(const string& s) {
    int n = s.size();
    if (n == 0) return "";

    // Create a 2D DP table to store whether substring s[i...j] is a palindrome
    vector<vector<bool>> dp(n, vector<bool>(n, false));

    // Every single character is a palindrome
    int start = 0, max_length = 1;
    for (int i = 0; i < n; ++i)
        dp[i][i] = true;

    // Check for 2-character palindromes
    for (int i = 0; i < n - 1; ++i) {
        if (s[i] == s[i + 1]) {
            dp[i][i + 1] = true;
            start = i;
            max_length = 2;
        }
    }

    // Check for palindromes of length 3 and more
    for (int len = 3; len <= n; ++len) {
        for (int i = 0; i < n - len + 1; ++i) {
            int j = i + len - 1;  // Ending index of the current substring

            // Check if the current substring s[i...j] is a palindrome
            if (s[i] == s[j] && dp[i + 1][j - 1]) {
                dp[i][j] = true;

                if (len > max_length) {
                    start = i;
                    max_length = len;
                }
            }
        }
    }

    // Return the longest palindromic substring
    return s.substr(start, max_length);
}

int main() {
    string s;
    cout << "Enter a string: ";
    cin >> s;

    string result = longest_palindrome(s);
    cout << "The longest palindromic substring is: " << result << endl;

    return 0;
}
