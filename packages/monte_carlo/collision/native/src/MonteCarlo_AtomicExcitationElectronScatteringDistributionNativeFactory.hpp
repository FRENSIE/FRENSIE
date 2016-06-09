//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AtomicExcitationElectronScatteringDistributionNativeFactory.hpp
//! \author Luke Kersting
//! \brief  The atomic excitation scattering distribution native factory declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ATOMIC_EXCITATION_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP
#define MONTE_CARLO_ATOMIC_EXCITATION_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
//#include "MonteCarlo_AtomicExcitationElectronScatteringDistributionFactory.hpp"
#include "MonteCarlo_AtomicExcitationElectronScatteringDistribution.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"

namespace MonteCarlo{

//! The atomic excitation scattering distribution factory class that uses Native data
class AtomicExcitationElectronScatteringDistributionNativeFactory //: public AtomicExcitationElectronScatteringDistributionFactory
{

public:

  //! Create a basic atomic excitation distribution
  static void createAtomicExcitationDistribution(
			const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
			Teuchos::RCP<const AtomicExcitationElectronScatteringDistribution>&
			  energy_loss_distribution );

protected:

  //! Create the energy loss function
  static void createEnergyLossFunction(
      const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
      AtomicExcitationElectronScatteringDistribution::AtomicDistribution&
                                                        scattering_function );
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ATOMIC_EXCITATION__ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AtomicExcitationElectronScatteringDistributionNativeFactory.hpp
//---------------------------------------------------------------------------//

