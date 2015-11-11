//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NuclearReactionBank.cpp
//! \author Alex Robinson
//! \brief  Nuclear reaction bank class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_NuclearReactionBank.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
NuclearReactionBank::NuclearReactionBank( 
			 const Teuchos::Array<NuclearReactionType>& reactions )
  : d_nuclear_reaction_banks()
{
  // Make sure there is at least on nuclear reaction of interest
  testPrecondition( reactions.size() > 0 );

  // Initialize the map
  for( unsigned i = 0; i < reactions.size(); ++i )
    d_nuclear_reaction_banks[reactions[i]];
}

// Push a neutron to the bank
void NuclearReactionBank::push( const NeutronState& neutron,
				const NuclearReactionType reaction )
{
  if( d_nuclear_reaction_banks.find( reaction ) != 
      d_nuclear_reaction_banks.end() )
    d_nuclear_reaction_banks[reaction].emplace_back( neutron.clone() );
  else
    ParticleBank::push( neutron );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclearReactionBank.cpp
//---------------------------------------------------------------------------//
