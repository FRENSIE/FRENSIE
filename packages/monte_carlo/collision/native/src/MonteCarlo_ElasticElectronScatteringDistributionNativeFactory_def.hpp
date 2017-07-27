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
#include "MonteCarlo_ScreenedRutherfordTraits.hpp"

namespace MonteCarlo{

template< class TwoDInterpPolicy >
struct TwoDInterpIsLinLinLog
{
    static const bool value = false;
};

template<>
struct TwoDInterpIsLinLinLog< Utility::LinLinLog >
{
    static const bool value = true;
};

//----------------------------------------------------------------------------//
//      ****FORWARD DATA PUBLIC FUNCTIONS****
//----------------------------------------------------------------------------//

// Create the analog elastic distribution ( combined Cutoff and Screened Rutherford )
template<typename TwoDInterpPolicy>
void ElasticElectronScatteringDistributionNativeFactory::createAnalogElasticDistribution(
    std::shared_ptr<const AnalogElasticElectronScatteringDistribution>&
        analog_elastic_distribution,
    const Teuchos::ArrayRCP<const double> energy_grid,
    const Teuchos::ArrayRCP<const double> cutoff_cross_section,
    const Teuchos::ArrayRCP<const double> total_cross_section,
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const bool correlated_sampling_mode_on,
    const double evaluation_tol )
{
  ThisType::createAnalogElasticDistribution<TwoDInterpPolicy>(
    analog_elastic_distribution,
    cutoff_cross_section,
    total_cross_section,
    energy_grid,
    data_container.getCutoffElasticAngles(),
    data_container.getCutoffElasticPDF(),
    data_container.getElasticAngularEnergyGrid(),
    data_container.getAtomicNumber(),
    correlated_sampling_mode_on,
    evaluation_tol );
}

// Create the hybrid elastic distribution ( combined Cutoff and Moment Preserving )
template<typename TwoDInterpPolicy>
void ElasticElectronScatteringDistributionNativeFactory::createHybridElasticDistribution(
    std::shared_ptr<const HybridElasticElectronScatteringDistribution>&
        hybrid_elastic_distribution,
    const Teuchos::ArrayRCP<const double> energy_grid,
    const Teuchos::ArrayRCP<const double> cutoff_cross_section,
    const Teuchos::ArrayRCP<const double> moment_preserving_cross_section,
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const bool correlated_sampling_mode_on,
    const double evaluation_tol )
{
  testPostcondition( data_container.hasMomentPreservingData() );

  ThisType::createHybridElasticDistribution<TwoDInterpPolicy>(
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
    correlated_sampling_mode_on,
    evaluation_tol );
}

// Create a cutoff elastic distribution
template<typename TwoDInterpPolicy>
void ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution(
    std::shared_ptr<const CutoffElasticElectronScatteringDistribution>&
        cutoff_elastic_distribution,
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const bool correlated_sampling_mode_on,
    const double evaluation_tol )
{
  ThisType::createCutoffElasticDistribution<TwoDInterpPolicy>(
    cutoff_elastic_distribution,
    data_container.getCutoffElasticAngles(),
    data_container.getCutoffElasticPDF(),
    data_container.getElasticAngularEnergyGrid(),
    cutoff_angle_cosine,
    correlated_sampling_mode_on,
    evaluation_tol );
}

// Create a moment preserving elastic distribution
template<typename TwoDInterpPolicy>
void ElasticElectronScatteringDistributionNativeFactory::createMomentPreservingElasticDistribution(
    std::shared_ptr<const MomentPreservingElasticElectronScatteringDistribution>&
        moment_preserving_elastic_distribution,
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const bool correlated_sampling_mode_on,
    const double evaluation_tol )
{
  testPostcondition( data_container.hasMomentPreservingData() );

  ThisType::createMomentPreservingElasticDistribution<TwoDInterpPolicy>(
    moment_preserving_elastic_distribution,
    data_container.getElasticAngularEnergyGrid(),
    data_container.getMomentPreservingElasticDiscreteAngles(),
    data_container.getMomentPreservingElasticWeights(),
    cutoff_angle_cosine,
    correlated_sampling_mode_on,
    evaluation_tol );
}

//----------------------------------------------------------------------------//
//      ****ADJOINT DATA PUBLIC FUNCTIONS****
//----------------------------------------------------------------------------//

// Create the analog elastic distribution ( combined Cutoff and Screened Rutherford )
template<typename TwoDInterpPolicy>
void ElasticElectronScatteringDistributionNativeFactory::createAnalogElasticDistribution(
    std::shared_ptr<const AnalogElasticElectronScatteringDistribution>&
        analog_elastic_distribution,
    const Teuchos::ArrayRCP<const double> energy_grid,
    const Teuchos::ArrayRCP<const double> cutoff_cross_section,
    const Teuchos::ArrayRCP<const double> total_cross_section,
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const bool correlated_sampling_mode_on,
    const double evaluation_tol )
{
  ThisType::createAnalogElasticDistribution<TwoDInterpPolicy>(
    analog_elastic_distribution,
    cutoff_cross_section,
    total_cross_section,
    energy_grid,
    data_container.getAdjointCutoffElasticAngles(),
    data_container.getAdjointCutoffElasticPDF(),
    data_container.getAdjointElasticAngularEnergyGrid(),
    data_container.getAtomicNumber(),
    correlated_sampling_mode_on,
    evaluation_tol );
}

// Create the hybrid elastic distribution ( combined Cutoff and Moment Preserving )
template<typename TwoDInterpPolicy>
void ElasticElectronScatteringDistributionNativeFactory::createHybridElasticDistribution(
    std::shared_ptr<const HybridElasticElectronScatteringDistribution>&
        hybrid_elastic_distribution,
    const Teuchos::ArrayRCP<const double> energy_grid,
    const Teuchos::ArrayRCP<const double> cutoff_cross_section,
    const Teuchos::ArrayRCP<const double> moment_preserving_cross_section,
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const bool correlated_sampling_mode_on,
    const double evaluation_tol )
{
  testPostcondition( data_container.hasAdjointMomentPreservingData() );

ThisType::createHybridElasticDistribution<TwoDInterpPolicy>(
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
    correlated_sampling_mode_on,
    evaluation_tol );
}

// Create a cutoff elastic distribution
template<typename TwoDInterpPolicy>
void ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution(
    std::shared_ptr<const CutoffElasticElectronScatteringDistribution>&
        cutoff_elastic_distribution,
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const bool correlated_sampling_mode_on,
    const double evaluation_tol )
{
  ThisType::createCutoffElasticDistribution<TwoDInterpPolicy>(
    cutoff_elastic_distribution,
    data_container.getAdjointCutoffElasticAngles(),
    data_container.getAdjointCutoffElasticPDF(),
    data_container.getAdjointElasticAngularEnergyGrid(),
    cutoff_angle_cosine,
    correlated_sampling_mode_on,
    evaluation_tol );
}

// Create a moment preserving elastic distribution
template<typename TwoDInterpPolicy>
void ElasticElectronScatteringDistributionNativeFactory::createMomentPreservingElasticDistribution(
    std::shared_ptr<const MomentPreservingElasticElectronScatteringDistribution>&
        moment_preserving_elastic_distribution,
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const bool correlated_sampling_mode_on,
    const double evaluation_tol )
{
  testPostcondition( data_container.hasAdjointMomentPreservingData() );

ThisType::createMomentPreservingElasticDistribution<TwoDInterpPolicy>(
    moment_preserving_elastic_distribution,
    data_container.getAdjointElasticAngularEnergyGrid(),
    data_container.getAdjointMomentPreservingElasticDiscreteAngles(),
    data_container.getAdjointMomentPreservingElasticWeights(),
    cutoff_angle_cosine,
    correlated_sampling_mode_on,
    evaluation_tol );
}

//----------------------------------------------------------------------------//
//      ****DATA CONTAINER INDEPENDENT PUBLIC FUNCTIONS****
//----------------------------------------------------------------------------//

// Create the analog elastic distribution ( combined Cutoff and Screened Rutherford )
/*! \details This function has been overloaded so it can be called without using
 *  the native data container. This functionality is neccessary for generating
 *  native moment preserving data without first creating native data files.
 */
template<typename TwoDInterpPolicy>
void ElasticElectronScatteringDistributionNativeFactory::createAnalogElasticDistribution(
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
    const double evaluation_tol )
{
  // Make sure the cross sections are valid
  testPrecondition( Data::ValuesGreaterThanOrEqualToZero( cutoff_cross_section ) );
  testPrecondition( Data::ValuesGreaterThanOrEqualToZero( total_cross_section ) );
  testPrecondition( total_cross_section.size() == cutoff_cross_section.size() );
  // Make sure the maps are valid
  testPrecondition( cutoff_elastic_pdf.size() == angular_energy_grid.size() );
  testPrecondition( cutoff_elastic_angles.size() == angular_energy_grid.size() );

  // Make sure the energy grids are valid
//  testPrecondition( energy_grid.back() > 0 );
  testPrecondition(
        Utility::Sort::isSortedAscending( energy_grid.begin(),
                                          energy_grid.end() ) );
  testPrecondition( Data::ValuesGreaterThanZero( energy_grid ) );
  testPrecondition( angular_energy_grid.back() > 0 );
  testPrecondition(
        Utility::Sort::isSortedAscending( angular_energy_grid.begin(),
                                          angular_energy_grid.end() ) );
  testPrecondition( Data::ValuesGreaterThanZero( angular_energy_grid ) );
  // Make sure the atomic number is valid
  testPrecondition( atomic_number > 0 );
  testPrecondition( atomic_number <= 100 );
  // Make sure the evaluation tolerance is valid
  testPrecondition( evaluation_tol > 0.0 );
  testPrecondition( evaluation_tol < 1.0 );

  // Get the distribution data
  TwoDDist::DistributionType function_data( angular_energy_grid.size() );
  std::vector<double> cutoff_ratios( angular_energy_grid.size() );
  std::vector<double> etas( angular_energy_grid.size() );

  // Create the cross section ratios
  std::shared_ptr<const Utility::OneDDistribution> cross_section_ratios;
  createCutoffCrossSectionRatios( energy_grid,
                                  cutoff_cross_section,
                                  total_cross_section,
                                  cross_section_ratios );

  // Create the screened Rutherford traits
  std::shared_ptr<const SRTraits> sr_traits(
    new SRTraits( atomic_number ) );

  // Create the scattering function
  std::shared_ptr<TwoDDist> scattering_function;
  ThisType::createAnalogScatteringFunction(
        cross_section_ratios,
        sr_traits,
        cutoff_elastic_angles,
        cutoff_elastic_pdf,
        angular_energy_grid,
        scattering_function,
        evaluation_tol );

  // Create analog distribution
  analog_elastic_distribution.reset(
      new AnalogElasticElectronScatteringDistribution(
                scattering_function,
                cross_section_ratios,
                sr_traits,
                correlated_sampling_mode_on ) );
}

// Create the hybrid elastic distribution ( combined Cutoff and Moment Preserving )
template<typename TwoDInterpPolicy>
void ElasticElectronScatteringDistributionNativeFactory::createHybridElasticDistribution(
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
    const double evaluation_tol )
{
  // Make sure the angular energy grid is valid
  testPrecondition( angular_energy_grid.back() > 0 );
  testPrecondition(
        Utility::Sort::isSortedAscending( angular_energy_grid.begin(),
                                          angular_energy_grid.end() ) );

  testPrecondition( Data::ValuesGreaterThanZero( angular_energy_grid ) );
  // Make sure the cutoff angle cosine is valid
  testPrecondition( cutoff_angle_cosine > -1.0 );
  testPrecondition( cutoff_angle_cosine <= 1.0 );
  // Make sure the evaluation tolerance is valid
  testPrecondition( evaluation_tol > 0.0 );
  testPrecondition( evaluation_tol < 1.0 );

  // Create the discrete scattering function
  std::shared_ptr<TwoDDist> discrete_function;
  ThisType::createScatteringFunction<TwoDInterpPolicy>(
                moment_preserving_angles,
                moment_preserving_weights,
                angular_energy_grid,
                discrete_function,
                1.0,
                evaluation_tol,
                true );

  // Create the continuous scattering function
  std::shared_ptr<TwoDDist> continuous_function;
  ThisType::createScatteringFunction<TwoDInterpPolicy>(
                cutoff_elastic_angles,
                cutoff_elastic_pdf,
                angular_energy_grid,
                continuous_function,
                cutoff_angle_cosine,
                evaluation_tol,
                false );

  // Create the full continuous scattering function
  std::shared_ptr<TwoDDist> full_continuous_function;
  ThisType::createScatteringFunction<TwoDInterpPolicy>(
                cutoff_elastic_angles,
                cutoff_elastic_pdf,
                angular_energy_grid,
                full_continuous_function,
                1.0,
                evaluation_tol,
                false );

  // Create the cross section ratios
  std::shared_ptr<const Utility::OneDDistribution> cross_section_ratios;
  createHybridCrossSectionRatios(
                energy_grid,
                cutoff_cross_section,
                moment_preserving_cross_section,
                full_continuous_function,
                cutoff_angle_cosine,
                cross_section_ratios );

  // Create hybrid distribution
  hybrid_elastic_distribution.reset(
        new HybridElasticElectronScatteringDistribution(
                continuous_function,
                discrete_function,
                cross_section_ratios,
                cutoff_angle_cosine,
                correlated_sampling_mode_on,
                evaluation_tol ) );
}

// Create a cutoff elastic distribution
template<typename TwoDInterpPolicy>
void ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution(
    std::shared_ptr<const CutoffElasticElectronScatteringDistribution>&
        cutoff_elastic_distribution,
    const std::map<double,std::vector<double> >& cutoff_elastic_angles,
    const std::map<double,std::vector<double> >& cutoff_elastic_pdf,
    const std::vector<double>& angular_energy_grid,
    const double cutoff_angle_cosine,
    const bool correlated_sampling_mode_on,
    const double evaluation_tol )
{
  // Make sure the angular energy grid is valid
  testPrecondition( angular_energy_grid.back() > 0 );
  testPrecondition(
        Utility::Sort::isSortedAscending( angular_energy_grid.begin(),
                                          angular_energy_grid.end() ) );

  testPrecondition( Data::ValuesGreaterThanZero( angular_energy_grid ) );
  // Make sure the cutoff angle cosine is valid
  testPrecondition( cutoff_angle_cosine > -1.0 );
  testPrecondition( cutoff_angle_cosine <= 1.0 );
  // Make sure the evaluation tolerance is valid
  testPrecondition( evaluation_tol > 0.0 );
  testPrecondition( evaluation_tol < 1.0 );

  // Create the scattering function
  std::shared_ptr<TwoDDist> scattering_function;
  ThisType::createScatteringFunction<TwoDInterpPolicy>(
        cutoff_elastic_angles,
        cutoff_elastic_pdf,
        angular_energy_grid,
        scattering_function,
        cutoff_angle_cosine,
        evaluation_tol,
        false );

  if( cutoff_angle_cosine < 0.999999 )
  {
    // Create the full scattering function
    std::shared_ptr<TwoDDist> full_scattering_function;
    ThisType::createScatteringFunction<TwoDInterpPolicy>(
        cutoff_elastic_angles,
        cutoff_elastic_pdf,
        angular_energy_grid,
        full_scattering_function,
        1.0,
        evaluation_tol,
        false );

    cutoff_elastic_distribution.reset(
        new CutoffElasticElectronScatteringDistribution(
                full_scattering_function,
                scattering_function,
                cutoff_angle_cosine,
                correlated_sampling_mode_on ) );
  }
  else
  {
    cutoff_elastic_distribution.reset(
        new CutoffElasticElectronScatteringDistribution(
                scattering_function,
                correlated_sampling_mode_on ) );
  }
}

// Create a moment preserving elastic distribution
template<typename TwoDInterpPolicy>
void ElasticElectronScatteringDistributionNativeFactory::createMomentPreservingElasticDistribution(
    std::shared_ptr<const MomentPreservingElasticElectronScatteringDistribution>&
        moment_preserving_elastic_distribution,
    const std::vector<double> angular_energy_grid,
    const std::map<double,std::vector<double> >& discrete_angles,
    const std::map<double,std::vector<double> >& discrete_weights,
    const double cutoff_angle_cosine,
    const bool correlated_sampling_mode_on,
    const double evaluation_tol )
{
  // Make sure the angular energy grid is valid
  testPrecondition( angular_energy_grid.back() > 0 );
  testPrecondition(
        Utility::Sort::isSortedAscending( angular_energy_grid.begin(),
                                          angular_energy_grid.end() ) );

  testPrecondition( Data::ValuesGreaterThanZero( angular_energy_grid ) );
  // Make sure the cutoff angle cosine is valid
  testPrecondition( cutoff_angle_cosine > -1.0 );
  testPrecondition( cutoff_angle_cosine <= 1.0 );
  // Make sure the evaluation tolerance is valid
  testPrecondition( evaluation_tol > 0.0 );
  testPrecondition( evaluation_tol < 1.0 );

  // Create the scattering function
  std::shared_ptr<TwoDDist> scattering_function;
  ThisType::createScatteringFunction<TwoDInterpPolicy>(
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
                cutoff_angle_cosine,
                correlated_sampling_mode_on ) );
}

