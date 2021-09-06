/*
 * Darian Marvel
 * 9/5/2021
 * cpp file for class delivery
*/

#include "delivery.h"

Delivery::Delivery(): _name("UNSPECIFIED"), _amount(0), _month(1)
{}

Delivery::Delivery(std::string n, int a, int m): _name(n), _amount(a), _month(m)
{}

bool Delivery::empty() const {
  return _amount == 0;
}

std::string Delivery::toString() const {
  std::string toRet;
  toRet += getName();
  toRet += " (";
  toRet += std::to_string(getQuantity());
  toRet += "), ";

  switch (_month)
  {
    case 1:
    toRet += "Jan";
    break;
    case 2:
    toRet += "Feb";
    break;
    case 3:
    toRet += "Mar";
    break;
    case 4:
    toRet += "Apr";
    break;
    case 5:
    toRet += "May";
    break;
    case 6:
    toRet += "Jun";
    break;
    case 7:
    toRet += "Jul";
    break;
    case 8:
    toRet += "Aug";
    break;
    case 9:
    toRet += "Sep";
    break;
    case 10:
    toRet += "Oct";
    break;
    case 11:
    toRet += "Nov";
    break;
    case 12:
    toRet += "Dec";
    break;
  }

  return toRet;
}

Delivery & Delivery::operator++() {
  _amount++;
  return *this;
}

Delivery Delivery::operator++(int){
  Delivery toRet(*this);
  ++(*this);
  return toRet;
}

Delivery & Delivery::operator--() {
  if(_amount > 0) _amount--;
  return *this;
}

Delivery Delivery::operator--(int) {
  Delivery toRet(*this);
  --(*this);
  return toRet;
}

std::string Delivery::getName() const {
  return _name;
}

int Delivery::getQuantity() const {
  return _amount;
}

int Delivery::getMonth() const {
 return _month;
}

void Delivery::setName(std::string n) {
 _name = n;
}

void Delivery::setQuantity(int i) {
  assert( i >= 0 );
 _amount = i;
}

void Delivery::setMonth(int i) {
  assert( i > 0 );
  assert( i < 13 );
 _month = i;
}

bool operator==(const Delivery & one, const Delivery & two) {
  return one.getName() == two.getName() && one.getQuantity() == two.getQuantity() && one.getMonth() == two.getMonth();
}

bool operator!=(const Delivery & one, const Delivery & two) {
  return !(one == two);
}

std::ostream & operator<<(std::ostream & stream, const Delivery & del) {
  stream << del.toString();
  return stream;
}
