//---------------------------------------------------------------------------//
//!
//! \file Tuple_def.hpp
//! \author Alex Robinson
//! \brief Template definitions for the tuple structs.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_TUPLE_DEF_HPP
#define FACEMC_TUPLE_DEF_HPP

// HDF5 Includes
#include <H5Cpp.h>

// FACEMC Includes
#include "HDF5TypeTraits.hpp"
#include "ExceptionCatchMacros.hpp"

namespace FACEMC{

//! Create an HDF5 type that represents the FACEMC::Pair struct.
template<typename T1, typename T2>
inline H5::CompType Pair<T1,T2>::createHDF5DataType()
{
  typedef Pair<T1,T2> Tuple;
  
  H5::CompType memtype( sizeof(Tuple) );
  
  // the insertMember function can throw H5::DataTypeIException exceptions
  try
  {
    
    memtype.insertMember( "first",
			  HOFFSET( Tuple , first ),
			  Traits::HDF5TypeTraits<T1>::dataType() );
    
    memtype.insertMember( "second",
			  HOFFSET( Tuple, second ),
			  Traits::HDF5TypeTraits<T2>::dataType() );
    
  }
  
  HDF5_EXCEPTION_CATCH_AND_EXIT();
  
  return memtype;
}

//! Return the name of the FACEMC::Pair struct.
template<typename T1, typename T2>
inline std::string Pair<T1,T2>::name()
{ 
  return "Pair<" + Traits::HDF5TypeTraits<T1>::name() + "," +
    Traits::HDF5TypeTraits<T2>::name() + ">";
}

//! Create an HDF5 type that represents the FACEMC::Trip struct
template<typename T1, typename T2, typename T3>
inline H5::CompType Trip<T1,T2,T3>::createHDF5DataType()
{
  typedef Trip<T1,T2,T3> Tuple;
    
  H5::CompType memtype( sizeof(Tuple) );
  
  // the insertMember function can throw H5::DataTypeIException exceptions
  try
  {
    
    memtype.insertMember( "first",
			  HOFFSET( Tuple, first ),
			  Traits::HDF5TypeTraits<T1>::dataType() );
    
    memtype.insertMember( "second",
			  HOFFSET( Tuple, second ),
			  Traits::HDF5TypeTraits<T2>::dataType() );
    
    memtype.insertMember( "third",
			  HOFFSET( Tuple, third ),
			  Traits::HDF5TypeTraits<T3>::dataType() );
  }
  
  HDF5_EXCEPTION_CATCH_AND_EXIT();
  
  return memtype;
}

//! Return the name of the FACEMC::Trip struct.
template<typename T1, typename T2, typename T3>
inline std::string Trip<T1,T2,T3>::name()
{
  return "Trip<" + Traits::HDF5TypeTraits<T1>::name() + "," +
    Traits::HDF5TypeTraits<T2>::name() + "," +
    Traits::HDF5TypeTraits<T3>::name() + ">";
}

//! Create an HDF5 type that represents the FACEMC::Quad struct.
template<typename T1, typename T2, typename T3, typename T4>
inline H5::CompType Quad<T1,T2,T3,T4>::createHDF5DataType()
{
  typedef Quad<T1,T2,T3,T4> Tuple;
    
  H5::CompType memtype( sizeof(Tuple) );
  
  // the insertMember function can throw H5::DataTypeIException exceptions
  try
  {
    
    memtype.insertMember( "first",
			  HOFFSET( Tuple, first ),
			  Traits::HDF5TypeTraits<T1>::dataType() );
    
    memtype.insertMember( "second",
			  HOFFSET( Tuple, second ),
			  Traits::HDF5TypeTraits<T2>::dataType() );
    
    memtype.insertMember( "third",
			  HOFFSET( Tuple, third ),
			  Traits::HDF5TypeTraits<T3>::dataType() );
    
    memtype.insertMember( "fourth",
			  HOFFSET( Tuple, fourth ),
			  Traits::HDF5TypeTraits<T4>::dataType() );
  }
  
  HDF5_EXCEPTION_CATCH_AND_EXIT();
  
  return memtype;
}

//! Return the name of the FACEMC::Quad struct.
template<typename T1, typename T2, typename T3, typename T4>
inline std::string Quad<T1,T2,T3,T4>::name()
{
  return "Quad<" + Traits::HDF5TypeTraits<T1>::name() + "," +
    Traits::HDF5TypeTraits<T2>::name() + "," +
    Traits::HDF5TypeTraits<T3>::name() + "," +
    Traits::HDF5TypeTraits<T4>::name() + ">";
}

} // end FACEMC namespace

#endif // end FACEMC_TUPLE_DEF_HPP

//---------------------------------------------------------------------------//
// end Tuple_def.hpp
//---------------------------------------------------------------------------//
