//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_IncoherentAdjointPhotonScatteringDistributionFactory.cpp
//! \author Alex Robinson
//! \brief  The incoherent adjoint photon scattering distribution factory
//!         base class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_IncoherentAdjointPhotonScatteringDistributionFactory.hpp"
#include "MonteCarlo_KleinNishinaAdjointPhotonScatteringDistribution.hpp"
#include "MonteCarlo_SimulationAdjointPhotonProperties.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create a Klein-Nishina distribution
void IncoherentAdjointPhotonScatteringDistributionFactory::createKleinNishinaDistribution(
          std::shared_ptr<IncoherentAdjointPhotonScatteringDistribution>&
          incoherent_adjoint_distribution,
          const double max_energy )
{
  // Make sure the max energy is valid
  testPrecondition( max_energy <= SimulationAdjointPhotonProperties::getAbsoluteMaxAdjointPhotonEnergy() );
  testPrecondition( max_energy > SimulationAdjointPhotonProperties::getAbsoluteMinAdjointPhotonEnergy() );

  incoherent_adjoint_distribution.reset(
           new KleinNishinaAdjointPhotonScatteringDistribution( max_energy ) );
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_IncoherentAdjointPhotonScatteringDistributionFactory.cpp
//---------------------------------------------------------------------------//
