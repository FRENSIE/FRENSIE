//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp
//! \author Luke Kersting
//! \brief  The elastic scattering distribution Native factory declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELASTIC_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP
#define MONTE_CARLO_ELASTIC_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ScreenedRutherfordElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_AnalogElasticElectronScatteringDistribution.hpp"
#include "Data_EvaluatedElectronDataContainer.hpp"

namespace MonteCarlo{

//! The elastic scattering distribution factory class that uses Native data
class ElasticElectronScatteringDistributionNativeFactory
{

public:

  typedef ScreenedRutherfordElasticElectronScatteringDistribution::ParameterArray 
            ParameterArray;
  typedef AnalogElasticElectronScatteringDistribution::ElasticDistribution
            ElasticDistribution;    


  //! Create a elastic distributions ( both Analog and Screened Rutherford ) 
  static void createHardElasticDistributions(
	Teuchos::RCP<const AnalogElasticElectronScatteringDistribution>&
        analog_elastic_distribution,
	Teuchos::RCP<const ScreenedRutherfordElasticElectronScatteringDistribution>&
        screened_rutherford_elastic_distribution,
	const Data::EvaluatedElectronDataContainer& raw_electroatom_data,
    const double analog_lower_cutoff_angle = 1.0e-6 );

  //! Create a analog elastic distribution
  static void createAnalogElasticDistribution(
	Teuchos::RCP<const AnalogElasticElectronScatteringDistribution>&
        analog_elastic_distribution,
	const Data::EvaluatedElectronDataContainer& raw_electroatom_data,
    const double lower_cutoff_angle = 1.0e-6 );

  //! Create a screened Rutherford elastic distribution
  static void createScreenedRutherfordElasticDistribution(
	Teuchos::RCP<const ScreenedRutherfordElasticElectronScatteringDistribution>&
        screened_rutherford_elastic_distribution,
	const Data::EvaluatedElectronDataContainer& raw_electroatom_data,
    const double upper_cutoff_angle = 1.0e-6 );

  //! Return angle cosine grid for given grid energy bin
  static Teuchos::Array<double> getAngularGrid(
    const Data::EvaluatedElectronDataContainer& raw_electroatom_data,
    const double energy,
    const double cutoff_angle );

protected:

  //! Create the elastic scattering function
  static void createScatteringFunction(
        const Data::EvaluatedElectronDataContainer& raw_electroatom_data,
        const std::vector<double> angular_energy_grid, 
        ElasticDistribution& scattering_function );

  //! Create the screened Rutherford parameter array
  static void createScreenedRutherfordParameterArray(
        const Data::EvaluatedElectronDataContainer& raw_electroatom_data,
        const std::vector<double> angular_energy_grid, 
        ParameterArray& screened_rutherford_parameters );

};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp
//---------------------------------------------------------------------------//

