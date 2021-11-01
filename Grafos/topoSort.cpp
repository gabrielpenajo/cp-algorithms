#include <bits/stdc++.h>

#define mp make_pair
#define pb push_back
using namespace std;

typedef vector<int> vi;
typedef vector<bool> vb;
template <class T>
using graph = vector<vector<T>>;


graph<int> g;
vb vis;
vi topo;

void dfs(int v) {
    vis[v] = true;

    for (int u : g[v])
        if (!vis[u])
            dfs(u);
    
    topo.pb(v);
}

void topoSort(int n) {
    vis.assign(n, false);
    topo.clear();
    for (int i = 0; i < n; i++)
        if (!vis[i])
            dfs(i);

    reverse(topo.begin(), topo.end());
}

int main() {
    g = {{1, 2}, // 0
         {2},    // 1
         {3, 4}, // 2
         {4, 6}, // 3
         {6},    // 4
         {6},    // 5
         {}};    // 6
    topoSort((int) g.size());
    for (int i : topo)
        cout << i << " ";
    cout << endl;
    return 0;
}