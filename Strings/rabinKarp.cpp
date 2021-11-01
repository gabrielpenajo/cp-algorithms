// algoritmo usado para encontrar todas as ocorrencias de um padrao em um texto
// em O(|texto| + |padrao|). Utiliza hash.

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

// dado um texto 'txt' e um padrao 's', retorna os indices 
// de cada ocorrencia de 's' no texto no vetor 'out'
void rabinKarp(string& txt, string& sample, vi& out) {
    int lenT = txt.size(), lenS = sample.size();
    build(max(lenT, lenS));
    vll hashes(lenT+1, 0);
    // calcula o hash cumulativo do texto
    for (int i = 0; i < lenT; i++)
        hashes[i+1] = (hashes[i] + (txt[i] - 'a' + 1) * p_pow[i]) % mod;

    // hash do padrao
    ll hash_s = strHash(sample);
    
    // verifica o hash de cada substring de tamanho |sample|
    for (int i = 0; i + lenS - 1 < lenT; i++) {
        ll cur_hash = (hashes[i + lenS] - hashes[i])%mod;
        if (cur_hash == (hash_s * p_pow[i]) % mod)
            out.pb(i);
    }
}

// teste
int main() {
    vi out;
    string a, b;
    a = "ababab", b = "ab";
    rabinKarp(a, b, out);
    cout << "padrao \"" << b <<"\" no texto \"" << a << "\":" << endl;
    for (auto i : out)
        cout << i << endl;
    cout << "FIN" << endl;

    out.clear();
    a = "aaaaa", b = "bbb";
    rabinKarp(a, b, out);
    cout << "padrao \"" << b <<"\" no texto \"" << a << "\":" << endl;
    for (auto i : out)
        cout << i << endl;
    cout << "FIN" << endl;

    out.clear();
    a = "aafafaasf", b = "aaf";
    rabinKarp(a, b, out);
    cout << "padrao \"" << b <<"\" no texto \"" << a << "\":" << endl;
    for (auto i : out)
        cout << i << endl;
    cout << "FIN" << endl;

    return 0;
}