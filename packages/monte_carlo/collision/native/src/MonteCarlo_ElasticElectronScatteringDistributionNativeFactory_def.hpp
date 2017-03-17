//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElasticElectronScatteringDistributionNativeFactory_def.hpp
//! \author Luke Kersting
//! \brief  The elastic scattering distribution Native factory def.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELASTIC_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_DEF_HPP
#define MONTE_CARLO_ELASTIC_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_DEF_HPP

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
template <typename TwoDInterpPolicy>
void ElasticElectronScatteringDistributionNativeFactory::createAnalogElasticDistribution(
    std::shared_ptr<const AnalogElasticElectronScatteringDistribution>&
        analog_elastic_distribution,
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double evalation_tol,
    const bool correlated_sampling_mode_on )
{
  ElasticElectronScatteringDistributionNativeFactory::createAnalogElasticDistribution<TwoDInterpPolicy>(
    analog_elastic_distribution,
    data_container.getCutoffElasticAngles(),
    data_container.getCutoffElasticPDF(),
    data_container.getElasticAngularEnergyGrid(),
    data_container.getAtomicNumber(),
    evalation_tol,
    correlated_sampling_mode_on );
}

// Create a cutoff elastic distribution
template <typename TwoDInterpPolicy>
void ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution(
    std::shared_ptr<const CutoffElasticElectronScatteringDistribution>&
        cutoff_elastic_distribution,
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const double evalation_tol )
{
  ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution<TwoDInterpPolicy>(
    cutoff_elastic_distribution,
    data_container.getCutoffElasticAngles(),
    data_container.getCutoffElasticPDF(),
    data_container.getElasticAngularEnergyGrid(),
    cutoff_angle_cosine,
    evalation_tol );
}

// Create a moment preserving elastic distribution
template <typename TwoDInterpPolicy>
void ElasticElectronScatteringDistributionNativeFactory::createMomentPreservingElasticDistribution(
    std::shared_ptr<const MomentPreservingElasticElectronScatteringDistribution>&
        moment_preserving_elastic_distribution,
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const double evalation_tol )
{
  testPostcondition( data_container.hasMomentPreservingData() );

  ElasticElectronScatteringDistributionNativeFactory::createMomentPreservingElasticDistribution<TwoDInterpPolicy>(
    moment_preserving_elastic_distribution,
    data_container.getElasticAngularEnergyGrid(),
    data_container.getMomentPreservingElasticDiscreteAngles(),
    data_container.getMomentPreservingElasticWeights(),
    cutoff_angle_cosine,
    evalation_tol );
}

//----------------------------------------------------------------------------//
//      ****ADJOINT DATA PUBLIC FUNCTIONS****
//----------------------------------------------------------------------------//

// Create the analog elastic distribution ( combined Cutoff and Screened Rutherford )
template <typename TwoDInterpPolicy>
void ElasticElectronScatteringDistributionNativeFactory::createAnalogElasticDistribution(
    std::shared_ptr<const AnalogElasticElectronScatteringDistribution>&
        analog_elastic_distribution,
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const double evalation_tol,
    const bool correlated_sampling_mode_on )
{
  ElasticElectronScatteringDistributionNativeFactory::createAnalogElasticDistribution<TwoDInterpPolicy>(
    analog_elastic_distribution,
    data_container.getAdjointCutoffElasticAngles(),
    data_container.getAdjointCutoffElasticPDF(),
    data_container.getAdjointElasticAngularEnergyGrid(),
    data_container.getAtomicNumber(),
    evalation_tol,
    correlated_sampling_mode_on );
}

// Create a cutoff elastic distribution
template <typename TwoDInterpPolicy>
void ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution(
    std::shared_ptr<const CutoffElasticElectronScatteringDistribution>&
        cutoff_elastic_distribution,
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const double evalation_tol )
{
  ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution<TwoDInterpPolicy>(
    cutoff_elastic_distribution,
    data_container.getAdjointCutoffElasticAngles(),
    data_container.getAdjointCutoffElasticPDF(),
    data_container.getAdjointElasticAngularEnergyGrid(),
    cutoff_angle_cosine,
    evalation_tol );
}

// Create a moment preserving elastic distribution
template <typename TwoDInterpPolicy>
void ElasticElectronScatteringDistributionNativeFactory::createMomentPreservingElasticDistribution(
    std::shared_ptr<const MomentPreservingElasticElectronScatteringDistribution>&
        moment_preserving_elastic_distribution,
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const double evalation_tol )
{
  testPostcondition( data_container.hasAdjointMomentPreservingData() );

ElasticElectronScatteringDistributionNativeFactory::createMomentPreservingElasticDistribution<TwoDInterpPolicy>(
    moment_preserving_elastic_distribution,
    data_container.getAdjointElasticAngularEnergyGrid(),
    data_container.getAdjointMomentPreservingElasticDiscreteAngles(),
    data_container.getAdjointMomentPreservingElasticWeights(),
    cutoff_angle_cosine,
    evalation_tol );
}

//----------------------------------------------------------------------------//
//      ****DATA CONTAINER INDEPENDENT PUBLIC FUNCTIONS****
//----------------------------------------------------------------------------//

// Create the analog elastic distribution ( combined Cutoff and Screened Rutherford )
/*! \details This function has been overloaded so it can be called without using
 *  the native data container. This functionality is neccessary for generating
 *  native moment preserving data without first creating native data files.
 */
