#include <iostream>

using namespace std;

#include <iostream>
#include <vector>
#include <queue>

#define INF 1.0

using namespace std;

typedef double Weight;

struct Edge {
  int v;
  Weight weight;
  Edge( int v, Weight w ) : v( v ), weight( w ) {}
};

struct Comparator { bool operator()( Edge a, Edge b ) { return a.weight > b.weight; } };

typedef vector<Edge> vla;
typedef priority_queue < Edge, vector<Edge>, Comparator> Heap;


class Graph {
  public:
  Graph( int n ) :n( n ) {
    this->la = new vla[n];
    this->estimated.assign( n, INF );
  }

  void addEdge( int u, int v, Weight w ) {
    la[u].push_back( Edge( v, w ) );
  }

  void visit( Heap& heap, int u ) {
    Weight cost;
    for ( Edge e : this->la[u] ) {
      int v = e.v;
      Weight w = e.weight;

      cost = this->estimated[u] * w;

      if ( cost < this->estimated[v] ) {
        this->estimated[v] = cost;
        heap.push( Edge( v, this->estimated[v] ) );
      }

    }
  }

  void BellmanFord( int root ) {
    this->estimated[root] = INF;
    this->root = root;

    Heap heap;

    heap.push( Edge( root, INF ) );

    bool visited[this->n] = {};

    while ( !heap.empty() ) {
      Edge e = heap.top();
      heap.pop();

      int u = e.v;

      if ( !visited[u] ) {
        visited[u] = true;
        this->visit( heap, u );
      }
    }
  }

  friend ostream& operator<<( ostream& out, const Graph& g ) {
    for ( int i = 0; i < g.n; i++ ) {
      out << "Estimativa " << g.root + 1 << " -> " << i + 1 << " = " << INF - g.estimated[i] << endl;
    }
    return out;
  }
  private:
  int n;
  int root;
  vector<Weight> estimated;
  vla* la;
};

int main() {
  int n, m;
  cin >> n >> m;
  Graph g( n );
  int u, v;
  Weight w;
  for ( int i = 0; i < m; i++ ) {
    cin >> u >> v >> w;
    g.addEdge( u - 1, v - 1, 1.0 - w / 10.0 );
  }
  int root;
  cin >> root;
  g.BellmanFord( root );
  cout << g;
  return 0;
}