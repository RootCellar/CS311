// Glenn G. Chappell
// Started: 2021-10-12
// Updated: 2021-10-20
//
// For CS 311 Fall 2021
// Header for class FSTArray
// Frightfully smart array of int
// Preliminary to Project 5

/*
 * Darian Marvel
 * 10/28/2021
 * Completing Project 5 by:
 *  - turning FSTArray into a template (and therefore FSTArray)
 *  - finishing the implementation, and incomplete comments
*/

#ifndef FILE_FSTArray_H_INCLUDED
#define FILE_FSTArray_H_INCLUDED

#include <cstddef>
// For std::size_t
#include <algorithm>
// For std::max


// *********************************************************************
// class FSTArray - Class definition
// *********************************************************************


// class FSTArray
// Frightfully Smart Templated Array
// Resizable, copyable/movable, exception-safe.
// Invariants:
//     0 <= _size <= _capacity.
//     _data points to an array of value_type, allocated with new [],
//      owned by *this, holding _capacity value_type values -- UNLESS
//      _capacity == 0, in which case _data may be nullptr.
template<typename VType>
class FSTArray {

// ***** FSTArray: types *****
public:

    // value_type: type of data items
    using value_type = VType;

    // size_type: type of sizes & indices
    using size_type = std::size_t;

    // iterator, const_iterator: random-access iterator types
    using iterator = value_type *;
    using const_iterator = const value_type *;

// ***** FSTArray: internal-use constants *****
private:

    // Capacity of default-constructed object
    enum { DEFAULT_CAP = 16 };

// ***** FSTArray: ctors, op=, dctor *****
public:

    // Default ctor & ctor from size
    // Strong Guarantee
    explicit FSTArray(size_type size=0)
        :_capacity(std::max(size, size_type(DEFAULT_CAP))),
            // _capacity must be declared before _data
         _size(size),
         _data(_capacity == 0 ? nullptr
                              : new value_type[_capacity])
    {}

    // Copy ctor
    // Strong Guarantee
    FSTArray(const FSTArray<value_type> & other);

    // Move ctor
    // No-Throw Guarantee
    FSTArray(FSTArray<value_type> && other) noexcept;

    // Copy assignment operator
    // Strong Guarantee
    FSTArray<value_type> & operator=(const FSTArray<value_type> & other);

    // Move assignment operator
    // No-Throw Guarantee
    FSTArray<value_type> & operator=(FSTArray<value_type> && other) noexcept;

    // Dctor
    // No-Throw Guarantee
    ~FSTArray()
    {
        delete [] _data;
    }

// ***** FSTArray: general public operators *****
public:

    // operator[] - non-const & const
    // Pre:
    //     index is on [0, _size)
    // No-Throw Guarantee
    value_type & operator[](size_type index)
    {
        if(index >= _size) index = _size-1;
        if(index < 0) index = 0;

        return _data[index];
    }
    const value_type & operator[](size_type index) const
    {
      if(index >= _size) index = _size-1;
      if(index < 0) index = 0;

      return _data[index];
    }

// ***** FSTArray: general public functions *****
public:

    // size
    // No-Throw Guarantee
    size_type size() const noexcept
    {
        return _size;
    }

    // empty
    // No-Throw Guarantee
    bool empty() const noexcept
    {
        return size() == 0;
    }

    // begin - non-const & const
    // No-Throw Guarantee
    iterator begin() noexcept
    {
        return _data;
    }
    const_iterator begin() const noexcept
    {
        return _data;
    }

    // end - non-const & const
    // No-Throw Guarantee
    iterator end() noexcept
    {
        return begin() + size();
    }
    const_iterator end() const noexcept
    {
        return begin() + size();
    }

    // resize
    // Strong Guarantee
    void resize(size_type newsize);

    // insert
    // Strong Guarantee
    iterator insert(iterator pos,
                    const value_type & item)
    {

        size_t index = pos - begin();
        resize(_size + 1);

        _data[size()-1] = item;
        std::rotate(begin()+index, end()-1, end());

        return begin() + index;
    }

