//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AtomicExcitationAdjointElectronScatteringDistributionACEFactory.hpp
//! \author Luke Kersting
//! \brief  The atomic excitation adjoint scattering distribution ACE factory declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ATOMIC_EXCITATION_ADJOINT_ELECTRON_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP
#define MONTE_CARLO_ATOMIC_EXCITATION_ADJOINT_ELECTRON_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
//#include "MonteCarlo_AtomicExcitationAdjointElectronScatteringDistributionFactory.hpp"
#include "MonteCarlo_AtomicExcitationAdjointElectronScatteringDistribution.hpp"
#include "Data_XSSEPRDataExtractor.hpp"

namespace MonteCarlo{

//! The atomic excitation scattering distribution factory class that uses ACE data
class AtomicExcitationAdjointElectronScatteringDistributionACEFactory
{

public:

  //! Create a basic atomic excitation adjoint distribution
  static void createAtomicExcitationAdjointDistribution(
    const Data::XSSEPRDataExtractor& raw_electroatom_data,
    std::shared_ptr<const AtomicExcitationAdjointElectronScatteringDistribution>&
      energy_gain_distribution );

protected:

  //! Create the energy gain function
  static void createEnergyGainFunction(
    const Data::XSSEPRDataExtractor& raw_electroatom_data,
    AtomicExcitationAdjointElectronScatteringDistribution::AtomicDistribution&
      scattering_function );
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ATOMIC_EXCITATION_ADJOINT_ELECTRON_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AtomicExcitationAdjointElectronScatteringDistributionACEFactory.hpp
//---------------------------------------------------------------------------//

