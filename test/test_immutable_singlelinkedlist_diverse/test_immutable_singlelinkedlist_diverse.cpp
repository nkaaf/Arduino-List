#include <Arduino.h>

#include "unity.h"

#include <SingleLinkedList.hpp>

// ---------- getSize ---------- //

void getSize_primitive(void) {
  SingleLinkedList<int> list;

  TEST_ASSERT_EQUAL_INT(0, list.getSize());

  list.add(1);

  TEST_ASSERT_EQUAL_INT(1, list.getSize());

  list.add(2);
  list.add(3);

  TEST_ASSERT_EQUAL_INT(3, list.getSize());
}

void getSize_class(void) {
  SingleLinkedList<String> list;

  TEST_ASSERT_EQUAL_INT(0, list.getSize());

  list.add("1");

  TEST_ASSERT_EQUAL_INT(1, list.getSize());

  list.add("2");
  list.add("3");

  TEST_ASSERT_EQUAL_INT(3, list.getSize());
}

// ---------- is mutable ---------- //

void isMutable_primitive(void) {
  SingleLinkedList<int> list;

  TEST_ASSERT_FALSE(list.isMutable());
}

void isMutable_class(void) {
  SingleLinkedList<String> list;

  TEST_ASSERT_FALSE(list.isMutable());
}

// ---------- is empty ---------- //

void isEmpty_primitive(void) {
  SingleLinkedList<int> list;

  TEST_ASSERT_TRUE(list.isEmpty());

  list.add(1);

  TEST_ASSERT_FALSE(list.isEmpty());

  list.add(2);
  list.add(3);

  TEST_ASSERT_FALSE(list.isEmpty());

  list.clear();

  TEST_ASSERT_TRUE(list.isEmpty());
}

void isEmpty_class(void) {
  SingleLinkedList<String> list;

  TEST_ASSERT_TRUE(list.isEmpty());

  list.add("1");

  TEST_ASSERT_FALSE(list.isEmpty());

  list.add("2");
  list.add("3");

  TEST_ASSERT_FALSE(list.isEmpty());

  list.clear();

  TEST_ASSERT_TRUE(list.isEmpty());
}

void setup() {
  UNITY_BEGIN();

  // ---------- getSize ---------- //
  RUN_TEST(getSize_primitive);
  RUN_TEST(getSize_class);

  // ---------- is mutable ---------- //
  RUN_TEST(isMutable_primitive);
  RUN_TEST(isMutable_class);

  // ---------- is empty ---------- //
  RUN_TEST(isEmpty_primitive);
  RUN_TEST(isEmpty_class);

  UNITY_END();
}

void loop() {
}
