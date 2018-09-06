//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_VoidAbsorptionPositronatomicReaction.hpp
//! \author Luke Kersting
//! \brief  The void absorption positron-atomic reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_VOID_ABSORPTION_POSITRONATOMIC_REACTION_HPP
#define MONTE_CARLO_VOID_ABSORPTION_POSITRONATOMIC_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_PositronatomicReaction.hpp"
#include "MonteCarlo_VoidAtomicReaction.hpp"

namespace MonteCarlo{

/*! The void absorption positron-atomic reaction class
* \details This class can be used to ignore absorption reactions.
*/

class VoidAbsorptionPositronatomicReaction : public VoidAtomicReaction<PositronatomicReaction>
{

public:

  //! Constructor
  VoidAbsorptionPositronatomicReaction()
  { /* ... */ }

  //! Destructor
  ~VoidAbsorptionPositronatomicReaction()
  { /* ... */ }

  //! Return the reaction type
  PositronatomicReactionType getReactionType() const final override;

  //! Return the differential cross section
  double getDifferentialCrossSection( const double incoming_energy,
                                      const double secondary_variable ) const final override;

  //! Simulate the reaction
  void react( PositronState& positron,
              ParticleBank& bank,
              Data::SubshellType& shell_of_interaction ) const final override;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_VOID_ABSORPTION_POSITRONATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_VoidAbsorptionPositronatomicReaction.hpp
//---------------------------------------------------------------------------//
