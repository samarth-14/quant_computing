class Solution {
    // Helper function to calculate greatest common divisor
    long long gcd(long long a, long long b) {
        return std::gcd(a, b);
    }

    // Helper function to calculate least common multiple
    long long lcm(long long a, long long b) {
        if (a == 0 || b == 0) return 0;
        return (a / gcd(a, b)) * b;
    }

    // Returns the count of distinct amounts <= x made by single coin denominations
    long long countAmounts(long long x, const vector<int>& coins) {
        int n = coins.size();
        long long total = 0;

        // Iterate through all non-empty subsets of coins using bitmask
        for (int mask = 1; mask < (1 << n); ++mask) {
            long long currentLcm = 1;
            int bitCount = 0;
            bool overflow = false;

            for (int i = 0; i < n; ++i) {
                if ((mask >> i) & 1) {
                    bitCount++;
                    currentLcm = lcm(currentLcm, coins[i]);
                    if (currentLcm > x) {
                        overflow = true;
                        break;
                    }
                }
            }

            if (overflow) continue;

            if (bitCount % 2 == 1) {
                total += x / currentLcm;
            } else {
                total -= x / currentLcm;
            }
        }

        return total;
    }

public:
    long long findKthSmallest(vector<int>& coins, int k) {
        long long low = 1;
        long long minCoin = *min_element(coins.begin(), coins.end());
        long long high = minCoin * k;
        long long ans = high;

        while (low <= high) {
            long long mid = low + (high - low) / 2;

            if (countAmounts(mid, coins) >= k) {
                ans = mid;
                high = mid - 1; // Try to find a smaller valid value
            } else {
                low = mid + 1;  // Need a larger value
            }
        }

        return ans;
    }
};