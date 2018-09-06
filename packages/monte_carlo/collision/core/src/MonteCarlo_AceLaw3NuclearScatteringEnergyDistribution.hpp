//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AceLaw3NuclearScatteringEnergyDistribution.hpp
//! \author Alex Robinson, Alex Bennett
//! \brief  The nuclear inelastic level scattering energy distribution class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ACE_LAW_3_NUCLEAR_SCATTERING_ENERGY_DISTRIBUTION_HPP
#define MONTE_CARLO_ACE_LAW_3_NUCLEAR_SCATTERING_ENERGY_DISTRIBUTION_HPP

// FRENSIE Includes
#include "MonteCarlo_NuclearScatteringEnergyDistribution.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

/*! The inelastic level scattering energy distribution class (ENDF Law 3)
 * \ingroup ace_laws
 */
class AceLaw3NuclearScatteringEnergyDistribution : public NuclearScatteringEnergyDistribution
{

public:

  //! Constructor
  AceLaw3NuclearScatteringEnergyDistribution( const double param_a,
					       const double param_b );

  //! Destructor
  ~AceLaw3NuclearScatteringEnergyDistribution()
  { /* ... */ }

  //! Sample a scattering energy
  double sampleEnergy( const double energy ) const override;

private:

  // (A+1)/A * |Q|
  double d_param_a;

  // (A/(A+1))^2
  double d_param_b;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ACE_LAW_3_NUCLEAR_SCATTERING_ENERGY_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AceLaw3NuclearScatteringEnergyDistribution.hpp
//---------------------------------------------------------------------------//