template <typename TwoDInterpPolicy>
void ElasticElectronScatteringDistributionNativeFactory::createAnalogElasticDistribution(
    std::shared_ptr<const AnalogElasticElectronScatteringDistribution>&
        analog_elastic_distribution,
    const std::map<double,std::vector<double> >& cutoff_elastic_angles,
    const std::map<double,std::vector<double> >& cutoff_elastic_pdf,
    const std::vector<double>& angular_energy_grid,
    const unsigned atomic_number,
    const double evalation_tol,
    const bool correlated_sampling_mode_on )
{
  // Make sure the angular energy grid is valid
  testPrecondition( angular_energy_grid.back() > 0 );
  testPrecondition(
        Utility::Sort::isSortedAscending( angular_energy_grid.begin(),
                                          angular_energy_grid.end() ) );

  testPrecondition( Data::ValuesGreaterThanZero( angular_energy_grid ) );
  // Make sure the atomic number is valid
  testPrecondition( atomic_number > 0 );
  testPrecondition( atomic_number <= 100 );
  // Make sure the evaluation tolerance is valid
  testPrecondition( evalation_tol > 0.0 );
  testPrecondition( evalation_tol < 1.0 );

  // Create the scattering function
  std::shared_ptr<TwoDDist> scattering_function;

  // Create the scattering function
  ElasticElectronScatteringDistributionNativeFactory::createScatteringFunction<TwoDInterpPolicy>(
        cutoff_elastic_angles,
        cutoff_elastic_pdf,
        angular_energy_grid,
        scattering_function,
        evalation_tol,
        false );

  // Set the interpolation policy
  bool linlinlog_interpolation_mode_on = false;
  if ( TwoDInterpIsLinLinLog<TwoDInterpPolicy>::value )
    linlinlog_interpolation_mode_on = true;

  // Create analog distribution
  analog_elastic_distribution.reset(
      new AnalogElasticElectronScatteringDistribution(
                scattering_function,
                atomic_number,
                linlinlog_interpolation_mode_on ) );
}

// Create a cutoff elastic distribution
template <typename TwoDInterpPolicy>
void ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution(
    std::shared_ptr<const CutoffElasticElectronScatteringDistribution>&
        cutoff_elastic_distribution,
    const std::map<double,std::vector<double> >& cutoff_elastic_angles,
    const std::map<double,std::vector<double> >& cutoff_elastic_pdf,
    const std::vector<double>& angular_energy_grid,
    const double cutoff_angle_cosine,
    const double evalation_tol )
{
  // Create the scattering function
  std::shared_ptr<TwoDDist> scattering_function;
  ElasticElectronScatteringDistributionNativeFactory::createScatteringFunction<TwoDInterpPolicy>(
        cutoff_elastic_angles,
        cutoff_elastic_pdf,
        angular_energy_grid,
        scattering_function,
        evalation_tol,
        false );

  cutoff_elastic_distribution.reset(
        new CutoffElasticElectronScatteringDistribution(
                scattering_function,
                cutoff_angle_cosine ) );
}

// Create a moment preserving elastic distribution
template <typename TwoDInterpPolicy>
void ElasticElectronScatteringDistributionNativeFactory::createMomentPreservingElasticDistribution(
    std::shared_ptr<const MomentPreservingElasticElectronScatteringDistribution>&
        moment_preserving_elastic_distribution,
    const std::vector<double> angular_energy_grid,
    const std::map<double,std::vector<double> >& discrete_angles,
    const std::map<double,std::vector<double> >& discrete_weights,
    const double cutoff_angle_cosine,
    const double evalation_tol )
{
  // Create the scattering function
  std::shared_ptr<TwoDDist> scattering_function;
  ElasticElectronScatteringDistributionNativeFactory::createScatteringFunction<TwoDInterpPolicy>(
    discrete_angles,
    discrete_weights,
    angular_energy_grid,
    scattering_function,
    evalation_tol,
    true );

  // Create the moment preserving distribution
  moment_preserving_elastic_distribution.reset(
        new MonteCarlo::MomentPreservingElasticElectronScatteringDistribution(
                scattering_function,
                cutoff_angle_cosine ) );
}

// Return angle cosine grid with the evaluated pdf for the given energy
template <typename TwoDInterpPolicy>
void ElasticElectronScatteringDistributionNativeFactory::getAngularGridAndPDF(
    std::vector<double>& angular_grid,
    std::vector<double>& evaluated_pdf,
    const std::map<double,std::vector<double> >& angles,
    const std::map<double,std::vector<double> >& pdf,
    const double energy,
    const double evalation_tol )
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
    angular_grid = angles.at( energy );
    evaluated_pdf = pdf.at( energy );
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
        evalation_tol ) );

    // Use the angular grid for the energy bin closes to the energy
    if ( energy - lower_bin->first <= upper_bin->first - energy )
    {
      angular_grid = lower_bin->second;
    }
    else
    {
      angular_grid = upper_bin->second;
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

// Create the scattering function
/*! \details This function has been overloaded so it can be called without using
 *  the native data container. This functionality is neccessary for generating
 *  native moment preserving data without first creating native data files.
 */
template <typename TwoDInterpPolicy>
void ElasticElectronScatteringDistributionNativeFactory::createScatteringFunction(
        const std::map<double,std::vector<double> >& elastic_angles,
        const std::map<double,std::vector<double> >& elastic_pdf,
        const std::vector<double>& energy_grid,
        std::shared_ptr<TwoDDist>& scattering_function,
        const double evalation_tol,
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
    ElasticElectronScatteringDistributionNativeFactory::createScatteringFunction(
        elastic_angles,
        elastic_pdf,
        energy_grid[n],
        function_data[n],
        discrete_function );
  }

  // Set the scattering function
  scattering_function.reset(
    new Utility::InterpolatedFullyTabularTwoDDistribution<TwoDInterpPolicy>(
        function_data,
        1e-6,
        evalation_tol ) );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElasticElectronScatteringDistributionNativeFactory_def.hpp
//---------------------------------------------------------------------------//
