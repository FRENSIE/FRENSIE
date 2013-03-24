//---------------------------------------------------------------------------//
// \file   Tuple.hpp
// \author Alex Robinson
// \brief  Simple structs for storing several objects of arbitrary type
//---------------------------------------------------------------------------//

#ifndef FACEMC_TUPLE_HPP
#define FACEMC_TUPLE_HPP

// Std Lib Includes
#include <iostream>

// HDF5 Includes
#include <H5Cpp.h>

// FACEMC Includes
#include "HDF5TypeTraits.hpp"
#include "ExceptionCatchMacros.hpp"

namespace FACEMC{

//! Struct for holding two objects of arbitrary type
template<typename T1, typename T2>
struct Pair
{
  Pair() : first(), second() { /* ... */ }
  Pair( T1 value1, T2 value2 ) : first(value1), second(value2) 
  { /* ... */ }
  void operator()( T1 value1, T2 value2 ) { first = value1; second = value2; }
  static const int size = 2;
  static H5::CompType createHDF5DataType();
  static std::string name();
  typedef T1 firstType;
  typedef T2 secondType;
  T1 first;
  T2 second;
};

//! Struct for holding three objects of arbitrary type
template<typename T1, typename T2, typename T3>
struct Trip
{
  Trip() : first(), second(), third() { /* ... */ }
  Trip( T1 value1, T2 value2, T3 value3 ) : first(value1), second(value2),
					    third(value3) 
  { /* ... */ }
  void operator()( T1 value1, T2 value2, T3 value3 ) { first = value1; second = value2; third = value3; }
  static const int size = 3;
  static H5::CompType createHDF5DataType();
  static std::string name();
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
  Quad() : first(), second(), third(), fourth() { /* ... */ }
  Quad( T1 value1, T2 value2, T3 value3, T4 value4 ) : first(value1),
						       second(value2),
						       third(value3),
						       fourth(value4) 
  { /* ... */ }
  void operator()( T1 value1, T2 value2, T3 value3, T4 value4 ) { first = value1; second = value2; third = value3; fourth = value4; }
  static const int size = 4;
  static H5::CompType createHDF5DataType();
  static std::string name();
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

//---------------------------------------------------------------------------//
// Specialize the HDF5TypeTraits class for the Tuple Structs
//---------------------------------------------------------------------------//
template<typename T, typename T2>
struct HDF5TypeTraits<Pair<T,T2> >
{
  static H5::CompType dataType()
  {
    return Pair<T,T2>::createHDF5DataType();
  }
  
  static inline std::string name() 
  {
    return Pair<T,T2>::name();
  }
};

template<typename T, typename T2, typename T3>
struct HDF5TypeTraits<Trip<T,T2,T3> >
{
  static H5::CompType dataType()
  {
    return Trip<T,T2,T3>::createHDF5DataType();
  }
  
  static inline std::string name() 
  { 
    return Trip<T,T2,T3>::name();
  }
};

template<typename T, typename T2, typename T3, typename T4>
struct HDF5TypeTraits<Quad<T,T2,T3,T4> >
{
  static H5::CompType dataType()
  {
    return Quad<T,T2,T3,T4>::createHDF5DataType();
  }
  
  static inline std::string name() 
  { 
    return Quad<T,T2,T3,T4>::name();
  }
};

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "Tuple_def.hpp"

//---------------------------------------------------------------------------//

#endif // end FACEMC_TUPLE_HPP

//---------------------------------------------------------------------------//
// end Tuple.hpp
//---------------------------------------------------------------------------//
