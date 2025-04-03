#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <climits>
using namespace std;
 
// С����
class mycomparison {
public:
    bool operator()(const pair<int, int>& lhs, const pair<int, int>& rhs) {
        return lhs.second > rhs.second;
    }
};

// ����һ���ṹ������ʾ��Ȩ�صı�
struct Edge {
    int to;  // �ڽӶ���
    int val; // �ߵ�Ȩ��
    Edge(int t, int w): to(t), val(w) {}  // ���캯��
};

int main() {
    int n, m, p1, p2, val;
    cin >> n >> m;

    vector<list<Edge>> grid(n + 1);

    for(int i = 0; i < m; i++){
        cin >> p1 >> p2 >> val; 
        // p1 ָ�� p2��ȨֵΪ val
        grid[p1].push_back(Edge(p2, val));

    }

    int start = 1;  // ���
    int end = n;    // �յ�

    // �洢��Դ�㵽ÿ���ڵ����̾���
    std::vector<int> minDist(n + 1, INT_MAX);

    // ��¼�����Ƿ񱻷��ʹ�
    std::vector<bool> visited(n + 1, false); 
    
    // ���ȶ����д�� pair<�ڵ㣬Դ�㵽�ýڵ��Ȩֵ>
    priority_queue<pair<int, int>, vector<pair<int, int>>, mycomparison> pq;


    // ��ʼ�����У�Դ�㵽Դ��ľ���Ϊ0�����Գ�ʼΪ0
    pq.push(pair<int, int>(start, 0)); 
    
    minDist[start] = 0;  // ��ʼ�㵽����ľ���Ϊ0

    while (!pq.empty()) {
        // 1. ��һ����ѡԴ�㵽�ĸ��ڵ���Ҹýڵ�δ�����ʹ� ��ͨ�����ȼ�������ʵ�֣�
        // <�ڵ㣬 Դ�㵽�ýڵ�ľ���>
        pair<int, int> cur = pq.top(); pq.pop();
        if (visited[cur.first]) 
            continue;

        // 2. �ڶ�����������ڵ㱻��Ƿ��ʹ�
        visited[cur.first] = true;

        // 3. �����������·Ƿ��ʽڵ㵽Դ��ľ��루������minDist���飩
        for (Edge edge : grid[cur.first]) { // ����curָ��Ľڵ�
            // curָ��Ľڵ�edge.to�������ߵ�ȨֵΪ edge.val
            if (!visited[edge.to] && minDist[cur.first] + edge.val < minDist[edge.to]) { // ����minDist
                minDist[edge.to] = minDist[cur.first] + edge.val;
                pq.push(pair<int, int>(edge.to, minDist[edge.to]));
            }
        }

    }

    if (minDist[end] == INT_MAX) 
        cout << -1 << endl; // ���ܵ����յ�
    else 
        cout << minDist[end] << endl; // �����յ����·��
}
