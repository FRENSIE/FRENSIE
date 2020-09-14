//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DiscretizedImportanceSampledParticleDistribution.cpp
//! \author Philip Britt
//! \brief  Discretized Importance Sampled Particle distribution class declaration
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_DiscretizedImportanceSampledParticleDistribution.hpp"

namespace MonteCarlo{

  //! Constructor (without specifics of which mesh elements are to be considered source)
  DiscretizedImportanceSampledParticleDistribution::DiscretizedImportanceSampledParticleDistribution( const std::string& name,
                                                                                                      const std::shared_ptr<const Utility::Mesh>& mesh,
                                                                                                      const std::vector<double>& energy_bin_bounds,
                                                                                                      const std::shared_ptr<const Utility::PQLAQuadrature>& direction_discretization)
  :ParticleDistribution(name),
   d_mesh(mesh),
   d_direction_discretization(direction_discretization),
   d_energy_discretization_boundaries(energy_bin_bounds)
  { /* ... */ }

    //! Constructor (with specifics of which mesh elements are to be considered source)
  DiscretizedImportanceSampledParticleDistribution::DiscretizedImportanceSampledParticleDistribution(const std::string& name,
                                                   const std::shared_ptr<const Utility::Mesh>& mesh,
                                                   const std::vector<Utility::Mesh::ElementHandle>& mesh_source_elements,
                                                   const std::vector<double>& energy_bin_bounds,
                                                   const std::shared_ptr<const Utility::PQLAQuadrature>& direction_discretization)
  :ParticleDistribution(name),
   d_mesh(mesh),
   d_direction_discretization(direction_discretization),
   d_energy_discretization_boundaries(energy_bin_bounds)
  { /* ... */ }

  std::string DiscretizedImportanceSampledParticleDistribution::getDimensionDistributionTypeName( const PhaseSpaceDimension dimension ) const
  {

  }

  bool DiscretizedImportanceSampledParticleDistribution::isSpatiallyUniform() const
  {

  }
  
  bool DiscretizedImportanceSampledParticleDistribution::isDirectionallyUniform() const
  {

  }

  void DiscretizedImportanceSampledParticleDistribution::initializeDimensionCounters( DiscretizedImportanceSampledParticleDistribution::DimensionCounterMap& trials ) const
  {

  }

  double DiscretizedImportanceSampledParticleDistribution::evaluate( const ParticleState& particle ) const
  {

  }

  void DiscretizedImportanceSampledParticleDistribution::sample( ParticleState& particle ) const
  {

  }

  void DiscretizedImportanceSampledParticleDistribution::sampleAndRecordTrials( ParticleState& particle,
                                                                                DiscretizedImportanceSampledParticleDistribution::DimensionCounterMap& trials ) const
  {

  }

  void DiscretizedImportanceSampledParticleDistribution::sampleWithDimensionValue( ParticleState& particle,
                                                                                   const PhaseSpaceDimension dimension,
                                                                                   const double dimension_value ) const
  {

  }

  void  DiscretizedImportanceSampledParticleDistribution::sampleWithDimensionValueAndRecordTrials(
                                      ParticleState& particle,
                                      DiscretizedImportanceSampledParticleDistribution::DimensionCounterMap& trials,
                                      const PhaseSpaceDimension dimension,
                                      const double dimension_value ) const
  {

  }
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_DiscretizedImportanceSampledParticleDistribution.cpp
//---------------------------------------------------------------------------//
