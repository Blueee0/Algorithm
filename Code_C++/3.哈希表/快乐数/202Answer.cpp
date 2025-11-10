class Solution {
public:
    int getSum(int n) {
        int sum = 0;
        while (n) {
            sum += (n % 10) * (n % 10);
            n = n / 10;
        }
        return sum;
    }

    bool isHappy(int n) {
        unordered_set<int> sum_set;
        while (1) {
            int sum = getSum(n);
            if (sum == 1) {
                return true;
            }
            if (sum_set.find(sum) != sum_set.end()) {
                return false;
            } else {
                sum_set.insert(sum);
            }
            n = sum;
        }
    }
};