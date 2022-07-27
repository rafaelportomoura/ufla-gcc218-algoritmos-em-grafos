#include <iostream>

using namespace std;

enum Color {
  WHITE,
  GRAY,
  BLACK
};

ostream& operator<<( ostream& output, const Color& c ) {
  switch ( c ) {
    case WHITE:
      output << "WHITE";
      break;

    case GRAY:
      output << "GRAY";
      break;

    case BLACK:
      output << "BLACK";
      break;

    default:
      output << "NO_COLOR";
      break;
  }

  return output;
}