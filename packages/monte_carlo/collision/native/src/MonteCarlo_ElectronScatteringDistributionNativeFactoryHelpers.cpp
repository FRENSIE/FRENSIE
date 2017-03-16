//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectronScatteringDistributionNativeFactoryHelpers.cpp
//! \author Luke Kersting
//! \brief  The electron scattering distribution native factory helpers definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ElectronScatteringDistributionNativeFactoryHelpers.hpp"

namespace MonteCarlo{

//----------------------------------------------------------------------------//
//      ****ELASTIC DISTRIBUTIONS****
//----------------------------------------------------------------------------//

// Create the analog elastic distribution ( combined Cutoff and Screened Rutherford )
std::shared_ptr<const AnalogElasticElectronScatteringDistribution> createAnalogElasticDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const bool use_linlinlog_interpolation )
{
  std::shared_ptr<const MonteCarlo::AnalogElasticElectronScatteringDistribution>
    distribution;

  if ( use_linlinlog_interpolation )
  {
    ElasticElectronScatteringDistributionNativeFactory::createAnalogElasticDistribution<true>(
      distribution, data_container );
  }
  else
  {
    ElasticElectronScatteringDistributionNativeFactory::createAnalogElasticDistribution<false>(
      distribution, data_container );
  }

  return distribution;
}

// Create the analog elastic distribution ( combined Cutoff and Screened Rutherford )
std::shared_ptr<const AnalogElasticElectronScatteringDistribution> createAnalogElasticDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const bool use_linlinlog_interpolation )
{
  std::shared_ptr<const MonteCarlo::AnalogElasticElectronScatteringDistribution>
    distribution;

  if ( use_linlinlog_interpolation )
  {
    ElasticElectronScatteringDistributionNativeFactory::createAnalogElasticDistribution<true>(
      distribution, data_container );
  }
  else
  {
    ElasticElectronScatteringDistributionNativeFactory::createAnalogElasticDistribution<false>(
      distribution, data_container );
  }

  return distribution;
}

//! Create the hybrid elastic distribution ( combined Cutoff and Moment Preserving )
std::shared_ptr<const HybridElasticElectronScatteringDistribution> createHybridElasticDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const bool use_linlinlog_interpolation )
{
  // Extract the common energy grid used for this atom
  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.assign( data_container.getElectronEnergyGrid().begin(),
                      data_container.getElectronEnergyGrid().end() );

  // Construct the hash-based grid searcher for this atom
  Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(
     new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>, false>(
                             energy_grid,
                             100 ) );

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

  if ( use_linlinlog_interpolation )
  {
    ElasticElectronScatteringDistributionNativeFactory::createHybridElasticDistribution<true>(
      distribution,
      grid_searcher,
      energy_grid,
      cutoff_cross_section,
      mp_cross_section,
      data_container,
      cutoff_angle_cosine );
  }
  else
  {
    ElasticElectronScatteringDistributionNativeFactory::createHybridElasticDistribution<false>(
      distribution,
      grid_searcher,
      energy_grid,
      cutoff_cross_section,
      mp_cross_section,
      data_container,
      cutoff_angle_cosine );
  }


  return distribution;
}

//! Create the hybrid elastic distribution ( combined Cutoff and Moment Preserving )
std::shared_ptr<const HybridElasticElectronScatteringDistribution> createHybridElasticDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const bool use_linlinlog_interpolation )
{
  // Extract the common energy grid used for this atom
  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.assign( data_container.getAdjointElectronEnergyGrid().begin(),
                      data_container.getAdjointElectronEnergyGrid().end() );

  // Construct the hash-based grid searcher for this atom
  Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(
     new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>, false>(
                             energy_grid,
                             100 ) );

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

  if ( use_linlinlog_interpolation )
  {
    ElasticElectronScatteringDistributionNativeFactory::createHybridElasticDistribution<true>(
      distribution,
      grid_searcher,
      energy_grid,
      cutoff_cross_section,
      mp_cross_section,
      data_container,
      cutoff_angle_cosine );
  }
  else
  {
    ElasticElectronScatteringDistributionNativeFactory::createHybridElasticDistribution<false>(
      distribution,
      grid_searcher,
      energy_grid,
      cutoff_cross_section,
      mp_cross_section,
      data_container,
      cutoff_angle_cosine );
  }

  return distribution;
}

//! Create a cutoff elastic distribution
std::shared_ptr<const CutoffElasticElectronScatteringDistribution> createCutoffElasticDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const bool use_linlinlog_interpolation )
{
  std::shared_ptr<const CutoffElasticElectronScatteringDistribution>
    distribution;

  if ( use_linlinlog_interpolation )
  {
    ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution<Utility::LinLinLog>(
      distribution, data_container, cutoff_angle_cosine );
  }
  else
  {
    ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution<Utility::LinLinLin>(
      distribution, data_container, cutoff_angle_cosine );
  }

  return distribution;
}

//! Create a cutoff elastic distribution
std::shared_ptr<const CutoffElasticElectronScatteringDistribution> createCutoffElasticDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const bool use_linlinlog_interpolation )
{
  std::shared_ptr<const CutoffElasticElectronScatteringDistribution>
    distribution;

  if ( use_linlinlog_interpolation )
  {
    ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution<Utility::LinLinLog>(
      distribution, data_container, cutoff_angle_cosine );
  }
  else
  {
    ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution<Utility::LinLinLin>(
      distribution, data_container, cutoff_angle_cosine );
  }

  return distribution;
}

