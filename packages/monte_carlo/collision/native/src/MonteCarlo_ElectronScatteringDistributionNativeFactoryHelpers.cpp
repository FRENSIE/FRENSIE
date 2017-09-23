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

// Create the coupled elastic distribution ( combined Cutoff and Screened Rutherford )
std::shared_ptr<const CoupledElasticElectronScatteringDistribution> createCoupledElasticDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const std::string two_d_interp_policy_name,
    const std::string sampling_method,
    const bool correlated_sampling_mode_on,
    const double evaluation_tol )
{
  std::shared_ptr<const MonteCarlo::CoupledElasticElectronScatteringDistribution>
    distribution;

  MonteCarlo::CoupledElasticSamplingMethod method =
    MonteCarlo::convertStringToCoupledElasticSamplingMethod( sampling_method );

  if ( two_d_interp_policy_name == Utility::LinLinLog::name() )
  {
    ElasticElectronScatteringDistributionNativeFactory::createCoupledElasticDistribution<Utility::LinLinLog>(
        distribution,
        data_container,
        method,
        correlated_sampling_mode_on,
        evaluation_tol );
  }
  else if ( two_d_interp_policy_name == Utility::LogLogLog::name() )
  {
    ElasticElectronScatteringDistributionNativeFactory::createCoupledElasticDistribution<Utility::LogLogLog>(
        distribution,
        data_container,
        method,
        correlated_sampling_mode_on,
        evaluation_tol );
  }
  else if ( two_d_interp_policy_name == Utility::LinLinLin::name() )
  {
    ElasticElectronScatteringDistributionNativeFactory::createCoupledElasticDistribution<Utility::LinLinLin>(
        distribution,
        data_container,
        method,
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

  // Make sure the distribution was created correctly
  testPostcondition( distribution.use_count() > 0 );

  return distribution;
}

//! Create the hybrid elastic distribution ( combined Cutoff and Moment Preserving )
std::shared_ptr<const HybridElasticElectronScatteringDistribution> createHybridElasticDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine,
    const std::string two_d_interp_policy_name,
    const bool correlated_sampling_mode_on,
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
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "Error: the TwoDInterpPolicy " <<
                     two_d_interp_policy_name <<
                     " is invalid or currently not supported!" );
  }

  // Make sure the distribution was created correctly
  testPostcondition( distribution.use_count() > 0 );

  return distribution;
}

//! Create a cutoff elastic distribution
std::shared_ptr<const CutoffElasticElectronScatteringDistribution> createCutoffElasticDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
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
  else if ( two_d_interp_policy_name == Utility::LogLogLog::name() )
  {
    ElasticElectronScatteringDistributionNativeFactory::createCutoffElasticDistribution<Utility::LogLogLog>(
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
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "Error: the TwoDInterpPolicy " <<
                     two_d_interp_policy_name <<
                     " is invalid or currently not supported!" );
  }

  // Make sure the distribution was created correctly
  testPostcondition( distribution.use_count() > 0 );

  return distribution;
}

// Create a screened rutherford elastic distribution
std::shared_ptr<const MonteCarlo::ScreenedRutherfordElasticElectronScatteringDistribution> createScreenedRutherfordElasticDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container )
{
  std::shared_ptr<const ScreenedRutherfordElasticElectronScatteringDistribution>
    distribution;

  ElasticElectronScatteringDistributionNativeFactory::createScreenedRutherfordElasticDistribution(
        distribution,
        data_container.getAtomicNumber() );


  // Make sure the distribution was created correctly
  testPostcondition( distribution.use_count() > 0 );

  return distribution;
}

