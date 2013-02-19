//---------------------------------------------------------------------------//
// \file Tuple_def.hpp
// \author Alex Robinson
// \brief Template definitions for the tuple structs.
//---------------------------------------------------------------------------//

#ifndef FACEMC_TUPLE_DEF_HPP
#define FACEMC_TUPLE_DEF_HPP

// HDF5 Includes
#include <H5Cpp.h>

// FACEMC Includes
#include "HDF5TypeTraits.hpp"
#include "HDF5ExceptionCatchMacro.hpp"

namespace FACEMC{

//! Create an HDF5 type that represents the Pair struct.
template<typename T1, typename T2>
inline H5::CompType Pair<T1,T2>::createHDF5DataType()
{
    
  H5::CompType memtype( sizeof(Pair) );
  
  // the insertMember function can throw H5::DataTypeIException exceptions
  try
  {
    
    memtype.insertMember( "first",
			  HOFFSET( Pair, first ),
			  HDF5TypeTraits<T1>::dataType() );
    
    memtype.insertMember( "second",
			  HOFFSET( Pair, second ),
			  HDF5TypeTraits<T2>::dataType() );
    
  }
  
  HDF5_EXCEPTION_CATCH_AND_EXIT();
  
  return memtype;
}

//! Return the name of the pair struct.
template<typename T1, typename T2>
inline std::string Pair<T1,T2>::name()
{ 
  return "Pair<" + HDF5TypeTraits<T1>::name() + "," +
    HDF5TypeTraits<T2>::name() + ">";
}

//! Create an HDF5 type that represents the triple struct
template<typename T1, typename T2, typename T3>
inline H5::CompType Trip<T1,T2,T3>::createHDF5DataType()
{
    
  H5::CompType memtype( sizeof(Trip) );
  
  // the insertMember function can throw H5::DataTypeIException exceptions
  try
  {
    
    memtype.insertMember( "first",
			  HOFFSET( Trip, first ),
			  HDF5TypeTraits<T1>::dataType() );
    
    memtype.insertMember( "second",
			  HOFFSET( Trip, second ),
			  HDF5TypeTraits<T2>::dataType() );
    
    memtype.insertMember( "third",
			  HOFFSET( Trip, third ),
			  HDF5TypeTraits<T3>::dataType() );
  }
  
  HDF5_EXCEPTION_CATCH_AND_EXIT();
  
  return memtype;
}

//! Return the name of the triplet struct.
template<typename T1, typename T2, typename T3>
inline std::string Trip<T1,T2,T3>::name()
{
  return "Trip<" + HDF5TypeTraits<T1>::name() + "," +
    HDF5TypeTraits<T2>::name() + "," +
    HDF5TypeTraits<T3>::name() + ">";
}

  //! Create an HDF5 type that represents the quadruplet struct.
template<typename T1, typename T2, typename T3, typename T4>
inline H5::CompType Quad<T1,T2,T3,T4>::createHDF5DataType()
{
    
  H5::CompType memtype( sizeof(Quad) );
  
  // the insertMember function can throw H5::DataTypeIException exceptions
  try
  {
    
    memtype.insertMember( "first",
			  HOFFSET( Quad, first ),
			  HDF5TypeTraits<T1>::dataType() );
    
    memtype.insertMember( "second",
			  HOFFSET( Quad, second ),
			  HDF5TypeTraits<T2>::dataType() );
    
    memtype.insertMember( "third",
			  HOFFSET( Quad, third ),
			  HDF5TypeTraits<T3>::dataType() );
    
    memtype.insertMember( "fourth",
			  HOFFSET( Quad, fourth ),
			  HDF5TypeTraits<T4>::dataType() );
  }
  
  HDF5_EXCEPTION_CATCH_AND_EXIT();
  
  return memtype;
}

//! Return the name of the quadruplet struct.
template<typename T1, typename T2, typename T3, typename T4>
inline std::string Quad<T1,T2,T3,T4>::name()
{
  return "Quad<" + HDF5TypeTraits<T1>::name() + "," +
    HDF5TypeTraits<T2>::name() + "," +
    HDF5TypeTraits<T3>::name() + "," +
    HDF5TypeTraits<T4>::name() + ">";
}

} // end FACEMC namespace

#endif // end FACEMC_TUPLE_DEF_HPP

//---------------------------------------------------------------------------//
// end Tuple_def.hpp
//---------------------------------------------------------------------------//
