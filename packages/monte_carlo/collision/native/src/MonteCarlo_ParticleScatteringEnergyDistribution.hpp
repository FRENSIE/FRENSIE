//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleScatteringEnergyDistribution.hpp
//! \author Alex Robinson, Alex Bennett
//! \brief  The particle scattering energy distribution base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_SCATTERING_ENERGY_DISTRIBUTION
#define MONTE_CARLO_PARTICLE_SCATTERING_ENERGY_DISTRIBUTION

// Std Lib Includes
#include <limits>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"

namespace MonteCarlo{

//! The energy scattering distribution base class
class ParticleScatteringEnergyDistribution
{

public:

  //! Constructor
  ParticleScatteringEnergyDistribution( const unsigned law );

  //! Destructor
  virtual ~ParticleScatteringEnergyDistribution()
  { /* ... */ }

   //! Sample a scattering energy
  virtual double sampleEnergy( const double energy ) const = 0;

  //! Sample a scattering energy (and return the sampled bin index)
  virtual double sampleEnergy( const double energy, 
			       unsigned& incoming_bin_index,
			       unsigned& outgoing_bin_index,
                               double& energy_prime ) const;

  //! Return the scattering law
  unsigned getLaw() const;

private:

  // The endf law that this distribution represents
  unsigned d_law;
};

// Sample a scattering energy (and return the sampled bin index)
inline double ParticleScatteringEnergyDistribution::sampleEnergy( 
					    const double energy, 
					    unsigned& incoming_bin_index,
					    unsigned& outgoing_bin_index,
                                            double& energy_prime ) const
{
  incoming_bin_index = std::numeric_limits<unsigned>::max();
  
  outgoing_bin_index = std::numeric_limits<unsigned>::max();

  return this->sampleEnergy( energy );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_SCATTERING_ENERGY_DISTRIBUTION

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleScatteringEnergyDistribution.hpp
//---------------------------------------------------------------------------//
