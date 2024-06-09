#include <bits/stdc++.h>

using namespace std;

int r, c, t;
int G[50][50];
vector <int> air_y;
int my[] = { -1,1,0,0 };
int mx[] = { 0,0,-1,1 };

void spread() {
	int add[50][50] = { 0 };
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (G[i][j] == -1) continue;
			int tmp = (G[i][j] / 5);
			for (int k = 0; k < 4; k++) {
				int ny = i + my[k];
				int nx = j + mx[k];
				if (ny < 0 || nx < 0 || ny >= r || nx >= c) continue;
				if (G[ny][nx] == -1) continue;
				add[ny][nx] += tmp;
				G[i][j] -= tmp;
			}
		}
	}
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			G[i][j] += add[i][j];
}

void fresh() {
	for (int i = air_y[0] - 1; i > 0; i--)
		G[i][0] = G[i - 1][0];
	for (int j = 0; j < c - 1; j++) {
		if (G[0][j] == -1) continue;
		G[0][j] = G[0][j + 1];
	}
	for (int i = 0; i < air_y[0] + 1; i++)
		G[i][c - 1] = G[i + 1][c - 1];
	for (int j = c - 1; j > 1; j--)
		G[air_y[0]][j] = G[air_y[0]][j - 1];
	G[air_y[0]][1] = 0;

	for (int i = air_y[1] + 1; i < r - 1; i++)
		G[i][0] = G[i + 1][0];
	for (int j = 0; j < c - 1; j++) {
		if (G[r - 1][j] == -1) continue;
		G[r - 1][j] = G[r - 1][j + 1];
	}
	for (int i = r - 1; i > air_y[1]; i--)
		G[i][c - 1] = G[i - 1][c - 1];
	for (int j = c - 1; j > 1; j--)
		G[air_y[1]][j] = G[air_y[1]][j - 1];
	G[air_y[1]][1] = 0;
}

int count() {
	int ret = 2;
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			ret += G[i][j];

	return ret;
}

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);

	cin >> r >> c >> t;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			cin >> G[i][j];
			if (G[i][j] == -1) air_y.push_back(i);
		}
	}

	cin >> t;

	while (t--) {
		spread();
		fresh();
	}

	int ans = count();
	cout << ans;

	return 0;
}