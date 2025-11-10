class Solution {
    public:
        static bool cmp(int a, int b) { 
            return abs(a) > abs(b); 
        }
    
        int largestSumAfterKNegations(vector<int>& A, int K) {
            // 先排序，按绝对值从大到小排序
            sort(A.begin(), A.end(), cmp);
    
            // 当有负数时，先对绝对值最大的负数取反
            for (int i = 0; i < A.size(); i++) {
                if (A[i] < 0 && K > 0) {
                    A[i] *= -1;
                    K--;
                }
            }
    
            // 如果此时K还剩，且K为奇数，就把最小的数取反一次就可以
            // 如果K为偶数，对最小的数反复取反，相当于没变
            if (K % 2 == 1)
                A[A.size() - 1] *= -1;
    
            // 记录结果result
            int result = 0;
            for (int a : A)
                result += a;
            return result;
        }
    };