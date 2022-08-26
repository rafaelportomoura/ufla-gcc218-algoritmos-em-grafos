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
    output << "ID: " << v.id + 1;
    // output << "\n\tColor: " << v.color;
    // output << "\n\tDistance: " << v.distance;
    // output << "\n\tFather: ";
    // if ( v.father ) output << v.father->getId() + 1;
    // else output << "NULL";
    output << "\n\tEdges:";
    for ( Vertex* x : v.edges ) {
      output << " " << x->getId() + 1;
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

class OrientedGraph {
  public:
  OrientedGraph( int number_of_vertex ) {
    this->number_of_vertex = number_of_vertex;
    this->adjacency_list = new Vertex * [number_of_vertex];
    for ( int id = 0; id < number_of_vertex; id++ ) {
      this->adjacency_list[id] = new Vertex( id );
    }
  }
  void addEdge( int u, int v ) {
    this->adjacency_list[u]->addEdge( this->adjacency_list[v] );
  }
  friend ostream& operator<<( ostream& output, const OrientedGraph g ) {
    output << "Number of vertex: " << g.number_of_vertex << endl;
    output << "\nAdjacency list:\n";
    for ( int id = 0; id < g.number_of_vertex; id++ ) {
      output << *g.adjacency_list[id] << endl;
    }
    return output;
  }
  private:
  Vertex** adjacency_list;
  int number_of_vertex;

};

class Graph {
  public:
  Graph( int number_of_vertex ) {
    this->number_of_vertex = number_of_vertex;
    this->adjacency_list = new Vertex * [number_of_vertex];
    for ( int id = 0; id < number_of_vertex; id++ ) {
      this->adjacency_list[id] = new Vertex( id );
    }
    this->root = NULL;
    this->target = NULL;
    this->graph = new OrientedGraph( number_of_vertex );
  }
  void addEdge( int u, int v ) {
    this->adjacency_list[u]->addEdge( this->adjacency_list[v] );
    this->adjacency_list[v]->addEdge( this->adjacency_list[u] );
  }
  void BFS_Search( int vertex, queue<int>& bfs_queue ) {
    vector<Vertex*> edges = this->adjacency_list[vertex]->getEdges();
    for ( Vertex* edge : edges ) {
      if ( edge->getColor() == WHITE ) {
        this->graph->addEdge( vertex, edge->getId() );
        edge->changeColor( GRAY );
        edge->setFather( this->adjacency_list[vertex] );
        bfs_queue.push( edge->getId() );
      }
    }
  }

  void print() {
    cout << *this->graph;
  }

  void BFS( int root, int target ) {
    this->root = this->adjacency_list[root];
    this->target = this->adjacency_list[target];
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
    output << "X: " << g.root->getId() + 1;
    output << "\nY: " << g.target->getId() + 1;
    output << "\nAdjacency list:\n";
    for ( int id = 0; id < g.number_of_vertex; id++ ) {
      output << *g.adjacency_list[id] << endl;
    }
    return output;
  }
  private:
  OrientedGraph* graph;
  Vertex** adjacency_list;
  int number_of_vertex;
  Vertex* root;
  Vertex* target;
};


int main() {
  int number_of_vertex, number_of_edges, root, u, v, target;
  cin >> number_of_vertex >> number_of_edges;
  while ( number_of_vertex && number_of_edges ) {
    Graph g( number_of_vertex );
    for ( int i = 0; i < number_of_edges; i++ ) {
      cin >> u >> v;
      g.addEdge( u - 1, v - 1 );
    }
    cin >> root >> target;
    g.BFS( root - 1, target - 1 );
    g.print();
    cout << endl << "---------------------" << endl;
    cin >> number_of_vertex >> number_of_edges;
  }
  return 0;
}