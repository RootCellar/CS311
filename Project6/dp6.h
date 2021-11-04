/*
 * Darian Marvel
 * 11-3-2021
 * Completing Project 6
*/

#ifndef DP6_H
#define DP6_H

#include <utility>
#include <iostream>

#include "llnode2.h"

//Reverses the ordering of an LLNode2 list,
//given a unique_ptr to the head.
//Does not throw
template<typename ValType>
void reverseList(std::unique_ptr<LLNode2<ValType>> & head) {
  //handle lists where size < 2
  if(head == nullptr) return;
  if(head->_next == nullptr) return;

  //setup pointers
  std::unique_ptr<LLNode2<ValType>> prev = std::move(head);
  std::unique_ptr<LLNode2<ValType>> current;
  std::unique_ptr<LLNode2<ValType>> next = std::move(prev->_next);

  //move along the list, moving unique_ptrs around to reverse the direction
  //in which they point
  while( next != nullptr) {
    //move current forward
    current = std::move(next);

    //create a place to go next, so we can actually go there
    //after current->_next is set to point to previous
    if(current->_next != nullptr) next = std::move(current->_next);
    else next = nullptr;

    //make current->_next point to previous,
    //then make current the previous item
    current->_next = std::move(prev);
    prev = std::move(current);
  }

  //set head to the new beginning of the list
  head = std::move(prev);

}

// Requirements on Types:
//  "vtype" or value_type must have a copy constructor
//  "ktype" or key_type must also have a copy constructor
//  both key_type and value_type must have a non-throwing destructor
// Invariants:
//  _data is either a nullptr or points to the valid head of the list
template<typename ktype, typename vtype>
class LLMap {

private:

  using key_type = ktype;
  using value_type = vtype;
  using size_type = std::size_t;

  using pair_type = std::pair<key_type, value_type>;

  std::unique_ptr<LLNode2<pair_type>> _data;

public:

  LLMap(): _data(nullptr) {}

  ~LLMap() = default;

  // Copy ctor
  LLMap(const LLMap<key_type, value_type> & other) = delete;
  // Move ctor
  LLMap(LLMap<key_type, value_type> && other) = delete;
  // Copy assignment operator
  LLMap<key_type, value_type> & operator=(const LLMap<key_type, value_type> & other) = delete;
  // Move assignment operator
  LLMap<key_type, value_type> & operator=(LLMap<key_type, value_type> && other) = delete;


  // Logic Written by Glenn G. Chappell (llnode2.h)
  // No-Throw Guarantee
  size_type size() const {
    if(_data == nullptr) return 0;

    auto p = _data.get();      // Iterates through list
    std::size_t counter = 0;  // Number of nodes so far

    while (p != nullptr)
    {
        p = p->_next.get();
        ++counter;
    }

    return counter;
  }

  // No-Throw Guarantee
  // Exception Neutral
  bool empty() const {
    return _data == nullptr;
  }

  // No-Throw Guarantee
  // Exception Neutral
  const value_type* find(const key_type& key) const {
    if(_data == nullptr) return nullptr;
    auto p = _data.get();

    while(p != nullptr && p->_data.first != key) p = p->_next.get();

    if(p == nullptr) return nullptr;
    else return &(p->_data.second);
  }

  // No-Throw Guarantee
  // Exception Neutral
  value_type* find(const key_type& key) {
    if(_data == nullptr) return nullptr;
    auto p = _data.get();

    while(p != nullptr && p->_data.first != key) p = p->_next.get();

    if(p == nullptr) return nullptr;
    else return &(p->_data.second);
  }

  // Strong Guarantee
  // Exception Neutral
  void insert(const key_type& key, const value_type& value) {
    value_type* data = find(key);

    //if we didn't find it, just put it at the front
    if(data == nullptr) push_front(_data, std::make_pair(key, value));
    //otherwise, just change the data to the new value
    else *data = value;
  }

  // No-Throw Guarantee
  // Exception Neutral
  void erase(const key_type& key) {
    auto p = _data.get();
    auto previous = p;

    //find the node by key, keeping track of the previous node
    while(p != nullptr && p->_data.first != key) {
      previous = p;
      p = p->_next.get();
    }

    //if a node with the given key does not exist, ...
    if(p == nullptr) return;

    //if we are at the front of the list, ...
    if(previous == p) pop_front(_data);
    else {
      //pretend previous->_next is the head of another list for a moment
      //and pop it's head, also making previous->_next point to the new head
      pop_front(previous->_next);
    }


  }

  // Pre:
  //  func is a function that takes two parameters: key_type and value_type
  // Basic Guarantee
  // Exception Neutral
  template<typename func>
  void traverse(func function) {
    auto p = _data.get();

    //iterate through the list, calling the function on
    //the key and value of each item.
    while(p != nullptr) {
      function(p->_data.first, p->_data.second); // may throw
      p = p->_next.get();
    }
  }

};

#endif