//// Create a screened Rutherford elastic distribution
//template<typename TwoDInterpPolicy>
//void ElasticElectronScatteringDistributionNativeFactory::createScreenedRutherfordElasticDistribution(
//    std::shared_ptr<const ScreenedRutherfordElasticElectronScatteringDistribution>&
//        screened_rutherford_elastic_distribution,
//    const std::shared_ptr<const CutoffElasticElectronScatteringDistribution>&
//        cutoff_elastic_distribution,
//    const unsigned atomic_number )
//{
//  // Create the screened Rutherford distribution
//  screened_rutherford_elastic_distribution.reset(
//        new MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution(
//                cutoff_elastic_distribution,
//                atomic_number ) );
//}

//// Return angle cosine grid for given grid energy bin
//template<typename TwoDInterpPolicy>
//std::vector<double> ElasticElectronScatteringDistributionNativeFactory::getAngularGrid(
//    const std::map<double, std::vector<double> >& raw_cutoff_elastic_angles,
//    const double energy,
//    const double cutoff_angle_cosine )
//{
//  testPrecondition( energy >= raw_cutoff_elastic_angles.begin()->first );
//  testPrecondition( energy <= raw_cutoff_elastic_angles.rbegin()->first );

//  // Get the angular grid
//  std::vector<double> raw_grid;
//  if( raw_cutoff_elastic_angles.count( energy ) > 0 )
//  {
//    raw_grid = raw_cutoff_elastic_angles.at( energy );
//  }
//  else
//  {
//    std::map<double,std::vector<double>>::const_iterator lower_bin, upper_bin;
//    upper_bin = raw_cutoff_elastic_angles.upper_bound( energy );
//    lower_bin = upper_bin;
//    --lower_bin;

