#include <iostream>

using namespace std;

enum Status {
  NOT_VISITED,
  VISITED
};

ostream& operator<<( ostream& output, const Status& s ) {
  switch ( s ) {
    case NOT_VISITED:
      output << "NOT_VISITED";
      break;

    case VISITED:
      output << "VISITED";
      break;

    default:
      output << s;
      break;
  }
  return output;
}