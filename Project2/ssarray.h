/*
 * Darian Marvel
 * 9/15/2021
 * Header containing template class SSArray
*/

#ifndef INCLUDED_SSARRAY_H
#define INCLUDED_SSARRAY_H

//std::size_t
#include <cstddef>

//assert
#include <cassert>

template<typename Data_Type>
class SSArray {

//Public Data Members
public:
  using value_type = Data_Type;
  using size_type = std::size_t;

//constructors, deconstructor, etc.
public:

  SSArray(): _arrPtr(new value_type[8]), _size(8)
  {}

  explicit SSArray(size_type size)
  {
    assert(size >= 0);
    _arrPtr = new value_type[size];
    _size = size;
  }

  SSArray(size_type size, value_type item)
  {
    assert(size >= 0);
    _arrPtr = new value_type[size];
    _size = size;

    for(size_type i = 0; i < _size; i++) {
      _arrPtr[i] = item;
    }
  }

  ~SSArray() {
    delete [] _arrPtr;
  }

//public functions
public:

  value_type& operator[](size_type i) {
    assert(i >= 0);
    assert(i < _size);

    return _arrPtr[i];
  }

  const value_type& operator[](size_type i) const {
    assert(i >= 0);
    assert(i < _size);

    return _arrPtr[i];
  }

  value_type* begin() {
    return _arrPtr;
  }

  value_type* end() {
    return _arrPtr + _size;
  }

  const value_type* begin() const {
    return _arrPtr;
  }

  const value_type* end() const {
    return _arrPtr + _size;
  }

  size_type size() const {
    return _size;
  }

//private functions
private:


//Private Data Members
private:
  value_type* _arrPtr;
  size_type _size;
};

//Global Operator Functions
template<typename Data_Type>
bool operator==( const SSArray<Data_Type> & one, const SSArray<Data_Type> & two ) {
  if(one.size() != two.size()) return false;

  for(std::size_t i = 0; i < one.size(); i++) {
    if(one[i] != two[i]) return false;
  }

  return true;
}

template<typename Data_Type>
bool operator!=( const SSArray<Data_Type> & one, const SSArray<Data_Type> & two ) {
  return !(one == two);
}


template<typename Data_Type>
bool operator<( const SSArray<Data_Type> & one, const SSArray<Data_Type> & two ) {
  for( std::size_t i = 0; i < one.size() && i < two.size(); i++) {
    if(one[i] < two[i]) return true;
  }

  if(two.size() > one.size()) return true;
  return false;
}

template<typename Data_Type>
bool operator<=( const SSArray<Data_Type> & one, const SSArray<Data_Type> & two ) {
  return !(one > two);
}

template<typename Data_Type>
bool operator>( const SSArray<Data_Type> & one, const SSArray<Data_Type> & two ) {
  return !(one <= two);
}

template<typename Data_Type>
bool operator>=( const SSArray<Data_Type> & one, const SSArray<Data_Type> & two ) {
  return !(one < two);
}

#endif
