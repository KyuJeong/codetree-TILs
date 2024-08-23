#include <bits/stdc++.h>

using namespace std;

typedef pair <int, int> pii;

struct Trip {
	int r, dst, enable;
};

int srt;
int n, m;
vector <pii> vtx[2001];
int dist[2001];
int max_id;
Trip trip[30001];
priority_queue <pii> best_trip;

void dijkstra() {
	for (int i = 0; i < n; i++) {
		dist[i] = 1e9;
	}
	dist[srt] = 0;

	bool chk[2001] = { false };

	priority_queue <pii> pq;

	pq.push({ 0,srt });

	while (!pq.empty()) {
		int cur_dist = -pq.top().first;
		int cur = pq.top().second;
		pq.pop();

		if (chk[cur]) continue;
		chk[cur] = true;

		for (auto i : vtx[cur]) {
			int nxt_dist = i.first;
			int nxt = i.second;
			if (dist[nxt] > cur_dist + nxt_dist) {
				dist[nxt] = cur_dist + nxt_dist;
				pq.push({ -dist[nxt],nxt });
			}
		}
	}
}

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);

	int q;
	cin >> q;
	int x, u, v, w;
	int id, rev, dst;
	while (q--) {
		cin >> x;
		if (x == 100) {
			cin >> n >> m;
			for (int i = 0; i < m; i++) {
				cin >> u >> v >> w;
				vtx[u].push_back({ w,v });
				vtx[v].push_back({ w,u });
			}
			dijkstra();
		}
		else if (x == 200) {
			cin >> id >> rev >> dst;
			trip[id] = { rev, dst, true};
			if (id > max_id) max_id = id;
			int b = rev - dist[dst];
			if (b >= 0) best_trip.push({ b, -id });
		}
		else if (x == 300) {
			cin >> id;
			trip[id].enable = false;
		}
		else if (x == 400) {
			id = -1;
			while (!best_trip.empty()) {
				id = -best_trip.top().second;
				best_trip.pop();
				if (trip[id].enable) {
					trip[id].enable = false;
					break;
				}
				id = -1;
			}
			cout << id << "\n";
		}
		else if (x == 500) {
			cin >> srt;
			dijkstra();
			best_trip = priority_queue <pii>();
			for (int i = 1; i <= max_id; i++) {
				if (trip[i].enable) {
					int b = trip[i].r - dist[trip[i].dst];
					if (b >= 0) best_trip.push({ b, -i });
				}
			}
		}
	}

	return 0;
}