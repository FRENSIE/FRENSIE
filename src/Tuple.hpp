//---------------------------------------------------------------------------//
// \file Tuple.hpp
// \author Alex Robinson
// \brief Simple structs for storing several objects of arbitrary type
//---------------------------------------------------------------------------//

#ifndef FACEMC_TUPLE_HPP
#define FACEMC_TUPLE_HPP

// Std Lib Includes
#include <iostream>

// HDF5 Includes
#include <H5Cpp.h>

// FACEMC Includes
#include "HDF5TypeTraits.hpp"
#include "HDF5ExceptionCatchMacro.hpp"

namespace FACEMC{

//! Struct for holding two objects of arbitrary type
template<typename T1, typename T2>
struct Pair
{
  static const int size = 2;
  static H5::CompType createHDF5DataType();
  static std::string name();
  typedef T1 first_type;
  typedef T2 second_type;
  T1 first;
  T2 second;
};

//! Struct for holding three objects of arbitrary type
template<typename T1, typename T2, typename T3>
struct Trip
{
  static const int size = 3;
  static H5::CompType createHDF5DataType();
  static std::string name();
  typedef T1 first_type;
  typedef T2 second_type;
  typedef T3 third_type;
  T1 first;
  T2 second;
  T3 third;
};

//! Struct for holding four objects of arbitrary type
template<typename T1, typename T2, typename T3, typename T4>
struct Quad
{
  static const int size = 4;
  static H5::CompType createHDF5DataType();
  static std::string name();
  typedef T1 first_type;
  typedef T2 second_type;
  typedef T3 third_type;
  typedef T4 fourth_type;
  T1 first;
  T2 second;
  T3 third;
  T4 fourth;
};

//---------------------------------------------------------------------------//
// Specialize the HDF5TypeTraits class for the Tuple Structs
//---------------------------------------------------------------------------//
template<>
struct HDF5TypeTraits<Pair<double,double> >
{
  static H5::CompType dataType()
  {
    return Pair<double,double>::createHDF5DataType();
  }
  
  static inline std::string name() 
  {
    return Pair<double,double>::name();
  }
};

template<>
struct HDF5TypeTraits<Trip<unsigned int,double,double> >
{
  static H5::CompType dataType()
  {
    return Trip<unsigned int,double,double>::createHDF5DataType();
  }
  
  static inline std::string name() 
  { 
    return Trip<unsigned int,double,double>::name();
  }
};

template<>
struct HDF5TypeTraits<Quad<unsigned int,unsigned int,double,double> >
{
  static H5::CompType dataType()
  {
    return Quad<unsigned int,unsigned int,double,double>::createHDF5DataType();
  }
  
  static inline std::string name() 
  { 
    return Quad<unsigned int,unsigned int,double,double>::name();
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
