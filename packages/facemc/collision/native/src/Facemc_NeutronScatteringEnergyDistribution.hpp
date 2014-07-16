//---------------------------------------------------------------------------//
//!
//! \file   Facemc_NeutronScatteringEnergyDistribution.hpp
//! \author Alex Robinson, Alex Bennett
//! \brief  The neutron scattering energy distribution base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_NEUTRON_SCATTERING_ENERGY_DISTRIBUTION
#define FACEMC_NEUTRON_SCATTERING_ENERGY_DISTRIBUTION

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

private:

  // Records if the energy distribution is for the cm energy
  bool d_is_cm_dist;
};

// Return if the distribution is for the CM energy
inline bool NeutronScatteringEnergyDistribution::isCMDistribution() const
{
  return d_is_cm_dist;
}

} // end Facemc namespace

#endif // end FACEMC_NEUTRON_SCATTERING_ENERGY_DISTRIBUTION

//---------------------------------------------------------------------------//
// end Facemc_NeutronScatteringEnergyDistribution.hpp
//---------------------------------------------------------------------------//
