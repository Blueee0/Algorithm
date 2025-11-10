class Solution {
public:
    void reverseString(vector<char>& s) {
        int len = s.size();
        for (int i = 0, j = len - 1; i < len / 2; i++, j--) {
            swap(s[i], s[j]);
        }
    }
};