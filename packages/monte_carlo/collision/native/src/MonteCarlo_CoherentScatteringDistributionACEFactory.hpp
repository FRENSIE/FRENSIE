//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CoherentScatteringDistributionACEFactory.hpp
//! \author Alex Robinson
//! \brief  The coherent scattering distribution ACE factory declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COHERENT_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP
#define MONTE_CARLO_COHERENT_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_CoherentScatteringDistributionFactory.hpp"
#include "Data_XSSEPRDataExtractor.hpp"

namespace MonteCarlo{

//! The coherent scattering distribution factory class that uses ACE data
class CoherentScatteringDistributionACEFactory : public CoherentScatteringDistributionFactory
{

public:

  //! Create a basic coherent distribution
  static void createBasicCoherentDistribution(
			   const Data::XSSEPRDataExtractor& raw_photoatom_data,
			   Teuchos::RCP<const CoherentScatteringDistribution>&
			   coherent_distribution );

  //! Create an efficient coherent distribution
  static void createEfficientCoherentDistribution(
			   const Data::XSSEPRDataExtractor& raw_photoatom_data,
			   Teuchos::RCP<const CoherentScatteringDistribution>&
			   coherent_distribution );

protected:

  //! Create the form factor squared distribution
  static void createFormFactorSquared(
	   const Data::XSSEPRDataExtractor& raw_photoatom_data,
           Teuchos::RCP<const Utility::TabularOneDDistribution>& form_factor );
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_COHERENT_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CoherentScatteringDistributionACEFactory.hpp
//---------------------------------------------------------------------------//
