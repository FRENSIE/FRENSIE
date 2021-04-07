//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp
//! \author Luke Kersting
//! \brief  The elastic scattering distribution Native factory declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELASTIC_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP
#define MONTE_CARLO_ELASTIC_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_ScreenedRutherfordElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_MomentPreservingElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_CoupledElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_HybridElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_CutoffElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_ElasticElectronTraits.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_Vector.hpp"

namespace MonteCarlo{

//! The elastic scattering distribution factory class that uses Native data
class ElasticElectronScatteringDistributionNativeFactory
{

public:

  using ThisType = ElasticElectronScatteringDistributionNativeFactory;
  using ElasticTraits = MonteCarlo::ElasticElectronTraits;
  using BasicBivariateDist = Utility::FullyTabularBasicBivariateDistribution;
  using TabularDist = Utility::TabularDistribution<Utility::LinLin>;

//----------------------------------------------------------------------------//
//      ****FORWARD DATA PUBLIC FUNCTIONS****
//----------------------------------------------------------------------------//

  //! Create the coupled elastic distribution ( combined Cutoff and Screened Rutherford )
  template<typename TwoDInterpPolicy = Utility::LogNudgedLogCosLog,
           template<typename> class TwoDGridPolicy = Utility::Correlated>
  static void createCoupledElasticDistribution(
    std::shared_ptr<const CoupledElasticElectronScatteringDistribution>&
        coupled_elastic_distribution,
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const CoupledElasticSamplingMethod& sampling_method,
    const double evaluation_tol );

  //! Create the coupled elastic distribution ( combined Cutoff and Screened Rutherford )
  template<typename TwoDInterpPolicy = Utility::LogNudgedLogCosLog,
           template<typename> class TwoDGridPolicy = Utility::Correlated>
  static void createCoupledElasticDistribution(
    std::shared_ptr<const CoupledElasticElectronScatteringDistribution>&
        coupled_elastic_distribution,
    const std::shared_ptr<const std::vector<double> > energy_grid,
    const std::shared_ptr<const std::vector<double> > cutoff_cross_section,
    const std::shared_ptr<const std::vector<double> > total_cross_section,
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const CoupledElasticSamplingMethod& sampling_method,
    const double evaluation_tol );

  //! Create the hybrid elastic distribution ( combined Cutoff and Moment Preserving )
  template<typename TwoDInterpPolicy = Utility::LogNudgedLogCosLog,
           template<typename> class TwoDGridPolicy = Utility::Correlated>
  static void createHybridElasticDistribution(
    std::shared_ptr<const HybridElasticElectronScatteringDistribution>&
        hybrid_elastic_distribution,
    const std::shared_ptr<const std::vector<double> > energy_grid,
    const std::shared_ptr<const std::vector<double> > cutoff_cross_section,
    const std::shared_ptr<const std::vector<double> > moment_preserving_cross_section,
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const double evaluation_tol );

  //! Create a cutoff elastic distribution
  template<typename TwoDInterpPolicy = Utility::LogLogCosLog,
           template<typename> class TwoDGridPolicy = Utility::Correlated>
  static void createCutoffElasticDistribution(
    std::shared_ptr<const CutoffElasticElectronScatteringDistribution>&
        cutoff_elastic_distribution,
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const double evaluation_tol );

  //! Create a moment preserving elastic distribution
  template<typename TwoDInterpPolicy = Utility::LogLogCosLog,
           template<typename> class TwoDGridPolicy = Utility::Correlated>
  static void createMomentPreservingElasticDistribution(
    std::shared_ptr<const MomentPreservingElasticElectronScatteringDistribution>&
        moment_preserving_elastic_distribution,
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const double evaluation_tol );

