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

//----------------------------------------------------------------------------//
//      ****FORWARD DATA PUBLIC FUNCTIONS****
//----------------------------------------------------------------------------//

// Create the analog elastic distribution ( combined Cutoff and Screened Rutherford )
template <bool use_linlinlog_interpolation>
void ElasticElectronScatteringDistributionNativeFactory::createAnalogElasticDistribution(
    std::shared_ptr<const AnalogElasticElectronScatteringDistribution>&
        analog_elastic_distribution,
    const Data::ElectronPhotonRelaxationDataContainer& data_container )
{
  ElasticElectronScatteringDistributionNativeFactory::createAnalogElasticDistribution<use_linlinlog_interpolation>(
    analog_elastic_distribution,
    data_container.getCutoffElasticAngles(),
    data_container.getCutoffElasticPDF(),
    data_container.getElasticAngularEnergyGrid(),
    data_container.getAtomicNumber() );
}

// Create the hybrid elastic distribution ( combined Cutoff and Moment Preserving )
template <bool use_linlinlog_interpolation>
void ElasticElectronScatteringDistributionNativeFactory::createHybridElasticDistribution(
    std::shared_ptr<const HybridElasticElectronScatteringDistribution>&
        hybrid_elastic_distribution,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
    const Teuchos::ArrayRCP<const double> energy_grid,
    const Teuchos::ArrayRCP<const double> cutoff_cross_section,
    const Teuchos::ArrayRCP<const double> moment_preserving_cross_section,
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double& cutoff_angle_cosine )
{
  testPostcondition( data_container.hasMomentPreservingData() );

ElasticElectronScatteringDistributionNativeFactory::createHybridElasticDistribution<use_linlinlog_interpolation>(
    hybrid_elastic_distribution,
    grid_searcher,
    energy_grid,
    cutoff_cross_section,
    data_container.getCutoffElasticAngles(),
    data_container.getCutoffElasticPDF(),
    moment_preserving_cross_section,
    data_container.getMomentPreservingElasticDiscreteAngles(),
    data_container.getMomentPreservingElasticWeights(),
    data_container.getElasticAngularEnergyGrid(),
    cutoff_angle_cosine );
}

// Create a cutoff elastic distribution
template <typename TwoDInterpPolicy>
void ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution(
    std::shared_ptr<const CutoffElasticElectronScatteringDistribution>&
        cutoff_elastic_distribution,
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double& cutoff_angle_cosine )
{
  ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution<TwoDInterpPolicy>(
    cutoff_elastic_distribution,
    data_container.getCutoffElasticAngles(),
    data_container.getCutoffElasticPDF(),
    data_container.getElasticAngularEnergyGrid(),
    cutoff_angle_cosine );
}

// Create a moment preserving elastic distribution
template <typename TwoDInterpPolicy>
void ElasticElectronScatteringDistributionNativeFactory::createMomentPreservingElasticDistribution(
    std::shared_ptr<const MomentPreservingElasticElectronScatteringDistribution>&
        moment_preserving_elastic_distribution,
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double& cutoff_angle_cosine )
{
  testPostcondition( data_container.hasMomentPreservingData() );

  ElasticElectronScatteringDistributionNativeFactory::createMomentPreservingElasticDistribution<TwoDInterpPolicy>(
    moment_preserving_elastic_distribution,
    data_container.getElasticAngularEnergyGrid(),
    data_container.getMomentPreservingElasticDiscreteAngles(),
    data_container.getMomentPreservingElasticWeights(),
    cutoff_angle_cosine );
}

//----------------------------------------------------------------------------//
//      ****ADJOINT DATA PUBLIC FUNCTIONS****
//----------------------------------------------------------------------------//

// Create the analog elastic distribution ( combined Cutoff and Screened Rutherford )
template <bool use_linlinlog_interpolation>
void ElasticElectronScatteringDistributionNativeFactory::createAnalogElasticDistribution(
    std::shared_ptr<const AnalogElasticElectronScatteringDistribution>&
        analog_elastic_distribution,
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container )
{
  ElasticElectronScatteringDistributionNativeFactory::createAnalogElasticDistribution<use_linlinlog_interpolation>(
    analog_elastic_distribution,
    data_container.getAdjointCutoffElasticAngles(),
    data_container.getAdjointCutoffElasticPDF(),
    data_container.getAdjointElasticAngularEnergyGrid(),
    data_container.getAtomicNumber() );
}

