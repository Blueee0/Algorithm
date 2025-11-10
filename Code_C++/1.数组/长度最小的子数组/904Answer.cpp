class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        int i=0,ans = 0;
        unordered_map<int, int> cnt; // 用于记录两种数的个数

        for(int j=0; j<fruits.size();j++){
            cnt[fruits[j]]++;
            while(cnt.size() > 2){
                int out = fruits[i];
                cnt[out]--; // fruits[i] 离开窗口
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