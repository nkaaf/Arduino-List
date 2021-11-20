/*!
 * @file SingleLinkedList.hpp
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

#ifndef LIST_SINGLE_LINKED_LIST_HPP
#define LIST_SINGLE_LINKED_LIST_HPP

#include <stdlib.h>
#include <string.h>

#include "AbstractList.hpp"

/*!
 * @brief   Implementation of a single-linked list
 *
 * @tparam T    Data Type of entries, that should be stored in the list.
 */
template <typename T> class SingleLinkedList : public AbstractList<T> {
private:
  /*!
   * @brief Class representing one entry of the list.
   */
  class Entry {
  private:
    T *value = nullptr;    /// Pointer to the value
    Entry *next = nullptr; /// Pointer to the next element of the list

  public:
    /*!
     * @brief   Constructor of an Entry Object.
     *
     * @param value Value of the entry.
     */
    explicit Entry(T *value) : value(value) {}

    /*!
     * @brief   Destructor of an Entry Object.
     */
    ~Entry() { next = nullptr; }

    /*!
     * @brief   Free the memory of the value to prevent memory leaks.
     */
    void freeValue() { free(value); }

    /*!
     * @brief   Get the value of the entry.
     *
     * @return  Pointer to the value of the entry.
     */
    T *getValue() { return this->value; };

    /*!
     * @brief   Get the next entry of the list.
     *
     * @return  Pointer to the next element.
     */
    Entry *getNext() const { return this->next; };

    /*!
     * @brief   Set the next entry of the list.
     *
     * @param nextEntry Pointer to the next entry.
     */
    void setNext(Entry *nextEntry) { this->next = nextEntry; }
  };

  Entry *head = nullptr; /// The first entry of the list.
  Entry *tail = nullptr; /// The last entry of the list.

public:
  /*!
   * @brief Constructor of a SingleLinkedList Object.
   *
   * @param mutableList true if the list should be mutable (default); false
   *                    otherwise.
   */
  explicit SingleLinkedList<T>(bool mutableList = true)
      : AbstractList<T>(mutableList) {}

  /*!
   * @brief Destructor of a SingleLinkedList Object.
   */
  ~SingleLinkedList() {
    if (this->head != nullptr) {
      Entry *current = this->head;
      Entry *next;
      for (int i = 0; i < this->getSize(); i++) {
        next = current->getNext();

        if (!this->isMutable()) {
          current->freeValue();
        }

        delete current;
        current = next;
      }

      this->head = nullptr;
      this->tail = nullptr;
    }
  }

  void addAtIndex(int index, T &value) override {
    // it is allowed, that index == this->getSize() to insert it behind the last
    // entry
    if (index != this->getSize()) {
      if (this->isIndexOutOfBounds(index)) {
        return;
      }
    }

    Entry *entry;

    if (this->isMutable()) {
      entry = new Entry(&value);
    } else {
      T *finalValue = (T *)malloc(sizeof(T));
      memcpy(finalValue, &value, sizeof(T));
      entry = new Entry(finalValue);
    }

    if (this->getSize() == 0) {
      // Add entry to empty list
      this->head = entry;
      this->tail = entry;
    } else if (index == 0) {
      // Add entry to not empty list but at first position
      entry->setNext(this->head);
      this->head = entry;
    } else if (index == this->getSize()) {
      // Add entry at not empty list but at last position
      this->tail->setNext(entry);
      this->tail = entry;
    } else {
      // Add entry to not empty list, somewhere in the middle
      Entry *current = this->head;
      for (int i = 0; i < index - 1; ++i) {
        current = current->getNext();
      }
      entry->setNext(current->getNext());
      current->setNext(entry);
    }

    this->increaseSize();
  };

  void remove(int index) override {
    if (this->isIndexOutOfBounds(index)) {
      return;
    }

    Entry *current = this->head;
    // current is either the element to delete if index == 0, or the previous
    // element
    if (index != 0) {
      int i = 0;
      while (i < index - 1) {
        current = current->getNext();
        i++;
      }
    }

    if (index == this->getSize() - 1) {
      this->tail = current;
    }

    if (index == 0) {
      this->head = current->getNext();
    }

    // current is always the element to delete
    if (index != 0) {
      current = current->getNext();
    }

    if (!this->isMutable()) {
      current->freeValue();
    }
    delete current;

    this->decreaseSize();

    if (this->getSize() == 0) {
      this->head = nullptr;
      this->tail = nullptr;
    }
  }

  T *get(int index) override {
    if (!this->isMutable() || this->isIndexOutOfBounds(index)) {
      return nullptr;
    }

    Entry *current = this->head;
    int i = 0;
    while (i != index) {
      current = current->getNext();
      i++;
    }

    return (T *)current->getValue();
  }
};

#endif /* LIST_SINGLE_LINKED_LIST_HPP */
