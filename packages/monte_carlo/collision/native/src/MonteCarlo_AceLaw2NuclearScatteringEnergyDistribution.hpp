//---------------------------------------------------------------------------//
//! 
//! \file   MonteCarlo_AceLaw2NuclearScatteringEnergyDistribution.hpp
//! \author Eli Moll
//! \brief  The law 2 scattering energy distribution class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ACE_LAW_2_NUCLEAR_SCATTERING_ENERGY_DISTRIBUTION_HPP
#define MONTE_CARLO_ACE_LAW_2_NUCLEAR_SCATTERING_ENERGY_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayRCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_NuclearScatteringEnergyDistribution.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_TabularOneDDistribution.hpp"
#include "Utility_Tuple.hpp"

namespace MonteCarlo{

/*! The law 2 scattering energy distribution class (Ace Law 2)
 * \ingroup ace_laws
 */
class AceLaw2NuclearScatteringEnergyDistribution : public NuclearScatteringEnergyDistribution
{

public:

  //! Constructor
  AceLaw2NuclearScatteringEnergyDistribution( 
                                            int photonType,
                                            double photonEnergy,
                                            const double atomic_weight_ratio );

  //! Destructor
  ~AceLaw2NuclearScatteringEnergyDistribution()
  { /* ... */ }

  //! Sample a scattering energy
  double sampleEnergy( const double energy ) const;

private:

  int d_photon_type;
  
  double d_photon_energy;
  
  double d_atomic_weight_ratio;

};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ACE_LAW_2_NUCLEAR_SCATTERING_ENERGY_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AceLaw2NuclearScatteringEnergyDistribution.hpp
//---------------------------------------------------------------------------//

