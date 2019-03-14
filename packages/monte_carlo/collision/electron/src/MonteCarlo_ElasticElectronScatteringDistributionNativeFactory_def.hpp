//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElasticElectronScatteringDistributionNativeFactory_def.hpp
//! \author Luke Kersting
//! \brief  The elastic scattering distribution Native factory def.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELASTIC_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_DEF_HPP
#define MONTE_CARLO_ELASTIC_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_DEF_HPP

// FRENSIE Includes
#include "MonteCarlo_CoupledElasticDistribution.hpp"
#include "MonteCarlo_HybridElasticDistribution.hpp"
#include "MonteCarlo_ElasticBasicBivariateDistribution.hpp"
#include "Utility_GridGenerator.hpp"

namespace MonteCarlo{

//----------------------------------------------------------------------------//
//      ****FORWARD DATA PUBLIC FUNCTIONS****
//----------------------------------------------------------------------------//

// Create the coupled elastic distribution ( combined Cutoff and Screened Rutherford )
template<typename TwoDInterpPolicy, template<typename> class TwoDGridPolicy>
void ElasticElectronScatteringDistributionNativeFactory::createCoupledElasticDistribution(
    std::shared_ptr<const CoupledElasticElectronScatteringDistribution>&
        coupled_elastic_distribution,
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const CoupledElasticSamplingMethod& sampling_method,
    const double evaluation_tol )
{
  ThisType::createCoupledElasticDistribution<TwoDInterpPolicy,TwoDGridPolicy>(
    coupled_elastic_distribution,
    std::make_shared<const std::vector<double> >( data_container.getCutoffElasticCrossSection() ),
    std::make_shared<const std::vector<double> >( data_container.getTotalElasticCrossSection() ),
    std::make_shared<const std::vector<double> >( data_container.getElectronEnergyGrid() ),
    data_container.getCutoffElasticAngles(),
    data_container.getCutoffElasticPDF(),
    data_container.getElasticAngularEnergyGrid(),
    data_container.getAtomicNumber(),
    sampling_method,
    evaluation_tol );
}

// Create the coupled elastic distribution ( combined Cutoff and Screened Rutherford )
template<typename TwoDInterpPolicy, template<typename> class TwoDGridPolicy>
void ElasticElectronScatteringDistributionNativeFactory::createCoupledElasticDistribution(
    std::shared_ptr<const CoupledElasticElectronScatteringDistribution>&
        coupled_elastic_distribution,
    const std::shared_ptr<const std::vector<double> > energy_grid,
    const std::shared_ptr<const std::vector<double> > cutoff_cross_section,
    const std::shared_ptr<const std::vector<double> > total_cross_section,
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const CoupledElasticSamplingMethod& sampling_method,
    const double evaluation_tol )
{
  ThisType::createCoupledElasticDistribution<TwoDInterpPolicy,TwoDGridPolicy>(
    coupled_elastic_distribution,
    cutoff_cross_section,
    total_cross_section,
    energy_grid,
    data_container.getCutoffElasticAngles(),
    data_container.getCutoffElasticPDF(),
    data_container.getElasticAngularEnergyGrid(),
    data_container.getAtomicNumber(),
    sampling_method,
    evaluation_tol );
}

// Create the hybrid elastic distribution ( combined Cutoff and Moment Preserving )
template<typename TwoDInterpPolicy, template<typename> class TwoDGridPolicy>
void ElasticElectronScatteringDistributionNativeFactory::createHybridElasticDistribution(
    std::shared_ptr<const HybridElasticElectronScatteringDistribution>&
        hybrid_elastic_distribution,
    const std::shared_ptr<const std::vector<double> > energy_grid,
    const std::shared_ptr<const std::vector<double> > cutoff_cross_section,
    const std::shared_ptr<const std::vector<double> > moment_preserving_cross_section,
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const double evaluation_tol )
{
  testPostcondition( data_container.hasMomentPreservingData() );

  ThisType::createHybridElasticDistribution<TwoDInterpPolicy,TwoDGridPolicy>(
    hybrid_elastic_distribution,
    energy_grid,
    cutoff_cross_section,
    data_container.getCutoffElasticAngles(),
    data_container.getCutoffElasticPDF(),
    moment_preserving_cross_section,
    data_container.getMomentPreservingElasticDiscreteAngles(),
    data_container.getMomentPreservingElasticWeights(),
    data_container.getElasticAngularEnergyGrid(),
    cutoff_angle_cosine,
    evaluation_tol );
}

// Create a cutoff elastic distribution
template<typename TwoDInterpPolicy, template<typename> class TwoDGridPolicy>
void ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution(
    std::shared_ptr<const CutoffElasticElectronScatteringDistribution>&
        cutoff_elastic_distribution,
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const double evaluation_tol )
{
  ThisType::createCutoffElasticDistribution<TwoDInterpPolicy,TwoDGridPolicy>(
    cutoff_elastic_distribution,
    data_container.getCutoffElasticAngles(),
    data_container.getCutoffElasticPDF(),
    data_container.getElasticAngularEnergyGrid(),
    cutoff_angle_cosine,
    evaluation_tol );
}

// Create a moment preserving elastic distribution
template<typename TwoDInterpPolicy, template<typename> class TwoDGridPolicy>
void ElasticElectronScatteringDistributionNativeFactory::createMomentPreservingElasticDistribution(
    std::shared_ptr<const MomentPreservingElasticElectronScatteringDistribution>&
        moment_preserving_elastic_distribution,
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const double evaluation_tol )
{
  testPostcondition( data_container.hasMomentPreservingData() );

  ThisType::createMomentPreservingElasticDistribution<TwoDInterpPolicy,TwoDGridPolicy>(
    moment_preserving_elastic_distribution,
    data_container.getElasticAngularEnergyGrid(),
    data_container.getMomentPreservingElasticDiscreteAngles(),
    data_container.getMomentPreservingElasticWeights(),
    cutoff_angle_cosine,
    evaluation_tol );
}

// Calculate the moment preserving cross section
template<typename TwoDInterpPolicy, template<typename> class TwoDGridPolicy>
void ElasticElectronScatteringDistributionNativeFactory::calculateMomentPreservingCrossSections(
    std::vector<double>& cross_sections,
    size_t& threshold_energy_index,
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const double evaluation_tol )
{
  // Make sure there is moment preserving data
  testPrecondition( data_container.hasMomentPreservingData() );
  //Make sure the energy grid and cross sections are valid
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid->begin(),
                                                      energy_grid->end() ) );
  //Make sure the evaluation tolerance is valid
  testPrecondition( evaluation_tol > 0.0 );

  std::shared_ptr<const MonteCarlo::CutoffElasticElectronScatteringDistribution> cutoff_distribution;
  ThisType::createCutoffElasticDistribution<TwoDInterpPolicy,TwoDGridPolicy>(
    cutoff_distribution,
    data_container,
    0.999999,
    evaluation_tol );

  // Create the elastic cross section reduction distribution
  std::shared_ptr<const Utility::UnivariateDistribution> reduction_distribution =
  std::make_shared<Utility::TabularDistribution<Utility::LogLog> >(
            data_container.getElasticAngularEnergyGrid(),
            data_container.getMomentPreservingCrossSectionReduction() );

  // Get the cutoff elastic cross sections
  auto cutoff_cross_sections = std::make_shared<const std::vector<double> >(
       data_container.getCutoffElasticCrossSection() );

  // Get the total elastic cross sections
  auto total_cross_sections = std::make_shared<const std::vector<double> >(
       data_container.getTotalElasticCrossSection() );

  ThisType::calculateMomentPreservingCrossSections(
              cutoff_distribution,
              reduction_distribution,
              energy_grid,
              cutoff_cross_sections,
              total_cross_sections,
              data_container.getCutoffAngleCosine(),
              cross_sections,
              threshold_energy_index,
              evaluation_tol );

  testPostcondition( threshold_energy_index >= 0u );
  testPostcondition( cross_sections.size() + threshold_energy_index ==
                     energy_grid->size() );
}

