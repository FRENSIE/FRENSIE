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
#include "MonteCarlo_MomentPreservingElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_AnalogElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_HybridElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_CutoffElasticElectronScatteringDistribution.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"

namespace MonteCarlo{

//! The elastic scattering distribution factory class that uses Native data
class ElasticElectronScatteringDistributionNativeFactory
{

public:

  typedef AnalogElasticElectronScatteringDistribution::CutoffDistribution
            CutoffDistribution;

  typedef HybridElasticElectronScatteringDistribution::DiscreteDistribution
            DiscreteDistribution;

  typedef MomentPreservingElasticElectronScatteringDistribution::DiscreteElasticDistribution
            DiscreteElasticDistribution;

  //! Create the analog elastic distribution ( combined Cutoff and Screened Rutherford )
  static void createAnalogElasticDistribution(
	std::shared_ptr<const AnalogElasticElectronScatteringDistribution>&
        analog_elastic_distribution,
	const Data::ElectronPhotonRelaxationDataContainer& data_container );

  //! Create the analog elastic distribution ( combined Cutoff and Screened Rutherford )
  static void createAnalogElasticDistribution(
	std::shared_ptr<const AnalogElasticElectronScatteringDistribution>&
        analog_elastic_distribution,
    const std::map<double,std::vector<double> >& cutoff_elastic_angles,
    const std::map<double,std::vector<double> >& cutoff_elastic_pdf,
    const std::vector<double>& angular_energy_grid,
    const unsigned& atomic_number );

  //! Create the hybrid elastic distribution ( combined Cutoff and Moment Preserving )
  static void createHybridElasticDistribution(
	std::shared_ptr<const HybridElasticElectronScatteringDistribution>&
        hybrid_elastic_distribution,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
    const Teuchos::ArrayRCP<const double> energy_grid,
    const Teuchos::ArrayRCP<const double> cutoff_cross_section,
    const Teuchos::ArrayRCP<const double> moment_preserving_cross_section,
	const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double& cutoff_angle_cosine );

  //! Create a cutoff elastic distribution
  static void createCutoffElasticDistribution(
	std::shared_ptr<const CutoffElasticElectronScatteringDistribution>&
        cutoff_elastic_distribution,
	const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double& cutoff_angle_cosine = 1.0 );

  //! Create a screened Rutherford elastic distribution
  static void createScreenedRutherfordElasticDistribution(
	std::shared_ptr<const ScreenedRutherfordElasticElectronScatteringDistribution>&
        screened_rutherford_elastic_distribution,
	const std::shared_ptr<const CutoffElasticElectronScatteringDistribution>&
        cutoff_elastic_distribution,
	const Data::ElectronPhotonRelaxationDataContainer& data_container );

  //! Create a moment preserving elastic distribution
  static void createMomentPreservingElasticDistribution(
	std::shared_ptr<const MomentPreservingElasticElectronScatteringDistribution>&
        moment_preserving_elastic_distribution,
	const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double& cutoff_angle_cosine = 0.9 );

  //! Return angle cosine grid for the given cutoff angle and grid energy bin
  static std::vector<double> getAngularGrid(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
    const double& energy,
    const double& cutoff_angle_cosine );

  //! Return angle cosine grid for the given cutoff angle
  static std::vector<double> getAngularGrid(
    const std::vector<double>& raw_cutoff_elastic_angles,
    const double& cutoff_angle_cosine );

protected:

  //! Create the cutoff elastic scattering function
  static void createCutoffScatteringFunction(
        const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
        const std::vector<double>& angular_energy_grid,
        CutoffDistribution& scattering_function );

  //! Create the moment preserving elastic scattering function
  static void createMomentPreservingScatteringFunction(
        const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
        const std::vector<double>& angular_energy_grid,
        DiscreteElasticDistribution& scattering_function );

  //! Create the hybrid elastic scattering functions and cross section ratio
  static void createHybridScatteringFunction(
        const Data::ElectronPhotonRelaxationDataContainer& data_container,
        const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
        const Teuchos::ArrayRCP<const double> energy_grid,
        const Teuchos::ArrayRCP<const double> cutoff_cross_section,
        const Teuchos::ArrayRCP<const double> moment_preserving_cross_section,
        const std::vector<double>& angular_energy_grid,
        const double cutoff_angle_cosine,
        CutoffDistribution& cutoff_function,
        DiscreteDistribution& moment_preserving_function );

  //! Create the cutoff elastic scattering function
  static void createScatteringFunction(
    const std::map<double,std::vector<double> >& cutoff_elastic_angles,
    const std::map<double,std::vector<double> >& cutoff_elastic_pdf,
    const std::vector<double>& angular_energy_grid,
    CutoffDistribution& scattering_function );
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp
//---------------------------------------------------------------------------//

