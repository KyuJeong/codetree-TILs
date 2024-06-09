#include <bits/stdc++.h>

using namespace std;

typedef pair <int, int> pii;

struct COLOR {
	int color;
	int update_sec;
};

struct NODE {
	int id;
	int pid;
	COLOR color;
	int max_depth;
	vector <int> cid;
};

int Q;
vector <NODE*> root;
vector <int> root_id;
NODE node[100005];
int sec;
int sum;

bool chk_add(int pid) {
	NODE* par_node = &node[pid];
	int cur_depth = 2;
	while (1) {
		if (par_node->max_depth < cur_depth) {
			return false;
		}
		if (par_node->pid == -1) break;
		par_node = &node[par_node->pid];
		cur_depth++;
	}
	return true;
}

void add_node(int mid, int pid, int color, int max_depth) {
	node[mid] = NODE({ mid,pid,{color, sec},max_depth });

	if (pid == -1) {
		root_id.push_back(mid);
		return;
	}
	else if (!chk_add(pid)) return;

	NODE* par_node = &node[pid];
	par_node->cid.push_back(mid);
}

void change_color(int mid, int color) {
	NODE* cur_node = &node[mid];
	cur_node->color = { color,sec };
	for (auto i : cur_node->cid) {
		change_color(i, color);
	}
}

COLOR get_color(int mid) {
	NODE* cur_node = &node[mid];
	if (cur_node->pid == -1) {
		return{ cur_node->color};
	}
	COLOR par_info = get_color(cur_node->pid);
	if (cur_node->color.update_sec > par_info.update_sec) return cur_node->color;
	else return par_info;
}

int dfs(int mid, COLOR color) {
	NODE* cur_node = &node[mid];
	if (cur_node->color.update_sec < color.update_sec) {
		cur_node->color = color;
	}

	int chk = 1 << cur_node->color.color;

	if (cur_node->cid.size() == 0) {
		sum += 1;
		return chk;
	}

	for (auto i : cur_node->cid) {
		chk |= dfs(i, cur_node->color);
	}
	int color_cnt = 0;
	for (int i = 1; i <= 5; i++) {
		if (chk & (1 << i)) color_cnt++;
	}
	sum += (color_cnt * color_cnt);
	return chk;
}

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);

	cin >> Q;

	int x;
	while (Q--) {
		cin >> x;
		int mid, pid, color, max_depth;
		sec++;
		switch (x)
		{
		case 100:
			cin >> mid >> pid >> color >> max_depth;
			add_node(mid, pid, color, max_depth);
			break;
		case 200:
			cin >> mid >> color;
			change_color(mid, color);
			break;
		case 300:
			cin >> mid;
			cout << get_color(mid).color << "\n";
			break;
		case 400:
			sum = 0;
			for (auto i : root_id) {
				dfs(i, {0, 0});
			}
			cout << sum << "\n";
			break;
		default:
			break;
		}
	}

	return 0;
}