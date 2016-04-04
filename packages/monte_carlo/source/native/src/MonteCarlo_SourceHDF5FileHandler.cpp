//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SourceHDF5FileHandler.cpp
//! \author Alex Robinson
//! \brief  Source HDF5 file handler class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <sstream>

// FRENSIE Includes
#include "MonteCarlo_SourceHDF5FileHandler.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Initialize static member data
const std::string SourceHDF5FileHandler::source_group_loc_name( "/Source/" );

// Constructor (file ownership)
/*! \details The EstimatorHDF5FileOps enum will determine how the HDF5 file
 * is opened. If the read only option is used, calling any of the set
 * methods will result in an exception.
 */
SourceHDF5FileHandler::SourceHDF5FileHandler(
                                             const std::string& hdf5_file_name,
                                             const SourceHDF5FileOps file_op )
  : d_hdf5_file( new Utility::HDF5FileHandler ),
    d_hdf5_file_ownership( true )
{
  // Make sure the name is valid
  testPrecondition( hdf5_file_name.size() > 0 );

  Utility::HDF5FileHandler::throwExceptions();

  try{
    switch( file_op )
    {
    case OVERWRITE_SOURCE_HDF5_FILE:
      d_hdf5_file->openHDF5FileAndOverwrite( hdf5_file_name );
      break;
    case APPEND_SOURCE_HDF5_FILE:
      d_hdf5_file->openHDF5FileAndAppend( hdf5_file_name );
      break;
    case READ_ONLY_SOURCE_HDF5_FILE:
      d_hdf5_file->openHDF5FileAndReadOnly( hdf5_file_name );
      break;
    }
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
                           "Error: Unable to construct the source HDF5 file "
                           "handler!" );
  
}

// Constructor (file sharing)
SourceHDF5FileHandler::SourceHDF5FileHandler(
                   const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file )
  : d_hdf5_file( hdf5_file ),
    d_hdf5_file_ownership( false )
{
  // Make sure the file is valid
  testPrecondition( hdf5_file.get() );
  testPrecondition( hdf5_file->hasOpenFile() );
  
  Utility::HDF5FileHandler::throwExceptions();
}

// Destructor
SourceHDF5FileHandler::~SourceHDF5FileHandler()
{
  if( d_hdf5_file_ownership )
    d_hdf5_file->closeHDF5File();
}

// Check if a source exists
bool SourceHDF5FileHandler::doesSourceExist( const unsigned source_id ) const
{
  return d_hdf5_file->doesGroupExist( 
                                   this->getSourceGroupLocation( source_id ) );
}

// Set the number of source sampling trials
void SourceHDF5FileHandler::setNumberOfSourceSamplingTrials( 
                                              const unsigned source_id,
                                              const unsigned long long trials )
{
  std::string group_location = 
    this->getSourceGroupLocation( source_id );
  
  try{
    d_hdf5_file->writeValueToGroupAttribute( trials, 
                                             group_location, 
                                             "trials" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Error: Unable to set the number of trials for "
                           "source " << source_id << "!" );
}

// Get the number of source sampling trials
unsigned long long SourceHDF5FileHandler::getNumberOfSourceSamplingTrials( 
                                               const unsigned source_id ) const
{
  std::string group_location = 
    this->getSourceGroupLocation( source_id );

  unsigned long long trials;

  try{
    d_hdf5_file->readValueFromGroupAttribute( trials, 
                                              group_location,
                                              "trials" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Error: Unable to get the number of trials for "
                           "source" << source_id << "!" );

  return trials;
}

// Set the number of default source sampling trials
void SourceHDF5FileHandler::setNumberOfDefaultSourceSamplingTrials( 
                                              const unsigned long long trials )
{
  std::string group_location = 
    SourceHDF5FileHandler::source_group_loc_name;

  try{
    d_hdf5_file->writeValueToGroupAttribute( trials, 
                                             group_location, 
                                             "trials" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Error: Unable to set the number of trials for "
                           "the default source!" );
}

// Get the number of default source sampling trials
unsigned long long 
SourceHDF5FileHandler::getNumberOfDefaultSourceSamplingTrials() const
{
  std::string group_location = 
    SourceHDF5FileHandler::source_group_loc_name;

  unsigned long long trials;

  try{
    d_hdf5_file->readValueFromGroupAttribute( trials, 
                                              group_location, 
                                              "trials" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Error: Unable to get the number of trials for "
                           "the default source!" );

  return trials;
}


// Set the number of source samples
void SourceHDF5FileHandler::setNumberOfSourceSamples( 
                                             const unsigned source_id,
                                             const unsigned long long samples )
{
  std::string group_location = 
    this->getSourceGroupLocation( source_id );
  
  try{
    d_hdf5_file->writeValueToGroupAttribute( samples, 
                                             group_location,
                                             "samples" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Error: Unable to set the number of samples for "
                           "source " << source_id << "!" );
}

// Get the number of source samples
unsigned long long SourceHDF5FileHandler::getNumberOfSourceSamples( 
                                               const unsigned source_id ) const
{
  std::string group_location = 
    this->getSourceGroupLocation( source_id );

  unsigned long long samples;
  
  try{
    d_hdf5_file->readValueFromGroupAttribute( samples, 
                                              group_location,
                                              "samples" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Error: Unable to get the number of samples for "
                           "source " << source_id << "!" );

  return samples;
}

// Set the number of default source samples
void SourceHDF5FileHandler::setNumberOfDefaultSourceSamples( 
                                             const unsigned long long samples )
{
  std::string group_location = 
    SourceHDF5FileHandler::source_group_loc_name;
  
  try{
    d_hdf5_file->writeValueToGroupAttribute( samples, 
                                             group_location,
                                             "samples" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Error: Unable to set the number of samples for "
                           "the default source!" );
}

// Get the number of default source samples
unsigned long long 
SourceHDF5FileHandler::getNumberOfDefaultSourceSamples() const
{
  std::string group_location = 
    SourceHDF5FileHandler::source_group_loc_name;

  unsigned long long samples;
  
  try{
    d_hdf5_file->readValueFromGroupAttribute( samples, 
                                              group_location,
                                              "samples" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error, 
			   "Error: Unable to get the number of samples for "
                           "the default source!" );

  return samples;
}

// Get the source location
std::string SourceHDF5FileHandler::getSourceGroupLocation( 
                                               const unsigned source_id ) const
{
  std::ostringstream oss;
  oss << SourceHDF5FileHandler::source_group_loc_name;
  oss << source_id << "/";

  return oss.str();
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_SourceHDF5FileHandler.cpp
//---------------------------------------------------------------------------//