//----------------------------------------------------------------------------//
//      ****ADJOINT DATA PUBLIC FUNCTIONS****
//----------------------------------------------------------------------------//

// Create the coupled elastic distribution ( combined Cutoff and Screened Rutherford )
template<typename TwoDInterpPolicy, template<typename> class TwoDGridPolicy>
void ElasticElectronScatteringDistributionNativeFactory::createCoupledElasticDistribution(
    std::shared_ptr<const CoupledElasticElectronScatteringDistribution>&
        coupled_elastic_distribution,
    const std::shared_ptr<const std::vector<double> > energy_grid,
    const std::shared_ptr<const std::vector<double> > cutoff_cross_section,
    const std::shared_ptr<const std::vector<double> > total_cross_section,
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const CoupledElasticSamplingMethod& sampling_method,
    const double evaluation_tol )
{
  ThisType::createCoupledElasticDistribution<TwoDInterpPolicy,TwoDGridPolicy>(
    coupled_elastic_distribution,
    cutoff_cross_section,
    total_cross_section,
    energy_grid,
    data_container.getAdjointCutoffElasticAngles(),
    data_container.getAdjointCutoffElasticPDF(),
    data_container.getAdjointElasticAngularEnergyGrid(),
    data_container.getAtomicNumber(),
    sampling_method,
    evaluation_tol );
}

