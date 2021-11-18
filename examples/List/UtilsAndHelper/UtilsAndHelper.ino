#include <List.hpp>

// Create a mutable list
List<int> list;

void setup() {
  Serial.begin(9600);

  // Check if list is empty
  Serial.print("Is the List empty? ");
  if (list.isEmpty()) {
    Serial.println("Yes the list is empty");
  } else {
    Serial.println("No the list is not empty");
  }

  // Add the first element to the list
  int setup1 = 25;
  list.add(setup1);
  Serial.println("Inserted the first element");

  // Check another time
  Serial.print("Is the List empty? ");
  if (list.isEmpty()) {
    Serial.println("Yes the list is empty");
  } else {
    Serial.println("No the list is not empty");
  }

  Serial.println();

  // Add another element
  int setup2 = 50;
  list.add(setup2);
  Serial.println("Inserted another element");

  // Convert list to array
  int *array = list.toArray();
  // Print every element from the new array
  Serial.print("The list contains the following values which are get by converting the list to an array: [");
  for (int i = 0; i < list.getSize(); ++i) {
    Serial.print(array[i]);
    if (i != list.getSize() - 1) { // only add the ',' if the element is not the last; otherwise the output would be: [2,2,]; but now it is [2,2]
      Serial.print(",");
    }
  }
  Serial.println("]");

  Serial.println();

  // Compare two lists
  List<int> secondList; // Create second list
  if (list.equals(secondList)) {
    Serial.println("The two lists are identical.");
  } else {
    Serial.println("The two lists aren't identical.");
  }
  Serial.println("Inserting both elements in the second list, that are also in the first list.");
  secondList.add(setup1);
  secondList.add(setup2);

  // Check another time
  if (list == secondList) { // The '==' operator is a synonym for the equals() method.
    Serial.println("The two lists are identical.");
  } else {
    Serial.println("The two lists aren't identical.");
  }

  Serial.println();

  Serial.println("Add two more elements to the second list.");
  int setup3 = 12;
  int setup4 = 41;
  secondList.add(setup3); // add two more values to the second List
  secondList.add(setup4);

  // Add one list to another
  Serial.println("Add all elements of the second list to the first list.");
  list.addAll(secondList);

  // Print every element from the new array
  Serial.print("The list contains the following values which are get by converting the list to an array: [");
  for (int i = 0; i < list.getSize(); ++i) {
    Serial.print(*list[i]);
    if (i != list.getSize() - 1) { // only add the ',' if the element is not the last; otherwise the output would be: [2,2,]; but now it is [2,2]
      Serial.print(",");
    }
  }
  Serial.println("]");
}

void loop() {}