#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Aresta {
  int u;
  int v;
  int custo;

  static bool compare( Aresta a1, Aresta a2 ) {
    return a1.custo < a2.custo;
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
public:
  DisjointSet( int n ) {
    pai = new int[n];
    rank = new int[n];
    for ( int i = 0; i < n; i++ ) {
      pai[i] = i;
      rank[i] = 0;
    }
  }

  ~DisjointSet() {
    delete[ ] pai;
    delete[ ] rank;
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
    ler_ligacoes_de_pontos();
  }
  int Kruskall() {
    sort( this->arestas.begin(), this->arestas.end(), Aresta::compare );

    int arestas_encontradas = 0;
    int i = 0;
    int resultado = 0;
    DisjointSet dj( this->pontos_principais );
    Aresta menor = arestas[i];
    while ( arestas_encontradas < this->pontos_principais - 1 ) {
      Aresta a = arestas[i];
      if ( !dj.mesmo_conjunto( a.u, a.v ) ) {
        dj.conecta( a.u, a.v );
        arestas_encontradas++;
        resultado += a.custo;
      }
      i++;
    }
    return resultado;
  }
  Resultado retorna_resultados( int quantidade_de_resultados ) {
    Resultado resultado( quantidade_de_resultados );
    for ( int i = 0; i < quantidade_de_resultados; i++ ) {
      resultado += this->Kruskall();
    }

    return resultado;
  }
private:
  int pontos_principais;
  int ligacoes;
  vector<Aresta> arestas;
  void ler_ligacoes_de_pontos() {
    for ( int ligacao = 0; ligacao < this->ligacoes; ligacao++ ) {
      Aresta aresta;
      cin >> aresta.u >> aresta.v >> aresta.custo;
      this->arestas.push_back( aresta );
    }
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