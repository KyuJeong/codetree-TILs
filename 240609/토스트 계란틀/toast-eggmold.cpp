#include <stdio.h>
#include <vector>
#include <queue>
#include <cmath>
#include <cstring>

using namespace std;

struct Node
{
	int y;
	int x;
	Node() {}
	Node(int _y, int _x) :y(_y), x(_x) {}
};

int n, l, r;
int G[51][51];
bool visit[51][51];
int cnt, num;
int my[] = { -1,1,0,0 };
int mx[] = { 0,0,-1,1 };
queue <Node> tmp;

bool bfs(int y, int x)
{
	queue <Node> q;
	q.push({ y,x });
	visit[y][x] = true;
	bool ret = false;

	vector <Node> v;
	int sum = 0;

	while (!q.empty())
	{
		Node c = q.front();
		q.pop();
		v.push_back({ c.y,c.x });
		sum += G[c.y][c.x];
		for (int i = 0; i < 4; i++)
		{
			int ny = c.y + my[i];
			int nx = c.x + mx[i];
			if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;
			if (visit[ny][nx]) continue;
			int dif = abs(G[c.y][c.x] - G[ny][nx]);
			if (dif >= l && dif <= r)
			{
				visit[ny][nx] = true;
				q.push({ ny,nx });
				ret = true;
			}
		}
	}

	if (!ret) return ret;
	int num = sum / v.size();
	for (auto i : v)
	{
		G[i.y][i.x] = num;
		tmp.push({ i.y,i.x });
	}
	return ret;
}

bool chk(int y, int x)
{
	for (int i = 0; i < 4; i++)
	{
		int ny = y + my[i];
		int nx = x + mx[i];

		if (ny < 0 || nx < 0 || ny >= n || nx >= n) continue;
		int dif = abs(G[ny][nx] - G[y][x]);
		if (dif >= l && dif <= r) return true;
	}
	return false;
}

int main()
{
	scanf("%d %d %d", &n, &l, &r);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			scanf("%d", &G[i][j]);
			tmp.push({ i,j });
		}
	}

	while (1)
	{
		bool flag = false;
		int sz = tmp.size();
		for (int i = 0; i < sz; i++)
		{
			Node c = tmp.front();
			tmp.pop();
			if (visit[c.y][c.x] || !chk(c.y, c.x)) continue;
			if (bfs(c.y, c.x)) flag = true;
		}
		if (!flag) break;
		cnt++;
		memset(visit, false, sizeof(visit));
	}

	printf("%d", cnt);

	return 0;
}