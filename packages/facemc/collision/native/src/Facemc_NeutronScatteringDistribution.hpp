//---------------------------------------------------------------------------//
//!
//! \file   Facemc_NeutronScatteringDistribution.hpp
//! \author Alex Robinson
//! \brief  The neutron scattering distribution base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_NEUTRON_SCATTERING_DISTRIBUTION_HPP
#define FACEMC_NEUTRON_SCATTERING_DISTRIBUTION_HPP

// FRENSIE Includes
#include "Facemc_NeutronState.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_RandomNumberGenerator.hpp"

namespace Facemc{

//! The scattering distribution base class
class NeutronScatteringDistribution
{

public:

  //! Constructor 
  NeutronScatteringDistribution( const double atomic_weight_ratio );

  //! Destructor
  virtual ~NeutronScatteringDistribution()
  { /* ... */ }

  //! Set the free gas thermal treatment temperature threshold
  static void setFreeGasThermalTreatmentTemperatureThreshold( 
					  const double temperature_threshold );

  //! Randomly scatter the neutron
  virtual void scatterNeutron( NeutronState& neutron,
			       const double temperature ) const = 0;

protected:
  
  //! Return the atomic weight ratio
  double getAtomicWeightRatio() const;

  //! Sample an azimuthal angle from a uniform distribution
  double sampleAzimuthalAngle() const;

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

  //! Sample the speed of the target nucleus
  double sampleTargetSpeed( ParticleState& neutron,
			    const double temperature ) const;

  // The free gas thermal treatment temperature threshold
  static unsigned free_gas_threshold;

  // The atomic weight of the nuclide in units of neutron mass
  double d_atomic_weight_ratio;
};

// Return the atomic weight ratio
inline double 
NeutronScatteringDistribution::getAtomicWeightRatio() const
{
  return d_atomic_weight_ratio;
}

// Sample an azimuthal angle from a uniform distribution
inline double 
NeutronScatteringDistribution::sampleAzimuthalAngle() const
{
  return 2*Utility::PhysicalConstants::pi*
    Utility::RandomNumberGenerator::getRandomNumber<double>();
}

// Calculate the center-of-mass velocity
inline void 
NeutronScatteringDistribution::calculateCenterOfMassVelocity( 
				      const double neutron_velocity[3],
				      const double target_velocity[3],
				      double center_of_mass_velocity[3] ) const
{
  center_of_mass_velocity[0] = 
    (neutron_velocity[0] + d_atomic_weight_ratio*target_velocity[0])/
    (d_atomic_weight_ratio + 1.0);

  center_of_mass_velocity[1] = 
    (neutron_velocity[1] + d_atomic_weight_ratio*target_velocity[1])/
    (d_atomic_weight_ratio + 1.0);

  center_of_mass_velocity[2] = 
    (neutron_velocity[2] + d_atomic_weight_ratio*target_velocity[2])/
    (d_atomic_weight_ratio + 1.0);
}

// Transform a velocity in lab frame to the center-of-mass frame
inline void 
NeutronScatteringDistribution::transformVelocityToCenterOfMassFrame( 
				       const double center_of_mass_velocity[3],
				       double velocity[3] ) const
{
  velocity[0] -= center_of_mass_velocity[0];
  velocity[1] -= center_of_mass_velocity[1];
  velocity[2] -= center_of_mass_velocity[2];
}

// Transform a velocity in the center-of-mass frame to the lab frame
inline void NeutronScatteringDistribution::transformVelocityToLabFrame( 
				       const double center_of_mass_velocity[3],
				       double velocity[3] ) const
{
  velocity[0] += center_of_mass_velocity[0];
  velocity[1] += center_of_mass_velocity[1];
  velocity[2] += center_of_mass_velocity[2];
}

} // end Facemc namespace

#endif // end FACEMC_NEUTRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Facemc_NeutronScatteringDistribution.hpp
//---------------------------------------------------------------------------//
