//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NuclearReactionBank.hpp
//! \author Alex Robinson
//! \brief  Nuclear reaction bank class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_NUCLEAR_REACTION_BANK_HPP
#define MONTE_CARLO_NUCLEAR_REACTION_BANK_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_ParticleBank.hpp"
#include "Utility_List.hpp"
#include "Utility_Vector.hpp"
#include "Utility_Map.hpp"

namespace MonteCarlo{

//! The nuclear reaction bank class
class NuclearReactionBank : public ParticleBank
{

public:

  //! Constructor
  NuclearReactionBank( const std::vector<NuclearReactionType>& reactions );

  //! Push a neutron to the bank
  void push( const NeutronState& neutron,
	     const NuclearReactionType reaction );

private:

  // The nuclear reactions of interest
  std::unordered_map<NuclearReactionType,std::list<boost::scoped_ptr<ParticleState> > > d_nuclear_reaction_banks;
};

} // end MonteCarlo namespace

#endif // end MonteCarlo_NUCLEAR_REACTION_BANK_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclearReactionBank.hpp
//---------------------------------------------------------------------------//
