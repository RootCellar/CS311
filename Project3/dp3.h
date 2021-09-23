// dp3.h  SKELETON
// Glenn G. Chappell
// 2021-09-16
//
// For CS 311 Fall 2021
// Header for Project 3 functions

#ifndef FILE_DP3_H_INCLUDED
#define FILE_DP3_H_INCLUDED

#include "llnode.h"    // For LLNode
#include <cstddef>     // For std::size_t
#include <functional>  // For std::function
#include <algorithm>   // For std::unique


template <typename ValueType>
ValueType lookup(const LLNode<ValueType> * head,
                 std::size_t index)
{
    if(head == nullptr) {
      throw std::out_of_range("lookup: invalid index " + index);
    }
    if(index == 0) return head->_data;

    const LLNode<ValueType>* current = head;
    std::size_t spot = 0;

    do {
      spot++;
    } while( (current = current->_next) != nullptr && spot != index );

    if(current == nullptr) {
      throw std::out_of_range("lookup: invalid index " + index);
    }
    else return current->_data;
}


// Implementation in source file
void didItThrow(const std::function<void()> & ff,
                bool & threw);


template <typename RAIter>
std::size_t uniqueCount(RAIter first,
                        RAIter last)
{
    std::sort(first, last);
    RAIter newLast = std::unique(first, last);
    return std::size_t( newLast - first );
}


// Implementation in source file
int gcd(int a,
        int b);


#endif  //#ifndef FILE_DP3_H_INCLUDED