  //! Calculate the moment preserving cross sections
  template<typename TwoDInterpPolicy = Utility::LogLogCosLog,
           template<typename> class TwoDGridPolicy = Utility::Correlated>
  static void calculateMomentPreservingCrossSections(
    std::vector<double>& cross_sections,
    size_t& threshold_energy_index,
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const double evaluation_tol );

//----------------------------------------------------------------------------//
//      ****ADJOINT DATA PUBLIC FUNCTIONS****
//----------------------------------------------------------------------------//

  //! Create the coupled elastic distribution ( combined Cutoff and Screened Rutherford )
  template<typename TwoDInterpPolicy = Utility::LogNudgedLogCosLog,
           template<typename> class TwoDGridPolicy = Utility::Correlated>
  static void createCoupledElasticDistribution(
    std::shared_ptr<const CoupledElasticElectronScatteringDistribution>&
        coupled_elastic_distribution,
    const std::shared_ptr<const std::vector<double> > energy_grid,
    const std::shared_ptr<const std::vector<double> > cutoff_cross_section,
    const std::shared_ptr<const std::vector<double> > total_cross_section,
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const CoupledElasticSamplingMethod& sampling_method,
    const double evaluation_tol );

  //! Create the hybrid elastic distribution ( combined Cutoff and Moment Preserving )
  template<typename TwoDInterpPolicy = Utility::LogNudgedLogCosLog,
           template<typename> class TwoDGridPolicy = Utility::Correlated>
  static void createHybridElasticDistribution(
    std::shared_ptr<const HybridElasticElectronScatteringDistribution>&
        hybrid_elastic_distribution,
    const std::shared_ptr<const std::vector<double> > energy_grid,
    const std::shared_ptr<const std::vector<double> > cutoff_cross_section,
    const std::shared_ptr<const std::vector<double> > moment_preserving_cross_section,
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const double evaluation_tol );

  //! Create a cutoff elastic distribution
  template<typename TwoDInterpPolicy = Utility::LogLogCosLog,
           template<typename> class TwoDGridPolicy = Utility::Correlated>
  static void createCutoffElasticDistribution(
    std::shared_ptr<const CutoffElasticElectronScatteringDistribution>&
        cutoff_elastic_distribution,
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const double evaluation_tol );

  //! Create a moment preserving elastic distribution
  template<typename TwoDInterpPolicy = Utility::LogLogCosLog,
           template<typename> class TwoDGridPolicy = Utility::Correlated>
  static void createMomentPreservingElasticDistribution(
    std::shared_ptr<const MomentPreservingElasticElectronScatteringDistribution>&
        moment_preserving_elastic_distribution,
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const double evaluation_tol );

  //! Calculate the moment preserving cross sections
  template<typename TwoDInterpPolicy = Utility::LogLogCosLog,
           template<typename> class TwoDGridPolicy = Utility::Correlated>
  static void calculateMomentPreservingCrossSections(
    std::vector<double>& cross_sections,
    size_t& threshold_energy_index,
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const double evaluation_tol );

//----------------------------------------------------------------------------//
//      ****DATA CONTAINER INDEPENDENT PUBLIC FUNCTIONS****
//----------------------------------------------------------------------------//

  //! Create the coupled elastic distribution ( combined Cutoff and Screened Rutherford )
  template<typename TwoDInterpPolicy = Utility::LogNudgedLogCosLog,
           template<typename> class TwoDGridPolicy = Utility::Correlated>
  static void createCoupledElasticDistribution(
    std::shared_ptr<const CoupledElasticElectronScatteringDistribution>&
        coupled_elastic_distribution,
    const std::shared_ptr<const std::vector<double> >& cutoff_cross_section,
    const std::shared_ptr<const std::vector<double> >& total_cross_section,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::map<double,std::vector<double> >& cutoff_elastic_angles,
    const std::map<double,std::vector<double> >& cutoff_elastic_pdf,
    const std::vector<double>& angular_energy_grid,
    const unsigned atomic_number,
    const CoupledElasticSamplingMethod& sampling_method,
    const double evaluation_tol );

