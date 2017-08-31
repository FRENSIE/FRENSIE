//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectronScatteringDistributionNativeFactoryHelpers.cpp
//! \author Luke Kersting
//! \brief  The adjoint electron scattering distribution native factory helpers definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_AdjointElectronScatteringDistributionNativeFactoryHelpers.hpp"

namespace MonteCarlo{

//----------------------------------------------------------------------------//
//      ****ELASTIC DISTRIBUTIONS****
//----------------------------------------------------------------------------//

// Create the coupled elastic distribution ( combined Cutoff and Screened Rutherford )
std::shared_ptr<const CoupledElasticElectronScatteringDistribution> createCoupledElasticDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const std::string two_d_interp_policy_name,
    const bool correlated_sampling_mode_on,
    const double evaluation_tol )
{
  std::shared_ptr<const MonteCarlo::CoupledElasticElectronScatteringDistribution>
    distribution;

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

  if ( two_d_interp_policy_name == Utility::LinLinLog::name() )
  {
    ElasticElectronScatteringDistributionNativeFactory::createCoupledElasticDistribution<Utility::LinLinLog>(
        distribution,
        energy_grid,
        cutoff_cross_section,
        total_cross_section,
        data_container,
        correlated_sampling_mode_on,
        evaluation_tol );
  }
  else if ( two_d_interp_policy_name == Utility::LinLinLin::name() )
  {
    ElasticElectronScatteringDistributionNativeFactory::createCoupledElasticDistribution<Utility::LinLinLin>(
        distribution,
        energy_grid,
        cutoff_cross_section,
        total_cross_section,
        data_container,
        correlated_sampling_mode_on,
        evaluation_tol );
  }
  else if ( two_d_interp_policy_name == Utility::LogLogLog::name() )
  {
    ElasticElectronScatteringDistributionNativeFactory::createCoupledElasticDistribution<Utility::LogLogLog>(
        distribution,
        energy_grid,
        cutoff_cross_section,
        total_cross_section,
        data_container,
        correlated_sampling_mode_on,
        evaluation_tol );
  }
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "Error: the TwoDInterpPolicy " <<
                     two_d_interp_policy_name <<
                     " is invalid or currently not supported!" );
  }

  return distribution;
}

//! Create the hybrid elastic distribution ( combined Cutoff and Moment Preserving )
std::shared_ptr<const HybridElasticElectronScatteringDistribution> createHybridElasticDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const std::string two_d_interp_policy_name,
    const bool correlated_sampling_mode_on,
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

  if ( two_d_interp_policy_name == Utility::LinLinLog::name() )
  {
    ElasticElectronScatteringDistributionNativeFactory::createHybridElasticDistribution<Utility::LinLinLog>(
        distribution,
        energy_grid,
        cutoff_cross_section,
        mp_cross_section,
        data_container,
        cutoff_angle_cosine,
        correlated_sampling_mode_on,
        evaluation_tol );
  }
  else if ( two_d_interp_policy_name == Utility::LinLinLin::name() )
  {
    ElasticElectronScatteringDistributionNativeFactory::createHybridElasticDistribution<Utility::LinLinLin>(
        distribution,
        energy_grid,
        cutoff_cross_section,
        mp_cross_section,
        data_container,
        cutoff_angle_cosine,
        correlated_sampling_mode_on,
        evaluation_tol );
  }
  else if ( two_d_interp_policy_name == Utility::LogLogLog::name() )
  {
    ElasticElectronScatteringDistributionNativeFactory::createHybridElasticDistribution<Utility::LogLogLog>(
        distribution,
        energy_grid,
        cutoff_cross_section,
        mp_cross_section,
        data_container,
        cutoff_angle_cosine,
        correlated_sampling_mode_on,
        evaluation_tol );
  }
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "Error: the TwoDInterpPolicy " <<
                     two_d_interp_policy_name <<
                     " is invalid or currently not supported!" );
  }

  return distribution;
}

//! Create a cutoff elastic distribution
std::shared_ptr<const CutoffElasticElectronScatteringDistribution> createCutoffElasticDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const std::string two_d_interp_policy_name,
    const bool correlated_sampling_mode_on,
    const double evaluation_tol )
{
  std::shared_ptr<const CutoffElasticElectronScatteringDistribution>
    distribution;

  if ( two_d_interp_policy_name == Utility::LinLinLog::name() )
  {
    ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution<Utility::LinLinLog>(
        distribution,
        data_container,
        cutoff_angle_cosine,
        correlated_sampling_mode_on,
        evaluation_tol );
  }
  else if ( two_d_interp_policy_name == Utility::LinLinLin::name() )
  {
    ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution<Utility::LinLinLin>(
        distribution,
        data_container,
        cutoff_angle_cosine,
        correlated_sampling_mode_on,
        evaluation_tol );
  }
  else if ( two_d_interp_policy_name == Utility::LogLogLog::name() )
  {
    ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution<Utility::LogLogLog>(
        distribution,
        data_container,
        cutoff_angle_cosine,
        correlated_sampling_mode_on,
        evaluation_tol );
  }
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "Error: the TwoDInterpPolicy " <<
                     two_d_interp_policy_name <<
                     " is invalid or currently not supported!" );
  }

  return distribution;
}

