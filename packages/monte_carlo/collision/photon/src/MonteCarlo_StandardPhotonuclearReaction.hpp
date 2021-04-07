//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardPhotonuclearReaction.hpp
//! \author Alex Robinson
//! \brief  The standard photonuclear reaction base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_PHOTONUCLEAR_REACTION_HPP
#define MONTE_CARLO_STANDARD_PHOTONUCLEAR_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_PhotonuclearReaction.hpp"
#include "MonteCarlo_StandardReactionBaseImpl.hpp"
#include "MonteCarlo_NuclearScatteringDistribution.hpp"
#include "Utility_Vector.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

//! The standard photonuclear reaction base class
class StandardPhotonuclearReaction : public StandardReactionBaseImpl<PhotonuclearReaction,Utility::LinLin,false>
{
  // QuantityTraits typedef
  typedef Utility::QuantityTraits<double> QT;

  // The base type
  typedef StandardReactionBaseImpl<PhotonuclearReaction,Utility::LinLin,false> BaseType;

public:

  //! Basic Constructor
  StandardPhotonuclearReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const PhotonuclearReactionType reaction_type,
       const double q_value );

  //! Constructor
  StandardPhotonuclearReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
       grid_searcher,
       const PhotonuclearReactionType reaction_type,
       const double q_value );

  //! Destructor
  ~StandardPhotonuclearReaction()
  { /* ... */ }

  //! Return the reaction type
  PhotonuclearReactionType getReactionType() const final override;

  //! Return the reaction Q value
  double getQValue() const final override;

private:

  // The reaction type
  PhotonuclearReactionType d_reaction_type;

  // The q value
  double d_q_value;
};
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_PHOTONUCLEAR_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardPhotonuclearReaction.hpp
//---------------------------------------------------------------------------//
