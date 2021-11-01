// algoritmo utilizado para calcular o tamanho do
// maior prefixo proprio (diferente da propria string)
// que tambem eh um sufixo da mesma. Eh base para o KMP
// ex: pref. proprio de "aaabaa" = "aa"

#include <bits/stdc++.h>
#define ll long long

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

// sample
int main() {
    //          0 2 4 6 8 0 2 4 6 8 0 2 4 6 8 0
    string s = "aaabaab";
    vi pi = prefixFunc(s);
    int len = (int) pi.size();
    cout << "pi: [";
    for (int i = 0; i < len; i++)
        cout << pi[i] << "],"[i < len-1];
    cout << endl;

    s = "abcdabcad";
    pi = prefixFunc(s);
    len = (int) pi.size();
    cout << "pi: [";
    for (int i = 0; i < len; i++)
        cout << pi[i] << "],"[i < len-1];
    cout << endl;

    s = "aabaaab";
    pi = prefixFunc(s);
    len = (int) pi.size();
    cout << "pi: [";
    for (int i = 0; i < len; i++)
        cout << pi[i] << "],"[i < len-1];
    cout << endl;
    
    return 0;
}