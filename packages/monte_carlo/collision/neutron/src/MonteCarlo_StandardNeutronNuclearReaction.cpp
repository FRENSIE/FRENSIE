//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardNeutronNuclearReaction.cpp
//! \author Alex Robinson
//! \brief  The standard neutron nuclear reaction base class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_StandardNeutronNuclearReaction.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Basic Constructor
StandardNeutronNuclearReaction::StandardNeutronNuclearReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const NuclearReactionType reaction_type,
       const double q_value,
       const double temperature )
  : BaseType( incoming_energy_grid, cross_section, threshold_energy_index ),
    d_reaction_type( reaction_type ),
    d_q_value( q_value ),
    d_temperature( temperature )
{
  // Make sure that the Q value is valid
  testPrecondition( !QT::isnaninf( q_value ) );
  // Make sure that the temperature is valid
  testPrecondition( !QT::isnaninf( temperature ) );
  testPrecondition( temperature >= 0.0 );
}

// Constructor
StandardNeutronNuclearReaction::StandardNeutronNuclearReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
       grid_searcher,
       const NuclearReactionType reaction_type,
       const double q_value,
       const double temperature )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index,
              grid_searcher ),
    d_reaction_type( reaction_type ),
    d_q_value( q_value ),
    d_temperature( temperature )
{
  // Make sure that the Q value is valid
  testPrecondition( !QT::isnaninf( q_value ) );
  // Make sure that the temperature is valid
  testPrecondition( !QT::isnaninf( temperature ) );
  testPrecondition( temperature >= 0.0 );
}

// Return the reaction type
NuclearReactionType StandardNeutronNuclearReaction::getReactionType() const
{
  return d_reaction_type;
}

// Return the reaction Q value
double StandardNeutronNuclearReaction::getQValue() const
{
  return d_q_value;
}

// Return the temperature (in MeV) at which the reaction occurs
double StandardNeutronNuclearReaction::getTemperature() const
{
  return d_temperature;
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardNeutronNuclearReaction.cpp
//---------------------------------------------------------------------------//
