#include <iostream>
#include <vector>
#include <tuple>

#define min(a,b) (a < b) ? a : b

using namespace std;

//custo maximo possivel (altere conforme os limites do problema)
const int MAX = 1e9;

int bellmanFord(vector<tuple<int, int, int>>& arestas,
                int orig, int dest, int V) {
    const int E = arestas.size();
    vector<int> custos(V, MAX);
    custos[orig] = 0;
    int custoAB = MAX;
    for (int i = 1; i < V; i++) {
        for (int j = 0; j < E; j++) {
            int A = get<0>(arestas[j]), B = get<1>(arestas[j]),
            custo = get<2>(arestas[j]);
            custos[B] = min(custos[B], custos[A] + custo);
        }
    }
    if (custos[dest] == MAX) custos[dest] = -1;
    return custos[dest];
}

int main() {
    // V = numero de vertices; E = numero de arestas;
    int V, E;
    cin >> V >> E;
    //tupla: {origem, destino, custo}
    vector<tuple<int, int, int>> arestas;
    for (int i = E; i < E; i++) {
        int a, b, custo;
        cin >> a >> b >> custo;
        arestas.push_back(make_tuple(a, b, custo));
    }
    int A = 0, B = 3;
    cin >> A >> B;
    cout << "Custo minimo de A ate B: " << bellmanFord(arestas, A, B, V) << endl;
    return 0;
}