//! Create a moment preserving elastic distribution
std::shared_ptr<const MomentPreservingElasticElectronScatteringDistribution> createMomentPreservingElasticDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
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
  else if ( two_d_interp_policy_name == Utility::LogLogLog::name() )
  {
    ElasticElectronScatteringDistributionNativeFactory::createMomentPreservingElasticDistribution<Utility::LogLogLog>(
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
  else
  {
    THROW_EXCEPTION( std::runtime_error,
                     "Error: the TwoDInterpPolicy " <<
                     two_d_interp_policy_name <<
                     " is invalid or currently not supported!" );
  }

  // Make sure the distribution was created correctly
  testPostcondition( distribution.use_count() > 0 );

  return distribution;
}

//----------------------------------------------------------------------------//
//      ****BREMSSTRAHLUNG DISTRIBUTIONS****
//----------------------------------------------------------------------------//

// Create a simple dipole bremsstrahlung distribution
std::shared_ptr<const BremsstrahlungElectronScatteringDistribution> createBremsstrahlungDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const std::string two_d_interp_policy_name,
    const bool correlated_sampling_mode_on,
    const bool unit_based_interpolation_mode_on,
    const double evaluation_tol )
{
  std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>
    distribution;

  if ( two_d_interp_policy_name == Utility::LinLinLog::name() )
  {
    BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution<Utility::LinLinLog>(
        data_container,
        distribution,
        correlated_sampling_mode_on,
        unit_based_interpolation_mode_on,
        evaluation_tol );
  }
  else if ( two_d_interp_policy_name == Utility::LogLogLog::name() )
  {
    BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution<Utility::LogLogLog>(
        data_container,
        distribution,
        correlated_sampling_mode_on,
        unit_based_interpolation_mode_on,
        evaluation_tol );
  }
  else if ( two_d_interp_policy_name == Utility::LinLinLin::name() )
  {
    BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution<Utility::LinLinLin>(
        data_container,
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

  // Make sure the distribution was created correctly
  testPostcondition( distribution.use_count() > 0 );

  return distribution;
}

//! Create a detailed 2BS bremsstrahlung distribution
std::shared_ptr<const BremsstrahlungElectronScatteringDistribution> createBremsstrahlungDistribution(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const int atomic_number,
    const std::string two_d_interp_policy_name,
    const bool correlated_sampling_mode_on,
    const bool unit_based_interpolation_mode_on,
    const double evaluation_tol )
{
  std::shared_ptr<const BremsstrahlungElectronScatteringDistribution>
    distribution;

  if ( two_d_interp_policy_name == Utility::LinLinLog::name() )
  {
    BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution<Utility::LinLinLog>(
        data_container,
        data_container.getAtomicNumber(),
        distribution,
        correlated_sampling_mode_on,
        unit_based_interpolation_mode_on,
        evaluation_tol );
  }
  else if ( two_d_interp_policy_name == Utility::LogLogLog::name() )
  {
    BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution<Utility::LogLogLog>(
        data_container,
        data_container.getAtomicNumber(),
        distribution,
        correlated_sampling_mode_on,
        unit_based_interpolation_mode_on,
        evaluation_tol );
  }
  else if ( two_d_interp_policy_name == Utility::LinLinLin::name() )
  {
    BremsstrahlungElectronScatteringDistributionNativeFactory::createBremsstrahlungDistribution<Utility::LinLinLin>(
        data_container,
        data_container.getAtomicNumber(),
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

  // Make sure the distribution was created correctly
  testPostcondition( distribution.use_count() > 0 );

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
    const std::string two_d_interp_policy_name,
    const bool correlated_sampling_mode_on,
    const bool unit_based_interpolation_mode_on,
    const double evaluation_tol )
{
  std::shared_ptr<const ElectroionizationSubshellElectronScatteringDistribution>
    distribution;

  if ( two_d_interp_policy_name == Utility::LinLinLog::name() )
  {
    ElectroionizationSubshellElectronScatteringDistributionNativeFactory::createElectroionizationSubshellDistribution<Utility::LinLinLog>(
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
    ElectroionizationSubshellElectronScatteringDistributionNativeFactory::createElectroionizationSubshellDistribution<Utility::LogLogLog>(
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
    ElectroionizationSubshellElectronScatteringDistributionNativeFactory::createElectroionizationSubshellDistribution<Utility::LinLinLin>(
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

  // Make sure the distribution was created correctly
  testPostcondition( distribution.use_count() > 0 );

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
