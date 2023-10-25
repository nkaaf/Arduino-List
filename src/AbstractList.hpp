/*!
 * @file AbstractList.hpp
 *
 * This file is part of the List library. It extends the arduino ecosystem with
 * easy-to-use list implementations. They are specially designed and optimized
 * for different purposes.
 *
 * Copyright (C) 2021-2023  Niklas Kaaf
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
 * USA
 */

#ifndef LIST_ABSTRACT_LIST_HPP
#define LIST_ABSTRACT_LIST_HPP

#include <stdlib.h>

// TODO: update keywords

/*!
 * @brief   Abstract class from which all lists can be derived.
 *
 * @tparam T    Data Type of entries, that should be stored in the list.
 */
template<typename T>
class AbstractList {
 private:
  size_t size = 0;    /// Size of the list.
  bool mutableList = false;    /// Is the list mutable or immutable.

 protected:
  /// Sometimes it is allowed, that index == this->getSize() to insert it behind
  /// the last entry
#define extendedIsIndexOutOfBounds(index)                                      \
  ((index) != this->getSize() && this->isIndexOutOfBounds(index))

  /**
   * Class representing an abstract entry in the list.
   */
  class AbstractEntry {
   private:
    T value; /// The raw value.

   public:
    /*!
     * @brief   Get a reference to the value.
     *
     * @return  Pointer to the value of the entry.
     */
    T *getValue() { return &value; };

    /*!
     * @brief   Set the value for the entry.
     *
     * @param val   Reference to the value.
     */
    void setValue(T &val) {
      value = val;
    }
  };

  /*!
   * @brief Constructor of an AbstractList Object.
   *
   * @param mutableList true if the list should be mutable; false otherwise.
   */
  explicit AbstractList<T>(bool mutableList) : mutableList(mutableList) {}

  /*!
   * @brief Get a pointer to the element, stored at specific index-
   *
   * @param index The index of the element to retrieve.
   * @return The nullptr, if the index is out of bounds, otherwise the address of the element.
   *
   * @note  This is independent from their mutability. It will always return the correct address (pointer) to the element.
   */
  virtual T *getPointer(int index) = 0;

  /*!
   * @brief Increase the size of the list by one. Should only be called after an
   *        insertion!
   */
  void increaseSize() { size++; }

  /*!
   * @brief Decrease the size of the list by one. Should only be called after an
   *        deletion!
   */
  void decreaseSize() { size--; }

  /*!
   * @brief Reset the size to zero.
   */
  void resetSize() { size = 0; }

  /*!
   * @brief Method to verify if the given index is out of the range of the list
   *        size.
   *
   * @param index   Index to check.
   * @return    true if the given index is in the range of the list; false
   *            otherwise
   */
  bool isIndexOutOfBounds(int index) { return index < 0 || index >= getSize(); }

 public:
  /*!
   * @copybrief AbstractList::addLast()
   * @note Alias of addLast().
   * @see addLast()
   */
  void add(T &value) { addLast(value); }

#if __cplusplus >= 201103L || defined(__GXX_EXPERIMENTAL_CXX0X__)
  /*!
   * @copydoc AbstractList::add()
   */
  void add(T &&value) { addLast(value); }
#endif

  /*!
   * @brief Add the value to the list at the given index. The original entry at
   *        this index, and followings, will be placed directly after the new
   *        entry.
   * @note  Allowed indices are 0 to getSize(). If the index is out of bounds, nothing will happen.
   *
   * @param index   Index of the entry, where the value should be added.
   * @param value   Value of the new entry.
   */
  virtual void addAtIndex(int index, T &value) = 0;

#if __cplusplus >= 201103L || defined(__GXX_EXPERIMENTAL_CXX0X__)
  /*!
   * @copydoc AbstractList::addAtIndex()
   */
  virtual void addAtIndex(int index, T &&value) {
    addAtIndex(index, value);
  }
#endif

