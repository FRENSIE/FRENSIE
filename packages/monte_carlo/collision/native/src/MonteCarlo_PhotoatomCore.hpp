//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotoatomCore.hpp
//! \author Alex Robinson
//! \brief  The photoatom core class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHOTOATOM_CORE_HPP
#define MONTE_CARLO_PHOTOATOM_CORE_HPP

// Boost Includes
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "MonteCarlo_PhotoatomicReactionType.hpp"
#include "MonteCarlo_PhotoatomicReaction.hpp"
#include "MonteCarlo_AtomicRelaxationModel.hpp"
#include "Utility_HashBasedGridSearcher.hpp"

namespace MonteCarlo{

/*! The photoatom core class for storing photoatomic reactions
 * \details This class can be used to store all reactions and the atomic
 * relaxation model associated with a photoatom. Exposing this object (e.g.
 * get method or export method) is safe since it only allows access to
 * the underlying member data in a way that prohibits modification of that
 * data. This class was created to address the issue that arises when dealing
 * with photonuclear data - photo-nuclides that share the same atomic number
 * need the same photoatomic data. This class allows each photo-nuclide to
 * share the photoatomic data without copying that data (even if each
 * photo-nuclide has its own copy of the photoatom core object).
 */
class PhotoatomCore
{

public:

  //! Typedef for the particle state type
  typedef PhotonState ParticleStateType;

  //! Typedef for the reaction map
  typedef boost::unordered_map<PhotoatomicReactionType,
			       Teuchos::RCP<PhotoatomicReaction> >
  ReactionMap;

  //! Typedef for the const reaction map
  typedef boost::unordered_map<PhotoatomicReactionType,
			       Teuchos::RCP<const PhotoatomicReaction> >
  ConstReactionMap;

  // Reactions that should be treated as absorption
  static const boost::unordered_set<PhotoatomicReactionType>
  absorption_reaction_types;

  //! Default constructor
  PhotoatomCore();

  //! Basic constructor
  template<typename InterpPolicy>
  PhotoatomCore(
       const Teuchos::ArrayRCP<const double>& energy_grid,
       const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
       const ReactionMap& standard_scattering_reactions,
       const ReactionMap& standard_absorption_reactions,
       const Teuchos::RCP<const AtomicRelaxationModel>& relaxation_model,
       const bool processed_atomic_cross_sections,
       const InterpPolicy policy );

  //! Advanced constructor
  PhotoatomCore(
     const Teuchos::RCP<const PhotoatomicReaction>& total_reaction,
     const Teuchos::RCP<const PhotoatomicReaction>& total_absorption_reaction,
     const ConstReactionMap& scattering_reactions,
     const ConstReactionMap& absorption_reactions,
     const ConstReactionMap& miscellaneous_reactions,
     const Teuchos::RCP<const AtomicRelaxationModel>& relaxation_model,
     const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher );

  //! Copy constructor
  PhotoatomCore( const PhotoatomCore& instance );

  //! Assignment operator
  PhotoatomCore& operator=( const PhotoatomCore& instance );

  //! Destructor
  ~PhotoatomCore()
  { /* ... */ }

  //! Return the total reaction
  const PhotoatomicReaction& getTotalReaction() const;

  //! Return the total absorption reaction
  const PhotoatomicReaction& getTotalAbsorptionReaction() const;

  //! Return the scattering reactions
  const ConstReactionMap& getScatteringReactions() const;

  //! Return the absorption reactions
  const ConstReactionMap& getAbsorptionReactions() const;

  //! Return the miscellaneous reactions
  const ConstReactionMap& getMiscReactions() const;

  //! Return the atomic relaxation model
  const AtomicRelaxationModel& getAtomicRelaxationModel() const;

  //! Return the hash-based grid searcher
  const Utility::HashBasedGridSearcher& getGridSearcher() const;

  //! Test if all of the reactions share a common energy grid
  bool hasSharedEnergyGrid() const;

private:

  // Set the default absorption reaction types
  static boost::unordered_set<PhotoatomicReactionType>
  setDefaultAbsorptionReactionTypes();

  // Create the total absorption reaction
  template<typename InterpPolicy>
  static void createTotalAbsorptionReaction(
		const Teuchos::ArrayRCP<const double>& energy_grid,
		const ConstReactionMap& absorption_reactions,
		Teuchos::RCP<PhotoatomicReaction>& total_absorption_reaction );

  // Create the processed total absorption reaction
  template<typename InterpPolicy>
  static void createProcessedTotalAbsorptionReaction(
		const Teuchos::ArrayRCP<const double>& energy_grid,
		const ConstReactionMap& absorption_reactions,
		Teuchos::RCP<PhotoatomicReaction>& total_absorption_reaction );

  // Create the total reaction
  template<typename InterpPolicy>
  static void createTotalReaction(
      const Teuchos::ArrayRCP<const double>& energy_grid,
      const ConstReactionMap& scattering_reactions,
      const Teuchos::RCP<const PhotoatomicReaction>& total_absorption_reaction,
      Teuchos::RCP<PhotoatomicReaction>& total_reaction );

  // Calculate the processed total absorption cross section
  template<typename InterpPolicy>
  static void createProcessedTotalReaction(
      const Teuchos::ArrayRCP<const double>& energy_grid,
      const ConstReactionMap& scattering_reactions,
      const Teuchos::RCP<const PhotoatomicReaction>& total_absorption_reaction,
      Teuchos::RCP<PhotoatomicReaction>& total_reaction );

  // The total reaction
  Teuchos::RCP<const PhotoatomicReaction> d_total_reaction;

  // The total absorption reaction
  Teuchos::RCP<const PhotoatomicReaction> d_total_absorption_reaction;

  // The scattering reactions
  ConstReactionMap d_scattering_reactions;

  // The absorption reactions
  ConstReactionMap d_absorption_reactions;

  // The miscellaneous reactions
  ConstReactionMap d_miscellaneous_reactions;

  // The atomic relaxation model
  Teuchos::RCP<const AtomicRelaxationModel> d_relaxation_model;

  // The hash-based grid searcher
  Teuchos::RCP<const Utility::HashBasedGridSearcher> d_grid_searcher;
};

// Return the total reaction
inline const PhotoatomicReaction& PhotoatomCore::getTotalReaction() const
{
  return *d_total_reaction;
}

// Return the total absorption reaction
inline const PhotoatomicReaction&
PhotoatomCore::getTotalAbsorptionReaction() const
{
  return *d_total_absorption_reaction;
}

// Return the scattering reactions
inline const PhotoatomCore::ConstReactionMap&
PhotoatomCore::getScatteringReactions() const
{
  return d_scattering_reactions;
}

// Return the absorption reactions
inline const PhotoatomCore::ConstReactionMap&
PhotoatomCore::getAbsorptionReactions() const
{
  return d_absorption_reactions;
}

// Return the miscellaneous reactions
inline const PhotoatomCore::ConstReactionMap&
PhotoatomCore::getMiscReactions() const
{
  return d_miscellaneous_reactions;
}

// Return the atomic relaxation model
inline const AtomicRelaxationModel&
PhotoatomCore::getAtomicRelaxationModel() const
{
  return *d_relaxation_model;
}

// Return the hash-based grid searcher
inline const Utility::HashBasedGridSearcher& PhotoatomCore::getGridSearcher() const
{
  return *d_grid_searcher;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_PhotoatomCore_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_PHOTOATOM_CORE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotoatomCore.hpp
//---------------------------------------------------------------------------//