//! Create a moment preserving elastic distribution
std::shared_ptr<const MomentPreservingElasticElectronScatteringDistribution> createMomentPreservingElasticDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const bool use_linlinlog_interpolation )
{
  std::shared_ptr<const MomentPreservingElasticElectronScatteringDistribution>
    distribution;

  if ( use_linlinlog_interpolation )
  {
    ElasticElectronScatteringDistributionNativeFactory::createMomentPreservingElasticDistribution<Utility::LinLinLog>(
      distribution,
      data_container,
      cutoff_angle_cosine );
  }
  else
  {
    ElasticElectronScatteringDistributionNativeFactory::createMomentPreservingElasticDistribution<Utility::LinLinLin>(
      distribution,
      data_container,
      cutoff_angle_cosine );
  }

  return distribution;
}

//! Create a moment preserving elastic distribution
std::shared_ptr<const MomentPreservingElasticElectronScatteringDistribution> createMomentPreservingElasticDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const bool use_linlinlog_interpolation )
{
  std::shared_ptr<const MomentPreservingElasticElectronScatteringDistribution>
    distribution;

  if ( use_linlinlog_interpolation )
  {
    ElasticElectronScatteringDistributionNativeFactory::createMomentPreservingElasticDistribution<Utility::LinLinLog>(
      distribution, data_container, cutoff_angle_cosine );
  }
  else
  {
    ElasticElectronScatteringDistributionNativeFactory::createMomentPreservingElasticDistribution<Utility::LinLinLin>(
      distribution, data_container, cutoff_angle_cosine );
  }

  return distribution;
}

//----------------------------------------------------------------------------//
//      ****BREMSSTRAHLUNG DISTRIBUTIONS****
//----------------------------------------------------------------------------//

// Create a simple dipole bremsstrahlung distribution
std::shared_ptr<const BremsstrahlungElectronScatteringDistribution> createBremsstrahlungDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const bool use_linlinlog_interpolation,
    const bool use_correlated_sampling,
    const bool use_unit_based_interpolation,
    const double evalation_tol )
{
  std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>
    distribution;

  if (use_linlinlog_interpolation)
  {
  BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution<Utility::LinLinLog>(
    data_container,
    distribution,
    use_correlated_sampling,
    use_unit_based_interpolation,
    evalation_tol );
  }
  else
  {
  BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution<Utility::LinLinLin>(
    data_container,
    distribution,
    use_correlated_sampling,
    use_unit_based_interpolation,
    evalation_tol );
  }

  return distribution;
}

//! Create a detailed 2BS bremsstrahlung distribution
std::shared_ptr<const BremsstrahlungElectronScatteringDistribution> createBremsstrahlungDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const int atomic_number,
    const bool use_linlinlog_interpolation,
    const bool use_correlated_sampling,
    const bool use_unit_based_interpolation,
    const double evalation_tol )
{
  std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>
    distribution;

  if (use_linlinlog_interpolation)
  {
  BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution<Utility::LinLinLog>(
    data_container,
    data_container.getAtomicNumber(),
    distribution,
    use_correlated_sampling,
    use_unit_based_interpolation,
    evalation_tol );
  }
  else
  {
  BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution<Utility::LinLinLin>(
    data_container,
    data_container.getAtomicNumber(),
    distribution,
    use_correlated_sampling,
    use_unit_based_interpolation,
    evalation_tol );
  }

  return distribution;
}

//----------------------------------------------------------------------------//
//      ****ELECTROIONIZATION SUBSHELL DISTRIBUTIONS****
//----------------------------------------------------------------------------//

//! Create a electroionization subshell distribution
std::shared_ptr<const ElectroionizationSubshellElectronScatteringDistribution> createElectroionizationSubshellDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const unsigned subshell,
    const double binding_energy,
    const bool use_linlinlog_interpolation,
    const bool use_correlated_sampling,
    const bool use_unit_based_interpolation,
    const double evalation_tol )
{
  std::shared_ptr<const ElectroionizationSubshellElectronScatteringDistribution>
    distribution;

  if (use_linlinlog_interpolation)
  {
    ElectroionizationSubshellElectronScatteringDistributionNativeFactory::createElectroionizationSubshellDistribution<Utility::LinLinLog>(
    data_container,
    subshell,
    binding_energy,
    distribution,
    use_correlated_sampling,
    use_unit_based_interpolation,
    evalation_tol );
  }
  else
  {
    ElectroionizationSubshellElectronScatteringDistributionNativeFactory::createElectroionizationSubshellDistribution<Utility::LinLinLin>(
    data_container,
    subshell,
    binding_energy,
    distribution,
    use_correlated_sampling,
    use_unit_based_interpolation,
    evalation_tol );
  }

  return distribution;
}

//----------------------------------------------------------------------------//
//      ****ATOMIC EXCITATION DISTRIBUTION****
//----------------------------------------------------------------------------//

//! Create a atomic excitation distribution
std::shared_ptr<const AtomicExcitationElectronScatteringDistribution> createAtomicExcitationDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container )
{
  std::shared_ptr<const AtomicExcitationElectronScatteringDistribution>
    distribution;

  AtomicExcitationElectronScatteringDistributionNativeFactory::createAtomicExcitationDistribution(
    data_container, distribution );

  return distribution;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectronScatteringDistributionNativeFactoryHelpers.cpp
//---------------------------------------------------------------------------//
