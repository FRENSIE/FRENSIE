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
                         MonteCarlo::HDF5FileHandler::OVERWRITE_FILE );

  //! Constructor (file sharing)
  SourceHDF5FileHandler(
                  const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file );

  //! Destructor
  ~SourceHDF5FileHandler()
  { /* ... */ }

  //! Check if a source exists
  bool doesSourceExist(
                       const ModuleTraits::InternalROIHandle source_id ) const;

  //! Check if a source dimension exists
  bool doesSourceDimensionExist(
                               const ModuleTraits::InternalROIHandle source_id,
                               const PhaseSpaceDimension dimension ) const;

  //! Set the number of source sampling trials
  void setNumberOfSourceSamplingTrials(
                           const ModuleTraits::InternalROIHandle source_id,
                           const Utility::DistributionTraits::Counter trials );

  //! Get the number of source sampling trials
  Utility::DistributionTraits::Counter getNumberOfSourceSamplingTrials(
                       const ModuleTraits::InternalROIHandle source_id ) const;

  //! Set the number of source samples
  void setNumberOfSourceSamples(
                          const ModuleTraits::InternalROIHandle source_id,
                          const Utility::DistributionTraits::Counter samples );

  //! Get the number of source samples
  Utility::DistributionTraits::Counter getNumberOfSourceSamples(
                        const ModuleTraits::InternalROIHandle source_id) const;

  //! Set the number of sampling trials in the source phase space dimension
  void setNumberOfSourceDimensionSamplingTrials(
                           const ModuleTraits::InternalROIHandle source_id,
                           const PhaseSpaceDimension dimension,
                           const Utility::DistributionTraits::Counter trials );

  //! Get the number of sampling trials in the source phase space dimension
  Utility::DistributionTraits::Counter getNumberOfSourceDimensionSamplingTrials(
                               const ModuleTraits::InternalROIHandle source_id,
                               const PhaseSpaceDimension dimension ) const;
                                             
  //! Set the number of samples in the phase space dimension
  void setNumberOfSourceDimensionSamples(
                          const ModuleTraits::InternalROIHandle source_id,
                          const PhaseSpaceDimension dimension,
                          const Utility::DistributionTraits::Counter samples );

  //! Get the number of samples in the phase space dimension
  Utility::DistributionTraits::Counter getNumberOfSourceDimensionSamples(
                               const ModuleTraits::InternalROIHandle source_id,
                               const PhaseSpaceDimension dimension ) const;

  //! Set the start cell cache
  template<template<typename,typename...> class StdCompliantSet>
  void setStartCellCache( const ModuleTraits::InternalROIHandle source_id,
                          const StdCompliantSet<Geometry::ModuleTraits::InternalCellHandle>& starting_cell_cache );

  //! Get the start cell cache
  template<template<typename,typename...> class StdCompliantSet>
  void getStartCellCache( const ModuleTraits::InternalROIHandle source_id,
                          StdCompliantSet<Geometry::ModuleTraits::InternalCellHandle>& starting_cell_cache );
  
private:

  // Get the source location
  std::string getSourceGroupLocation(
                       const ModuleTraits::InternalROIHandle source_id ) const;

  // Get the source dimension location
  std::string getSourceDimensionGroupLocation(
                               const ModuleTraits::InternalROIHandle source_id,
                               const PhaseSpaceDimension dimension ) const;

  // The source group root location and name
  static const std::string source_group_root_loc_name;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_SourceHDF5FileHandler_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_SOURCE_HDF5_FILE_HANDLER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SourceHDF5FileHandler.hpp
//---------------------------------------------------------------------------//
