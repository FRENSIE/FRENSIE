//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectronScatteringDistributionNativeFactoryHelpers.cpp
//! \author Luke Kersting
//! \brief  The adjoint electron scattering distribution native factory helpers definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_AdjointElectronScatteringDistributionNativeFactoryHelpers.hpp"

namespace MonteCarlo{

//----------------------------------------------------------------------------//
//      ****ELASTIC DISTRIBUTIONS****
//----------------------------------------------------------------------------//


//----------------------------------------------------------------------------//
//      ****ATOMIC EXCITATION DISTRIBUTION****
//----------------------------------------------------------------------------//

//! Create a atomic excitation distribution
std::shared_ptr<AtomicExcitationAdjointElectronScatteringDistribution> createAtomicExcitationDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container )
{
  std::shared_ptr<AtomicExcitationAdjointElectronScatteringDistribution>
    distribution;

  AtomicExcitationAdjointElectronScatteringDistributionNativeFactory::createAtomicExcitationDistribution(
    data_container, distribution );

  return distribution;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectronScatteringDistributionNativeFactoryHelpers.cpp
//---------------------------------------------------------------------------//
