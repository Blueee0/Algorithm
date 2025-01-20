class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        int i=0,ans = 0;
        unordered_map<int, int> cnt; // ���ڼ�¼�������ĸ���

        for(int j=0; j<fruits.size();j++){
            cnt[fruits[j]]++;
            while(cnt.size() > 2){
                int out = fruits[i];
                cnt[out]--; // fruits[i] �뿪����
                if (cnt[out] == 0) {
                    cnt.erase(out);
                }
                i++;
            }
            ans = max(ans, j - i + 1);
        }
        return ans;
    }
};