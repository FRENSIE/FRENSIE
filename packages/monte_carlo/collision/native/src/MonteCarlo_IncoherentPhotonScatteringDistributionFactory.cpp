//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_IncoherentPhotonScatteringDistributionFactory.cpp
//! \author Alex Robinson
//! \brief  The incoherent photon scattering distribution factory base class
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_IncoherentPhotonScatteringDistributionFactory.hpp"
#include "MonteCarlo_KleinNishinaPhotonScatteringDistribution.hpp"
#include "MonteCarlo_SimulationPhotonProperties.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create a Klein-Nishina distribution
void IncoherentPhotonScatteringDistributionFactory::createKleinNishinaDistribution(
		    Teuchos::RCP<const IncoherentPhotonScatteringDistribution>&
		    incoherent_distribution,
		    const double kahn_sampling_cutoff_energy )
{
  // Make sure the cutoff energy is valid
  testPrecondition( kahn_sampling_cutoff_energy >=
		    SimulationPhotonProperties::getAbsoluteMinKahnSamplingCutoffEnergy() );

  incoherent_distribution.reset( new KleinNishinaPhotonScatteringDistribution(
					       kahn_sampling_cutoff_energy ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_IncoherentPhotonScatteringDistributionFactory.cpp
//---------------------------------------------------------------------------//
