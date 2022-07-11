#include <iostream>
#include <vector>

using namespace std;

struct Edge {
  Vertix* origin;
  Vertix* destination;
  int weight;
};

class Vertix {
public:
  Vertix( int id ) {
    this->id = id;
  }
private:
  int id;

}



int main() {
  vector<Edge> edges;
  return 0;
}