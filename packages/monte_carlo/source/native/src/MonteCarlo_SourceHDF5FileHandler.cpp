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
/*! \details The MonteCarlo::HDF5FileHandler::FileOps enum will determine how 
 * the HDF5 file is opened. If the read only option is used, calling any of the
 * set methods will result in an exception.
 */
SourceHDF5FileHandler::SourceHDF5FileHandler(
                                             const std::string& hdf5_file_name,
                                             const SourceHDF5FileOps file_op )
  : MonteCarlo::HDF5FileHandler( hdf5_file_name, file_op )
{ /* ... */ }

// Constructor (file sharing)
SourceHDF5FileHandler::SourceHDF5FileHandler(
                   const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file )
  : MonteCarlo::HDF5FileHandler( hdf5_file )
{ /* ... */ }

// Check if a source exists
bool SourceHDF5FileHandler::doesSourceExist(
                                      const InternalROIHandle source_id ) const
{
  return this->getHDF5File().doesGroupExist(
                                   this->getSourceGroupLocation( source_id ) );
}

// Check if a source dimension exists
bool SourceHDF5FileHandler::doesSourceDimenionExist(
                                    const InternalROIHandle source_id,
                                    const PhaseSpaceDimension dimension ) const
{
  return this->getHDF5File().doesGroupExist(
               this->getSourceDimensionGroupLocation( source_id, dimension ) );
}

// Set the number of source sampling trials
void SourceHDF5FileHandler::setNumberOfSourceSamplingTrials(
                                             const InternalROIHandle source_id,
                                             const InternalCounter trials )
{
  std::string group_location =
    this->getSourceGroupLocation( source_id );

  try{
    this->getHDF5File().writeValueToGroupAttribute(
                                            trials, group_location, "trials" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Error: Unable to set the number of trials for "
                           "source " << source_id << "!" );
}

// Get the number of source sampling trials
TrialCounter SourceHDF5FileHandler::getNumberOfSourceSamplingTrials(
                                      const InternalROIHandle source_id ) const
{
  std::string group_location = this->getSourceGroupLocation( source_id );

  InternalCounter trials;

  try{
    this->getHDF5File().readValueFromGroupAttribute(
                                            trials, group_location, "trials" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Error: Unable to get the number of trials for "
                           "source" << source_id << "!" );

  return trials;
}


// Set the number of source samples
void SourceHDF5FileHandler::setNumberOfSourceSamples(
                                             const InternalROIHandle source_id,
                                             const InternalCounter samples )
{
  std::string group_location =
    this->getSourceGroupLocation( source_id );

  try{
    this->getHDF5File().writeValueToGroupAttribute(
                                          samples, group_location, "samples" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Error: Unable to set the number of samples for "
                           "source " << source_id << "!" );
}

// Get the number of source samples
InternalCounter SourceHDF5FileHandler::getNumberOfSourceSamples(
                                      const InternalROIHandle source_id ) const
{
  std::string group_location =
    this->getSourceGroupLocation( source_id );

  InternalCounter samples;

  try{
    this->getHDF5File().readValueFromGroupAttribute(
                                          samples, group_location, "samples" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Error: Unable to get the number of samples for "
                           "source " << source_id << "!" );

  return samples;
}
  
// Set the number of sampling trials in the source phase space dimension
void SourceHDF5FileHandler::setNumberOfSourceDimensionSamplingTrials(
                                           const InternalROIHandle source_id,
                                           const PhaseSpaceDimension dimension,
                                           const InternalCounter trials )
{
  std::string group_location =
    this->getSourceDimensionGroupLocation( source_id, dimension );

  try{
    this->getHDF5File().writeValueToGroupAttribute(
                                          trials, group_location, "trials" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Error: Unable to set the number of trials for "
                           "source " << source_id << " dimension "
                           << dimension << "!" );
}

// Get the number of sampling trials in the source phase space dimension
InternalCounter
SourceHDF5FileHandler::getNumberOfSourceDimensionSamplingTrials(
                                    const InternalROIHandle source_id,
                                    const PhaseSpaceDimension dimension ) const
{
  std::string group_location =
    this->getSourceDimensionGroupLocation( source_id, dimension );

  InternalCounter trials;

  try{
    this->getHDF5File().readValueFromGroupAttribute(
                                          trials, group_location, "trials" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Error: Unable to get the number of trials for "
                           "source " << source_id << " dimension "
                           << dimension << "!" );

  return trials;
}
                                             
// Set the number of samples in the phase space dimension
void SourceHDF5FileHandler::setNumberOfSourceDimensionSamples(
                                          const InternalROIHandle source_id,
                                          const PhaseSpaceDimension dimension,
                                          const InternalCounter samples )
{
  std::string group_location =
    this->getSourceDimensionGroupLocation( source_id, dimension );

  try{
    this->getHDF5File().writeValueToGroupAttribute(
                                          samples, group_location, "samples" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Error: Unable to set the number of samples for "
                           "source " << source_id << " dimension "
                           << dimension << "!" );
}

// Get the number of samples in the phase space dimension
InternalCounter SourceHDF5FileHandler::getNumberOfSourceDimensionSamples(
                                    const InternalROIHandle source_id,
                                    const PhaseSpaceDimension dimension ) const
{
  std::string group_location =
    this->getSourceDimensionGroupLocation( source_id, dimension );

  InternalCounter samples;

  try{
    this->getHDF5File().readValueFromGroupAttribute(
                                          samples, group_location, "samples" );
  }
  EXCEPTION_CATCH_RETHROW( std::runtime_error,
			   "Error: Unable to get the number of samples for "
                           "source " << source_id << " dimension "
                           << dimension << "!" );

  return samples;
}

// Get the source location
std::string SourceHDF5FileHandler::getSourceGroupLocation(
                                      const InternalROIHandle source_id ) const
{
  std::ostringstream oss;
  oss << SourceHDF5FileHandler::source_group_loc_name;
  oss << source_id << "/";

  return oss.str();
}

// Get the source dimension location
std::string SourceHDF5FileHandler::getSourceDimensionGroupLocation(
                                    const InternalROIHandle source_id,
                                    const PhaseSpaceDimension dimension ) const
{
  std::string location = this->getSourceGroupLocation();
  
  location += convertPhaseSpaceDimensionEnumToBasicString( dimension );
  location += "/";

  return location;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_SourceHDF5FileHandler.cpp
//---------------------------------------------------------------------------//
