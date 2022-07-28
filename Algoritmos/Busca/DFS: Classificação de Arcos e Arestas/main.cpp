#include <iostream>
#include <vector>
#include "../../Libs/Color.hpp"
#include "../../Libs/Arcs.hpp"

using namespace std;


class Vertex {
  public:
  Vertex( int id ) {
    this->id = id;
    this->father = NULL;
    this->color = WHITE;
    this->time_open = 0;
    this->time_closed = 0;
  }
  int getId() { return this->id; }
  void setFather( Vertex* father ) {
    if ( !father ) return;

    this->father = father;
  }
  Vertex* getFather() { return this->father; }
  void changeColor( Color c ) { this->color = c; }
  Color getColor() { return this->color; }
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
    output << "\n\t\tColor: " << v.color;
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
  Color color;
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
    return output;
  }
  void DFS_VISIT( vector<int>& stack, int& time ) {
    while ( !stack.empty() ) {
      time++;
      int id = stack.back();
      stack.pop_back();
      Vertex* origin = this->vertex_list[id];
      origin->changeColor( GRAY );
      origin->setTimeOpen( time );
      vector<Arcs*> arcs;
      arcs = origin->getArcs();
      for ( Arcs* a : arcs ) {
        Vertex* target = this->vertex_list[a->target];
        switch ( target->getColor() ) {
          case WHITE:
            a->type = THREE;
            stack.push_back( target->getId() );
            target->setFather( origin );
            DFS_VISIT( stack, time );
            break;

          case GRAY:
            a->type = RETURN;
            break;

          case BLACK:
            if ( target->getTimeClosed() < origin->getTimeOpen() ) {
              a->type = CROSSED;
            }
            else {
              a->type = DIRECT;
            }

          default:
            break;
        }
      }
      time++;
      this->vertex_list[id]->setTimeClosed( time );
      this->vertex_list[id]->changeColor( BLACK );
    }
  }
  void DFS() {
    vector<int> stack;
    int time = 0;
    for ( int id = 0; id < this->number_of_vertex; id++ ) {
      if ( this->vertex_list[id]->getColor() == WHITE ) {
        stack.push_back( id );
        DFS_VISIT( stack, time );
      }
    }
  }

  private:
  Vertex** vertex_list;
  int number_of_vertex;
  int number_of_arcs;
  vector<Arcs*> arcs_list;

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