#include "slice.h"
#include <gtest/gtest.h>

TEST(SliceTest, make_ok) {
  Slice s = make(0, 1);
  EXPECT_EQ(s.len, 0);
  EXPECT_EQ(s.cap, 1);
  EXPECT_NE(s.data, nullptr);
  free_slice(s);
}


TEST(SliceTest, make_len_gt_cap) {
  EXPECT_THROW(make(2, 1), std::runtime_error);
}

TEST(SliceTest, append_with_grow) {
  Slice s = make(0, 1);
  for (int i = 0; i < 10; i++) {
    s = append(s, i);
  }
  EXPECT_EQ(s.len, 10);
  EXPECT_EQ(s.cap, 16);
  EXPECT_NE(s.data, nullptr);
  free_slice(s);
}

TEST(SliceTest, append_without_grow) {
  Slice s = make(0, 10);
  for (int i = 0; i < 10; i++) {
    s = append(s, i);
  }
  EXPECT_EQ(s.len, 10);
  EXPECT_EQ(s.cap, 10);
  EXPECT_NE(s.data, nullptr);
  free_slice(s);
}

TEST(SliceTest, set_value_ok) {
  Slice s = make(0, 1);
  s = append(s, 1);
  set_value(s, 0, 100);
  EXPECT_EQ(get_value(s, 0), 100);
  free_slice(s);
}

TEST(SliceTest, set_value_index_out_of_range) {
  Slice s = make(0, 1);
  s = append(s, 1);
  EXPECT_THROW(set_value(s, 1, 100), std::out_of_range);
  free_slice(s);
}

TEST(SliceTest, get_value_ok) {
  Slice s = make(0, 1);
  s = append(s, 1);
  EXPECT_EQ(get_value(s, 0), 1);
  free_slice(s);
}

TEST(SliceTest, get_value_index_out_of_range) {
  Slice s = make(0, 1);
  s = append(s, 1);
  EXPECT_THROW(get_value(s, 1), std::out_of_range);
  free_slice(s);
}

TEST(SliceTest, to_string) {
  Slice s = make(0, 1);
  s = append(s, 1);
  s = append(s, 2);
  s = append(s, 3);
  EXPECT_EQ(to_string(s), "[1, 2, 3]");
  EXPECT_EQ(s.len, 3);
  EXPECT_EQ(s.cap, 4);
  free_slice(s);
}

TEST(SliceTest, to_string_empty) {
  Slice s = make(0, 1);
  EXPECT_EQ(to_string(s), "[]");
  EXPECT_EQ(s.len, 0);
  EXPECT_EQ(s.cap, 1);
  free_slice(s);
}

TEST(SliceTest, outstream_operator) {
  Slice s = make(0, 1);
  s = append(s, 1);
  s = append(s, 2);
  s = append(s, 3);
  std::stringstream stream;
  stream << s;
  EXPECT_EQ(stream.str(), "Slice{ .len=3 .cap=4 .data=[1, 2, 3] }");
  EXPECT_EQ(s.len, 3) << "len should not be changed";
  EXPECT_EQ(s.cap, 4);
  free_slice(s);
}