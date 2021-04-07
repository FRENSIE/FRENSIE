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
template<typename TwoDInterpPolicy,typename TwoDSamplePolicy>
std::shared_ptr<const CoupledElasticElectronScatteringDistribution> createCoupledElasticDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const CoupledElasticSamplingMethod method,
    const double evaluation_tol )
{
  std::shared_ptr<const MonteCarlo::CoupledElasticElectronScatteringDistribution>
    distribution;

  // Assign the cutoff and total elastic cross section and electron energy grid
  std::shared_ptr<std::vector<double> >
    cutoff_cross_section( new std::vector<double> ),
    total_cross_section( new std::vector<double> ),
    energy_grid( new std::vector<double> );

  cutoff_cross_section->assign(
    data_container.getAdjointCutoffElasticCrossSection().begin(),
    data_container.getAdjointCutoffElasticCrossSection().end() );
  total_cross_section->assign(
    data_container.getAdjointTotalElasticCrossSection().begin(),
    data_container.getAdjointTotalElasticCrossSection().end() );
  energy_grid->assign(
    data_container.getAdjointElectronEnergyGrid().begin(),
    data_container.getAdjointElectronEnergyGrid().end() );

  ElasticElectronScatteringDistributionNativeFactory::createCoupledElasticDistribution<TwoDInterpPolicy,TwoDSamplePolicy>(
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
template<typename TwoDInterpPolicy,typename TwoDSamplePolicy>
std::shared_ptr<const HybridElasticElectronScatteringDistribution> createHybridElasticDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const double evaluation_tol )
{
  // Extract the common energy grid used for this atom
  std::shared_ptr<std::vector<double> > energy_grid( new std::vector<double> );
  energy_grid->assign( data_container.getAdjointElectronEnergyGrid().begin(),
                       data_container.getAdjointElectronEnergyGrid().end() );

  // Cutoff elastic cross section
  std::shared_ptr<std::vector<double> >
    cutoff_cross_section( new std::vector<double> );
  cutoff_cross_section->assign(
    data_container.getAdjointCutoffElasticCrossSection().begin(),
    data_container.getAdjointCutoffElasticCrossSection().end() );

  // Cutoff elastic cross section threshold energy bin index
  unsigned cutoff_threshold_energy_index =
    data_container.getAdjointCutoffElasticCrossSectionThresholdEnergyIndex();

  // Moment preserving elastic cross section
  std::shared_ptr<std::vector<double> >
    mp_cross_section( new std::vector<double> );

  unsigned mp_threshold_energy_index;
  ElasticElectronScatteringDistributionNativeFactory::calculateMomentPreservingCrossSections<TwoDInterpPolicy,TwoDSamplePolicy>(
                                *mp_cross_section,
                                mp_threshold_energy_index,
                                data_container,
                                energy_grid,
                                evaluation_tol );

  // Create the hybrid elastic scattering distribution
  std::shared_ptr<const HybridElasticElectronScatteringDistribution>
    distribution;

  ElasticElectronScatteringDistributionNativeFactory::createHybridElasticDistribution<TwoDInterpPolicy,TwoDSamplePolicy>(
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
template<typename TwoDInterpPolicy,typename TwoDSamplePolicy>
std::shared_ptr<const CutoffElasticElectronScatteringDistribution> createCutoffElasticDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const double evaluation_tol )
{
  std::shared_ptr<const CutoffElasticElectronScatteringDistribution>
    distribution;

  ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution<TwoDInterpPolicy,TwoDSamplePolicy>(
      distribution,
      data_container,
      cutoff_angle_cosine,
      evaluation_tol );

  return distribution;
}

//! Create a moment preserving elastic distribution
template<typename TwoDInterpPolicy,typename TwoDSamplePolicy>
std::shared_ptr<const MomentPreservingElasticElectronScatteringDistribution> createMomentPreservingElasticDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const double evaluation_tol )
{
  std::shared_ptr<const MomentPreservingElasticElectronScatteringDistribution>
    distribution;

  ElasticElectronScatteringDistributionNativeFactory::createMomentPreservingElasticDistribution<TwoDInterpPolicy,TwoDSamplePolicy>(
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
template<typename TwoDInterpPolicy,typename TwoDSamplePolicy>
std::shared_ptr<const BremsstrahlungAdjointElectronScatteringDistribution> createBremsstrahlungDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const double evaluation_tol )
{
  std::shared_ptr<const BremsstrahlungAdjointElectronScatteringDistribution>
    distribution;

  BremsstrahlungAdjointElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution<TwoDInterpPolicy,TwoDSamplePolicy>(
    data_container,
    data_container.getAdjointElectronBremsstrahlungEnergyGrid(),
    distribution,
    evaluation_tol );

  return distribution;
}

//----------------------------------------------------------------------------//
//      ****ELECTROIONIZATION SUBSHELL DISTRIBUTIONS****
//----------------------------------------------------------------------------//

//! Create a electroionization subshell distribution
template<typename TwoDInterpPolicy,typename TwoDSamplePolicy>
std::shared_ptr<const ElectroionizationSubshellAdjointElectronScatteringDistribution> createElectroionizationSubshellDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const unsigned subshell,
    const double binding_energy,
    const double evaluation_tol )
{
  std::shared_ptr<const ElectroionizationSubshellAdjointElectronScatteringDistribution>
    distribution;

  ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory::createElectroionizationSubshellDistribution<TwoDInterpPolicy,TwoDSamplePolicy>(
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
