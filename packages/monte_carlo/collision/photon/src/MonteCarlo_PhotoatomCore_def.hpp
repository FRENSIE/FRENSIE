//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotoatomCore_def.hpp
//! \author Alex Robinson
//! \brief  The photoatom core class template definitions
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHOTOATOM_CORE_DEF_HPP
#define MONTE_CARLO_PHOTOATOM_CORE_DEF_HPP

// FRENSIE Includes
#include "MonteCarlo_AbsorptionPhotoatomicReaction.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Basic constructor
/*! \details The scattering absorption and miscellaneous reactions will be
 * organized using the standard scattering reactions, standard absorption
 * reactions and the default absorption type map. Once organized, the
 * total and absorption reactions will be created.
 */
template<typename InterpPolicy>
PhotoatomCore::PhotoatomCore(
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
    grid_searcher,
    const ConstReactionMap& standard_scattering_reactions,
    const ConstReactionMap& standard_absorption_reactions,
    const std::shared_ptr<const AtomicRelaxationModel>& relaxation_model,
    const bool processed_atomic_cross_sections,
    const InterpPolicy policy )
  : BaseType( standard_scattering_reactions,
              standard_absorption_reactions,
              relaxation_model,
              grid_searcher )
{
  // Make sure the energy grid is valid
  testPrecondition( energy_grid->size() > 1 );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid->begin(),
						      energy_grid->end() ) );

  // Create the total absorption and total reactions
  if( processed_atomic_cross_sections )
  {
    this->createProcessedTotalAbsorptionReaction<InterpPolicy,AbsorptionPhotoatomicReaction>(
                                       energy_grid,
                                       TOTAL_ABSORPTION_PHOTOATOMIC_REACTION );

    this->createProcessedTotalReaction<InterpPolicy,AbsorptionPhotoatomicReaction>(
                                                  energy_grid,
						  TOTAL_PHOTOATOMIC_REACTION );
  }
  else
  {
    this->createTotalAbsorptionReaction<InterpPolicy,AbsorptionPhotoatomicReaction>(
                                       energy_grid,
                                       TOTAL_ABSORPTION_PHOTOATOMIC_REACTION );

    this->createTotalReaction<InterpPolicy,AbsorptionPhotoatomicReaction>(
                                                  energy_grid,
						  TOTAL_PHOTOATOMIC_REACTION );
  }
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHOTOATOM_CORE_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotoatomCore_def.hpp
//---------------------------------------------------------------------------//