    // erase
    // Strong Guarantee
    iterator erase(iterator pos)
    {

      if(_size == 0) return begin();
      if(pos >= end() || pos < begin()) return begin();

      size_t index = pos - begin();

      std::rotate(begin()+index, begin()+index+1, end());

      resize(size() - 1);

      return begin()+index;
    }

    // push_back
    // Strong Guarantee
    void push_back(const value_type & item)
    {
        insert(end(), item);
    }

    // pop_back
    // Strong Guarantee
    void pop_back()
    {
        erase(end()-1);
    }

    // swap
    // No-Throw Guarantee
    void swap(FSTArray<value_type> & other) noexcept;

// ***** FSTArray: data members *****
private:

    // Below, _capacity must be declared before _data
    size_type    _capacity;  // Size of our allocated array
    size_type    _size;      // Size of client's data
    value_type * _data;      // Pointer to our array

};  // End class FSTArray

// *********************************************************************
// class FSTArray - Member function definitions
// *********************************************************************


// Copy ctor
// See header for info.
template<typename VType>
FSTArray<VType>::FSTArray(const FSTArray<VType> & other)
    :_capacity(other._capacity),
     _size(other.size()),
     _data(other._capacity == 0 ? nullptr
                                : new value_type[other._capacity])
{
  if(other._capacity != 0) {
    try{
      std::copy(other.begin(), other.end(), begin());
    } catch(...) {
        delete [] _data;
        throw;
    }
  }
}


// Move ctor
// See header for info.
template<typename VType>
FSTArray<VType>::FSTArray(FSTArray<VType> && other) noexcept
    :_capacity(other._capacity),
     _size(other._size),
     _data(other._data)
{
    other._capacity = 0;
    other._size = 0;
    other._data = nullptr;
}


// Copy assignment operator
// See header for info.
template<typename VType>
FSTArray<VType> & FSTArray<VType>::operator=(const FSTArray<VType> & other)
{
  FSTArray<VType> temp(other.size());

  std::copy(other.begin(), other.end(), temp.begin());

  swap(temp);

  return *this;
}


// Move assignment operator
// See header for info.
template<typename VType>
FSTArray<VType> & FSTArray<VType>::operator=(FSTArray<VType> && other) noexcept
{
    swap(other);
    return *this;
}


// resize
// See header for info.
template<typename VType>
void FSTArray<VType>::resize(FSTArray<VType>::size_type newsize)
{
  if(newsize >= _capacity) {

    //Create a new list of data with the proper size
    FSTArray<VType> newData(newsize * 3);
    newData._size = newsize;

    //copy our stuff to it.
    //this CAN throw. BUT, if it does,
    //we will simply propogate out and destroy the newData,
    //and leave our data unchanged.
    std::copy(begin(), end(), newData.begin());

    //We successfully copied, so now
    //we can just swap. This does not throw!
    swap(newData);
  }
  else if(newsize < _capacity){
    _size = newsize;
  }
}

/*

// insert
// See header for info.
template<typename VType>
FSTArray::iterator FSTArray<VType>::insert(FSTArray::iterator pos,
                                  const FSTArray::value_type & item)
{
    // TODO: WRITE THIS!!!
    return begin();  // DUMMY
}


// erase
// See header for info.
template<typename VType>
FSTArray::iterator FSTArray<VType>::erase(FSTArray::iterator pos)
{
    // TODO: WRITE THIS!!!
    return begin();  // DUMMY
}

*/

// swap
// See header for info.
template<typename VType>
void FSTArray<VType>::swap(FSTArray<VType> & other) noexcept
{
    std::swap(_data, other._data);
    std::swap(_size, other._size);
    std::swap(_capacity, other._capacity);
}

#endif  //#ifndef FILE_FSTArray_H_INCLUDED
