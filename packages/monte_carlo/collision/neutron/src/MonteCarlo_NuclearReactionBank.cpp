//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NuclearReactionBank.cpp
//! \author Alex Robinson
//! \brief  Nuclear reaction bank class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_NuclearReactionBank.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
NuclearReactionBank::NuclearReactionBank(
                            const std::vector<NuclearReactionType>& reactions )
  : d_nuclear_reaction_banks()
{
  // Make sure there is at least on nuclear reaction of interest
  testPrecondition( reactions.size() > 0 );

  // Initialize the map
  for( size_t i = 0; i < reactions.size(); ++i )
    d_nuclear_reaction_banks[reactions[i]];
}

// Insert a neutron into the bank after an interaction (Most Efficient/Recommended)
void NuclearReactionBank::push( std::shared_ptr<NeutronState>& neutron,
                                const int reaction )
{
  // Make sure that the neutron pointer is valid
  testPrecondition( neutron.get() );
  
  NuclearReactionTypeBankMap::iterator reaction_it =
    d_nuclear_reaction_banks.find( reaction );
  
  if( reaction_it != d_nuclear_reaction_banks.end() )
  {
    if( neutron.use_count() == 1 )
      reaction_it->second.push_back( neutron );
    else
      reaction_it->second.emplace_back( neutron->clone() );

    neutron.reset();
  }
  else
    ParticleBank::push( neutron );
}

// Push a neutron to the bank
void NuclearReactionBank::push( const NeutronState& neutron,
				const int reaction )
{
  NuclearReactionTypeBankMap::iterator reaction_it =
    d_nuclear_reaction_banks.find( reaction );
  
  if( reaction_it != d_nuclear_reaction_banks.end() )
    reaction_it->second.emplace_back( neutron.clone() );
  else
    ParticleBank::push( neutron );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclearReactionBank.cpp
//---------------------------------------------------------------------------//