  /*!
   * @brief Add all entries from the given list to this list at the given index.
   *        The original entry at this index, and followings, will be placed
   *        directly after the entries of the given list.
   *  @note The elements from the other list, remain untouched.
   *
   * @param index   Index of this list, at which all entries should be added.
   * @param list    Other list from where to copy the entries.
   */
  void addAll(int index, AbstractList<T> &list) {
    for (int i = 0; i < list.getSize(); i++) {
      addAtIndex(index++, list.get(i));
    }
  }

  /*!
   * @brief Add all entries from the given list at the end of the list.
   *  @note The elements from the other list, remain untouched.
   *
   * @param list    Other list to copy from.
   */
  void addAll(AbstractList<T> &list) { addAll(getSize(), list); }

  /*!
   * @brief Add all entries from the given array.
   *  @note The elements from the other list, remain untouched.
   *
   * @param arr Array.
   * @param size  Size of array.
   */
  void addAll(T *arr, size_t arrSize) {
    for (size_t i = 0; i < arrSize; ++i) {
      add(arr[i]);
    }
  }

  /*!
   * @brief Add a new entry at the beginning of the list.
   *
   * @param value   Value to add.
   */
  void addFirst(T &value) { addAtIndex(0, value); }

#if __cplusplus >= 201103L || defined(__GXX_EXPERIMENTAL_CXX0X__)
  /*!
    * @copydoc AbstractList::addFirst()
    */
  void addFirst(T &&value) { addAtIndex(0, value); }
#endif

  /*!
   * @brief Add a new entry at the end of the list.
   *
   * @param value   Value to add.
   */
  void addLast(T &value) { addAtIndex(getSize(), value); }

#if __cplusplus >= 201103L || defined(__GXX_EXPERIMENTAL_CXX0X__)
  /*!
   * @copydoc AbstractList::addLast()
   */
  void addLast(T &&value) { addAtIndex(getSize(), value); }
#endif

  /*!
   * @brief Get the raw value at a specified index.
   *
   * @note Allowed indices are 0 to getSize() - 1. If the index is out of bounds, undefined behaviour will happen. Please ne sure, that the index is valid!
   * @note This will method will always return an immutable object. If you want to get the mutable object from your mutable list, plese use getMutableValue().
   *
   * @param index   Index of the element to get.
   * @return    Immutable object.
   */
  T get(int index) {
    return *this->getPointer(index);
  }

  /*!
   * @brief Get the pointer to the mutable object at a specified index.
   *
   * @note Allowed indices are 0 to getSize() -1. If the index is out of bounds, a nullptr will be returned.
   * @note This method will only return a valid object for a mutable list. A immutable list will return always the nullptr.
   *
   * @param index Index of teh element to get.
   * @return Mutable object, or nullptr if the index is out of bounds or the list is immutable.
   */
  T *getMutableValue(int index) {
    if (!this->isMutable()) {
      return nullptr;
    }

    return this->getPointer(index);
  }

  /*!
   * @brief Remove all elements from the List.
   */
  virtual void clear() = 0;

  /*!
   * @brief Remove the entry at the given index.
   *
   * @note Allowed indices are 0 to getSize() - 1. If the index is out of bounds, nothing will happen.
   *
   * @param index   Index of element to remove.
   */
  virtual void remove(int index) = 0;

  /*!
   * @brief Remove the first entry from the list.
   */
  virtual void removeFirst() { remove(0); }

  /*!
   * @brief Remove the las entry from the list.
   */
  virtual void removeLast() { remove(getSize() - 1); }

  /*!
   * @copybrief AbstractList::clear()
   * @note Alias of clear().
   * @see clear()
   */
  void removeAll() { clear(); }

  /*!
   * @brief Get the number how many elements are saved in the list.
   *
   * @return    Size of the list.
   */
  int getSize() { return size; }

  /*!
   * @brief Check if the list is mutable.
   *
   * @return    true if the list is mutable; false otherwise.
   */
  bool isMutable() { return mutableList; }

