//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotoatomicReaction_def.hpp
//! \author Alex Robinson
//! \brief  The photoatomic reaction base class definition
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_STANDARD_PHOTOATOMIC_REACTION_DEF_HPP
#define FACEMC_STANDARD_PHOTOATOMIC_REACTION_DEF_HPP

// FRENSIE Includes
#include "MonteCarlo_PhotoatomicReaction.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
template<typename InterpPolicy>
PhotoatomicReaction<InterpPolicy>::PhotoatomicReaction(
		  const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
		  const Teuchos::ArrayRCP<const double>& cross_section,
		  const double treshold_energy )
  : d_incoming_energy_grid( incoming_energy_grid ),
    d_cross_section( cross_section )
{
  // Make sure the incoming energy grid is valid
  testPrecondition( incoming_energy_grid.size() > 0 );
  testPrecondition( Utility::Sort::isSortedAscending(
						incoming_energy_grid.begin(),
						incoming_energy_grid.end() ) );
  // Make sure the cross section is valid
  testPrecondition( cross_section.size() == incoming_energy_grid.size() );
  // Make sure the threshold energy is valid
  testPrecondition( threshold_energy < incoming_energy_grid.back() );
}

// Return the cross section at the given energy
template<typename InterpPolicy>
PhotoatomicReaction<InterpPolicy>::getCrossSection( const double energy )
{
  
}
						       

} // end MonteCarlo namespace

#endif // end FACEMC_STANDARD_PHOTOATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotoatomicReaction.cpp
//---------------------------------------------------------------------------//
