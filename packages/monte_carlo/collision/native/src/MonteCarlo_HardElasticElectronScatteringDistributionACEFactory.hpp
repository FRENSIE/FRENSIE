//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_HardElasticElectronScatteringDistributionACEFactory.hpp
//! \author Luke Kersting
//! \brief  The hard elastic scattering distribution ACE factory declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_HARD_ELASTIC_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP
#define MONTE_CARLO_HARD_ELASTIC_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
//#include "MonteCarlo_HardElasticElectronScatteringDistributionFactory.hpp"
#include "MonteCarlo_HardElasticElectronScatteringDistribution.hpp"
#include "Data_XSSEPRDataExtractor.hpp"

namespace MonteCarlo{

//! The hard elastic scattering distribution factory class that uses ACE data
class HardElasticElectronScatteringDistributionACEFactory //: public HardElasticElectronScatteringDistributionFactory
{

public:

  //! Create a basic hard elastic distribution
  static void createHardElasticDistribution(
			const Data::XSSEPRDataExtractor& raw_electroatom_data,
			Teuchos::RCP<const HardElasticElectronScatteringDistribution>&
			  elastic_distribution );

  //! Create common angle cosine grid for interpolation between energies
  static void createCommonAngularGrid(
                 const Data::XSSEPRDataExtractor& raw_electroatom_data,
                 Teuchos::Array<double>& common_angular_grid );

protected:

  //! Create the elastic scattering function
  static void createScatteringFunction(
	   const Data::XSSEPRDataExtractor& raw_electroatom_data,
           const int size,
           HardElasticElectronScatteringDistribution::ElasticDistribution& 
                                                        scattering_function );
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_HARD_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_HardElasticElectronScatteringDistributionACEFactory.hpp
//---------------------------------------------------------------------------//

