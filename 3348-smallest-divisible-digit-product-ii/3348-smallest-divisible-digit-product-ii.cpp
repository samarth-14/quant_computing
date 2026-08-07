#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class Solution {
    int factorDigit[10][4] = {
        {0, 0, 0, 0}, {0, 0, 0, 0}, {1, 0, 0, 0}, // 0, 1, 2
        {0, 1, 0, 0}, {2, 0, 0, 0}, {0, 0, 1, 0}, // 3, 4, 5
        {1, 1, 0, 0}, {0, 0, 0, 1}, {3, 0, 0, 0}, // 6, 7, 8
        {0, 2, 0, 0}                             // 9
    };

    // Calculate minimum digits needed to form the required prime factors
    int minDigitsNeeded(const vector<int>& req) {
        int r2 = max(0, req[0]);
        int r3 = max(0, req[1]);
        int r5 = max(0, req[2]);
        int r7 = max(0, req[3]);

        int count = r5 + r7 + (r3 + 1) / 2; // 5s, 7s, and 9s (from 3s)
        int rem2 = r2;
        if (r3 % 2 != 0) {
            rem2 = max(0, rem2 - 1); // Combine 1 extra 3 with a 2 to make 6
        }
        count += (rem2 + 2) / 3; // 8s (from 2s)
        return count;
    }

    // Generate the minimal string for missing prime factors
    string buildMinimalSuffix(vector<int> req, int targetLen) {
        vector<int> digits;
        int r2 = max(0, req[0]);
        int r3 = max(0, req[1]);
        int r5 = max(0, req[2]);
        int r7 = max(0, req[3]);

        for (int i = 0; i < r7; ++i) digits.push_back(7);
        for (int i = 0; i < r5; ++i) digits.push_back(5);

        while (r3 >= 2) { digits.push_back(9); r3 -= 2; }
        while (r2 >= 3) { digits.push_back(8); r2 -= 3; }

        if (r3 > 0 && r2 > 0) { digits.push_back(6); r3--; r2--; }
        else if (r3 > 0) { digits.push_back(3); r3--; }

        if (r2 == 2) { digits.push_back(4); }
        else if (r2 == 1) { digits.push_back(2); }

        sort(digits.begin(), digits.end());

        string res(targetLen - digits.size(), '1');
        for (int d : digits) res += to_string(d);
        return res;
    }

public:
    string smallestNumber(string num, long long t) {
        vector<int> target(4, 0);
        long long temp = t;
        int primes[4] = {2, 3, 5, 7};
        
        for (int i = 0; i < 4; ++i) {
            while (temp % primes[i] == 0) {
                target[i]++;
                temp /= primes[i];
            }
        }
        if (temp > 1) return "-1"; // Contains invalid prime factors

        int n = num.length();
        int firstZero = num.find('0');
        
        // Count factors in original prefix
        vector<vector<int>> pref(n + 1, vector<int>(4, 0));
        for (int i = 0; i < n; ++i) {
            int d = num[i] - '0';
            pref[i + 1] = pref[i];
            if (d > 0) {
                for (int k = 0; k < 4; ++k) pref[i + 1][k] += factorDigit[d][k];
            }
        }

        // Check if num itself is valid
        if (firstZero == string::npos) {
            bool valid = true;
            for (int k = 0; k < 4; ++k) {
                if (pref[n][k] < target[k]) { valid = false; break; }
            }
            if (valid) return num;
        }

        int limitZero = (firstZero == string::npos) ? n : firstZero;

        // Try modifying digit from right to left
        for (int i = n - 1; i >= 0; --i) {
            if (i > limitZero) continue; // Can't keep prefix after first 0

            int origDigit = num[i] - '0';
            int spaceRemaining = n - 1 - i;

            for (int bigger = origDigit + 1; bigger <= 9; ++bigger) {
                vector<int> req(4);
                for (int k = 0; k < 4; ++k) {
                    req[k] = target[k] - pref[i][k] - factorDigit[bigger][k];
                }

                if (minDigitsNeeded(req) <= spaceRemaining) {
                    string prefix = num.substr(0, i) + to_string(bigger);
                    string suffix = buildMinimalSuffix(req, spaceRemaining);
                    return prefix + suffix;
                }
            }
        }

        // Extend string length if no solution found with length n
        int extLen = max((int)n + 1, minDigitsNeeded(target));
        return buildMinimalSuffix(target, extLen);
    }
};