#include <Arduino.h>

#include "unity.h"

#include <SingleLinkedList.hpp>

// ---------- In different scope (ds) ---------- //

void add_ds_rvalue_primitive(void) {
  SingleLinkedList<int> list;

  {
    list + 1;
  }
  TEST_ASSERT_EQUAL_INT(1, list[0]);
  TEST_ASSERT_EQUAL_INT(1, list.getSize());

  {
    list + 2;
  }
  TEST_ASSERT_EQUAL_INT(1, list[0]);
  TEST_ASSERT_EQUAL_INT(2, list[1]);
  TEST_ASSERT_EQUAL_INT(2, list.getSize());
}

void add_ds_lvalue_primitive(void) {
  SingleLinkedList<int> list;

  {
    int a = 1;
    list + a;

    TEST_ASSERT_EQUAL_INT(1, a);
    a = 2;
  }
  TEST_ASSERT_EQUAL_INT(1, list[0]);
  TEST_ASSERT_EQUAL_INT(1, list.getSize());

  {
    int b = 2;
    list + b;

    TEST_ASSERT_EQUAL_INT(2, b);
    b = 3;
  }
  TEST_ASSERT_EQUAL_INT(1, list[0]);
  TEST_ASSERT_EQUAL_INT(2, list[1]);
  TEST_ASSERT_EQUAL_INT(2, list.getSize());
}

void add_ds_rvalue_class(void) {
  SingleLinkedList<String> list;

  {
    list + "1";
  }
  TEST_ASSERT_EQUAL_STRING("1", list[0].c_str());
  TEST_ASSERT_EQUAL_INT(1, list.getSize());

  {
    list + "2";
  }
  TEST_ASSERT_EQUAL_STRING("1", list[0].c_str());
  TEST_ASSERT_EQUAL_STRING("2", list[1].c_str());
  TEST_ASSERT_EQUAL_INT(2, list.getSize());
}

void add_ds_lvalue_class(void) {
  SingleLinkedList<String> list;

  {
    String a = "1";
    list + a;

    TEST_ASSERT_EQUAL_STRING("1", a.c_str());
    a = "2";
  }
  TEST_ASSERT_EQUAL_STRING("1", list[0].c_str());
  TEST_ASSERT_EQUAL_INT(1, list.getSize());

  {
    String b = "2";
    list + b;

    TEST_ASSERT_EQUAL_STRING("2", b.c_str());
    b = "3";
  }
  TEST_ASSERT_EQUAL_STRING("1", list[0].c_str());
  TEST_ASSERT_EQUAL_STRING("2", list[1].c_str());
  TEST_ASSERT_EQUAL_INT(2, list.getSize());
}

// ---------- In same scope (ss) ---------- //

void add_ss_rvalue_primitive(void) {
  SingleLinkedList<int> list;

  list + 1;
  TEST_ASSERT_EQUAL_INT(1, list[0]);
  TEST_ASSERT_EQUAL_INT(1, list.getSize());

  list + 2;
  TEST_ASSERT_EQUAL_INT(1, list[0]);
  TEST_ASSERT_EQUAL_INT(2, list[1]);
  TEST_ASSERT_EQUAL_INT(2, list.getSize());
}

void add_ss_lvalue_primitive(void) {
  SingleLinkedList<int> list;

  int a = 1, b = 2;

  list + a;

  TEST_ASSERT_EQUAL_INT(1, a);
  a = 2;
  TEST_ASSERT_EQUAL_INT(1, list[0]);
  TEST_ASSERT_EQUAL_INT(1, list.getSize());

  list + b;

  TEST_ASSERT_EQUAL_INT(2, b);
  b = 3;
  TEST_ASSERT_EQUAL_INT(1, list[0]);
  TEST_ASSERT_EQUAL_INT(2, list[1]);
  TEST_ASSERT_EQUAL_INT(2, list.getSize());
}

void add_ss_rvalue_class(void) {
  SingleLinkedList<String> list;

  list + "1";
  TEST_ASSERT_EQUAL_STRING("1", list[0].c_str());
  TEST_ASSERT_EQUAL_INT(1, list.getSize());

  list + "2";
  TEST_ASSERT_EQUAL_STRING("1", list[0].c_str());
  TEST_ASSERT_EQUAL_STRING("2", list[1].c_str());
  TEST_ASSERT_EQUAL_INT(2, list.getSize());
}

void add_ss_lvalue_class(void) {
  SingleLinkedList<String> list;

  String a = "1", b = "2";

  list + a;

  TEST_ASSERT_EQUAL_STRING("1", a.c_str());
  a = "2";
  TEST_ASSERT_EQUAL_STRING("1", list[0].c_str());
  TEST_ASSERT_EQUAL_INT(1, list.getSize());

  list + b;

  TEST_ASSERT_EQUAL_STRING("2", b.c_str());
  b = "3";
  TEST_ASSERT_EQUAL_STRING("1", list[0].c_str());
  TEST_ASSERT_EQUAL_STRING("2", list[1].c_str());
  TEST_ASSERT_EQUAL_INT(2, list.getSize());
}

// ---------- void operator+(AbstractList<T> &list) ---------- //

void addAll_primitive(void) {
  SingleLinkedList<int> fromList;
  SingleLinkedList<int> toList;

  toList.add(1);
  toList.add(2);
  toList.add(3);
  fromList.add(4);
  fromList.add(5);
  fromList.add(6);

  toList + fromList;

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

void addAll_class(void) {
  SingleLinkedList<String> fromList;
  SingleLinkedList<String> toList;

  toList.add("1");
  toList.add("2");
  toList.add("3");
  fromList.add("4");
  fromList.add("5");
  fromList.add("6");

  toList + fromList;

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

void setup() {
  UNITY_BEGIN();

  // different scope tests
  RUN_TEST(add_ds_rvalue_primitive);
  RUN_TEST(add_ds_lvalue_primitive);
  RUN_TEST(add_ds_rvalue_class);
  RUN_TEST(add_ds_lvalue_class);

  // same scope tests
  RUN_TEST(add_ss_rvalue_primitive);
  RUN_TEST(add_ss_lvalue_primitive);
  RUN_TEST(add_ss_rvalue_class);
  RUN_TEST(add_ss_lvalue_class);

  // ---------- void operator+(AbstractList<T> &list) ---------- //
  RUN_TEST(addAll_primitive);
  RUN_TEST(addAll_class);

  UNITY_END();
}

void loop() {
}
