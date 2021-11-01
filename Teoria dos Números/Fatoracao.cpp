#include<iostream>
#include<bits/stdc++.h>
#define ll long long int
#define vi vector<int>
#define pii pair<int,int>
#define vll vector<ll>
#define msi multiset<int>
#define mii map<int,int>
using namespace std;


mii fat(int n){
	mii res;
	int aux = n;
	for(int i = 2; i*i <= n; i++){
		while(aux%i == 0){
			res[i]++;
			aux /= i;
		}
	}
	return res;
   
}

int main(){
	int n; cin >> n;
	mii res = fat(n);
	for(auto i:res) cout <<"[" << i.first << "] = " << i.second << endl;
	
}
