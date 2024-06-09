#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector <int> vi;

int N;
int G[21][21];
int ans;

void BFS(vector <vi> vec)
{
	queue <vector <vi>> q;

	q.push(vec);

	int cnt = 0;
	
	while (cnt <= 1364)
	{
		vector <vi> cur = q.front();
		q.pop();

		for (int i = 0; i < 4; i++)
		{
			vector <vi> nxt = cur;
			if (i == 0) // <-
			{
				for (int j = 0; j < N; j++)
				{
					// 숫자 합치는 코드
					for (int k = 0; k < N - 1; k++)
					{
						if (nxt[j][k] == 0)
							continue;
						for (int m = k + 1; m < N; m++)
						{
							if (nxt[j][m] == 0)
								continue;
							if (nxt[j][k] == nxt[j][m])
							{
								nxt[j][k] *= 2;
								nxt[j][m] = 0;
								break;
							}
							else
								break;
						}
					}

					// 왼쪽으로 붙이는 코드
					for (int k = 0; k < N; k++)
					{
						if (nxt[j][k] == 0)
						{
							for (int m = k + 1; m < N; m++)
							{
								if (nxt[j][m] != 0)
								{
									nxt[j][k] = nxt[j][m];
									nxt[j][m] = 0;
									break;
								}
							}
						}
					}
				}
			}
			else if (i == 1) // ->
			{
				for (int j = 0; j < N; j++)
				{
					// 숫자 합치는 코드
					for (int k = N - 1; k >= 0; k--)
					{
						if (nxt[j][k] == 0)
							continue;
						for (int m = k - 1; m >= 0; m--)
						{
							if (nxt[j][m] == 0)
								continue;
							if (nxt[j][k] == nxt[j][m])
							{
								nxt[j][k] *= 2;
								nxt[j][m] = 0;
								break;
							}
							else
								break;
						}
					}

					// 오른쪽으로 붙이는 코드
					for (int k = N - 1; k >= 0; k--)
					{
						if (nxt[j][k] == 0)
						{
							for (int m = k - 1; m >= 0; m--)
							{
								if (nxt[j][m] != 0)
								{
									nxt[j][k] = nxt[j][m];
									nxt[j][m] = 0;
									break;
								}
							}
						}
					}
				}
			}
			else if (i == 2) // ↑
			{
				for (int j = 0; j < N; j++)
				{
					// 숫자 합치는 코드
					for (int k = 0; k < N - 1; k++)
					{
						if (nxt[k][j] == 0)
							continue;
						for (int m = k + 1; m < N; m++)
						{
							if (nxt[m][j] == 0)
								continue;
							if (nxt[k][j] == nxt[m][j])
							{
								nxt[k][j] *= 2;
								nxt[m][j] = 0;
								break;
							}
							else
								break;
						}
					}

					// 위로 붙이는 코드
					for (int k = 0; k < N; k++)
					{
						if (nxt[k][j] == 0)
						{
							for (int m = k + 1; m < N; m++)
							{
								if (nxt[m][j] != 0)
								{
									nxt[k][j] = nxt[m][j];
									nxt[m][j] = 0;
									break;
								}
							}
						}
					}
				}
			}
			else if (i == 3) // ↓
			{
				for (int j = 0; j < N; j++)
				{
					// 숫자 합치는 코드
					for (int k = N - 1; k > 0; k--)
					{
						if (nxt[k][j] == 0)
							continue;
						for (int m = k - 1; m >= 0; m--)
						{
							if (nxt[m][j] == 0)
								continue;
							if (nxt[k][j] == nxt[m][j])
							{
								nxt[k][j] *= 2;
								nxt[m][j] = 0;
								break;
							}
							else
								break;
						}
					}

					// 아래로 붙이는 코드
					for (int k = N - 1; k > 0; k--)
					{
						if (nxt[k][j] == 0)
						{
							for (int m = k - 1; m >= 0; m--)
							{
								if (nxt[m][j] != 0)
								{
									nxt[k][j] = nxt[m][j];
									nxt[m][j] = 0;
									break;
								}
							}
						}
					}
				}
			}

			for (int j = 0; j < N; j++)
			{
				for (int k = 0; k < N; k++)
				{
					ans = max(ans, nxt[j][k]);
				}
			}
			cnt++;
			q.push(nxt);
		}
	}
}


int main()
{
	std::ios::sync_with_stdio(false);

	cin >> N;
	vector <vi> v;
	
	v.resize(N);
	for (int i = 0; i < N; i++)
	{
		v[i].resize(N);
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> v[i][j];
		}
	}

	BFS(v);
	
	cout << ans;

	return 0;
}