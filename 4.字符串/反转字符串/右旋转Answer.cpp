#include <iostream>
#include <algorithm>
using namespace std;

int main(){
    int n;
    string s;
    cin >> n;
    cin >> s;
    
    int length = s.size();  // ��ȡ�ַ�������
    reverse(s.begin(),s.end());
    reverse(s.begin(),s.begin()+n);
    reverse(s.begin()+n,s.end());
    
    cout << s;
}