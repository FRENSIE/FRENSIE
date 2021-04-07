//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_Positronatom.cpp
//! \author Luke Kersting
//! \brief  The positron-atom base class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_Positronatom.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Return the cross section for a specific positron-atomic reaction
double Positronatom::getReactionCrossSection(
                    const double energy,
                    const PositronatomicReactionType reaction ) const
{
  switch( reaction )
  {
  case TOTAL_POSITRONATOMIC_REACTION:
    return this->getTotalCrossSection( energy );
  case TOTAL_ABSORPTION_POSITRONATOMIC_REACTION:
    return this->getAbsorptionCrossSection( energy );
  default:
    ConstReactionMap::const_iterator positronatomic_reaction =
      this->getCore().getScatteringReactions().find( reaction );

    if( positronatomic_reaction != this->getCore().getScatteringReactions().end() )
      return positronatomic_reaction->second->getCrossSection( energy );

    positronatomic_reaction = this->getCore().getAbsorptionReactions().find( reaction );

    if( positronatomic_reaction != this->getCore().getAbsorptionReactions().end() )
      return positronatomic_reaction->second->getCrossSection( energy );

    positronatomic_reaction = this->getCore().getMiscReactions().find( reaction );

    if( positronatomic_reaction != this->getCore().getMiscReactions().end() )
      return positronatomic_reaction->second->getCrossSection( energy );
    else // If the reaction does not exist for an atom, return 0
      return 0.0;
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_Positronatom.cpp
//---------------------------------------------------------------------------//


