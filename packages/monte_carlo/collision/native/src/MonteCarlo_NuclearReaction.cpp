//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NuclearReaction.cpp
//! \author Alex Robinson
//! \brief  The nuclear reaction base class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_NuclearReaction.hpp"
#include "MonteCarlo_NuclearReactionHelper.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
NuclearReaction::NuclearReaction( 
		   const NuclearReactionType reaction_type,
		   const double temperature,
		   const double q_value,
		   const unsigned threshold_energy_index,
	     const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
		   const Teuchos::ArrayRCP<const double>& cross_section)
  : d_reaction_type( reaction_type ),
    d_temperature( temperature ),
    d_q_value( q_value ),
    d_threshold_energy_index( threshold_energy_index ),
    d_incoming_energy_grid( incoming_energy_grid ),
    d_cross_section( cross_section )
{
  // Make sure the Q value is valid
  testPrecondition( !ST::isnaninf( q_value ) );
  // Make sure the temperature is valid
  testPrecondition( !ST::isnaninf( temperature ) );
  // Make sure the threshold energy index is valid
  testPrecondition( threshold_energy_index < incoming_energy_grid.size() );
  // Make sure the incoming energy grid is valid
  testPrecondition( Utility::Sort::isSortedAscending( 
					        incoming_energy_grid.begin(),
						incoming_energy_grid.end() ) );
  testPrecondition( incoming_energy_grid.size() > 0 );
  // Make sure the cross section is valid
  testPrecondition( cross_section.size() > 0 );
}

// Return the reaction type
NuclearReactionType NuclearReaction::getReactionType() const
{
  return d_reaction_type;
}

// Return the reaction Q value
double NuclearReaction::getQValue() const
{
  return d_q_value;
}

// Return the cross section value at a given energy
double NuclearReaction::getCrossSection( const double energy ) const
{
  return MonteCarlo::getCrossSection( energy,
                          d_incoming_energy_grid,
                          d_cross_section,
                          d_threshold_energy_index );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclearReaction.cpp
//---------------------------------------------------------------------------//