  //! Create the hybrid elastic distribution ( combined Cutoff and Moment Preserving )
  template<typename TwoDInterpPolicy = Utility::LogNudgedLogCosLog,
           template<typename> class TwoDGridPolicy = Utility::Correlated>
  static void createHybridElasticDistribution(
    std::shared_ptr<const HybridElasticElectronScatteringDistribution>&
        hybrid_elastic_distribution,
    const std::shared_ptr<const std::vector<double> > energy_grid,
    const std::shared_ptr<const std::vector<double> > cutoff_cross_section,
    const std::map<double,std::vector<double> >& cutoff_elastic_angles,
    const std::map<double,std::vector<double> >& cutoff_elastic_pdf,
    const std::shared_ptr<const std::vector<double> > moment_preserving_cross_section,
    const std::map<double,std::vector<double> >& moment_preserving_angles,
    const std::map<double,std::vector<double> >& moment_preserving_weights,
    const std::vector<double>& angular_energy_grid,
    const double cutoff_angle_cosine,
    const double evaluation_tol );

  //! Create a cutoff elastic distribution
  template<typename TwoDInterpPolicy = Utility::LogLogCosLog,
           template<typename> class TwoDGridPolicy = Utility::Correlated>
  static void createCutoffElasticDistribution(
    std::shared_ptr<const CutoffElasticElectronScatteringDistribution>&
        cutoff_elastic_distribution,
    const std::map<double,std::vector<double> >& cutoff_elastic_angles,
    const std::map<double,std::vector<double> >& cutoff_elastic_pdf,
    const std::vector<double>& angular_energy_grid,
    const double cutoff_angle_cosine,
    const double evaluation_tol );

  //! Create a screened Rutherford elastic distribution
  static void createScreenedRutherfordElasticDistribution(
    std::shared_ptr<const ScreenedRutherfordElasticElectronScatteringDistribution>&
        screened_rutherford_elastic_distribution,
    const unsigned atomic_number );

  //! Create a moment preserving elastic distribution
  template<typename TwoDInterpPolicy = Utility::LogLogCosLog,
           template<typename> class TwoDGridPolicy = Utility::Correlated>
  static void createMomentPreservingElasticDistribution(
    std::shared_ptr<const MomentPreservingElasticElectronScatteringDistribution>&
        moment_preserving_elastic_distribution,
    const std::vector<double> angular_energy_grid,
    const std::map<double,std::vector<double> >& discrete_angles,
    const std::map<double,std::vector<double> >& discrete_weights,
    const double cutoff_angle_cosine,
    const double evaluation_tol );

  //! Calculate the moment preserving cross sections
  static void calculateMomentPreservingCrossSections(
    const std::shared_ptr<const MonteCarlo::CutoffElasticElectronScatteringDistribution>&
      cutoff_distribution,
    const std::shared_ptr<const Utility::UnivariateDistribution>& reduction_distribution,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const std::vector<double> >& cutoff_cross_sections,
    const std::shared_ptr<const std::vector<double> >& total_cross_sections,
    const double cutoff_angle_cosine,
    std::vector<double>& cross_sections,
    size_t& threshold_energy_index,
    const double evaluation_tol );

  //! Return angle cosine grid with the evaluated pdf for the given energy and cutoff angle
  template<typename TwoDInterpPolicy,
           template<typename> class TwoDGridPolicy>
  static void evaluateAngularGridAndPDF(
    std::vector<double>& angular_grid,
    std::vector<double>& evaluated_pdf,
    const std::map<double,std::vector<double> >& angles,
    const std::map<double,std::vector<double> >& pdf,
    const double energy,
    const double cutoff_angle_cosine,
    const double evaluation_tol,
    const double grid_convergence_tol = 1e-3,
    const double absolute_diff_tol = 1e-13,
    const double distance_tol = 1e-13 );

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

