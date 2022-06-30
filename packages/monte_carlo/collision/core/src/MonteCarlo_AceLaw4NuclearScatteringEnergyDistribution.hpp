//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AceLaw4NuclearScatteringEnergyDistribution.hpp
//! \author Alex Bennett, Eli Moll
//! \brief  The law 4 scattering energy distribution class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ACE_LAW_4_NUCLEAR_SCATTERING_ENERGY_DISTRIBUTION_HPP
#define MONTE_CARLO_ACE_LAW_4_NUCLEAR_SCATTERING_ENERGY_DISTRIBUTION_HPP

// FRENSIE Includes
#include "MonteCarlo_NuclearScatteringEnergyDistribution.hpp"
#include "Utility_TabularUnivariateDistribution.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_Vector.hpp"

namespace MonteCarlo{

/*! The law 4 scattering energy distribution class (Ace Law 4)
 * \ingroup ace_laws
 */
class AceLaw4NuclearScatteringEnergyDistribution : public NuclearScatteringEnergyDistribution
{

public:

  //! Typedef for the energy distribution
  typedef std::vector<std::pair<double,std::shared_ptr<const Utility::TabularUnivariateDistribution> > >
                                                        EnergyDistribution;
  //! Constructor
  AceLaw4NuclearScatteringEnergyDistribution(
				     EnergyDistribution& energy_distribution );

  //! Destructor
  ~AceLaw4NuclearScatteringEnergyDistribution()
  { /* ... */ }

  //! Sample a scattering energy
  double sampleEnergy( const double energy ) const override;

  //! Sample a scattering energy
  double sampleEnergy( const double energy,
                       size_t& incoming_index,
                       size_t& outgoing_index,
                       double& energy_prime ) const override;

  void getDistribution( AceLaw4NuclearScatteringEnergyDistribution::EnergyDistribution& energy_distribution );

  EnergyDistribution d_energy_distribution;

};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ACE_LAW_4_NUCLEAR_SCATTERING_ENERGY_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AceLaw4NuclearScatteringEnergyDistribution.hpp
//---------------------------------------------------------------------------//

