#include <iostream>
#include <vector>

using namespace std;

enum Status {
  NOT_VISITED,
  VISITED,
  CFC_NULL
};

ostream& operator<<( ostream& output, const Status& s ) {
  switch ( s ) {
    case NOT_VISITED:
      output << "NOT_VISITED";
      break;

    case VISITED:
      output << "VISITED";
      break;

    case CFC_NULL:
      output << "CFC_NULL";
      break;

    default:
      output << s;
      break;
  }
  return output;
}

struct Edges {
  int u;
  int v;
  bool ciclica;
  Edges( int u, int v ) {
    this->u = u;
    this->v = v;
    ciclica = false;
  }
  bool is_this_edge( int u, int v ) {
    if ( u == this->u and v == this->v ) return true;
    if ( v == this->u and u == this->v ) return true;
    return false;
  }
  int getOther( int u ) {
    if ( u == this->u ) return this->v;
    return this->u;
  }
  int getOtherTwo( int u, int v ) {
    if ( has( u ) ) return getOther( u );
    return getOther( v );
  }
  bool has_one_of_two( Edges e ) {
    return has( e.u ) || has( e.v );
  }
  bool has( int u ) {
    return u == this->v or u == this->u;
  }
  bool equal( Edges e ) {
    if ( e.u == this->u )
      if ( e.v == this->v )
        return true;
    return false;
  }
};

ostream& operator<<( ostream& output, const Edges& edges ) {
  output << edges.u + 1 << "-" << edges.v + 1;
  return output;
}

class Vertex {
  public:
  Vertex( int id ) {
    this->id = id;
    this->father = NULL;
    this->status = NOT_VISITED;
  }
  int getId() { return this->id; }
  void setFather( Vertex* father ) {
    if ( !father ) return;

    this->father = father;
  }
  Vertex* getFather() { return this->father; }
  void changeStatus( Status c ) { this->status = c; }
  Status getStatus() { return this->status; }
  void addEdge( Edges* edge ) {
    if ( !edge ) return;

    edges.push_back( edge );
  }
  vector<Edges*> getEdges() { return this->edges; }
  friend ostream& operator<<( ostream& output, const Vertex v ) {
    if ( v.edges.empty() ) return output;
    output << "ID: " << v.id + 1;
    output << "\n\tStatus: " << v.status;
    output << "\n\tFather: ";
    if ( v.father ) output << v.father->getId() + 1;
    else output << "NULL";
    output << "\n\tEdges: ";
    for ( Edges* x : v.edges ) {
      output << *x << " ";
    }
    output << endl << endl;
    return output;
  }
  private:
  int id;
  Vertex* father;
  Status status;
  vector<Edges*> edges;
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
    Edges* edge = new Edges( u, v );
    this->edges.push_back( edge );
    this->adjacency_list[u]->addEdge( edge );
    this->adjacency_list[v]->addEdge( edge );
  }

  friend ostream& operator<<( ostream& output, const Graph g ) {
    output << "Number of vertex: " << g.number_of_vertex << endl;
    output << "Adjacency list:\n";
    for ( int id = 0; id < g.number_of_vertex; id++ ) {
      output << *g.adjacency_list[id];
    }
    output << "Cicles:\n";
    int c = 1;
    for ( vector<Edges*> ve : g.cicles ) {
      output << "Cicle " << c << ": ";
      c++;
      int u = -1, v = -1;
      for ( Edges* e : ve ) {
        if ( u == -1 and v == -1 ) {
          output << *e;
        }
        else {
          output << "-" << e->getOtherTwo( u, v ) + 1;
        }
        u = e->u;
        v = e->v;
      }
      output << endl;
    }
    return output;
  }

  bool find_cicle( vector<Edges>& stack, Edges& e, Edges& s_edge, vector<Edges*>& cicle, int id ) {
    s_edge = stack.back();
    if ( !s_edge.has_one_of_two( e ) ) {
      Edges x( id, id );
      s_edge = x;
      return false;
    };
    for ( Edges* edge : this->edges ) {
      if ( edge->equal( s_edge ) and !edge->ciclica ) {
        stack.pop_back();
        e = s_edge;
        cicle.push_back( edge );
      }
    }
    return true;
  }

  void DFS_VISIT( int id, vector<Edges>& stack ) {
    vector<Edges*> adjacency_vertex;
    adjacency_vertex = this->adjacency_list[id]->getEdges();
    for ( Edges* edge : adjacency_vertex ) {
      Vertex* v = this->adjacency_list[edge->getOther( id )];
      if ( v->getStatus() == NOT_VISITED ) {
        stack.push_back( *edge );
        v->changeStatus( VISITED );
        v->setFather( this->adjacency_list[id] );
        DFS_VISIT( v->getId(), stack );
      }
      else {
        Vertex* father = this->adjacency_list[id]->getFather();
        if ( father ) {
          if ( v->getId() != father->getId() and !edge->ciclica ) {
            vector<Edges*> cicle;
            cicle.push_back( edge );
            Edges s_edge( -1, -1 );
            Edges old( edge->u, edge->v );
            bool add_cicle = false;
            do {
              add_cicle = this->find_cicle( stack, old, s_edge, cicle, v->getId() );
              if ( !add_cicle ) {
                stack.push_back( *edge );
              }
            } while ( !stack.empty() and !s_edge.has( v->getId() ) );
            if ( add_cicle ) {
              for ( Edges* _ : cicle ) {
                _->ciclica = true;
              }
              this->cicles.push_back( cicle );
            }
          }
        }
      }
    }
  }
  void addXY( int u, int v ) {
    this->x = this->adjacency_list[u];
    this->y = this->adjacency_list[v];
  }

  void DFS() {
    vector<Edges> stack;
    for ( int id = 0; id < this->number_of_vertex; id++ ) {
    // int id = this->x->getId();
      if ( this->adjacency_list[id]->getStatus() == NOT_VISITED ) {
        this->adjacency_list[id]->changeStatus( VISITED );
        DFS_VISIT( id, stack );
      }
    }
  }

  private:
  vector<vector<Edges*>> cicles;
  vector<Edges*> edges;
  Vertex** adjacency_list;
  int number_of_vertex;
  Vertex* x;
  Vertex* y;
};

int main() {
  int number_of_vertex, number_of_edges, u, v;
  cin >> number_of_vertex >> number_of_edges;
  while ( number_of_vertex && number_of_edges ) {
    Graph g( number_of_vertex );
    for ( int i = 0; i < number_of_edges; i++ ) {
      cin >> u >> v;
      g.addEdge( u - 1, v - 1 );
    }
    cin >> u >> v;
    g.addXY( u - 1, v - 1 );
    g.DFS();
    cout << g;
    cin >> number_of_vertex >> number_of_edges;
  }
  return 0;
}