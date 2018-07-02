//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AceLaw7NuclearScatteringEnergyDistribution.hpp
//! \author Eli Moll
//! \brief  The law 7 scattering energy distribution class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ACE_LAW_7_NUCLEAR_SCATTERING_ENERGY_DISTRIBUTION_HPP
#define MONTE_CARLO_ACE_LAW_7_NUCLEAR_SCATTERING_ENERGY_DISTRIBUTION_HPP

// FRENSIE Includes
#include "MonteCarlo_NuclearScatteringEnergyDistribution.hpp"
#include "Utility_DesignByContract.hpp"
#include "Utility_TabularUnivariateDistribution.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_Vector.hpp"

namespace MonteCarlo{

/*! The law 7 scattering energy distribution class (Ace Law 7)
 * \ingroup ace_laws
 */
class AceLaw7NuclearScatteringEnergyDistribution : public NuclearScatteringEnergyDistribution
{

public:

  //! Typedef for the energy distribution
  typedef std::vector<std::pair<double,double> > EnergyDistribution;

  //! Constructor
  AceLaw7NuclearScatteringEnergyDistribution(
                                       EnergyDistribution& energy_distribution,
                                       double restriction_energy);

  //! Destructor
  ~AceLaw7NuclearScatteringEnergyDistribution()
  { /* ... */ }

  //! Sample a scattering energy
  double sampleEnergy( const double energy ) const override;

private:

  EnergyDistribution d_energy_distribution;

  double d_restriction_energy;

};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ACE_LAW_7_NUCLEAR_SCATTERING_ENERGY_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AceLaw7NuclearScatteringEnergyDistribution.hpp
//---------------------------------------------------------------------------//

