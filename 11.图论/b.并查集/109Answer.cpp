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

// ɾһ����֮���ж��ǲ�����
bool isTreeAfterRemoveEdge(const vector<vector<int>>& edges, int deleteEdge) {
    init(); // ��ʼ�����鼯
    for (int i = 0; i < n; i++) {
        if (i == deleteEdge) 
            continue;
        if (isSame(edges[i][0], edges[i][1])) { // ���������ˣ�һ��������
            return false;
        }
        join(edges[i][0], edges[i][1]);
    }
    return true;
}

// ������ͼ���ҵ�ɾ���������ߣ�ʹ������
void getRemoveEdge(const vector<vector<int>>& edges) {
    init(); // ��ʼ�����鼯
    for (int i = 0; i < n; i++) { // �������еı�
        if (isSame(edges[i][0], edges[i][1])) { // ���������ˣ�����Ҫɾ���ı�
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
    vector<int> inDegree(n + 1, 0); // ��¼�ڵ����
    for (int i = 0; i < n; i++) {
        cin >> s >> t;
        inDegree[t]++;
        edges.push_back({s, t});
    }

    vector<int> vec; // ��¼���Ϊ2�ıߣ�����еĻ��������ߣ�
    // �����Ϊ2�Ľڵ�����Ӧ�ıߣ�ע��Ҫ������Ϊ����ɾ�������ֵ�һ����
    for (int i = n - 1; i >= 0; i--) {
        if (inDegree[edges[i][1]] == 2) {
            vec.push_back(i);
        }
    }

    // �������Ϊ2�Ľڵ�
    if (vec.size() > 0) {
        // ����vec��ı��Ѿ����յ���ŵģ��������������ɾvec[0]������
        if (isTreeAfterRemoveEdge(edges, vec[0])) {
            cout << edges[vec[0]][0] << " " << edges[vec[0]][1];
        } else {
            cout << edges[vec[1]][0] << " " << edges[vec[1]][1];
        }
        return 0;
    }

    // ��������
    getRemoveEdge(edges);
    return 0;
}