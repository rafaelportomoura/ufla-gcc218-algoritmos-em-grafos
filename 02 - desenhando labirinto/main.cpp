#include <iostream>
#include <vector>
#include <queue>

using namespace std;

enum COLOR { WHITE, GRAY, BLACK };


class Vertix {
  private:
  int id;
  COLOR color;
  Vertix* father;
  int distance;
  vector<Vertix*> sons;
  public:
  Vertix( int id ) {
    father = NULL;
    color = WHITE;
    distance = 0;
    this->id = id;
  }
  void setId( int id ) { this->id = id; }
  int getId() { return this->id; }
  COLOR getColor() { return color; }
  void setColor( COLOR color ) { this->color = color; }
  Vertix* getFather() { return father; }
  void setFather( Vertix* father ) { this->father = father; }
  int getDistance() { return distance; }
  void setDistance( int distance ) { this->distance = distance; }
  vector<Vertix*> getSons() { return this->sons; }
  void setSon( Vertix* son ) {
    for ( Vertix* old_son : sons ) {
      if ( old_son == son ) return;
    }
    this->sons.push_back( son );
  }
  friend bool operator==( Vertix& esse, Vertix& other ) {
    return esse.getId() == other.getId();
  }
  friend ostream& operator<<( ostream& output, const Vertix& v ) {
    output << "(" << v.id << ")";
    if ( v.father ) {

      output << "\n\tf: " << v.father->getId();
    }
    else {

      output << "\n\tf: " << "NULL";
    }
    output << "\n\tc: " << v.color;
    output << "\n\td: " << v.distance;
    output << "\n\tsons: {";
    for ( Vertix* son : v.sons ) {
      output << " (" << son->getId() << ")";
    }
    output << " }\n";
    return output;
  }
};

class Graph {
  private:
  Vertix* root;
  vector<Vertix*> all_vertixs;
  queue<int> drawing_queue;
  public:
  Graph( int root ) {
    this->root = new Vertix( root );
    all_vertixs.push_back( this->root );
  }
  Vertix* getVertix( int id ) {
    for ( Vertix* vertix : all_vertixs ) {
      if ( vertix->getId() == id ) return vertix;
    }
    return NULL;
  }
  Vertix* addVertix( int id ) {
    Vertix* vertix = getVertix( id );
    if ( vertix ) return vertix;

    vertix = new Vertix( id );
    all_vertixs.push_back( vertix );

    return vertix;
  }
  void addEdge( int source, int target ) {
    Vertix* source_vertix = addVertix( source );
    Vertix* target_vertix = addVertix( target );

    source_vertix->setSon( target_vertix );
    target_vertix->setSon( source_vertix );
  }

  int bfs( Vertix* focused_vertix ) {
    int distance = 0;
    vector<Vertix*> sons = focused_vertix->getSons();
    bool have_son = false;
    for ( Vertix* son : sons ) {
      if ( son->getColor() == WHITE ) {
        have_son = true;
        son->setColor( GRAY );
        son->setDistance( focused_vertix->getDistance() + 1 );
        son->setFather( focused_vertix );
        this->drawing_queue.push( son->getId() );
        distance += 2;
      }
    }
    return distance;
  }

  int makeDraw() {
    this->root->setColor( GRAY );
    int distance = 0;
    this->drawing_queue.push( this->root->getId() );
    while ( !this->drawing_queue.empty() ) {
      Vertix* focused_vertix = this->getVertix( this->drawing_queue.front() );
      this->drawing_queue.pop();
      COLOR color = focused_vertix->getColor();
      if ( color == GRAY ) {
        distance += bfs( focused_vertix );
      }
      focused_vertix->setColor( BLACK );
    }
    return distance;
  }

  friend ostream& operator<<( ostream& output, const Graph& g ) {
    for ( Vertix* v : g.all_vertixs ) {
      cout << *v << endl;
    }
  }

};


int testCase() {
  int vertixs;
  int edges;
  int root;
  cin >> root >> vertixs >> edges;
  Graph g( root );
  for ( int i = 0; i < edges; ++i ) {
    int source, target;
    cin >> source >> target;
    g.addEdge( source, target );
  }
  int distance = g.makeDraw();
  // cout << g;
  // cout << "\nDistance: " << distance << endl;
  // cout << endl << endl;
  return distance;
}

int main() {
  int tests;
  cin >> tests;
  for ( int i = 0; i < tests; i++ ) {
    cout << testCase() << endl;
  }
  return 0;
}