// Create the hybrid elastic distribution ( combined Cutoff and Moment Preserving )
template <bool use_linlinlog_interpolation>
void ElasticElectronScatteringDistributionNativeFactory::createHybridElasticDistribution(
    std::shared_ptr<const HybridElasticElectronScatteringDistribution>&
        hybrid_elastic_distribution,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
    const Teuchos::ArrayRCP<const double> energy_grid,
    const Teuchos::ArrayRCP<const double> cutoff_cross_section,
    const Teuchos::ArrayRCP<const double> moment_preserving_cross_section,
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const double& cutoff_angle_cosine )
{
  testPostcondition( data_container.hasAdjointMomentPreservingData() );

ElasticElectronScatteringDistributionNativeFactory::createHybridElasticDistribution<use_linlinlog_interpolation>(
    hybrid_elastic_distribution,
    grid_searcher,
    energy_grid,
    cutoff_cross_section,
    data_container.getAdjointCutoffElasticAngles(),
    data_container.getAdjointCutoffElasticPDF(),
    moment_preserving_cross_section,
    data_container.getAdjointMomentPreservingElasticDiscreteAngles(),
    data_container.getAdjointMomentPreservingElasticWeights(),
    data_container.getAdjointElasticAngularEnergyGrid(),
    cutoff_angle_cosine );
}

// Create a cutoff elastic distribution
template <typename TwoDInterpPolicy>
void ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution(
    std::shared_ptr<const CutoffElasticElectronScatteringDistribution>&
        cutoff_elastic_distribution,
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const double& cutoff_angle_cosine )
{
  ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution<TwoDInterpPolicy>(
    cutoff_elastic_distribution,
    data_container.getAdjointCutoffElasticAngles(),
    data_container.getAdjointCutoffElasticPDF(),
    data_container.getAdjointElasticAngularEnergyGrid(),
    cutoff_angle_cosine );
}

// Create a moment preserving elastic distribution
template <typename TwoDInterpPolicy>
void ElasticElectronScatteringDistributionNativeFactory::createMomentPreservingElasticDistribution(
    std::shared_ptr<const MomentPreservingElasticElectronScatteringDistribution>&
        moment_preserving_elastic_distribution,
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const double& cutoff_angle_cosine )
{
  testPostcondition( data_container.hasAdjointMomentPreservingData() );

ElasticElectronScatteringDistributionNativeFactory::createMomentPreservingElasticDistribution<TwoDInterpPolicy>(
    moment_preserving_elastic_distribution,
    data_container.getAdjointElasticAngularEnergyGrid(),
    data_container.getAdjointMomentPreservingElasticDiscreteAngles(),
    data_container.getAdjointMomentPreservingElasticWeights(),
    cutoff_angle_cosine );
}

//----------------------------------------------------------------------------//
//      ****DATA CONTAINER INDEPENDENT PUBLIC FUNCTIONS****
//----------------------------------------------------------------------------//

// Create the analog elastic distribution ( combined Cutoff and Screened Rutherford )
/*! \details This function has been overloaded so it can be called without using
 *  the native data container. This functionality is neccessary for generating
 *  native moment preserving data without first creating native data files.
 */
template <bool use_linlinlog_interpolation>
void ElasticElectronScatteringDistributionNativeFactory::createAnalogElasticDistribution(
    std::shared_ptr<const AnalogElasticElectronScatteringDistribution>&
        analog_elastic_distribution,
    const std::map<double,std::vector<double> >& cutoff_elastic_angles,
    const std::map<double,std::vector<double> >& cutoff_elastic_pdf,
    const std::vector<double>& angular_energy_grid,
    const unsigned& atomic_number )
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

  // Create the scattering function
  std::shared_ptr<TwoDDist> scattering_function;

  if ( use_linlinlog_interpolation )
  {
    // Create the scattering function that uses LinLinLog interpolation
    ElasticElectronScatteringDistributionNativeFactory::createScatteringFunction<Utility::LinLinLog>(
        cutoff_elastic_angles,
        cutoff_elastic_pdf,
        angular_energy_grid,
        scattering_function,
        false );
  }
  else
  {
    // Create the scattering function that uses LinLinLin interpolation
    ElasticElectronScatteringDistributionNativeFactory::createScatteringFunction<Utility::LinLinLin>(
        cutoff_elastic_angles,
        cutoff_elastic_pdf,
        angular_energy_grid,
        scattering_function,
        false );
  }

  // Create analog distribution
  analog_elastic_distribution.reset(
    new AnalogElasticElectronScatteringDistribution(
                scattering_function,
                atomic_number,
                use_linlinlog_interpolation ) );
}

