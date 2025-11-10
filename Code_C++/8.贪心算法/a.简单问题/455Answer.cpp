class Solution {
    public:
        int findContentChildren(vector<int>& g, vector<int>& s) {
            // 对饼干和小孩的胃口进行排序
            sort(g.begin(), g.end());
            sort(s.begin(), s.end());
    
            // 从后往前遍历数组，记录多少个小孩能被满足
            int index = s.size() - 1; // 饼干数组的下标
            int cnt = 0;
    
            for (int i = g.size() - 1; i >= 0; i--) { // 遍历胃口
                // 注意：使用if来判断是否应该移动饼干
                // 如果喂不饱目前的小孩，饼干应该不动，移动向下一个胃口小的小孩
                if (index >= 0 && s[index] >= g[i]) { // 遍历饼干
                    cnt++;
                    index--;
                }
            }
    
            return cnt;
        }
    };