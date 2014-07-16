//---------------------------------------------------------------------------//
//! 
//! \file   Facemc_InelasticLevelNeutronScatteringEnergyDistribution.hpp
//! \author Alex Robinson, Alex Bennett
//! \brief  The neutron inelastic level scattering energy distribution class
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_INELASTIC_LEVEL_NEUTRON_SCATTERING_ENERGY_DISTRIBUTION
#define FACEMC_INELASTIC_LEVEL_NEUTRON_SCATTERING_ENERGY_DISTRIBUTION

// FRENSIE Includes
#include "Facemc_NeutronScatteringEnergyDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace Facemc{

//! The inelastic level scattering energy distribution class (ENDF Law 3)
class InelasticLevelNeutronScatteringEnergyDistribution : public NeutronScatteringEnergyDistribution
{

public:
  
  //! Constructor
  InelasticLevelNeutronScatteringEnergyDistribution( const double param_a,
						     const double param_b );
  
  //! Destructor
  ~InelasticLevelNeutronScatteringEnergyDistribution()
  { /* ... */ }
  
  //! Sample a scattering energy
  double sampleEnergy( const double energy ) const;

private:

  // (A+1)/A * |Q|
  double d_param_a;
  
  // (A/(A+1))^2
  double d_param_b;
};

} // end Facemc namespace

#endif // end FACEMC_INELASTIC_LEVEL_NEUTRON_SCATTERING_ENERGY_DISTRIBUTION

//---------------------------------------------------------------------------//
// end Facemc_InelasticLevelNeutronScatteringEnergyDistribution.hpp
//---------------------------------------------------------------------------//
