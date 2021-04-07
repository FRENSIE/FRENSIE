//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_VoidAbsorptionElectroatomicReaction.hpp
//! \author Luke Kersting
//! \brief  The void absorption electroatomic reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_VOID_ABSORPTION_ELECTROATOMIC_REACTION_HPP
#define MONTE_CARLO_VOID_ABSORPTION_ELECTROATOMIC_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_ElectroatomicReaction.hpp"
#include "MonteCarlo_VoidAtomicReaction.hpp"

namespace MonteCarlo{

/*! The void absorption electroatomic reaction class
* \details This class can be used to ignore absorption reactions.
*/
class VoidAbsorptionElectroatomicReaction : public VoidAtomicReaction<ElectroatomicReaction>
{

public:

  //! Constructor
  VoidAbsorptionElectroatomicReaction()
  { /* ... */ }

  //! Destructor
  ~VoidAbsorptionElectroatomicReaction()
  { /* ... */ }

  //! Return the reaction type
  ElectroatomicReactionType getReactionType() const final override;

  //! Return the differential cross section
  double getDifferentialCrossSection( const double incoming_energy,
                                      const double secondary_variable ) const final override;

  //! Simulate the reaction
  void react( ElectronState& electron,
              ParticleBank& bank,
              Data::SubshellType& shell_of_interaction ) const final override;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_VOID_ABSORPTION_ELECTROATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_VoidAbsorptionElectroatomicReaction.hpp
//---------------------------------------------------------------------------//
