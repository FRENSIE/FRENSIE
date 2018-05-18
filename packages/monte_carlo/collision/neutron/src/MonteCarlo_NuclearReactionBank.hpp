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
#include "MonteCarlo_NuclearReactionType.hpp"
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

  //! Insert a neutron into the bank after an interaction (Most Efficient/Recommended)
  void push( std::shared_ptr<NeutronState>& neutron,
             const int reaction ) final override;
  
  //! Insert a neutron into the bank after an interaction
  void push( const NeutronState& neutron,
	     const int reaction ) final override;

private:

  // The nuclear reactions type bank map
  typedef std::map<int, ParticleBank::BankContainerType>
  NuclearReactionTypeBankMap;
  
  NuclearReactionTypeBankMap d_nuclear_reaction_banks;
};

} // end MonteCarlo namespace

#endif // end MonteCarlo_NUCLEAR_REACTION_BANK_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclearReactionBank.hpp
//---------------------------------------------------------------------------//
