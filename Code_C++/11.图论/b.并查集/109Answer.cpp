#include <iostream>
#include <vector>
using namespace std;

int n;
vector<int> father(1001, 0);

void init(){
    for(int i = 0; i <= n; i++){
        father[i] = i;
    }
}

int find(int u){
    if(u == father[u])
        return u;
    else
        return father[u] = find(father[u]);
}

bool isSame(int u, int v) {
    u = find(u);
    v = find(v);
    return u == v;
}

void join(int u, int v){
    u = find(u);
    v = find(v);
    if(u == v)
        return;
    father[v] = u;
}

// 删一条边之后判断是不是树
bool isTreeAfterRemoveEdge(const vector<vector<int>>& edges, int deleteEdge) {
    init(); // 初始化并查集
    for (int i = 0; i < n; i++) {
        if (i == deleteEdge) 
            continue;
        if (isSame(edges[i][0], edges[i][1])) { // 构成有向环了，一定不是树
            return false;
        }
        join(edges[i][0], edges[i][1]);
    }
    return true;
}

// 在有向图里找到删除的那条边，使其变成树
void getRemoveEdge(const vector<vector<int>>& edges) {
    init(); // 初始化并查集
    for (int i = 0; i < n; i++) { // 遍历所有的边
        if (isSame(edges[i][0], edges[i][1])) { // 构成有向环了，就是要删除的边
            cout << edges[i][0] << " " << edges[i][1];
            return;
        } else {
            join(edges[i][0], edges[i][1]);
        }
    }
}

int main(){
    int s, t;
    vector<vector<int>> edges;
    cin >> n;
    vector<int> inDegree(n + 1, 0); // 记录节点入度
    for (int i = 0; i < n; i++) {
        cin >> s >> t;
        inDegree[t]++;
        edges.push_back({s, t});
    }

    vector<int> vec; // 记录入度为2的边（如果有的话就两条边）
    // 找入度为2的节点所对应的边，注意要倒序，因为优先删除最后出现的一条边
    for (int i = n - 1; i >= 0; i--) {
        if (inDegree[edges[i][1]] == 2) {
            vec.push_back(i);
        }
    }

    // 存在入度为2的节点
    if (vec.size() > 0) {
        // 放在vec里的边已经按照倒叙放的，所以这里就优先删vec[0]这条边
        if (isTreeAfterRemoveEdge(edges, vec[0])) {
            cout << edges[vec[0]][0] << " " << edges[vec[0]][1];
        } else {
            cout << edges[vec[1]][0] << " " << edges[vec[1]][1];
        }
        return 0;
    }

    // 处理有向环
    getRemoveEdge(edges);
    return 0;
}