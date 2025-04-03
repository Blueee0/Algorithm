#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// l,r为 边两边的节点，val为边的数值
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

    // 按边的权值对边进行从小到大排序
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