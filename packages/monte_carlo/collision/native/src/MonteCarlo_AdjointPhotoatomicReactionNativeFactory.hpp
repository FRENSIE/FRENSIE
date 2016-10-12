//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointPhotoatomicReactionNativeFactory.hpp
//! \author Alex Robinson
//! \brief  The adjoint photoatomic reaction native data factory declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHOTOATOMIC_REACTION_NATIVE_FACTORY_HPP
#define MONTE_CARLO_PHOTOATOMIC_REACTION_NATIVE_FACTORY_HPP

// Std Lib Includes
#include <memory>
#include <vector>

// Trilinos Includes
#include <Teuchos_ArrayRCP.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotoatomicReaction.hpp"
#include "MonteCarlo_LineEnergyAdjointPhotoatomicReaction.hpp"
#include "MonteCarlo_PhotoatomicReaction.hpp"
#include "MonteCarlo_IncoherentAdjointModelType.hpp"
#include "Data_AdjointElectronPhotonRelaxationDataContainer.hpp"
#include "Utility_FullyTabularTwoDDistribution.hpp"
#include "Utility_HashBasedGridSearcher.hpp"

namespace MonteCarlo{

//! The adjoint photoatomic reaction factory class that uses native data
class AdjointPhotoatomicReactionNativeFactory
{

private:

  // Typedef for this type
  typedef AdjointPhotoatomicReactionNativeFactory ThisType;
  
public:

  //! Create the union energy grid with the desired max energy
  static void createUnionEnergyGrid(
                      const Data::AdjointElectronPhotonRelaxationDataContainer&
                      raw_adjoint_photoatom_data,
                      Teuchos::ArrayRCP<double>& energy_grid,
                      const double max_energy );

  //! Create the incoherent adjoint photoatomic reaction(s)
  static void createIncoherentReactions(
       const Data::AdjointElectronPhotonRelaxationDataContainer&
       raw_adjoint_photoatom_data,
       const Teuchos::ArrayRCP<const double>& energy_grid,
       const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
       std::vector<std::shared_ptr<AdjointPhotoatomicReaction> >&
       incoherent_adjoint_reactions,
       const IncoherentAdjointModelType incoherent_adjoint_model,
       const Teuchos::ArrayRCP<const double>& critical_line_energies );

  //! Create the coherent adjoint photoatomic reaction
  static void createCoherentReaction(
      const Data::AdjointElectronPhotonRelaxationDataContainer&
      raw_adjoint_photoatom_data,
      const Teuchos::ArrayRCP<const double>& energy_grid,
      const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
      std::shared_ptr<AdjointPhotoatomicReaction>& coherent_adjoint_reaction );

  //! Create the pair production adjoint photoatomic reaction
  static void createPairProductionReaction(
      const Data::AdjointElectronPhotonRelaxationDataContainer&
      raw_adjoint_photoatom_data,
      const Teuchos::ArrayRCP<const double>& energy_grid,
      const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
      std::shared_ptr<LineEnergyAdjointPhotoatomicReaction>&
      pair_production_adjoint_reaction );

  //! Create the triplet production adjoint photoatomic reaction
  static void createTripletProductionReaction(
      const Data::AdjointElectronPhotonRelaxationDataContainer&
      raw_adjoint_photoatom_data,
      const Teuchos::ArrayRCP<const double>& energy_grid,
      const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
      std::shared_ptr<LineEnergyAdjointPhotoatomicReaction>&
      triplet_production_adjoint_reaction );

  //! Create the forward total reaction (only used to get the cross section)
  static void createTotalForwardReaction(
      const Data::AdjointElectronPhotonRelaxationDataContainer&
      raw_adjoint_photoatom_data,
      const Teuchos::ArrayRCP<const double>& energy_grid,
      const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
      std::shared_ptr<PhotoatomicReaction>& total_forward_reaction );

private:

  // Reduce a 2D cross section to a 1D cross section
  static void reduceTwoDCrossSection(
              const Utility::FullyTabularTwoDDistribution& two_d_cross_section,
              const Teuchos::ArrayRCP<const double>& energy_grid,
              Teuchos::ArrayRCP<double>& cross_section );

  // Slice the cross section based on the max energy
  static void sliceCrossSection( const std::vector<double>& full_energy_grid,
                                 const std::vector<double>& full_cross_section,
                                 const double max_energy,
                                 Teuchos::ArrayRCP<double>& cross_section );
};
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHOTOATOMIC_REACTION_NATIVE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointPhotoatomicReactionNativeFactory.hpp
//---------------------------------------------------------------------------//
