#include <bits/stdc++.h>

using namespace std;

struct Node {
	int y;
	int x;
};

int n, m;
int G[51][51];
vector <Node> house;
vector <Node> chic;

int dist(Node a, Node b) {
	return abs(a.x - b.x) + abs(a.y - b.y); 
}

int solve() {
	int house_len = house.size();
	int chic_len = chic.size();
	vector <int> arr;

	for (int i = 0; i < m; i++)
		arr.push_back(0);

	for (int i = m; i < chic_len; i++)
		arr.push_back(1);

	int ret = 1e9;

	do {
		int sum = 0;
		for (int i = 0; i < house_len; i++) {
			int _min = 1e9;
			for (int j = 0; j < chic_len; j++) {
				if (arr[j] == 0)
					_min = min(_min, dist(house[i], chic[j]));
			}
			sum += _min;
		}

		ret = min(ret, sum);
	} while (next_permutation(arr.begin(), arr.end()));

	return ret;
}

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);

	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> G[i][j];
			if (G[i][j] == 1) house.push_back({ i,j });
			else if (G[i][j] == 2) chic.push_back({ i,j });
		}
	}

	int ans = solve();
	cout << ans;

	return 0;
}