// Create the hybrid elastic distribution ( combined Cutoff and Moment Preserving )
template<typename TwoDInterpPolicy, template<typename> class TwoDGridPolicy>
void ElasticElectronScatteringDistributionNativeFactory::createHybridElasticDistribution(
    std::shared_ptr<const HybridElasticElectronScatteringDistribution>&
        hybrid_elastic_distribution,
    const std::shared_ptr<const std::vector<double> > energy_grid,
    const std::shared_ptr<const std::vector<double> > cutoff_cross_section,
    const std::shared_ptr<const std::vector<double> > moment_preserving_cross_section,
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const double evaluation_tol )
{
  testPostcondition( data_container.hasAdjointMomentPreservingData() );

ThisType::createHybridElasticDistribution<TwoDInterpPolicy,TwoDGridPolicy>(
    hybrid_elastic_distribution,
    energy_grid,
    cutoff_cross_section,
    data_container.getAdjointCutoffElasticAngles(),
    data_container.getAdjointCutoffElasticPDF(),
    moment_preserving_cross_section,
    data_container.getAdjointMomentPreservingElasticDiscreteAngles(),
    data_container.getAdjointMomentPreservingElasticWeights(),
    data_container.getAdjointElasticAngularEnergyGrid(),
    cutoff_angle_cosine,
    evaluation_tol );
}

// Create a cutoff elastic distribution
template<typename TwoDInterpPolicy, template<typename> class TwoDGridPolicy>
void ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution(
    std::shared_ptr<const CutoffElasticElectronScatteringDistribution>&
        cutoff_elastic_distribution,
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const double evaluation_tol )
{
  ThisType::createCutoffElasticDistribution<TwoDInterpPolicy,TwoDGridPolicy>(
    cutoff_elastic_distribution,
    data_container.getAdjointCutoffElasticAngles(),
    data_container.getAdjointCutoffElasticPDF(),
    data_container.getAdjointElasticAngularEnergyGrid(),
    cutoff_angle_cosine,
    evaluation_tol );
}

// Create a moment preserving elastic distribution
template<typename TwoDInterpPolicy, template<typename> class TwoDGridPolicy>
void ElasticElectronScatteringDistributionNativeFactory::createMomentPreservingElasticDistribution(
    std::shared_ptr<const MomentPreservingElasticElectronScatteringDistribution>&
        moment_preserving_elastic_distribution,
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const double evaluation_tol )
{
  testPostcondition( data_container.hasAdjointMomentPreservingData() );

ThisType::createMomentPreservingElasticDistribution<TwoDInterpPolicy,TwoDGridPolicy>(
    moment_preserving_elastic_distribution,
    data_container.getAdjointElasticAngularEnergyGrid(),
    data_container.getAdjointMomentPreservingElasticDiscreteAngles(),
    data_container.getAdjointMomentPreservingElasticWeights(),
    cutoff_angle_cosine,
    evaluation_tol );
}

// Calculate the moment preserving cross section
template<typename TwoDInterpPolicy, template<typename> class TwoDGridPolicy>
void ElasticElectronScatteringDistributionNativeFactory::calculateMomentPreservingCrossSections(
    std::vector<double>& cross_sections,
    size_t& threshold_energy_index,
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const double evaluation_tol )
{
  // Make sure there is moment preserving data
  testPrecondition( data_container.hasAdjointMomentPreservingData() );
  //Make sure the energy grid and cross sections are valid
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid->begin(),
                                                      energy_grid->end() ) );
  //Make sure the evaluation tolerance is valid
  testPrecondition( evaluation_tol > 0.0 );

  std::shared_ptr<const MonteCarlo::CutoffElasticElectronScatteringDistribution> cutoff_distribution;
  ThisType::createCutoffElasticDistribution<TwoDInterpPolicy,TwoDGridPolicy>(
    cutoff_distribution,
    data_container,
    0.999999,
    evaluation_tol );

  // Create the elastic cross section reduction distribution
  std::shared_ptr<const Utility::UnivariateDistribution> reduction_distribution =
  std::make_shared<Utility::TabularDistribution<Utility::LogLog> >(
            data_container.getAdjointElasticAngularEnergyGrid(),
            data_container.getAdjointMomentPreservingCrossSectionReduction() );

  // Get the cutoff elastic cross sections
  auto cutoff_cross_sections = std::make_shared<const std::vector<double> >(
    data_container.getAdjointCutoffElasticCrossSection() );

  // Get the total elastic cross sections
  auto total_cross_sections = std::make_shared<const std::vector<double> >(
    data_container.getAdjointTotalElasticCrossSection() );

  ThisType::calculateMomentPreservingCrossSections(
              cutoff_distribution,
              reduction_distribution,
              energy_grid,
              cutoff_cross_sections,
              total_cross_sections,
              data_container.getCutoffAngleCosine(),
              cross_sections,
              threshold_energy_index,
              evaluation_tol );

  testPrecondition( threshold_energy_index >= 0u );
  testPostcondition( cross_sections.size() + threshold_energy_index ==
                     energy_grid->size() );
}

