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
            }else if (str[fastIndex] == '#' & slowIndex > 0 ) {  // ȷ�� slowIndex �����Ϊ����
                slowIndex--;
            }
        }
        return str.substr(0, slowIndex); // ��ȡ str �д����� 0 ��ʼ������Ϊ slowIndex �����ַ���
    }
};