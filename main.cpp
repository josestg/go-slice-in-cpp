#include <iostream>
#include "slice.h"

int main() {
  Slice s = make(0, 1);
  std::cout << "slice created: " << s << std::endl;
  std::cout << "size of slice: " << sizeof(s) << std::endl;

  int last_cap = s.cap;
  for (int i = 0; i < 10; i++) {
    std::cout << "append value: " << i << std::endl;
    s = append(s, i);
    if (s.cap != last_cap) {
      std::cout << "slice capacity changed: " << s << std::endl;
      last_cap = s.cap;
    }
  }

  std::cout << "slice: " << s << std::endl;

  std::cout << "updating slice[0] to 100" << std::endl;
  set_value(s, 0, 100);

  std::cout << "slice after update: " << s << std::endl;
  std::cout << "size of slice: " << sizeof(s) << std::endl;
  free_slice(s);
  return 0;
}
