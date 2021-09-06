/*
 * Darian Marvel
 * 9/5/2021
 * Header file for class delivery
*/

#ifndef INCLUDED_DELIVERY_H
#define INCLUDED_DELIVERY_H

#include <cassert>
#include <string>

class Delivery {

//Constructors
public:

  Delivery();

  Delivery(std::string n, int a, int m);

//Member functions
public:

  bool empty() const;
  std::string toString() const;

//Operator functions
public:

  Delivery & operator++();
  Delivery operator++(int);

  Delivery & operator--();
  Delivery operator--(int);

//getter and setter member functions
public:

  std::string getName() const;
  int getQuantity() const;
  int getMonth() const;

  void setName(std::string);
  void setQuantity(int i);
  void setMonth(int i);

//Private Data Members
private:
  std::string _name;
  int _amount;
  int _month;

};

bool operator==(const Delivery & one, const Delivery & two);
bool operator!=(const Delivery & one, const Delivery & two);

std::ostream & operator<<(std::ostream & stream, const Delivery & del);

#endif
