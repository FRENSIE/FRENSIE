//---------------------------------------------------------------------------//
//!
//! \file   Tuple.hpp
//! \author Alex Robinson
//! \brief  Simple structs for storing several objects of arbitrary type
//!
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
  //! Default constructor
  Pair() : first(), second() { /* ... */ }
  
  //! Constructor
  Pair( T1 value1, T2 value2 ) : first(value1), second(value2) 
  { /* ... */ }
  
  //! Reassignment operator
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
  //! Default constructor
  Trip() : first(), second(), third() { /* ... */ }

  //! Constructor
  Trip( T1 value1, T2 value2, T3 value3 ) : first(value1), second(value2),
					    third(value3) 
  { /* ... */ }

  //! Reassignment operator
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
  //! Default constructor
  Quad() : first(), second(), third(), fourth() { /* ... */ }
  
  //! Constructor
  Quad( T1 value1, T2 value2, T3 value3, T4 value4 ) : first(value1),
						       second(value2),
						       third(value3),
						       fourth(value4) 
  { /* ... */ }

  //! Reassignment operator
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

//! Non-member Pair non-equality operator
template<typename T1, typename T2>
bool operator!=( const Pair<T1,T2> &left, const Pair<T1,T2> &right ) { return (left.first != right.first) || (left.second != right.second); }

//! Non-member Pair equality operator 
template<typename T1, typename T2>
bool operator==( const Pair<T1,T2> &left, const Pair<T1,T2> &right ) { return (left.first == right.first) && (left.second == right.second); }

//! Non-member Trip non-equality operator
template<typename T1, typename T2, typename T3>
bool operator!=( const Trip<T1,T2,T3> &left, const Trip<T1,T2,T3> &right ) { return (left.first != right.first) || (left.second != right.second) || (left.third != right.third); }

//! Non-member Trip equality operator 
template<typename T1, typename T2, typename T3>
bool operator==( const Trip<T1,T2,T3> &left, const Trip<T1,T2,T3> &right ) { return (left.first == right.first) && (left.second == right.second) && (left.third == right.third); }

//! Non-member Quad non-equality operator
template<typename T1, typename T2, typename T3, typename T4>
bool operator!=( const Quad<T1,T2,T3,T4> &left, const Quad<T1,T2,T3,T4> &right ) { return (left.first != right.first) || (left.second != right.second) || (left.third != right.third) || (left.fourth != right.fourth); }

//! Non-member Quad equality operator
template<typename T1, typename T2, typename T3, typename T4>
bool operator==( const Quad<T1,T2,T3,T4> &left, const Quad<T1,T2,T3,T4> &right ) { return (left.first == right.first) && (left.second == right.second) && (left.third == right.third) && (left.fourth == right.fourth); }

//---------------------------------------------------------------------------//
// Specialize the HDF5TypeTraits class for the Tuple Structs
//---------------------------------------------------------------------------//
/*! \brief The partial specialization of the FACEMC::HDF5TypeTraits for the
 * FACEMC::Pair struct
 * \ingroup hdf5_type_traits
 */
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

/*! \brief The partial specialization of the FACEMC::HDF5TypeTraits for the
 * FACEMC::Trip struct
 * \ingroup hdf5_type_traits
 */
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

/*! \brief The partial specialization of the FACEMC::HDF5TypeTraits for the
 * FACEMC::Quad struct
 * \ingroup hdf5_type_traits
 */
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
