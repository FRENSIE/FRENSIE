//---------------------------------------------------------------------------//
//! 
//! \file   MonteCarlo_AceLaw7NuclearScatteringEnergyDistribution.hpp
//! \author Eli Moll
//! \brief  The law 9 scattering energy distribution class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ACE_LAW_9_NUCLEAR_SCATTERING_ENERGY_DISTRIBUTION_HPP
#define MONTE_CARLO_ACE_LAW_9_NUCLEAR_SCATTERING_ENERGY_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayRCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_NuclearScatteringEnergyDistribution.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_Tuple.hpp"

namespace MonteCarlo{

/*! The law 9 scattering energy distribution class (Ace Law 9)
 * \ingroup ace_laws
 */
class AceLaw9NuclearScatteringEnergyDistribution : public NuclearScatteringEnergyDistribution
{

public:

  //! Typedef for the energy distribution
  typedef Teuchos::Array<Utility::Pair<double,Teuchos::RCP<Utility::TabularOneDDistribution> > >
                                                        EnergyDistribution;

  //! Constructor
  AceLaw7NuclearScatteringEnergyDistribution(
                                          EnergyDistribution& energy_distribution,
                                          double restriction_energy);

  //! Destructor
  ~AceLaw7NuclearScatteringEnergyDistribution()
  { /* ... */ }

  //! Sample a scattering energy
  double sampleEnergy( const double energy ) const;

private:

  EnergyDistribution d_energy_distribution;
  
  double d_restriction_energy;

};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ACE_LAW_9_NUCLEAR_SCATTERING_ENERGY_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AceLaw9NuclearScatteringEnergyDistribution.hpp
//---------------------------------------------------------------------------//

