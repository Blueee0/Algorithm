class Solution {
public:
    void getNext(int* next, const string& s) {
        // jǰ׺ĩβ��i��׺ĩβ
        int j = 0, i = 1;
        next[0] = 0;

        // �ж�����ǰ��׺�����Ҹ���next����
        for (i = 1; i < s.size(); i++) {
            // ��ǰ��׺�����ʱ������j��j=0ʱ�������ˣ�
            while (j > 0 && s[i] != s[j])
                j = next[j - 1];

            // ��ǰ��׺���ʱ������j
            if (s[i] == s[j])
                j++;

            // ����next����
            next[i] = j;
        }
    }

    int strStr(string haystack, string needle) {
        // ����ģʽ������Ϊ0�����
        if (needle.size() == 0) {
            return 0;
        }

        // ��ȡǰ׺��
        vector<int> next(needle.size());
        getNext(&next[0], needle);

        int j = 0;
        for (int i = 0; i < haystack.size(); i++) {
            // ����ַ�����ƥ�䣬����ǰ׺���ȡ���ص�λ��
            while (j > 0 && haystack[i] != needle[j]) {
                j = next[j - 1];
            }
            // ����ַ���ƥ�䣬�����ƶ�j
            if (haystack[i] == needle[j]) {
                j++;
            }
            // ����ַ���ƥ����ϣ����ص�һ��ƥ�����±�
            if (j == needle.size()) {
                return (i - needle.size() + 1);
            }
        }
        return -1;
    }
};