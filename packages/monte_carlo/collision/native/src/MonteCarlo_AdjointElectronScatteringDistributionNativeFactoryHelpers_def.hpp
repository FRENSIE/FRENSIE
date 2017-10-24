//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectronScatteringDistributionNativeFactoryHelpers_def.hpp
//! \author Luke Kersting
//! \brief  The adjoint electron scattering distribution native factory helpers definitions
//!
//---------------------------------------------------------------------------//

namespace MonteCarlo{

//----------------------------------------------------------------------------//
//      ****ELASTIC DISTRIBUTIONS****
//----------------------------------------------------------------------------//

// Create the coupled elastic distribution ( combined Cutoff and Screened Rutherford )
template<typename TwoDInterpPolicy,typename TwoDSamplingPolicy>
std::shared_ptr<const CoupledElasticElectronScatteringDistribution> createCoupledElasticDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const std::string sampling_method,
    const double evaluation_tol )
{
  std::shared_ptr<const MonteCarlo::CoupledElasticElectronScatteringDistribution>
    distribution;

  CoupledElasticSamplingMethod method =
    convertStringToCoupledElasticSamplingMethod( sampling_method );

  // Assign the cutoff and total elastic cross section and electron energy grid
  Teuchos::ArrayRCP<double> cutoff_cross_section, total_cross_section, energy_grid;
  cutoff_cross_section.assign(
    data_container.getAdjointCutoffElasticCrossSection().begin(),
    data_container.getAdjointCutoffElasticCrossSection().end() );
  total_cross_section.assign(
    data_container.getAdjointTotalElasticCrossSection().begin(),
    data_container.getAdjointTotalElasticCrossSection().end() );
  energy_grid.assign(
    data_container.getAdjointElectronEnergyGrid().begin(),
    data_container.getAdjointElectronEnergyGrid().end() );

  ElasticElectronScatteringDistributionNativeFactory::createCoupledElasticDistribution<TwoDInterpPolicy,TwoDSamplingPolicy>(
      distribution,
      energy_grid,
      cutoff_cross_section,
      total_cross_section,
      data_container,
      method,
      evaluation_tol );

  return distribution;
}

//! Create the hybrid elastic distribution ( combined Cutoff and Moment Preserving )
template<typename TwoDInterpPolicy,typename TwoDSamplingPolicy>
std::shared_ptr<const HybridElasticElectronScatteringDistribution> createHybridElasticDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const double evaluation_tol )
{
  // Extract the common energy grid used for this atom
  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.assign( data_container.getAdjointElectronEnergyGrid().begin(),
                      data_container.getAdjointElectronEnergyGrid().end() );

  // Cutoff elastic cross section
  Teuchos::ArrayRCP<double> cutoff_cross_section;
  cutoff_cross_section.assign(
    data_container.getAdjointCutoffElasticCrossSection().begin(),
    data_container.getAdjointCutoffElasticCrossSection().end() );

  // Cutoff elastic cross section threshold energy bin index
  unsigned cutoff_threshold_energy_index =
    data_container.getAdjointCutoffElasticCrossSectionThresholdEnergyIndex();

  // Moment preserving elastic cross section
  Teuchos::ArrayRCP<double> mp_cross_section;
  mp_cross_section.assign(
    data_container.getAdjointMomentPreservingCrossSection().begin(),
    data_container.getAdjointMomentPreservingCrossSection().end() );

  // Moment preserving elastic cross section threshold energy bin index
  unsigned mp_threshold_energy_index =
    data_container.getAdjointMomentPreservingCrossSectionThresholdEnergyIndex();

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

  return distribution;
}

//! Create a cutoff elastic distribution
template<typename TwoDInterpPolicy,typename TwoDSamplingPolicy>
std::shared_ptr<const CutoffElasticElectronScatteringDistribution> createCutoffElasticDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
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

  return distribution;
}

//! Create a moment preserving elastic distribution
template<typename TwoDInterpPolicy,typename TwoDSamplingPolicy>
std::shared_ptr<const MomentPreservingElasticElectronScatteringDistribution> createMomentPreservingElasticDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
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

  return distribution;
}

//----------------------------------------------------------------------------//
//      ****BREMSSTRAHLUNG DISTRIBUTIONS****
//----------------------------------------------------------------------------//

// Create an adjoint bremsstrahlung distribution
template<typename TwoDInterpPolicy,typename TwoDSamplingPolicy>
std::shared_ptr<const BremsstrahlungAdjointElectronScatteringDistribution> createBremsstrahlungDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const double evaluation_tol )
{
  std::shared_ptr<const BremsstrahlungAdjointElectronScatteringDistribution>
    distribution;

  BremsstrahlungAdjointElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution<TwoDInterpPolicy,TwoDSamplingPolicy>(
    data_container,
    data_container.getAdjointElectronEnergyGrid(),
    distribution,
    evaluation_tol );

  return distribution;
}

//----------------------------------------------------------------------------//
//      ****ELECTROIONIZATION SUBSHELL DISTRIBUTIONS****
//----------------------------------------------------------------------------//

//! Create a electroionization subshell distribution
template<typename TwoDInterpPolicy,typename TwoDSamplingPolicy>
std::shared_ptr<const ElectroionizationSubshellAdjointElectronScatteringDistribution> createElectroionizationSubshellDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const unsigned subshell,
    const double binding_energy,
    const double evaluation_tol )
{
  std::shared_ptr<const ElectroionizationSubshellAdjointElectronScatteringDistribution>
    distribution;

  ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory::createElectroionizationSubshellDistribution<TwoDInterpPolicy,TwoDSamplingPolicy>(
      data_container,
      subshell,
      binding_energy,
      distribution,
      evaluation_tol );

  return distribution;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectronScatteringDistributionNativeFactoryHelpers_def.hpp
//---------------------------------------------------------------------------//
