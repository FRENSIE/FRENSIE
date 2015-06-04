//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AtomicExcitationScatteringDistributionACEFactory.hpp
//! \author Alex Robinson
//! \brief  The atomic excitation scattering distribution ACE factory declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ATOMIC_EXCITATION_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP
#define MONTE_CARLO_ATOMIC_EXCITATION_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
//#include "MonteCarlo_AtomicExcitationScatteringDistributionFactory.hpp"
#include "MonteCarlo_AtomicExcitationScatteringDistribution.hpp"
#include "Data_XSSEPRDataExtractor.hpp"

namespace MonteCarlo{

//! The atomic excitation scattering distribution factory class that uses ACE data
class AtomicExcitationScatteringDistributionACEFactory //: public AtomicExcitationScatteringDistributionFactory
{

public:

  //! Create a basic atomic excitation distribution
  static void createAtomicExcitationDistribution(
			const Data::XSSEPRDataExtractor& raw_electroatom_data,
			Teuchos::RCP<const AtomicExcitationScatteringDistribution>&
			  energy_loss_distribution );

protected:

  //! Create the energy loss function
  static void createEnergyLossFunction(
	   const Data::XSSEPRDataExtractor& raw_electroatom_data,
           AtomicExcitationElectronScatteringDistribution::AtomicDistribution& 
                                                        scattering_function );
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ATOMIC_EXCITATION_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AtomicExcitationScatteringDistributionACEFactory.hpp
//---------------------------------------------------------------------------//

