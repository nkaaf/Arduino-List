#include <Arduino.h>

#include "unity.h"

#include <DoubleLinkedList.hpp>

// ---------- bool equals(AbstractList<T> &other) ---------- //

void equals_primitive(void) {
  DoubleLinkedList<int> list;
  DoubleLinkedList<int> other;

  TEST_ASSERT_TRUE(list.equals(other));

  list.add(1);

  TEST_ASSERT_FALSE(list.equals(other));

  list.add(2);
  other.add(1);
  other.add(2);

  TEST_ASSERT_TRUE(list.equals(other));

  other.add(3);

  TEST_ASSERT_FALSE(list.equals(other));

  list.add(3);

  TEST_ASSERT_TRUE(list.equals(other));

  list.clear();

  DoubleLinkedList<int> mutableList(true);

  TEST_ASSERT_FALSE(list.equals(mutableList));
}

void equals_class(void) {
  DoubleLinkedList<String> list;
  DoubleLinkedList<String> other;

  TEST_ASSERT_TRUE(list.equals(other));

  list.add("1");

  TEST_ASSERT_FALSE(list.equals(other));

  list.add("2");
  other.add("1");
  other.add("2");

  TEST_ASSERT_TRUE(list.equals(other));

  other.add("3");

  TEST_ASSERT_FALSE(list.equals(other));

  list.add("3");

  TEST_ASSERT_TRUE(list.equals(other));

  list.clear();

  DoubleLinkedList<String> mutableList(true);

  TEST_ASSERT_FALSE(list.equals(mutableList));
}

// ---------- bool operator==(AbstractList<T> &other) ---------- //
void equals_operator_primitive(void) {
  DoubleLinkedList<int> list;
  DoubleLinkedList<int> other;

  TEST_ASSERT_TRUE(list == other);

  list.add(1);

  TEST_ASSERT_FALSE(list == other);

  list.add(2);
  other.add(1);
  other.add(2);

  TEST_ASSERT_TRUE(list == other);

  other.add(3);

  TEST_ASSERT_FALSE(list == other);

  list.add(3);

  TEST_ASSERT_TRUE(list == other);

  list.clear();

  DoubleLinkedList<int> mutableList(true);

  TEST_ASSERT_FALSE(list == mutableList);
}

void equals_operator_class(void) {
  DoubleLinkedList<String> list;
  DoubleLinkedList<String> other;

  TEST_ASSERT_TRUE(list == other);

  list.add("1");

  TEST_ASSERT_FALSE(list == other);

  list.add("2");
  other.add("1");
  other.add("2");

  TEST_ASSERT_TRUE(list == other);

  other.add("3");

  TEST_ASSERT_FALSE(list == other);

  list.add("3");

  TEST_ASSERT_TRUE(list == other);

  list.clear();

  DoubleLinkedList<String> mutableList(true);

  TEST_ASSERT_FALSE(list == mutableList);
}

// ---------- bool operator!=(AbstractList<T> &other) ---------- //
void not_equals_operator_primitive(void) {
  DoubleLinkedList<int> list;
  DoubleLinkedList<int> other;

  TEST_ASSERT_FALSE(list != other);

  list.add(1);

  TEST_ASSERT_TRUE(list != other);

  list.add(2);
  other.add(1);
  other.add(2);

  TEST_ASSERT_FALSE(list != other);

  other.add(3);

  TEST_ASSERT_TRUE(list != other);

  list.add(3);

  TEST_ASSERT_FALSE(list != other);

  list.clear();

  DoubleLinkedList<int> mutableList(true);

  TEST_ASSERT_TRUE(list != mutableList);
}

void not_equals_operator_class(void) {
  DoubleLinkedList<String> list;
  DoubleLinkedList<String> other;

  TEST_ASSERT_FALSE(list != other);

  list.add("1");

  TEST_ASSERT_TRUE(list != other);

  list.add("2");
  other.add("1");
  other.add("2");

  TEST_ASSERT_FALSE(list != other);

  other.add("3");

  TEST_ASSERT_TRUE(list != other);

  list.add("3");

  TEST_ASSERT_FALSE(list != other);

  list.clear();

  DoubleLinkedList<String> mutableList(true);

  TEST_ASSERT_TRUE(list != mutableList);
}

void setup() {
  UNITY_BEGIN();

  // ---------- bool equals(AbstractList<T> &other) ---------- //
  RUN_TEST(equals_primitive);
  RUN_TEST(equals_class);

  // ---------- bool operator==(AbstractList<T> &other) ---------- //
  RUN_TEST(equals_operator_primitive);
  RUN_TEST(equals_operator_class);

  // ---------- bool operator!=(AbstractList<T> &other) ---------- //
  RUN_TEST(not_equals_operator_primitive);
  RUN_TEST(not_equals_operator_class);

  UNITY_END();
}

void loop() {
}
