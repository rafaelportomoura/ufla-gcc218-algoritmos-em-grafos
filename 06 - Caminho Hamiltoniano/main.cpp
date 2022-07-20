#include<iostream>
#include<vector>
using namespace std;

typedef vector<int> vi;

int obtemMenorGrauDeEntrada( int* grau_entrada, int n ) {
  int menor = n + 1;
  int indice = -1;
  for ( int i = 0; i < n; i++ ) {
    if ( menor > grau_entrada[i] && grau_entrada[i] >= 0 ) {
      indice = i;
      menor = grau_entrada[i];
    }
  }
  grau_entrada[menor] = -1;
  return indice;
}

/*
 * Parâmetros:
 *  LA: lista de adjacência do grafo.
 *  n: quantidade de vértices do grafo.
 * Retorna: um vector<int> com a sequência de vértices que forma o caminho
 * Hamiltoniano. Caso não haja, retorna um vector<int> vazio.
 */
vi caminhoHamiltoniano( vi* LA, int n, int* grau_entrada ) {
  vi resposta; // caminho Hamiltoniano, se houver.

  int menor = obtemMenorGrauDeEntrada( grau_entrada, n );
  int vertices_encontrados = 0;

  while ( menor >= 0 ) {
    resposta.push_back( menor );
    vertices_encontrados++;
    vi vertice_busca = LA[menor];
    int menor_filho = n + 1;
    menor = -1;
    for ( int vertice : vertice_busca ) {
      if ( grau_entrada[vertice] >= 0 && grau_entrada[vertice] < menor_filho ) {
        menor_filho = grau_entrada[vertice];
        menor = vertice;
      }
    }
    if ( menor >= 0 ) {
      grau_entrada[menor] = -1;
    }
  }

  if ( vertices_encontrados < n ) {
    vi empty;
    return empty;
  }

  return resposta;
}

int main() {
  // quantidade de vértices e quantidade de arcos
  int n, m;
  cin >> n >> m;
  int* grau_entrada = new int[n] {0};
  vi* LA = new vi[n];
  int u, v;
  for ( int i = 0; i < m; i++ ) {
    cin >> u >> v;
    grau_entrada[v - 1]++;
    LA[u - 1].push_back( v - 1 );
  }
  vi caminho = caminhoHamiltoniano( LA, n, grau_entrada );
  if ( caminho.empty() )
    cout << "Não há caminho Hamiltoniano" << endl;
  else {
    for ( auto v = caminho.begin(); v != caminho.end(); v++ )
      cout << *v + 1 << " ";
    cout << endl;
  }

  return 0;
}
