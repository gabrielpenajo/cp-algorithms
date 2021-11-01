#include<iostream>
#include<bits/stdc++.h>
#define ll long long int
#define vi vector<int>
#define pii pair<int,int>
#define vll vector<ll>
#define msi multiset<int>
using namespace std;

struct Point{
	ll x,y;

	Point(ll x, ll y){
		this->x = x;
		this->y = y;
	}
	Point operator+(Point &b){
		return Point(x + b.x, y + b.y);
	}
	Point operator-(Point &b){
		return Point(x - b.x, y - b.y);
	}
	//escalar
	ll operator*(Point &b){
		return x*b.x + y*b.y;
	}
	//vetorial
	ll operator^(Point &b){
		return x*b.y - y*b.x;
	}
};

/*
recebemos um vetor de pontos(ordenado em sentido anti-horario), representando um poligono
e um ponto, return true se ponto dentro do poligono, false caso contrario

para calcular vamos fazer 2 vetores um com um lado do poligono
e outro entre um ponto do poligono e o ponto que estamos pesquisando
calculamos produto vetorial, se esse for menor que 0, o seno tambem é
assim o ponto vai para o lado de fora do poligono, return false.

*/
bool insidePol(vector<Point> polygon, Point a){
	int n = polygon.size();
	for(int i = 0; i < n; i++){
		Point p = polygon[(i+1)%n] - polygon[i];
		Point v = a - polygon[i];
		if((p^v) < 0) return false;
	}
	return true;
}

int main(){
	int sides;cin >> sides;
	vector<Point> polygon;
	for(int i = 0; i < sides; i++){
		int x,y; cin >> x >> y;
		Point a(x,y);
		polygon.push_back(a);
	}
	int x,y;
	cin >> x >> y;
	Point a(x,y);
	insidePol(polygon,a)?cout << "YES\n": cout << "NO\n";
}