//----------------------------------------------------------------------------//
//      ****DATA CONTAINER INDEPENDENT PUBLIC FUNCTIONS****
//----------------------------------------------------------------------------//

// Create the coupled elastic distribution ( combined Cutoff and Screened Rutherford )
/*! \details This function has been overloaded so it can be called without using
 *  the native data container. This functionality is necessary for generating
 *  native moment preserving data without first creating native data files.
 */
template<typename TwoDInterpPolicy, template<typename> class TwoDGridPolicy>
void ElasticElectronScatteringDistributionNativeFactory::createCoupledElasticDistribution(
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
    const double evaluation_tol )
{
  // Make sure the cross sections are valid
  testPrecondition( Data::valuesGreaterThanOrEqualToZero( *cutoff_cross_section ) );
  testPrecondition( Data::valuesGreaterThanOrEqualToZero( *total_cross_section ) );
  testPrecondition( total_cross_section->size() == cutoff_cross_section->size() );
  // Make sure the maps are valid
  testPrecondition( cutoff_elastic_pdf.size() == angular_energy_grid.size() );
  testPrecondition( cutoff_elastic_angles.size() == angular_energy_grid.size() );

  // Make sure the energy grids are valid
//  testPrecondition( energy_grid->back() > 0 );
  testPrecondition(
        Utility::Sort::isSortedAscending( energy_grid->begin(),
                                          energy_grid->end() ) );
  testPrecondition( Data::valuesGreaterThanZero( *energy_grid ) );
  testPrecondition( angular_energy_grid.back() > 0 );
  testPrecondition(
        Utility::Sort::isSortedAscending( angular_energy_grid.begin(),
                                          angular_energy_grid.end() ) );
  testPrecondition( Data::valuesGreaterThanZero( angular_energy_grid ) );
  // Make sure the atomic number is valid
  testPrecondition( atomic_number > 0 );
  testPrecondition( atomic_number <= 100 );
  // Make sure the evaluation tolerance is valid
  testPrecondition( evaluation_tol > 0.0 );
  testPrecondition( evaluation_tol < 1.0 );

  if( (TwoDInterpPolicy::name() == "LogLogCosLog" || TwoDInterpPolicy::name() == "LogNudgedLogCosLog") && sampling_method == MODIFIED_TWO_D_UNION && TwoDGridPolicy<TwoDInterpPolicy>::name() == "Direct" )
  {
    THROW_EXCEPTION( std::runtime_error, "the bivariate grid policy "
                  << TwoDGridPolicy<TwoDInterpPolicy>::name() << " is not currently supported "
                  << "with a " << sampling_method
                  << " coupled elastic sampling mode!" );
  }

  // Get the distribution data
  std::vector<double> cutoff_ratios( angular_energy_grid.size() );
  std::vector<double> etas( angular_energy_grid.size() );

  // Create the cross section ratios
  std::shared_ptr<const Utility::UnivariateDistribution> cross_section_ratios;
  ThisType::createCutoffCrossSectionRatios( energy_grid,
                                            cutoff_cross_section,
                                            total_cross_section,
                                            cross_section_ratios );

  // Create the Elastic electron traits
  auto elastic_traits = std::make_shared<const ElasticTraits>( atomic_number );

  // Create the scattering function
  std::shared_ptr<BasicBivariateDist> scattering_function;
  ThisType::createCoupledScatteringFunction<TwoDInterpPolicy,TwoDGridPolicy>(
        cross_section_ratios,
        elastic_traits,
        cutoff_elastic_angles,
        cutoff_elastic_pdf,
        angular_energy_grid,
        scattering_function,
        evaluation_tol );

  // Create coupled distribution
  coupled_elastic_distribution.reset(
      new CoupledElasticElectronScatteringDistribution(
                scattering_function,
                cross_section_ratios,
                elastic_traits,
                sampling_method ) );
}

