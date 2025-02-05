class Solution {
public:
    // ��ת�ַ���s������ұյ�����[start, end]
    void reverse(string& s, int start, int end) {
        for (int i = start, j = end; i < j; i++, j--) {
            swap(s[i], s[j]);
        }
    }

    void removeExtraSpaces(string& s) { // ȥ���ո�
        int slow = 0,
            fast = 0; // fastָ�������ĿҪ�����ĸ��slowָ����Ҫ���ĵĵط�
        for (fast = 0; fast < s.size(); fast++) {
            if (s[fast] != ' ') {
                if (slow != 0) { // ���slowָ���һ�����ʣ�����Ҫ���ո�
                    s[slow] = ' ';
                    slow++;
                }
                while (fast < s.size() && s[fast] != ' ') {
                    s[slow] = s[fast];
                    fast++;
                    slow++;
                }
            }
        }
        s.resize(slow); // slow�Ĵ�С��Ϊȥ������ո��Ĵ�С��
    }

    string reverseWords(string s) {
        removeExtraSpaces(
            s); // ȥ������ո񣬱�֤����֮��ֻ֮��һ���ո����ַ�����βû�ո�
        reverse(s, 0, s.size() - 1);
        int start = 0; // removeExtraSpaces��֤��һ�����ʵĿ�ʼ�±�һ����0��
        for (int i = 0; i <= s.size(); ++i) {
            if (i == s.size() ||
                s[i] == ' ') { // ����ո���ߴ�β��˵��һ�����ʽ��������з�ת��
                reverse(s, start, i - 1); // ��ת��ע��������ұ� []�ķ�ת��
                start = i + 1; // ������һ�����ʵĿ�ʼ�±�start
            }
        }
        return s;
    }
};