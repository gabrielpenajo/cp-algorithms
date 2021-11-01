// automato (maquina de estados finitos) para calcular
// a funcao de prefixo descrita em prefixFunction.cpp

#include <bits/stdc++.h>
#define ll long long
#define DEBUG 0
using namespace std;
typedef vector<int> vi;
template <class T>
using graph = vector<vector<T>>;

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

void prefixAutomaton(string s, graph<int>& aut) {
    s += "#";
    int len = s.size();
    vi pi = prefixFunc(s);
    aut.assign(len, vi(26));
    // aut[i][c] indica a transicao entre a funcao prefixo
    // de s[0, i-1] para s[0, i] considerando que o proximo
    // caractere eh a c-esima letra do alfabeto. ou seja, dado
    // um caractere 'c', aut[i][c] indica o proximo estado
    // dentro da funcao prefixo
    for (int i = 0; i < len; i++) {
        for (int c = 0; c < 26; c++) {
            if (i > 0 && 'a' + c != s[i])
                aut[i][c] = aut[pi[i-1]][c];
            else
                aut[i][c] = i + ('a' + c == s[i]);
        }
    }
}

// exemplo: conta quantas vezes o padrao calculado no automato aparece no texto 't'
int traverse(graph<int>& aut, string& t) {
    int ans = 0;
    int state = 0;
    for (int i = 0; i < (int) t.size(); i++) {
        state = aut[state][t[i] - 'a'];
        if (state == (int) aut.size() - 1) ans++;
    }
    return ans;
}

int main() {
    string s = "abcba";
    graph<int> aut;
    prefixAutomaton(s, aut);
    #if DEBUG
    cout << "automaton:" << endl;
    for (int i = 0; i < aut.size(); i++) {
        cout << "[";
        for (int j = 0; j < aut[i].size(); j++) {
            cout << setw(4) << setfill(' ') << aut[i][j] << ",]"[j == aut[i].size()-1];
        }
        cout << endl;
    }
    #endif
    string txt = "abcacbabcbabbccaabcbabcbacabccabcba";
    cout << "o padrao \"" << s << "\" apareceu no texto " << traverse(aut, txt) << " vezes" << endl;
    return 0;
}

// problemas para praticar:
// medio: https://codeforces.com/contest/432/problem/D
// hard: https://codeforces.com/contest/808/problem/G