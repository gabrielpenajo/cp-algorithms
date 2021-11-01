#include<iostream>
#include <bits/stdc++.h>
#include<cstdlib>
#define pii pair<int,int>
using namespace std;

template<class T>
T Push(T x){
    cin >> x;
    return x;
}
vector<pii> sorted;
const int MAX = 400;
int paths[MAX][MAX],sufpaths[MAX][MAX];
int temps[MAX];
bool ver[MAX], versuf[MAX];

bool cmp(int m, int temp, int L_G){
    if(L_G == 1) return temps[m] >= temp;
    return temps[m] <= temp;
}
/* pra resolver vamos
   chamar o floyd para os i valores de temperaturas que vao ser dados,
   lembrando que n mais frios = prefixo 0 a n-1, n mais quente = sufixo n-1-(k-1) a n-1
   cada fez vamos passar o valor de i para essa função floyd criada,
   pois devemos resolver as queries menores antes das maiores, já que só temos uma matriz
   ela vai ser sobrescrita com a nova resposta em cada chamada,
   para isso vamos ordenar pelos valores de temperatura as queries, 
   mantendo a ordem de solicitacao das queries
*/
void floyd(int n, int i, int i2){
        int aux,aux2;
        aux = sorted[i].second;
        aux2 = sorted[n-i2-1].second;
        for(int j = 0; j < n; j++)
            for(int k = 0; k < n; k++){
            //ifs para garantir que não vamos recalcular algo
                    if(!ver[i])paths[j][k] = min(paths[j][k], paths[j][aux] + paths[aux][k]);
                    if(!versuf[i2])sufpaths[j][k] = min(sufpaths[j][k], sufpaths[j][aux2] + sufpaths[aux2][k]);  
            }
        //ordem de planetas que pode usar
        ver[i] = true;
        versuf[i2] = true;
}

int main(){
    memset(ver,false,sizeof(ver));
    memset(versuf,false,sizeof(versuf));
    int n,r;
    cin >> n >> r;

    for(int i = 0; i < n; i++){
        int x;
        cin >> x;
        temps[i] = x;
        sorted.push_back(make_pair(x,i));
    }

    sort(sorted.begin(),sorted.end());
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++){
                paths[i][j] = i==j?0:0x3f3f3f;
                sufpaths[i][j] = i==j?0:0x3f3f3f;
            }
                

    for(int i = 0; i < r; i++){
        int x, y, d;
        cin >> x >> y >> d;
        paths[x-1][y-1] = d;
        paths[y-1][x-1] = d;
        sufpaths[x-1][y-1] = d;
        sufpaths[y-1][x-1] = d;
    }
    int clientes;
    cin >> clientes;
    vector<tuple<int,int,int,int,int>> Q;
    vector<int> res(clientes);
    for(int i = 0; i < clientes; i++){
        int a,b,k,t;
        cin >> a >> b >> k >> t;
        Q.push_back(make_tuple(k-1,min(a,b),max(a,b),t,i));
        
    }
    sort(Q.begin(),Q.end());
    int j = 0, k = 0;
    int idx = 0, idx2 = 0;
    int pref = 0, suf = 0;
    while(j < n || k < n){
        pref++; suf++;
        int begin = sorted[j].first;
        int begin2 = sorted[n-k-1].first;
        /*
        o enunciado considera que temperaturas iguais não são contadas mais de uma vez
        então no caso quando repetirmos varias temperaturas por exemplo:
        1 2 3 3 3 4
        ao solicitar a 3 mais fria vamos utilizar na verdade até o 5 planeta, onde está a
        ultima repetição da 3 temperatura mais fria, para isso fazemos esse while para
        chamar o floyd para todas as repetições
        */
        while(sorted[j].first == begin || sorted[n-k-1].first == begin2){
            /* como dito vamos chamar para todas as repetições
               para evitar sobrescrever a matriz de prefixo quando
               a repetição estiver na chamada do sufixo ou viceversa
               fazemos esses ifs para não incrementar os contadores 
               j (indice chamada de prefixo) ou k (indice chamada de sufixo)
               dependendo do caso
            */
            if(sorted[j].first != begin) floyd(n,j-1,k);
            else if(sorted[n-k-1].first != begin2) floyd(n,j,k-1);
            else floyd(n,j,k);

            if(j < n && sorted[j].first == begin) j++;
            if(k < n && sorted[n-k-1].first == begin2) k++;
            if(j >= n && k >= n) break;
        }
        /*
        ao salvar as respostas vamos utilizar um indice prefixo ou sufixo 
        para saber até que querie podemos responder, eles são incrementados de 1 em 1
        porem caso aconteça de as ultimas temperaturas serem repetidas, ele vira n,
        exemplificando
        temps: 1 2 2 3 3 3 4 5
        mais frias:
        primeira = 1, segunda = 2 terceira = 3... (pois temperaturas repetidas não contam 2 		vezes)
        porém a entrada pode ser de 1 até n, seria um corner case.
        */
        pref = j==n?j:pref;
        suf = k==n?k:suf;
        //cout << "saiu" << endl;
        tuple<int,int,int,int,int> exced = make_tuple(0,1,1,3,1);
        auto aux = idx==Q.size()?exced:Q[idx];
        auto aux2 = idx2==Q.size()?exced:Q[idx2];
        int s1 ,s2;
        while(get<0>(aux) < pref || get<0>(aux2) < suf){
            /*
            repetimos esse while salvando todas as queries que podemos resolver atualmente
            os ifs evitam escrever de novo em uma querie ou ir para uma que ainda nao temos
            solução.
            as variaveis s1 e s2 evitam que caiamos em um loop infinito, pois pode ocorrer
            casos onde a temperatura solicitada por aux ou aux2 é menor que o limitante,
            porem o idx não está sento atualizado pois já chegou ao fim, então afim de evitar
            um loop infinito usamos essas variaveis (deve ter um jeito mais facil de 
            resolver isso).
            */
            s1 = idx; s2 = idx2;
            int pos = paths[get<1>(aux)-1][get<2>(aux)-1];
            int pos2 = sufpaths[get<1>(aux2)-1][get<2>(aux2)-1];
            if(get<0>(aux) < pref && get<3>(aux)==0) res[get<4>(aux)] = pos;
            if(get<0>(aux2) < suf && get<3>(aux2)==1) res[get<4>(aux2)] =pos2;
            if(idx < Q.size() && get<0>(aux) < pref)idx++;
            if(idx2 < Q.size() && get<0>(aux2) < suf)idx2++;
            if(idx < Q.size()) aux = Q[idx];
            if(idx2 < Q.size()) aux2 = Q[idx2];
            if(idx >= Q.size() && idx2 >= Q.size()) goto next;
            if(idx == s1 && idx2 == s2) break;
        }

    }
    next:
    for(auto i:res) i==0x3f3f3f?cout << "-1" << endl:cout << i << endl;

}

