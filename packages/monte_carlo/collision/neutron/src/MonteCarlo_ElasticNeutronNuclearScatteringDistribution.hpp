//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElasticNeutronNuclearScatteringDistribution.hpp
//! \author Alex Robinson
//! \brief  The elastic scattering distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELASTIC_NUCLEAR_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_ELASTIC_NUCLEAR_SCATTERING_DISTRIBUTION_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_NuclearScatteringDistribution.hpp"
#include "MonteCarlo_NuclearScatteringAngularDistribution.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "Utility_UnivariateDistribution.hpp"
#include "Utility_Tuple.hpp"

namespace MonteCarlo{

//! The elastic scattering distribution class
class ElasticNeutronNuclearScatteringDistribution : public NuclearScatteringDistribution<NeutronState,NeutronState>
{

public:

  //! Constructor
  ElasticNeutronNuclearScatteringDistribution(
             const double atomic_weight_ratio,
             const double free_gas_threshold,
             const std::shared_ptr<const NuclearScatteringAngularDistribution>&
             angular_scattering_distribution );

  //! Destructor
  ~ElasticNeutronNuclearScatteringDistribution()
  { /* ... */ }

  //! Randomly scatter the particle
  void scatterParticle( const NeutronState& incoming_particle,
			NeutronState& outgoing_particle,
			const double temperature ) const override;

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
  void sampleTargetVelocity( const ParticleState& neutron,
			     const double temperature,
			     double target_velocity[3] ) const;

private:

  // Sample the speed of the target nucleus
  double sampleTargetSpeed( const ParticleState& neutron,
			    const double temperature ) const;

  // The free gas threshold
  double d_free_gas_threshold;

  // The incoming energy dependent angular scattering distribution
  std::shared_ptr<const NuclearScatteringAngularDistribution>
  d_angular_scattering_distribution;
};

// Calculate the center-of-mass velocity
inline void
ElasticNeutronNuclearScatteringDistribution::calculateCenterOfMassVelocity(
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
ElasticNeutronNuclearScatteringDistribution::transformVelocityToCenterOfMassFrame(
				       const double center_of_mass_velocity[3],
				       double velocity[3] ) const
{
  velocity[0] -= center_of_mass_velocity[0];
  velocity[1] -= center_of_mass_velocity[1];
  velocity[2] -= center_of_mass_velocity[2];
}

// Transform a velocity in the center-of-mass frame to the lab frame
inline void ElasticNeutronNuclearScatteringDistribution::transformVelocityToLabFrame(
				       const double center_of_mass_velocity[3],
				       double velocity[3] ) const
{
  velocity[0] += center_of_mass_velocity[0];
  velocity[1] += center_of_mass_velocity[1];
  velocity[2] += center_of_mass_velocity[2];
}


} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELASTIC_NUCLEAR_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElasticNeutronNuclearScatteringDistribution.hpp
//---------------------------------------------------------------------------//
