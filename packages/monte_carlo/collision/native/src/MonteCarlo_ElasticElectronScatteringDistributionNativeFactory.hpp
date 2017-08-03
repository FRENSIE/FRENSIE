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
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "Utility_AnalogElasticDistribution.hpp"

namespace MonteCarlo{

//! The elastic scattering distribution factory class that uses Native data
class ElasticElectronScatteringDistributionNativeFactory
{

public:

  typedef ElasticElectronScatteringDistributionNativeFactory ThisType;

  typedef ElasticElectronTraits ElasticTraits;

  typedef Utility::Pair<double, std::shared_ptr<const Utility::UnitAwareTabularOneDDistribution<void, void> > > TwoDFunction;

  typedef Utility::FullyTabularTwoDDistribution TwoDDist;

  typedef Utility::AnalogElasticDistribution<Utility::LinLin> AnalogDist;

  typedef Utility::TabularDistribution<Utility::LinLin> TabularDist;

  typedef Utility::DiscreteDistribution DiscreteDist;

//----------------------------------------------------------------------------//
//      ****FORWARD DATA PUBLIC FUNCTIONS****
//----------------------------------------------------------------------------//

  //! Create the analog elastic distribution ( combined Cutoff and Screened Rutherford )
  template<typename TwoDInterpPolicy = Utility::LinLinLog>
  static void createAnalogElasticDistribution(
    std::shared_ptr<const AnalogElasticElectronScatteringDistribution>&
        analog_elastic_distribution,
    const Teuchos::ArrayRCP<const double> energy_grid,
    const Teuchos::ArrayRCP<const double> cutoff_cross_section,
    const Teuchos::ArrayRCP<const double> total_cross_section,
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const bool correlated_sampling_mode_on,
    const double evaluation_tol );

  //! Create the hybrid elastic distribution ( combined Cutoff and Moment Preserving )
  template<typename TwoDInterpPolicy = Utility::LinLinLog>
  static void createHybridElasticDistribution(
    std::shared_ptr<const HybridElasticElectronScatteringDistribution>&
        hybrid_elastic_distribution,
    const Teuchos::ArrayRCP<const double> energy_grid,
    const Teuchos::ArrayRCP<const double> cutoff_cross_section,
    const Teuchos::ArrayRCP<const double> moment_preserving_cross_section,
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const bool correlated_sampling_mode_on,
    const double evaluation_tol );

  //! Create a cutoff elastic distribution
  template<typename TwoDInterpPolicy = Utility::LinLinLog>
  static void createCutoffElasticDistribution(
    std::shared_ptr<const CutoffElasticElectronScatteringDistribution>&
        cutoff_elastic_distribution,
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const bool correlated_sampling_mode_on,
    const double evaluation_tol );

  //! Create a moment preserving elastic distribution
  template<typename TwoDInterpPolicy = Utility::LinLinLog>
  static void createMomentPreservingElasticDistribution(
    std::shared_ptr<const MomentPreservingElasticElectronScatteringDistribution>&
        moment_preserving_elastic_distribution,
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const bool correlated_sampling_mode_on,
    const double evaluation_tol );

//----------------------------------------------------------------------------//
//      ****ADJOINT DATA PUBLIC FUNCTIONS****
//----------------------------------------------------------------------------//

  //! Create the analog elastic distribution ( combined Cutoff and Screened Rutherford )
  template<typename TwoDInterpPolicy = Utility::LinLinLog>
  static void createAnalogElasticDistribution(
    std::shared_ptr<const AnalogElasticElectronScatteringDistribution>&
        analog_elastic_distribution,
    const Teuchos::ArrayRCP<const double> energy_grid,
    const Teuchos::ArrayRCP<const double> cutoff_cross_section,
    const Teuchos::ArrayRCP<const double> total_cross_section,
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const bool correlated_sampling_mode_on,
    const double evaluation_tol );

  //! Create the hybrid elastic distribution ( combined Cutoff and Moment Preserving )
  template<typename TwoDInterpPolicy = Utility::LinLinLog>
  static void createHybridElasticDistribution(
    std::shared_ptr<const HybridElasticElectronScatteringDistribution>&
        hybrid_elastic_distribution,
    const Teuchos::ArrayRCP<const double> energy_grid,
    const Teuchos::ArrayRCP<const double> cutoff_cross_section,
    const Teuchos::ArrayRCP<const double> moment_preserving_cross_section,
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const bool correlated_sampling_mode_on,
    const double evaluation_tol );

