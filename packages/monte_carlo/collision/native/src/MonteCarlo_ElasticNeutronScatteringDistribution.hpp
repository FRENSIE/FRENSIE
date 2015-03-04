//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElasticNeutronScatteringDistribution.hpp
//! \author Alex Robinson
//! \brief  The elastic scattering distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELASTIC_NEUTRON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_ELASTIC_NEUTRON_SCATTERING_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_NeutronScatteringDistribution.hpp"
#include "MonteCarlo_ParticleScatteringAngularDistribution.hpp"
#include "Utility_OneDDistribution.hpp"
#include "Utility_Tuple.hpp"

namespace MonteCarlo{

//! The elastic scattering distribution class
class ElasticNeutronScatteringDistribution : public NeutronScatteringDistribution
{

public:
  
  //! Constructor
  ElasticNeutronScatteringDistribution( 
		     const double atomic_weight_ratio,
                     const Teuchos::RCP<ParticleScatteringAngularDistribution>&
		     angular_scattering_distribution );

  //! Destructor
  ~ElasticNeutronScatteringDistribution()
  { /* ... */ }
  
  //! Randomly scatter the neutron
  void scatterNeutron( NeutronState& neutron,
		       const double temperature ) const;

protected:
  
  //! Calculate the center-of-mass velocity
  void calculateCenterOfMassVelocity(const double neutron_velocity[3],
				     const double target_velocity[3],
				     double center_of_mass_velocity[3] ) const;

  //! Transform a velocity in lab frame to the center-of-mass frame
  void transformVelocityToCenterOfMassFrame( 
				       const double center_of_mass_velocity[3],
				       double velocity[3] ) const;

  //! Transform a velocity in the center-of-mass frame to the lab frame
  void transformVelocityToLabFrame( const double center_of_mass_velocity[3],
				    double velocity[3] ) const;

  //! Sample the velocity of the target nucleus
  void sampleTargetVelocity( ParticleState& neutron,
			     const double temperature,
			     double target_velocity[3] ) const;

private:

  // Sample the speed of the target nucleus
  double sampleTargetSpeed( ParticleState& neutron,
			    const double temperature ) const;

  // The incoming energy dependent angular scattering distribution
  Teuchos::RCP<ParticleScatteringAngularDistribution> 
  d_angular_scattering_distribution;
};

// Calculate the center-of-mass velocity
inline void 
ElasticNeutronScatteringDistribution::calculateCenterOfMassVelocity( 
				      const double neutron_velocity[3],
				      const double target_velocity[3],
				      double center_of_mass_velocity[3] ) const
{
  center_of_mass_velocity[0] = 
    (neutron_velocity[0] + this->getAtomicWeightRatio()*target_velocity[0])/
    (this->getAtomicWeightRatio() + 1.0);

  center_of_mass_velocity[1] = 
    (neutron_velocity[1] + this->getAtomicWeightRatio()*target_velocity[1])/
    (this->getAtomicWeightRatio() + 1.0);

  center_of_mass_velocity[2] = 
    (neutron_velocity[2] + this->getAtomicWeightRatio()*target_velocity[2])/
    (this->getAtomicWeightRatio() + 1.0);
}

// Transform a velocity in lab frame to the center-of-mass frame
inline void 
ElasticNeutronScatteringDistribution::transformVelocityToCenterOfMassFrame( 
				       const double center_of_mass_velocity[3],
				       double velocity[3] ) const
{
  velocity[0] -= center_of_mass_velocity[0];
  velocity[1] -= center_of_mass_velocity[1];
  velocity[2] -= center_of_mass_velocity[2];
}

// Transform a velocity in the center-of-mass frame to the lab frame
inline void ElasticNeutronScatteringDistribution::transformVelocityToLabFrame( 
				       const double center_of_mass_velocity[3],
				       double velocity[3] ) const
{
  velocity[0] += center_of_mass_velocity[0];
  velocity[1] += center_of_mass_velocity[1];
  velocity[2] += center_of_mass_velocity[2];
}


} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELASTIC_NEUTRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElasticNeutronScatteringDistribution.hpp
//---------------------------------------------------------------------------//
