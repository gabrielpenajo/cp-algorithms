#include <bits/stdc++.h>
#define len(i) ((int) i.size())

using namespace std;

using pii = pair<int, int>;
using ll = long long;
template<class T> using vec = vector<T>;
using vi = vec<int>;
using vll = vec<ll>;
using vec2 = vec<vec<int>>;
using vec3 = vec<vec2>;
using vec4 = vec<vec3>;
using graph = vec2;

// dfs for finding bridges
void dfs(int at, int parent, graph& g, vec<bool>& vis, vi& ids, vi& low, vi& bridges, int& id) {
    vis[at] = true;
    low[at] = ids[at] = ++id;

    for (int to : g[at]) {
        if (to == parent) continue;
        if (!vis[to]) {
            dfs(to, at, g, vis, ids, low, bridges, id);
            low[at] = min(low[at], low[to]);
            if (ids[at] < low[to]) {
                bridges.push_back(at);
                bridges.push_back(to);
            }
        }
        else {
            low[at] = min(low[at], ids[to]);
        }
    }
}

// dfs for finding articulation points
void dfs(int root, int at, int parent, graph& g, vec<bool>& vis, vi& ids, vi& low, vec<bool>& art, int& id, int& rootOut) {
    if (parent == root) rootOut++;
    
    vis[at] = true;
    low[at] = ids[at] = ++id;

    for (int to : g[at]) {
        if (to == parent) continue;
        if (!vis[to]) {
            dfs(root, at, parent, g, vis, ids, low, art, id, rootOut);
            low[at] = min(low[at], low[to]);
            if (ids[at] <= low[to])
                art[at] = true;
        }
        else
            low[at] = min(low[at], ids[to]);
    }
}

// returns a list of pairs of nodes which form bridges.
// the returned list is always even in length and indices (2*i, 2*i+1) form a
// pair.
// e.g.: (0, 1), (2, 3), ...
vi findBriges(graph& g) {
    int n = len(g),
    id = 0;
    vi low(n), ids(n), bridges;
    vec<bool> vis(n, false);

    for (int i = 0; i < n; ++i)
        if (!vis[i])
            dfs(i, -1, g, vis, ids, low, bridges, id);

    return bridges;
}

// returns a vector indicating which nodes are articulation points.
// for example, if a node _i_ is an articulation point, then
// isArticulation[_i_] will be true.
vec<bool> findArticulations(graph& g) {
    int n = len(g),
    id = 0;
    vi low(n), ids(n);
    vec<bool> isArticulation(n, false),
    vis(n, false);

    for (int i = 0; i < n; ++i)
        if (!vis[i]) {
            int rootOutCount = 0;
            dfs(i, i, -1, g, vis, ids, low, isArticulation, id, rootOutCount);
            isArticulation[i] = (rootOutCount > 1);
        }
    return isArticulation;
}