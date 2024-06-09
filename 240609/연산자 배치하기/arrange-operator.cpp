#include <bits/stdc++.h>

using namespace std;

int n, k;
vector <int> v, seq;
int op[4];
int _max = -1e9;
int _min = 1e9;

int main() {
	cin.tie(NULL);
	std::ios::sync_with_stdio(false);

	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> k;
		v.push_back(k);
	}

	for (int i = 0; i < 4; i++) {
		cin >> k;
		for (int j = 0; j < k; j++)
			seq.push_back(i);
	}

	do {
		int sum = v[0];
		for (int i = 0; i < n - 1; i++) {
			if (seq[i] == 0) {
				sum += v[i + 1];
			}
			else if (seq[i] == 1) {
				sum -= v[i + 1];
			}
			else if (seq[i] == 2) {
				sum *= v[i + 1];
			}
			else
				sum /= v[i + 1];
		}
		_max = max(_max, sum);
		_min = min(_min, sum);
	} while (next_permutation(seq.begin(), seq.end()));

	cout << _min << " " << _max;

	return 0;
}