// Create the hybrid elastic distribution ( combined Cutoff and Moment Preserving )
template<typename TwoDInterpPolicy, template<typename> class TwoDGridPolicy>
void ElasticElectronScatteringDistributionNativeFactory::createHybridElasticDistribution(
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
    const double evaluation_tol )
{
  // Make sure the angular energy grid is valid
  testPrecondition( angular_energy_grid.back() > 0 );
  testPrecondition(
        Utility::Sort::isSortedAscending( angular_energy_grid.begin(),
                                          angular_energy_grid.end() ) );

  testPrecondition( Data::valuesGreaterThanZero( angular_energy_grid ) );
  // Make sure the cutoff angle cosine is valid
  testPrecondition( cutoff_angle_cosine > -1.0 );
  testPrecondition( cutoff_angle_cosine <= 1.0 );
  // Make sure the evaluation tolerance is valid
  testPrecondition( evaluation_tol > 0.0 );
  testPrecondition( evaluation_tol < 1.0 );

  // Create the full continuous scattering function
  std::shared_ptr<BasicBivariateDist> full_continuous_function;
  ThisType::createScatteringFunction<TwoDInterpPolicy,TwoDGridPolicy>(
                cutoff_elastic_angles,
                cutoff_elastic_pdf,
                angular_energy_grid,
                full_continuous_function,
                1.0,
                evaluation_tol,
                false );

  // Create the cross section ratios
  std::shared_ptr<const Utility::UnivariateDistribution> cross_section_ratios;
  createHybridCrossSectionRatios(
                energy_grid,
                cutoff_cross_section,
                moment_preserving_cross_section,
                full_continuous_function,
                cutoff_angle_cosine,
                cross_section_ratios );

  // Create the hybrid scattering function
  std::shared_ptr<BasicBivariateDist> hybrid_function;
    ThisType::createHybridScatteringFunction<TwoDInterpPolicy,TwoDGridPolicy>(
                cross_section_ratios,
                cutoff_elastic_angles,
                cutoff_elastic_pdf,
                moment_preserving_angles,
                moment_preserving_weights,
                angular_energy_grid,
                hybrid_function,
                cutoff_angle_cosine,
                evaluation_tol );

  // Create hybrid distribution
  hybrid_elastic_distribution.reset(
        new HybridElasticElectronScatteringDistribution(
                hybrid_function,
                cutoff_angle_cosine,
                evaluation_tol ) );
}

// Create a cutoff elastic distribution
template<typename TwoDInterpPolicy, template<typename> class TwoDGridPolicy>
void ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution(
    std::shared_ptr<const CutoffElasticElectronScatteringDistribution>&
        cutoff_elastic_distribution,
    const std::map<double,std::vector<double> >& cutoff_elastic_angles,
    const std::map<double,std::vector<double> >& cutoff_elastic_pdf,
    const std::vector<double>& angular_energy_grid,
    const double cutoff_angle_cosine,
    const double evaluation_tol )
{
  // Make sure the angular energy grid is valid
  testPrecondition( angular_energy_grid.back() > 0 );
  testPrecondition(
        Utility::Sort::isSortedAscending( angular_energy_grid.begin(),
                                          angular_energy_grid.end() ) );

  testPrecondition( Data::valuesGreaterThanZero( angular_energy_grid ) );
  // Make sure the cutoff angle cosine is valid
  testPrecondition( cutoff_angle_cosine > -1.0 );
  testPrecondition( cutoff_angle_cosine <= 1.0 );
  // Make sure the evaluation tolerance is valid
  testPrecondition( evaluation_tol > 0.0 );
  testPrecondition( evaluation_tol < 1.0 );

  // Create the full scattering function
  std::shared_ptr<BasicBivariateDist> full_scattering_function;
    ThisType::createScatteringFunction<TwoDInterpPolicy,TwoDGridPolicy>(
        cutoff_elastic_angles,
        cutoff_elastic_pdf,
        angular_energy_grid,
        full_scattering_function,
        ElasticTraits::mu_peak,
        evaluation_tol,
        false );

  if( cutoff_angle_cosine >= ElasticTraits::mu_peak )
  {
    cutoff_elastic_distribution.reset(
        new CutoffElasticElectronScatteringDistribution(
                full_scattering_function ) );
  }
  else
  {
    // Create the scattering function below the cutoff angle cosine
    std::shared_ptr<BasicBivariateDist> scattering_function;
    ThisType::createScatteringFunction<TwoDInterpPolicy,TwoDGridPolicy>(
        cutoff_elastic_angles,
        cutoff_elastic_pdf,
        angular_energy_grid,
        scattering_function,
        cutoff_angle_cosine,
        evaluation_tol,
        false );

    cutoff_elastic_distribution.reset(
        new CutoffElasticElectronScatteringDistribution(
                full_scattering_function,
                scattering_function,
                cutoff_angle_cosine ) );
  }
}