//    // Use the angular grid for the energy bin closes to the energy
//    if ( energy - lower_bin->first <= upper_bin->first - energy )
//    {
//      raw_grid = lower_bin->second;
//    }
//    else
//    {
//      raw_grid = upper_bin->second;
//    }
//  }

//  return ThisType::getAngularGrid(
//            raw_grid,
//            cutoff_angle_cosine );
//}

//// Return angle cosine grid for the given cutoff angle
//template<typename TwoDInterpPolicy>
//std::vector<double> ElasticElectronScatteringDistributionNativeFactory::getAngularGrid(
//    const std::vector<double>& raw_cutoff_elastic_angles,
//    const double cutoff_angle_cosine )
//{
//  // Find the first angle cosine above the cutoff angle cosine
//  std::vector<double>::const_iterator start;
//  for ( start = raw_cutoff_elastic_angles.begin(); start != raw_cutoff_elastic_angles.end(); start++ )
//  {
//    if ( *start > cutoff_angle_cosine )
//    {
//      break;
//    }
//  }

//  std::vector<double> grid( start, raw_cutoff_elastic_angles.end() );

//   grid.insert( grid.begin(), cutoff_angle_cosine );

//  return grid;
//}

// Return angle cosine grid with the evaluated pdf for the given energy
template<typename TwoDInterpPolicy>
void ElasticElectronScatteringDistributionNativeFactory::getAngularGridAndPDF(
    std::vector<double>& angular_grid,
    std::vector<double>& evaluated_pdf,
    const std::map<double,std::vector<double> >& angles,
    const std::map<double,std::vector<double> >& pdf,
    const double energy,
    const double cutoff_angle_cosine,
    const double evaluation_tol )
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
//    angular_grid = angles.at( energy );
//    evaluated_pdf = pdf.at( energy );

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
    TwoDDist::DistributionType function_data( 2 );

    // Get the lower angular distributions
    function_data[0].first = lower_bin->first;
    function_data[0].second.reset(
      new const TabularDist( lower_bin->second, pdf.at( lower_bin->first ) ) );

    // Get the upper angular distributions
    function_data[1].first = upper_bin->first;
    function_data[1].second.reset(
      new const TabularDist( upper_bin->second, pdf.at( upper_bin->first ) ) );

    // Create the TwoDDistribution between the two distributions
    std::shared_ptr<TwoDDist> scattering_function(
      new Utility::InterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy>(
        function_data,
        1e-6,
        evaluation_tol ) );

    // Use the angular grid for the energy bin closes to the energy
    if ( energy - lower_bin->first <= upper_bin->first - energy )
    {
      angular_grid = ThisType::getAngularGrid(
                            lower_bin->second,
                            cutoff_angle_cosine );
    }
    else
    {
      angular_grid = ThisType::getAngularGrid(
                            upper_bin->second,
                            cutoff_angle_cosine );
    }

    // Evaluate the pdf on the angular grid
    evaluated_pdf.resize( angular_grid.size() );
    for ( unsigned i = 0; i < angular_grid.size(); i++ )
    {
      evaluated_pdf[i] =
        scattering_function->evaluateSecondaryConditionalPDFExact(
                                                    energy, angular_grid[i] );
    }
    testPostcondition( evaluated_pdf.size() > 1 );
    testPostcondition( angular_grid.size() > 1 );
  }
}

