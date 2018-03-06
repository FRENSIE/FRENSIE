//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectroatomicReactionNativeFactoryHelpers_def.hpp
//! \author Luke Kersting
//! \brief  The adjoint electroatomic reaction native factory helpers definitions
//!
//---------------------------------------------------------------------------//

namespace MonteCarlo{

//----------------------------------------------------------------------------//
//      ****ELASTIC REACTIONS****
//----------------------------------------------------------------------------//

//! Create an coupled elastic scattering adjoint electroatomic reaction
template<typename TwoDInterpPolicy,typename TwoDSamplePolicy>
std::shared_ptr<AdjointElectroatomicReaction>
createCoupledElasticReaction(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_adjoint_electroatom_data,
    const std::string sampling_method,
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
  AdjointElectroatomicReactionNativeFactory::createCoupledElasticReaction<TwoDInterpPolicy,TwoDSamplePolicy>(
      raw_adjoint_electroatom_data,
      energy_grid,
      grid_searcher,
      reaction,
      method,
      evaluation_tol );


  // Make sure the reaction was created correctly
  testPostcondition( reaction.use_count() > 0 );

  return reaction;
}

//! Create a decoupled elastic scattering adjoint electroatomic reaction
template<typename TwoDInterpPolicy,typename TwoDSamplePolicy>
std::shared_ptr<AdjointElectroatomicReaction>
createDecoupledElasticReaction(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_adjoint_electroatom_data,
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
  AdjointElectroatomicReactionNativeFactory::createDecoupledElasticReaction<TwoDInterpPolicy,TwoDSamplePolicy>(
      raw_adjoint_electroatom_data,
      energy_grid,
      grid_searcher,
      reaction,
      evaluation_tol );


  // Make sure the reaction was created correctly
  testPostcondition( reaction.use_count() > 0 );

  return reaction;
}

//! Create a hybrid elastic scattering adjoint electroatomic reaction
template<typename TwoDInterpPolicy,typename TwoDSamplePolicy>
std::shared_ptr<AdjointElectroatomicReaction>
createHybridElasticReaction(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_adjoint_electroatom_data,
    const double cutoff_angle_cosine,
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
  AdjointElectroatomicReactionNativeFactory::createHybridElasticReaction<TwoDInterpPolicy,TwoDSamplePolicy>(
      raw_adjoint_electroatom_data,
      energy_grid,
      grid_searcher,
      reaction,
      cutoff_angle_cosine,
      evaluation_tol );

  // Make sure the reaction was created correctly
  testPostcondition( reaction.use_count() > 0 );

  return reaction;
}

//! Create an cutoff elastic scattering adjoint electroatomic reaction
template<typename TwoDInterpPolicy,typename TwoDSamplePolicy>
std::shared_ptr<AdjointElectroatomicReaction>
createCutoffElasticReaction(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_adjoint_electroatom_data,
    const double cutoff_angle_cosine,
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
  AdjointElectroatomicReactionNativeFactory::createCutoffElasticReaction<TwoDInterpPolicy,TwoDSamplePolicy>(
      raw_adjoint_electroatom_data,
      energy_grid,
      grid_searcher,
      reaction,
      cutoff_angle_cosine,
      evaluation_tol );

  // Make sure the reaction was created correctly
  testPostcondition( reaction.use_count() > 0 );

  return reaction;
}

//! Create the moment preserving elastic scattering adjoint electroatomic reaction
template<typename TwoDInterpPolicy,typename TwoDSamplePolicy>
std::shared_ptr<AdjointElectroatomicReaction>
createMomentPreservingElasticReaction(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_adjoint_electroatom_data,
    const double cutoff_angle_cosine,
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
  AdjointElectroatomicReactionNativeFactory::createMomentPreservingElasticReaction<TwoDInterpPolicy,TwoDSamplePolicy>(
      raw_adjoint_electroatom_data,
      energy_grid,
      grid_searcher,
      reaction,
      cutoff_angle_cosine,
      evaluation_tol );

  // Make sure the reaction was created correctly
  testPostcondition( reaction.use_count() > 0 );

  return reaction;
}

//----------------------------------------------------------------------------//
//      ****ELECTROIONIZATION SUBSHELL REACTIONS****
//----------------------------------------------------------------------------//

//! Create the subshell electroionization adjoint electroatomic reaction
template<typename TwoDInterpPolicy,typename TwoDSamplePolicy>
std::shared_ptr<AdjointElectroatomicReaction>
createSubshellElectroionizationReaction(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_adjoint_electroatom_data,
    const unsigned subshell,
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
  AdjointElectroatomicReactionNativeFactory::createSubshellElectroionizationReaction<TwoDInterpPolicy,TwoDSamplePolicy>(
      raw_adjoint_electroatom_data,
      energy_grid,
      grid_searcher,
      subshell,
      reaction,
      evaluation_tol );

  // Make sure the reaction was created correctly
  testPostcondition( reaction.use_count() > 0 );

  return reaction;
}

//! Create the subshell electroionization adjoint electroatomic reactions
template<typename TwoDInterpPolicy,typename TwoDSamplePolicy>
std::vector<std::shared_ptr<AdjointElectroatomicReaction> >
createSubshellElectroionizationReactions(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_adjoint_electroatom_data,
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
  AdjointElectroatomicReactionNativeFactory::createSubshellElectroionizationReactions<TwoDInterpPolicy,TwoDSamplePolicy>(
      raw_adjoint_electroatom_data,
      energy_grid,
      grid_searcher,
      reactions,
      evaluation_tol );

  return reactions;
}

//----------------------------------------------------------------------------//
//      ****BREMSSTRAHLUNG REACTIONS****
//----------------------------------------------------------------------------//

//! Create the bremsstrahlung adjoint electroatomic reaction
template<typename TwoDInterpPolicy,typename TwoDSamplePolicy>
std::shared_ptr<AdjointElectroatomicReaction>
createBremsstrahlungReaction(
    const Data::AdjointElectronPhotonRelaxationDataContainer& raw_adjoint_electroatom_data,
    const bool dipole_distribution_mode_on,
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
  AdjointElectroatomicReactionNativeFactory::createBremsstrahlungReaction<TwoDInterpPolicy,TwoDSamplePolicy>(
      raw_adjoint_electroatom_data,
      energy_grid,
      grid_searcher,
      reaction,
      evaluation_tol );

  // Make sure the reaction was created correctly
  testPostcondition( reaction.use_count() > 0 );

  return reaction;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectroatomicReactionNativeFactoryHelpers_def.hpp
//---------------------------------------------------------------------------//
