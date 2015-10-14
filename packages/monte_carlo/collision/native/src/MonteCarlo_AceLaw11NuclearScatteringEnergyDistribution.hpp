//---------------------------------------------------------------------------//
//! 
//! \file   MonteCarlo_AceLaw11NuclearScatteringEnergyDistribution.hpp
//! \author Eli Moll
//! \brief  The law 11 scattering energy distribution class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ACE_LAW_11_NUCLEAR_SCATTERING_ENERGY_DISTRIBUTION_HPP
#define MONTE_CARLO_ACE_LAW_11_NUCLEAR_SCATTERING_ENERGY_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayRCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_NuclearScatteringEnergyDistribution.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_TabularOneDDistribution.hpp"
#include "Utility_Tuple.hpp"

namespace MonteCarlo{

/*! The law 11 scattering energy distribution class (Ace Law 11)
 * \ingroup ace_laws
 */
class AceLaw11NuclearScatteringEnergyDistribution : public NuclearScatteringEnergyDistribution
{

public:

  //! Typedef for the energy distribution
  typedef Teuchos::Array<Utility::Pair<double,double> > EnergyDistribution;

  //! Constructor
  AceLaw11NuclearScatteringEnergyDistribution(
                                          EnergyDistribution& a_distribution,
                                          EnergyDistribution& b_distribution,
                                          double restriction_energy);

  //! Destructor
  ~AceLaw11NuclearScatteringEnergyDistribution()
  { /* ... */ }

  //! Sample a scattering energy
  double sampleEnergy( const double energy ) const;

private:

  EnergyDistribution d_a_distribution;
  
  EnergyDistribution d_b_distribution;
  
  double d_restriction_energy;

};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ACE_LAW_11_NUCLEAR_SCATTERING_ENERGY_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AceLaw11NuclearScatteringEnergyDistribution.hpp
//---------------------------------------------------------------------------//

