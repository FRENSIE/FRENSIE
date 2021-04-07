//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PositronatomCore_def.hpp
//! \author Luke Kersting
//! \brief  The positron-atom core class template definitions
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_POSITRONATOM_CORE_DEF_HPP
#define MONTE_CARLO_POSITRONATOM_CORE_DEF_HPP

// FRENSIE Includes
#include "Utility_DesignByContract.hpp"
#include "MonteCarlo_AbsorptionPositronatomicReaction.hpp"
#include "MonteCarlo_VoidAbsorptionPositronatomicReaction.hpp"

namespace MonteCarlo{

// Basic constructor
/*! \details The scattering absorption and miscellaneous reactions will be
 * organized using the standard scattering reactions, standard absorption
 * reactions and the default scattering type map. Once organized, the
 * total and absorption reactions will be created. If there is not a standard
 * absorption reaction a void absorption reaction will be inserted for the
 * TotalAbsorptionReaction
 */
template<typename InterpPolicy>
PositronatomCore::PositronatomCore(
        const std::shared_ptr<const std::vector<double> >& energy_grid,
        const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
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
    if( this->getAbsorptionReactions().size() > 0 )
    {
      this->createProcessedTotalAbsorptionReaction<InterpPolicy,AbsorptionPositronatomicReaction>(
                                     energy_grid,
                                     TOTAL_ABSORPTION_POSITRONATOMIC_REACTION );
    }
    else
    {
      // Create void absorption reaction
      this->setTotalAbsorptionReaction( std::make_shared<VoidAbsorptionPositronatomicReaction>() );
    }

    this->createProcessedTotalReaction<InterpPolicy,AbsorptionPositronatomicReaction>(
                                               energy_grid,
                                               TOTAL_POSITRONATOMIC_REACTION );
  }
  else
  {
    if( this->getAbsorptionReactions().size() > 0 )
    {
      this->createTotalAbsorptionReaction<InterpPolicy,AbsorptionPositronatomicReaction>(
                                    energy_grid,
                                    TOTAL_ABSORPTION_POSITRONATOMIC_REACTION );
    }
    else
    {
       // Create void absorption reaction
      this->setTotalAbsorptionReaction( std::make_shared<VoidAbsorptionPositronatomicReaction>() );
    }

    this->createTotalReaction<InterpPolicy,AbsorptionPositronatomicReaction>(
                                               energy_grid,
                                               TOTAL_POSITRONATOMIC_REACTION );
  }
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_POSITRONATOM_CORE_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PositronatomCore_def.hpp
//---------------------------------------------------------------------------//