  //! Create a cutoff elastic distribution
  template<typename TwoDInterpPolicy = Utility::LinLinLog>
  static void createCutoffElasticDistribution(
    std::shared_ptr<const CutoffElasticElectronScatteringDistribution>&
        cutoff_elastic_distribution,
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const bool correlated_sampling_mode_on,
    const double evaluation_tol );

  //! Create a moment preserving elastic distribution
  template<typename TwoDInterpPolicy = Utility::LinLinLog>
  static void createMomentPreservingElasticDistribution(
    std::shared_ptr<const MomentPreservingElasticElectronScatteringDistribution>&
        moment_preserving_elastic_distribution,
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const bool correlated_sampling_mode_on,
    const double evaluation_tol );

//----------------------------------------------------------------------------//
//      ****DATA CONTAINER INDEPENDENT PUBLIC FUNCTIONS****
//----------------------------------------------------------------------------//

  //! Create the analog elastic distribution ( combined Cutoff and Screened Rutherford )
  template<typename TwoDInterpPolicy = Utility::LinLinLog>
  static void createAnalogElasticDistribution(
    std::shared_ptr<const AnalogElasticElectronScatteringDistribution>&
        analog_elastic_distribution,
    const Teuchos::ArrayRCP<const double>& cutoff_cross_section,
    const Teuchos::ArrayRCP<const double>& total_cross_section,
    const Teuchos::ArrayRCP<const double>& energy_grid,
    const std::map<double,std::vector<double> >& cutoff_elastic_angles,
    const std::map<double,std::vector<double> >& cutoff_elastic_pdf,
    const std::vector<double>& angular_energy_grid,
    const unsigned atomic_number,
    const bool correlated_sampling_mode_on,
    const double evaluation_tol );

  //! Create the hybrid elastic distribution ( combined Cutoff and Moment Preserving )
  template<typename TwoDInterpPolicy = Utility::LinLinLog>
  static void createHybridElasticDistribution(
    std::shared_ptr<const HybridElasticElectronScatteringDistribution>&
        hybrid_elastic_distribution,
    const Teuchos::ArrayRCP<const double> energy_grid,
    const Teuchos::ArrayRCP<const double> cutoff_cross_section,
    const std::map<double,std::vector<double> >& cutoff_elastic_angles,
    const std::map<double,std::vector<double> >& cutoff_elastic_pdf,
    const Teuchos::ArrayRCP<const double> moment_preserving_cross_section,
    const std::map<double,std::vector<double> >& moment_preserving_angles,
    const std::map<double,std::vector<double> >& moment_preserving_weights,
    const std::vector<double>& angular_energy_grid,
    const double cutoff_angle_cosine,
    const bool correlated_sampling_mode_on,
    const double evaluation_tol );

  //! Create a cutoff elastic distribution
  template<typename TwoDInterpPolicy = Utility::LinLinLog>
  static void createCutoffElasticDistribution(
    std::shared_ptr<const CutoffElasticElectronScatteringDistribution>&
        cutoff_elastic_distribution,
    const std::map<double,std::vector<double> >& cutoff_elastic_angles,
    const std::map<double,std::vector<double> >& cutoff_elastic_pdf,
    const std::vector<double>& angular_energy_grid,
    const double cutoff_angle_cosine,
    const bool correlated_sampling_mode_on,
    const double evaluation_tol );

  //! Create a screened Rutherford elastic distribution
  static void createScreenedRutherfordElasticDistribution(
    std::shared_ptr<const ScreenedRutherfordElasticElectronScatteringDistribution>&
        screened_rutherford_elastic_distribution,
    const std::shared_ptr<const CutoffElasticElectronScatteringDistribution>&
        cutoff_elastic_distribution,
    const unsigned atomic_number );

  //! Create a moment preserving elastic distribution
  template<typename TwoDInterpPolicy = Utility::LinLinLog>
  static void createMomentPreservingElasticDistribution(
    std::shared_ptr<const MomentPreservingElasticElectronScatteringDistribution>&
        moment_preserving_elastic_distribution,
    const std::vector<double> angular_energy_grid,
    const std::map<double,std::vector<double> >& discrete_angles,
    const std::map<double,std::vector<double> >& discrete_weights,
    const double cutoff_angle_cosine,
    const bool correlated_sampling_mode_on,
    const double evaluation_tol );

