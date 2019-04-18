//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AtomicExcitationAdjointElectronScatteringDistributionNativeFactory.hpp
//! \author Luke Kersting
//! \brief  The Atomic Excitation adjoint scattering distribution native factory declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ATOMIC_EXCITATION_ADJOINT_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP
#define MONTE_CARLO_ATOMIC_EXCITATION_ADJOINT_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP

// FRENSIE Includes
#include "MonteCarlo_AtomicExcitationAdjointElectronScatteringDistribution.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"

namespace MonteCarlo{

//! The Atomic Excitation adjoint distribution factory class that uses Native data
class AtomicExcitationAdjointElectronScatteringDistributionNativeFactory
{

public:

  //! Create a Atomic Excitation adjoint distribution
  static void createAtomicExcitationDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    std::shared_ptr<AtomicExcitationAdjointElectronScatteringDistribution>&
        scattering_distribution );

  //! Create the energy gain function
  static void createEnergyGainFunction(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    std::shared_ptr<Utility::UnivariateDistribution>& energy_gain_function );
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ATOMIC_EXCITATION_ADJOINT_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AtomicExcitationAdjointElectronScatteringDistributionNativeFactory.hpp
//---------------------------------------------------------------------------//

