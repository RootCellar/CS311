// treesorter.h  SKELETON
// Glenn G. Chappell
// 2021-11-08
//
// For CS 311 Fall 2021
// Header for function template treesort
// There is no associated source file.

// Darian Marvel
// 11/14/2021
// Completing implementation of this file for Project 7

#ifndef FILE_TREESORTER_H_INCLUDED
#define FILE_TREESORTER_H_INCLUDED

#include <iterator>
// For std::iterator_traits
#include <memory>
// For std::unique_ptr

template<typename Value>
struct BSTreeNode {
  Value _data;

  std::unique_ptr<BSTreeNode<Value>> _left;
  std::unique_ptr<BSTreeNode<Value>> _right;

  // copy constructs _data, may throw
  BSTreeNode(Value item): _data(item) {}
};

// Given a binary search tree and the beginning of a forward-iterated list,
// inorder traverse the tree, copying items into the list
// thereby resulting in the list being sorted.
//
// Pre:
//    "spot" points to the valid beginnng of the list,
//    and the list has enough space to hold all the items in the tree
//
// Exception Neutral
// Basic Guarantee
template<typename Value, typename FDIter>
void traverse_insert(const std::unique_ptr<BSTreeNode<Value>> & head,
            FDIter & spot) {

    if(head == nullptr) return;

    // inorder traverse: left child, middle("me", head), right child

    //recurse left child
    traverse_insert(head->_left, spot);

    //middle ("me")
    *spot = head->_data;
    spot++;

    //recurse right child
    traverse_insert(head->_right, spot);

}

// Given the head of a binary search tree,
// insert the item into that tree, recursing as needed.
//
// Exception Neutral
// Basic Guarantee
template<typename Value>
void insert(std::unique_ptr<BSTreeNode<Value>> & head,
            const Value & item) {

    if(head == nullptr) {
      head = std::make_unique<BSTreeNode<Value>>(item);
      return;
    }
    else if(item < head->_data) {
      insert(head->_left, item);
    }
    else {
      insert(head->_right, item);
    }
}

// treesort
// Sort a given range using Treesort.
// Exception Neutral
// Pre:
//     first, last point to the valid beginning and ending
//     of the data range
// Requirements on Types:
//     FDIter is a forward iterator
//     value_type or Value has:
//        operator<, copy constructor, non-throwing destructor,
//        move assignment, and move constructor
// Exception safety guarantee:
//     Basic Guarantee
template<typename FDIter>
void treesort(FDIter first, FDIter last)
{
    // Value is the type that FDIter points to
    using Value = typename std::iterator_traits<FDIter>::value_type;

    // Create a Binary Search Tree
    std::unique_ptr<BSTreeNode<Value>> head = nullptr;

    // Insert everything into the tree
    for(FDIter current = first; current != last; current++) {
      insert(head, *current);
    }

    // Inorder Traverse the tree, copying items back into the original
    traverse_insert(head, first);
}


#endif //#ifndef FILE_TREESORTER_H_INCLUDED
