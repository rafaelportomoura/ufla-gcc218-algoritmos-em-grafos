#include <iostream>
#include <vector>
using namespace std;

enum { ORIGIN, TARGET };

int bfs( int number_of_vertixs, int** Matrix, vector<int>& stack, int moves = 0 ) {
  int searched = stack.back();
  stack.pop_back();
  for ( int colunm = 0; colunm < number_of_vertixs; colunm++ ) {
    if ( Matrix[searched][colunm] == 1 ) {
      stack.push_back( colunm );
      for ( int index = 0; index < number_of_vertixs; index++ ) {
        if ( Matrix[index][colunm] ) Matrix[index][colunm]++;
      }
      Matrix[colunm][searched]++;
      moves += 2;
    }
  }
  return moves;
}


int search( int number_of_vertixs, int** Matrix, int searched ) {
  vector<int> stack;
  stack.push_back( searched );
  int moves = 0;
  while ( !stack.empty() ) {
    moves = bfs( number_of_vertixs, Matrix, stack, moves );

  }
  return moves;
}

int* getEdge() {
  int origin, target;
  cin >> origin >> target;
  int* edge = new int[2];
  edge[0] = origin;
  edge[1] = target;
  return edge;
}

int doTest() {
  int root;
  cin >> root;
  int number_of_vertixs, number_of_edges;
  cin >> number_of_vertixs >> number_of_edges;
  int** AdjancyMatrix = new int* [number_of_vertixs];

  for ( int i = 0; i < number_of_vertixs; i++ ) {
    AdjancyMatrix[i] = new int[number_of_vertixs];
    for ( int j = 0; j < number_of_vertixs; j++ ) {
      AdjancyMatrix[i][j] = 0;
    }
  }

  for ( int i = 0; i < number_of_edges; i++ ) {
    int* edge = getEdge();
    int origin = edge[ORIGIN];
    int target = edge[TARGET];
    AdjancyMatrix[origin][target] = 1;
    AdjancyMatrix[target][origin] = 1;
  }

  int moves = search( number_of_vertixs, AdjancyMatrix, root );


  return moves;
}


int main() {
  int tests = 0;
  cin >> tests;
  int* testes_results = new int[tests];
  for ( int number_test = 0; number_test < tests; number_test++ ) {
    int test_result = doTest();
    testes_results[number_test] = test_result;
  }
  for ( int test = 0; test < tests; test++ ) {
    cout << testes_results[test] << endl;
  }
  return 0;
}