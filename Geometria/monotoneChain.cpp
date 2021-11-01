#include<bits/stdc++.h>
#define ll long long int
#define vi vector<int>
#define pii pair<int,int>
#define vll vector<ll>
#define msi multiset<int>
using namespace std;

struct Point {
	ll x, y;

	Point(ll x = 0, ll y = 0) {
		this->x = x;
		this->y = y;
	}
	Point operator+(Point &b) {
		return Point(x + b.x, y + b.y);
	}
	Point operator-(Point &b) {
		return Point(x - b.x, y - b.y);
	}
	//escalar
	ll operator*(Point &b) {
		return x*b.x + y*b.y;
	}
	//vetorial
	ll operator^(Point &b) {
		return x*b.y - y*b.x;
	}

    bool operator==(Point& b) {
        return x == b.x && y == b.y;
    }

    bool operator <(Point& b) {
        return x < b.x || (x == b.x && y < b.y);
    }
};

ll vetorial(Point o, Point a, Point b) {
    return (a.x - o.x)*(b.y - o.y) - (a.y - o.y)*(b.x - o.x);
}

/*
retorna um vetor de pontos no convex hull, em sentido anti horario
algoritmo: monotone chain
    constroi um fecho convexo em 2 etapas:
    1- constroi o fecho convexo inferior
    2- constroi o fecho convexo superior
*/
vector<Point> convex_hull(vector<Point> points){
	int n = points.size(), k = 0;
	// Caso trivial: um triangulo está sempre ordenado em sentido anti horario
    // ou menos de 3 pontos nao formam um poligono
    if (n <= 3)
        return points;
    vector<Point> hull(2*n);
    sort(points.begin(), points.end());
    // etapa 1
    for (int i = 0; i < n; i++) {
        // se o ponto na (k-1)-esima posicao nao deveria estar no fecho,
        // entao os vetores hull[k-2]->hull[k-1] e hull[k-2]->points[i] tem
        // produto vetorial menor ou igual a 0, o que nao deveria acontecer (ver pontoEmPoligono)
        while (k >= 2 && vetorial(hull[k-2], hull[k-1], points[i]) <= 0)
            k--;
        
        hull[k++] = points[i];
    }
    // etapa 2
    for (int i = n-2, t = k+1; i > 0; i--) {
        // compara pontos apenas fora do fecho construido inferiormente
        while (k >= t && vetorial(hull[k-2], hull[k-1], points[i]) <= 0)
            k--;
        
        hull[k++] = points[i];
    }
    hull.resize(k);
    return hull;
}

int main(){
	int total; cin >> total;
	vector<Point> points(total);
	for (auto& cur : points) {
		cin >> cur.x >> cur.y;
	}
    vector<Point> hull = convex_hull(points);
    for (auto i : hull) {
        cout << "(" << i.x << ", " << i.y << ")" << endl;
    }
    return 0;
}
/*
Exemplo:
7
0 3
2 2
1 1
2 1
3 0
0 0
3 3
Saida:
(0, 0)
(3, 0)
(3, 3)
(0, 3)
*/