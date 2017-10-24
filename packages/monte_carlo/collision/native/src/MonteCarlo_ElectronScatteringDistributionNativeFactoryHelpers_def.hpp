//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectronScatteringDistributionNativeFactoryHelpers_def.hpp
//! \author Luke Kersting
//! \brief  The electron scattering distribution native factory helpers definitions
//!
//---------------------------------------------------------------------------//

namespace MonteCarlo{

//----------------------------------------------------------------------------//
//      ****ELASTIC DISTRIBUTIONS****
//----------------------------------------------------------------------------//

// Create the coupled elastic distribution ( combined Cutoff and Screened Rutherford )
template<typename TwoDInterpPolicy,typename TwoDSamplingPolicy>
std::shared_ptr<const CoupledElasticElectronScatteringDistribution> createCoupledElasticDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const std::string sampling_method,
    const double evaluation_tol )
{
  std::shared_ptr<const MonteCarlo::CoupledElasticElectronScatteringDistribution>
    distribution;

  MonteCarlo::CoupledElasticSamplingMethod method =
    MonteCarlo::convertStringToCoupledElasticSamplingMethod( sampling_method );

  ElasticElectronScatteringDistributionNativeFactory::createCoupledElasticDistribution<TwoDInterpPolicy,TwoDSamplingPolicy>(
      distribution,
      data_container,
      method,
      evaluation_tol );

  // Make sure the distribution was created correctly
  testPostcondition( distribution.use_count() > 0 );

  return distribution;
}

//! Create the hybrid elastic distribution ( combined Cutoff and Moment Preserving )
template<typename TwoDInterpPolicy,typename TwoDSamplingPolicy>
std::shared_ptr<const HybridElasticElectronScatteringDistribution> createHybridElasticDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const double evaluation_tol )
{
  // Extract the common energy grid used for this atom
  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.assign( data_container.getElectronEnergyGrid().begin(),
                      data_container.getElectronEnergyGrid().end() );

  // Cutoff elastic cross section
  Teuchos::ArrayRCP<double> cutoff_cross_section;
  cutoff_cross_section.assign(
    data_container.getCutoffElasticCrossSection().begin(),
    data_container.getCutoffElasticCrossSection().end() );

  // Cutoff elastic cross section threshold energy bin index
  unsigned cutoff_threshold_energy_index =
    data_container.getCutoffElasticCrossSectionThresholdEnergyIndex();

  // Moment preserving elastic cross section
  Teuchos::ArrayRCP<double> mp_cross_section;
  mp_cross_section.assign(
    data_container.getMomentPreservingCrossSection().begin(),
    data_container.getMomentPreservingCrossSection().end() );

  // Moment preserving elastic cross section threshold energy bin index
  unsigned mp_threshold_energy_index =
    data_container.getMomentPreservingCrossSectionThresholdEnergyIndex();

  // Create the hybrid elastic scattering distribution
  std::shared_ptr<const HybridElasticElectronScatteringDistribution>
    distribution;

  ElasticElectronScatteringDistributionNativeFactory::createHybridElasticDistribution<TwoDInterpPolicy,TwoDSamplingPolicy>(
      distribution,
      energy_grid,
      cutoff_cross_section,
      mp_cross_section,
      data_container,
      cutoff_angle_cosine,
      evaluation_tol );

  // Make sure the distribution was created correctly
  testPostcondition( distribution.use_count() > 0 );

  return distribution;
}

//! Create a cutoff elastic distribution
template<typename TwoDInterpPolicy,typename TwoDSamplingPolicy>
std::shared_ptr<const CutoffElasticElectronScatteringDistribution> createCutoffElasticDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const double evaluation_tol )
{
  std::shared_ptr<const CutoffElasticElectronScatteringDistribution>
    distribution;

  ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution<TwoDInterpPolicy,TwoDSamplingPolicy>(
      distribution,
      data_container,
      cutoff_angle_cosine,
      evaluation_tol );

  // Make sure the distribution was created correctly
  testPostcondition( distribution.use_count() > 0 );

  return distribution;
}

//! Create a moment preserving elastic distribution
template<typename TwoDInterpPolicy,typename TwoDSamplingPolicy>
std::shared_ptr<const MomentPreservingElasticElectronScatteringDistribution> createMomentPreservingElasticDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const double evaluation_tol )
{
  std::shared_ptr<const MomentPreservingElasticElectronScatteringDistribution>
    distribution;

  ElasticElectronScatteringDistributionNativeFactory::createMomentPreservingElasticDistribution<TwoDInterpPolicy,TwoDSamplingPolicy>(
      distribution,
      data_container,
      cutoff_angle_cosine,
      evaluation_tol );

  // Make sure the distribution was created correctly
  testPostcondition( distribution.use_count() > 0 );

  return distribution;
}

//----------------------------------------------------------------------------//
//      ****BREMSSTRAHLUNG DISTRIBUTIONS****
//----------------------------------------------------------------------------//

// Create a simple dipole bremsstrahlung distribution
template<typename TwoDInterpPolicy,typename TwoDSamplingPolicy>
std::shared_ptr<const BremsstrahlungElectronScatteringDistribution> createBremsstrahlungDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double evaluation_tol )
{
  std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>
    distribution;

  BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution<TwoDInterpPolicy,TwoDSamplingPolicy>(
      data_container,
      distribution,
      evaluation_tol );

  // Make sure the distribution was created correctly
  testPostcondition( distribution.use_count() > 0 );

  return distribution;
}

//! Create a detailed 2BS bremsstrahlung distribution
template<typename TwoDInterpPolicy,typename TwoDSamplingPolicy>
std::shared_ptr<const BremsstrahlungElectronScatteringDistribution> createBremsstrahlungDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const int atomic_number,
    const double evaluation_tol )
{
  std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>
    distribution;

  BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution<TwoDInterpPolicy,TwoDSamplingPolicy>(
      data_container,
      data_container.getAtomicNumber(),
      distribution,
      evaluation_tol );

  // Make sure the distribution was created correctly
  testPostcondition( distribution.use_count() > 0 );

  return distribution;
}

//----------------------------------------------------------------------------//
//      ****ELECTROIONIZATION SUBSHELL DISTRIBUTIONS****
//----------------------------------------------------------------------------//

//! Create a electroionization subshell distribution
template<typename TwoDInterpPolicy,typename TwoDSamplingPolicy>
std::shared_ptr<const ElectroionizationSubshellElectronScatteringDistribution> createElectroionizationSubshellDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const unsigned subshell,
    const double binding_energy,
    const double evaluation_tol )
{
  std::shared_ptr<const ElectroionizationSubshellElectronScatteringDistribution>
    distribution;

  ElectroionizationSubshellElectronScatteringDistributionNativeFactory::createElectroionizationSubshellDistribution<TwoDInterpPolicy,TwoDSamplingPolicy>(
      data_container,
      subshell,
      binding_energy,
      distribution,
      evaluation_tol );

  // Make sure the distribution was created correctly
  testPostcondition( distribution.use_count() > 0 );

  return distribution;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectronScatteringDistributionNativeFactoryHelpers_def.hpp
//---------------------------------------------------------------------------//
