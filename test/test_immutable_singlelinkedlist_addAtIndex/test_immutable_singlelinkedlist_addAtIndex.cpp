#include <Arduino.h>

#include "unity.h"

#include <SingleLinkedList.hpp>

// ---------- In different scope (ds) ---------- //

void addAtIndex_ds_rvalue_primitive(void) {
  SingleLinkedList<int> list;

  {
    list.addAtIndex(0, 1);
  }
  TEST_ASSERT_EQUAL_INT(1, list[0]);
  TEST_ASSERT_EQUAL_INT(1, list.getSize());

  {
    list.addAtIndex(1, 2);
  }
  TEST_ASSERT_EQUAL_INT(1, list[0]);
  TEST_ASSERT_EQUAL_INT(2, list[1]);
  TEST_ASSERT_EQUAL_INT(2, list.getSize());

  {
    list.addAtIndex(1, 3);
  }
  TEST_ASSERT_EQUAL_INT(1, list[0]);
  TEST_ASSERT_EQUAL_INT(3, list[1]);
  TEST_ASSERT_EQUAL_INT(2, list[2]);
  TEST_ASSERT_EQUAL_INT(3, list.getSize());
}

void addAtIndex_ds_lvalue_primitive(void) {
  SingleLinkedList<int> list;

  {
    int a = 1;
    list.addAtIndex(0, a);

    TEST_ASSERT_EQUAL_INT(1, a);
    a = 2;
  }
  TEST_ASSERT_EQUAL_INT(1, list[0]);
  TEST_ASSERT_EQUAL_INT(1, list.getSize());

  {
    int b = 2;
    list.addAtIndex(1, b);

    TEST_ASSERT_EQUAL_INT(2, b);
    b = 3;
  }
  TEST_ASSERT_EQUAL_INT(1, list[0]);
  TEST_ASSERT_EQUAL_INT(2, list[1]);
  TEST_ASSERT_EQUAL_INT(2, list.getSize());

  {
    int c = 3;
    list.addAtIndex(1, c);

    TEST_ASSERT_EQUAL_INT(3, c);
    c = 3;
  }
  TEST_ASSERT_EQUAL_INT(1, list[0]);
  TEST_ASSERT_EQUAL_INT(3, list[1]);
  TEST_ASSERT_EQUAL_INT(2, list[2]);
  TEST_ASSERT_EQUAL_INT(3, list.getSize());
}

void addAtIndex_ds_rvalue_class(void) {
  SingleLinkedList<String> list;

  {
    list.addAtIndex(0, "1");
  }
  TEST_ASSERT_EQUAL_STRING("1", list[0].c_str());
  TEST_ASSERT_EQUAL_INT(1, list.getSize());

  {
    list.addAtIndex(1, "2");
  }
  TEST_ASSERT_EQUAL_STRING("1", list[0].c_str());
  TEST_ASSERT_EQUAL_STRING("2", list[1].c_str());
  TEST_ASSERT_EQUAL_INT(2, list.getSize());

  {
    list.addAtIndex(1, "3");
  }
  TEST_ASSERT_EQUAL_STRING("1", list[0].c_str());
  TEST_ASSERT_EQUAL_STRING("3", list[1].c_str());
  TEST_ASSERT_EQUAL_STRING("2", list[2].c_str());
  TEST_ASSERT_EQUAL_INT(3, list.getSize());
}

void addAtIndex_ds_lvalue_class(void) {
  SingleLinkedList<String> list;

  {
    String a = "1";
    list.addAtIndex(0, a);

    TEST_ASSERT_EQUAL_STRING("1", a.c_str());
    a = "2";
  }
  TEST_ASSERT_EQUAL_STRING("1", list[0].c_str());
  TEST_ASSERT_EQUAL_INT(1, list.getSize());

  {
    String b = "2";
    list.addAtIndex(1, b);

    TEST_ASSERT_EQUAL_STRING("2", b.c_str());
    b = "3";
  }
  TEST_ASSERT_EQUAL_STRING("1", list[0].c_str());
  TEST_ASSERT_EQUAL_STRING("2", list[1].c_str());
  TEST_ASSERT_EQUAL_INT(2, list.getSize());

  {
    String c = "3";
    list.addAtIndex(1, c);

    TEST_ASSERT_EQUAL_STRING("3", c.c_str());
    c = "4";
  }
  TEST_ASSERT_EQUAL_STRING("1", list[0].c_str());
  TEST_ASSERT_EQUAL_STRING("3", list[1].c_str());
  TEST_ASSERT_EQUAL_STRING("2", list[2].c_str());
  TEST_ASSERT_EQUAL_INT(3, list.getSize());
}

// ---------- In same scope (ss) ---------- //

