#include <bits/stdc++.h>

using namespace std;

typedef pair <int, int> pii;

struct NODE {
	int id;
	int pid;
	int color;
	int max_depth;
	int update_sec;
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
	if (pid == -1) {
		node[mid] = NODE({ mid,pid,color,max_depth,sec });
		root_id.push_back(mid);
		return;
	}
	else if (!chk_add(pid)) return;

	node[mid] = NODE({ mid,pid,color,max_depth,sec });

	NODE* par_node = &node[pid];
	par_node->cid.push_back(mid);
}

void change_color(int mid, int color) {
	NODE* cur_node = &node[mid];
	cur_node->color = color;
	cur_node->update_sec = sec;
	for (auto i : cur_node->cid) {
		change_color(i, color);
	}
}

pii get_color(int mid) {
	NODE* cur_node = &node[mid];
	if (cur_node->pid == -1) {
		return { cur_node->color,0 };
	}
	pii par_info = get_color(cur_node->pid);
	if (cur_node->update_sec > par_info.second) return{ cur_node->color,cur_node->update_sec };
	else return par_info;
}

int dfs(int mid) {
	NODE* cur_node = &node[mid];
	if (cur_node->pid != -1) {
		NODE* par_node = &node[cur_node->pid];
		pii par_info = { par_node->color, par_node->update_sec };
		if (cur_node->update_sec < par_info.second) {
			cur_node->color = par_node->color;
			cur_node->update_sec = par_node->update_sec;
		}
	}
	int chk = 1 << cur_node->color;

	if (cur_node->cid.size() == 0) {
		sum += 1;
		return chk;
	}

	for (auto i : cur_node->cid) {
		chk |= dfs(i);
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
			cout << get_color(mid).first << "\n";
			break;
		case 400:
			sum = 0;
			for (auto i : root_id) {
				dfs(i);
			}
			cout << sum << "\n";
			break;
		default:
			break;
		}
	}

	return 0;
}