  //! Create the coupled elastic scattering function
  template<typename TwoDInterpPolicy = Utility::LogNudgedLogCosLog,
           template<typename> class TwoDGridPolicy = Utility::Correlated>
  static void createCoupledScatteringFunction(
    const std::shared_ptr<const Utility::UnivariateDistribution>& cross_section_ratios,
    const std::shared_ptr<const ElasticTraits>& elastic_traits,
    const std::map<double,std::vector<double> >& angles,
    const std::map<double,std::vector<double> >& pdf,
    const std::vector<double>& energy_grid,
    std::shared_ptr<BasicBivariateDist>& scattering_function,
    const double evaluation_tol );

  //! Create the cutoff elastic scattering function
  template<typename TwoDInterpPolicy,
           template<typename> class TwoDGridPolicy>
  static void createScatteringFunction(
    const std::map<double,std::vector<double> >& angles,
    const std::map<double,std::vector<double> >& pdf,
    const std::vector<double>& energy_grid,
    std::shared_ptr<BasicBivariateDist>& scattering_function,
    const double cutoff_angle_cosine,
    const double evaluation_tol,
    const bool discrete_function = false );

  //! Create the hybrid elastic scattering function
  template<typename TwoDInterpPolicy = Utility::LogNudgedLogCosLog,
           template<typename> class TwoDGridPolicy = Utility::Correlated>
  static void createHybridScatteringFunction(
    const std::shared_ptr<const Utility::UnivariateDistribution>& cross_section_ratios,
    const std::map<double,std::vector<double> >& cutoff_elastic_angles,
    const std::map<double,std::vector<double> >& cutoff_elastic_pdf,
    const std::map<double,std::vector<double> >& moment_preserving_angles,
    const std::map<double,std::vector<double> >& moment_preserving_weights,
    const std::vector<double>& angular_energy_grid,
    std::shared_ptr<BasicBivariateDist>& hybrid_functions,
    const double cutoff_angle_cosine,
    const double evaluation_tol );

protected:

  //! Calculate the moment preserving cross section
  static double calculateMomentPreservingCrossSection(
    const double& cutoff_cdf,
    const double& cross_section_reduction,
    const double& cutoff_cross_section,
    const double& total_elastic_cross_Section );

  //! Create the cutoff to total preserving cross section ratios
  static void createCutoffCrossSectionRatios(
    const std::shared_ptr<const std::vector<double> > energy_grid,
    const std::shared_ptr<const std::vector<double> > cutoff_cross_section,
    const std::shared_ptr<const std::vector<double> > total_cross_section,
    std::shared_ptr<const Utility::UnivariateDistribution>& cross_section_ratios );

  //! Create the cutoff to moment preserving cross section ratios
  template<typename TwoDInterpPolicy = Utility::LogNudgedLogCosLog,
           template<typename> class TwoDGridPolicy = Utility::Correlated>
  static void createHybridCrossSectionRatios(
    const std::shared_ptr<const std::vector<double> > energy_grid,
    const std::shared_ptr<const std::vector<double> > cutoff_cross_section,
    const std::shared_ptr<const std::vector<double> > moment_preserving_cross_section,
    const std::shared_ptr<BasicBivariateDist>& cutoff_scattering_function,
    const double cutoff_angle_cosine,
    std::shared_ptr<const Utility::UnivariateDistribution>& cross_section_ratios );

  //! Create the cutoff elastic scattering function
  static void createScatteringFunction(
    const std::vector<double>& angles,
    const std::vector<double>& pdf,
    const double energy,
    double& primary_scattering_function_grid_value,
    std::shared_ptr<const Utility::TabularUnivariateDistribution>&
    secondary_scattering_function_grid_dist,
    const bool discrete_function = false );

  //! Create the cutoff elastic scattering function in subrange
  static void createScatteringFunctionInSubrange(
    const std::vector<double>& angles,
    const std::vector<double>& pdf,
    const double energy,
    const double cutoff_angle_cosine,
    double& primary_scattering_function_grid_value,
    std::shared_ptr<const Utility::TabularUnivariateDistribution>&
    secondary_scattering_function_grid_dist );

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

