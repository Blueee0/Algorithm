class Solution {
public:
    bool backspaceCompare(string s, string t) {
        s = backspaceString(s);
        t = backspaceString(t);
        return s == t;
    }
private:
    string backspaceString(string str){
        int slowIndex = 0;
        for (int fastIndex = 0;fastIndex < str.size();fastIndex++){
            if(str[fastIndex] != '#'){
                str[slowIndex] = str[fastIndex];
                slowIndex++;
            }else if (str[fastIndex] == '#' & slowIndex > 0 ) {  // 确保 slowIndex 不会变为负数
                slowIndex--;
            }
        }
        return str.substr(0, slowIndex); // 提取 str 中从索引 0 开始、长度为 slowIndex 的子字符串
    }
};