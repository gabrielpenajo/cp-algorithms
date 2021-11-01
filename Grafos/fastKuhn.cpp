#include <iostream>
#include <vector>
#include <string>
#define mp make_pair
#define pb push_back
using namespace std;
typedef vector<int> vi;
typedef vector<vi> graph;
typedef vector<bool> vb;

graph grafoA, grafoB;
vb marcA, marcB;
vi matchA, matchB;

bool dfs(int v) {
    for (int i = 0; i < grafoA[v].size(); i++) {
        int viz = grafoA[v][i];
        if (marcB[viz] == 1)
            continue;
        marcB[viz] = 1;

        if (matchB[viz] == -1 || dfs(matchB[viz])) {
            matchB[viz] = v;
            matchA[v] = viz;
            return true;
        }
    }
    return false;
}

int maxMatching(int n, int m) {
    for (int i = 0; i < n; i++)
        matchA[i] = -1;
    for (int j = 0; j < m; j++)
        matchB[j] = -1;

    bool aux = true;
    int resp = 0;
    while (aux) {
        for (int j = 0; j < m; j++)
            marcB[j] = 0;
        aux = false;
        for (int i = 0; i < n; i++) {
            if (matchA[i] != -1)
                continue;
            if (dfs(i)) {
                resp++;
                aux = true;
            }
        }
    }
    return resp;
}

int main() {
    grafoA = {{0},{},{},{2,3}};
    grafoB = {{0},{},{3},{3}};
    marcA = vb(4); marcB = vb(4);
    matchA = vi(4); matchB = vi(4);
    cout << maxMatching(4, 4) << endl;
    return 0;
}