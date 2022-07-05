#include<iostream>
#include<vector>
#include <utility>
using namespace std;

enum COLOR { WHITE, GRAY, BLACK };

int min( int a, int b ) {
  if ( a < b ) return a;
  return b;
}

class Package {
  private:
  vector<Package*> dependencies;
  Package* father;
  int id;
  COLOR color;
  int low;
  int find_time;
  bool articulation;
  public:
  Package( int id ) {
    this->id = id;
    this->color = WHITE;
    this->low = 0;
    this->find_time = 0;
    this->father = NULL;
    this->articulation = false;
  }
  COLOR getColor() { return color; }
  void setColor( COLOR color ) { this->color = color; }
  int getId() { return this->id; }
  Package* getFather() { return father; }
  int getFatherID() {
    if ( this->father == NULL ) {
      return this->id;
    }
    return father->getId();
  }
  void setFather( Package* father ) { this->father = father; }
  Package* getDependency( int id ) {
    for ( Package* p : dependencies ) {
      if ( p->getId() == id ) {
        return p;
      }
    }
    return NULL;
  }
  vector<Package*> getDependencies() { return dependencies; }
  void setDependencie( Package* dependecie ) {
    Package* p = getDependency( dependecie->getId() );
    if ( p != NULL ) { return; }

    dependencies.push_back( dependecie );
  }
  int getFindTime() { return this->find_time; }
  void setFindTime( int time ) { this->find_time = time; }
  int getLow() { return this->low; }
  void setLow( int low ) { this->low = low; }
  bool isArticulation() { return this->articulation; }
  void setArticulation( bool isArticulation ) { this->articulation = isArticulation; }
  friend ostream& operator<<( ostream& output, const Package& pack ) {
    output << "\nid: " << pack.id;
    output << "\ncolor: " << pack.color;
    output << "\nfind_time: " << pack.find_time;
    output << "\nlow: " << pack.low;
    output << "\narticulation: " << pack.articulation;
    if ( pack.father != NULL ) output << "\nfather: " << pack.father->getId();
    else output << "\nfather: " << pack.id;
    output << "\ndependencies:";
    for ( Package* p : pack.dependencies ) {
      output << "\n\t" << p->getId();
    }
    output << endl;
    return output;
  }
};

class Compiler {
  private:
  Package** packages;
  vector<pair<int, int>> bridges;
  int number_of_package;
  int loop_packages;
  int loop_init;
  int root;

  void setRoot( int root ) {
    this->root = root;
  }

  // TARJAN
  void dfs_visit( Package* package, int& time, int& filhos_raiz ) {
    time++;
    package->setColor( GRAY );
    package->setFindTime( time );
    package->setLow( time );
    vector<Package*> dependecies = package->getDependencies();
    for ( Package* dependency : dependecies ) {
      if ( dependency->getColor() == WHITE ) {
        dependency->setFather( package );
        if ( package->getId() == this->root ) filhos_raiz++;
        dfs_visit( dependency, time, filhos_raiz );
        if ( dependency->getLow() >= package->getFindTime() ) package->setArticulation( true );

        if ( dependency->getLow() > package->getFindTime() ) {
          bridges.push_back( pair<int, int>( package->getId(), dependency->getId() ) );
        }
      }
      else if ( dependency->getId() != package->getFatherID() ) {
        package->setLow( min( package->getLow(), dependency->getLow() ) );
      }
    }

    package->setColor( BLACK );
  }

  public:
  Compiler( int number_of_package ) {
    this->number_of_package = number_of_package;
    this->loop_packages = number_of_package + 1;
    this->loop_init = 1;
    packages = new Package * [number_of_package + 1];
    for ( int id = this->loop_init; id < this->loop_packages; id++ ) {
      packages[id] = new Package( id );
    }
    this->root = -1;
  }
  ~Compiler() {
    for ( int id = this->loop_init; id < this->loop_packages; id++ ) {
      delete packages[id];
    }
  }
  void addDependency( int source, int target ) {
    packages[source]->setDependencie( packages[target] );
  }
  void dfs() {
    int time = 0;
    for ( int id = this->loop_init; id < this->loop_packages; id++ ) {
      if ( this->packages[id]->getColor() == WHITE ) {
        int filhos_raiz = 0;
        dfs_visit( this->packages[id], time, filhos_raiz );
        setRoot( id );
        this->packages[id]->setArticulation( filhos_raiz > 1 );
      }
    }
  }

  friend ostream& operator<<( ostream& output, const Compiler& c ) {
    cout << "[PACKAGES]\n";
    for ( int id = c.loop_init; id < c.loop_packages; id++ ) {
      output << *c.packages[id] << endl;
    }
    cout << "[BRIDGES]\n";
    for ( pair<int, int> bridge : c.bridges ) {
      cout << bridge.first << "->" << bridge.second << endl;
    }
    return output;
  }

};


int main() {
  int number_of_package, number_of_dependencies;
  cin >> number_of_package >> number_of_dependencies;
  int source, target;
  Compiler compiler( number_of_package );
  for ( int i = 0; i < number_of_dependencies; i++ ) {
    cin >> source >> target;
    compiler.addDependency( source, target );
  }
  compiler.dfs();
  cout << compiler;

  return 0;
}