class Solution {
    public:
        static bool cmp(int a, int b) { 
            return abs(a) > abs(b); 
        }
    
        int largestSumAfterKNegations(vector<int>& A, int K) {
            // �����򣬰�����ֵ�Ӵ�С����
            sort(A.begin(), A.end(), cmp);
    
            // ���и���ʱ���ȶԾ���ֵ���ĸ���ȡ��
            for (int i = 0; i < A.size(); i++) {
                if (A[i] < 0 && K > 0) {
                    A[i] *= -1;
                    K--;
                }
            }
    
            // �����ʱK��ʣ����KΪ�������Ͱ���С����ȡ��һ�ξͿ���
            // ���KΪż��������С��������ȡ�����൱��û��
            if (K % 2 == 1)
                A[A.size() - 1] *= -1;
    
            // ��¼���result
            int result = 0;
            for (int a : A)
                result += a;
            return result;
        }
    };