//----------------------------------------------------------------------------//
//      ****PRIVATE FUNCTIONS****
//----------------------------------------------------------------------------//

// Create the ratio of the cutoff to the total elastic cross section
template<typename TwoDInterpPolicy>
void ElasticElectronScatteringDistributionNativeFactory::createCutoffCrossSectionRatios(
    const Teuchos::ArrayRCP<const double> raw_energy_grid,
    const Teuchos::ArrayRCP<const double> cutoff_cross_section,
    const Teuchos::ArrayRCP<const double> total_cross_section,
    std::shared_ptr<const Utility::OneDDistribution>& cross_section_ratios )
{
  // Calculate the ratio of the cutoff to the total cross section
  std::vector<double> cross_section_ratio( raw_energy_grid.size() );
  std::vector<double> energy_grid( raw_energy_grid.size() );
  for( unsigned n = 0; n < energy_grid.size(); ++n )
  {
    // Get the energy
    energy_grid[n] = raw_energy_grid[n];

    // Get the ratio of the cutoff to the total cross section
    cross_section_ratio[n] = cutoff_cross_section[n]/total_cross_section[n];
  }
    // Create cross section ratios
    cross_section_ratios.reset(
      new const TabularDist( energy_grid, cross_section_ratio ) );
}

// Create the ratio of the cutoff to the moment preserving cross section
template<typename TwoDInterpPolicy>
void ElasticElectronScatteringDistributionNativeFactory::createHybridCrossSectionRatios(
    const Teuchos::ArrayRCP<const double> raw_energy_grid,
    const Teuchos::ArrayRCP<const double> cutoff_cross_section,
    const Teuchos::ArrayRCP<const double> moment_preserving_cross_section,
    const std::shared_ptr<TwoDDist>& cutoff_scattering_function,
    const double cutoff_angle_cosine,
    std::shared_ptr<const Utility::OneDDistribution>& cross_section_ratios )
{
  // Calculate the ratio of the cutoff to the moment preserving cross section
  std::vector<double> cross_section_ratio( raw_energy_grid.size() );
  std::vector<double> energy_grid( raw_energy_grid.size() );
  for( unsigned n = 0; n < energy_grid.size(); ++n )
  {
    // Get the energy
    energy_grid[n] = raw_energy_grid[n];

    // Get the cutoff cdf value at the angle cosine cutoff
    double cutoff_cdf =
            cutoff_scattering_function->evaluateSecondaryConditionalCDFExact(
                                                        energy_grid[n],
                                                        cutoff_angle_cosine );

    // Get the ratio of the cutoff to the moment preserving cross section
    cross_section_ratio[n] = cutoff_cross_section[n]*cutoff_cdf/
                                            moment_preserving_cross_section[n];
  }
    // Create cross section ratios
    cross_section_ratios.reset(
      new const TabularDist( energy_grid, cross_section_ratio ) );
}

