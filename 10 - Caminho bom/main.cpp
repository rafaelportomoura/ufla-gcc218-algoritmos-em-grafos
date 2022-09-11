#include <iostream>

using namespace std;

#include <iostream>
#include <vector>
#include <queue>

#define INF INT16_MAX

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
  }

  void addEdge( int u, int v, Weight w ) {
    la[u].push_back( Edge( v, w ) );
  }

  void visit( Heap& heap, int u ) {
    Weight cost;
    for ( Edge e : this->la[u] ) {
      int v = e.v;
      Weight w = e.weight;

      cost = this->estimated[u] + w;
      if ( cost < this->estimated[v] ) {
        this->father[v] = u;
        this->estimated[v] = cost;
        heap.push( Edge( v, this->estimated[v] ) );
      }

    }
  }

  int Dijkstra( int root, int target ) {
    this->estimated.assign( n, INF );
    this->father.assign( n, -1 );
    this->estimated[root] = 0;
    this->root = root;

    Heap heap;

    heap.push( Edge( root, 0 ) );

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

    return this->estimated[target];
  }

  int getElementIndex( int u, int v ) {
    int count = 0;
    for ( Edge e : this->la[u] ) {
      if ( e.v == v ) {
        return count;
      }
      count++;
    }
    return -1;
  }

  void eraseFathersEdge( int father ) {
    int v = father;
    father = this->father[v];
    while ( father > -1 ) {
      int index = this->getElementIndex( father, v );
      la[father].erase( la[father].begin() + index );
      v = father;
      father = this->father[v];
    }
  }

  int getGoodWay( int root, int target ) {
    int first_way = this->Dijkstra( root, target );
    int good_way = first_way;
    while ( good_way == first_way and good_way < INF ) {
      eraseFathersEdge( target );
      good_way = this->Dijkstra( root, target );
    }
    return good_way < INF ? good_way : -1;
  }

  friend ostream& operator<<( ostream& out, const Graph& g ) {
    for ( int i = 0; i < g.n; i++ ) {
      out << "Estimativa " << g.root + 1 << " -> " << i + 1 << " = " << g.estimated[i] << endl;
    }
    return out;
  }
private:
  int n;
  int root;
  vector<int> father;
  vector<Weight> estimated;
  vla* la;
};

int main() {
  int n, m;
  cin >> n >> m;
  while ( n && m ) {
    int root, target;
    cin >> root >> target;
    Graph g( n );
    int u, v;
    Weight w;
    for ( int i = 0; i < m; i++ ) {
      cin >> u >> v >> w;
      g.addEdge( u, v, w );
    }
    cout << g.getGoodWay( root, target ) << endl;
    cin >> n >> m;
  }
  return 0;
}