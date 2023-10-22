#pragma once
#include <string>

typedef struct {
  int *data;// for simplicity, we only support int slices.
  int len;
  int cap;
} Slice;

// Create a slice of length len and capacity cap.
Slice make(int len, int cap);

// Deallocate the backing array.
void free_slice(Slice &s);

// Append a new element to the slice.
Slice append(Slice s, int v);

// Set the value at given index.
void set_value(Slice &s, int index, int value);

// Get the value at given index.
int get_value(const Slice &s, int index);

// Return a string representation of the slice.
// For example:
// [1, 2, 3]
std::string to_string(const Slice &s);

// Implement the << operator for printing the slice in beautify format.
// For example:
// Slice{ .len=2, .cap=4, .data=[1, 2] }
std::ostream &operator<<(std::ostream &os, const Slice &s);