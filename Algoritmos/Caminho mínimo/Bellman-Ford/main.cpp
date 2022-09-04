#include <iostream>
#include <vector>

#define INF INT16_MAX

using namespace std;


struct Edge {
  int v;
  int weight;
  Edge() {};
  Edge( int v, int w ) : v( v ), weight( w ) {}
};

typedef vector<Edge> vla;

class Graph {
public:
  Graph( int n ) :n( n ) {
    this->la = new vla[n];
    this->estimated.assign( n, INF );
  }

  void addEdge( int u, int v, int w ) {
    la[u].push_back( Edge( v, w ) );
  }

  void BellmanFord( int root ) {
    this->estimated[root] = 0;
    this->root = root;

    int v, w;

    for ( int i = 0; i < n - 1; i++ )
      for ( int u = 0; u < n; u++ )
        for ( Edge neightboor : this->la[u] ) {
          v = neightboor.v;
          w = neightboor.weight;
          this->estimated[v] = min( this->estimated[v], this->estimated[u] + w );
        }
  }

  friend ostream& operator<<( ostream& out, const Graph& g ) {
    for ( int i = 0; i < g.n; i++ ) {
      out << "Estimativa " << g.root << " -> " << i << " = " << g.estimated[i] << endl;
    }
    return out;
  }
private:
  int n;
  int root;
  vector<int> estimated;
  vla* la;
};

int main() {
  int n, m;
  cin >> n >> m;
  Graph g( n );
  int u, v, w;
  for ( int i = 0; i < m; i++ ) {
    cin >> u >> v >> w;
    g.addEdge( u, v, w );
  }
  int root;
  cin >> root;
  g.BellmanFord( root );
  cout << g;
  return 0;
}