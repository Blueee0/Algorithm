#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

int main(){
    int m, n, s, t;
    cin >> n >> m;
    vector<int> inDegree(n, 0); // ��¼���
    vector<int> result; // ��¼���
    unordered_map<int, vector<int>> umap; // ��¼�ļ�������ϵ

    while(m--){
        cin >> s >> t;
        inDegree[t]++;
        umap[s].push_back(t);
    }

    // ��ʼ���洢���Ϊ0�ĵ�
    queue<int> que;
    for (int i = 0; i < n; i++) {
        if (inDegree[i] == 0) 
            que.push(i);
    }

    // ��¼���
    while (que.size()) {
        int cur = que.front();
        que.pop();
        result.push_back(cur);

        // ���ýڵ��ͼ���Ƴ����ýڵ���Ϊ�����������ӵĽڵ�� ��� ��һ
        vector<int> files = umap[cur];
        if (files.size()) { 
            for (int i = 0; i < files.size(); i++) {
                inDegree[files[i]] --; // curָ��Ľڵ���ȶ�����һ����
                // ���ָ��Ľڵ��һ֮�����Ϊ0��˵����Ҫѡȡ����һ���ڵ㣬������С�
                if(inDegree[files[i]] == 0) 
                    que.push(files[i]); 
            }
        }
    }

    if (result.size() == n) {
        for (int i = 0; i < n - 1; i++) 
            cout << result[i] << " ";
        cout << result[n - 1];
    } else 
        cout << -1 << endl;

    return 0;
}