#include <iostream>
#include <vector>

using namespace std;

enum Color {
  WHITE,
  GRAY,
  BLACK
};

struct Edges {
  int u;
  int v;
  Edges( int u, int v ) {
    this->u = u;
    this->v = v;
  }
};

ostream& operator<<( ostream& output, const Edges& edges ) {
  output << edges.u + 1 << "-" << edges.v + 1;
  return output;
}

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
    this->father = NULL;
    this->color = WHITE;
    this->find_time = 0;
    this->low = 0;
    articulation = false;
  }
  int getId() { return this->id; }
  void setFather( Vertex* father ) {
    if ( !father ) return;

    this->father = father;
  }
  Vertex* getFather() { return this->father; }
  void changeColor( Color c ) { this->color = c; }
  Color getColor() { return this->color; }
  void addEdge( Vertex* target ) {
    if ( !target ) return;

    edges.push_back( target );
  }
  vector<Vertex*> getEdges() { return this->edges; }
  friend ostream& operator<<( ostream& output, const Vertex v ) {
    output << "ID: " << v.id + 1;
    output << "\n\tColor: " << v.color;
    output << "\n\tLow: " << v.low;
    output << "\n\tFind Time: " << v.find_time;
    string articulation = v.articulation ? "True" : "False";
    output << "\n\tArticulation: " << articulation;
    output << "\n\tFather: ";
    if ( v.father ) output << v.father->getId() + 1;
    else output << "NULL";
    output << "\n\tEdges:";
    for ( Vertex* x : v.edges ) {
      output << " " << x->getId();
    }
    output << endl;
    return output;
  }
  void setLow( int low ) { this->low = low; }
  void setFindTime( int find_time ) { this->find_time = find_time; }
  int getLow() { return this->low; }
  int getFindTime() { return this->find_time; }
  void setArticulation( bool articulation ) { this->articulation = articulation; }
  bool getArticulation() { return this->articulation; }
private:
  int id;
  Vertex* father;
  Color color;
  vector<Vertex*> edges;
  int low;
  int find_time;
  bool articulation;
};

class Graph {
public:
  Graph( int number_of_vertex ) {
    this->number_of_vertex = number_of_vertex;
    this->adjacency_list = new Vertex * [number_of_vertex];
    for ( int id = 0; id <= number_of_vertex; id++ ) {
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
    output << endl;
    output << "Bridging edges:\n";
    for ( Edges bridge : g.bridges ) {
      cout << "\t" << bridge << endl;
    }
    return output;
  }
  void TARJAN( int id, int cont_dfs, int root, int& sons_of_root ) {
    cont_dfs++;
    int low = cont_dfs;
    int find_time = cont_dfs;
    Vertex* tarjan_vertex = this->adjacency_list[id];
    tarjan_vertex->changeColor( GRAY );
    tarjan_vertex->setLow( low );
    tarjan_vertex->setFindTime( find_time );
    vector<Vertex*> adjacency_vertex;
    adjacency_vertex = tarjan_vertex->getEdges();
    for ( Vertex* v : adjacency_vertex ) {
      if ( id == root ) {
        sons_of_root++;
      }
      if ( v->getColor() == WHITE ) {
        v->setFather( tarjan_vertex );
        TARJAN( v->getId(), cont_dfs, root, sons_of_root );
        if ( v->getLow() >= tarjan_vertex->getLow() ) {
          tarjan_vertex->setArticulation( true );
          if ( v->getLow() > tarjan_vertex->getLow() ) {
            Edges brige( id, v->getId() );
            bridges.push_back( brige );
          }
        }
        tarjan_vertex->setLow( min( tarjan_vertex->getLow(), v->getLow() ) );
      }
      else if ( v != tarjan_vertex->getFather() ) {
        tarjan_vertex->setLow( min( tarjan_vertex->getLow(), v->getLow() ) );
      }
    }
    tarjan_vertex->changeColor( BLACK );
  }

  void DFS() {
    vector<int> stack;
    for ( int id = 0; id < this->number_of_vertex; id++ ) {
      if ( this->adjacency_list[id]->getColor() == WHITE ) {
        int sons = 0;
        TARJAN( id, 0, id, sons );
        this->adjacency_list[id]->setArticulation( sons > 1 );
      }
    }
  }

private:
  Vertex** adjacency_list;
  int number_of_vertex;
  vector<Edges> bridges;
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