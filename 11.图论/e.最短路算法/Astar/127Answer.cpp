#include<iostream>
#include<queue>
#include<string.h>
using namespace std;

// ���ָ��а����߷�
int dir[8][2]={-2,-1,-2,1,-1,2,1,2,2,1,2,-1,1,-2,-1,-2};    
int b1, b2; // Ŀ��λ��
int moves[1001][1001];  // ��ʾ����㵽λ�� (next.x, next.y) ����С�ƶ�������

// F = G + H
// G = ����㵽�ýڵ�·������
// H = �ýڵ㵽�յ��Ԥ������
struct Knight{
    int x,y;
    int g,h,f;
    bool operator < (const Knight & k) const{  // ����������� ��С��������
        return k.f < f;
    }
};

int Heuristic(const Knight& k) { // ŷ�����룺�������ţ���߾���
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
		    break;  // �ߵ��յ㣬�˳�

		for(int i = 0; i < 8; i++){

			next.x = cur.x + dir[i][0];
			next.y = cur.y + dir[i][1];
			if(next.x < 1 || next.x > 1000 || next.y < 1 || next.y > 1000)
			    continue;   // Խ���ˣ�����
			if(!moves[next.x][next.y]){ // ���Ŀ��λ���Ƿ��Ѿ������ʹ���Ϊ0����δ����
				moves[next.x][next.y] = moves[cur.x][cur.y] + 1;
                // ��ʼ����F
				next.g = cur.g + 5; // �����գ�ŷ�����룺1 * 1 + 2 * 2 = 5
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
            que.pop(); // �������
		cout << moves[b1][b2] << endl;
	}
	return 0;
}
