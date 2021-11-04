#ifndef DP6_H
#define DP6_H

#include <utility>

#include "llnode2.h"

template<typename ValType>
void reverseList(std::unique_ptr<LLNode2<ValType>> & head) {

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

  LLMap(): _data() {

  }

  ~LLMap() = default;

  // Copy ctor
  LLMap(const LLMap<key_type, value_type> & other) = delete;

  // Move ctor
  LLMap(LLMap<key_type, value_type> && other) = delete;

  // Copy assignment operator
  LLMap<key_type, value_type> & operator=(const LLMap<key_type, value_type> & other) = delete;

  // Move assignment operator
  LLMap<key_type, value_type> & operator=(LLMap<key_type, value_type> && other) = delete;


  // ??? Guarantee
  size_type size() const {

  }

  // ??? Guarantee
  bool empty() const {

  }

  const value_type* find(key_type key) const {

  }

  // ??? Guarantee
  value_type* find(key_type key) {

  }

  // ??? Guarantee
  void insert(key_type key, value_type value) {

  }

  // ??? Guarantee
  void erase(key_type key) {

  }

  // ??? Guarantee
  template<typename func>
  void traverse(func function) {

  }

};

#endif
