#include <bits/stdc++.h>

#define esq(i) (2*i)
#define dir(i) (2*i+1)

using namespace std;
typedef vector<int> vi;

// example implementation: update adds 'val' to all elements in range [ul, ur];
// query returns the sum of all elements in range [ql, qr];
class lazySegTree {
public:
    lazySegTree(vi& arr) {
        int r = arr.size();
        lazy = vi(4*r, 0);
        seg = vi(4*r);
        build(arr, 1, r);
    }
    int query(int ql, int qr, int l, int r, int cur = 1) {
        // invalid range
        if (ql > qr) return 0;
        // match
        if (ql == l && qr == r) return seg[cur];
        // keep querying bounds until match
        int len = r - l + 1;
        push(cur, len);
        int mid = (l+r)/2;
        return query(ql, min(qr, mid), l, mid, esq(cur)) +
               query(max(ql, mid+1), qr, mid+1, r, dir(cur));
    }
    void update(int val, int ul, int ur, int l, int r, int cur = 1) {
        // invalid range
        if (ul > ur) return;
        // match
        int len = r - l + 1;
        if (ul == l && ur == r) {
            seg[cur] += val * len;
            lazy[cur] += val;
            return;
        }
        // push prior updates to children
        push(cur, len);
        int mid = (l+r)/2;
        update(val, ul, min(ur, mid), l, mid, esq(cur));
        update(val, max(ul, mid+1), ur, mid+1, r, dir(cur));
        seg[cur] = merge(cur);
    }
protected:
    vector<int> seg;
    vector<int> lazy;
    void push(int cur, int len) {
        int& val = lazy[cur];
        seg[esq(cur)] += val * (len/2);
        seg[dir(cur)] += val * (len/2);
        lazy[esq(cur)] += val;
        lazy[dir(cur)] += val;
        val = 0;
    }
    void build(vi& arr, int l, int r, int cur = 1) {
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

// Exemple
int main() {
    vector<int> ex = {1, 2, 3, 4, 5, 6, 7, 8};
    lazySegTree seg(ex);
    cout << seg.query(3, 4, 1, 8) << endl;
    seg.update(2, 1, 4, 1, 8);
    //      { 1, 2, 3, 4, 5, 6, 7, 8}
    //      {+2,+2,+2,+2,NA,NA,NA,NA}
    // ex = { 3, 4, 5, 6, 5, 6, 7, 8}
    cout << seg.query(3, 4, 1, 8) << endl;
    seg.update(-1, 4, 7, 1, 8);
    //      { 1, 2, 3, 4, 5, 6, 7, 8}
    //      {-1,-1,-1,-1,NA,NA,NA,NA}
    // ex = { 3, 4, 5, 5, 4, 5, 6, 8}
    cout << seg.query(1, 8, 1, 8) << endl;
    return 0;
}