/*
 * Darian Marvel
 * 9/15/2021
 * Header containing template class SSArray
*/

#ifndef INCLUDED_SSARRAY_H
#define INCLUDED_SSARRAY_H

//std::size_t
#include <cstddef>

template<typename Data_Type>
class SSArray {

//constructor, deconstructor, etc.
public:

//public functions
public:

//private functions
private:

//Public Data Members
public:
  using value_type = Data_Type;
  using size_type = std::size_t;

//Private Data Members
private:
  Data_Type* _arrPtr;
  size_type _size;
};

#endif
