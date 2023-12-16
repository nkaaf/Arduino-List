#include <Arduino.h>

#include "unity.h"

#include <DoubleLinkedList.hpp>

// ---------- void addAll(AbstractList<T> &list) ---------- //

void addAll_list_primitive(void) {
  DoubleLinkedList<int> fromList;
  DoubleLinkedList<int> toList;

  toList.add(1);
  toList.add(2);
  toList.add(3);
  fromList.add(4);
  fromList.add(5);
  fromList.add(6);

  toList.addAll(fromList);

  TEST_ASSERT_EQUAL_INT(4, fromList[0]);
  TEST_ASSERT_EQUAL_INT(5, fromList[1]);
  TEST_ASSERT_EQUAL_INT(6, fromList[2]);
  TEST_ASSERT_EQUAL_INT(3, fromList.getSize());

  fromList.clear();

  TEST_ASSERT_EQUAL_INT(1, toList[0]);
  TEST_ASSERT_EQUAL_INT(2, toList[1]);
  TEST_ASSERT_EQUAL_INT(3, toList[2]);
  TEST_ASSERT_EQUAL_INT(4, toList[3]);
  TEST_ASSERT_EQUAL_INT(5, toList[4]);
  TEST_ASSERT_EQUAL_INT(6, toList[5]);
  TEST_ASSERT_EQUAL_INT(6, toList.getSize());
}

void addAll_list_class(void) {
  DoubleLinkedList<String> fromList;
  DoubleLinkedList<String> toList;

  toList.add("1");
  toList.add("2");
  toList.add("3");
  fromList.add("4");
  fromList.add("5");
  fromList.add("6");

  toList.addAll(fromList);

  TEST_ASSERT_EQUAL_STRING("4", fromList[0].c_str());
  TEST_ASSERT_EQUAL_STRING("5", fromList[1].c_str());
  TEST_ASSERT_EQUAL_STRING("6", fromList[2].c_str());
  TEST_ASSERT_EQUAL_INT(3, fromList.getSize());

  fromList.clear();

  TEST_ASSERT_EQUAL_STRING("1", toList[0].c_str());
  TEST_ASSERT_EQUAL_STRING("2", toList[1].c_str());
  TEST_ASSERT_EQUAL_STRING("3", toList[2].c_str());
  TEST_ASSERT_EQUAL_STRING("4", toList[3].c_str());
  TEST_ASSERT_EQUAL_STRING("5", toList[4].c_str());
  TEST_ASSERT_EQUAL_STRING("6", toList[5].c_str());
  TEST_ASSERT_EQUAL_INT(6, toList.getSize());
}

// ---------- void addAll(int index, AbstractList<T> &list) ---------- //

void addAll_index_primitive(void) {
  DoubleLinkedList<int> fromList;
  DoubleLinkedList<int> toList;

  toList.add(1);
  toList.add(5);
  toList.add(6);
  fromList.add(2);
  fromList.add(3);
  fromList.add(4);

  toList.addAll(1, fromList);

  TEST_ASSERT_EQUAL_INT(2, fromList[0]);
  TEST_ASSERT_EQUAL_INT(3, fromList[1]);
  TEST_ASSERT_EQUAL_INT(4, fromList[2]);
  TEST_ASSERT_EQUAL_INT(3, fromList.getSize());

  fromList.clear();

  TEST_ASSERT_EQUAL_INT(1, toList[0]);
  TEST_ASSERT_EQUAL_INT(2, toList[1]);
  TEST_ASSERT_EQUAL_INT(3, toList[2]);
  TEST_ASSERT_EQUAL_INT(4, toList[3]);
  TEST_ASSERT_EQUAL_INT(5, toList[4]);
  TEST_ASSERT_EQUAL_INT(6, toList[5]);
  TEST_ASSERT_EQUAL_INT(6, toList.getSize());
}

void addAll_index_class(void) {
  DoubleLinkedList<String> fromList;
  DoubleLinkedList<String> toList;

  toList.add("1");
  toList.add("5");
  toList.add("6");
  fromList.add("2");
  fromList.add("3");
  fromList.add("4");

  toList.addAll(1, fromList);

  TEST_ASSERT_EQUAL_STRING("2", fromList[0].c_str());
  TEST_ASSERT_EQUAL_STRING("3", fromList[1].c_str());
  TEST_ASSERT_EQUAL_STRING("4", fromList[2].c_str());
  TEST_ASSERT_EQUAL_INT(3, fromList.getSize());

  fromList.clear();

  TEST_ASSERT_EQUAL_STRING("1", toList[0].c_str());
  TEST_ASSERT_EQUAL_STRING("2", toList[1].c_str());
  TEST_ASSERT_EQUAL_STRING("3", toList[2].c_str());
  TEST_ASSERT_EQUAL_STRING("4", toList[3].c_str());
  TEST_ASSERT_EQUAL_STRING("5", toList[4].c_str());
  TEST_ASSERT_EQUAL_STRING("6", toList[5].c_str());
  TEST_ASSERT_EQUAL_INT(6, toList.getSize());
}

// ---------- void addAll(T *arr, size_t arrSize) ---------- //

