#include <Arduino.h>

#include "unity.h"

#include <DoubleLinkedList.hpp>

// ---------- In different scope (ds) ---------- //

void addFirst_ds_rvalue_primitive(void) {
  DoubleLinkedList<int> list;

  {
    list.addFirst(1);
  }
  TEST_ASSERT_EQUAL_INT(1, list[0]);
  TEST_ASSERT_EQUAL_INT(1, list.getSize());

  {
    list.addFirst(2);
  }
  TEST_ASSERT_EQUAL_INT(2, list[0]);
  TEST_ASSERT_EQUAL_INT(1, list[1]);
  TEST_ASSERT_EQUAL_INT(2, list.getSize());
}

void addFirst_ds_lvalue_primitive(void) {
  DoubleLinkedList<int> list;

  {
    int a = 1;
    list.addFirst(a);

    TEST_ASSERT_EQUAL_INT(1, a);
    a = 2;
  }
  TEST_ASSERT_EQUAL_INT(1, list[0]);
  TEST_ASSERT_EQUAL_INT(1, list.getSize());

  {
    int b = 2;
    list.addFirst(b);

    TEST_ASSERT_EQUAL_INT(2, b);
    b = 3;
  }
  TEST_ASSERT_EQUAL_INT(2, list[0]);
  TEST_ASSERT_EQUAL_INT(1, list[1]);
  TEST_ASSERT_EQUAL_INT(2, list.getSize());
}

void addFirst_ds_rvalue_class(void) {
  DoubleLinkedList<String> list;

  {
    list.addFirst("1");
  }
  TEST_ASSERT_EQUAL_STRING("1", list[0].c_str());
  TEST_ASSERT_EQUAL_INT(1, list.getSize());

  {
    list.addFirst("2");
  }
  TEST_ASSERT_EQUAL_STRING("2", list[0].c_str());
  TEST_ASSERT_EQUAL_STRING("1", list[1].c_str());
  TEST_ASSERT_EQUAL_INT(2, list.getSize());
}

void addFirst_ds_lvalue_class(void) {
  DoubleLinkedList<String> list;

  {
    String a = "1";
    list.addFirst(a);

    TEST_ASSERT_EQUAL_STRING("1", a.c_str());
    a = "2";
  }
  TEST_ASSERT_EQUAL_STRING("1", list[0].c_str());
  TEST_ASSERT_EQUAL_INT(1, list.getSize());

  {
    String b = "2";
    list.addFirst(b);

    TEST_ASSERT_EQUAL_STRING("2", b.c_str());
    b = "3";
  }
  TEST_ASSERT_EQUAL_STRING("2", list[0].c_str());
  TEST_ASSERT_EQUAL_STRING("1", list[1].c_str());
  TEST_ASSERT_EQUAL_INT(2, list.getSize());
}

// ---------- In same scope (ss) ---------- //

void addFirst_ss_rvalue_primitive(void) {
  DoubleLinkedList<int> list;

  list.addFirst(1);
  TEST_ASSERT_EQUAL_INT(1, list[0]);
  TEST_ASSERT_EQUAL_INT(1, list.getSize());

  list.addFirst(2);
  TEST_ASSERT_EQUAL_INT(2, list[0]);
  TEST_ASSERT_EQUAL_INT(1, list[1]);
  TEST_ASSERT_EQUAL_INT(2, list.getSize());
}

void addFirst_ss_lvalue_primitive(void) {
  DoubleLinkedList<int> list;

  int a = 1, b = 2;

  list.addFirst(a);

  TEST_ASSERT_EQUAL_INT(1, a);
  a = 2;
  TEST_ASSERT_EQUAL_INT(1, list[0]);
  TEST_ASSERT_EQUAL_INT(1, list.getSize());

  list.addFirst(b);

  TEST_ASSERT_EQUAL_INT(2, b);
  b = 3;
  TEST_ASSERT_EQUAL_INT(2, list[0]);
  TEST_ASSERT_EQUAL_INT(1, list[1]);
  TEST_ASSERT_EQUAL_INT(2, list.getSize());
}

void addFirst_ss_rvalue_class(void) {
  DoubleLinkedList<String> list;

  list.addFirst("1");
  TEST_ASSERT_EQUAL_STRING("1", list[0].c_str());
  TEST_ASSERT_EQUAL_INT(1, list.getSize());

  list.addFirst("2");
  TEST_ASSERT_EQUAL_STRING("2", list[0].c_str());
  TEST_ASSERT_EQUAL_STRING("1", list[1].c_str());
  TEST_ASSERT_EQUAL_INT(2, list.getSize());
}

void addFirst_ss_lvalue_class(void) {
  DoubleLinkedList<String> list;

  String a = "1", b = "2";

  list.addFirst(a);

  TEST_ASSERT_EQUAL_STRING("1", a.c_str());
  a = "2";
  TEST_ASSERT_EQUAL_STRING("1", list[0].c_str());
  TEST_ASSERT_EQUAL_INT(1, list.getSize());

  list.addFirst(b);

  TEST_ASSERT_EQUAL_STRING("2", b.c_str());
  b = "3";
  TEST_ASSERT_EQUAL_STRING("2", list[0].c_str());
  TEST_ASSERT_EQUAL_STRING("1", list[1].c_str());
  TEST_ASSERT_EQUAL_INT(2, list.getSize());
}

void setup() {
  UNITY_BEGIN();

  // different scope tests
  RUN_TEST(addFirst_ds_rvalue_primitive);
  RUN_TEST(addFirst_ds_lvalue_primitive);
  RUN_TEST(addFirst_ds_rvalue_class);
  RUN_TEST(addFirst_ds_lvalue_class);

  // same scope tests
  RUN_TEST(addFirst_ss_rvalue_primitive);
  RUN_TEST(addFirst_ss_lvalue_primitive);
  RUN_TEST(addFirst_ss_rvalue_class);
  RUN_TEST(addFirst_ss_lvalue_class);

  UNITY_END();
}

void loop() {
}
