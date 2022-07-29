#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

enum COR {
  BRANCO,
  CINZA,
  PRETO
};
struct Aresta {
  int u;
  int v;
  int custo;

  void swap() {
    int aux = u;
    u = v;
    v = aux;
  }
  static bool compare( Aresta a1, Aresta a2 ) {
    return a1.custo < a2.custo;
  }
  bool operator!=( const Aresta a2 ) {
    return !( ( a2.u == u ) && ( a2.v == v ) || ( a2.u == v ) && ( a2.v == u ) );
  }
};

struct Resultado {
  int* resultados;
  int qtd = 0;
  int tam = 0;
  Resultado( int tam ) {
    this->tam = tam;
    this->resultados = new int[tam];
  }
};

Resultado operator+=( Resultado& r, const int i ) {
  if ( r.qtd >= r.tam ) return r;

  r.resultados[r.qtd] = i;
  r.qtd++;
  return r;
}

ostream& operator<<( ostream& output, const Resultado r ) {
  for ( int i = 0; i < r.qtd; i++ ) {
    output << r.resultados[i];
    if ( i < r.qtd - 1 ) output << " ";
  }
  return output;
}


class DisjointSet {
  private:
  int* pai;
  int* rank;
  int tam;
  int tam_vector;
  int init_vector;
  public:
  DisjointSet( int n ) {
    this->tam = n;
    this->init_vector = 1;
    this->tam_vector = this->tam + init_vector;
    pai = new int[this->tam_vector];
    rank = new int[this->tam_vector];
    for ( int i = this->init_vector; i < this->tam_vector; i++ ) {
      pai[i] = i;
      rank[i] = 0;
    }
  }

  int busca_pai( int u ) {
    if ( pai[u] == u ) {
      return u;
    }
    pai[u] = busca_pai( pai[u] );
    return pai[u];
  }

  bool mesmo_conjunto( int u, int v ) {
    return busca_pai( u ) == busca_pai( v );
  }

  void conecta( int u, int v ) {
    if ( mesmo_conjunto( u, v ) )
      return;

    if ( rank[u] > rank[v] ) {
      pai[busca_pai( v )] = busca_pai( u );
    }
    else {
      pai[busca_pai( u )] = busca_pai( v );
      if ( rank[u] == rank[v] )
        rank[busca_pai( v )] += 1;
    }
  }
};


class Hill_Valey {
  public:
  Hill_Valey( const int pontos_principais, const int ligacoes ) {
    this->ligacoes = ligacoes;
    this->pontos_principais = pontos_principais;
    grafo = new vector<Aresta>[pontos_principais + 1];
    ler_ligacoes_de_pontos();
  }
  Resultado retorna_resultados( int quantidade_de_resultados ) {
    Resultado resultado( quantidade_de_resultados );
    for ( int i = 0; i < quantidade_de_resultados; i++ ) {
      resultado += this->DFS() + this->Kruskall();
    }

    return resultado;
  }
  private:
  int pontos_principais;
  int ligacoes;
  vector<Aresta> arestas;
  vector<Aresta> arestas_nao_usadas;
  vector<Aresta>* grafo;

  void ler_ligacoes_de_pontos() {
    for ( int ligacao = 0; ligacao < this->ligacoes; ligacao++ ) {
      Aresta aresta;
      cin >> aresta.u >> aresta.v >> aresta.custo;
      this->arestas.push_back( aresta );
    }
  }

  bool menor_diferenca( vector<Aresta>* grafo, int u, int* cor, int* pai, Aresta a, int* menor ) {
    cor[u] = COR::CINZA;
    bool encontrou_ciclo = false;
    for ( Aresta aresta : grafo[u] ) {
      if ( pai[u] == aresta.v ) continue;
      if ( cor[aresta.v] == COR::BRANCO ) {
        pai[aresta.v] = u;
        encontrou_ciclo = menor_diferenca( grafo, aresta.v, cor, pai, a, menor );
      }
      else if ( cor[aresta.v] == COR::CINZA ) {
        encontrou_ciclo = true;
      }
      if ( encontrou_ciclo ) {
        if ( !( ( a.u == aresta.u ) && ( a.v == aresta.v ) || ( a.u == aresta.v ) && ( a.v == aresta.u ) ) ) {
          int diferenca_peso = a.custo - aresta.custo;
          if ( diferenca_peso < *menor ) {
            *menor = diferenca_peso;
          }
        }
        return encontrou_ciclo;
      }
    }
    cor[u] = COR::PRETO;
    return encontrou_ciclo;
  }

  int DFS() {
    if ( not this->arestas_nao_usadas.size() ) return 0;
    int* menor_diff = new int;
    *menor_diff = INT32_MAX;
    int* pai = new int[pontos_principais + 1];
    int* cor = new int[pontos_principais + 1];

    for ( Aresta a : arestas_nao_usadas ) {
      for ( int i = 0; i <= pontos_principais; i++ ) {
        pai[i] = -1;
        cor[i] = COR::BRANCO;
      }
      grafo[a.u].push_back( a );
      a.swap();
      grafo[a.u].push_back( a );
      menor_diferenca( grafo, a.u, cor, pai, a, menor_diff );
      grafo[a.u].pop_back();
      grafo[a.v].pop_back();
    }
    return *menor_diff;
  }

  int Kruskall() {
    sort( this->arestas.begin(), this->arestas.end(), Aresta::compare );

    int arestas_encontradas = 0;
    int i = 0;
    int resultado = 0;
    DisjointSet dj( this->pontos_principais );
    while ( i < this->ligacoes and arestas_encontradas < this->pontos_principais - 1 ) {
      Aresta a = arestas[i];
      if ( !dj.mesmo_conjunto( a.u, a.v ) ) {
        dj.conecta( a.u, a.v );
        arestas_encontradas++;
        resultado += a.custo;
        grafo[a.u].push_back( a );
        a.swap();
        grafo[a.u].push_back( a );
      }
      else {
        arestas_nao_usadas.push_back( a );
      }
      i++;
    }
    return resultado;
  }
};


int main() {
  int casos_de_teste;
  cin >> casos_de_teste;
  int pontos_principais;
  int ligacoes;
  Hill_Valey** hill_valey = new Hill_Valey * [casos_de_teste];
  for ( int caso = 0; caso < casos_de_teste; caso++ ) {
    cin >> pontos_principais >> ligacoes;
    hill_valey[caso] = new Hill_Valey( pontos_principais, ligacoes );
    cout << hill_valey[caso]->retorna_resultados( 2 );
    if ( caso < casos_de_teste - 1 ) cout << endl;
  }
  cout << endl;
}