//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AtomicExcitationElectronScatteringDistributionNativeFactory.hpp
//! \author Luke Kersting
//! \brief  The atomic excitation scattering distribution native factory declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ATOMIC_EXCITATION_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP
#define MONTE_CARLO_ATOMIC_EXCITATION_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP

// FRENSIE Includes
#include "MonteCarlo_AtomicExcitationElectronScatteringDistribution.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"

namespace MonteCarlo{

//! The atomic excitation scattering distribution factory class that uses Native data
class AtomicExcitationElectronScatteringDistributionNativeFactory
{

public:

  //! Create a basic atomic excitation distribution
  static void createAtomicExcitationDistribution(
            const Data::ElectronPhotonRelaxationDataContainer& data_container,
            std::shared_ptr<const AtomicExcitationElectronScatteringDistribution>&
              energy_loss_distribution );

protected:

  //! Create the energy loss function
  static void createEnergyLossFunction(
      const Data::ElectronPhotonRelaxationDataContainer& data_container,
      AtomicExcitationElectronScatteringDistribution::AtomicDistribution&
                                                        scattering_function );
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ATOMIC_EXCITATION_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AtomicExcitationElectronScatteringDistributionNativeFactory.hpp
//---------------------------------------------------------------------------//