void addAll_array_primitive(void) {
  int fromArray[] = {4, 5, 6};
  DoubleLinkedList<int> toList;

  toList.add(1);
  toList.add(2);
  toList.add(3);

  toList.addAll(fromArray, 3);

  TEST_ASSERT_EQUAL_INT(4, fromArray[0]);
  TEST_ASSERT_EQUAL_INT(5, fromArray[1]);
  TEST_ASSERT_EQUAL_INT(6, fromArray[2]);

  fromArray[0] = 7;
  fromArray[1] = 8;
  fromArray[2] = 9;

  TEST_ASSERT_EQUAL_INT(1, toList[0]);
  TEST_ASSERT_EQUAL_INT(2, toList[1]);
  TEST_ASSERT_EQUAL_INT(3, toList[2]);
  TEST_ASSERT_EQUAL_INT(4, toList[3]);
  TEST_ASSERT_EQUAL_INT(5, toList[4]);
  TEST_ASSERT_EQUAL_INT(6, toList[5]);
  TEST_ASSERT_EQUAL_INT(6, toList.getSize());
}

void addAll_array_class(void) {
  String fromArray[] = {"4", "5", "6"};
  DoubleLinkedList<String> toList;

  toList.add("1");
  toList.add("2");
  toList.add("3");

  toList.addAll(fromArray, 3);

  TEST_ASSERT_EQUAL_STRING("4", fromArray[0].c_str());
  TEST_ASSERT_EQUAL_STRING("5", fromArray[1].c_str());
  TEST_ASSERT_EQUAL_STRING("6", fromArray[2].c_str());

  fromArray[0] = "7";
  fromArray[1] = "8";
  fromArray[2] = "9";

  TEST_ASSERT_EQUAL_STRING("1", toList[0].c_str());
  TEST_ASSERT_EQUAL_STRING("2", toList[1].c_str());
  TEST_ASSERT_EQUAL_STRING("3", toList[2].c_str());
  TEST_ASSERT_EQUAL_STRING("4", toList[3].c_str());
  TEST_ASSERT_EQUAL_STRING("5", toList[4].c_str());
  TEST_ASSERT_EQUAL_STRING("6", toList[5].c_str());
  TEST_ASSERT_EQUAL_INT(6, toList.getSize());
}

// ---------- void addAll(int index, T* arr, size_t arrSize) ---------- //

void addAll_array_index_primitive(void) {
  int fromArray[] = {2, 3, 4};
  DoubleLinkedList<int> toList;

  toList.add(1);
  toList.add(5);
  toList.add(6);

  toList.addAll(1, fromArray, 3);

  TEST_ASSERT_EQUAL_INT(2, fromArray[0]);
  TEST_ASSERT_EQUAL_INT(3, fromArray[1]);
  TEST_ASSERT_EQUAL_INT(4, fromArray[2]);

  fromArray[0] = 7;
  fromArray[1] = 8;
  fromArray[2] = 9;

  TEST_ASSERT_EQUAL_INT(1, toList[0]);
  TEST_ASSERT_EQUAL_INT(2, toList[1]);
  TEST_ASSERT_EQUAL_INT(3, toList[2]);
  TEST_ASSERT_EQUAL_INT(4, toList[3]);
  TEST_ASSERT_EQUAL_INT(5, toList[4]);
  TEST_ASSERT_EQUAL_INT(6, toList[5]);
  TEST_ASSERT_EQUAL_INT(6, toList.getSize());
}

void addAll_array_index_class(void) {
  String fromArray[] = {"2", "3", "4"};
  DoubleLinkedList<String> toList;

  toList.add("1");
  toList.add("5");
  toList.add("6");

  toList.addAll(1, fromArray, 3);

  TEST_ASSERT_EQUAL_STRING("2", fromArray[0].c_str());
  TEST_ASSERT_EQUAL_STRING("3", fromArray[1].c_str());
  TEST_ASSERT_EQUAL_STRING("4", fromArray[2].c_str());

  fromArray[0] = "7";
  fromArray[1] = "8";
  fromArray[2] = "9";

  TEST_ASSERT_EQUAL_STRING("1", toList[0].c_str());
  TEST_ASSERT_EQUAL_STRING("2", toList[1].c_str());
  TEST_ASSERT_EQUAL_STRING("3", toList[2].c_str());
  TEST_ASSERT_EQUAL_STRING("4", toList[3].c_str());
  TEST_ASSERT_EQUAL_STRING("5", toList[4].c_str());
  TEST_ASSERT_EQUAL_STRING("6", toList[5].c_str());
  TEST_ASSERT_EQUAL_INT(6, toList.getSize());
}

void setup() {
  UNITY_BEGIN();

  // ---------- void addAll(AbstractList<T> &list) ---------- //
  RUN_TEST(addAll_list_primitive);
  RUN_TEST(addAll_list_class);

  // ---------- void addAll(int index, AbstractList<T> &list) ---------- //
  RUN_TEST(addAll_index_primitive);
  RUN_TEST(addAll_index_class);

  // ---------- void addAll(T *arr, size_t arrSize) ---------- //
  RUN_TEST(addAll_array_primitive);
  RUN_TEST(addAll_array_class);

  // ---------- void addAll(int index, T* arr, size_t arrSize) ---------- //
  RUN_TEST(addAll_array_index_primitive);
  RUN_TEST(addAll_array_index_class);

  UNITY_END();
}

void loop() {
}
