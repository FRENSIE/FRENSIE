//---------------------------------------------------------------------------//
//!
//! \file   NuclearReactionBank.hpp
//! \author Alex Robinson
//! \brief  Nuclear reaction bank class declaration
//!
//---------------------------------------------------------------------------//

#ifndef NUCLEAR_REACTION_BANK_HPP
#define NUCLEAR_REACTION_BANK_HPP

// Std Lib Includes
#include <list>

// Boost Includes
#include <boost/unordered_map.hpp>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FACEMC Includes
#include "ParticleBank.hpp"

namespace FACEMC{

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

} // end FACEMC namespace

#endif // end NUCLEAR_REACTION_BANK_HPP

//---------------------------------------------------------------------------//
// end NuclearReactionBank.hpp
//---------------------------------------------------------------------------//
