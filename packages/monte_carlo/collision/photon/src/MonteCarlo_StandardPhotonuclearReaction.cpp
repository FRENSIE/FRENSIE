//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardPhotonuclearReaction.cpp
//! \author Alex Robinson
//! \brief  The standard photonuclear reaction base class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_StandardPhotonuclearReaction.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
StandardPhotonuclearReaction::StandardPhotonuclearReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const PhotonuclearReactionType reaction_type,
       const double q_value )
  : BaseType( incoming_energy_grid, cross_section, threshold_energy_index ),
    d_reaction_type( reaction_type ),
    d_q_value( q_value )
{
  // Make sure the Q value is valid
  testPrecondition( !QT::isnaninf( q_value ) );
}

// Constructor
StandardPhotonuclearReaction::StandardPhotonuclearReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
       grid_searcher,
       const PhotonuclearReactionType reaction_type,
       const double q_value )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index,
              grid_searcher ),
    d_reaction_type( reaction_type ),
    d_q_value( q_value )
{
  // Make sure the Q value is valid
  testPrecondition( !QT::isnaninf( q_value ) );
}

// Return the reaction type
PhotonuclearReactionType StandardPhotonuclearReaction::getReactionType() const
{
  return d_reaction_type;
}

// Return the reaction Q value
double StandardPhotonuclearReaction::getQValue() const
{
  return d_q_value;
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardPhotonuclearReaction.cpp
//---------------------------------------------------------------------------//

