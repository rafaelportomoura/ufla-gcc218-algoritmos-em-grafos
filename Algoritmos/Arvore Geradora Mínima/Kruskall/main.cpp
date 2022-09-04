#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

struct Vertex {
  int father;
  int rank;
  Vertex() {
    father = 0;
    rank = 0;
  }
};

struct Edge {
  int u;
  int v;
  int weight;
  Edge( int u, int v, int weight ) : u( u ), v( v ), weight( weight ) {};
};

struct Comparator {
  bool operator()( Edge a, Edge b ) {
   //Sorting on the basis of height(Just for example)
    return ( a.weight > b.weight );
  }
};

class UFDS {
  public:
  UFDS( int number_of_vertex ) {
    this->n = number_of_vertex;
    this->v = new Vertex[this->n];
    for ( int i = 0; i < this->n; i++ ) this->v[i].father = i;
  }

  int search_father( int i ) {
    if ( this->v[i].father == i ) return i;

    this->v[i].father = this->search_father( this->v[i].father );

    return this->v[i].father;
  }

  bool same_set( int u, int v ) {
    return search_father( u ) == search_father( v );
  }

  void union_set( int u, int v ) {
    if ( same_set( u, v ) ) return;

    int s1 = search_father( u );
    int s2 = search_father( v );

    if ( this->v[s1].rank > this->v[s2].rank ) this->v[s2].father = s1;
    else {
      this->v[s1].father = s2;
      if ( this->v[s1].rank == this->v[s2].rank ) this->v[s1].rank++;
    }
  }

  private:
  int n;
  Vertex* v;
};

int Kruskall( priority_queue<Edge, vector<Edge>, Comparator> edges, int number_of_vertex, int number_of_edges ) {
  int total_weight = 0;
  int total_of_edges = 0;
  int u, v;

  UFDS ufds( number_of_vertex );

  while ( not edges.empty() ) {
    Edge edge = edges.top();
    edges.pop();
    u = edge.u;
    v = edge.v;
    if ( not ufds.same_set( u, v ) ) {
      total_weight += edge.weight;
      total_of_edges++;
      if ( total_of_edges == number_of_vertex - 1 ) return total_weight;

      ufds.union_set( u, v );
    }
  }

  return total_weight;
}

int main() {
  priority_queue<Edge, vector<Edge>, Comparator> edge_heap;
  int n, m;
  cin >> n >> m;

  int u, v, w;

  for ( int i = 0; i < m; i++ ) {
    cin >> u >> v >> w;
    edge_heap.push( Edge( u, v, w ) );
  }

  cout << "Custo AGM: " << Kruskall( edge_heap, n, m );
  return 0;
}