  //! Return angle cosine grid with the evaluated pdf for the given energy and cutoff angle
  template<typename TwoDInterpPolicy = Utility::LinLinLog>
  static void getAngularGridAndPDF(
    std::vector<double>& angular_grid,
    std::vector<double>& evaluated_pdf,
    const std::map<double,std::vector<double> >& angles,
    const std::map<double,std::vector<double> >& pdf,
    const double energy,
    const double cutoff_angle_cosine,
    const double evaluation_tol );

  //! Return angle cosine grid with the evaluated pdf for the given cutoff angle
  static void getAngularGridAndPDF(
    std::vector<double>& angular_grid,
    std::vector<double>& evaluated_pdf,
    const std::vector<double>& raw_angular_grid,
    const std::vector<double>& raw_pdf,
    const double cutoff_angle_cosine );

  //! Return angle cosine grid below the cutoff
  static std::vector<double> getAngularGrid(
    const std::vector<double>& raw_angular_grid,
    const double cutoff_angle_cosine );

  //! Return angle cosine grid above the cutoff for the given energy
  static std::vector<double> getAngularGridAboveCutoff(
    const std::map<double, std::vector<double> >& raw_angular_grid,
    const double energy,
    const double cutoff_angle_cosine );

  //! Return angle cosine grid above the cutoff
  static std::vector<double> getAngularGridAboveCutoff(
    const std::vector<double>& raw_angular_grid,
    const double cutoff_angle_cosine );

  //! Create the analog elastic scattering function
  template<typename TwoDInterpPolicy = Utility::LinLinLog>
  static void createAnalogScatteringFunction(
    const std::shared_ptr<const Utility::OneDDistribution>& cross_section_ratios,
    const std::shared_ptr<const ElasticTraits>& sr_traits,
    const std::map<double,std::vector<double> >& angles,
    const std::map<double,std::vector<double> >& pdf,
    const std::vector<double>& energy_grid,
    std::shared_ptr<TwoDDist>& scattering_function,
    const double evaluation_tol );

  //! Create the cutoff elastic scattering function
  template<typename TwoDInterpPolicy = Utility::LinLinLog>
  static void createScatteringFunction(
    const std::map<double,std::vector<double> >& angles,
    const std::map<double,std::vector<double> >& pdf,
    const std::vector<double>& energy_grid,
    std::shared_ptr<TwoDDist>& scattering_function,
    const double cutoff_angle_cosine,
    const double evaluation_tol,
    const bool discrete_function = false );

protected:

  //! Create the cutoff to total preserving cross section ratios
  template<typename TwoDInterpPolicy = Utility::LinLinLog>
  static void createCutoffCrossSectionRatios(
    const Teuchos::ArrayRCP<const double> energy_grid,
    const Teuchos::ArrayRCP<const double> cutoff_cross_section,
    const Teuchos::ArrayRCP<const double> total_cross_section,
    std::shared_ptr<const Utility::OneDDistribution>& cross_section_ratios );

  //! Create the cutoff to moment preserving cross section ratios
  template<typename TwoDInterpPolicy = Utility::LinLinLog>
  static void createHybridCrossSectionRatios(
    const Teuchos::ArrayRCP<const double> energy_grid,
    const Teuchos::ArrayRCP<const double> cutoff_cross_section,
    const Teuchos::ArrayRCP<const double> moment_preserving_cross_section,
    const std::shared_ptr<TwoDDist>& cutoff_scattering_function,
    const double cutoff_angle_cosine,
    std::shared_ptr<const Utility::OneDDistribution>& cross_section_ratios );

  //! Create the cutoff elastic scattering function
  static void createScatteringFunction(
    const std::vector<double>& angles,
    const std::vector<double>& pdf,
    const double energy,
    TwoDFunction& scattering_function,
    const bool discrete_function = false );

  //! Create the cutoff elastic scattering function in subrange
  static void createScatteringFunctionInSubrange(
    const std::vector<double>& angles,
    const std::vector<double>& pdf,
    const double energy,
    const double cutoff_angle_cosine,
    TwoDFunction& scattering_function );

};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory_def.hpp"

//---------------------------------------------------------------------------//


#endif // end MONTE_CARLO_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp
//---------------------------------------------------------------------------//

