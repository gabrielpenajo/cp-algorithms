#include <bits/stdc++.h>
#define odd(i) (i&1) // verifica se o numero eh impar (caso o bit menos significativo seja 1)
#define even(i) (!(i&1)) // verifica se o numero eh par
#define fr(i, j) for(int i=0; i<j;++i) // loop for mais compacto para uso geral
#define pb push_back
#define mp make_pair
#define f first
#define s second
#define len(i) ((int) i.size())

using namespace std;

using pii = pair<int, int>;
using ll = long long;
template<class T>
using vec = vector<T>;
using vi = vec<int>;
using vll = vec<ll>;
using vec2 = vec<vec<int>>;
using vec3 = vec<vec2>;
using vec4 = vec<vec3>;
using graph = vec2;

fstream is;
fstream os;

// verifica os argumentos inseridos no terminal ao rodar o programa e abre o 
// modo debug do programa.
// modo de uso: execute o comando "./[nome_exec] -d" ou "./[nome_exec] -D" para
// rodar o debug.
void init(int argc, char *argv[]) { // ./nome opcao1
    if (argc > 1) {
        fr (i, argc) {
            if (string(argv[i]) == "-d" || string(argv[i]) == "-D") {
                string inname; cout << "text file name: ";
                cin >> inname; inname += ".in";
                is.open(inname, fstream::in);
                if (is.bad())
                    exit(1);
            }
        }
    }
}
// destroi o leitor do arquivo de texto, caso o modo debug esteja ativo.
void dest() {
    if (is.is_open())
        is.close();
}

// funcao customizada para ler input. aceita multiplos argumentos, de quaisquer
// tipos primarios de dados (int, double, float, char, string, etc.).
// uso: rd(ARG_1, ARG_2, ..., ARG_N)
template<class T>
void rd(T& var) {
    if (is.is_open()) is >> var;
    else cin >> var;
}
template<class T, class... Ts>
void rd(T& var, Ts&... ts) {
    if (is.is_open()) is >> var;
    else cin >> var;
    rd(ts...);
}

// funcao customizada para printar strings formatadas. semelhante ao printf,
// porem nao eh necessario especificar a mascara dos tipos de dados.
// uso: print([STRING_MODELO], ARG_1, ARG_2, ..., ARG_N)
//      para formatar argumentos na string, utilizar o caractere '%'
// ex: print("% world! % % %", "Hello", 1, 2, 3)
// saida: "Hello, world! 1 2 3"
// baseado em: https://en.cppreference.com/w/cpp/language/parameter_pack
void print(const char* format)
{
    cout << format;
}
template<typename T, typename... Targs>
void print(const char* format, T value, Targs... Fargs)
{
    for ( ; *format != '\0'; format++ ) {
        if ( *format == '%' ) {
           cout << value;
           print(format+1, Fargs...);
           return;
        }
        cout << *format;
    }
}

// implementacao da solucao do exercicio.
void sol() {
    int a, b, c; rd(a, b, c);
    // printf("%d %c", inteiro, char)
    print("% world! Your input: %\n", "Hello");
}

// main generica
int main(int argc, char *argv[]) {
    init(argc, argv);
    sol();
    dest();
    return 0;
}
