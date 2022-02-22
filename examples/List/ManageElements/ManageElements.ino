#include <List.hpp>

// Create an immutable list
List<int> list;

void setup() {
  Serial.begin(9600);

  // Add the first element to the list
  int setup1 = 25;
  list.add(setup1); // add() will always place the element at the end of the list. Its synonym is addLast(). addFirst() will place the element directly at the front of the list.
  Serial.println("Inserted the first element");

  Serial.println();

  // Get the first element
  Serial.print("The value of the first element with the getValue() method is: ");
  Serial.println(list.getValue(0)); // The most comfortable way to get the first elements value is to call the getValue() method. You cannot get the address of the element with the getValue() method!

  // Get the first element (alternative)
  Serial.print("The value of the first element with the [] operator is: ");
  int firstElement = list[0]; // The '[]' Operator is a synonym for the getValue() method.
  Serial.println(firstElement);

  // Get the first element (alternative)
  Serial.print("The value of the first element with the getPointer() method and '*' is: ");
  int *firstElementPtr = list.getPointer(0); // Here, have to be the '*' to get the int Value, because otherwise a pointer (memory address) will be returned.
  Serial.println(*firstElementPtr);
  free(firstElementPtr); // free the pointer because it is an immutable list

  Serial.println("As you can see, there are three possible ways to get the value. The last way is not for beginners because you have to handle pointers.");
  Serial.println();

  // Get the size of the list
  Serial.print("The list has: ");
  Serial.print(list.getSize());
  Serial.println(" element(s)");

  // Remove element from list
  list.remove(0); // With this, you will remove the first element of the list.
  Serial.print("After the deletion, the list has: ");
  Serial.print(list.getSize());
  Serial.println(" element(s)");

  // Add 10 more elements
  int e = 0;
  for (int i = 0; i < 10; ++i) {
    list.add(e);
  }
  Serial.print("After the insertion, the list has: ");
  Serial.print(list.getSize());
  Serial.println(" element(s)");

  // Clear list
  list.clear();
  Serial.print("After the clear, the list has: ");
  Serial.print(list.getSize());
  Serial.println(" element(s)");
}

void loop() {}