#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;

int timer = 0;
const int MAX_N = 1e4, LOG = 14;

vector<int> children[MAX_N];
int up[MAX_N][LOG];
int depth[MAX_N];

void dfs(int a) {
    for (int b : children[a]) {
        depth[b] = depth[a] + 1;
        up[b][0] = a;
        for (int j = 1; j < LOG; j++) {
            up[b][j] = up[up[b][j-1]][j-1];
        }
        dfs(b);
    }
}

int lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a,b);
    int k = depth[a] - depth[b];
    // move a to the same depth as b
    for (int j = LOG-1; j+1; j--) {
        if (k & (1 << j)) {
            a = up[a][j];
        }
    }
    // b is a's lca
    if (a == b) return a;
    for (int j = LOG-1; j+1; j--) {
        // move a and b upward the same amount
        if (up[a][j] != up[b][j]) {
            a = up[a][j];
            b = up[b][j];
        }
    }
    return up[a][0];
}

int main() {
    int n;
	cin >> n;
	for(int v = 0; v < n; ++v) {
		// read children of v
		int cnt;
		cin >> cnt;
		for(int i = 0; i < cnt; i++) {
			int c;
			cin >> c;
			children[v].push_back(c);
		}
	}
	dfs(0);
	int q;
	cin >> q;
	for(int i = 0; i < q; i++) {
		int a, b;
		cin >> a >> b;
		cout << lca(a, b) << "\n";
	}
}