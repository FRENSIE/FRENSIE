//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AtomicExcitationElectronScatteringDistributionACEFactory.hpp
//! \author Luke Kersting
//! \brief  The atomic excitation scattering distribution ACE factory declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ATOMIC_EXCITATION_ELECTRON_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP
#define MONTE_CARLO_ATOMIC_EXCITATION_ELECTRON_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP

// FRENSIE Includes
#include "MonteCarlo_AtomicExcitationElectronScatteringDistribution.hpp"
#include "Data_XSSEPRDataExtractor.hpp"

namespace MonteCarlo{

//! The atomic excitation scattering distribution factory class that uses ACE data
class AtomicExcitationElectronScatteringDistributionACEFactory
{

public:

  //! Create a basic atomic excitation distribution
  static void createAtomicExcitationDistribution(
			const Data::XSSEPRDataExtractor& raw_electroatom_data,
			std::shared_ptr<const AtomicExcitationElectronScatteringDistribution>&
			  energy_loss_distribution );

protected:

  //! Create the energy loss function
  static void createEnergyLossFunction(
      const Data::XSSEPRDataExtractor& raw_electroatom_data,
      AtomicExcitationElectronScatteringDistribution::AtomicDistribution&
                                                        scattering_function );
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ATOMIC_EXCITATION__ELECTRON_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AtomicExcitationElectronScatteringDistributionACEFactory.hpp
//---------------------------------------------------------------------------//