//// Create the hybrid elastic scattering functions
//template<typename TwoDInterpPolicy>
//void ElasticElectronScatteringDistributionNativeFactory::createHybridScatteringFunction(
//    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
//    const Teuchos::ArrayRCP<const double> energy_grid,
//    const Teuchos::ArrayRCP<const double> cutoff_cross_section,
//    const std::map<double,std::vector<double> >& cutoff_elastic_angles,
//    const std::map<double,std::vector<double> >& cutoff_elastic_pdf,
//    const Teuchos::ArrayRCP<const double> moment_preserving_cross_section,
//    const std::map<double,std::vector<double> >& moment_preserving_angles,
//    const std::map<double,std::vector<double> >& moment_preserving_weights,
//    const std::vector<double>& angular_energy_grid,
//    const double cutoff_angle_cosine,
//    std::shared_ptr<HybridDistribution>& hybrid_functions )
//{
//  // Get the distribution data
//  HybridDistribution function_data( angular_energy_grid.size() );

//  // Loop through all energies below the max energy
//  for( unsigned n = 0; n < angular_energy_grid.size(); ++n )
//  {
//    ThisType::createHybridScatteringFunction<TwoDInterpPolicy>(
//        grid_searcher,
//        energy_grid,
//        cutoff_cross_section,
//        cutoff_elastic_angles,
//        cutoff_elastic_pdf,
//        moment_preserving_cross_section,
//        moment_preserving_angles,
//        moment_preserving_weights,
//        angular_energy_grid[n],
//        cutoff_angle_cosine,
//        function_data[n] );
//  }

