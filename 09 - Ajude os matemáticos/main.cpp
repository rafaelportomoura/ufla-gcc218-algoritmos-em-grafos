#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

#define INF 10000000

using namespace std;

enum Color {
  WHITE,
  GRAY,
  BLACK
};

struct NotDirectGraphVertexStruct {
  int father;
  int dist;
  NotDirectGraphVertexStruct() {
    father = -1;
    dist = INF;
  }
};

class NotDirectedGraph {
  public:
  NotDirectedGraph( int number_of_vertex ) {
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
  }
  void setAdjacencyVertex( int source, int target ) {
    this->adjacency_matrix[this->source_vertex][source] = 2;
    this->adjacency_matrix[target][this->target_vertex] = 2;
  }
  void addEdge( int u, int v ) {
    this->adjacency_matrix[u][v]++;
    this->adjacency_matrix[v][u]++;
  }
  void BFS_VISIT( int u, queue<int>& bfs_queue ) {
    for ( int v = 0; v < this->number_of_vertex; v++ ) {
      if ( this->adjacency_matrix[u][v] && this->vertex_struct[v].dist == INF ) {
        this->vertex_struct[v].father = u;
        this->vertex_struct[v].dist = this->vertex_struct[u].dist + 1;
        bfs_queue.push( v );
      }
    }
  }

  void BFS() {
    this->vertex_struct = new NotDirectGraphVertexStruct[this->number_of_vertex];
    this->vertex_struct[this->source_vertex].dist = 0;
    queue<int> bfs_queue;
    bfs_queue.push( source_vertex );

    while ( !bfs_queue.empty() ) {
      int u = bfs_queue.front();
      bfs_queue.pop();
      if ( u == this->target_vertex ) return;
      BFS_VISIT( u, bfs_queue );
    }
  }

  void rising_way( int v, int flow_capacity, int& flow ) {
    if ( v == this->source_vertex ) {
      flow = flow_capacity;
      return;
    }
    else if ( this->vertex_struct[v].father != -1 ) {
      int father = this->vertex_struct[v].father;
      rising_way( father, min( flow_capacity, this->adjacency_matrix[father][v] ), flow );
      this->adjacency_matrix[father][v] -= flow;
      this->adjacency_matrix[v][father] += flow;
    }
  }

  int Edmonds_Karp() {
    int max_flow = 0;
    int flow = 0;
    do {
      max_flow += flow;
      flow = 0;
      this->BFS();
      this->rising_way( this->target_vertex, INF, flow );
      delete[ ] this->vertex_struct;
    } while ( flow );
    return max_flow;
  }
  private:
  int** adjacency_matrix;
  int number_of_vertex;
  NotDirectGraphVertexStruct* vertex_struct;
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
    g.setAdjacencyVertex( u - 1, v - 1 );
    int flow = g.Edmonds_Karp();
    if ( flow == 2 ) cout << 1;
    else cout << 0;
    cin >> number_of_vertex >> number_of_edges;
    if ( number_of_vertex && number_of_edges ) cout << endl;
  }

  return 0;
}