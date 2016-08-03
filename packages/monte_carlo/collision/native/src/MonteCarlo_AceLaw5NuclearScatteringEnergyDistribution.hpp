//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AceLaw5NuclearScatteringEnergyDistribution.hpp
//! \author Eli Moll
//! \brief  The law 5 scattering energy distribution class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ACE_LAW_5_NUCLEAR_SCATTERING_ENERGY_DISTRIBUTION_HPP
#define MONTE_CARLO_ACE_LAW_5_NUCLEAR_SCATTERING_ENERGY_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayRCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_NuclearScatteringEnergyDistribution.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_TabularOneDDistribution.hpp"
#include "Utility_Tuple.hpp"

namespace MonteCarlo{

/*! The law 5 scattering energy distribution class (Ace Law 5)
 * \ingroup ace_laws
 */
class AceLaw5NuclearScatteringEnergyDistribution : public NuclearScatteringEnergyDistribution
{

public:

  //! Typedef for the energy distribution
  typedef Teuchos::Array<Utility::Pair<double,double> > EnergyDistribution;

  //! Constructor
  AceLaw5NuclearScatteringEnergyDistribution(
                                          EnergyDistribution& energy_distribution,
                                          EnergyDistribution& probabilistic_function);

  //! Destructor
  ~AceLaw5NuclearScatteringEnergyDistribution()
  { /* ... */ }

  //! Sample a scattering energy
  double sampleEnergy( const double energy ) const;

private:

  EnergyDistribution d_energy_distribution;

  EnergyDistribution d_probabilistic_function;

};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ACE_LAW_5_NUCLEAR_SCATTERING_ENERGY_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AceLaw5NuclearScatteringEnergyDistribution.hpp
//---------------------------------------------------------------------------//

