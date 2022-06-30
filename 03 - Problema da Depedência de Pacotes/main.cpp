#include<iostream>
#include<vector>
using namespace std;

enum COLOR { WHITE, GRAY, BLACK };

class Package {
  private:
  vector<Package*> dependencies;
  Package* father;
  int id;
  COLOR color;
  int low;
  int find_time;
  public:
  Package( int id ) {
    this->id = id;
    this->color = WHITE;
    this->low = 0;
    this->find_time = 0;
    this->father = NULL;
  }
  COLOR getColor() { return color; }
  void setColor( COLOR color ) { this->color = color; }
  int getId() { return this->id; }
  Package* getFather() { return father; }
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
  friend ostream& operator<<( ostream& output, const Package& pack ) {
    output << pack.id;
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
  int number_of_package;
  int loop_packages;
  int loop_init;

  public:
  Compiler( int number_of_package ) {
    this->number_of_package = number_of_package;
    this->loop_packages = number_of_package + 1;
    this->loop_init = 1;
    packages = new Package * [number_of_package + 1];
    for ( int id = this->loop_init; id < this->loop_packages; id++ ) {
      packages[id] = new Package( id );
    }
  }
  void addDependency( int source, int target ) {
    packages[source]->setDependencie( packages[target] );
  }
  void dfs_visit( Package* package ) {

  }

  void dfs() {
    for ( int id = this->loop_init; id < this->loop_packages; id++ ) {
      if ( this->packages[id]->getColor() == WHITE ) {
        dfs_visit( this->packages[id] );
      }
    }
  }

  friend ostream& operator<<( ostream& output, const Compiler& c ) {
    for ( int id = c.loop_init; id < c.loop_packages; id++ ) {
      output << *c.packages[id] << endl;
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
  cout << compiler;

  return 0;
}