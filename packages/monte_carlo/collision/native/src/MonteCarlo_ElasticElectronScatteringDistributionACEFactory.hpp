//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElasticElectronScatteringDistributionACEFactory.hpp
//! \author Luke Kersting
//! \brief  The elastic scattering distribution ACE factory declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELASTIC_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP
#define MONTE_CARLO_ELASTIC_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ScreenedRutherfordElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_AnalogElasticElectronScatteringDistribution.hpp"
#include "Data_XSSEPRDataExtractor.hpp"

namespace MonteCarlo{

//! The elastic scattering distribution factory class that uses ACE data
class ElasticElectronScatteringDistributionACEFactory
{

public:


  //! Create a elastic distributions ( both Analog and Screened Rutherford ) 
  static void createHardElasticDistributions(
	Teuchos::RCP<const AnalogElasticElectronScatteringDistribution>&
        analog_elastic_distribution,
	Teuchos::RCP<const ScreenedRutherfordElasticElectronScatteringDistribution>&
        screened_rutherford_elastic_distribution,
	const Data::XSSEPRDataExtractor& raw_electroatom_data,
    const double analog_lower_cutoff_angle = 1.0e-6 );

  //! Create a analog elastic distribution
  static void createAnalogElasticDistribution(
	Teuchos::RCP<const AnalogElasticElectronScatteringDistribution>&
        analog_elastic_distribution,
	const Data::XSSEPRDataExtractor& raw_electroatom_data,
    const double lower_cutoff_angle = 1.0e-6 );

  //! Create a screened Rutherford elastic distribution
  static void createScreenedRutherfordElasticDistribution(
	Teuchos::RCP<const ScreenedRutherfordElasticElectronScatteringDistribution>&
        screened_rutherford_elastic_distribution,
	const Data::XSSEPRDataExtractor& raw_electroatom_data,
    const double upper_cutoff_angle = 1.0e-6 );

  //! Return angle cosine grid for given grid energy bin
  static Teuchos::Array<double> getAngularGrid(
    const Data::XSSEPRDataExtractor& raw_electroatom_data,
    const unsigned energy_bin,
    const double cutoff_angle_cosine );

protected:

  //! Create the elastic scattering function
  static void createScatteringFunction(
        const Data::XSSEPRDataExtractor& raw_electroatom_data,
        AnalogElasticElectronScatteringDistribution::ElasticDistribution& 
            scattering_function );

  //! Create the elastic cutoff pdf function
  static void createCutoffPDFFunction(
        Teuchos::RCP<const Utility::TabularDistribution<Utility::LinLin> >&
                elastic_cutoff_pdf_function,
        const AnalogElasticElectronScatteringDistribution::ElasticDistribution& 
                scattering_function,
        const double upper_cutoff_angle );
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElasticElectronScatteringDistributionACEFactory.hpp
//---------------------------------------------------------------------------//

