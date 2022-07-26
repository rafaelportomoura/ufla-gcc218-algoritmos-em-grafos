#include <iostream>
#include <vector>

using namespace std;

int number_of_sticks( int length_of_sticks, int** mpp, int processing_points, int measurements ) {
  int numbers = 0;
  for ( int pp = 0; pp < processing_points; pp++ ) {
    int stick = 0;
    for ( int m = 0; m < measurements; m++ ) {
      if ( mpp[m][pp] ) stick++;
      else {
        if ( stick >= length_of_sticks ) numbers++;
        stick = 0;
      }
    }
    if ( stick >= length_of_sticks ) numbers++;
  }
  return numbers;
}


int main() {
  int processing_points, measurements, length_of_sticks;

  cin >> processing_points >> measurements >> length_of_sticks;
  while ( processing_points || measurements || length_of_sticks ) {
    int** mpp = new int* [measurements];
    for ( int m = 0; m < measurements; m++ ) {
      mpp[m] = new int[processing_points];
      for ( int pp = 0; pp < processing_points; pp++ ) {
        cin >> mpp[m][pp];
      }
    }
    cout << number_of_sticks( length_of_sticks, mpp, processing_points, measurements ) << endl;
    cin >> processing_points >> measurements >> length_of_sticks;
  }
  return 0;
}