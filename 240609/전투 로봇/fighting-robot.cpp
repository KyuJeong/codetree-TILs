#include <bits/stdc++.h>

using namespace std;

struct Node {
	int y;
	int x;
};

bool operator < (const Node &a, const Node &b) {
	if (a.y == b.y) return a.x < b.x;
	return a.y < b.y;
}

int n;
int G[20][20];
int feed_cnt[10];
int my[] = { -1,1,0,0 };
int mx[] = { 0,0,-1,1 };

int solve(Node srt) {
	Node shark = srt;

	int ret = 0;
	int qsz = 1;
	int shark_size = 2;
	int feed_stack = 0;

	while (1) {
		int sec = 0;
		queue <Node> q;
		q.push(shark);
		bool flag = false;
		for (int i = 1; i < shark_size; i++) {
			if (feed_cnt[i] > 0)
				flag = true;
		}
		if (!flag) return ret;
		bool visit[20][20] = { false };
		visit[shark.y][shark.x] = true;
		G[shark.y][shark.x] = 0;
		qsz = 1;
		while (!q.empty()) {
			vector <Node> feed;
			while (qsz--) {
				Node cur = q.front();
				q.pop();
				for (int i = 0; i < 4; i++) {
					int ny = cur.y + my[i];
					int nx = cur.x + mx[i];
					if (ny < 0 || nx < 0 || ny >= n || nx >= n || visit[ny][nx]) continue;
					if (G[ny][nx] > shark_size) continue;
					else if (G[ny][nx] == shark_size || G[ny][nx] == 0) {
						q.push({ ny,nx });
						visit[ny][nx] = true;
					}
					else {
						feed.push_back({ ny,nx });
						visit[ny][nx] = true;
					}
				}
			}
			if (q.size() == 0 && feed.size() == 0) return ret;
			sec++;
			if (feed.size() > 0) {
				sort(feed.begin(), feed.end());
				int feed_size = G[feed[0].y][feed[0].x];
				feed_cnt[feed_size]--;
				shark.y = feed[0].y;
				shark.x = feed[0].x;
				G[feed[0].y][feed[0].x] = 0;
				if (++feed_stack == shark_size) {
					shark_size++;
					feed_stack = 0;
				}
				feed.clear();
				ret += sec;
				sec = 0;
				break;
			}
			qsz = q.size();
		}
	}
	return ret;
}

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);

	cin >> n;

	Node shark;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> G[i][j];
			if (G[i][j] == 9)
				shark = { i,j };
			else
				feed_cnt[G[i][j]]++;
		}
	}

	int ans = solve(shark);

	cout << ans;

	return 0;
}