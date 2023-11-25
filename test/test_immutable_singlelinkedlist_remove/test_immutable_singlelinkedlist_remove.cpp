#include <Arduino.h>

#include "unity.h"

#include <SingleLinkedList.hpp>

// ---------- void clear() ---------- //

void clear_primitive(void) {
  SingleLinkedList<int> list;

  list.add(1);
  list.add(2);
  list.add(3);

  TEST_ASSERT_EQUAL_INT(3, list.getSize());

  list.clear();

  TEST_ASSERT_EQUAL_INT(0, list.getSize());
}

void clear_class(void) {
  SingleLinkedList<String> list;

  list.add("1");
  list.add("2");
  list.add("3");

  TEST_ASSERT_EQUAL_INT(3, list.getSize());

  list.clear();

  TEST_ASSERT_EQUAL_INT(0, list.getSize());
}

// ---------- void removeAll() ---------- //

void removeAll_primitive(void) {
  SingleLinkedList<int> list;

  list.add(1);
  list.add(2);
  list.add(3);

  TEST_ASSERT_EQUAL_INT(3, list.getSize());

  list.removeAll();

  TEST_ASSERT_EQUAL_INT(0, list.getSize());
}

void removeAll_class(void) {
  SingleLinkedList<String> list;

  list.add("1");
  list.add("2");
  list.add("3");

  TEST_ASSERT_EQUAL_INT(3, list.getSize());

  list.removeAll();

  TEST_ASSERT_EQUAL_INT(0, list.getSize());
}

// ---------- void remove(int index) ---------- //

void remove_primitive(void) {
  SingleLinkedList<int> list;

  list.add(1);

  TEST_ASSERT_EQUAL_INT(1, list.getSize());

  list.remove(0);

  TEST_ASSERT_EQUAL_INT(0, list.getSize());

  list.add(2);
  list.add(3);
  list.add(4);

  TEST_ASSERT_EQUAL_INT(3, list.getSize());

  list.remove(1);

  TEST_ASSERT_EQUAL_INT(2, list.get(0));
  TEST_ASSERT_EQUAL_INT(4, list.get(1));
  TEST_ASSERT_EQUAL_INT(2, list.getSize());
}

void remove_class(void) {
  SingleLinkedList<String> list;

  list.add("1");

  TEST_ASSERT_EQUAL_INT(1, list.getSize());

  list.remove(0);

  TEST_ASSERT_EQUAL_INT(0, list.getSize());

  list.add("2");
  list.add("3");
  list.add("4");

  TEST_ASSERT_EQUAL_INT(3, list.getSize());

  list.remove(1);

  TEST_ASSERT_EQUAL_STRING("2", list.get(0).c_str());
  TEST_ASSERT_EQUAL_STRING("4", list.get(1).c_str());
  TEST_ASSERT_EQUAL_INT(2, list.getSize());
}

// ---------- void removeFirst() ---------- //

void removeFirst_primitive(void) {
  SingleLinkedList<int> list;

  list.add(1);

  TEST_ASSERT_EQUAL_INT(1, list.getSize());

  list.removeFirst();

  TEST_ASSERT_EQUAL_INT(0, list.getSize());

  list.add(2);
  list.add(3);
  list.add(4);

  TEST_ASSERT_EQUAL_INT(3, list.getSize());

  list.removeFirst();

  TEST_ASSERT_EQUAL_INT(3, list.get(0));
  TEST_ASSERT_EQUAL_INT(4, list.get(1));
  TEST_ASSERT_EQUAL_INT(2, list.getSize());
}

void removeFirst_class(void) {
  SingleLinkedList<String> list;

  list.add("1");

  TEST_ASSERT_EQUAL_INT(1, list.getSize());

  list.removeFirst();

  TEST_ASSERT_EQUAL_INT(0, list.getSize());

  list.add("2");
  list.add("3");
  list.add("4");

  TEST_ASSERT_EQUAL_INT(3, list.getSize());

  list.removeFirst();

  TEST_ASSERT_EQUAL_STRING("3", list.get(0).c_str());
  TEST_ASSERT_EQUAL_STRING("4", list.get(1).c_str());
  TEST_ASSERT_EQUAL_INT(2, list.getSize());
}

// ---------- void removeLast() ---------- //

void removeLast_primitive(void) {
  SingleLinkedList<int> list;

  list.add(1);

  TEST_ASSERT_EQUAL_INT(1, list.getSize());

  list.removeLast();

  TEST_ASSERT_EQUAL_INT(0, list.getSize());

  list.add(2);
  list.add(3);
  list.add(4);

  TEST_ASSERT_EQUAL_INT(3, list.getSize());

  list.removeLast();

  TEST_ASSERT_EQUAL_INT(2, list.get(0));
  TEST_ASSERT_EQUAL_INT(3, list.get(1));
  TEST_ASSERT_EQUAL_INT(2, list.getSize());
}

void removeLast_class(void) {
  SingleLinkedList<String> list;

  list.add("1");

  TEST_ASSERT_EQUAL_INT(1, list.getSize());

  list.removeLast();

  TEST_ASSERT_EQUAL_INT(0, list.getSize());

  list.add("2");
  list.add("3");
  list.add("4");

  TEST_ASSERT_EQUAL_INT(3, list.getSize());

  list.removeLast();

  TEST_ASSERT_EQUAL_STRING("2", list.get(0).c_str());
  TEST_ASSERT_EQUAL_STRING("3", list.get(1).c_str());
  TEST_ASSERT_EQUAL_INT(2, list.getSize());
}

void setup() {
  UNITY_BEGIN();

  // ---------- void clear() ---------- //
  RUN_TEST(clear_primitive);
  RUN_TEST(clear_class);

  // ---------- void removeAll() ---------- //
  RUN_TEST(removeAll_primitive);
  RUN_TEST(removeAll_class);

  // ---------- void remove(int index) ---------- //
  RUN_TEST(remove_primitive);
  RUN_TEST(remove_class);

  // ---------- void removeFirst() ---------- //
  RUN_TEST(removeFirst_primitive);
  RUN_TEST(removeFirst_class);

  // ---------- void removeLast() ---------- //
  RUN_TEST(removeLast_primitive);
  RUN_TEST(removeLast_class);

  UNITY_END();
}

void loop() {
}
