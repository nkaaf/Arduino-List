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

/*!
 * @brief   Abstract class from which all lists can be derived.
 *
 * @tparam T    Data Type of entries, that should be stored in the list.
 */
template <typename T> class AbstractList {
private:
  int size = 0;            /// Size of the list
  bool mutableList = true; /// Is the list mutable or immutable

protected:
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
  void increaseSize() { this->size++; }

  /*!
   * @brief Decrease the size of the list by one. Should only be called after an
   *        deletion!
   */
  void decreaseSize() { this->size--; }

  /*!
   * @brief Method to verify if the given index is out of the range of the list
   *        size.
   *
   * @param index   Index to check.
   * @return    true if the given index is in the range of the list; false
   *            otherwise
   */
  bool isIndexOutOfBounds(int index) {
    return index < 0 || index >= this->getSize();
  }

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
   * @brief Remove the entry at the given index.
   *
   * @param index   Index of element to remove.
   */
  virtual void remove(int index) = 0;

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
    if (!this->isMutable()) {
      free(ptr);
    }
    return val;
  }

  /*!
   * @brief Get a pointer to the entry at the given index. If the given index
   *        does not exists, null will be returned.
   * @note  If the list is immutable, the returned pointer has to be free'd with
   *        free() in order to prevent memory leaks.
   *
   * @param index   Index of element to get.
   * @return    Pointer to the element.
   */
  T *getPointer(int index) { return get(index); }

  /*!
   * @brief Add a new entry at the end of the list.
   * @see   add()
   *
   * @param value   Value to add.
   */
  void addLast(T &value) { this->addAtIndex(this->getSize(), value); }

  /*!
   * @brief Add a new entry at the beginning of the list.
   *
   * @param value   Value to add.
   */
  void addFirst(T &value) { this->addAtIndex(0, value); }

  /*!
   * @brief Add a new entry at the end of the list.
   * @see   addLast()
   *
   * @param value   Value to add.
   */
  void add(T &value) { this->addLast(value); }

  /*!
   * @brief Add all entries from the given list at the end of the list.
   * @see   addLast()
   *
   * @param list    Other list to copy from.
   */
  void addAll(AbstractList<T> &list) { this->addAll(this->getSize(), list); }

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
      T *finalValue = (T *)malloc(sizeof(T));
      memcpy(finalValue, &val, sizeof(T));
      this->addAtIndex(index++, *finalValue);
      if (!this->isMutable()) {
        free(finalValue);
      }
    }
  }

  /*!
   * @brief Get an array which represent the list.
   * @note  The returned pointer has to be free'd with free() in order to
   *        prevent memory leaks.
   *
   * @return    Array representation of the list or null if the list is empty.
   */
  T *toArray() {
    if (this->getSize() == 0) {
      return nullptr;
    }

    T *arr = (T *)malloc(this->getSize() * sizeof(T));

    for (int i = 0; i < this->getSize(); ++i) {
      arr[i] = this->getValue(i);
    }

    return arr;
  }

  /*!
   * @brief Get the number how many elements are saved in the list.
   *
   * @return    Size of the list.
   */
  int getSize() { return this->size; }

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
  bool isEmpty() { return this->size == 0; }

  /*!
   * @brief Compare two lists whether their attributes and entries are equal.
   * @note  If you use this list for non-primitive data types, check if the
   *        data type implements the != operator!
   *
   * @param list    Second list to compare.
   * @return    true if the lists are equal; false otherwise.
   */
  bool equals(AbstractList<T> &list) {
    if (list.isMutable() != this->isMutable()) {
      return false;
    }

    if (list.getSize() != this->getSize()) {
      return false;
    }

    for (int i = 0; i < this->getSize(); i++) {
      if (list.getValue(i) != this->getValue(i)) {
        return false;
      }
    }
    return true;
  }

  /*!
   * @brief Get the value of the element at the index.
   * @see   getValue()
   *
   * @param index   Index of the element to get.
   * @return    Value of the element.
   */
  T operator[](int index) { return getValue(index); }

  /*!
   * @brief Compare two lists whether their attributes and entries are equal.
   * @see   equals()
   *
   * @param list    Second list to compare.
   * @return    true if the lists are equal; false otherwise.
   */
  bool operator==(AbstractList<T> &list) { return equals(list); }

  /*!
   * @brief Add a new entry at the end of the list.
   * @see   add()
   * @see   addLast()
   *
   * @param value   Value to add.
   */
  void operator+(T &value) { this->addLast(value); }

  /*!
   * @brief Add all entries from the given list at the end of the list.
   * @see   addAll()
   *
   * @param list    Other list to copy from.
   */
  void operator+(AbstractList<T> &list) { this->addAll(list); }
};

#endif /* LIST_ABSTRACT_LIST_HPP */
