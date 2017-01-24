//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleDistribution.hpp
//! \author Alex Robinson
//! \brief  Particle distribution declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_DISTRIBUTION_HPP
#define MONTE_CARLO_PARTICLE_DISTRIBUTION_HPP

// Std Lib Includes
#include <iostream>
#include <memory>

// Trilinos Includes
#include <Teuchos_Comm.hpp>

// FRENSIE Includes
#include "MonteCarlo_PhaseSpaceDimensionDistribution.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_ModuleTraits.hpp"
#include "Utility_HDF5FileHandler.hpp"

namespace MonteCarlo{

//! The particle distribution base class
class ParticleDistribution
{

public:

  //! The dimension trial counter map
  typedef PhaseSpaceDimensionDistribution::DimensionTrialCounterMap DimensionTrialCounterMap;

  //! Constructor
  ParticleDistribution( const ModuleTraits::InternalSourceHandle id,
                        const std::string& name )
  { /* ... */ }

  //! Destructor
  virtual ~ParticleDistribution()
  { /* ... */ }

  //! Return the id
  unsigned getId() const;

  //! Return the name of the region of interest
  const std::string& getName() const;

  //! Check if the distribution is spatially uniform (somewhere)
  virtual bool isSpatiallyUniform() const = 0;
  
  //! Check if the distribution is directionally uniform (isotropic)
  virtual bool isDirectionallyUniform() const = 0;

  //! Evaluate the distribution at the desired phase space point
  virtual double evaluate( const ParticleState& particle ) const = 0;

  //! Sample a particle state from the distribution
  virtual void sample( ParticleState& particle ) const = 0;

  //! Sample a particle state from the dist. and record the number of trials
  virtual void sampleAndRecordTrials(
                                  ParticleState& particle,
                                  DimensionTrialCounterMap& trials ) const = 0;

  //! Sample a particle state with the desired dimension value
  virtual void sampleWithDimensionValue(
                                      ParticleState& particle,
                                      const PhaseSpaceDimension dimension,
                                      const double dimension_value ) const = 0;

  //! Sample a particle state with the desired dim. value and record trials
  virtual void sampleWithDimensionValueAndRecordTrials(
                                      ParticleState& particle,
                                      DimensionTrialCounterMap& trials,
                                      const PhaseSpaceDimension dimension,
                                      const double dimension_value ) const = 0;

private:

  // The distribution id
  unsigned d_id;

  // The distribution name
  std::string d_name;
};
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleDistribution.hpp
//---------------------------------------------------------------------------//
