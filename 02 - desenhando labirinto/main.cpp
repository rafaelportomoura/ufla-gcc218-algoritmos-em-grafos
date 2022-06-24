#include <iostream>
#include <vector>

using namespace std;

enum COLORS {
  WHITE,
  GRAY,
  BLACK
};

void debug_print( string text ) {
  cout << text;
}

struct Traits {
  int id;
  COLORS color;
  int distance;
  Traits() {
    color = WHITE;
    distance = 0;
  }
  bool operator==( const Traits& x ) {
    return id == x.id;
  }
  COLORS color_change() {
    if ( color == WHITE ) {
      color = GRAY;
    }
    else if ( color == GRAY ) {
      color = BLACK;
    }

    return color;
  }
};
ostream& operator<<( ostream& output, const Traits& trait ) {
  output << "id: " << trait.id << "  color: " << trait.color;
  return output;
}

class Noh {
  private:
  Traits trait;
  vector<Noh*> my_edges;
  public:
  Noh( Traits trait ) {
    this->trait = trait;
  }
  Traits getTraits() { return this->trait; }
  vector<Noh*> getEdges() { return my_edges; }
  void setTraits( Traits traits ) { this->trait = traits; }
  COLORS updateColor() { return this->trait.color_change(); };
  COLORS getColor() { return this->trait.color; }
  void addEdge( Noh* newEdge ) {
    if ( not newEdge ) return;
    bool has_edge = false;
    for ( unsigned vertix = 0; vertix < my_edges.size() and not has_edge; vertix++ ) {
      has_edge = newEdge->getTraits() == my_edges[vertix]->getTraits();
    }

    if ( not has_edge ) my_edges.push_back( newEdge );
  }
  friend ostream& operator<<( ostream& output, const Noh& noh ) {
    output << "Vertix: " << noh.trait << endl;
    output << "Edge: " << noh.my_edges.size() << endl;

    for ( unsigned vertix = 0; vertix < noh.my_edges.size(); vertix++ ) {
      output << "\t" << noh.my_edges[vertix]->getTraits() << endl;
    }

    output << endl;
    return output;
  }

};

class Graph {
  private:
  int test;
  Noh* vertix_root;
  vector<Noh*> know_vertixs;
  vector<Noh> my_stack;
  int moves;
  void addRoot( int id ) {
    Noh* vertix = addToKnownRoots( id );
    this->vertix_root = vertix;
    moves = 0;
  }
  public:
  Graph( int root_id, int test ) {
    this->addRoot( root_id );
    this->test = test;
  }
  int getVertixIndex( int id ) {
    int index = -1;
    for ( unsigned i = 0; i < know_vertixs.size() and index < 0; i++ ) {
      if ( id == know_vertixs[i]->getTraits().id ) {
        index = i;
      }
    }
    return index;
  }
  Noh* getVertix( int id ) {
    int index = getVertixIndex( id );
    if ( index < 0 ) {
      return NULL;
    }
    return know_vertixs[index];
  }
  Noh* addToKnownRoots( int id ) {
    Noh* vertix = getVertix( id );
    if ( vertix ) return vertix;
    Traits trait;
    trait.id = id;
    Noh* newVertix = new Noh( trait );
    // cout << trait << endl;
    // cout << *newVertix << endl;
    know_vertixs.push_back( newVertix );
    return newVertix;
  }
  void addVertixInStack( Noh* newVertixInStack ) {
    newVertixInStack->updateColor();
    my_stack.push_back( *newVertixInStack );
  }
  Noh pop_stack() {
    Noh poped = my_stack.back();
    my_stack.pop_back();
    return poped;
  }
  void print_stack() {
    cout << "Stack\n";
    for ( Noh stack : my_stack ) {
      cout << "\t" << stack.getTraits() << endl;
    }
    cout << endl;
  }
  void countMoves() {
    addVertixInStack( this->vertix_root );
    while ( !my_stack.empty() ) {
      Noh search_vertix = pop_stack();
      // cout << "Id: " << search_vertix.getTraits().id << endl;
      vector<Noh*> edges = search_vertix.getEdges();
      for ( Noh* edge : edges ) {
        // cout << "\tId: " << edge->getTraits().id << endl;

        this->moves++;
        COLORS color = edge->getColor();
        if ( color == WHITE ) {
          addVertixInStack( edge );
        }
      }
      // print_stack();
    }
  }
  void addEdge( int id_source, int id_target ) {
    Noh* vertix_source = addToKnownRoots( id_source );
    Noh* vertix_target = addToKnownRoots( id_target );
    vertix_source->addEdge( vertix_target );
    vertix_target->addEdge( vertix_source );
  }
  void print_three() {
    cout << "============================= " << test << " ============================" << endl;
    cout << "ROOT: ";
    cout << this->vertix_root->getTraits() << endl;
    for ( Noh* vertix : know_vertixs ) {
      cout << *vertix << endl;
    }
    cout << "=============================================================" << endl;
  }
  void print() {
    countMoves();
    cout << moves;
  }

};

Graph* inputGraph( istream& in, int test ) {
  int root, total_vertixs, total_edges;
  in >> root >> total_vertixs >> total_edges;
  int vertix_source, vertix_target;
  Graph* graph = new Graph( root, test );
  for ( int i = 0; i < total_edges; i++ ) {
    in >> vertix_source >> vertix_target;
    graph->addEdge( vertix_source, vertix_target );
  }
  return graph;
}


int main() {
  vector<Graph*> graphs;
  int test;
  cin >> test;
  for ( int i = 0; i < test; i++ ) {
    graphs.push_back( inputGraph( cin, i + 1 ) );
  }
  int count = 0;
  for ( Graph* g : graphs ) {
    if ( count != 0 ) {
      cout << endl;
    }
    g->print();
    count++;
  }
  return 0;
}