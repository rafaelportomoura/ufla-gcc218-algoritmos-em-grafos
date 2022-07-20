#include <iostream>
#include <vector>

using namespace std;

enum COLOR { WHITE, GRAY };

struct Edge {
  int destination;
  int weight;
  Edge( int destination, int weight ) {
    this->destination = destination;
    this->weight = weight;
  }
  bool operator==( int id ) {
    return this->destination == id;
  }
  bool operator<( Edge* e ) {
    return this->weight < e->weight;
  }
};

class Vertix {
public:
  Vertix( int id ) {
    this->id = id;
    this->color = WHITE;
  };
  Edge* getEdge( int id ) {
    for ( Edge* edge : this->edges ) {
      if ( *edge == id ) return edge;
    }
    return NULL;
  }
  void addEdge( int destination, int weight ) {
    if ( getEdge( destination ) ) return;
    edges.push_back( new Edge( destination, weight ) );
  }
  vector<Edge*> getEdges() {
    return edges;
  }
  void setColorGray() {
    this->color = GRAY;
  }
  bool operator==( COLOR c ) {
    return this->color == c;
  }
  int getId() { return this->id; }
private:
  vector<Edge*> edges;
  int id;
  COLOR color;
};

class Three {
public:
  Three( int number_of_vertix ) {
    this->vertix_edge = new Vertix * [number_of_vertix];
    this->otimized_three = new Vertix * [number_of_vertix];
    this->number_of_vertix = number_of_vertix;
    for ( int id = 0; id < number_of_vertix; id++ ) {
      this->vertix_edge[id] = new Vertix( id );
      this->otimized_three[id] = new Vertix( id );
    }
    this->total_weight = 0;
    this->otimized_weight = 0;
  }
  void addEdge( int source, int destination, int weight ) {
    this->vertix_edge[source]->addEdge( destination, weight );
    this->vertix_edge[destination]->addEdge( source, weight );
    this->total_weight += weight;
  }
  void boruvka_visit( Vertix* vertix ) {
    if ( !vertix ) return;
    vertix->setColorGray();

    vector<Edge*> edges = vertix->getEdges();
    Edge* lowest_edge = NULL;
    for ( Edge* edge : edges ) {
      int destination = edge->destination;
      if ( *vertix_edge[destination] == WHITE ) {
        if ( !lowest_edge ) {
          lowest_edge = edge;
        }
        else if ( edge < lowest_edge ) {
          lowest_edge = edge;
        }
      }
    }
    if ( !lowest_edge ) return;
    otimized_three[vertix->getId()]->addEdge( lowest_edge->destination, lowest_edge->weight );
    otimized_three[lowest_edge->destination]->addEdge( vertix->getId(), lowest_edge->weight );
    otimized_weight += lowest_edge->weight;
  }
  void boruvka() {
    for ( int id = 0; id < this->number_of_vertix; id++ ) {
      boruvka_visit( vertix_edge[id] );
    }
  }
  int getDiferrenceBetweenWeights() {
    return total_weight - otimized_weight;
  }
  friend ostream& operator<<( ostream& o, const Three& t ) {
    o << t.total_weight - t.otimized_weight;
    return o;
  }
private:
  Vertix** vertix_edge;
  Vertix** otimized_three;
  int number_of_vertix;
  int total_weight;
  int otimized_weight;
};


int main() {
  int number_of_vertix, number_of_edges;
  cin >> number_of_vertix >> number_of_edges;
  Three three( number_of_vertix );
  int source, destination, weight;
  cin >> source >> destination;
  while ( source || destination ) {
    cin >> weight;
    three.addEdge( source, destination, weight );
    cin >> source >> destination;
  }
  three.boruvka();
  cout << three.getDiferrenceBetweenWeights();
  return 0;
}