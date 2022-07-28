#include <iostream>
#include <vector>
#include "../../Libs/Status.hpp"
#include "../../Libs/Arcs.hpp"

using namespace std;


class Vertex {
  public:
  Vertex( int id ) {
    this->id = id;
    this->father = NULL;
    this->status = NOT_VISITED;
    this->time_open = 0;
    this->time_closed = 0;
  }
  int getId() { return this->id; }
  void setFather( Vertex* father ) {
    if ( !father ) return;

    this->father = father;
  }
  Vertex* getFather() { return this->father; }
  void changeStatus( Status c ) { this->status = c; }
  Status getStatus() { return this->status; }
  void addArc( Arcs* arc ) {
    if ( !arc ) return;
    if ( arc->origin != this->id ) return;

    arc_vertex.push_back( arc );
  }
  vector<Arcs*> getArcs() { return this->arc_vertex; }
  int getTimeOpen() { return this->time_open; }
  void setTimeOpen( int time ) { this->time_open = time; }
  int getTimeClosed() { return this->time_closed; }
  void setTimeClosed( int time ) { this->time_closed = time; }
  friend ostream& operator<<( ostream& output, const Vertex v ) {
    output << "\tID: " << v.id + 1;
    output << "\n\t\tStatus: " << v.status;
    output << "\n\t\tOpen: " << v.time_open;
    output << "\n\t\tClosed: " << v.time_closed;
    output << "\n\t\tFather: ";
    if ( v.father ) output << v.father->getId() + 1;
    else output << "NULL";
    output << "\n\t\tArcs:";
    for ( Arcs* x : v.arc_vertex ) {
      output << "\n\t\t\t" << *x;
    }
    output << endl;
    return output;
  }
  private:
  int id;
  Vertex* father;
  Status status;
  vector<Arcs*> arc_vertex;
  int time_open;
  int time_closed;
};

class Graph {
  public:
  Graph( int number_of_vertex, int number_of_arcs ) {
    this->number_of_vertex = number_of_vertex;
    this->vertex_list = new Vertex * [number_of_vertex];
    for ( int id = 0; id < number_of_vertex; id++ ) {
      this->vertex_list[id] = new Vertex( id );
    }
  }
  void addArc( int u, int v ) {
    Arcs* arc = new Arcs( u, v );
    this->arcs_list.push_back( arc );
    this->vertex_list[u]->addArc( arc );
  }
  friend ostream& operator<<( ostream& output, const Graph g ) {
    output << "Number of vertex: " << g.number_of_vertex << endl;
    output << "Vertex list:\n";
    for ( int id = 0; id < g.number_of_vertex; id++ ) {
      output << *g.vertex_list[id] << endl;
    }
    output << "Arc list:\n";
    for ( Arcs* arc : g.arcs_list ) {
      output << "\t" << *arc << endl;
    }
    output << "\nOrdered graph:\n\t";
    for ( int vertex : g.ordered_graph ) {
      output << vertex + 1 << " -> ";
    }
    return output;
  }
  void DFS_SORT( int id, vector<int>& stack, int& time ) {
    time++;
    Vertex* origin = this->vertex_list[id];
    origin->changeStatus( VISITED );
    origin->setTimeOpen( time );
    vector<Arcs*> arcs;
    arcs = origin->getArcs();
    for ( Arcs* a : arcs ) {
      Vertex* target = this->vertex_list[a->target];
      if ( target->getStatus() == NOT_VISITED ) {
        target->setFather( origin );
        DFS_SORT( a->target, stack, time );
      }
    }
    time++;
    stack.push_back( id );
    this->vertex_list[id]->setTimeClosed( time );
  }
  void DFS() {
    int time = 0;
    vector<int> order_stack;
    for ( int id = 0; id < this->number_of_vertex; id++ ) {
      if ( this->vertex_list[id]->getStatus() == NOT_VISITED ) {
        DFS_SORT( id, order_stack, time );
      }
    }
    while ( !ordered_graph.empty() ) {
      ordered_graph.pop_back();
    }
    while ( !order_stack.empty() ) {
      this->ordered_graph.push_back( order_stack.back() );
      order_stack.pop_back();
    }
  }

  private:
  Vertex** vertex_list;
  int number_of_vertex;
  int number_of_arcs;
  vector<Arcs*> arcs_list;
  vector<int> ordered_graph;

};

int main() {
  int number_of_vertex, number_of_arcs, u, v;
  cin >> number_of_vertex >> number_of_arcs;
  Graph g( number_of_vertex, number_of_arcs );
  for ( int i = 0; i < number_of_arcs; i++ ) {
    cin >> u >> v;
    g.addArc( u - 1, v - 1 );
  }
  g.DFS();
  cout << g;
  return 0;
}