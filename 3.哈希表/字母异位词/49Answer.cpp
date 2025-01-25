class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> m;
        for (string& s : strs) {
            string sorted_s = s;
            ranges::sort(sorted_s);
            m[sorted_s].push_back(s); // sorted_s ��ͬ���ַ����ֵ�ͬһ��
        }

        vector<vector<string>> ans;
        ans.reserve(m.size()); // Ԥ����ռ�
        for (auto& [_, value] : m) {
            ans.push_back(value);
        }
        return ans;
    }
};