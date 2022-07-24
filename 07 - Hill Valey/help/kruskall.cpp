#include <iostream>
#include <vector>
#include <algorithm>

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

int kruskal(vector<aresta> &arestas, int n, int m) {
  sort(arestas.begin(), arestas.end(), aresta::compare);
  
  int arestas_encontradas = 0;
  int i = 0;
  int resultado = 0;
  DisjointSet dj(n);
  while (arestas_encontradas < n-1) {
    aresta a = arestas[i];
    if(!dj.mesmo_conjunto(a.u, a.v)) {
      dj.conecta(a.u, a.v); 
      arestas_encontradas++;
      resultado += a.custo;
    }
    i++;
  }
  return resultado;
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
  cout << "Custo Minimo: " << kruskal(arestas, n, m) << "\n";
  return 0; 
}

