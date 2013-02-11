//---------------------------------------------------------------------------//
// \file DataProcessorBase.hpp
// \author Alex Robinson
// \brief Data Processor Base Class member function definitions
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <cmath>

// FACEMC Includes
#include "DataProcessorBase.hpp"
#include "ElectronShell.hpp"
#include "Exception.hpp"

namespace FACEMC{

//! Open an HDF5 file and overwrite any existing data
hid_t DataProcessorBase::openHDF5FileAndOverwrite( const std::string 
						   &file_name )
{
  return H5Fcreate( file_name.c_str(),
		    H5F_ACC_TRUNC,
		    H5P_DEFAULT,
		    H5P_DEFAULT );
}

//! Open an HDF5 file and append to any existing data
hid_t DataProcessorBase::openHDF5FileAndAppend( const std::string &file_name )
{
  return H5Fcreate( file_name.c_str(),
		    H5F_ACC_RDWR,
		    H5P_DEFAULT,
		    H5P_DEFAULT );
}

//! Close an HDF5 file
void DataProcessorBase::closeHDF5File( hid_t file_id )
{
  herr_t status = H5Fclose( file_id );
  testHDF5Status( status == SUCCEED,
		  "HDF5 file close error" );
}

//! Write atomic weight attribute to HDF5 file
void DataProcessorBase::writeAtomicWeightAttributeToHDF5File( const hid_t 
							      file_id,
							      const double 
							      atomic_weight )
{
  hid_t dataset_id, attribute_id, dataspace_id;
  hsize_t attribute_dim = 1;
  dataset_id = H5Dopen( file_id,
			"/Atomic_Weight",
			H5P_DEFAULT );
  dataspace_id = H5Screate_simple(1, &attribute_dim, NULL);
  attribute_id = H5Acreate( dataset_id, 
			    "Weight",
			    HDF5ScalarTraits<double>::fileTypeBE,
			    dataspace_id,
			    H5P_DEFAULT,
			    H5P_DEFAULT );
  status = H5Awrite( attribute_id,
		     HDF5ScalarTraits<double>::memoryType,
		     &atomic_weight );
  testHDF5( status == SUCCEED,
	    "HDF5 atomic weight attribute write error" );
  
  // Close the current attribute, dataspace and dataset
  status = H5Aclose( attribute_id );
  testHDF5( status == SUCCEED,
	    "HDF5 attribute close error" );
  
  status = H5Sclose( dataspace_id );
  testHDF5( status == SUCCEED,
	    "HDF5 dataspace close error" );
  
  status = H5Dclose( dataset_id );
  testHDF5( status == SUCCEED,
	    "HDF5 dataset close error" );
}

//! Read the first table header
void DataProcessorBase::readFirstTableHeader( FILE* datafile,
					      int &atomic_number,
					      int &outgoing_particle_designator,
					      int &atomic_weight,
					      int &interpolation_flag )
{
  // Variables for reading in EPDL data file header 1
  //  the variable names are consistent with the names in the EPDL docs
  char zaid[7];
  zaid[6] = '\0';
  char space[2];
  space[1] = '\0';
  char Yi[2];
  yi[1] = '\0';
  char Yo[3];
  yo[2] = '\0';
  char Al[10];
  AWl[9] = '\0';
  char Ar[3];
  AWr[2] = '\0';
  char date[7];
  data[6] = '\0';
  char iflag[2];
  iflag[1] = '\0';
  char extra[40];
  extra[39] = '\0';

  // File read return value dummy
  int rv;

  // Read first header
  rv = fscanf( epdl, "%6c%1c%2c%1c%2c%1c%9c%2c%1c%6c%1c%39c", zaid, space, Yi, 
	       space, Yo, space, Al, Ar, space, date, iflag, extra ); 

  atomic_number = atoi(zaid)/1000;
  outgoing_particle_designator = atoi(Yo);
  atomic_weight = extractValue<double>( Al, Ar );
  interpolation_flag = atoi(iflag);
}

//! Read the second table header
void DataProcessorBase::readSecondTableHeader( FILE* datafile, 
					       int &reaction_type,
					       int &electron_shell )
{
  // Variables for reading in the EPDL data file header 2
  //  the variable names are consistent with the names in the EPDL docs
  char C [3];
  C[2] = '\0';
  char I [4];
  Ic[3] = '\0';
  char S [4];
  Sc[3] = '\0';
  char garbage [14];
  garbage[13] = '\0';
  char X1l [10];
  X1l[9] = '\0';
  char X1r [3];
  X1r[2] = '\0';
  char extra [38];
  extra[37] = '\0';

  // File read return value dummy
  int rv;
  
  // Read second header
  rv = fscanf( epdl, "%2c%3c%3c%13c%9c%2c%37c", C, I, S, garbage, X1l, X1r, 
	       extra );
  
  reaction_type = atoi(C)*1000 + atoi(I);
  electron_shell = extractValue<int>( X1l, X1r );  
}

//! Skip two column table in EPDL file
void DataProcessorBase::skipTwoColumnTable( FILE* datafile )
{
  char line[24];
  line[0] = 'n';
  line[23] = '\0';
  char test[] = "                       ";
  char end_of_table[51];
  end_of_table[50] = '\0';
  int rv; // dummy return value for file reading

  while( strcmp( line, test ) != 0 )
    rv = fscanf( datafile, "%23c", line);

  // Read rest of end of table line
  rv = fscanf( datafile, "%50c", end_of_table );
}

//! Convert an EPDL shell integer to a shell name
std::string DataProcessorBase::intToShellStr( const int shell )
{
  testInvalidShell( shell > 0, 
		    "Invalid shell detected" );
  return ElectronShellStr[shell];
}

//---------------------------------------------------------------------------//
// LogLogDataProcessingPolicy definitions
//---------------------------------------------------------------------------//

//! Process Independent Variable
static inline double DataProcessorBase::LogLogDataProcessingPolicy::processIndependentVar( const double indep_var )
{
  if( indep_var > 0.0 )
    return log( indep_var );
  else
    return log( std::numeric_limits<double>::min() );
}

//! Process Dependent Variable
static inline double DataProcessorBase::LogLogDataProcessingPolicy::processDependentVar( const double dep_var )
{
  if( dep_var > 0.0 )
    return log( dep_var );
  else
    return log( std::numeric_limits<double>::min() );
}

//---------------------------------------------------------------------------//
// LinearLogDataProcessingPolicy definitions
//---------------------------------------------------------------------------//

//! Process Independent Variable
static inline double DataProcessorBase::LinearLogDataProcessingPolicy::processIndependentVar( const double indep_var )
{
  return indep_var;
}

//! Process Dependent Variable
static inline double DataProcessorBase::LinearLogDataProcessingPolicy::processDependentVar( const double dep_var )
{
  if( dep_var > 0.0 )
    return log( dep_var );
  else
    return log( std::numeric_limits<double>::min() );
}

//---------------------------------------------------------------------------//
// LogLinearDataProcessingPolicy definitions
//---------------------------------------------------------------------------//

//! Process Independent Variable
static inline double DataProcessorBase::LogLinearDataProcessingPolicy::processIndependentVar( const double indep_var )
{
  if( indep_var > 0.0 )
    return log( dep_var );
  else
    return log( std::numberic_limits<double>::min() );
}

//! Process Dependent Variable
static inline double DataProcessorBase::LogLinearDataProcessingPolicy::processDependentVar( const double dep_var )
{
  return dep_var;
}

//---------------------------------------------------------------------------//
// LinearLinearDataProcessingPolicy definitions
//---------------------------------------------------------------------------//

//! Process Independent Variable
static inline double DataProcessorBase::LinearLinearDataProcessingPolicy::processIndependentVar( const double indep_var )
{
  return indep_var;
}

//! Process Dependent Variable
static inline double DataProcessorBase::LinearLinearDataProcessingPolicy::processDependentVar( const double dep_var )
{
  return dep_var;
}

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end DataProcessorBase.cpp
//---------------------------------------------------------------------------//


