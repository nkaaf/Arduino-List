#include <Arduino.h>

#include "unity.h"

#include <SingleLinkedList.hpp>

// ---------- T *toArray() ---------- //

void toArray_primitive(void) {
  SingleLinkedList<int> list;

  int *nullptrArr = list.toArray();
  TEST_ASSERT_EQUAL_PTR(nullptr, nullptrArr);

  list.add(1);
  list.add(2);
  list.add(3);
  int *array = list.toArray();

  TEST_ASSERT_EQUAL_INT(1, list[0]);
  TEST_ASSERT_EQUAL_INT(2, list[1]);
  TEST_ASSERT_EQUAL_INT(3, list[2]);
  TEST_ASSERT_EQUAL_INT(3, list.getSize());
  TEST_ASSERT_EQUAL_INT(1, array[0]);
  TEST_ASSERT_EQUAL_INT(2, array[1]);
  TEST_ASSERT_EQUAL_INT(3, array[2]);

  free(array);
}

void toArray_class(void) {
  SingleLinkedList<String> list;

  String *nullptrArr = list.toArray();
  TEST_ASSERT_EQUAL_PTR(nullptr, nullptrArr);

  list.add("1");
  list.add("2");
  list.add("3");
  String *array = list.toArray();

  TEST_ASSERT_EQUAL_STRING("1", list[0].c_str());
  TEST_ASSERT_EQUAL_STRING("2", list[1].c_str());
  TEST_ASSERT_EQUAL_STRING("3", list[2].c_str());
  TEST_ASSERT_EQUAL_INT(3, list.getSize());
  TEST_ASSERT_EQUAL_STRING("1", array[0].c_str());
  TEST_ASSERT_EQUAL_STRING("2", array[1].c_str());
  TEST_ASSERT_EQUAL_STRING("3", array[2].c_str());

  free(array);
}

// ---------- void fromArray(T *arr, size_t arrSize) ---------- //

void fromArray_primitive(void) {
}

void fromArray_class(void) {
}

void setup() {
  UNITY_BEGIN();

  // ---------- T *toArray() ---------- //
  RUN_TEST(toArray_primitive);
  RUN_TEST(toArray_class);

  UNITY_END();
}

void loop() {
}