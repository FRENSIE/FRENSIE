//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotoatomicReactionNativeFactory.hpp
//! \author Alex Robinson
//! \brief  The photoatomic reaction native data factory declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHOTOATOMIC_REACTION_NATIVE_FACTORY_HPP
#define MONTE_CARLO_PHOTOATOMIC_REACTION_NATIVE_FACTORY_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_PhotoatomicReaction.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"

namespace MonteCarlo{

//! The photoatomic reaction factory class that used native data
class PhotoatomicReactionNativeFactory
{

public:
  
  //! Create the total incoherent photoatomic reaction
  static void createTotalIncoherentReaction(
       const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
       const Teuchos::ArrayRCP<const double>& energy_grid,
       const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
       Teuchos::RCP<PhotoatomicReaction>& incoherent_reaction,
       const bool use_doppler_broadening_data );

  //! Create the subshell incoherent photoatomic reactions
  static void createSubshellIncoherentReactions(
       const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
       const Teuchos::ArrayRCP<const double>& energy_grid,
       const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
       Teuchos::Array<Teuchos::RCP<PhotoatomicReaction> >&
       subshell_incoherent_reactions,
       const bool use_doppler_broadening_data );

  //! Create the coherent scattering photoatomic reaction
  static void createCoherentReaction(
       const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
       const Teuchos::ArrayRCP<const double>& energy_grid,
       const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
       Teuchos::RCP<PhotoatomicReaction>& coherent_reaction );

  //! Create the pair production photoatomic reaction
  static void createPairProductionReaction(
       const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
       const Teuchos::ArrayRCP<const double>& energy_grid,
       const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
       Teuchos::RCP<PhotoatomicReaction>& pair_production_reaction,
       const bool use_detailed_pair_production_data );
  
  //! Create the total photoelectric photoatomic reaction
  static void createTotalPhotoelectricReaction(
       const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
       const Teuchos::ArrayRCP<const double>& energy_grid,
       const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
       Teuchos::RCP<PhotoatomicReaction>& photoelectric_reaction );
					       
  //! Create the subshell photoelectric photoatomic reactions
  static void createSubshellPhotoelectricReactions(
       const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
       const Teuchos::ArrayRCP<const double>& energy_grid,
       const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
       Teuchos::Array<Teuchos::RCP<PhotoatomicReaction> >&
       subshell_photoelectric_reactions );

  //! Create the heating photoatomic reaction
  static void createHeatingReaction(
       const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
       const Teuchos::ArrayRCP<const double>& energy_grid,
       const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
       Teuchos::RCP<PhotoatomicReaction>& heating_reaction );

private:

  // Constructor
  PhotoatomicReactionNativeFactory();

};
				     

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHOTOATOMIC_REACTION_NATIVE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotoatomicReactionNativeFactory.hpp
//---------------------------------------------------------------------------//
