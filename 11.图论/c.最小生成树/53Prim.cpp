#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main(){
    int v, e;
    int x, y, k;
    cin >> v >> e;

    vector<vector<int>> imap(v + 1, vector<int>(v + 1, 10001));
    while (e--) {
        cin >> x >> y >> k;
        // ��Ϊ������ͼ��������������Ҫ����
        imap[x][y] = k;
        imap[y][x] = k;
    }

    // ���нڵ㵽��С����������С����
    vector<int> minDist(v + 1, 10001);

    // ����ڵ��Ƿ�������
    vector<bool> isInTree(v + 1, false);

    // prim������
    for(int i = 1; i < v; i++){

        // ��һ����ѡ��������������ڵ�
        int cur = -1; // ѡ���ĸ��ڵ�,����������С������
        int minVal = INT_MAX;
        for (int j = 1; j <= v; j++) {
            //  ѡȡ��С�������ڵ��������
            //  ��1��������С��������
            //  ��2��������С����������Ľڵ�
            if (!isInTree[j] &&  minDist[j] < minVal) {
                minVal = minDist[j];
                cur = j;
            }
        }
        // �ڶ���������ڵ㣨cur������������
        isInTree[cur] = true;

        // �����������·��������ڵ㵽�������ľ��루������minDist���飩
        for (int j = 1; j <= v; j++) {
            // ���µ�������
            // ��1���ڵ��� ����������Ľڵ�
            // ��2����cur������ĳ�ڵ��Ȩֵ �� ��ĳ�ڵ������С�������ľ���С
            if (!isInTree[j] && imap[cur][j] < minDist[j]) {
                minDist[j] = imap[cur][j];
            }
        }
    }

    // ͳ�ƽ��
    int result = 0;
    for (int i = 2; i <= v; i++) {
        result += minDist[i];
    }
    cout << result << endl;

    return 0;
}