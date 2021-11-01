#include <bits/stdc++.h>

#define dir(i) (2*i+1)
#define esq(i) (2*i)

using namespace std;

// Complexidade de espaco: O(n) - precisa de um vetor
// de 4n posicoes para armazenamento basico
// Complexidade de tempo:
// -O(M*log n) para updates/queries
// -O(M*n) para inicializacao
// onde O(M) eh o custo que depende do tipo de dados que a seg armazena

// example implementation: update assigns 'val' to element arr[pos];
// query returns the sum of all elements in range [ql, qr];
class segTree {
public:
    segTree(vector<int>& arr) {
        int l = 1, r = arr.size();
        seg = vector<int>(4*r);
        build(arr, l, r);
    }
    void update(int val, int pos, int l, int r, int cur = 1) {
        // match
        if (l == r) {
            seg[cur] = val;
            return;
        }
        // keep searching
        int mid = (l+r)/2;
        if (pos <= mid) update(val, pos, l, mid, esq(cur));
        else update(val, pos, mid+1, r, dir(cur));
        seg[cur] = merge(cur);
    }
    int query(int ql, int qr, int l, int r, int cur = 1) {
        // invalid range
        if (ql > qr) return 0;
        // found
        if (ql == l && qr == r) return seg[cur];
        // keep querying
        int mid = (l+r)/2;
        return query(ql, min(qr, mid), l, mid, esq(cur)) +
               query(max(ql, mid+1), qr, mid+1, r, dir(cur));
    }
protected:
    vector<int> seg;
    void build(vector<int>& arr, int l, int r, int cur = 1) {
        if (l == r) {
            seg[cur] = arr[l-1];
            return;
        }
        int mid = (l+r)/2;
        build(arr, l, mid, esq(cur));
        build(arr, mid+1, r, dir(cur));
        seg[cur] = merge(cur);
    }
    int merge(int cur) {
        return seg[esq(cur)] + seg[dir(cur)];
    }
};

// Exemplo
int main() {
    vector<int> ex = {1, 2, 3, 4, 5, 6, 7, 8};
    // seg tree para pegar a soma dos elementos
    // no intervalo [l, r]
    segTree seg(ex);
    cout << "soma[0, 8]: " << seg.query(1, 8, 1, 8) << endl;
    seg.update(6, 8, 1, 8);
    // ex = {1, 2, 3, 4, 5, 6, 7, 6}
    cout << "soma[4, 8]: " << seg.query(5, 8, 1, 8) << endl;
    return 0;
}