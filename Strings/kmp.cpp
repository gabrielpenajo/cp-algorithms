// calcula quantas vezes um padrao 'k'
// aparece numa string 's'. o padrao
// eh observado onde pi[i] = |k|

#include <bits/stdc++.h>
#define ll long long
#define pb push_back

using namespace std;

typedef vector<int> vi;

vi prefixFunc(string& s) {
    int len = (int) s.size();
    // armazena o tamanho do maior
    // prefixo proprio da substring
    // s[0, i]
    vi pi(len, 0);
    for (int i = 1; i < len; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

vi kmp(string& s, string& k) {
    int lenK = (int) k.size();
    int lenS = (int) s.size();
    string aux = k + '#' + s;
    vi pi = prefixFunc(aux);

    vi occ;
    for (int i = lenK + 1; i < pi.size(); i++)
        if (pi[i] == lenK)
            // posicao relativa a 's': i - (len('#') + len(k)) - len(k) + 1
            occ.pb(i - 2*lenK);
    
    return occ;
}

// sample
int main() {
    //          0 2 4 6 8 0 2 4 6 8 0 2 4 6 8 0
    string s = "caso de teste para fins de teste";
    string k = "teste";
    vi occ = kmp(s, k);
    
    cout << "ocorrencias: ";
    for (auto i : occ)
        cout << i << " ";
    cout << endl;
    
    return 0;
}