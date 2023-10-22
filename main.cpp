#include <iostream>
#include "slice.h"


int main() {
  Slice s = make(0, 1);
  for (int i = 0; i < 10; i++) {
    s = append(s, i);
  }

  std::cout << s << std::endl;
  free_slice(s);
  return 0;
}
