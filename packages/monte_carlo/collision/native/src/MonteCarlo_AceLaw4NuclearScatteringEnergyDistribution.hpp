//---------------------------------------------------------------------------//
//! 
//! \file   MonteCarlo_AceLaw4NuclearScatteringEnergyDistribution.hpp
//! \author Alex Bennett, Eli Moll
//! \brief  The law 4 scattering energy distribution class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ACE_LAW_4_NUCLEAR_SCATTERING_ENERGY_DISTRIBUTION_HPP
#define MONTE_CARLO_ACE_LAW_4_NUCLEAR_SCATTERING_ENERGY_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayRCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_NuclearScatteringEnergyDistribution.hpp"
#include "Utility_TabularOneDDistribution.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_Tuple.hpp"

namespace MonteCarlo{

/*! The law 4 scattering energy distribution class (Ace Law 4)
 * \ingroup ace_laws
 */
class AceLaw4NuclearScatteringEnergyDistribution : public NuclearScatteringEnergyDistribution
{

public:

  //! Typedef for the energy distribution
  typedef Teuchos::Array<Utility::Pair<double,Teuchos::RCP<Utility::TabularOneDDistribution> > >
                                                        EnergyDistribution;
  //! Constructor
  AceLaw4NuclearScatteringEnergyDistribution( 
				     EnergyDistribution& energy_distribution );

  //! Destructor
  ~AceLaw4NuclearScatteringEnergyDistribution()
  { /* ... */ }

  //! Sample a scattering energy
  double sampleEnergy( const double energy ) const;

  //! Sample a scattering energy
  double sampleEnergy( const double energy, 
                       unsigned& incoming_index, 
                       unsigned& outgoing_index,
                       double& energy_prime ) const;

  void getDistribution( AceLaw4NuclearScatteringEnergyDistribution::EnergyDistribution energy_distribution );

  EnergyDistribution d_energy_distribution;

};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ACE_LAW_4_NUCLEAR_SCATTERING_ENERGY_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AceLaw4NuclearScatteringEnergyDistribution.hpp
//---------------------------------------------------------------------------//

