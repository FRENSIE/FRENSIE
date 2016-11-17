//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectroatomCore.hpp
//! \author Luke Kersting
//! \brief  The adjoint electroatom core class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_ELECTROATOM_CORE_HPP
#define MONTE_CARLO_ADJOINT_ELECTROATOM_CORE_HPP

// Boost Includes
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "MonteCarlo_AdjointElectroatomicReactionType.hpp"
#include "MonteCarlo_AdjointElectroatomicReaction.hpp"
#include "MonteCarlo_AtomicRelaxationModel.hpp"

namespace MonteCarlo{

/*! The adjoint electroatom core class for storing adjoint electroatomic reactions
 * \details This class can be used to store all reactions and the atomic
 * relaxation model associated with a adjoint electroatom. Exposing this object (e.g.
 * get method or export method) is safe since it only allows access to
 * the underlying member data in a way that prohibits modification of that
 * data. This class was created to address the issue that arrises when dealing
 * with electronuclear data - electronuclide's that share the same atomic number
 * need the same adjoint electroatomic data. This class allows each electronuclide to
 * share the adjoint electroatomic data without copying that data (even if each
 * electronuclide has its own copy of the adjoint electroatom core object).
 */
class AdjointElectroatomCore
{

public:

  //! Typedef for the reaction map
  typedef boost::unordered_map<AdjointElectroatomicReactionType,
                   std::shared_ptr<AdjointElectroatomicReaction> >
  ReactionMap;

  //! Typedef for the const reaction map
  typedef boost::unordered_map<AdjointElectroatomicReactionType,
                   std::shared_ptr<const AdjointElectroatomicReaction> >
  ConstReactionMap;

  // Reactions that should be treated as scattering
  static const boost::unordered_set<AdjointElectroatomicReactionType>
  scattering_reaction_types;

  // Reactions that should be treated as void
  static const boost::unordered_set<AdjointElectroatomicReactionType>
  void_reaction_types;

  //! Default constructor
  AdjointElectroatomCore();

  //! Basic constructor
  template<typename InterpPolicy>
  AdjointElectroatomCore(
      const Teuchos::ArrayRCP<double>& energy_grid,
      const ReactionMap& standard_scattering_reactions,
      const ReactionMap& standard_absorption_reactions,
      const Teuchos::RCP<AtomicRelaxationModel>& relaxation_model,
      const bool processed_atomic_cross_sections,
      const InterpPolicy policy );

  //! Advanced constructor
  AdjointElectroatomCore(
      const std::shared_ptr<const AdjointElectroatomicReaction>& total_reaction,
      const std::shared_ptr<const AdjointElectroatomicReaction>& total_absorption_reaction,
      const ConstReactionMap& scattering_reactions,
      const ConstReactionMap& absorption_reactions,
      const ConstReactionMap& miscellaneous_reactions,
      const Teuchos::RCP<const AtomicRelaxationModel> relaxation_model );

  //! Copy constructor
  AdjointElectroatomCore( const AdjointElectroatomCore& instance );

  //! Assignment operator
  AdjointElectroatomCore& operator=( const AdjointElectroatomCore& instance );

  //! Destructor
  ~AdjointElectroatomCore()
  { /* ... */ }

  //! Return the total reaction
  const AdjointElectroatomicReaction& getTotalReaction() const;

  //! Return the total absorption reaction
  const AdjointElectroatomicReaction& getTotalAbsorptionReaction() const;

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
  static boost::unordered_set<AdjointElectroatomicReactionType>
  setDefaultScatteringReactionTypes();

  // Create the total absorption reaction
  template<typename InterpPolicy>
  static void createTotalAbsorptionReaction(
        const Teuchos::ArrayRCP<double>& energy_grid,
        const ConstReactionMap& absorption_reactions,
        std::shared_ptr<AdjointElectroatomicReaction>& total_absorption_reaction );

  // Create the processed total absorption reaction
  template<typename InterpPolicy>
  static void createProcessedTotalAbsorptionReaction(
        const Teuchos::ArrayRCP<double>& energy_grid,
        const ConstReactionMap& absorption_reactions,
        std::shared_ptr<AdjointElectroatomicReaction>& total_absorption_reaction );

  // Create the total reaction
  template<typename InterpPolicy>
  static void createTotalReaction(
      const Teuchos::ArrayRCP<double>& energy_grid,
      const ConstReactionMap& scattering_reactions,
      const std::shared_ptr<const AdjointElectroatomicReaction>& total_absorption_reaction,
      std::shared_ptr<AdjointElectroatomicReaction>& total_reaction );

  // Calculate the processed total absorption cross section
  template<typename InterpPolicy>
  static void createProcessedTotalReaction(
      const Teuchos::ArrayRCP<double>& energy_grid,
      const ConstReactionMap& scattering_reactions,
      const std::shared_ptr<const AdjointElectroatomicReaction>& total_absorption_reaction,
      std::shared_ptr<AdjointElectroatomicReaction>& total_reaction );

  // The total reaction
  std::shared_ptr<const AdjointElectroatomicReaction> d_total_reaction;

  // The total absorption reaction
  std::shared_ptr<const AdjointElectroatomicReaction> d_total_absorption_reaction;

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
inline const AdjointElectroatomicReaction& AdjointElectroatomCore::getTotalReaction() const
{
  return *d_total_reaction;
}

// Return the total absorption reaction
inline const AdjointElectroatomicReaction&
AdjointElectroatomCore::getTotalAbsorptionReaction() const
{
  return *d_total_absorption_reaction;
}

// Return the scattering reactions
inline const AdjointElectroatomCore::ConstReactionMap&
AdjointElectroatomCore::getScatteringReactions() const
{
  return d_scattering_reactions;
}

// Return the absorption reactions
inline const AdjointElectroatomCore::ConstReactionMap&
AdjointElectroatomCore::getAbsorptionReactions() const
{
  return d_absorption_reactions;
}

// Return the miscellaneous reactions
inline const AdjointElectroatomCore::ConstReactionMap&
AdjointElectroatomCore::getMiscReactions() const
{
  return d_miscellaneous_reactions;
}

// Return the atomic relaxation model
inline const AtomicRelaxationModel&
AdjointElectroatomCore::getAtomicRelaxationModel() const
{
  return *d_relaxation_model;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_AdjointElectroatomCore_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_ADJOINT_ELECTROATOM_CORE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectroatomCore.hpp
//---------------------------------------------------------------------------//

