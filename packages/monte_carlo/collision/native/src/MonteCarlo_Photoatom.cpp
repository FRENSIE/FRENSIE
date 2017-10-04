//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_Photoatom.cpp
//! \author Alex Robinson
//! \brief  The photoatom base class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_Photoatom.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Return the reactions that are treated as absorption
const boost::unordered_set<PhotoatomicReactionType>&
Photoatom::getAbsorptionReactionTypes()
{
  return PhotoatomCore::absorption_reaction_types;
}

// Return the cross section for a specific photoatomic reaction
double Photoatom::getReactionCrossSection(
			        const double energy,
			        const PhotoatomicReactionType reaction ) const
{
  switch( reaction )
  {
  case TOTAL_PHOTOATOMIC_REACTION:
    return this->getAtomicTotalCrossSection( energy );
  case TOTAL_ABSORPTION_PHOTOATOMIC_REACTION:
    return this->getAtomicAbsorptionCrossSection( energy );
  default:
    ConstReactionMap::const_iterator photoatomic_reaction =
      d_core.getScatteringReactions().find( reaction );

    if( photoatomic_reaction != d_core.getScatteringReactions().end() )
      return photoatomic_reaction->second->getCrossSection( energy );

    photoatomic_reaction = d_core.getAbsorptionReactions().find( reaction );

    if( photoatomic_reaction != d_core.getAbsorptionReactions().end() )
      return photoatomic_reaction->second->getCrossSection( energy );

    photoatomic_reaction = d_core.getMiscReactions().find( reaction );

    if( photoatomic_reaction != d_core.getMiscReactions().end() )
      return photoatomic_reaction->second->getCrossSection( energy );
    else // If the reaction does not exist for an atom, return 0
      return 0.0;
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_Photoatom.cpp
//---------------------------------------------------------------------------//

