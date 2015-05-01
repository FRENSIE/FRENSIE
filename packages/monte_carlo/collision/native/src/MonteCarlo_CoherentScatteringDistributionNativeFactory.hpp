//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CoherentScatteringDistributionNativeFactory.hpp
//! \author Alex Robinson
//! \brief  The coherent scattering distribution native factory declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COHERENT_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP
#define MONTE_CARLO_COHERENT_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_CoherentScatteringDistributionFactory.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"

namespace MonteCarlo{

//! The coherent scattering distribution factory class that uses native data
class CoherentScatteringDistributionNATIVEFactory : public CoherentScatteringDistributionFactory
{

public:

  //! Create a basic coherent distribution
  static void createBasicCoherentDistribution(
	 const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
	 Teuchos::RCP<const CoherentScatteringDistribution>&
	 coherent_distribution );

  //! Create an efficient coherent distribution
  static void createEfficientCoherentDistribution(
	 const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
	 Teuchos::RCP<const CoherentScatteringDistribution>&
	 coherent_distribution );

protected:

  //! Create the form factor squared distribution
  static void createFormFactorSquared(
	 const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
	 Teuchos::RCP<const Utility::TabularOneDDistribution>& form_factor );
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_COHERENT_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CoherentScatteringDistributionNativeFactory.hpp
//---------------------------------------------------------------------------//
