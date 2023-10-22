#include "slice.h"

#include <iostream>
#include <stdexcept>
#include <sstream>

// Create a slice of length len and capacity cap.
Slice make(int len, int cap) {
  if (len > cap) {
    throw std::runtime_error("make: len > cap");
  }

  // make sure the capacity is at least 1 and the length is at least 0.
  len = std::max(len, 0);
  cap = std::max(cap, 1);

  // create a contiguous block of memory as the backing array for
  // storing the actual data.
  int *backing_array = (int *) calloc(cap, sizeof(int));
  if (backing_array == nullptr) {
    throw std::runtime_error("make: out of memory");
  }

  return {.data = backing_array, .len = len, .cap = cap};
}

// Deallocate the backing array.
void free_slice(Slice &s) { free(s.data); }

// Append a new element to the slice.
Slice append(Slice &s, int v) {
  if (s.len == s.cap) {
    // grow the backing array by 2x or 1 if the capacity is 0.
    int new_cap = std::max(2 * s.cap, 1);
    // reallocate basically creates a new contiguous block of memory
    // with the new capacity and copies the data from the old block to
    // the new block.
    int *new_backing_array = (int *) realloc(s.data, new_cap * sizeof(int));
    if (new_backing_array == nullptr) {
      throw std::runtime_error("grow: out of memory");
    }
    // move the pointer to the new backing array.
    s.data = new_backing_array;
    // update the capacity.
    s.cap = new_cap;
  }
  s.data[s.len] = v;
  s.len++;
  return s;
}

// Set the value at given index.
void set_value(Slice &s, int index, int value) {
  if (index < 0 || index >= s.len) {
    throw std::out_of_range("set_value: index out of range");
  }
  // setting the value by using pointer arithmetic.
  *(s.data + index) = value;
}

// Get the value at given index.
int get_value(const Slice &s, int index) {
  if (index < 0 || index >= s.len) {
    throw std::out_of_range("get_value: index out of range");
  }
  // getting the value by using pointer arithmetic.
  return *(s.data + index);
}

// Return a string representation of the slice.
// For example:
// [1, 2, 3]
std::string to_string(const Slice &s) {
  std::stringstream stream;
  stream << "[";
  for (int i = 0; i < s.len; i++) {
    stream << get_value(s, i);
    if (i != s.len - 1) {
      stream << ", ";
    }
  }
  stream << "]";
  return stream.str();
}

// Implement the << operator for printing the slice in beautify format.
// For example:
// Slice{ .len=2, .cap=4, .data=[1, 2] }
std::ostream &operator<<(std::ostream &os, const Slice &s) {
  os << "Slice{"
        " .len="  << s.len <<
        " .cap="  << s.cap <<
        " .data=" << to_string(s)
     << " }";
  return os;
}