//  // Set the cutoff scattering function
//  hybrid_functions.reset( new HybridDistribution( function_data ) );
//}

//// Create the hybrid elastic scattering functions and cross section ratio
//template<typename TwoDInterpPolicy>
//void ElasticElectronScatteringDistributionNativeFactory::createHybridScatteringFunction(
//    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
//    const Teuchos::ArrayRCP<const double> energy_grid,
//    const Teuchos::ArrayRCP<const double> cutoff_cross_section,
//    const std::map<double,std::vector<double> >& cutoff_elastic_angles,
//    const std::map<double,std::vector<double> >& cutoff_elastic_pdf,
//    const Teuchos::ArrayRCP<const double> moment_preserving_cross_section,
//    const std::map<double,std::vector<double> >& moment_preserving_angles,
//    const std::map<double,std::vector<double> >& moment_preserving_weights,
//    const double energy,
//    const double cutoff_angle_cosine,
//    HybridFunction& function_data )
//{
//  testPrecondition( cutoff_elastic_angles.count( energy ) );

//  // Create the cutoff elastic scattering function
//  function_data.first = energy;

//  function_data.second.reset(
//    new const TabularDist( cutoff_elastic_angles.find( energy )->second,
//                           cutoff_elastic_pdf.find( energy )->second ) );

