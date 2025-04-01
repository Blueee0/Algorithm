#include <iostream>
#include <vector>
using namespace std;

int n;
vector<int> father(1001, 0);

// ���鼯��ʼ��
void init(){
    for(int i = 0; i <= n; i++){
        father[i] = i;
    }
}

// ���鼯��Ѱ���Ĺ���
int find(int u){
    if(u == father[u])
        return u;
    else
        return father[u] = find(father[u]);

}

// �ж� u �� v�Ƿ��ҵ�ͬһ����
bool isSame(int u, int v){
    u = find(u);
    v = find(v);
    return u == v;
}


// ��v->u �����߼��벢�鼯
void join(int u, int v){
    u = find(u);
    v = find(v);
    if(u == v)
        return;
    father[v] = u;
}

int main(){
    int s, t;
    cin >> n;
    init();
    for(int i = 0; i < n; i++){
        cin >> s >> t;
        if (isSame(s, t)) {
            cout << s << " " << t << endl;
            return 0;
        } else {
            join(s, t);
        }
    }
    return 0;
}