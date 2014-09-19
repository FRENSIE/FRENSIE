//---------------------------------------------------------------------------//
//! 
//! \file   MonteCarlo_AceLaw3NeutronScatteringEnergyDistribution.hpp
//! \author Alex Robinson, Alex Bennett
//! \brief  The neutron inelastic level scattering energy distribution class
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_ACE_LAW_3_NEUTRON_SCATTERING_ENERGY_DISTRIBUTION_HPP
#define FACEMC_ACE_LAW_3_NEUTRON_SCATTERING_ENERGY_DISTRIBUTION_HPP

// FRENSIE Includes
#include "MonteCarlo_NeutronScatteringEnergyDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

/*! The inelastic level scattering energy distribution class (ENDF Law 3)
 * \ingroup ace_laws
 */
class AceLaw3NeutronScatteringEnergyDistribution : public NeutronScatteringEnergyDistribution
{

public:
  
  //! Constructor
  AceLaw3NeutronScatteringEnergyDistribution( const double param_a,
						     const double param_b );
  
  //! Destructor
  ~AceLaw3NeutronScatteringEnergyDistribution()
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

#endif // end FACEMC_ACE_LAW_3_NEUTRON_SCATTERING_ENERGY_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AceLaw3NeutronScatteringEnergyDistribution.hpp
//---------------------------------------------------------------------------//
