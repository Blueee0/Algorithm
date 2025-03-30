#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <string>

using namespace std;

// �ж������ַ����Ƿ����ͨ���ı�һ���ַ��໥ת��
bool canConvert(const string& str1, const string& str2) {
    int diffCount = 0;
    for (size_t i = 0; i < str1.size(); ++i) {
        if (str1[i] != str2[i]) {
            ++diffCount;
        }
        if (diffCount > 1) {
            return false;
        }
    }
    return true;
}

// �����������
int bfs(const string& beginStr, const string& endStr, const unordered_map<string, vector<string>>& graph) {
    queue<pair<string, int>> que;
    unordered_set<string> visited;

    que.push({beginStr, 1}); // ��ʼ����Ϊ1
    visited.insert(beginStr);

    while (!que.empty()) {
        auto [curStr, step] = que.front();
        que.pop();

        if (curStr == endStr) 
            return step; // �ҵ�Ŀ���ַ��������ز���

        // ������ǰ�ַ����������ھ�
        if (graph.find(curStr) != graph.end()) {
            for (const string& nextStr : graph.at(curStr)) {
                if (!visited.count(nextStr)) {
                    visited.insert(nextStr);
                    que.push({nextStr, step + 1});
                }
            }
        }
    }
    return 0; // �Ҳ���·��
}

int main() {
    int n;
    cin >> n;
    string beginStr, endStr;
    cin >> beginStr >> endStr; 
    vector<string> strList(n);
    for (int i = 0; i < n; i++) {
        cin >> strList[i];
    }

    // ����ͼ
    unordered_map<string, vector<string>> graph;
    for (int i = 0; i < n; i++) {
        if (canConvert(beginStr, strList[i])) {
            graph[beginStr].push_back(strList[i]);
        }
        if (canConvert(strList[i], endStr)) {
            graph[strList[i]].push_back(endStr);
        }

        for (int j = i + 1; j < n; j++) {
            // ע�⣺������������ͼ
            if (canConvert(strList[i], strList[j])) {
                graph[strList[i]].push_back(strList[j]);
                graph[strList[j]].push_back(strList[i]);
            }
        }
    }

    // ���� BFS ����
    int result = bfs(beginStr, endStr, graph);
    cout << result << endl;

    return 0;
}