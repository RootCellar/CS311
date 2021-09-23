// dp3.cpp  SKELETON
// Glenn G. Chappell
// 2021-09-16
//
// For CS 311 Fall 2021
// Source for Project 3 functions
//
// Darian Marvel
// 2021-09-22
// Completing project 3 using the skeleton

#include "dp3.h"       // For Project 3 prototypes & templates

#include <functional>
using std::function;

//Throws if ff() does
void didItThrow(const function<void()> & ff,
                bool & threw)
{
    threw = false;

    try{
      ff();
    } catch(...) {
      threw = true;
      throw;
    }
}

//Pre: a and b are positive, and not both zero.
int gcd(int a,
        int b)
{
    if(a == 0) return b;
    else if( a > b ) return gcd(b, a);
    else return gcd(b % a, a);
}
