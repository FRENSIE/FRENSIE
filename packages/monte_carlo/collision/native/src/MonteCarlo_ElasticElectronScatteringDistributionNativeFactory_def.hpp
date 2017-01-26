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
