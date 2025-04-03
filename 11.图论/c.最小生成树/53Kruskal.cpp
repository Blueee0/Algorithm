#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// l,rΪ �����ߵĽڵ㣬valΪ�ߵ���ֵ
struct Edge {
    int l, r, val;
};

int n = 10001;
vector<int> father(10001, -1);

void init() {
    for (int i = 0; i < n; ++i) {
        father[i] = i;
    }
}

int find(int u) {
    if(u == father[u])
        return u;
    else
        return father[u] = find(father[u]);
}

void join(int u, int v) {
    u = find(u);
    v = find(v);
    if (u == v) 
        return;
    father[v] = u;
}

int main(){

    int v, e;
    int v1, v2, val;
    vector<Edge> edges;
    cin >> v >> e;
    while (e--) {
        cin >> v1 >> v2 >> val;
        edges.push_back({v1, v2, val});
    }

    // ���ߵ�Ȩֵ�Ա߽��д�С��������
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.val < b.val;
    });

    init();
    int result_val = 0;
    for (Edge edge : edges) {
        int x = find(edge.l);
        int y = find(edge.r);
        if (x != y) {
            result_val += edge.val;
            join(x, y);
        }
    }
    cout << result_val << endl;
    return 0;
}