//! Create a moment preserving elastic distribution
std::shared_ptr<const MomentPreservingElasticElectronScatteringDistribution> createMomentPreservingElasticDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const std::string two_d_interp_policy_name,
    const bool correlated_sampling_mode_on,
    const double evaluation_tol )
{
  std::shared_ptr<const MomentPreservingElasticElectronScatteringDistribution>
    distribution;

  if ( two_d_interp_policy_name == Utility::LinLinLog::name() )
  {
    ElasticElectronScatteringDistributionNativeFactory::createMomentPreservingElasticDistribution<Utility::LinLinLog>(
        distribution,
        data_container,
        cutoff_angle_cosine,
        correlated_sampling_mode_on,
        evaluation_tol );
  }
  else if ( two_d_interp_policy_name == Utility::LinLinLin::name() )
  {
    ElasticElectronScatteringDistributionNativeFactory::createMomentPreservingElasticDistribution<Utility::LinLinLin>(
        distribution,
        data_container,
        cutoff_angle_cosine,
        correlated_sampling_mode_on,
        evaluation_tol );
  }
  else if ( two_d_interp_policy_name == Utility::LogLogLog::name() )
  {
    ElasticElectronScatteringDistributionNativeFactory::createMomentPreservingElasticDistribution<Utility::LogLogLog>(
        distribution,
        data_container,
        cutoff_angle_cosine,
        correlated_sampling_mode_on,
        evaluation_tol );
  }
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "Error: the TwoDInterpPolicy " <<
                     two_d_interp_policy_name <<
                     " is invalid or currently not supported!" );
  }

  return distribution;
}

//----------------------------------------------------------------------------//
//      ****BREMSSTRAHLUNG DISTRIBUTIONS****
//----------------------------------------------------------------------------//

// Create an adjoint bremsstrahlung distribution
std::shared_ptr<const BremsstrahlungAdjointElectronScatteringDistribution> createBremsstrahlungDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const std::string two_d_interp_policy_name,
    const bool correlated_sampling_mode_on,
    const bool unit_based_interpolation_mode_on,
    const double evaluation_tol )
{
  std::shared_ptr<const BremsstrahlungAdjointElectronScatteringDistribution>
    distribution;

  if ( two_d_interp_policy_name == Utility::LinLinLog::name() )
  {
  BremsstrahlungAdjointElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution<Utility::LinLinLog>(
    data_container,
    data_container.getAdjointElectronEnergyGrid(),
    distribution,
    correlated_sampling_mode_on,
    unit_based_interpolation_mode_on,
    evaluation_tol );
  }
  else if ( two_d_interp_policy_name == Utility::LinLinLin::name() )
  {
  BremsstrahlungAdjointElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution<Utility::LinLinLin>(
    data_container,
    data_container.getAdjointElectronEnergyGrid(),
    distribution,
    correlated_sampling_mode_on,
    unit_based_interpolation_mode_on,
    evaluation_tol );
  }
  else if ( two_d_interp_policy_name == Utility::LogLogLog::name() )
  {
  BremsstrahlungAdjointElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution<Utility::LogLogLog>(
    data_container,
    data_container.getAdjointElectronEnergyGrid(),
    distribution,
    correlated_sampling_mode_on,
    unit_based_interpolation_mode_on,
    evaluation_tol );
  }
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "Error: the TwoDInterpPolicy " <<
                     two_d_interp_policy_name <<
                     " is invalid or currently not supported!" );
  }

  return distribution;
}

//----------------------------------------------------------------------------//
//      ****ELECTROIONIZATION SUBSHELL DISTRIBUTIONS****
//----------------------------------------------------------------------------//

//! Create a electroionization subshell distribution
std::shared_ptr<const ElectroionizationSubshellAdjointElectronScatteringDistribution> createElectroionizationSubshellDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container,
    const unsigned subshell,
    const double binding_energy,
    const std::string two_d_interp_policy_name,
    const bool correlated_sampling_mode_on,
    const bool unit_based_interpolation_mode_on,
    const double evaluation_tol )
{
  std::shared_ptr<const ElectroionizationSubshellAdjointElectronScatteringDistribution>
    distribution;

  if ( two_d_interp_policy_name == Utility::LinLinLog::name() )
  {
    ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory::createElectroionizationSubshellDistribution<Utility::LinLinLog>(
        data_container,
        subshell,
        binding_energy,
        distribution,
        correlated_sampling_mode_on,
        unit_based_interpolation_mode_on,
        evaluation_tol );
  }
  else if ( two_d_interp_policy_name == Utility::LinLinLin::name() )
  {
    ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory::createElectroionizationSubshellDistribution<Utility::LinLinLin>(
        data_container,
        subshell,
        binding_energy,
        distribution,
        correlated_sampling_mode_on,
        unit_based_interpolation_mode_on,
        evaluation_tol );
  }
  else if ( two_d_interp_policy_name == Utility::LogLogLog::name() )
  {
    ElectroionizationSubshellAdjointElectronScatteringDistributionNativeFactory::createElectroionizationSubshellDistribution<Utility::LogLogLog>(
        data_container,
        subshell,
        binding_energy,
        distribution,
        correlated_sampling_mode_on,
        unit_based_interpolation_mode_on,
        evaluation_tol );
  }
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "Error: the TwoDInterpPolicy " <<
                     two_d_interp_policy_name <<
                     " is invalid or currently not supported!" );
  }

  return distribution;
}

//----------------------------------------------------------------------------//
//      ****ATOMIC EXCITATION DISTRIBUTION****
//----------------------------------------------------------------------------//

//! Create a atomic excitation distribution
std::shared_ptr<const AtomicExcitationAdjointElectronScatteringDistribution> createAtomicExcitationDistribution(
    const Data::AdjointElectronPhotonRelaxationDataContainer& data_container )
{
  std::shared_ptr<const AtomicExcitationAdjointElectronScatteringDistribution>
    distribution;

  AtomicExcitationAdjointElectronScatteringDistributionNativeFactory::createAtomicExcitationDistribution(
    data_container, distribution );

  return distribution;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectronScatteringDistributionNativeFactoryHelpers.cpp
//---------------------------------------------------------------------------//
