#include <iostream>
#include <vector>
#include <queue>

using namespace std;

enum Color {
  WHITE,
  GRAY,
  BLACK
};

class Vertex {
  public:
  Vertex( int id ) {
    this->id = id;
    this->father = NULL;
    this->distance = 0;
    this->color = WHITE;
  }
  int getId() { return this->id; }
  int getDistance() { return this->distance; }
  void setFather( Vertex* father ) {
    if ( !father ) return;

    this->father = father;
    this->distance = father->getDistance() + 1;
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
    output << "ID: " << v.id;
    output << "\n\tColor: " << v.color;
    output << "\n\tDistance: " << v.distance;
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
  vector<Vertex*> edges;
  Color color;
  Vertex* father;
  int distance;
  int id;
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
  void BFS_Search( int vertex, queue<int>& bfs_queue ) {
    vector<Vertex*> edges = this->adjacency_list[vertex]->getEdges();
    for ( Vertex* edge : edges ) {
      if ( edge->getColor() == WHITE ) {
        edge->changeColor( GRAY );
        edge->setFather( this->adjacency_list[vertex] );
        bfs_queue.push( edge->getId() );
      }
    }
  }
  void BFS( int root ) {
    queue<int> bfs_queue;
    bfs_queue.push( root );
    while ( !bfs_queue.empty() ) {
      int search = bfs_queue.front();
      bfs_queue.pop();
      if ( this->adjacency_list[search]->getColor() == WHITE ) {
        this->adjacency_list[search]->changeColor( GRAY );
      }
      BFS_Search( search, bfs_queue );
      this->adjacency_list[search]->changeColor( BLACK );
    }
  }
  friend ostream& operator<<( ostream& output, const Graph g ) {
    output << "Number of vertex: " << g.number_of_vertex << endl;
    output << "Adjacency list:\n";
    for ( int id = 0; id < g.number_of_vertex; id++ ) {
      output << *g.adjacency_list[id] << endl;
    }
    return output;
  }
  private:
  Vertex** adjacency_list;
  int number_of_vertex;
};


int main() {
  int number_of_vertex, number_of_edges, root, u, v;
  cin >> number_of_vertex >> number_of_edges >> root;
  Graph g( number_of_vertex );
  for ( int i = 0; i < number_of_edges; i++ ) {
    cin >> u >> v;
    g.addEdge( u, v );
  }
  g.BFS( root );
  cout << g;
  return 0;
}