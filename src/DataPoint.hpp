//---------------------------------------------------------------------------//
// \file DataPoint.hpp
// \author Alex Robinson
// \brief Simple struct for storing a data point
//---------------------------------------------------------------------------//

#ifndef DATA_POINT_HPP
#define DATA_POINT_HPP

// HDF5 Includes
#include <hdf5.h>

// FACEMC Includes
#include "FACEMC_assertion.hpp"

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
// Specialize the HDF5ScalarTraits class for the DataPoint Struct
//---------------------------------------------------------------------------//
template<>
struct HDF5ScalarTraits<DataPoint>
{
  static hid_t memoryType()
  {
    herr_t status;
    hid_t memtype;
    
    memtype = H5Tcreate( H5T_COMPOUND, 
			 sizeof(DataPoint) );
    
    status = H5Tinsert( memtype, 
			"value1",
			HOFFSET( DataPoint, value1 ),
			HDF5ScalarTraits<DataPoint::type1>::memoryType() );
    assertAlways( status == SUCCEED );
    
    status = H5Tinsert( memtype,
			"value2"
			HOFFSET( DataPoint, value2 ),
			HDF5ScalarTraits<DataPoint::type2>::memoryType() );
    assertAlways( status == SUCCEED );
    
    if( DataPoint::size > 2 )
      {
	status = H5Tinsert( memtype,
			    "value3",
			    HOFFSET( DataPoint, value3 ),
			    HDF5ScalarTraits<DataPoint::type3>::memoryType() );
	assertAlways( status == SUCCEED );
      }
    
    if( DataPoint::size > 3 )
      {
	status = H5Tinsert( memtype,
			    "value4",
			    HOFFSET( DataPoint, value4 ),
			    HDF5ScalarTraits<DataPoint::type4>::memoryType() );
	assertAlways( status == SUCCEED );
      }
    
    return memtype;
  }

  static hid_t fileTypeBE()
  {
    herr_t status;
    hid_t filetype;
    
    filetype = H5Tcreate( H5T_COMPOUND,
			  sizeof(DataPoint) );
    
    status = H5Tinsert( filetype,
			"value1",
			HOFFSET( DataPoint, value1 ),
			HDF5ScalarTraits<DataPoint::type1>::fileTypeBE() );
    assertAlways( status == SUCCEED );
    
    status = H5Tinsert( filetype,
			"value2",
			HOFFSET( DataPoint, value2 ),
			HDF5ScalarTraits<DataPoint::type2>::fileTypeBE() );
    assertAlways( status == SUCCEED );
    
    if( DataPoint::size > 2 )
      {
	status = H5Tinsert( filetype,
			    "value3",
			    HOFFSET( DataPoint, value3 ),
			    HDF5ScalarTraits<DataPoint::type3>::fileTypeBE() );
	assertAlways( status == SUCCEED );
      }
    
    if( DataPoint::size > 3 )
      {
	status = H5Tinsert( filetype,
			    "value4",
			    HOFFSET( DataPoint, value4 ),
			    HDF5ScalarTraits<DataPoint::type4>::fileTypeBE() );
	assertAlways( status == SUCCEED );
      }
    
    return filetype;
  }

  static hid_t fileTypeLE()
  {
    herr_t status;
    hid_t filetype;
    
    filetype = H5Tcreate( H5T_COMPOUND,
			  sizeof(DataPoint) );
    
    status = H5Tinsert( filetype,
			"value1",
			HOFFSET( DataPoint, value1 ),
			HDF5ScalarTraits<DataPoint::type1>::fileTypeLE() );
    assertAlways( status == SUCCEED );
    
    status = H5Tinsert( filetype,
			"value2",
			HOFFSET( DataPoint, value2 ),
			HDF5ScalarTraits<DataPoint::type2>::fileTypeLE() );
    assertAlways( status == SUCCEED );
    
    if( DataPoint::size > 2 )
      {
	status = H5Tinsert( filetype,
			    "value3",
			    HOFFSET( DataPoint, value3 ),
			    HDF5ScalarTraits<DataPoint::type3>::fileTypeLE() );
	assertAlways( status == SUCCEED );
      }
    
    if( DataPoint::size > 3 )
      {
	status = H5Tinsert( filetype,
			    "value4",
			    HOFFSET( DataPoint, value4 ),
			    HDF5ScalarTraits<DataPoint::type4>::fileTypeLE() );
	assertAlways( status == SUCCEED );
      }
    
    return filetype;
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
