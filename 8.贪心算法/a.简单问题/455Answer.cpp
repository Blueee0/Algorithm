class Solution {
    public:
        int findContentChildren(vector<int>& g, vector<int>& s) {
            // �Ա��ɺ�С����θ�ڽ�������
            sort(g.begin(), g.end());
            sort(s.begin(), s.end());
    
            // �Ӻ���ǰ�������飬��¼���ٸ�С���ܱ�����
            int index = s.size() - 1; // ����������±�
            int cnt = 0;
    
            for (int i = g.size() - 1; i >= 0; i--) { // ����θ��
                // ע�⣺ʹ��if���ж��Ƿ�Ӧ���ƶ�����
                // ���ι����Ŀǰ��С��������Ӧ�ò������ƶ�����һ��θ��С��С��
                if (index >= 0 && s[index] >= g[i]) { // ��������
                    cnt++;
                    index--;
                }
            }
    
            return cnt;
        }
    };