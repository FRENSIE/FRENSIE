//---------------------------------------------------------------------------//
//!
//! \file   Facemc_DistributedSource.hpp
//! \author Alex Robinson
//! \brief  Distributed source class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_DISTRIBUTED_SOURCE_HPP
#define FACEMC_DISTRIBUTED_SOURCE_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FACEMC Includes
#include "Facemc_ParticleSource.hpp"
#include "Utility_OneDDistribution.hpp"
#include "Utility_SpatialDistribution.hpp"
#include "Utility_DirectionalDistribution.hpp"
#include "Facemc_ParticleType.hpp"
#include "Facemc_ParticleBank.hpp"
#include "Geometry_ModuleTraits.hpp"
#include "Geometry_PointLocation.hpp"

namespace Facemc{

//! The distributed source class
class DistributedSource : public ParticleSource
{

private:
  
  // Typedef for scalar traits
  typedef Teuchos::ScalarTraits<double> ST;


public:

  //! Typedef for get particle location geometry module interface function
  typedef Geometry::PointLocation (*getLocationFunction)(const Geometry::Ray&, Geometry::ModuleTraits::InternalCellHandle );
  
  //! Constructor
  DistributedSource( 
	const Teuchos::RCP<Utility::SpatialDistribution>& spatial_distribution,
        const Teuchos::RCP<Utility::DirectionalDistribution>& 
	directional_distribution,
	const Teuchos::RCP<Utility::OneDDistribution>& 
	energy_distribution,
	const Teuchos::RCP<Utility::OneDDistribution>& 
	time_distribution,
	const ParticleType particle_type,
	getLocationFunction get_particle_location_func );

  //! Destructor
  ~DistributedSource()
  { /* ... */ }

  //! Set the spatial importance distribution
  void setSpatialImportanceDistribution( 
      const Teuchos::RCP<Utility::SpatialDistribution>& spatial_distribution );

  //! Set the directional importance distribution
  void setDirectionalImportanceDistribution(
                          const Teuchos::RCP<Utility::DirectionalDistribution>&
			  directional_distribution );

  //! Set the energy importance distribution
  void setEnergyImportanceDistribution(
	  const Teuchos::RCP<Utility::OneDDistribution>& energy_distribution );

  //! Set the time importance distribution
  void setTimeImportanceDistribution(
	    const Teuchos::RCP<Utility::OneDDistribution>& time_distribution );

  //! Set the rejection cell
  void setRejectionCell( 
		       const Geometry::ModuleTraits::InternalCellHandle& cell);

  //! Sample a particle state from the source
  void sampleParticleState( ParticleBank& bank );

  //! Get the sampling efficiency from the source distribution
  double getSamplingEfficiency() const;

private:

  // Sample the particle position
  void sampleParticlePosition( ParticleState& particle );

  // Sample the particle direction
  void sampleParticleDirection( ParticleState& particle );

  // Sample the particle energy
  void sampleParticleEnergy( ParticleState& particle );
  
  // Sample the particle time
  void sampleParticleTime( ParticleState& particle );

  // The spatial distribution of the source 
  Teuchos::RCP<Utility::SpatialDistribution> d_spatial_distribution;
  
  // The true spatial distribution of the source
  Teuchos::RCP<Utility::SpatialDistribution> d_spatial_importance_distribution;

  // The directional distribution
  Teuchos::RCP<Utility::DirectionalDistribution> d_directional_distribution;

  // The true directional distribution of the source
  Teuchos::RCP<Utility::DirectionalDistribution> 
  d_directional_importance_distribution;

  // The energy distribution
  Teuchos::RCP<Utility::OneDDistribution> d_energy_distribution;

  // The true energy distribution of the source
  Teuchos::RCP<Utility::OneDDistribution> d_energy_importance_distribution;

  // The time distribution
  Teuchos::RCP<Utility::OneDDistribution> d_time_distribution;

  // The true time distribution of the source
  Teuchos::RCP<Utility::OneDDistribution> d_time_importance_distribution;

  // The type of particle emitted
  ParticleType d_particle_type;

  // The cell handle of the cell used for rejection sampling of the position
  Geometry::ModuleTraits::InternalCellHandle d_rejection_cell;

  // The current history number
  unsigned long long d_history_number;

  // The number of trials
  unsigned d_number_of_trials;

  // The number of valid samples
  unsigned d_number_of_samples;

  // A pointer to the desired getParticleLocation geometry module function
  getLocationFunction d_get_particle_location_func;
};

} // end Facemc namespace

#endif // end FACEMC_DISTRIBUTED_SOURCE_HPP

//---------------------------------------------------------------------------//
// end Facemc_DistributedSource.hpp
//---------------------------------------------------------------------------//
