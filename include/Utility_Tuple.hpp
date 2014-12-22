//---------------------------------------------------------------------------//
//!
//! \file   Utility_Tuple.hpp
//! \author Alex Robinson
//! \brief  Simple structs for storing several objects of arbitrary type
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TUPLE_HPP
#define UTILITY_TUPLE_HPP

// Std Lib Includes
#include <iostream>

namespace Utility{

//! Struct for holding two objects of arbitrary type
template<typename T1, typename T2>
struct Pair
{
  //! Default constructor
  Pair() : first(), second() { /* ... */ }
  
  //! Constructor
  Pair( T1 value1, T2 value2 ) : first(value1), second(value2) 
  { /* ... */ }
  
  //! Reassignment operator
  void operator()( T1 value1, T2 value2 ) 
  { first = value1; second = value2; }
  
  static const int size = 2;
  typedef T1 firstType;
  typedef T2 secondType;
  T1 first;
  T2 second;
};

//! Struct for holding three objects of arbitrary type
template<typename T1, typename T2, typename T3>
struct Trip
{
  //! Default constructor
  Trip() : first(), second(), third() { /* ... */ }

  //! Constructor
  Trip( T1 value1, T2 value2, T3 value3 ) : first(value1), second(value2),
					    third(value3) 
  { /* ... */ }

  //! Reassignment operator
  void operator()( T1 value1, T2 value2, T3 value3 ) 
  { first = value1; second = value2; third = value3; }
  
  static const int size = 3;
  typedef T1 firstType;
  typedef T2 secondType;
  typedef T3 thirdType;
  T1 first;
  T2 second;
  T3 third;
};

//! Struct for holding four objects of arbitrary type
template<typename T1, typename T2, typename T3, typename T4>
struct Quad
{
  //! Default constructor
  Quad() : first(), second(), third(), fourth() { /* ... */ }
  
  //! Constructor
  Quad( T1 value1, T2 value2, T3 value3, T4 value4 ) : first(value1),
						       second(value2),
						       third(value3),
						       fourth(value4) 
  { /* ... */ }

  //! Reassignment operator
  void operator()( T1 value1, T2 value2, T3 value3, T4 value4 ) 
  { first = value1; second = value2; third = value3; fourth = value4; }
  
  static const int size = 4;
  typedef T1 firstType;
  typedef T2 secondType;
  typedef T3 thirdType;
  typedef T4 fourthType;
  T1 first;
  T2 second;
  T3 third;
  T4 fourth;
};

//! Enum for refering to tuple members
enum TupleMember{
  FIRST,
  SECOND,
  THIRD,
  FOURTH
};

//! Non-member Pair inequality operator
template<typename T1, typename T2>
bool operator!=( const Pair<T1,T2> &left, const Pair<T1,T2> &right ) 
{ return (left.first != right.first) || (left.second != right.second); }

//! Non-member Pair equality operator 
template<typename T1, typename T2>
bool operator==( const Pair<T1,T2> &left, const Pair<T1,T2> &right ) 
{ return (left.first == right.first) && (left.second == right.second); }

//! Non-member Trip inequality operator
template<typename T1, typename T2, typename T3>
bool operator!=( const Trip<T1,T2,T3> &left, const Trip<T1,T2,T3> &right ) 
{ return (left.first != right.first) || (left.second != right.second) || 
    (left.third != right.third); }

//! Non-member Trip equality operator 
template<typename T1, typename T2, typename T3>
bool operator==( const Trip<T1,T2,T3> &left, const Trip<T1,T2,T3> &right ) 
{ return (left.first == right.first) && (left.second == right.second) && 
    (left.third == right.third); }

//! Non-member Quad inequality operator
template<typename T1, typename T2, typename T3, typename T4>
bool operator!=( const Quad<T1,T2,T3,T4> &left, const Quad<T1,T2,T3,T4> &right)
{ return (left.first != right.first) || (left.second != right.second) || 
    (left.third != right.third) || (left.fourth != right.fourth); }

//! Non-member Quad equality operator
template<typename T1, typename T2, typename T3, typename T4>
bool operator==( const Quad<T1,T2,T3,T4> &left, const Quad<T1,T2,T3,T4> &right)
{ return (left.first == right.first) && (left.second == right.second) && 
    (left.third == right.third) && (left.fourth == right.fourth); }

/*! \brief Stream operator for Pair
 * \ingroup print_format
 */
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream &out, const Utility::Pair<T1,T2> &p)
{
  out << "{ " << p.first << ", " << p.second << " }";
  return out;
}

/*! Stream operator for Trip
 * \ingroup print_format
 */
template<typename T1, typename T2, typename T3>
std::ostream& operator<<(std::ostream &out, const Utility::Trip<T1,T2,T3> &p)
{
  out << "{ " << p.first << ", " << p.second << ", " << p.third << " }";
  return out;
}

/*! Stream operator for Quad
 * \ingroup print_format
 */
template<typename T1, typename T2, typename T3, typename T4>
std::ostream& operator<<(std::ostream &out, 
			 const Utility::Quad<T1,T2,T3,T4> &p)
{
  out << "{ " << p.first << ", " << p.second << ", " << p.third 
      << ", " << p.fourth << " }";
  return out;
}

} // end Utility namespace

#endif // end UTILITY_TUPLE_HPP

//---------------------------------------------------------------------------//
// end Utility_Tuple.hpp
//---------------------------------------------------------------------------//
