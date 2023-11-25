#include <Arduino.h>

#include "unity.h"

#include <SingleLinkedList.hpp>

// ---------- T get(int index) ---------- //

void get_primitive(void) {
  SingleLinkedList<int> list;

  list.add(1);

  TEST_ASSERT_EQUAL_INT(1, list.get(0));
  TEST_ASSERT_EQUAL_INT(1, list.getSize());

  list.add(2);

  TEST_ASSERT_EQUAL_INT(1, list.get(0));
  TEST_ASSERT_EQUAL_INT(2, list.get(1));
  TEST_ASSERT_EQUAL_INT(2, list.getSize());
}

void get_class(void) {
  SingleLinkedList<String> list;

  list.add("1");

  TEST_ASSERT_EQUAL_STRING("1", list.get(0).c_str());
  TEST_ASSERT_EQUAL_INT(1, list.getSize());

  list.add("2");

  TEST_ASSERT_EQUAL_STRING("1", list.get(0).c_str());
  TEST_ASSERT_EQUAL_STRING("2", list.get(1).c_str());
  TEST_ASSERT_EQUAL_INT(2, list.getSize());
}

// ---------- T *getMutableValue(int index) ---------- //

void getMutableValue_primitive(void) {
  SingleLinkedList<int> list;

  list.add(1);

  TEST_ASSERT_EQUAL_PTR(nullptr, list.getMutableValue(0));
  TEST_ASSERT_EQUAL_INT(1, list.getSize());

  list.add(2);

  TEST_ASSERT_EQUAL_PTR(nullptr, list.getMutableValue(0));
  TEST_ASSERT_EQUAL_PTR(nullptr, list.getMutableValue(1));
  TEST_ASSERT_EQUAL_INT(2, list.getSize());
}

void getMutableValue_class(void) {
  SingleLinkedList<String> list;

  list.add("1");

  TEST_ASSERT_EQUAL_PTR(nullptr, list.getMutableValue(0));
  TEST_ASSERT_EQUAL_INT(1, list.getSize());

  list.add("2");

  TEST_ASSERT_EQUAL_PTR(nullptr, list.getMutableValue(0));
  TEST_ASSERT_EQUAL_PTR(nullptr, list.getMutableValue(1));
  TEST_ASSERT_EQUAL_INT(2, list.getSize());
}

// ---------- T operator[](int index) ---------- //

void get_operator_primitive(void) {
  SingleLinkedList<int> list;

  list.add(1);

  TEST_ASSERT_EQUAL_INT(1, list[0]);
  TEST_ASSERT_EQUAL_INT(1, list.getSize());

  list.add(2);

  TEST_ASSERT_EQUAL_INT(1, list[0]);
  TEST_ASSERT_EQUAL_INT(2, list[1]);
  TEST_ASSERT_EQUAL_INT(2, list.getSize());
}

void get_operator_class(void) {
  SingleLinkedList<String> list;

  list.add("1");

  TEST_ASSERT_EQUAL_STRING("1", list[0].c_str());
  TEST_ASSERT_EQUAL_INT(1, list.getSize());

  list.add("2");

  TEST_ASSERT_EQUAL_STRING("1", list[0].c_str());
  TEST_ASSERT_EQUAL_STRING("2", list[1].c_str());
  TEST_ASSERT_EQUAL_INT(2, list.getSize());
}

void setup() {
  UNITY_BEGIN();

  // ---------- T get(int index) ---------- //
  RUN_TEST(get_primitive);
  RUN_TEST(get_class);

  // ---------- T *getMutableValue(int index) ---------- //
  RUN_TEST(getMutableValue_primitive);
  RUN_TEST(getMutableValue_class);

  // ---------- T operator[](int index) ---------- //
  RUN_TEST(get_operator_primitive);
  RUN_TEST(get_operator_class);

  UNITY_END();
}

void loop() {
}
