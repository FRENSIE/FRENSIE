//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardNeutronNuclearReaction.hpp
//! \author Alex Robinson
//! \brief  The standard neutron nuclear reaction base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_NEUTRON_NUCLEAR_REACTION_HPP
#define MONTE_CARLO_STANDARD_NEUTRON_NUCLEAR_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_NeutronNuclearReaction.hpp"
#include "MonteCarlo_StandardReactionBaseImpl.hpp"
#include "Utility_QuantityTraits.hpp"

namespace MonteCarlo{

//! The standard neutron nuclear reaction base class
class StandardNeutronNuclearReaction : public StandardReactionBaseImpl<NeutronNuclearReaction,Utility::LinLin,false>
{
  // QuantityTraits typedef
  typedef Utility::QuantityTraits<double> QT;

  // The base type
  typedef StandardReactionBaseImpl<NeutronNuclearReaction,Utility::LinLin,false> BaseType;

public:

  //! Basic Constructor
  StandardNeutronNuclearReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const NuclearReactionType reaction_type,
       const double q_value,
       const double temperature );

  //! Constructor
  StandardNeutronNuclearReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
       grid_searcher,
       const NuclearReactionType reaction_type,
       const double q_value,
       const double temperature );

  //! Destructor
  ~StandardNeutronNuclearReaction()
  { /* ... */ }

  //! Return the reaction type
  NuclearReactionType getReactionType() const final override;

  //! Return the reaction Q value
  double getQValue() const final override;

  //! Return the temperature (in MeV) at which the reaction occurs
  double getTemperature() const final override;

private:

  // The reaction type
  NuclearReactionType d_reaction_type;

  // The q value
  double d_q_value;

  // The temperature
  double d_temperature;
};
  
} // end MonteCarlo

#endif // MONTE_CARLO_STANDARD_NEUTRON_NUCLEAR_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardNeutronNuclearReaction.hpp
//---------------------------------------------------------------------------//
