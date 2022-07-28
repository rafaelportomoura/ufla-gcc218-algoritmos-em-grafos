#include <iostream>

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