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
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Create a Klein-Nishina distribution
void IncoherentAdjointPhotonScatteringDistributionFactory::createKleinNishinaDistribution(
                const AdjointKleinNishinaSamplingType adjoint_kn_sampling,
                const double max_energy,
                std::shared_ptr<IncoherentAdjointPhotonScatteringDistribution>&
                incoherent_adjoint_distribution )
{
  // Make sure the max energy is valid
  testPrecondition( max_energy <= SimulationAdjointPhotonProperties::getAbsoluteMaxAdjointPhotonEnergy() );
  testPrecondition( max_energy > SimulationAdjointPhotonProperties::getAbsoluteMinAdjointPhotonEnergy() );

  incoherent_adjoint_distribution.reset(
    new KleinNishinaAdjointPhotonScatteringDistribution( max_energy, adjoint_kn_sampling ) );
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_IncoherentAdjointPhotonScatteringDistributionFactory.cpp
//---------------------------------------------------------------------------//
