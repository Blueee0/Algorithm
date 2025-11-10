#include<iostream>
#include<queue>
#include<string.h>
using namespace std;

// 日字格有八种走法
int dir[8][2]={-2,-1,-2,1,-1,2,1,2,2,1,2,-1,1,-2,-1,-2};    
int b1, b2; // 目标位置
int moves[1001][1001];  // 表示从起点到位置 (next.x, next.y) 的最小移动步数。

// F = G + H
// G = 从起点到该节点路径消耗
// H = 该节点到终点的预估消耗
struct Knight{
    int x,y;
    int g,h,f;
    bool operator < (const Knight & k) const{  // 重载运算符， 从小到大排序
        return k.f < f;
    }
};

int Heuristic(const Knight& k) { // 欧拉距离：不开根号，提高精度
    return (k.x - b1) * (k.x - b1) + (k.y - b2) * (k.y - b2);
}

priority_queue<Knight> que;
void Astar(const Knight& k)
{
    Knight cur, next;
	que.push(k);
	while(!que.empty()){

		cur=que.top(); que.pop();
		if(cur.x == b1 && cur.y == b2)
		    break;  // 走到终点，退出

		for(int i = 0; i < 8; i++){

			next.x = cur.x + dir[i][0];
			next.y = cur.y + dir[i][1];
			if(next.x < 1 || next.x > 1000 || next.y < 1 || next.y > 1000)
			    continue;   // 越界了，跳过
			if(!moves[next.x][next.y]){ // 检查目标位置是否已经被访问过。为0，则未访问
				moves[next.x][next.y] = moves[cur.x][cur.y] + 1;
                // 开始计算F
				next.g = cur.g + 5; // 马走日，欧拉距离：1 * 1 + 2 * 2 = 5
                next.h = Heuristic(next);
                next.f = next.g + next.h;
                que.push(next);
			}

		}
	}
}

int main()
{
    int n, a1, a2;
    cin >> n;
    while (n--) {
        cin >> a1 >> a2 >> b1 >> b2;
        memset(moves,0,sizeof(moves));
        Knight start;
        start.x = a1;
        start.y = a2;
        start.g = 0;
        start.h = Heuristic(start);
        start.f = start.g + start.h;
		Astar(start);
        while(!que.empty()) 
            que.pop(); // 队列清空
		cout << moves[b1][b2] << endl;
	}
	return 0;
}
