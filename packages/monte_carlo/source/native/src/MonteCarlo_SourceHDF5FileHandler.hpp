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
#include "MonteCarlo_PhaseSpaceDimension.hpp"
#include "MonteCarlo_ModuleTraits.hpp"
#include "MonteCarlo_HDF5FileHandler.hpp"
#include "Utility_HDF5FileHandler.hpp"

namespace MonteCarlo{

//! The source hdf5 file handler
class SourceHDF5FileHandler : public MonteCarlo::HDF5FileHandler
{

public:

  //! Constructor (file ownership)
  SourceHDF5FileHandler( const std::string& hdf5_file_name,
                         const MonteCarlo::HDF5FileHandler::FileOps file_op =
                         OVERWRITE_SOURCE_HDF5_FILE );

  //! Constructor (file sharing)
  SourceHDF5FileHandler(
                  const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file );

  //! Destructor
  ~SourceHDF5FileHandler()
  { /* ... */ }

  //! Check if a source exists
  bool doesSourceExist( const InternalROIHandle source_id ) const;

  //! Check if a source dimension exists
  bool doesSourceDimenionExist( const InternalROIHandle source_id,
                                const PhaseSpaceDimension dimension ) const;

  //! Set the number of source sampling trials
  void setNumberOfSourceSamplingTrials( const InternalROIHandle source_id,
                                        const InternalCounter trials );

  //! Get the number of source sampling trials
  InternalCounter getNumberOfSourceSamplingTrials(
                                     const InternalROIHandle source_id ) const;

  //! Set the number of source samples
  void setNumberOfSourceSamples( const InternalROIHandle source_id,
                                 const InternalCounter samples );

  //! Get the number of source samples
  InternalCounter getNumberOfSourceSamples(
                                      const InternalROIHandle source_id) const;

  //! Set the number of sampling trials in the source phase space dimension
  void setNumberOfSourceDimensionSamplingTrials(
                                           const InternalROIHandle source_id,
                                           const PhaseSpaceDimension dimension,
                                           const InternalCounter trials );

  //! Get the number of sampling trials in the source phase space dimension
  InternalCounter getNumberOfSourceDimensionSamplingTrials(
                                   const InternalROIHandle source_id,
                                   const PhaseSpaceDimension dimension ) const;
                                             
  //! Set the number of samples in the phase space dimension
  void setNumberOfSourceDimensionSamples(
                                         const InternalROIHandle source_id,
                                         const PhaseSpaceDimension dimension,
                                         const InternalCounter samples );

  //! Get the number of samples in the phase space dimension
  InternalCounter getNumberOfSourceDimensionSamples(
                                   const InternalROIHandle source_id,
                                   const PhaseSpaceDimension dimension ) const;
  
private:

  // Get the source location
  std::string getSourceGroupLocation( const InternalROIHandle source_id ) const;

  // Get the source dimension location
  std::string getSourceDimensionGroupLocation(
                                   const InternalROIHandle source_id,
                                   const PhaseSpaceDimension dimension ) const;

  // The source group root location and name
  static const std::string source_group_root_loc_name;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_SOURCE_HDF5_FILE_HANDLER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SourceHDF5FileHandler.hpp
//---------------------------------------------------------------------------//
