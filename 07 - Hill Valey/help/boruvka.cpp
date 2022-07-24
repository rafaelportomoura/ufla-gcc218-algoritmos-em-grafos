#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
using namespace std;

class DisjointSet {
private:
  int* pai;
  int* rank;
public:
  DisjointSet(int n) {
    pai = new int[n];
    rank = new int[n];
    for (int i=0; i<n; i++) {
      pai[i] = i;
      rank[i] = 0;
    }
  }

  ~DisjointSet() {
    delete[] pai;
    delete[] rank;
  }

  int busca_pai(int u) {
    if (pai[u] == u) {
      return u;
    }
    pai[u] = busca_pai(pai[u]);
    return pai[u];
  }

  bool mesmo_conjunto(int u, int v) { 
    return busca_pai(u) == busca_pai(v);
  }

  void conecta(int u, int v) {
    if (mesmo_conjunto(u, v)) 
      return;

    if (rank[u] > rank[v]) {
      pai[busca_pai(v)] = busca_pai(u);
    } else {
      pai[busca_pai(u)] = busca_pai(v);
      if (rank[u] == rank[v])
        rank[busca_pai(v)] += 1;
    }
  }
};

struct aresta {
  int u;
  int v;
  int custo;

  static bool compare(aresta a1, aresta a2) {
    return a1.custo < a2.custo;
  }
};

int boruvka(vector<aresta> &arestas, int n, int m) {
  DisjointSet dj(n);
  vector<aresta> arvore;
  int total = 0;
  int numero_arestas = 0;
  while (numero_arestas < n-1) {
    vector<aresta>::iterator menor = arestas.begin();
    for(vector<aresta>::iterator it = arestas.begin(); it < arestas.end(); it++) {
      if (!dj.mesmo_conjunto(it->u, it->v)) {
        if ((it->custo < menor->custo) || dj.mesmo_conjunto(menor->u, menor->v))
          menor = it;
      }
    }
    dj.conecta(menor->u, menor->v);
    total += menor->custo;
    arestas.erase(menor);
    numero_arestas++;
  }
  return total;
}

int main() {
  vector<aresta> arestas;
  int n, m;
  cin >> n >> m;

  for(int i=0; i<m; i++) {
    int u, v, custo;
    cin >> u >> v >> custo;
    aresta a;
    a.u = u;
    a.v = v;
    a.custo = custo; 
    arestas.push_back(a);
  }
  int c = boruvka(arestas, n, m);
  cout << "Custo Minimo: " << c << "\n";
  return 0; 

  return 0;
}