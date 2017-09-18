//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectroatomicReactionNativeFactoryHelpers.cpp
//! \author Luke Kersting
//! \brief  The adjoint electroatomic reaction native factory helpers definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_AdjointElectroatomicReactionNativeFactoryHelpers.hpp"

namespace MonteCarlo{

//----------------------------------------------------------------------------//
//      ****ELASTIC REACTIONS****
//----------------------------------------------------------------------------//

//! Create an coupled elastic scattering adjoint electroatomic reaction
std::shared_ptr<AdjointElectroatomicReaction>
createCoupledElasticReaction(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_adjoint_electroatom_data,
    const std::string two_d_interp_policy_name,
    const std::string sampling_method,
    const bool correlated_sampling_mode_on,
    const double evaluation_tol )
{
  // Extract the common energy grid
  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.assign( raw_adjoint_electroatom_data.getAdjointElectronEnergyGrid().begin(),
                      raw_adjoint_electroatom_data.getAdjointElectronEnergyGrid().end() );

  // Construct the hash-based grid searcher
  Teuchos::RCP<const Utility::HashBasedGridSearcher> grid_searcher(
     new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>, false>(
                              energy_grid,
                              energy_grid.size()/10 ) );

  // Convert sampling method
  CoupledElasticSamplingMethod method =
    convertStringToCoupledElasticSamplingMethod( sampling_method );

  // Create the reaction
  std::shared_ptr<AdjointElectroatomicReaction> reaction;

  if ( two_d_interp_policy_name == Utility::LinLinLog::name() )
  {
    AdjointElectroatomicReactionNativeFactory::createCoupledElasticReaction<Utility::LinLinLog>(
        raw_adjoint_electroatom_data,
        energy_grid,
        grid_searcher,
        reaction,
        method,
        correlated_sampling_mode_on,
        evaluation_tol );
  }
  else if ( two_d_interp_policy_name == Utility::LogLogLog::name() )
  {
    AdjointElectroatomicReactionNativeFactory::createCoupledElasticReaction<Utility::LogLogLog>(
        raw_adjoint_electroatom_data,
        energy_grid,
        grid_searcher,
        reaction,
        method,
        correlated_sampling_mode_on,
        evaluation_tol );
  }
  else if ( two_d_interp_policy_name == Utility::LinLinLin::name() )
  {
    AdjointElectroatomicReactionNativeFactory::createCoupledElasticReaction<Utility::LinLinLin>(
        raw_adjoint_electroatom_data,
        energy_grid,
        grid_searcher,
        reaction,
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

  // Make sure the reaction was created correctly
  testPostcondition( reaction.use_count() > 0 );

  return reaction;
}

//! Create a decoupled elastic scattering adjoint electroatomic reaction
std::shared_ptr<AdjointElectroatomicReaction>
createDecoupledElasticReaction(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_adjoint_electroatom_data,
    const std::string two_d_interp_policy_name,
    const bool correlated_sampling_mode_on,
    const double evaluation_tol )
{
  // Extract the common energy grid
  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.assign( raw_adjoint_electroatom_data.getAdjointElectronEnergyGrid().begin(),
                      raw_adjoint_electroatom_data.getAdjointElectronEnergyGrid().end() );

  // Construct the hash-based grid searcher
  Teuchos::RCP<const Utility::HashBasedGridSearcher> grid_searcher(
     new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>, false>(
                              energy_grid,
                              energy_grid.size()/10 ) );

  // Create the reaction
  std::shared_ptr<AdjointElectroatomicReaction> reaction;

  if ( two_d_interp_policy_name == Utility::LinLinLog::name() )
  {
    AdjointElectroatomicReactionNativeFactory::createDecoupledElasticReaction<Utility::LinLinLog>(
        raw_adjoint_electroatom_data,
        energy_grid,
        grid_searcher,
        reaction,
        correlated_sampling_mode_on,
        evaluation_tol );
  }
  else if ( two_d_interp_policy_name == Utility::LogLogLog::name() )
  {
    AdjointElectroatomicReactionNativeFactory::createDecoupledElasticReaction<Utility::LogLogLog>(
        raw_adjoint_electroatom_data,
        energy_grid,
        grid_searcher,
        reaction,
        correlated_sampling_mode_on,
        evaluation_tol );
  }
  else if ( two_d_interp_policy_name == Utility::LinLinLin::name() )
  {
    AdjointElectroatomicReactionNativeFactory::createDecoupledElasticReaction<Utility::LinLinLin>(
        raw_adjoint_electroatom_data,
        energy_grid,
        grid_searcher,
        reaction,
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

  // Make sure the reaction was created correctly
  testPostcondition( reaction.use_count() > 0 );

  return reaction;
}

//! Create a hybrid elastic scattering adjoint electroatomic reaction
std::shared_ptr<AdjointElectroatomicReaction>
createHybridElasticReaction(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_adjoint_electroatom_data,
    const double cutoff_angle_cosine,
    const std::string two_d_interp_policy_name,
    const bool correlated_sampling_mode_on,
    const double evaluation_tol )
{
  // Extract the common energy grid
  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.assign( raw_adjoint_electroatom_data.getAdjointElectronEnergyGrid().begin(),
                      raw_adjoint_electroatom_data.getAdjointElectronEnergyGrid().end() );

  // Construct the hash-based grid searcher
  Teuchos::RCP<const Utility::HashBasedGridSearcher> grid_searcher(
     new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>, false>(
                              energy_grid,
                              energy_grid.size()/10 ) );

  // Create the reaction
  std::shared_ptr<AdjointElectroatomicReaction> reaction;

  if ( two_d_interp_policy_name == Utility::LinLinLog::name() )
  {
    AdjointElectroatomicReactionNativeFactory::createHybridElasticReaction<Utility::LinLinLog>(
        raw_adjoint_electroatom_data,
        energy_grid,
        grid_searcher,
        reaction,
        cutoff_angle_cosine,
        correlated_sampling_mode_on,
        evaluation_tol );
  }
  else if ( two_d_interp_policy_name == Utility::LogLogLog::name() )
  {
    AdjointElectroatomicReactionNativeFactory::createHybridElasticReaction<Utility::LogLogLog>(
        raw_adjoint_electroatom_data,
        energy_grid,
        grid_searcher,
        reaction,
        cutoff_angle_cosine,
        correlated_sampling_mode_on,
        evaluation_tol );
  }
  else if ( two_d_interp_policy_name == Utility::LinLinLin::name() )
  {
    AdjointElectroatomicReactionNativeFactory::createHybridElasticReaction<Utility::LinLinLin>(
        raw_adjoint_electroatom_data,
        energy_grid,
        grid_searcher,
        reaction,
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

  // Make sure the reaction was created correctly
  testPostcondition( reaction.use_count() > 0 );

  return reaction;
}

//! Create an cutoff elastic scattering adjoint electroatomic reaction
std::shared_ptr<AdjointElectroatomicReaction>
createCutoffElasticReaction(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_adjoint_electroatom_data,
    const double cutoff_angle_cosine,
    const std::string two_d_interp_policy_name,
    const bool correlated_sampling_mode_on,
    const double evaluation_tol )
{
  // Extract the common energy grid
  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.assign( raw_adjoint_electroatom_data.getAdjointElectronEnergyGrid().begin(),
                      raw_adjoint_electroatom_data.getAdjointElectronEnergyGrid().end() );

  // Construct the hash-based grid searcher
  Teuchos::RCP<const Utility::HashBasedGridSearcher> grid_searcher(
     new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>, false>(
                              energy_grid,
                              energy_grid.size()/10 ) );

  // Create the reaction
  std::shared_ptr<AdjointElectroatomicReaction> reaction;

  if ( two_d_interp_policy_name == Utility::LinLinLog::name() )
  {
    AdjointElectroatomicReactionNativeFactory::createCutoffElasticReaction<Utility::LinLinLog>(
        raw_adjoint_electroatom_data,
        energy_grid,
        grid_searcher,
        reaction,
        cutoff_angle_cosine,
        correlated_sampling_mode_on,
        evaluation_tol );
  }
  else if ( two_d_interp_policy_name == Utility::LogLogLog::name() )
  {
    AdjointElectroatomicReactionNativeFactory::createCutoffElasticReaction<Utility::LogLogLog>(
        raw_adjoint_electroatom_data,
        energy_grid,
        grid_searcher,
        reaction,
        cutoff_angle_cosine,
        correlated_sampling_mode_on,
        evaluation_tol );
  }
  else if ( two_d_interp_policy_name == Utility::LinLinLin::name() )
  {
    AdjointElectroatomicReactionNativeFactory::createCutoffElasticReaction<Utility::LinLinLin>(
        raw_adjoint_electroatom_data,
        energy_grid,
        grid_searcher,
        reaction,
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

  // Make sure the reaction was created correctly
  testPostcondition( reaction.use_count() > 0 );

  return reaction;
}

//! Create a screened Rutherford elastic scattering adjoint electroatomic reaction
std::shared_ptr<AdjointElectroatomicReaction>
createScreenedRutherfordElasticReaction(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_adjoint_electroatom_data )
{
  // Extract the common energy grid
  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.assign( raw_adjoint_electroatom_data.getAdjointElectronEnergyGrid().begin(),
                      raw_adjoint_electroatom_data.getAdjointElectronEnergyGrid().end() );

  // Construct the hash-based grid searcher
  Teuchos::RCP<const Utility::HashBasedGridSearcher> grid_searcher(
     new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>, false>(
                              energy_grid,
                              energy_grid.size()/10 ) );

  // Create the reaction
  std::shared_ptr<AdjointElectroatomicReaction> reaction;
  AdjointElectroatomicReactionNativeFactory::createScreenedRutherfordElasticReaction(
        raw_adjoint_electroatom_data,
        energy_grid,
        grid_searcher,
        reaction );

  // Make sure the reaction was created correctly
  testPostcondition( reaction.use_count() > 0 );

  return reaction;
}

//! Create the moment preserving elastic scattering adjoint electroatomic reaction
std::shared_ptr<AdjointElectroatomicReaction>
createMomentPreservingElasticReaction(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_adjoint_electroatom_data,
    const double cutoff_angle_cosine,
    const std::string two_d_interp_policy_name,
    const bool correlated_sampling_mode_on,
    const double evaluation_tol )
{
  // Extract the common energy grid
  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.assign( raw_adjoint_electroatom_data.getAdjointElectronEnergyGrid().begin(),
                      raw_adjoint_electroatom_data.getAdjointElectronEnergyGrid().end() );

  // Construct the hash-based grid searcher
  Teuchos::RCP<const Utility::HashBasedGridSearcher> grid_searcher(
     new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>, false>(
                              energy_grid,
                              energy_grid.size()/10 ) );

  // Create the reaction
  std::shared_ptr<AdjointElectroatomicReaction> reaction;

  if ( two_d_interp_policy_name == Utility::LinLinLog::name() )
  {
    AdjointElectroatomicReactionNativeFactory::createMomentPreservingElasticReaction<Utility::LinLinLog>(
        raw_adjoint_electroatom_data,
        energy_grid,
        grid_searcher,
        reaction,
        cutoff_angle_cosine,
        correlated_sampling_mode_on,
        evaluation_tol );
  }
  else if ( two_d_interp_policy_name == Utility::LogLogLog::name() )
  {
    AdjointElectroatomicReactionNativeFactory::createMomentPreservingElasticReaction<Utility::LogLogLog>(
        raw_adjoint_electroatom_data,
        energy_grid,
        grid_searcher,
        reaction,
        cutoff_angle_cosine,
        correlated_sampling_mode_on,
        evaluation_tol );
  }
  else if ( two_d_interp_policy_name == Utility::LinLinLin::name() )
  {
    AdjointElectroatomicReactionNativeFactory::createMomentPreservingElasticReaction<Utility::LinLinLin>(
        raw_adjoint_electroatom_data,
        energy_grid,
        grid_searcher,
        reaction,
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

  // Make sure the reaction was created correctly
  testPostcondition( reaction.use_count() > 0 );

  return reaction;
}

//----------------------------------------------------------------------------//
//      ****ATOMIC EXCITATION DISTRIBUTION****
//----------------------------------------------------------------------------//

//! Create an atomic excitation scattering adjoint electroatomic reaction
std::shared_ptr<AdjointElectroatomicReaction>
createAtomicExcitationReaction(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_adjoint_electroatom_data )
{
  // Extract the common energy grid
  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.assign( raw_adjoint_electroatom_data.getAdjointElectronEnergyGrid().begin(),
                      raw_adjoint_electroatom_data.getAdjointElectronEnergyGrid().end() );

  // Construct the hash-based grid searcher
  Teuchos::RCP<const Utility::HashBasedGridSearcher> grid_searcher(
     new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>, false>(
                              energy_grid,
                              energy_grid.size()/10 ) );

  // Create the reaction
  std::shared_ptr<AdjointElectroatomicReaction> reaction;

  AdjointElectroatomicReactionNativeFactory::createAtomicExcitationReaction(
        raw_adjoint_electroatom_data,
        energy_grid,
        grid_searcher,
        reaction );

  return reaction;
}

//----------------------------------------------------------------------------//
//      ****ELECTROIONIZATION SUBSHELL REACTIONS****
//----------------------------------------------------------------------------//

//! Create the subshell electroionization adjoint electroatomic reaction
std::shared_ptr<AdjointElectroatomicReaction>
createSubshellElectroionizationReaction(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_adjoint_electroatom_data,
    const unsigned subshell,
    const std::string two_d_interp_policy_name,
    const bool correlated_sampling_mode_on,
    const bool unit_based_interpolation_mode_on,
    const double evaluation_tol )
{
  // Extract the common energy grid
  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.assign( raw_adjoint_electroatom_data.getAdjointElectronEnergyGrid().begin(),
                      raw_adjoint_electroatom_data.getAdjointElectronEnergyGrid().end() );

  // Construct the hash-based grid searcher
  Teuchos::RCP<const Utility::HashBasedGridSearcher> grid_searcher(
     new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>, false>(
                              energy_grid,
                              energy_grid.size()/10 ) );

  // Create the reaction
  std::shared_ptr<AdjointElectroatomicReaction> reaction;

  if ( two_d_interp_policy_name == Utility::LinLinLog::name() )
  {
    AdjointElectroatomicReactionNativeFactory::createSubshellElectroionizationReaction<Utility::LinLinLog>(
        raw_adjoint_electroatom_data,
        energy_grid,
        grid_searcher,
        subshell,
        reaction,
        correlated_sampling_mode_on,
        unit_based_interpolation_mode_on,
        evaluation_tol );
  }
  else if ( two_d_interp_policy_name == Utility::LogLogLog::name() )
  {
    AdjointElectroatomicReactionNativeFactory::createSubshellElectroionizationReaction<Utility::LogLogLog>(
        raw_adjoint_electroatom_data,
        energy_grid,
        grid_searcher,
        subshell,
        reaction,
        correlated_sampling_mode_on,
        unit_based_interpolation_mode_on,
        evaluation_tol );
  }
  else if ( two_d_interp_policy_name == Utility::LinLinLin::name() )
  {
    AdjointElectroatomicReactionNativeFactory::createSubshellElectroionizationReaction<Utility::LinLinLin>(
        raw_adjoint_electroatom_data,
        energy_grid,
        grid_searcher,
        subshell,
        reaction,
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

  // Make sure the reaction was created correctly
  testPostcondition( reaction.use_count() > 0 );

  return reaction;
}

//! Create the subshell electroionization adjoint electroatomic reactions
std::vector<std::shared_ptr<AdjointElectroatomicReaction> >
createSubshellElectroionizationReactions(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_adjoint_electroatom_data,
    const std::string two_d_interp_policy_name,
    const bool correlated_sampling_mode_on,
    const bool unit_based_interpolation_mode_on,
    const double evaluation_tol )
{
  // Extract the common energy grid
  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.assign( raw_adjoint_electroatom_data.getAdjointElectronEnergyGrid().begin(),
                      raw_adjoint_electroatom_data.getAdjointElectronEnergyGrid().end() );

  // Construct the hash-based grid searcher
  Teuchos::RCP<const Utility::HashBasedGridSearcher> grid_searcher(
     new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>, false>(
                              energy_grid,
                              energy_grid.size()/10 ) );

  // Create the reaction
  std::vector<std::shared_ptr<AdjointElectroatomicReaction> > reactions;

  if ( two_d_interp_policy_name == Utility::LinLinLog::name() )
  {
    AdjointElectroatomicReactionNativeFactory::createSubshellElectroionizationReactions<Utility::LinLinLog>(
        raw_adjoint_electroatom_data,
        energy_grid,
        grid_searcher,
        reactions,
        correlated_sampling_mode_on,
        unit_based_interpolation_mode_on,
        evaluation_tol );
  }
  else if ( two_d_interp_policy_name == Utility::LogLogLog::name() )
  {
    AdjointElectroatomicReactionNativeFactory::createSubshellElectroionizationReactions<Utility::LogLogLog>(
        raw_adjoint_electroatom_data,
        energy_grid,
        grid_searcher,
        reactions,
        correlated_sampling_mode_on,
        unit_based_interpolation_mode_on,
        evaluation_tol );
  }
  else if ( two_d_interp_policy_name == Utility::LinLinLin::name() )
  {
    AdjointElectroatomicReactionNativeFactory::createSubshellElectroionizationReactions<Utility::LinLinLin>(
        raw_adjoint_electroatom_data,
        energy_grid,
        grid_searcher,
        reactions,
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

  return reactions;
}

//----------------------------------------------------------------------------//
//      ****BREMSSTRAHLUNG REACTIONS****
//----------------------------------------------------------------------------//

//! Create the bremsstrahlung adjoint electroatomic reaction
std::shared_ptr<AdjointElectroatomicReaction>
createBremsstrahlungReaction(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_adjoint_electroatom_data,
    const bool dipole_distribution_mode_on,
    const std::string two_d_interp_policy_name,
    const bool correlated_sampling_mode_on,
    const bool unit_based_interpolation_mode_on,
    const double evaluation_tol )
{
  // Extract the common energy grid
  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.assign( raw_adjoint_electroatom_data.getAdjointElectronEnergyGrid().begin(),
                      raw_adjoint_electroatom_data.getAdjointElectronEnergyGrid().end() );

  // Construct the hash-based grid searcher
  Teuchos::RCP<const Utility::HashBasedGridSearcher> grid_searcher(
     new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>, false>(
                              energy_grid,
                              energy_grid.size()/10 ) );

  // Create the reaction
  std::shared_ptr<AdjointElectroatomicReaction> reaction;

  if ( two_d_interp_policy_name == Utility::LinLinLog::name() )
  {
    AdjointElectroatomicReactionNativeFactory::createBremsstrahlungReaction<Utility::LinLinLog>(
        raw_adjoint_electroatom_data,
        energy_grid,
        grid_searcher,
        reaction,
        correlated_sampling_mode_on,
        unit_based_interpolation_mode_on,
        evaluation_tol );
  }
  else if ( two_d_interp_policy_name == Utility::LogLogLog::name() )
  {
    AdjointElectroatomicReactionNativeFactory::createBremsstrahlungReaction<Utility::LogLogLog>(
        raw_adjoint_electroatom_data,
        energy_grid,
        grid_searcher,
        reaction,
        correlated_sampling_mode_on,
        unit_based_interpolation_mode_on,
        evaluation_tol );
  }
  else if ( two_d_interp_policy_name == Utility::LinLinLin::name() )
  {
    AdjointElectroatomicReactionNativeFactory::createBremsstrahlungReaction<Utility::LinLinLin>(
        raw_adjoint_electroatom_data,
        energy_grid,
        grid_searcher,
        reaction,
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

  // Make sure the reaction was created correctly
  testPostcondition( reaction.use_count() > 0 );

  return reaction;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectroatomicReactionNativeFactoryHelpers.cpp
//---------------------------------------------------------------------------//
