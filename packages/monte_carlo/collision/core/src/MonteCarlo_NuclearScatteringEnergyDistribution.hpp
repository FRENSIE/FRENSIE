//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NuclearScatteringEnergyDistribution.hpp
//! \author Alex Robinson, Alex Bennett
//! \brief  The nuclear scattering energy distribution base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_NUCLEAR_SCATTERING_ENERGY_DISTRIBUTION
#define MONTE_CARLO_NUCLEAR_SCATTERING_ENERGY_DISTRIBUTION

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "Utility_UnivariateDistribution.hpp"

namespace MonteCarlo{

//! The energy scattering distribution base class
class NuclearScatteringEnergyDistribution
{

public:

  //! Constructor
  NuclearScatteringEnergyDistribution( const unsigned law );

  //! Destructor
  virtual ~NuclearScatteringEnergyDistribution()
  { /* ... */ }

   //! Sample a scattering energy
  virtual double sampleEnergy( const double energy ) const = 0;

  //! Sample a scattering energy (and return the sampled bin index)
  virtual double sampleEnergy( const double energy,
			       size_t& incoming_bin_index,
			       size_t& outgoing_bin_index,
                               double& energy_prime ) const;

  //! Return the scattering law
  unsigned getLaw() const;

  virtual void getDistribution();

private:

  // The endf law that this distribution represents
  unsigned d_law;
};

// Sample a scattering energy (and return the sampled bin index)
inline double NuclearScatteringEnergyDistribution::sampleEnergy(
					    const double energy,
					    size_t& incoming_bin_index,
					    size_t& outgoing_bin_index,
                                            double& energy_prime ) const
{
  incoming_bin_index = std::numeric_limits<size_t>::max();

  outgoing_bin_index = std::numeric_limits<size_t>::max();

  return this->sampleEnergy( energy );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_NUCLEAR_SCATTERING_ENERGY_DISTRIBUTION

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclearScatteringEnergyDistribution.hpp
//---------------------------------------------------------------------------//
