//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_VoidElectroatomicReaction.hpp
//! \author Luke Kersting
//! \brief  The void electroatomic reaction class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_VOID_ELECTROATOMIC_REACTION_HPP
#define MONTE_CARLO_VOID_ELECTROATOMIC_REACTION_HPP

// FRENSIE Includes
#include "MonteCarlo_ElectroatomicReaction.hpp"
#include "MonteCarlo_StandardGenericAtomicReaction.hpp"

namespace MonteCarlo{

/*! The void electroatomic reaction class
* \details This class can be used to create a electroatomic reaction
* class that only return cross section information and not react.
*/

template<typename InterpPolicy, bool processed_cross_section = false>
class VoidElectroatomicReaction : public StandardGenericAtomicReaction<ElectroatomicReaction,InterpPolicy,processed_cross_section>
{

private:

  // Typedef for the base class type
typedef StandardGenericAtomicReaction<ElectroatomicReaction,InterpPolicy,processed_cross_section> 
    BaseType;

public:

  //! Constructor
  VoidElectroatomicReaction(
    const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
    const Teuchos::ArrayRCP<const double>& cross_section,
    const unsigned threshold_energy_index );

  //! Constructor
  VoidElectroatomicReaction(
    const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
    const Teuchos::ArrayRCP<const double>& cross_section,
    const unsigned threshold_energy_index,
    const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher );

  //! Destructor
  ~VoidElectroatomicReaction()
  { /* ... */ }

  //! Return the number of electrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedElectrons( const double energy ) const;

  //! Return the number of photons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedPhotons( const double energy ) const;

  //! Return the reaction type
  ElectroatomicReactionType getReactionType() const;

  //! Return the differential cross section
  double getDifferentialCrossSection( const double incoming_energy,
                                      const double outgoing_energy ) const;

  //! Simulate the reaction
  void react( ElectronState& electron,
              ParticleBank& bank,
              Data::SubshellType& shell_of_interaction ) const;

};

template<typename InterpPolicy, bool processed_cross_section>
VoidElectroatomicReaction<InterpPolicy,processed_cross_section>::VoidElectroatomicReaction(
    const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
    const Teuchos::ArrayRCP<const double>& cross_section,
    const unsigned threshold_energy_index )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index )
  { /* ... */ }

template<typename InterpPolicy, bool processed_cross_section>
VoidElectroatomicReaction<InterpPolicy,processed_cross_section>::VoidElectroatomicReaction(
    const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
    const Teuchos::ArrayRCP<const double>& cross_section,
    const unsigned threshold_energy_index,
    const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index,
              grid_searcher )
  { /* ... */ }

// Return the number of electrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
inline unsigned
VoidElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedElectrons(
    const double energy ) const
{
  return 0u;
}

// Return the number of photons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
inline unsigned
VoidElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedPhotons(
    const double energy ) const
{
  return 0u;
}

// Return reaction type
template<typename InterpPolicy, bool processed_cross_section>
inline ElectroatomicReactionType
VoidElectroatomicReaction<InterpPolicy,processed_cross_section>::getReactionType() const
{
  return TOTAL_ELECTROATOMIC_REACTION;
}

// Return the differential cross section
template<typename InterpPolicy, bool processed_cross_section>
inline double VoidElectroatomicReaction<InterpPolicy,processed_cross_section>::getDifferentialCrossSection(
    const double incoming_energy,
    const double outgoing_energy ) const
{
  return this->getCrossSection( incoming_energy );
}

// Simulate the reaction
template<typename InterpPolicy, bool processed_cross_section>
inline void
VoidElectroatomicReaction<InterpPolicy,processed_cross_section>::react(
       ElectronState& electron,
       ParticleBank& bank,
       Data::SubshellType& shell_of_interaction ) const
{ 
  shell_of_interaction = Data::UNKNOWN_SUBSHELL;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_VOID_ELECTROATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_VoidElectroatomicReaction.hpp
//---------------------------------------------------------------------------//
