#include <iostream>
#include <queue>
#include <vector>


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
    this->degree = 0;
    this->father = NULL;
    this->color = WHITE;
    this->distance = 0;
  }
  int getId() { return this->id; }
  int getDegree() const { return this->degree; }
  void upDegree() { this->degree++; }
  vector<Vertex*> getAdjacencyList() { return this->adjacency_list; }
  void makeHeap() {
    for ( Vertex* x : this->adjacency_list ) {
      this->heap.push( *x );
    }
  }
  priority_queue<Vertex> getHeap() { return this->heap; }
  void addEdge( Vertex* v ) {
    if ( !v ) return;
    this->adjacency_list.push_back( v );
  }
  void setFather( Vertex* father ) {
    if ( !father ) return;

    this->father = father;
    this->distance = father->getDistance() + 1;
  }
  Vertex* getFather() { return this->father; }
  int getDistance() { return this->distance; }
  void changeColor( Color c ) { this->color = c; }
  Color getColor() { return this->color; }
  private:
  int id;
  int degree;
  vector<Vertex*> adjacency_list;
  priority_queue<Vertex> heap;
  Vertex* father;
  Color color;
  int distance;

};

bool operator<( Vertex const& u, Vertex const& v ) {
  return u.getDegree() > v.getDegree();
}

class NotDirectedGraph {
  public:
  NotDirectedGraph( int number_of_vertex ) {
    this->number_of_vertex = number_of_vertex;
    vertex_list = new Vertex * [this->number_of_vertex];
    for ( int i = 0; i < this->number_of_vertex; i++ ) {
      vertex_list[i] = new Vertex( i );
    }
  }
  void addEdge( int u, int v ) {
    this->vertex_list[u]->addEdge( this->vertex_list[v] );
    this->vertex_list[v]->addEdge( this->vertex_list[u] );
  }
  void BFS_Search( int vertex, queue<int>& bfs_queue ) {
    priority_queue<Vertex> heap = this->vertex_list[vertex]->getHeap();
    while ( !heap.empty() ) {
      Vertex v = heap.top();
      Vertex* edge = this->vertex_list[v.getId()];
      heap.pop();
      if ( edge->getColor() == WHITE ) {
        edge->changeColor( GRAY );
        edge->setFather( this->vertex_list[vertex] );
        this->direct_graph_adjacency_matrix[vertex][edge->getId()] = 1;
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
      if ( this->vertex_list[search]->getColor() == WHITE ) {
        this->vertex_list[search]->changeColor( GRAY );
      }
      BFS_Search( search, bfs_queue );
      this->vertex_list[search]->changeColor( BLACK );
    }
  }
  int** getDirectGraph( int** adjacency_matrix, int source ) {
    this->direct_graph_adjacency_matrix = adjacency_matrix;
    for ( int i = 0; i < this->number_of_vertex; i++ ) this->vertex_list[i]->makeHeap();
    BFS( source );
    return this->direct_graph_adjacency_matrix;
  }
  private:
  Vertex** vertex_list;
  int** direct_graph_adjacency_matrix;
  int number_of_vertex;
};

class DirectedGraph {
  public:
  DirectedGraph( NotDirectedGraph g, int source_adjacency, int target_adjacency, int number_of_vertex ) {
    this->number_of_vertex = number_of_vertex + 2;
    this->source_vertex = number_of_vertex;
    this->target_vertex = number_of_vertex + 1;
    this->adjacency_matrix = new int* [this->number_of_vertex];
    for ( int i = 0; i < this->number_of_vertex; i++ ) {
      this->adjacency_matrix[i] = new int[this->number_of_vertex];
      for ( int j = 0; j < this->number_of_vertex; j++ ) {
        this->adjacency_matrix[i][j] = 0;
      }
    }
    CreateDirectedGraph( g, source_adjacency, target_adjacency );
  }
  int Edmonds_Karp() {

  }

  friend ostream& operator<<( ostream& output, const DirectedGraph g ) {
    output << "Number of vertex: " << g.number_of_vertex << endl;
    output << "Adjacency list:\n";
    for ( int id = 0; id < g.number_of_vertex; id++ ) {
      for ( int column = 0; column < g.number_of_vertex; column++ ) {
        output << g.adjacency_matrix[id][column] << " ";
      }
      output << endl;
    }
    return output;
  }
  private:
  void CreateDirectedGraph( NotDirectedGraph g, int source_adjacency, int target_adjacency ) {
    this->adjacency_matrix = g.getDirectGraph( this->adjacency_matrix, source_adjacency );
    this->adjacency_matrix[this->source_vertex][source_adjacency] = 2;
    this->adjacency_matrix[target_adjacency][this->target_vertex] = 2;
  }
  int** adjacency_matrix;
  int number_of_vertex;

  int source_vertex;
  int target_vertex;
};

int main() {
  int number_of_vertex, number_of_edges, u, v;
  cin >> number_of_vertex >> number_of_edges;
  while ( number_of_vertex && number_of_edges ) {
    NotDirectedGraph g( number_of_vertex );
    for ( int i = 0; i < number_of_edges; i++ ) {
      cin >> u >> v;
      g.addEdge( u - 1, v - 1 );
    }
    cin >> u >> v;
    g.BFS( u - 1 );
    DirectedGraph dg( g, u - 1, v - 1, number_of_vertex );
    cout << dg;
    cin >> number_of_vertex >> number_of_edges;
  }

  return 0;
}