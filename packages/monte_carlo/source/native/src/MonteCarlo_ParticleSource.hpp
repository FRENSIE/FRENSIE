//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleSource.hpp
//! \author Alex Robinson
//! \brief  Particle source declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_SOURCE_HPP
#define MONTE_CARLO_PARTICLE_SOURCE_HPP

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_Comm.hpp>

// MonteCarlo Includes
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_PhaseSpaceDimension.hpp"
#include "MonteCarlo_ModuleTraits.hpp"
#include "Geometry_Model.hpp"
#include "Utility_HDF5FileHandler.hpp"

namespace MonteCarlo{

//! The particle source base class
class ParticleSource
{

public:

  //! Constructor
  ParticleSource();

  //! Destructor
  virtual ~ParticleSource()
  { /* ... */ }

  //! Get the source id
  virtual ModuleTraits::InternalROIHandle getId() const = 0;

  //! Enable thread support
  virtual void enableThreadSupport( const size_t threads ) = 0;

  //! Reset the source data
  virtual void resetData() = 0;

  //! Reduce the source data
  virtual void reduceData(
            const Teuchos::RCP<const Teuchos::Comm<unsigned long long> >& comm,
            const int root_process ) = 0;

  //! Export the source data
  virtual void exportData(
        const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file ) const = 0;

  //! Print a summary of the source data
  virtual void printSummary( std::ostream& os ) const = 0;

  //! Embed the source in the desired model
  void embedInModel( const std::shared_ptr<const Geometry::Model>& model );

  //! Sample a particle state from the source
  virtual void sampleParticleState( ParticleBank& bank,
				    const unsigned long long history ) = 0;

  //! Return the number of sampling trials
  virtual ModuleTraits::InternalCounter getNumberOfTrials() const = 0;

  //! Return the number of sampling trials in the phase space dimension
  virtual ModuleTraits::InternalCounter getNumberOfDimensionTrials(
                               const PhaseSpaceDimension dimension ) const = 0;

  //! Return the number of samples that have been generated
  virtual ModuleTraits::InternalCounter getNumberOfSamples() const = 0;

  //! Return the number of samples in the phase space dimension
  virtual ModuleTraits::InternalCounter getNumberOfDimensionSamples(
                               const PhaseSpaceDimension dimension ) const = 0;

  //! Return the sampling efficiency from the source
  virtual double getSamplingEfficiency() const = 0;

  //! Return the sampling efficiency in the phase space dimension
  virtual double getDimensionSamplingEfficiency(
                               const PhaseSpaceDimension dimension ) const = 0;

  //! Return the starting cells that have been cached
  virtual void getStaringCells( std::set<Geometry::ModuleTraits::InternalCellHandle>& starting_cells ) const = 0;

protected:

  //! Print a standard summary of the source data
  void printStandardSummary( const std::string& source_type,
                             const ModuleTraits::InternalCounter trials,
                             const ModuleTraits::InternalCounter samples,
                             const double efficiency,
                             std::ostream& os ) const;

  //! Print a standard summary of the source starting cells
  void printStandardStaringCellSummary(
           std::set<Geometry::ModuleTraits::InternalCellHandle> starting_cells,
           std::ostream& os ) const;

  //! Print a standard summary of the dimension data
  void printStandardDimensionSummary(
                                const std::string& dimension_distribution_type,
                                const PhaseSpaceDimension dimension,
                                const ModuleTraits::InternalCounter trials,
                                const ModuleTraits::InternalCounter samples,
                                const double efficiency,
                                std::ostream& os ) const;

  //! Get the model that this source is embedded in
  const Geometry::Model& getModel() const;

  //! Get the navigator for the model that this source is embedded in
  const Geometry::Navigator& getModelNavigator() const;

  //! Embed a particle in model
  void embedParticleInModel(
                  ParticleState& particle,
                  const Geometry::ModelTraits::InternalCellHandle cell ) const;

private:

  // The model that the source is embedded in
  std::shared_ptr<const Geometry::Model> d_model;

  // The navigator for the model that the source is embedded in
  std::shared_ptr<const Geometry::Navigator> d_navigator;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_SOURCE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleSource.hpp
//---------------------------------------------------------------------------//