// Create a moment preserving elastic distribution
template<typename TwoDInterpPolicy, template<typename> class TwoDGridPolicy>
void ElasticElectronScatteringDistributionNativeFactory::createMomentPreservingElasticDistribution(
    std::shared_ptr<const MomentPreservingElasticElectronScatteringDistribution>&
        moment_preserving_elastic_distribution,
    const std::vector<double> angular_energy_grid,
    const std::map<double,std::vector<double> >& discrete_angles,
    const std::map<double,std::vector<double> >& discrete_weights,
    const double cutoff_angle_cosine,
    const double evaluation_tol )
{
  // Make sure the angular energy grid is valid
  testPrecondition( angular_energy_grid.back() > 0 );
  testPrecondition(
        Utility::Sort::isSortedAscending( angular_energy_grid.begin(),
                                          angular_energy_grid.end() ) );

  testPrecondition( Data::valuesGreaterThanZero( angular_energy_grid ) );
  // Make sure the cutoff angle cosine is valid
  testPrecondition( cutoff_angle_cosine > -1.0 );
  testPrecondition( cutoff_angle_cosine <= 1.0 );
  // Make sure the evaluation tolerance is valid
  testPrecondition( evaluation_tol > 0.0 );
  testPrecondition( evaluation_tol < 1.0 );

  // Create the scattering function
  std::shared_ptr<BasicBivariateDist> scattering_function;
  ThisType::createScatteringFunction<TwoDInterpPolicy,TwoDGridPolicy>(
    discrete_angles,
    discrete_weights,
    angular_energy_grid,
    scattering_function,
    1.0,
    evaluation_tol,
    true );

  // Create the moment preserving distribution
  moment_preserving_elastic_distribution.reset(
        new MonteCarlo::MomentPreservingElasticElectronScatteringDistribution(
                scattering_function,
                cutoff_angle_cosine ) );
}

// Return angle cosine grid with the evaluated pdf for the given energy
template<typename TwoDInterpPolicy, template<typename> class TwoDGridPolicy>
void ElasticElectronScatteringDistributionNativeFactory::evaluateAngularGridAndPDF(
    std::vector<double>& angular_grid,
    std::vector<double>& evaluated_pdf,
    const std::map<double,std::vector<double> >& angles,
    const std::map<double,std::vector<double> >& pdf,
    const double energy,
    const double cutoff_angle_cosine,
    const double evaluation_tol,
    const double grid_convergence_tol,
    const double absolute_diff_tol,
    const double distance_tol )
{
  // Make sure the maps are valid
  testPrecondition( angles.size() == pdf.size() );
  testPrecondition( !angles.empty() );

  // Make sure the energy is valid
  testPrecondition( energy >= angles.begin()->first );
  testPrecondition( energy <= angles.rbegin()->first );

  // Get the angular grid
  if( angles.count( energy ) > 0 )
  {
    ThisType::getAngularGridAndPDF(
        angular_grid,
        evaluated_pdf,
        angles.at( energy ),
        pdf.at( energy ),
        cutoff_angle_cosine );
  }
  else
  {
    // Get the lower and upper angular grids
    std::map<double,std::vector<double>>::const_iterator lower_bin, upper_bin;
    upper_bin = angles.upper_bound( energy );
    lower_bin = upper_bin;
    --lower_bin;

    // Get the distribution data
    std::vector<double> primary_grid( 2 );
    std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
      secondary_dists( 2 );

    // Get the lower angular distributions
    primary_grid[0] = lower_bin->first;
    secondary_dists[0].reset(
      new const TabularDist( lower_bin->second, pdf.at( lower_bin->first ) ) );

    // Get the upper angular distributions
    primary_grid[1] = upper_bin->first;
    secondary_dists[1].reset(
      new const TabularDist( upper_bin->second, pdf.at( upper_bin->first ) ) );

    // Max scattering angle cosine
    double max_angle_cosine =
        std::max( lower_bin->second.back(), upper_bin->second.back() );

    // Fuzzy bound tolerance
    double fuzzy_bound_tol = 1e-6;

    // Create the BasicBivariateDistribution between the two distributions
    std::shared_ptr<BasicBivariateDist> scattering_function =
       std::make_shared<MonteCarlo::ElasticBasicBivariateDistribution<TwoDGridPolicy<TwoDInterpPolicy> > >(
                                                            primary_grid,
                                                            secondary_dists,
                                                            max_angle_cosine,
                                                            fuzzy_bound_tol,
                                                            evaluation_tol );

    // Create a grid generator
    Utility::GridGenerator<Utility::LinLin>
                                grid_generator( grid_convergence_tol,
                                                absolute_diff_tol,
                                                distance_tol );

    // Construct the evaluator functor
    auto&& pdf_evaluator = [&scattering_function, energy ]( const double& angle ){
      return scattering_function->evaluateSecondaryConditionalPDF( energy, angle );
    };

    // Use the angular grid at the upper energy grid point
    angular_grid = ThisType::getAngularGrid( upper_bin->second,
                                             cutoff_angle_cosine );

    // Refine the angular grid
    grid_generator.generateAndEvaluateInPlace( angular_grid,
                                               evaluated_pdf,
                                               pdf_evaluator );
  }
}

//----------------------------------------------------------------------------//
//      ****PRIVATE FUNCTIONS****
//----------------------------------------------------------------------------//

