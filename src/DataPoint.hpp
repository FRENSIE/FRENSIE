//---------------------------------------------------------------------------//
// \file DataPoint.hpp
// \author Alex Robinson
// \brief Simple struct for storing a data point
//---------------------------------------------------------------------------//

#ifndef DATA_POINT_HPP
#define DATA_POINT_HPP

// HDF5 Includes
#include <H5Cpp.h>

// FACEMC Includes
#include "FACEMC_assertion.hpp"
#include "HDF5TypeTraits.hpp"
#include "HDF5ExceptionCatchMacro.hpp"

namespace FACEMC{

//! Struct for holding a 2D data point
template<typename T1, typename T2>
struct DataPoint
{
  typedef 2 size;
  typedef T1 type1;
  typedef T2 type2;
  T1 value1;
  T2 value2;
}

//! Struct for holding a 3D data point
template<typename T1, typename T2, typename T3>
struct DataPoint
{
  typedef 3 size;
  typedef T1 type1;
  typedef T2 type2;
  typedef T3 type3;
  T1 value1;
  T2 value2;
  T3 value3;
}


//! Struct for holding a 4D data point
template<typename T1, typename T2, typename T3, typename T4>
struct DataPoint
{
  typedef 4 size;
  typedef T1 type1;
  typedef T2 type2;
  typedef T3 type3;
  typedef T4 type4;
  T1 value1;
  T2 value2;
  T3 value3;
  T4 value4;
}

//---------------------------------------------------------------------------//
// Specialize the HDF5TypeTraits class for the DataPoint Struct
//---------------------------------------------------------------------------//
template<>
struct HDF5TypeTraits<DataPoint>
{
  static H5::CompType dataType()
  {
    
    H5::CompType memtype( sizeof(DataPoint) );
    
    // the insertMember function can throw H5::DataTypeIException exceptions
    try{
      
      memtype.insertMember( "value1",
			    HOFFSET( DataPoint, value1 ),
			    HDF5TypeTraits<DataPoint::type1>::dataType() );
      
      memtype.insertMember( "value2",
			    HOFFSET( DataPoint, value2 ),
			    HDF5TypeTraits<DataPoint::type2>::dataType() );
    
      if( DataPoint::size > 2 )
      {
	memtype.insertMember( "value3",
			      HOFFSET( DataPoint, value3 ),
			      HDF5TypeTraits<DataPoint::type3>::dataType() );
      }
    
      if( DataPoint::size > 3 )
      {
	memtype.insertMember( "value4",
			      HOFFSET( DataPoint, value4 ),
			      HDF5TypeTraits<DataPoint::type4>::dataType() );
      }
    }
    
    HDF5_EXCEPTION_CATCH_AND_EXIT();
    
    return memtype;
  }
  
  static inline std::string name() 
  { 
    if( DataPoint::size == 2 )
      return "2D DataPoint";
    else if( DataPoint::size == 3 )
      return "3D DataPoint";
    else if( DataPoint::size == 4 )
      return "4D DataPoint";
  }
}

} // end FACEMC namespace

#endif // end DATA_POINT_HPP

//---------------------------------------------------------------------------//
// end DataPoint.hpp
//---------------------------------------------------------------------------//
