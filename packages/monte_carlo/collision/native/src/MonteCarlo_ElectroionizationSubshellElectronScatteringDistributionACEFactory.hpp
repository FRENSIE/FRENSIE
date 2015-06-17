//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroionizationSubshellElectronScatteringDistributionACEFactory.hpp
//! \author Luke Kersting
//! \brief  The subshell electroionization scattering distribution ACE factory declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTRIONIZATION_SUBSHELL_ELECTRON_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP
#define MONTE_CARLO_ELECTRIONIZATION_SUBSHELL_ELECTRON_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
//#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistributionFactory.hpp"
#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistribution.hpp"
#include "Data_XSSEPRDataExtractor.hpp"

namespace MonteCarlo{

//! The subshell electroionization scattering distribution factory class that uses ACE data
class ElectroionizationSubshellElectronScatteringDistributionACEFactory //: public ElectroionizationSubshellElectronScatteringDistributionFactory
{

public:

  //! Create a electroionization subshell distribution
  static void createElectroionizationSubshellDistribution(
        const unsigned table_info_location,
        const unsigned table_location,
        const unsigned number_of_tables,
        const double binding_energy,
	const Teuchos::ArrayView<const double>& raw_electroionization_data,
	Teuchos::RCP<const ElectroionizationSubshellElectronScatteringDistribution>&
	  electroionization_subshell_distribution );

//protected:


  //! Create the electroionization subshell distribution function
  static void createSubshellDistribution(
       const unsigned table_info_location,
       const unsigned table_location,
       const unsigned number_of_tables,
       const Teuchos::ArrayView<const double>& raw_electroionization_data,
       ElectroionizationSubshellElectronScatteringDistribution::ElectroionizationSubshellDistribution&
	 subshell_distribution );
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELECTRIONIZATION_SUBSHELL_ELECTRON_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationSubshellElectronScatteringDistributionACEFactory.hpp
//---------------------------------------------------------------------------//

