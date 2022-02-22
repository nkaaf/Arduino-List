/*!
 * @file AbstractList.hpp
 *
 * This file is part of the List library. It extends the arduino ecosystem with
 * easy-to-use list implementations. They are specially designed and optimized
 * for different purposes.
 *
 * Copyright (C) 2021  Niklas Kaaf
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
#include <string.h>

/*!
 * @brief   Abstract class from which all lists can be derived.
 *
 * @tparam T    Data Type of entries, that should be stored in the list.
 */
template <typename T> class AbstractList {
private:
  int size = 0;             /// Size of the list.
  bool mutableList = false; /// Is the list mutable or immutable.

protected:
  /// Sometimes it is allowed, that index == this->getSize() to insert it behind
  /// the last entry
#define extendedIsIndexOutOfBounds(index)                                      \
  ((index) != this->getSize() && this->isIndexOutOfBounds(index))

  /// Create a final Value from the given Value
#define createFinalValue(value, finalValue, T)                                 \
  finalValue = (T *)malloc(sizeof(T));                                         \
  memcpy(finalValue, &(value), sizeof(T));

  /**
   * Class representing an abstract entry in the list.
   */
  class AbstractEntry {
  private:
    T *value = nullptr; /// Pointer to the value.

  public:
    /*!
     * @brief   Constructor of an AbstractEntry Object.
     *
     * @param value Value of the entry.
     */
    explicit AbstractEntry(T *value) : value(value) {}

    /*!
     * @brief   Free the memory of the value to prevent memory leaks.
     */
    void freeValue() { free(value); }

    /*!
     * @brief   Get the value of the entry.
     *
     * @return  Pointer to the value of the entry.
     */
    T *getValue() { return value; };
  };

  /*!
   * @brief Constructor of an AbstractList Object.
   *
   * @param mutableList true if the list should be mutable; false otherwise.
   */
  explicit AbstractList<T>(bool mutableList) : mutableList(mutableList) {}

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

  /*!
   * @brief Get a pointer to the entry at the given index. If the given index
   *        does not exists, null will be returned.
   * @note  If the list is immutable, the returned pointer has to be free'd with
   *        free() in order to prevent memory leaks.
   *
   * @param index   Index of the element to get.
   * @return    Pointer to the element.
   */
  virtual T *get(int index) = 0;

public:
  /*!
   * @copybrief AbstractList::addLast()
   * @note Alias of addLast().
   * @see   addLast()
   *
   * @param value   Value to add.
   */
  void add(T &value) { addLast(value); }

  /*!
   * @brief Add the value to the list at the given index. The original entry at
   *        this index, and followings, will be placed directly after the new
   *        entry.
   * @note  Use this only if you know what you are doing. Otherwise use add(),
   *        addFirst() or addLast().
   *
   * @param index   Index of the entry, where the value should be added.
   * @param value   Value of the new entry.
   */
  virtual void addAtIndex(int index, T &value) = 0;

  /*!
   * @brief Add all entries from the given list to this list at the given index.
   *        The original entry at this index, and followings, will be placed
   *        directly after the entries of the given list.
   *
   * @param index   Index, at which the list should be added.
   * @param list    List to add.
   */
  void addAll(int index, AbstractList<T> &list) {
    for (int i = 0; i < list.getSize(); i++) {
      T val = list.getValue(i);
      T *finalValue;
      createFinalValue(val, finalValue, T);
      addAtIndex(index++, *finalValue);
      if (!this->isMutable()) {
        free(finalValue);
      }
    }
  }

  /*!
   * @brief Add all entries from the given list at the end of the list.
   * @see   addAll()
   *
   * @param list    Other list to copy from.
   */
  void addAll(AbstractList<T> &list) { addAll(getSize(), list); }

  /*!
   * @brief Add a new entry at the beginning of the list.
   *
   * @param value   Value to add.
   */
  void addFirst(T &value) { addAtIndex(0, value); }

  /*!
   * @brief Add a new entry at the end of the list.
   * @see   add()
   *
   * @param value   Value to add.
   */
  void addLast(T &value) { addAtIndex(getSize(), value); }

  /*!
   * @copydoc AbstractList::get()
   * @note Alias of get().
   * @see get()
   */
  T *getPointer(int index) { return get(index); }

  /*!
   * @brief Get the value at the index.
   * @note  Be safe, that the index exists otherwise the program will crash
   *        here!
   *
   * @param index   Index of element to get.
   * @return    Value.
   */
  T getValue(int index) {
    T *ptr = getPointer(index);
    T val = *ptr;
    if (!isMutable()) {
      free(ptr);
    }
    return val;
  }

  /*!
   * @brief Remove all elements from the List.
   */
  virtual void clear() = 0;

  /*!
   * @brief Remove the entry at the given index.
   *
   * @param index   Index of element to remove.
   */
  virtual void remove(int index) = 0;

  /*!
   * @copybrief AbstractList::clear()
   * @note Alias of clear().
   * @see clear().
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
  bool isEmpty() { return size == 0; }

  /*!
   * @brief Get an array which represent the list.
   * @note  The returned pointer has to be free'd with free() in order to
   *        prevent memory leaks.
   *
   * @return    Array representation of the list or null if the list is empty.
   */
  T *toArray() {
    if (getSize() == 0) {
      return nullptr;
    }

    T *arr = (T *)malloc(getSize() * sizeof(T));

    for (int i = 0; i < getSize(); ++i) {
      arr[i] = getValue(i);
    }

    return arr;
  }

  /*!
   * @brief Compare two lists whether their attributes and entries are equal.
   * @note  If you use this list for non-primitive data types, check if the
   *        data type implements the != operator!
   *
   * @param list    Second list to compare.
   * @return    true if the lists are equal; false otherwise.
   */
  bool equals(AbstractList<T> &list) {
    if (list.isMutable() != isMutable()) {
      return false;
    }

    if (list.getSize() != getSize()) {
      return false;
    }

    for (int i = 0; i < getSize(); i++) {
      if (list.getValue(i) != getValue(i)) {
        return false;
      }
    }
    return true;
  }

  /*!
   * @copydoc AbstractList::getValue()
   * @see   getValue()
   */
  T operator[](int index) { return getValue(index); }

  /*!
   * @copydoc AbstractList::equals()
   * @see   equals()
   */
  bool operator==(AbstractList<T> &list) { return equals(list); }

  /*!
   * @copydoc AbstractList::add()
   * @see add()
   */
  void operator+(T &value) { this->add(value); }

  /*!
   * @copydoc AbstractList::addAll(AbstractList<T>&)
   * @see addAll(AbstractList<T>&)
   */
  void operator+(AbstractList<T> &list) { this->addAll(list); }
};

#endif // LIST_ABSTRACT_LIST_HPP