// // Create the ratio of the cutoff to the total elastic cross section
// template<typename TwoDInterpPolicy, template<typename> class TwoDGridPolicy>
// void ElasticElectronScatteringDistributionNativeFactory::createCutoffCrossSectionRatios(
//     const std::shared_ptr<const std::vector<double> > raw_energy_grid,
//     const std::shared_ptr<const std::vector<double> > cutoff_cross_section,
//     const std::shared_ptr<const std::vector<double> > total_cross_section,
//     std::shared_ptr<const Utility::UnivariateDistribution>& cross_section_ratios )
// {
//   // Calculate the ratio of the cutoff to the total cross section
//   std::vector<double> cross_section_ratio( raw_energy_grid.size() );
//   std::vector<double> energy_grid( raw_energy_grid.size() );
//   for( unsigned n = 0; n < energy_grid.size(); ++n )
//   {
//     // Get the energy
//     energy_grid[n] = raw_energy_grid[n];

//     // Get the ratio of the cutoff to the total cross section
//     cross_section_ratio[n] = cutoff_cross_section[n]/total_cross_section[n];
//   }
//     // Create cross section ratios
//     cross_section_ratios.reset(
//       new const Utility::TabularDistribution<Utility::LogLog>( energy_grid, cross_section_ratio ) );
// }

// Create the ratio of the cutoff to the moment preserving cross section
template<typename TwoDInterpPolicy, template<typename> class TwoDGridPolicy>
void ElasticElectronScatteringDistributionNativeFactory::createHybridCrossSectionRatios(
    const std::shared_ptr<const std::vector<double> > raw_energy_grid,
    const std::shared_ptr<const std::vector<double> > cutoff_cross_section,
    const std::shared_ptr<const std::vector<double> > moment_preserving_cross_section,
    const std::shared_ptr<BasicBivariateDist>& cutoff_scattering_function,
    const double cutoff_angle_cosine,
    std::shared_ptr<const Utility::UnivariateDistribution>& cross_section_ratios )
{
  // Calculate the ratio of the cutoff to the moment preserving cross section
  std::vector<double> cross_section_ratio( raw_energy_grid->size() );
  std::vector<double> energy_grid( raw_energy_grid->size() );
  for( unsigned n = 0; n < energy_grid.size(); ++n )
  {
    // Get the energy
    energy_grid[n] = (*raw_energy_grid)[n];

    // Get the cutoff cdf value at the angle cosine cutoff
    double cutoff_cdf =
            cutoff_scattering_function->evaluateSecondaryConditionalCDF(
                                                        energy_grid[n],
                                                        cutoff_angle_cosine );

    // Get the reduced cutoff cross section
    double reduced_cross_section = (*cutoff_cross_section)[n]*cutoff_cdf;

    // Get the ratio of the cutoff to the moment preserving cross section
    cross_section_ratio[n] =
      reduced_cross_section/(reduced_cross_section + (*moment_preserving_cross_section)[n] );
  }
    // Create cross section ratios
    cross_section_ratios.reset(
      new const Utility::TabularDistribution<Utility::LogLog>( energy_grid, cross_section_ratio ) );
}

// Create the hybrid elastic scattering functions
template<typename TwoDInterpPolicy, template<typename> class TwoDGridPolicy>
void ElasticElectronScatteringDistributionNativeFactory::createHybridScatteringFunction(
    const std::shared_ptr<const Utility::UnivariateDistribution>& cross_section_ratios,
    const std::map<double,std::vector<double> >& elastic_angles,
    const std::map<double,std::vector<double> >& elastic_pdf,
    const std::map<double,std::vector<double> >& moment_preserving_angles,
    const std::map<double,std::vector<double> >& moment_preserving_weights,
    const std::vector<double>& energy_grid,
    std::shared_ptr<BasicBivariateDist>& hybrid_function,
    const double cutoff_angle_cosine,
    const double evaluation_tol )
{
  // Get the distribution data
  std::vector<double> primary_grid( energy_grid.size() );
  std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
    secondary_dists( energy_grid.size() );

  // Loop through all energies below the max energy
  for( size_t n = 0; n < energy_grid.size(); ++n )
  {
    // Create the cutoff elastic scattering function
    primary_grid[n] = energy_grid[n];

    // Create hybrid elastic distribution
    secondary_dists[n].reset(
      new const MonteCarlo::HybridElasticDistribution<Utility::LinLin>(
                      elastic_angles.find( energy_grid[n] )->second,
                      elastic_pdf.find( energy_grid[n] )->second,
                      moment_preserving_angles.find( energy_grid[n] )->second,
                      moment_preserving_weights.find( energy_grid[n] )->second,
                      cutoff_angle_cosine,
                      cross_section_ratios->evaluate( energy_grid[n] ) ) );
  }

  // Set the hybrid function
  hybrid_function.reset(
    new MonteCarlo::ElasticBasicBivariateDistribution<TwoDGridPolicy<TwoDInterpPolicy> >(
                                                            primary_grid,
                                                            secondary_dists,
                                                            1.0,
                                                            1e-6,
                                                            evaluation_tol ) );
}