// Create the hybrid elastic distribution ( combined Cutoff and Moment Preserving )
template <bool use_linlinlog_interpolation>
void ElasticElectronScatteringDistributionNativeFactory::createHybridElasticDistribution(
    std::shared_ptr<const HybridElasticElectronScatteringDistribution>&
        hybrid_elastic_distribution,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
    const Teuchos::ArrayRCP<const double> energy_grid,
    const Teuchos::ArrayRCP<const double> cutoff_cross_section,
    const std::map<double,std::vector<double> >& cutoff_elastic_angles,
    const std::map<double,std::vector<double> >& cutoff_elastic_pdf,
    const Teuchos::ArrayRCP<const double> moment_preserving_cross_section,
    const std::map<double,std::vector<double> >& moment_preserving_angles,
    const std::map<double,std::vector<double> >& moment_preserving_weights,
    const std::vector<double>& angular_energy_grid,
    const double& cutoff_angle_cosine )
{
  // Create the hybrid scattering functions and cross section ratio
  std::shared_ptr<HybridDistribution> hybrid_function;
  ElasticElectronScatteringDistributionNativeFactory::createHybridScatteringFunction(
    grid_searcher,
    energy_grid,
    cutoff_cross_section,
    cutoff_elastic_angles,
    cutoff_elastic_pdf,
    moment_preserving_cross_section,
    moment_preserving_angles,
    moment_preserving_weights,
    angular_energy_grid,
    cutoff_angle_cosine,
    hybrid_function );

  // Create hybrid distribution
  hybrid_elastic_distribution.reset(
        new HybridElasticElectronScatteringDistribution(
                hybrid_function,
                cutoff_angle_cosine,
                use_linlinlog_interpolation ) );
}

// Create a cutoff elastic distribution
template <typename TwoDInterpPolicy>
void ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution(
    std::shared_ptr<const CutoffElasticElectronScatteringDistribution>&
        cutoff_elastic_distribution,
    const std::map<double,std::vector<double> >& cutoff_elastic_angles,
    const std::map<double,std::vector<double> >& cutoff_elastic_pdf,
    const std::vector<double>& angular_energy_grid,
    const double& cutoff_angle_cosine )
{
  // Create the scattering function
  std::shared_ptr<TwoDDist> scattering_function;
  ElasticElectronScatteringDistributionNativeFactory::createScatteringFunction<TwoDInterpPolicy>(
        cutoff_elastic_angles,
        cutoff_elastic_pdf,
        angular_energy_grid,
        scattering_function );

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
    const double& cutoff_angle_cosine )
{
  // Create the scattering function
  std::shared_ptr<TwoDDist> scattering_function;
  ElasticElectronScatteringDistributionNativeFactory::createScatteringFunction<TwoDInterpPolicy>(
    discrete_angles,
    discrete_weights,
    angular_energy_grid,
    scattering_function,
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
    const double& energy )
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

    // Get the lower and upper angular distributions
    std::shared_ptr<const TabularDist> lower_distribution(
      new const TabularDist( lower_bin->second,
                             pdf.at( lower_bin->first ) ) );
    std::shared_ptr<const TabularDist> upper_distribution(
      new const TabularDist( upper_bin->second,
                             pdf.at( upper_bin->first ) ) );

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
      evaluated_pdf[i] = TwoDInterpPolicy::ZXInterpPolicy::interpolate(
                            lower_bin->first,
                            upper_bin->first,
                            energy,
                            lower_distribution->evaluate( angular_grid[i] ),
                            upper_distribution->evaluate( angular_grid[i] ) );
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
        bool discrete_function )
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
        function_data ) );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELASTIC_ELECTRON_SCATTERING_DISTRIBUTION_NATIVE_FACTORY_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElasticElectronScatteringDistributionNativeFactory_def.hpp
//---------------------------------------------------------------------------//
