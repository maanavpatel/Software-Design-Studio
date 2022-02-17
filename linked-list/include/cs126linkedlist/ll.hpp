// Copyright (c) 2020 CS126SP20. All rights reserved.

#include <cassert>
#include <utility>
#include <vector>

#include "ll.h"

// TODO(you): Implement these methods.

namespace cs126linkedlist {

template <typename ElementType>
LinkedList<ElementType>::LinkedList() {
  head = nullptr;
  tail = nullptr;
}

template <typename ElementType>
LinkedList<ElementType>::LinkedList(const std::vector<ElementType>& values) {
  head = nullptr;
  tail = nullptr;
  for (ElementType data : values) {
    this->push_back(data);
  }
}

// Copy constructor
template <typename ElementType>
LinkedList<ElementType>::LinkedList(const LinkedList<ElementType>& source) {
  head = nullptr;
  tail = nullptr;
  list_size = 0;
  for (auto iter = source.begin(); iter != source.end(); ++iter) {
    push_back(*iter);
  }
}

// Move constructor
template <typename ElementType>
LinkedList<ElementType>::LinkedList(LinkedList<ElementType>&& source) noexcept {
  head = source.head;
  tail = source.tail;
  list_size = source.list_size;
  source.head = nullptr;
  source.tail = nullptr;
  source.list_size = 0;
}

// Destructor
template <typename ElementType>
LinkedList<ElementType>::~LinkedList() {
  clear();
}

// Copy assignment operator
template <typename ElementType>
LinkedList<ElementType>& LinkedList<ElementType>::operator=(
    const LinkedList<ElementType>& source) {
  head = nullptr;
  tail = nullptr;
  list_size = 0;
  for (auto iter = source.begin(); iter != source.end(); ++iter) {
    push_back(*iter);
  }
  return *this;
}

// Move assignment operator
template <typename ElementType>
LinkedList<ElementType>& LinkedList<ElementType>::operator=(
    LinkedList<ElementType>&& source) noexcept {
  head = source.head;
  tail = source.tail;
  list_size = source.list_size;
  source.head = nullptr;
  source.tail = nullptr;
  source.list_size = 0;
}

template <typename ElementType>
void LinkedList<ElementType>::push_front(const ElementType& value) {
  // make a new node
  Node* temp = new Node;
  // set the value
  temp->data = value;
  if (empty()) {
    tail = temp;
  }
  temp->next = head;
  head = temp;
  ++list_size;
}

template <typename ElementType>
void LinkedList<ElementType>::push_back(const ElementType& value) {
  Node* temp = new Node;
  temp->next = nullptr;
  temp->data = value;
  if (empty()) {
    tail = temp;
    head = temp;
  } else {
    tail->next = temp;
    tail = temp;
  }
  ++list_size;
}

template <typename ElementType>
ElementType LinkedList<ElementType>::front() const {
  return head->data;
}

template <typename ElementType>
ElementType LinkedList<ElementType>::back() const {
  return tail->data;
}

template <typename ElementType>
void LinkedList<ElementType>::pop_front() {
  if (!empty()) {
    Node* to_remove;
    to_remove = head;
    // redirect head to point to next item
    head = head->next;
    delete to_remove;
    --list_size;
    if (list_size == 0) {
      tail = nullptr;
    }
  }
}

template <typename ElementType>
void LinkedList<ElementType>::pop_back() {
  if (!empty()) {
    Node* toRem = head;
    Node* before_rem = nullptr;
    // start at the head and find the Node before the tail
    while (toRem->next != nullptr) {  // stops when curr is tail
      before_rem = toRem;
      toRem = toRem->next;
    }
    tail = before_rem;
    if (before_rem != nullptr) {
      before_rem->next = nullptr;
    }
    delete toRem;
    --list_size;
    if (list_size == 0) {
      head = nullptr;
    }
  }
}

template <typename ElementType>
int LinkedList<ElementType>::size() const {
  return list_size;
}

template <typename ElementType>
bool LinkedList<ElementType>::empty() const {
  return head == nullptr && tail == nullptr && list_size == 0;
}

template <typename ElementType>
void LinkedList<ElementType>::clear() {
  Node* toRem = head;
  while (toRem != nullptr) {
    Node* nextNode = toRem->next;
    delete toRem;
    --list_size;
    toRem = nextNode;
  }
  head = nullptr;
  tail = nullptr;
}

template <typename ElementType>
std::ostream& operator<<(std::ostream& os,
                         const LinkedList<ElementType>& list) {
  size_t count = 0;
  for (auto list_iter = list.begin(); list_iter != list.end(); ++list_iter) {
    if (count == list.size() - 1) {
      os << *list_iter;
    } else {
      os << *list_iter << ", ";
    }
    count++;
  }
  return os;
}

template <typename ElementType>
void LinkedList<ElementType>::RemoveNth(int n) {
  if (n < 0 || n >= list_size) {  // out of bounds
    return;
  }
  if (n == list_size - 1) {
    pop_front();
  } else if (n == 0) {
    pop_back();
  } else {
    Node* curr = head;
    Node* prev = nullptr;
    for (size_t i = 0; i < n; i++) {
      prev = curr;
      curr = curr->next;
    }
    if (prev != nullptr) {
      prev->next = curr->next;
      delete curr;
      --list_size;
    }
  }
}

template <typename ElementType>
void LinkedList<ElementType>::RemoveOdd() {
  if (head == nullptr || head->next == nullptr) {
    return;
  }
  // Initialize prev and node to be deleted
  Node* prev = head;
  Node* toRem = prev->next;
  while (prev != nullptr && toRem != nullptr) {
    prev->next = toRem->next;
    delete toRem;
    // Update prev and node
    prev = toRem->next;
    if (prev != nullptr) {
      toRem = prev->next;
    }
    --list_size;
  }
}

template <typename ElementType>
bool LinkedList<ElementType>::operator==(
    const LinkedList<ElementType>& rhs) const {
  if (list_size == rhs.size()) {  // size is equal
    auto r_itr = rhs.begin();
    for (auto itr = begin(); itr != end(); ++itr) {
      if (*itr != *r_itr) {  // two elements are not equal
        // lists are not equal so return true
        return false;
      }
      ++r_itr;
    }
    // size was same and all elements were same
    return true;
  }
  // size was not same
  return false;
}

template <typename ElementType>
bool operator!=(const LinkedList<ElementType>& lhs,
                const LinkedList<ElementType>& rhs) {
  if (lhs.size() == rhs.size()) {  // size is equal
    auto r_itr = rhs.begin();
    for (auto l_itr = lhs.begin(); l_itr != lhs.end(); ++l_itr) {
      if (*l_itr != *r_itr) {  // two elements are not equal
        // lists are not equal so return true
        return true;
      }
      ++r_itr;
    }
    // size was same and all elements were same
    return false;
  }
  // size was not same
  return true;
}
/**
 * ? QuEsTiOns ?
 * Off by one problem
 * Const_iterator vs iterator (any difference in implementation?)
 * Comparing iterators (is the way I have valid?)
 *
 */
/*
 * iterator
 */
template <typename ElementType>
typename LinkedList<ElementType>::iterator&
LinkedList<ElementType>::iterator::operator++() {
  current_ = current_->next;
  return *this;
}

template <typename ElementType>
ElementType& LinkedList<ElementType>::iterator::operator*() const {
  return current_->data;
}

template <typename ElementType>
bool LinkedList<ElementType>::iterator::operator!=(
    const LinkedList<ElementType>::iterator& other) const {
  return this->current_ != other.current_;
}

template <typename ElementType>
typename LinkedList<ElementType>::iterator LinkedList<ElementType>::begin() {
  return iterator(head);
}

template <typename ElementType>
typename LinkedList<ElementType>::iterator LinkedList<ElementType>::end() {
  if (tail == nullptr) {
    return iterator(tail);
  }
  return iterator(tail->next);
}

/*
 * const_iterator
 */
template <typename ElementType>
typename LinkedList<ElementType>::const_iterator&
LinkedList<ElementType>::const_iterator::operator++() {
  current_ = current_->next;
  return *this;
}

template <typename ElementType>
const ElementType& LinkedList<ElementType>::const_iterator::operator*() const {
  return current_->data;
}

template <typename ElementType>
bool LinkedList<ElementType>::const_iterator::operator!=(
    const LinkedList<ElementType>::const_iterator& other) const {
  return this->current_ != other.current_;
}

template <typename ElementType>
typename LinkedList<ElementType>::const_iterator
LinkedList<ElementType>::begin() const {
  return const_iterator(head);
}

template <typename ElementType>
typename LinkedList<ElementType>::const_iterator LinkedList<ElementType>::end()
    const {
  if (tail == nullptr) {
    return const_iterator(tail);
  }
  return const_iterator(tail->next);
}

}  // namespace cs126linkedlist
