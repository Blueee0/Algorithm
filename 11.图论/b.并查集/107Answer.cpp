#include <iostream>
#include <vector>
using namespace std;

int n;
vector<int> father = vector<int> (101, 0);

// ���鼯��ʼ��
void init() {
    for (int i = 0; i <= n; ++i) {
        father[i] = i;
    }
}

// ���鼯��Ѱ���Ĺ���
int find(int u) {
    if (u == father[u]) return u;
    else return father[u] = find(father[u]); // ·��ѹ��
}

// �ж� u �� v�Ƿ��ҵ�ͬһ����
bool isSame(int u, int v) {
    u = find(u);
    v = find(v);
    return u == v;
}

// ��v->u �����߼��벢�鼯
void join(int u, int v) {
    u = find(u); // Ѱ��u�ĸ�
    v = find(v); // Ѱ��v�ĸ�
    if (u == v) return ; // ������ָ���ͬ����˵����һ�����ϣ����������ڵ�����ֱ�ӷ���
    father[v] = u;
}

int main(){
    int m, u, v, source, destination;
    cin >> n >> m;
    init();
    for(int i = 0; i < m; i++){
        cin >> u >> v;
        join(u, v);
    }

    cin >> source >> destination;
    if (isSame(source, destination)) 
        cout << 1 << endl;
    else 
        cout << 0 << endl;

    return 0;
}