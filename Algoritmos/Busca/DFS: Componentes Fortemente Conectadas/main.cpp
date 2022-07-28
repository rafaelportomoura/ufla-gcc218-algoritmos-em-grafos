#include <iostream>
#include <vector>
#include "../../Libs/Status.hpp"

using namespace std;

int min( int a, int b ) {
  if ( a <= b ) {
    return a;
  }
  else {
    return b;
  }
}

class Vertex {
  public:
  Vertex( int id ) {
    this->id = id;
    this->status = NOT_VISITED;
    this->find_time = 0;
    this->low = 0;
  }
  int getId() { return this->id; }
  void changeStatus( Status c ) { this->status = c; }
  Status getStatus() { return this->status; }
  void addEdge( Vertex* target ) {
    if ( !target ) return;

    edges.push_back( target );
  }
  vector<Vertex*> getEdges() { return this->edges; }
  friend ostream& operator<<( ostream& output, const Vertex v ) {
    output << "ID: " << v.id + 1;
    output << "\n\tStatus: " << v.status;
    output << "\n\tLow: " << v.low;
    output << "\n\tFind Time: " << v.find_time;
    output << "\n\tEdges:";
    for ( Vertex* x : v.edges ) {
      output << " " << x->getId() + 1;
    }
    output << endl;
    return output;
  }
  void setLow( int low ) { this->low = low; }
  void setFindTime( int find_time ) { this->find_time = find_time; }

  int getLow() { return this->low; }
  int getFindTime() { return this->find_time; }
  private:
  int id;
  Status status;
  vector<Vertex*> edges;
  int low;
  int find_time;
};

class Graph {
  public:
  Graph( int number_of_vertex ) {
    this->number_of_vertex = number_of_vertex;
    this->adjacency_list = new Vertex * [number_of_vertex];
    for ( int id = 0; id < number_of_vertex; id++ ) {
      this->adjacency_list[id] = new Vertex( id );
    }
  }
  void addEdge( int u, int v ) {
    this->adjacency_list[u]->addEdge( this->adjacency_list[v] );
  }
  friend ostream& operator<<( ostream& output, const Graph g ) {
    output << "Number of vertex: " << g.number_of_vertex << endl;
    output << "Adjacency list:\n";
    for ( int id = 0; id < g.number_of_vertex; id++ ) {
      output << *g.adjacency_list[id] << endl;
    }
    output << endl;
    output << "CFCs:";
    for ( vector<int> cfc : g.CFCs ) {
      output << "\n\tCFC:";
      for ( int v : cfc ) {
        output << " " << v + 1;
      }
    }
    output << endl;
    return output;
  }
  void TARJAN_CFC( int id, int& cont_dfs, vector<int>& stack ) {
    cont_dfs++;

    Vertex* tarjan_vertex = this->adjacency_list[id];
    tarjan_vertex->changeStatus( VISITED );
    tarjan_vertex->setLow( cont_dfs );
    tarjan_vertex->setFindTime( cont_dfs );

    vector<Vertex*> adjacency_list;
    adjacency_list = tarjan_vertex->getEdges();

    stack.push_back( id );

    for ( Vertex* v : adjacency_list ) {
      if ( v->getStatus() == NOT_VISITED ) {
        TARJAN_CFC( v->getId(), cont_dfs, stack );
      }

      if ( v->getStatus() == VISITED ) {
        tarjan_vertex->setLow( min( tarjan_vertex->getLow(), v->getLow() ) );
      }
    }

    if ( tarjan_vertex->getLow() == tarjan_vertex->getFindTime() ) {
      vector<int> cfc;
      int v = -1;
      while ( id != v ) {
        cout << v;
        v = stack.back();
        stack.pop_back();

        cfc.push_back( v );
        this->adjacency_list[v]->changeStatus( CFC_NULL );
      }
      CFCs.push_back( cfc );
    }
  }

  void DFS() {
    vector<int> stack;
    int time = 0;
    for ( int id = 0; id < this->number_of_vertex; id++ ) {
      if ( this->adjacency_list[id]->getStatus() == NOT_VISITED ) {
        TARJAN_CFC( id, time, stack );
      }
    }
  }

  private:
  Vertex** adjacency_list;
  int number_of_vertex;
  vector<vector<int>> CFCs;
};

int main() {
  int number_of_vertex, number_of_edges, u, v;
  cin >> number_of_vertex >> number_of_edges;
  Graph g( number_of_vertex );
  for ( int i = 0; i < number_of_edges; i++ ) {
    cin >> u >> v;
    g.addEdge( u - 1, v - 1 );
  }
  g.DFS();
  cout << g;
  return 0;
}