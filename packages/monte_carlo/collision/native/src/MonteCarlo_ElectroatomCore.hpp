//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroatomCore.hpp
//! \author Luke Kersting
//! \brief  The electroatom core class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTROATOM_CORE_HPP
#define MONTE_CARLO_ELECTROATOM_CORE_HPP

// Boost Includes
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectroatomicReactionType.hpp"
#include "MonteCarlo_ElectroatomicReaction.hpp"
#include "MonteCarlo_AtomicRelaxationModel.hpp"

namespace MonteCarlo{

/*! The electroatom core class for storing electroatomic reactions
 * \details This class can be used to store all reactions and the atomic 
 * relaxation model associated with a electroatom. Exposing this object (e.g.
 * get method or export method) is safe since it only allows access to 
 * the underlying member data in a way that prohibits modification of that
 * data. This class was created to address the issue that arrises when dealing
 * with electronuclear data - electronuclide's that share the same atomic number
 * need the same electroatomic data. This class allows each electronuclide to 
 * share the electroatomic data without copying that data (even if each
 * electronuclide has its own copy of the electroatom core object).
 */
class ElectroatomCore
{

public:

  //! Typedef for the reaction map
  typedef boost::unordered_map<ElectroatomicReactionType,
			       Teuchos::RCP<ElectroatomicReaction> >
  ReactionMap;

  //! Typedef for the const reaction map
  typedef boost::unordered_map<ElectroatomicReactionType,
			       Teuchos::RCP<const ElectroatomicReaction> >
  ConstReactionMap;

  // Reactions that should be treated as scattering
  static const boost::unordered_set<ElectroatomicReactionType> 
  scattering_reaction_types;

  //! Default constructor
  ElectroatomCore();

  //! Basic constructor
  template<typename InterpPolicy>
  ElectroatomCore(
	  const Teuchos::ArrayRCP<double>& energy_grid,
	  const ReactionMap& standard_scattering_reactions,
	  const ReactionMap& standard_absorption_reactions,
	  const Teuchos::RCP<AtomicRelaxationModel>& relaxation_model,
	  const bool processed_atomic_cross_sections,
	  const InterpPolicy policy );

  //! Advanced constructor
  ElectroatomCore( 
      const Teuchos::RCP<const ElectroatomicReaction>& total_reaction,
      const Teuchos::RCP<const ElectroatomicReaction>& total_absorption_reaction,
      const ConstReactionMap& scattering_reactions,
      const ConstReactionMap& absorption_reactions,
      const ConstReactionMap& miscellaneous_reactions,
      const Teuchos::RCP<const AtomicRelaxationModel> relaxation_model );

  //! Copy constructor
  ElectroatomCore( const ElectroatomCore& instance );

  //! Assignment operator
  ElectroatomCore& operator=( const ElectroatomCore& instance );

  //! Destructor
  ~ElectroatomCore()
  { /* ... */ }
  
  //! Return the total reaction
  const ElectroatomicReaction& getTotalReaction() const;

  //! Return the total absorption reaction
  const ElectroatomicReaction& getTotalAbsorptionReaction() const;

  //! Return the scattering reactions
  const ConstReactionMap& getScatteringReactions() const;

  //! Return the absorption reactions
  const ConstReactionMap& getAbsorptionReactions() const;

  //! Return the miscellaneous non scattering reactions
  const ConstReactionMap& getMiscReactions() const;

  //! Return the atomic relaxation model
  const AtomicRelaxationModel& getAtomicRelaxationModel() const;

private:

  // Set the default scattering reaction types
  static boost::unordered_set<ElectroatomicReactionType>
  setDefaultScatteringReactionTypes();

  // Create the total absorption reaction
  template<typename InterpPolicy>
  static void createTotalAbsorptionReaction(
		const Teuchos::ArrayRCP<double>& energy_grid,
		const ConstReactionMap& absorption_reactions,
		Teuchos::RCP<ElectroatomicReaction>& total_absorption_reaction );

  // Create the processed total absorption reaction
  template<typename InterpPolicy>
  static void createProcessedTotalAbsorptionReaction(
		const Teuchos::ArrayRCP<double>& energy_grid,
		const ConstReactionMap& absorption_reactions,
		Teuchos::RCP<ElectroatomicReaction>& total_absorption_reaction );

  // Create the total reaction
  template<typename InterpPolicy>
  static void createTotalReaction(
      const Teuchos::ArrayRCP<double>& energy_grid,
      const ConstReactionMap& scattering_reactions,
      const Teuchos::RCP<const ElectroatomicReaction>& total_absorption_reaction,
      Teuchos::RCP<ElectroatomicReaction>& total_reaction );
  
  // Calculate the processed total absorption cross section
  template<typename InterpPolicy>
  static void createProcessedTotalReaction(
      const Teuchos::ArrayRCP<double>& energy_grid,
      const ConstReactionMap& scattering_reactions,
      const Teuchos::RCP<const ElectroatomicReaction>& total_absorption_reaction,
      Teuchos::RCP<ElectroatomicReaction>& total_reaction );

  // The total reaction
  Teuchos::RCP<const ElectroatomicReaction> d_total_reaction;

  // The total absorption reaction
  Teuchos::RCP<const ElectroatomicReaction> d_total_absorption_reaction;

  // The scattering reactions
  ConstReactionMap d_scattering_reactions;

  // The absorption reactions
  ConstReactionMap d_absorption_reactions;

  // The miscellaneous reactions
  ConstReactionMap d_miscellaneous_reactions;

  // The atomic relaxation model
  Teuchos::RCP<const AtomicRelaxationModel> d_relaxation_model;
};

// Return the total reaction
inline const ElectroatomicReaction& ElectroatomCore::getTotalReaction() const
{
  return *d_total_reaction;
}

// Return the total absorption reaction
inline const ElectroatomicReaction& 
ElectroatomCore::getTotalAbsorptionReaction() const
{
  return *d_total_absorption_reaction;
}

// Return the scattering reactions
inline const ElectroatomCore::ConstReactionMap& 
ElectroatomCore::getScatteringReactions() const
{
  return d_scattering_reactions;
}

// Return the absorption reactions
inline const ElectroatomCore::ConstReactionMap& 
ElectroatomCore::getAbsorptionReactions() const
{
  return d_absorption_reactions;
}

// Return the miscellaneous reactions
inline const ElectroatomCore::ConstReactionMap& 
ElectroatomCore::getMiscReactions() const
{
  return d_miscellaneous_reactions;
}

// Return the atomic relaxation model
inline const AtomicRelaxationModel& 
ElectroatomCore::getAtomicRelaxationModel() const
{
  return *d_relaxation_model;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_ElectroatomCore_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_ELECTROATOM_CORE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroatomCore.hpp
//---------------------------------------------------------------------------//