  /*!
   * @brief Check if the list is empty.
   *
   * @return    true if the list is empty; false otherwise
   */
  bool isEmpty() { return getSize() == 0; }

  /*!
   * @brief Get an array which represent the list.
   *
   * @note If this list is empty, a nullptr will be returned.
   * @note The memory for the array is dynamically allocated. the returned pointer has to be free'd with free() in order to
   *        prevent memory leaks. For further processing of the array, e.g. inserting new elements, the other method toArray(T* arr) is preferred!
   * @note The array contains always immutable representations of the elements, saved in the list.
   *
   * @return    Array representation of the list or nullptr if the list is empty.
   */
  T *toArray() {
    if (getSize() == 0) {
      return nullptr;
    }

    T *arr = static_cast<T *>(malloc(getSize() * sizeof(T)));
    this->toArray(arr);

    return arr;
  }

  /*!
   * @brief Fill the passed array with immutable objects.
   *
   * @note The array contains always immutable representations of the elements, saved in the list.
   * @note Be sure, that the array has enough free space for all elements of the list.
   *
   * @param arr Array to fill.
   */
  void toArray(T *arr) {
    if (getSize() == 0) {
      return arr;
    }

    for (int i = 0; i < getSize(); i++) {
      arr[i] = get(i);
    }
  }

/*!
 * @brief Create the list from given array.
 * @note Removes all entries in current list.
 *
 * @param arr     Array
 * @param arrSize Size of Array
 */
  void fromArray(T *arr, size_t arrSize) {
    this->clear();
    addAll(arr, arrSize);
  }

/*!
 * @brief Sort the entries in the list with Quicksort.
 *
 * @param compFunc Comparator Method
 */
  void sort(int (*compFunc)(const void *, const void *)) {
    T *arr = this->toArray();

    qsort(arr, getSize(), sizeof(*arr), compFunc);

    this->fromArray(arr, getSize());
    free(arr);
  }

/*!
 * @brief Compare two lists whether their attributes and entries are equal.
 * @note  If you use this list for non-primitive data types, check if the
 *        data type implements the != operator!
 *
 * @param other    Second list to compare.
 * @return    true if the lists are equal; false otherwise.
 */
  bool equals(AbstractList<T> &other) {
    if (other.isMutable() != this->isMutable()) {
      return false;
    }

    if (other.getSize() != this->getSize()) {
      return false;
    }

    for (int i = 0; i < getSize(); i++) {
      if (this->isMutable()) {
        if (other.getMutableValue(i) != this->getMutableValue(i)) {
          return false;
        }
      } else {
        if (other.get(i) != this->get(i)) {
          return false;
        }
      }
    }
    return true;
  }

  /*!
   * @copydoc AbstractList::get()
   * @see   get()
   */
  T operator[](int index) { return get(index); }

  /*!
   * @copydoc AbstractList::equals()
   * @see   equals()
   */
  bool operator==(AbstractList<T> &other) { return equals(other); }

  /*!
   * @brief Opposite of '=='
   * @see equals()
   *
   * @param other Other list to compare
   * @return    true if the lists are not equal; false otherwise.
   */
  bool operator!=(AbstractList<T> &other) { return !this->equals(other); }

  /*!
   * @copydoc AbstractList::add()
   * @see add()
   */
  void operator+(T &value) { this->add(value); }

#if __cplusplus >= 201103L || defined(__GXX_EXPERIMENTAL_CXX0X__)
  /*!
     * @copydoc AbstractList::add()
     * @see add()
     */
  void operator+(T &&value) { this->add(value); }
#endif

  /*!
   * @copydoc AbstractList::addAll(AbstractList<T>&)
   * @see addAll(AbstractList<T>&)
   */
  void operator+(AbstractList<T> &list) { this->addAll(list); }
};

#endif // LIST_ABSTRACT_LIST_HPP