// Create the coupled scattering function
template<typename TwoDInterpPolicy, template<typename> class TwoDGridPolicy>
void ElasticElectronScatteringDistributionNativeFactory::createCoupledScatteringFunction(
    const std::shared_ptr<const Utility::UnivariateDistribution>& cross_section_ratios,
    const std::shared_ptr<const ElasticTraits>& elastic_traits,
    const std::map<double,std::vector<double> >& elastic_angles,
    const std::map<double,std::vector<double> >& elastic_pdf,
    const std::vector<double>& energy_grid,
    std::shared_ptr<BasicBivariateDist>& scattering_function,
    const double evaluation_tol )
{
  // Make sure the energy grid is valid
  testPrecondition( energy_grid.back() > 0 );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
                                                      energy_grid.end() ) );

  testPrecondition( Data::valuesGreaterThanZero( energy_grid ) );

  // Get the distribution data
  std::vector<double> primary_grid( energy_grid.size() );
  std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
    secondary_dists( energy_grid.size() );

  for( size_t n = 0; n < energy_grid.size(); ++n )
  {
    // Set the energy
    primary_grid[n] = energy_grid[n];

    // Get the value of moliere's eta
    double eta = elastic_traits->evaluateMoliereScreeningConstant( energy_grid[n] );

    // Get the ratio of the cutoff to total elastic cross section
    double cutoff_ratio = cross_section_ratios->evaluate( energy_grid[n] );

    // Create coupled elastic distribution
    secondary_dists[n].reset(
               new const MonteCarlo::CoupledElasticDistribution<Utility::LinLin>(
                                elastic_angles.find( energy_grid[n] )->second,
                                elastic_pdf.find( energy_grid[n] )->second,
                                eta,
                                cutoff_ratio ) );
  }

  // Set the scattering function
  scattering_function.reset(
    new MonteCarlo::ElasticBasicBivariateDistribution<TwoDGridPolicy<TwoDInterpPolicy> >(
                                                            primary_grid,
                                                            secondary_dists,
                                                            1.0,
                                                            1e-6,
                                                            evaluation_tol ) );
}

// Create the scattering function
/*! \details This function has been overloaded so it can be called without using
 *  the native data container. This functionality is necessary for generating
 *  native moment preserving data without first creating native data files.
 */
template<typename TwoDInterpPolicy, template<typename> class TwoDGridPolicy>
void ElasticElectronScatteringDistributionNativeFactory::createScatteringFunction(
        const std::map<double,std::vector<double> >& elastic_angles,
        const std::map<double,std::vector<double> >& elastic_pdf,
        const std::vector<double>& energy_grid,
        std::shared_ptr<BasicBivariateDist>& scattering_function,
        const double cutoff_angle_cosine,
        const double evaluation_tol,
        const bool discrete_function )
{
  // Make sure the energy grid is valid
  testPrecondition( energy_grid.back() > 0 );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
                                                      energy_grid.end() ) );

  testPrecondition( Data::valuesGreaterThanZero( energy_grid ) );

  // Get the distribution data
  std::vector<double> primary_grid( energy_grid.size() );
  std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
    secondary_dists( energy_grid.size() );

  for( size_t n = 0; n < energy_grid.size(); ++n )
  {
    if( cutoff_angle_cosine < elastic_angles.find( energy_grid[n] )->second.back() )
    {
      // Make sure the data is not discrete
      testPrecondition( !discrete_function );

      ThisType::createScatteringFunctionInSubrange(
        elastic_angles.find( energy_grid[n] )->second,
        elastic_pdf.find( energy_grid[n] )->second,
        energy_grid[n],
        cutoff_angle_cosine,
        primary_grid[n],
        secondary_dists[n] );
    }
    else
    {
      ThisType::createScatteringFunction(
        elastic_angles.find( energy_grid[n] )->second,
        elastic_pdf.find( energy_grid[n] )->second,
        energy_grid[n],
        primary_grid[n],
        secondary_dists[n],
        discrete_function );
    }
  }

  // Set the scattering function
  scattering_function.reset(
    new MonteCarlo::ElasticBasicBivariateDistribution<TwoDGridPolicy<TwoDInterpPolicy> >(
                                                           primary_grid,
                                                           secondary_dists,
                                                           cutoff_angle_cosine,
                                                           1e-6,
                                                           evaluation_tol ) );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElasticElectronScatteringDistributionNativeFactory_def.hpp
//---------------------------------------------------------------------------//
