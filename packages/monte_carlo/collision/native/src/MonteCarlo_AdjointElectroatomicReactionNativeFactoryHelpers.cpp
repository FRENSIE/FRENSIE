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

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectroatomicReactionNativeFactoryHelpers.cpp
//---------------------------------------------------------------------------//