//  function_data.third.reset(
//    new const DiscreteDist( moment_preserving_angles.find( energy )->second,
//                            moment_preserving_weights.find( energy )->second ) );

//  unsigned energy_index =
//    grid_searcher->findLowerBinIndex( energy );

//  // Get the moment preserving cross section at the given energy
//  double mp_cross_section_i =
//    Utility::LinLin::interpolate( energy_grid[energy_index],
//                                  energy_grid[energy_index+1],
//                                  energy,
//                                  moment_preserving_cross_section[energy_index],
//                                  moment_preserving_cross_section[energy_index+1] );

//  // Get the cutoff cross section at the given energy
//  double cutoff_cross_section_i =
//    Utility::LinLin::interpolate( energy_grid[energy_index],
//                                  energy_grid[energy_index+1],
//                                  energy,
//                                  cutoff_cross_section[energy_index],
//                                  cutoff_cross_section[energy_index+1] );

//  // Get the cutoff cdf value at the angle cosine cutoff
//  double cutoff_cdf = function_data.second->evaluateCDF( cutoff_angle_cosine );

//  // Get the ratio of the cutoff the moment preserving cross section
//  function_data.fourth = cutoff_cross_section_i*cutoff_cdf/mp_cross_section_i;
//}

//// Create the scattering function at the given energy
///*! \details This function has been overloaded so it can be called without using
// *  the native data container. This functionality is neccessary for generating
// *  native moment preserving data without first creating native data files.
// */
//template<typename TwoDInterpPolicy>
//void ElasticElectronScatteringDistributionNativeFactory::createScatteringFunction(
//        const std::map<double,std::vector<double> >& elastic_angles,
//        const std::map<double,std::vector<double> >& elastic_pdf,
//        const double energy,
//        TwoDFunction& function_data,
//        const bool discrete_function )
//{
//  // Make sure the energy is valid
//  testPrecondition( elastic_angles.count( energy ) );

