#include <iostream>

#define INF INT16_MAX

using namespace std;

void floyd_warshall( int** MA, int n ) {
  for ( int k = 0; k < n; k++ )
    for ( int i = 0; i < n; i++ )
      for ( int j = 0; j < n; j++ )
        MA[i][j] = min( MA[i][j], MA[i][k] + MA[k][j] );
}

int main() {
  int n, m;
  cin >> n >> m;

  while ( n and m ) {
    int** MA = new int* [n];
    int u, v, w;

    for ( int i = 0; i < n; i++ ) {
      MA[i] = new int[n];
      for ( int j = 0; j < n; j++ )
        MA[i][j] = INF;
    }

    for ( int i = 0; i < m; i++ ) {
      cin >> u >> v >> w;
      u--;
      v--;
      MA[u][v] = MA[v][u] = w;
    }

    floyd_warshall( MA, n );

    int source, target;
    int number_of_sources_and_targets;
    cin >> number_of_sources_and_targets;
    cout << "Estimativa: " << endl;
    while ( number_of_sources_and_targets > 0 ) {
      cin >> source >> target;

      source--;
      target--;

      cout << source << "->" << target << ": ";

      if ( source != target ) {
        cout << MA[source][target];
      }
      else {
        cout << 0;
      }
      cout << endl;
      number_of_sources_and_targets--;
    }
    cin >> n >> m;
  }

  return 0;
}