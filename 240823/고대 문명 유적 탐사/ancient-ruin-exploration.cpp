#include <bits/stdc++.h>

using namespace std;

struct Result {
	int y;
	int x;
	int val;
	int deg;
};

struct Node {
	int y, x;
};

int k, m;
int G[6][6];
int arr[301];
bool chk[6][6];
int dy[] = { -1,1,0,0 };
int dx[] = { 0,0,-1,1 };
int idx = 0;

bool operator < (Result& r1, Result& r2) {
	if (r1.val == r2.val) {
		if (r1.deg == r2.deg) {
			if (r1.x == r2.x) {
				return r1.y < r2.y;
			}
			return r1.x < r2.x;
		}
		return r1.deg < r2.deg;
	}
	return r1.val > r2.val;
}

int bfs(int y, int x, bool need_erase) {
	queue <Node> q;
	q.push({ y,x });
	chk[y][x] = true;
	int num = G[y][x];
	int cnt = 1;
	vector <Node> v;
	while (!q.empty()) {
		Node cur = q.front();
		q.pop();
		if (need_erase) v.push_back(cur);
		for (int i = 0; i < 4; i++) {
			int ny = cur.y + dy[i];
			int nx = cur.x + dx[i];
			if (ny < 0 || nx < 0 || ny >= 5 || nx >= 5 || chk[ny][nx]) continue;
			if (G[ny][nx] != num) continue;
			cnt++;
			chk[ny][nx] = true;
			q.push({ ny,nx });
		}
	}
	if (cnt < 3) return 0;
	if (need_erase) {
		for (auto i : v) 
			G[i.y][i.x] = 0;
	}
	return cnt;
}

Result rotateMatrix(int y, int x, int deg, bool only_rotate) {
	int T[6][6] = { 0 };
	for (int i = 0; i <= 2; i++) {
		for (int j = 0; j <= 2; j++) {
			T[i + y - 1][j + x - 1] = G[2 - j + y - 1][i + x - 1];
		}
	}
	for (int i = y - 1; i <= y + 1; i++) {
		for (int j = x - 1; j <= x + 1; j++) {
			G[i][j] = T[i][j];
		}
	}

	if (only_rotate) return{ 0,0,0,0 };

	memset(chk, false, sizeof(chk));
	int score = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (!chk[i][j]) score += bfs(i, j, false);
		}
	}
	return{ y,x,score,deg };
}

void startSearch() {
	vector <Result> res;
	for (int i = 1; i < 4; i++) {
		for (int j = 1; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				if (k != 3) res.push_back(rotateMatrix(i, j, k, false));
				else rotateMatrix(i, j, k, true);
			}
		}
	}
	sort(res.begin(), res.end());

	for (int i = 0; i < res[0].deg + 1; i++) {
		rotateMatrix(res[0].y, res[0].x, res[0].deg, true);
	}
}

int acquire() {
	int ans = 0;
	while (1) {
		int score = 0;
		memset(chk, false, sizeof(chk));
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (!chk[i][j]) score += bfs(i, j, true);
			}
		}
		if (score == 0) break;
		ans += score;

		for (int j = 0; j < 5; j++) {
			for (int i = 4; i >= 0; i--) {
				if (G[i][j] == 0) G[i][j] = arr[idx++];
			}
		}
	}
	return ans;
}

int solve() {
	startSearch();
	return acquire();
}

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);

	cin >> k >> m;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cin >> G[i][j];
		}
	}

	for (int i = 0; i < m; i++) {
		cin >> arr[i];
	}

	for (int i = 0; i < k; i++) {
		int ans = solve();
		if (ans == 0) break;
		cout << ans << " ";
	}

	return 0;
}