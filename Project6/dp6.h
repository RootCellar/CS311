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

//Exception Neutral
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
  bool empty() const {
    return _data == nullptr;
  }

  // No-Throw Guarantee
  const value_type* find(const key_type& key) const {
    if(_data == nullptr) return nullptr;
    auto p = _data.get();

    while(p != nullptr && p->_data.first != key) p = p->_next.get();

    if(p == nullptr) return nullptr;
    else return &(p->_data.second);
  }

  // No-Throw Guarantee
  value_type* find(const key_type& key) {
    if(_data == nullptr) return nullptr;
    auto p = _data.get();

    while(p != nullptr && p->_data.first != key) p = p->_next.get();

    if(p == nullptr) return nullptr;
    else return &(p->_data.second);
  }

  // Strong Guarantee
  void insert(const key_type& key, const value_type& value) {
    if(_data == nullptr) {
      //create first data node
      pair_type pair;
      pair.first = key;
      pair.second = value;

      //std::unique_ptr<LLNode2<pair_type>> toAdd = std::make_unique<LLNode2<pair_type>>(pair);
    }
  }

  // ??? Guarantee
  void erase(const key_type& key) {

  }

  // ??? Guarantee
  template<typename func>
  void traverse(func function) {
    auto p = _data.get();

    while(p != nullptr) {
      std::cout << "C" << std::endl;
      function(p->_data.first, p->_data.second);
      p = p->_next.get();
    }
  }

};

#endif
