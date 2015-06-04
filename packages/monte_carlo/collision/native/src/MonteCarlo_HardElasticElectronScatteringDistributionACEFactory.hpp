//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_HardElasticScatteringDistributionACEFactory.hpp
//! \author Alex Robinson
//! \brief  The hard elastic scattering distribution ACE factory declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_HARD_ELASTIC_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP
#define MONTE_CARLO_HARD_ELASTIC_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
//#include "MonteCarlo_HardElasticScatteringDistributionFactory.hpp"
#include "MonteCarlo_HardElasticScatteringDistribution.hpp"
#include "Data_XSSEPRDataExtractor.hpp"

namespace MonteCarlo{

//! The hard elastic scattering distribution factory class that uses ACE data
class HardElasticScatteringDistributionACEFactory //: public HardElasticScatteringDistributionFactory
{

public:

  //! Create a basic hard elastic distribution
  static void createHardElasticDistribution(
			const Data::XSSEPRDataExtractor& raw_electroatom_data,
			Teuchos::RCP<const HardElasticScatteringDistribution>&
			  elastic_distribution );

protected:

  //! Create the elastic scattering function
  static void createScatteringFunction(
	   const Data::XSSEPRDataExtractor& raw_electroatom_data,
           HardElasticElectronScatteringDistribution::ElasticDistribution& 
                                                        scattering_function );
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_HARD_ELASTIC_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_HardElasticScatteringDistributionACEFactory.hpp
//---------------------------------------------------------------------------//

