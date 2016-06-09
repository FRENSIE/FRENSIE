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
#include "MonteCarlo_CutoffElasticElectronScatteringDistribution.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"

namespace MonteCarlo{

//! The elastic scattering distribution factory class that uses Native data
class ElasticElectronScatteringDistributionNativeFactory
{

public:

  typedef ScreenedRutherfordElasticElectronScatteringDistribution::ParameterArray
            ParameterArray;
  typedef CutoffElasticElectronScatteringDistribution::ElasticDistribution
            ElasticDistribution;

  //! Create a elastic distributions ( both Cutoff and Screened Rutherford )
  static void createHardElasticDistributions(
	Teuchos::RCP<const CutoffElasticElectronScatteringDistribution>&
        cutoff_elastic_distribution,
	Teuchos::RCP<const ScreenedRutherfordElasticElectronScatteringDistribution>&
        screened_rutherford_elastic_distribution,
	const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const double cutoff_upper_cutoff_angle_cosine = 0.999999 );

  //! Create a cutoff elastic distribution
  static void createCutoffElasticDistribution(
	Teuchos::RCP<const CutoffElasticElectronScatteringDistribution>&
        cutoff_elastic_distribution,
	const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const double upper_cutoff_angle_cosine = 0.999999 );

  //! Create a screened Rutherford elastic distribution
  static void createScreenedRutherfordElasticDistribution(
	Teuchos::RCP<const ScreenedRutherfordElasticElectronScatteringDistribution>&
        screened_rutherford_elastic_distribution,
	const Teuchos::RCP<const CutoffElasticElectronScatteringDistribution>&
        cutoff_elastic_distribution,
	const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data );

  //! Return angle cosine grid for given grid energy bin
  static std::vector<double> getAngularGrid(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const double energy,
    const double cutoff_angle_cosine );

protected:

  //! Create the elastic scattering function
  static void createScatteringFunction(
        const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
        const std::vector<double> angular_energy_grid,
        ElasticDistribution& scattering_function );

/*
  //! Create the screened Rutherford parameter array
  static void createScreenedRutherfordParameterArray(
        const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
        const std::vector<double> angular_energy_grid,
        ParameterArray& screened_rutherford_parameters );
*/
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp
//---------------------------------------------------------------------------//

