#include <iostream>
#include <vector>
#include "../../Libs/Status.hpp"

using namespace std;

class Vertex {
  public:
  Vertex( int id ) {
    this->id = id;
    this->father = NULL;
    this->status = NOT_VISITED;
  }
  int getId() { return this->id; }
  void setFather( Vertex* father ) {
    if ( !father ) return;

    this->father = father;
  }
  Vertex* getFather() { return this->father; }
  void changeStatus( Status c ) { this->status = c; }
  Status getStatus() { return this->status; }
  void addEdge( Vertex* target ) {
    if ( !target ) return;

    edges.push_back( target );
  }
  vector<Vertex*> getEdges() { return this->edges; }
  friend ostream& operator<<( ostream& output, const Vertex v ) {
    output << "ID: " << v.id;
    output << "\n\tStatus: " << v.status;
    output << "\n\tFather: ";
    if ( v.father ) output << v.father->getId();
    else output << "NULL";
    output << "\n\tEdges:";
    for ( Vertex* x : v.edges ) {
      output << " " << x->getId();
    }
    output << endl;
    return output;
  }
  private:
  int id;
  Vertex* father;
  Status status;
  vector<Vertex*> edges;
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
    this->adjacency_list[v]->addEdge( this->adjacency_list[u] );
  }
  friend ostream& operator<<( ostream& output, const Graph g ) {
    output << "Number of vertex: " << g.number_of_vertex << endl;
    output << "Adjacency list:\n";
    for ( int id = 0; id < g.number_of_vertex; id++ ) {
      output << *g.adjacency_list[id] << endl;
    }
    return output;
  }
  void DFS_VISIT( vector<int>& stack ) {
    while ( !stack.empty() ) {
      int id = stack.back();
      stack.pop_back();
      vector<Vertex*> adjacency_vertex;
      adjacency_vertex = this->adjacency_list[id]->getEdges();
      for ( Vertex* v : adjacency_vertex ) {
        if ( v->getStatus() == NOT_VISITED ) {
          stack.push_back( v->getId() );
          v->changeStatus( VISITED );
          v->setFather( this->adjacency_list[id] );
          DFS_VISIT( stack );
        }
      }
    }
  }
  void DFS() {
    vector<int> stack;
    for ( int id = 0; id < this->number_of_vertex; id++ ) {
      if ( this->adjacency_list[id]->getStatus() == NOT_VISITED ) {
        stack.push_back( id );
        this->adjacency_list[id]->changeStatus( VISITED );
        DFS_VISIT( stack );
      }
    }
  }

  private:
  Vertex** adjacency_list;
  int number_of_vertex;

};

int main() {
  int number_of_vertex, number_of_edges, u, v;
  cin >> number_of_vertex >> number_of_edges;
  Graph g( number_of_vertex );
  for ( int i = 0; i < number_of_edges; i++ ) {
    cin >> u >> v;
    g.addEdge( u, v );
  }
  g.DFS();
  cout << g;
  return 0;
}