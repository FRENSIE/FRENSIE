//---------------------------------------------------------------------------//
//!
//! \file   Facemc_NeutronScatteringEnergyDistribution.hpp
//! \author Alex Robinson, Alex Bennett
//! \brief  The neutron scattering energy distribution base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_NEUTRON_SCATTERING_ENERGY_DISTRIBUTION
#define FACEMC_NEUTRON_SCATTERING_ENERGY_DISTRIBUTION

// Std Lib Includes
#include <limits>

namespace Facemc{

//! The energy scattering distribution base class
class NeutronScatteringEnergyDistribution
{

public:

  //! Constructor
  NeutronScatteringEnergyDistribution( const bool is_cm_dist = false );

  //! Destructor
  virtual ~NeutronScatteringEnergyDistribution()
  { /* ... */ }

  //! Return if the distribution is for the CM energy
  bool isCMDistribution() const;

  //! Sample a scattering energy
  virtual double sampleEnergy( const double energy ) const = 0;

  //! Sample a scattering energy (and return the sampled bin index)
  virtual double sampleEnergy( const double energy, 
			       unsigned& sampled_bin_index ) const;

private:

  // Records if the energy distribution is for the cm energy
  bool d_is_cm_dist;
};

// Return if the distribution is for the CM energy
inline bool NeutronScatteringEnergyDistribution::isCMDistribution() const
{
  return d_is_cm_dist;
}

// Sample a scattering energy (and return the sampled bin index)
inline double NeutronScatteringEnergyDistribution::sampleEnergy( 
					    const double energy, 
					    unsigned& sampled_bin_index ) const
{
  sampled_bin_index = std::numeric_limits<unsigned>::max();
  
  return this->sampleEnergy( energy );
}

} // end Facemc namespace

#endif // end FACEMC_NEUTRON_SCATTERING_ENERGY_DISTRIBUTION

//---------------------------------------------------------------------------//
// end Facemc_NeutronScatteringEnergyDistribution.hpp
//---------------------------------------------------------------------------//
