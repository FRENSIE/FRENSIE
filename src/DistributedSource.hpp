//---------------------------------------------------------------------------//
//!
//! \file   DistributedSource.hpp
//! \author Alex Robinson
//! \brief  Distributed source class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef DISTRIBUTED_SOURCE_HPP
#define DISTRIBUTED_SOURCE_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FACEMC Includes
#include "ParticleSource.hpp"
#include "OneDDistribution.hpp"
#include "SpatialDistribution.hpp"
#include "DirectionalDistribution.hpp"
#include "ParticleType.hpp"
#include "GeometryHandlerTraits.hpp"

namespace FACEMC{

//! The distributed source class
template<typename GeometryHandler>
class DistributedSource : public ParticleSource
{

private:
  
  // Typedef for geometry handler traits
  typedef Traits::GeometryHandlerTraits<GeometryHandler> GHT;

  // Typedef for scalar traits
  typedef Teuchos::ScalarTraits<double> ST;

public:
  
  //! Constructor
  DistributedSource( 
	 const Teuchos::RCP<SpatialDistribution>& spatial_distribution,
	 const Teuchos::RCP<DirectionalDistribution>& directional_distribution,
	 const Teuchos::RCP<OneDDistribution>& energy_distribution,
	 const Teuchos::RCP<OneDDistribution>& time_distribution,
	 const ParticleType particle_type );

  //! Destructor
  ~DistributedSource()
  { /* ... */ }

  //! Set the spatial importance distribution
  void setSpatialImportanceDistribution( 
	       const Teuchos::RCP<SpatialDistribution>& spatial_distribution );

  //! Set the directional importance distribution
  void setDirectionalImportanceDistribution(
       const Teuchos::RCP<DirectionalDistribution>& directional_distribution );

  //! Set the energy importance distribution
  void setEnergyImportanceDistribution(
	           const Teuchos::RCP<OneDDistribution>& energy_distribution );

  //! Set the time importance distribution
  void setTimeImportanceDistribution(
		     const Teuchos::RCP<OneDDistribution>& time_distribution );

  //! Set the rejection cell
  template<typename CellHandle>
  void setRejectionCell( const CellHandle& cell );

  //! Sample a particle state from the source
  void sampleParticleState( BasicParticleState& particle );

  //! Get the sampling efficiency from the source distribution
  double getSamplingEfficiency() const;

private:

  // Sample the particle position
  void sampleParticlePosition( BasicParticleState& particle );

  // Sample the particle direction
  void sampleParticleDirection( BasicParticleState& particle );

  // Sample the particle energy
  void sampleParticleEnergy( BasicParticleState& particle );
  
  // Sample the particle time
  void sampleParticleTime( BasicParticleState& particle );

  // The spatial distribution of the source (possibly an importance dist.)
  Teuchos::RCP<SpatialDistribution> d_spatial_distribution;
  
  // The true spatial distribution of the source
  Teuchos::RCP<SpatialDistribution> d_spatial_importance_distribution;

  // The directional distribution
  Teuchos::RCP<DirectionalDistribution> d_directional_distribution;

  // The true directional distribution of the source
  Teuchos::RCP<DirectionalDistribution> d_directional_importance_distribution;

  // The energy distribution
  Teuchos::RCP<OneDDistribution> d_energy_distribution;

  // The true energy distribution of the source
  Teuchos::RCP<OneDDistribution> d_energy_importance_distribution;

  // The time distribution
  Teuchos::RCP<OneDDistribution> d_time_distribution;

  // The true time distribution of the source
  Teuchos::RCP<OneDDistribution> d_time_importance_distribution;

  // The type of particle emitted
  ParticleType d_particle_type;

  // The cell handle of the cell used for rejection sampling of the position
  typename GHT::CellHandle d_rejection_cell;

  // The number of trials
  unsigned d_number_of_trials;

  // The number of valid samples
  unsigned d_number_of_samples;
};

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "DistributedSource_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DISTRIBUTED_SOURCE_HPP

//---------------------------------------------------------------------------//
// end DistributedSource.hpp
//---------------------------------------------------------------------------//
