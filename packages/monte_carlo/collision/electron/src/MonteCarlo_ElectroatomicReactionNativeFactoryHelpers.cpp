//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroatomicReactionNativeFactoryHelpers.cpp
//! \author Luke Kersting
//! \brief  The electroatomic reaction native factory helpers definitions
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ElectroatomicReactionNativeFactoryHelpers.hpp"

namespace MonteCarlo{

//----------------------------------------------------------------------------//
//      ****ELASTIC REACTIONS****
//----------------------------------------------------------------------------//

//! Create a screened Rutherford elastic scattering electroatomic reaction
std::shared_ptr<const ElectroatomicReaction>
createScreenedRutherfordElasticReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data )
{
  // Extract the common energy grid
  std::shared_ptr<std::vector<double> > energy_grid( new std::vector<double> );
  energy_grid->assign( raw_electroatom_data.getElectronEnergyGrid().begin(),
                       raw_electroatom_data.getElectronEnergyGrid().end() );

  // Construct the hash-based grid searcher
  std::shared_ptr<const Utility::HashBasedGridSearcher<double>> grid_searcher(
     new Utility::StandardHashBasedGridSearcher<std::vector<double>, false>(
                              energy_grid,
                              energy_grid->size()/10 ) );

  // Create the reaction
  std::shared_ptr<const ElectroatomicReaction> reaction;
  ElectroatomicReactionNativeFactory::createScreenedRutherfordElasticReaction(
        raw_electroatom_data,
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

//! Create an atomic excitation scattering electroatomic reaction
std::shared_ptr<const ElectroatomicReaction>
createAtomicExcitationReaction(
    const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data )
{
  // Extract the common energy grid
  std::shared_ptr<std::vector<double> > energy_grid( new std::vector<double> );
  energy_grid->assign( raw_electroatom_data.getElectronEnergyGrid().begin(),
                       raw_electroatom_data.getElectronEnergyGrid().end() );

  // Construct the hash-based grid searcher
  std::shared_ptr<const Utility::HashBasedGridSearcher<double>> grid_searcher(
     new Utility::StandardHashBasedGridSearcher<std::vector<double>, false>(
                              energy_grid,
                              energy_grid->size()/10 ) );

  // Create the reaction
  std::shared_ptr<const ElectroatomicReaction> reaction;

  ElectroatomicReactionNativeFactory::createAtomicExcitationReaction(
        raw_electroatom_data,
        energy_grid,
        grid_searcher,
        reaction );

  return reaction;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroatomicReactionNativeFactoryHelpers.cpp
//---------------------------------------------------------------------------//
