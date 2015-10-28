//---------------------------------------------------------------------------//
//! 
//! \file   MonteCarlo_AceLaw2NuclearScatteringEnergyDistribution.cpp
//! \author Eli Moll
//! \brief  The nuclear law 2 scattering energy distribution class
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "MonteCarlo_AceLaw2NuclearScatteringEnergyDistribution.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_RandomNumberGenerator.hpp"

namespace MonteCarlo{

// Constructor
AceLaw2NuclearScatteringEnergyDistribution::AceLaw2NuclearScatteringEnergyDistribution( 
                                             int photonType,
                                             double photonEnergy,
                                             const double atomic_weight_ratio )
  : NuclearScatteringEnergyDistribution( 1u ),
    d_photon_type( photonType ),
    d_photon_energy( photonEnergy ),
    d_atomic_weight_ratio( atomic_weight_ratio )
{
  // Check to make a valid photon type and photon energy are provided
  testPrecondition( photonType == 0 || photonType == 1 || photonType == 2 );
  testPrecondition( photonEnergy > 0 );
}

// Sample a scattering energy
double AceLaw2NuclearScatteringEnergyDistribution::sampleEnergy( 
						    const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( energy > 0 );
  testPrecondition( energy < std::numeric_limits<double>::infinity() );
  
  // Outgoing energy is dependent on the photonType
  if ( d_photon_type == 0 || d_photon_type == 1 )
  {
    return d_photon_energy;
  }
  else
  {
    return ( d_photon_energy + 
         d_atomic_weight_ratio/( d_atomic_weight_ratio + 1 )*energy );
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AceLaw5NuclearScatteringEnergyDistribution.cpp
//---------------------------------------------------------------------------//
