#include <List.hpp>

// Create a mutable list
List<int> list;

void setup() {
  Serial.begin(9600);

  // Add the first element to the list
  int setup1 = 25;
  list.add(setup1); // add() will always place the element at the end of the list. Its synonym is addLast(). addFirst() will place the element directly at the front of the list.
  Serial.println("Inserted the first element");

  Serial.println();

  // Get the first element
  Serial.print("The value of the first element with the get() method and '*' is: ");
  int firstElement = *list.get(0); // Here, have to be the '*' to get the int Value, because otherwise a pointer (memory address) will be get.
  Serial.println(firstElement);

  // Get the first element (alternative)
  Serial.print("The value of the first element with the [] operator is: ");
  firstElement = *list[0]; // The '[]' Operator is a synonym for the get() method.
  Serial.println(firstElement);

  // Get only the value of the first element
  Serial.print("The value of the first element with the getValue() method is: ");
  Serial.println(list.getValue(0)); // The more comfortable way to get only the first elements value is to call the getValue() method. You cannot get the address of the element with the getValue() method!

  Serial.println("As you can see, there are three possible ways to get the value. Choose your favorite one :)");
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
}

void loop() {}