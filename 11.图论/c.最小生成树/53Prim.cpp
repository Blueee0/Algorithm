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
        // 因为是无向图，所以两个方向都要填上
        imap[x][y] = k;
        imap[y][x] = k;
    }

    // 所有节点到最小生成树的最小距离
    vector<int> minDist(v + 1, 10001);

    // 这个节点是否在树里
    vector<bool> isInTree(v + 1, false);

    // prim三部曲
    for(int i = 1; i < v; i++){

        // 第一步：选距离生成树最近节点
        int cur = -1; // 选中哪个节点,，来加入最小生成树
        int minVal = INT_MAX;
        for (int j = 1; j <= v; j++) {
            //  选取最小生成树节点的条件：
            //  （1）不在最小生成树里
            //  （2）距离最小生成树最近的节点
            if (!isInTree[j] &&  minDist[j] < minVal) {
                minVal = minDist[j];
                cur = j;
            }
        }
        // 第二步：最近节点（cur）加入生成树
        isInTree[cur] = true;

        // 第三步：更新非生成树节点到生成树的距离（即更新minDist数组）
        for (int j = 1; j <= v; j++) {
            // 更新的条件：
            // （1）节点是 非生成树里的节点
            // （2）与cur相连的某节点的权值 比 该某节点距离最小生成树的距离小
            if (!isInTree[j] && imap[cur][j] < minDist[j]) {
                minDist[j] = imap[cur][j];
            }
        }
    }

    // 统计结果
    int result = 0;
    for (int i = 2; i <= v; i++) {
        result += minDist[i];
    }
    cout << result << endl;

    return 0;
}