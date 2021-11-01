// hash de uso geral para problemas envolvendo strings.
// permite comparar strings em O(1)

#include <bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;
typedef vector<int> vi;
typedef vector<ll> vll;

const int mod = 1e9 + 9;
const int prime = 31;
vll p_pow = {1};

void build(int n) {
    int len = p_pow.size();
    while (len < n) {
        p_pow.pb((p_pow[len-1] * prime) % mod);
        len++;
    }
}

ll strHash(string& s) {
    int n = s.size();

    if (p_pow.size() < n)
        build(n);

    ll ans = 0;
    int idx = 0;
    for (char c : s) {
        ans = (ans + (c - 'a' + 1) * p_pow[idx]) % mod;
        idx++;
    }
    return ans;
}

// sample
int main() {
    string a = "test";
    cout << "hash(a) = " << strHash(a) << endl;

    return 0;
}

