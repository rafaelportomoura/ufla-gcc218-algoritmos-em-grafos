#include <iostream>

using namespace std;

enum Arcs_Types {
  THREE,
  RETURN,
  DIRECT,
  CROSSED
};

ostream& operator<<( ostream& output, const Arcs_Types& at ) {
  switch ( at ) {
    case THREE:
      output << "THREE";
      break;

    case RETURN:
      output << "RETURN";
      break;

    case DIRECT:
      output << "DIRECT";
      break;

    case CROSSED:
      output << "CROSSED";
      break;

    default:
      output << "NOT_CLASSIFICATED";
      break;
  }
  return output;
}

struct Arcs {
  int origin;
  int target;
  Arcs_Types type;
  bool plus_one_in_output;
  Arcs( int origin, int target, bool plus_one_in_output = true ) {
    this->origin = origin;
    this->target = target;
    this->plus_one_in_output = plus_one_in_output;
  }
};

ostream& operator<<( ostream& output, const Arcs& a ) {
  output << a.type << ": " << a.origin + a.plus_one_in_output << "->" << a.target + a.plus_one_in_output;
  return output;
}