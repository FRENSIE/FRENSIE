//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SourceHDF5FileHandler.hpp
//! \author Alex Robinson
//! \brief  Source HDF5 file handler class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SOURCE_HDF5_FILE_HANDLER_HPP
#define MONTE_CARLO_SOURCE_HDF5_FILE_HANDLER_HPP

// Std Lib Includes
#include <memory>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Utility_HDF5FileHandler.hpp"

namespace MonteCarlo{

//! The source hdf5 file handler
class SourceHDF5FileHandler
{

public:
  
  //! Enum for file operations
  enum SourceHDF5FileOps{
    OVERWRITE_SOURCE_HDF5_FILE = 0,
    APPEND_SOURCE_HDF5_FILE,
    READ_ONLY_SOURCE_HDF5_FILE
  };

  //! Constructor (file ownership)
  SourceHDF5FileHandler(
                const std::string& hdf5_file_name,
                const SourceHDF5FileOps file_op = OVERWRITE_SOURCE_HDF5_FILE );

  //! Constructor (file sharing)
  SourceHDF5FileHandler(
                  const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file );

  //! Destructor
  ~SourceHDF5FileHandler();

  //! Check if a source exists
  bool doesSourceExist( const unsigned source_id ) const;

  //! Set the number of source sampling trials
  void setNumberOfSourceSamplingTrials( const unsigned source_id,
                                        const unsigned long long trials );

  //! Get the number of source sampling trials
  unsigned long long getNumberOfSourceSamplingTrials( 
                                              const unsigned source_id ) const;
  
  //! Set the number of default source sampling trials
  void setNumberOfDefaultSourceSamplingTrials( 
                                             const unsigned long long trials );

  //! Get the number of default source sampling trials
  unsigned long long getNumberOfDefaultSourceSamplingTrials() const;

  //! Set the number of source samples
  void setNumberOfSourceSamples( const unsigned source_id,
                                 const unsigned long long samples );

  //! Get the number of source samples
  unsigned long long getNumberOfSourceSamples( const unsigned source_id) const;

  //! Set the number of default source samples
  void setNumberOfDefaultSourceSamples( const unsigned long long samples );

  //! Get the number of default source samples
  unsigned long long getNumberOfDefaultSourceSamples() const;

private:
  
  // Get the source location
  std::string getSourceGroupLocation( const unsigned source_id ) const;

  // The source group location and name
  static const std::string source_group_loc_name;

  // The HDF5 file handler
  std::shared_ptr<Utility::HDF5FileHandler> d_hdf5_file;

  // The ownership flag
  bool d_hdf5_file_ownership;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_SOURCE_HDF5_FILE_HANDLER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SourceHDF5FileHandler.hpp
//---------------------------------------------------------------------------//
