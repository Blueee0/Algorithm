#include <iostream>
#include <vector>
using namespace std;

int n;
vector<int> father(1001, 0);

// 并查集初始化
void init(){
    for(int i = 0; i <= n; i++){
        father[i] = i;
    }
}

// 并查集里寻根的过程
int find(int u){
    if(u == father[u])
        return u;
    else
        return father[u] = find(father[u]);

}

// 判断 u 和 v是否找到同一个根
bool isSame(int u, int v){
    u = find(u);
    v = find(v);
    return u == v;
}


// 将v->u 这条边加入并查集
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