//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotoatomicReactionNativeFactory.hpp
//! \author Alex Robinson
//! \brief  The photoatomic reaction native data factory declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHOTOATOMIC_REACTION_NATIVE_FACTORY_HPP
#define MONTE_CARLO_PHOTOATOMIC_REACTION_NATIVE_FACTORY_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_PhotoatomicReaction.hpp"
#include "MonteCarlo_IncoherentModelType.hpp"
#include "Data_ElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_HashBasedGridSearcher.hpp"
#include "Utility_Vector.hpp"

namespace MonteCarlo{

//! The photoatomic reaction factory class that used native data
class PhotoatomicReactionNativeFactory
{

public:

  //! Create the incoherent photoatomic reaction(s)
  static void createIncoherentReactions(
       const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
       const std::shared_ptr<const std::vector<double> >& energy_grid,
       const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
       grid_searcher,
       std::vector<std::shared_ptr<const PhotoatomicReaction> >&
       incoherent_reactions,
       const IncoherentModelType incoherent_model,
       const double kahn_sampling_cutoff_energy );

  //! Create the coherent scattering photoatomic reaction
  static void createCoherentReaction(
       const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
       const std::shared_ptr<const std::vector<double> >& energy_grid,
       const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
       grid_searcher,
       std::shared_ptr<const PhotoatomicReaction>& coherent_reaction );

  //! Create the pair production photoatomic reaction
  static void createPairProductionReaction(
       const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
       const std::shared_ptr<const std::vector<double> >& energy_grid,
       const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
       grid_searcher,
       std::shared_ptr<const PhotoatomicReaction>& pair_production_reaction,
       const bool use_detailed_pair_production_data );

  //! Create the triplet production photoatomic reaction
  static void createTripletProductionReaction(
       const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
       const std::shared_ptr<const std::vector<double> >& energy_grid,
       const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
       grid_searcher,
       std::shared_ptr<const PhotoatomicReaction>& triplet_production_reaction,
       const bool use_detailed_triplet_production_data );

  //! Create the total photoelectric photoatomic reaction
  static void createTotalPhotoelectricReaction(
       const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
       const std::shared_ptr<const std::vector<double> >& energy_grid,
       const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
       grid_searcher,
       std::shared_ptr<const PhotoatomicReaction>& photoelectric_reaction );

  //! Create the subshell photoelectric photoatomic reactions
  static void createSubshellPhotoelectricReactions(
       const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
       const std::shared_ptr<const std::vector<double> >& energy_grid,
       const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
       grid_searcher,
       std::vector<std::shared_ptr<const PhotoatomicReaction> >&
       subshell_photoelectric_reactions );

  //! Create the heating photoatomic reaction
  static void createHeatingReaction(
       const Data::ElectronPhotonRelaxationDataContainer& raw_photoatom_data,
       const std::shared_ptr<const std::vector<double> >& energy_grid,
       const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
       grid_searcher,
       std::shared_ptr<const PhotoatomicReaction>& heating_reaction );

private:

  // Constructor
  PhotoatomicReactionNativeFactory();

};


} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHOTOATOMIC_REACTION_NATIVE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotoatomicReactionNativeFactory.hpp
//---------------------------------------------------------------------------//
