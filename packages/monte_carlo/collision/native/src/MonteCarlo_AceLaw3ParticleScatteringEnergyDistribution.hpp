//---------------------------------------------------------------------------//
//! 
//! \file   MonteCarlo_AceLaw3ParticleScatteringEnergyDistribution.hpp
//! \author Alex Robinson, Alex Bennett
//! \brief  The particle inelastic level scattering energy distribution class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ACE_LAW_3_PARTICLE_SCATTERING_ENERGY_DISTRIBUTION_HPP
#define MONTE_CARLO_ACE_LAW_3_PARTICLE_SCATTERING_ENERGY_DISTRIBUTION_HPP

// FRENSIE Includes
#include "MonteCarlo_ParticleScatteringEnergyDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

/*! The inelastic level scattering energy distribution class (ENDF Law 3)
 * \ingroup ace_laws
 */
class AceLaw3ParticleScatteringEnergyDistribution : public ParticleScatteringEnergyDistribution
{

public:
  
  //! Constructor
  AceLaw3ParticleScatteringEnergyDistribution( const double param_a,
					       const double param_b );
  
  //! Destructor
  ~AceLaw3ParticleScatteringEnergyDistribution()
  { /* ... */ }
  
  //! Sample a scattering energy
  double sampleEnergy( const double energy ) const;

private:

  // (A+1)/A * |Q|
  double d_param_a;
  
  // (A/(A+1))^2
  double d_param_b;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ACE_LAW_3_PARTICLE_SCATTERING_ENERGY_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AceLaw3ParticleScatteringEnergyDistribution.hpp
//---------------------------------------------------------------------------//