void addAtIndex_ss_rvalue_primitive(void) {
  SingleLinkedList<int> list;

  list.addAtIndex(0, 1);
  TEST_ASSERT_EQUAL_INT(1, list[0]);
  TEST_ASSERT_EQUAL_INT(1, list.getSize());

  list.addAtIndex(1, 2);
  TEST_ASSERT_EQUAL_INT(1, list[0]);
  TEST_ASSERT_EQUAL_INT(2, list[1]);
  TEST_ASSERT_EQUAL_INT(2, list.getSize());

  list.addAtIndex(1, 3);
  TEST_ASSERT_EQUAL_INT(1, list[0]);
  TEST_ASSERT_EQUAL_INT(3, list[1]);
  TEST_ASSERT_EQUAL_INT(2, list[2]);
  TEST_ASSERT_EQUAL_INT(3, list.getSize());
}

void addAtIndex_ss_lvalue_primitive(void) {
  SingleLinkedList<int> list;

  int a = 1, b = 2, c = 3;

  list.addAtIndex(0, a);

  TEST_ASSERT_EQUAL_INT(1, a);
  a = 2;
  TEST_ASSERT_EQUAL_INT(1, list[0]);
  TEST_ASSERT_EQUAL_INT(1, list.getSize());

  list.addAtIndex(1, b);

  TEST_ASSERT_EQUAL_INT(2, b);
  b = 3;
  TEST_ASSERT_EQUAL_INT(1, list[0]);
  TEST_ASSERT_EQUAL_INT(2, list[1]);
  TEST_ASSERT_EQUAL_INT(2, list.getSize());

  list.addAtIndex(1, c);

  TEST_ASSERT_EQUAL_INT(3, c);
  c = 4;
  TEST_ASSERT_EQUAL_INT(1, list[0]);
  TEST_ASSERT_EQUAL_INT(3, list[1]);
  TEST_ASSERT_EQUAL_INT(2, list[2]);
  TEST_ASSERT_EQUAL_INT(3, list.getSize());
}

void addAtIndex_ss_rvalue_class(void) {
  SingleLinkedList<String> list;

  list.addAtIndex(0, "1");
  TEST_ASSERT_EQUAL_STRING("1", list[0].c_str());
  TEST_ASSERT_EQUAL_INT(1, list.getSize());

  list.addAtIndex(1, "2");
  TEST_ASSERT_EQUAL_STRING("1", list[0].c_str());
  TEST_ASSERT_EQUAL_STRING("2", list[1].c_str());
  TEST_ASSERT_EQUAL_INT(2, list.getSize());

  list.addAtIndex(1, "3");
  TEST_ASSERT_EQUAL_STRING("1", list[0].c_str());
  TEST_ASSERT_EQUAL_STRING("3", list[1].c_str());
  TEST_ASSERT_EQUAL_STRING("2", list[2].c_str());
  TEST_ASSERT_EQUAL_INT(3, list.getSize());
}

void addAtIndex_ss_lvalue_class(void) {
  SingleLinkedList<String> list;

  String a = "1", b = "2", c = "3";

  list.addAtIndex(0, a);

  TEST_ASSERT_EQUAL_STRING("1", a.c_str());
  a = "2";
  TEST_ASSERT_EQUAL_STRING("1", list[0].c_str());
  TEST_ASSERT_EQUAL_INT(1, list.getSize());

  list.addAtIndex(1, b);

  TEST_ASSERT_EQUAL_STRING("2", b.c_str());
  b = "3";
  TEST_ASSERT_EQUAL_STRING("1", list[0].c_str());
  TEST_ASSERT_EQUAL_STRING("2", list[1].c_str());
  TEST_ASSERT_EQUAL_INT(2, list.getSize());

  list.addAtIndex(1, c);

  TEST_ASSERT_EQUAL_STRING("3", c.c_str());
  c = "4";
  TEST_ASSERT_EQUAL_STRING("1", list[0].c_str());
  TEST_ASSERT_EQUAL_STRING("3", list[1].c_str());
  TEST_ASSERT_EQUAL_STRING("2", list[2].c_str());
  TEST_ASSERT_EQUAL_INT(3, list.getSize());
}

void setup() {
  UNITY_BEGIN();

  // different scope tests
  RUN_TEST(addAtIndex_ds_rvalue_primitive);
  RUN_TEST(addAtIndex_ds_lvalue_primitive);
  RUN_TEST(addAtIndex_ds_rvalue_class);
  RUN_TEST(addAtIndex_ds_lvalue_class);

  // same scope tests
  RUN_TEST(addAtIndex_ss_rvalue_primitive);
  RUN_TEST(addAtIndex_ss_lvalue_primitive);
  RUN_TEST(addAtIndex_ss_rvalue_class);
  RUN_TEST(addAtIndex_ss_lvalue_class);

  UNITY_END();
}

void loop() {
}
