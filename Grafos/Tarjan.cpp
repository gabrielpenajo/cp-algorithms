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

class Tarjan {
public:
    Tarjan(graph& g) {
        this->g = g;
        n = len(g);
    }
    void findSCC() {
        ids = vi(n, -1);
        low = vi(n);
        onStack = vec<bool>(n, false);
        for (int i = 0; i < n; ++i) {
            if (ids[i] == UNVISITED) {
                dfs(i);
            }
        }
    }
    void print() {
        cout << "SCC count: " << SCCcount << endl;
        map<int, vi> sccs;
        for (int i = 0; i < n; ++i) {
            if (sccs.find(low[i]) == sccs.end())
                sccs[i] = vi();
            sccs[low[i]].push_back(ids[i]);
        }
        int cnt = 0;
        for (auto i = sccs.begin(); i != sccs.end(); i++) {
            cout << "component no.: " << cnt++ << endl;
            cout << "nodes: ";
            for (int j : i->second) {
                cout << j << " ";
            }
            cout << endl;
        }
    }
private:
    const int UNVISITED = -1;
    graph g;
    vi ids;
    vi low;
    vec<bool> onStack;
    stack<int> stk;
    int n;
    int id = 0;
    int SCCcount = 0;

    void dfs(int at) {
        stk.push(at);
        onStack[at] = true;
        ids[at] = low[at] = id++;

        // visit neighbors and update their low-link values on callback
        for (int to : g[at]) {
            if (ids[to] == UNVISITED) dfs(to);
            if (onStack[to]) low[at] = min(low[at], low[to]);
        }

        // after visiting all the neighbors of 'at', if the current node is the
        // low-link value of the SCC, empty the stack until the nodes of the
        // SCC are removed from the stack
        if (ids[at] == low[at]) {
            for (int node = stk.top();; node = stk.top()) {
                stk.pop();
                onStack[node] = false;
                low[node] = ids[at];
                if (node == at) break;
            }
            SCCcount++;
        }
    }
};

int main() {
    graph g({{1},
            {2},
            {0}});
    Tarjan tarjan(g);
    tarjan.findSCC();
    tarjan.print();
    return 0;
}