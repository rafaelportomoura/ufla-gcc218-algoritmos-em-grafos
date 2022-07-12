#include <iostream>
#include <vector>

using namespace std;

enum COLOR { WHITE, GRAY };

class Vertix {
  public:
  Vertix( const int id ) {
    this->id = id;
    this->color = WHITE;
  }
  int getId() { return this->id; }
  Vertix* getEdge( int id ) {
    for ( Vertix* edge : this->edges ) {
      if ( *edge == id ) {
        return edge;
      }
    }
    return NULL;
  }
  vector<Vertix*> getEdges() {
    return this->edges;
  }
  void addEdge( Vertix* connected_vertix ) {
    if ( !connected_vertix ) return;
    if ( getEdge( connected_vertix->getId() ) ) return;
    this->edges.push_back( connected_vertix );
  }
  bool operator==( int id ) {
    return this->id == id;
  }
  bool operator==( COLOR color ) {
    return this->color == color;
  }
  void setColor( COLOR color ) {
    this->color = color;
  }
  private:
  int id;
  COLOR color;
  vector<Vertix*> edges;
};

class Mobile {
  public:
  Mobile( const int number_of_vertixs ) {
    this->number_of_vertixs = number_of_vertixs;
    this->hash_end = number_of_vertixs + 1;
    this->hash_start = 0;
    vertixs = new Vertix * [this->hash_end];
    for ( int i = this->hash_start; i < this->hash_end; i++ ) {
      vertixs[i] = new Vertix( i );
    }
  }
  int dfs_visit( Vertix* vertix_to_search ) {
    if ( !vertix_to_search ) return 0;
    vertix_to_search->setColor( GRAY );
    vector<Vertix*> edges = vertix_to_search->getEdges();
    int weight = 1;
    int last_child = 0;
    for ( Vertix* edge : edges ) {
      if ( *edge == WHITE ) {
        int son_weight = dfs_visit( edge );
        if ( last_child && last_child != son_weight ) {
          throw runtime_error( "maluuuu" );
        }
        weight += son_weight;
        last_child = son_weight;
      }
    }
    return weight;
  }
  void dfs() {
    for ( int id = this->hash_start; id < this->hash_end; id++ ) {
      if ( *this->vertixs[id] == WHITE ) {
        dfs_visit( this->vertixs[id] );
      }
    }
  }
  void addEdge( int source, int target ) {
    this->vertixs[target]->addEdge( this->vertixs[source] );
  }
  private:
  int hash_end;
  int hash_start;
  Vertix** vertixs;
  int number_of_vertixs;
};


int main() {
  try {
    int number_of_vertixs;
    cin >> number_of_vertixs;
    Mobile mobile( number_of_vertixs );
    int source, target;
    for ( int i = 0; i < number_of_vertixs; i++ ) {
      cin >> source >> target;
      mobile.addEdge( source, target );
    }
    mobile.dfs();
    cout << "bem";
  }
  catch ( const std::exception& e ) {
    cout << "mal";
  }
  return 0;
}