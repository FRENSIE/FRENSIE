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
#include <list>

// Boost Includes
#include <boost/unordered_map.hpp>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleBank.hpp"

namespace MonteCarlo{

//! The nuclear reaction bank class
class NuclearReactionBank : public ParticleBank
{

public:

  //! Constructor
  NuclearReactionBank( const Teuchos::Array<NuclearReactionType>& reactions );

  //! Push a neutron to the bank
  void push( const Teuchos::RCP<NeutronState>& neutron,
	     const NuclearReactionType reaction );

private:

  // The nuclear reactions of interest
  boost::unordered_map<NuclearReactionType,std::list<Teuchos::RCP<NeutronState> > > d_nuclear_reaction_banks;
};

} // end MonteCarlo namespace

#endif // end MonteCarlo_NUCLEAR_REACTION_BANK_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclearReactionBank.hpp
//---------------------------------------------------------------------------//