//  // Get the incoming energy
//  function_data.first = energy;

//  // Create the distribution at the energy
//  if ( discrete_function )
//  {
//    // Create discrete distribution
//    function_data.second.reset(
//      new const DiscreteDist( elastic_angles.find( energy )->second,
//                              elastic_pdf.find( energy )->second,
//                              false,
//                              true ) );
//  }
//  else
//  {
//    // Create tabular distribution
//    function_data.second.reset(
//      new const TabularDist( elastic_angles.find( energy )->second,
//                             elastic_pdf.find( energy )->second ) );
//  }
//}

// Create the analog scattering function
template<typename TwoDInterpPolicy>
void ElasticElectronScatteringDistributionNativeFactory::createAnalogScatteringFunction(
    const std::shared_ptr<const Utility::OneDDistribution>& cross_section_ratios,
    const std::shared_ptr<const SRTraits>& sr_traits,
    const std::map<double,std::vector<double> >& elastic_angles,
    const std::map<double,std::vector<double> >& elastic_pdf,
    const std::vector<double>& energy_grid,
    std::shared_ptr<TwoDDist>& scattering_function,
    const double evaluation_tol )
{
  // Make sure the energy grid is valid
  testPrecondition( energy_grid.back() > 0 );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
                                                      energy_grid.end() ) );

  testPrecondition( Data::ValuesGreaterThanZero( energy_grid ) );

  // Get the distribution data
  TwoDDist::DistributionType function_data( energy_grid.size() );

  for( unsigned n = 0; n < energy_grid.size(); ++n )
  {
    // Set the energy
    function_data[n].first = energy_grid[n];

    // Get the value of moliere's eta
    double eta = sr_traits->evaluateMoliereScreeningConstant( energy_grid[n] );

    // Get the ratio of the cutoff to total elastic cross section
    double cutoff_ratio = cross_section_ratios->evaluate( energy_grid[n] );


  // Create analog elastic distribution
  function_data[n].second.reset(
    new const AnalogDist( elastic_angles.find( energy_grid[n] )->second,
                          elastic_pdf.find( energy_grid[n] )->second,
                          eta,
                          cutoff_ratio ) );
  }

  // Set the scattering function
  scattering_function.reset(
    new Utility::InterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy>(
        function_data,
        1e-6,
        evaluation_tol ) );
}

// Create the scattering function
/*! \details This function has been overloaded so it can be called without using
 *  the native data container. This functionality is neccessary for generating
 *  native moment preserving data without first creating native data files.
 */
template<typename TwoDInterpPolicy>
void ElasticElectronScatteringDistributionNativeFactory::createScatteringFunction(
        const std::map<double,std::vector<double> >& elastic_angles,
        const std::map<double,std::vector<double> >& elastic_pdf,
        const std::vector<double>& energy_grid,
        std::shared_ptr<TwoDDist>& scattering_function,
        const double cutoff_angle_cosine,
        const double evaluation_tol,
        const bool discrete_function )
{
  // Make sure the energy grid is valid
  testPrecondition( energy_grid.back() > 0 );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
                                                      energy_grid.end() ) );

  testPrecondition( Data::ValuesGreaterThanZero( energy_grid ) );

  // Get the distribution data
  TwoDDist::DistributionType function_data( energy_grid.size() );

  for( unsigned n = 0; n < energy_grid.size(); ++n )
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
        function_data[n] );
    }
    else
    {
      ThisType::createScatteringFunction(
        elastic_angles.find( energy_grid[n] )->second,
        elastic_pdf.find( energy_grid[n] )->second,
        energy_grid[n],
        function_data[n],
        discrete_function );
    }
  }

  // Set the scattering function
  scattering_function.reset(
    new Utility::InterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy>(
        function_data,
        1e-6,
        evaluation_tol ) );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElasticElectronScatteringDistributionNativeFactory_def.hpp
//---------------------------------------------------------------------------//
