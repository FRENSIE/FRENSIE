//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PositronatomCore.hpp
//! \author Luke Kersting
//! \brief  The positron-atom core class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_POSITRONATOM_CORE_HPP
#define MONTE_CARLO_POSITRONATOM_CORE_HPP

// Std Lib Includes
#include <memory>

// Boost Includes
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

// FRENSIE Includes
#include "MonteCarlo_PositronatomicReactionType.hpp"
#include "MonteCarlo_PositronatomicReaction.hpp"
#include "MonteCarlo_AtomicRelaxationModel.hpp"
#include "Utility_HashBasedGridSearcher.hpp"
#include "Utility_Vector.hpp"

namespace MonteCarlo{

/*! The positron-atom core class for storing positron-atomic reactions
 * \details This class can be used to store all reactions and the atomic
 * relaxation model associated with a positron-atom. Exposing this object (e.g.
 * get method or export method) is safe since it only allows access to the
 * underlying member data in a way that prohibits modification of that data.
 * This class was created to address the issue that arises when dealing with
 * positron-nuclear data - positron-nuclide's that share the same atomic number
 * need the same positron-atomic data. This class allows each positron-nuclide
 * to share the positron-atomic data without copying that data (even if each
 * positron-nuclide has its own copy of the positron-atom core object).
 */
class PositronatomCore
{

public:

  //! Typedef for the particle state type
  typedef PositronState ParticleStateType;

  //! Typedef for the reaction map
  typedef boost::unordered_map<PositronatomicReactionType,
                   std::shared_ptr<PositronatomicReaction> >
  ReactionMap;

  //! Typedef for the const reaction map
  typedef boost::unordered_map<PositronatomicReactionType,
                   std::shared_ptr<const PositronatomicReaction> >
  ConstReactionMap;

  // Reactions that should be treated as scattering
  static const boost::unordered_set<PositronatomicReactionType>
  scattering_reaction_types;

  // Reactions that should be treated as void
  static const boost::unordered_set<PositronatomicReactionType>
  void_reaction_types;

  //! Default constructor
  PositronatomCore();

  //! Basic constructor
  template<typename InterpPolicy>
  PositronatomCore(
    const std::shared_ptr<std::vector<double> >& energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher>& grid_searcher,
    const ReactionMap& standard_scattering_reactions,
    const ReactionMap& standard_absorption_reactions,
    const std::shared_ptr<AtomicRelaxationModel>& relaxation_model,
    const bool processed_atomic_cross_sections,
    const InterpPolicy policy );

  //! Advanced constructor
  PositronatomCore(
    const std::shared_ptr<const PositronatomicReaction>& total_reaction,
    const std::shared_ptr<const PositronatomicReaction>& total_absorption_reaction,
    const ConstReactionMap& scattering_reactions,
    const ConstReactionMap& absorption_reactions,
    const ConstReactionMap& miscellaneous_reactions,
    const std::shared_ptr<const AtomicRelaxationModel> relaxation_model,
    const std::shared_ptr<const Utility::HashBasedGridSearcher>& grid_searcher );

  //! Copy constructor
  PositronatomCore( const PositronatomCore& instance );

  //! Assignment operator
  PositronatomCore& operator=( const PositronatomCore& instance );

  //! Destructor
  ~PositronatomCore()
  { /* ... */ }

  //! Return the total reaction
  const PositronatomicReaction& getTotalReaction() const;

  //! Return the total absorption reaction
  const PositronatomicReaction& getTotalAbsorptionReaction() const;

  //! Return the scattering reactions
  const ConstReactionMap& getScatteringReactions() const;

  //! Return the absorption reactions
  const ConstReactionMap& getAbsorptionReactions() const;

  //! Return the miscellaneous non scattering reactions
  const ConstReactionMap& getMiscReactions() const;

  //! Return the atomic relaxation model
  const AtomicRelaxationModel& getAtomicRelaxationModel() const;

  //! Return the hash-based grid searcher
  const Utility::HashBasedGridSearcher& getGridSearcher() const;

  //! Test if all of the reactions share a common energy grid
  bool hasSharedEnergyGrid() const;

private:

  // Set the default scattering reaction types
  static boost::unordered_set<PositronatomicReactionType>
  setDefaultScatteringReactionTypes();

  // Create the total absorption reaction
  template<typename InterpPolicy>
  static void createTotalAbsorptionReaction(
        const std::shared_ptr<std::vector<double> >& energy_grid,
        const ConstReactionMap& absorption_reactions,
        std::shared_ptr<PositronatomicReaction>& total_absorption_reaction );

  // Create the processed total absorption reaction
  template<typename InterpPolicy>
  static void createProcessedTotalAbsorptionReaction(
        const std::shared_ptr<std::vector<double> >& energy_grid,
        const ConstReactionMap& absorption_reactions,
        std::shared_ptr<PositronatomicReaction>& total_absorption_reaction );

  // Create the total reaction
  template<typename InterpPolicy>
  static void createTotalReaction(
      const std::shared_ptr<std::vector<double> >& energy_grid,
      const ConstReactionMap& scattering_reactions,
      const std::shared_ptr<const PositronatomicReaction>& total_absorption_reaction,
      std::shared_ptr<PositronatomicReaction>& total_reaction );

  // Calculate the processed total absorption cross section
  template<typename InterpPolicy>
  static void createProcessedTotalReaction(
      const std::shared_ptr<std::vector<double> >& energy_grid,
      const ConstReactionMap& scattering_reactions,
      const std::shared_ptr<const PositronatomicReaction>& total_absorption_reaction,
      std::shared_ptr<PositronatomicReaction>& total_reaction );

  // The total reaction
  std::shared_ptr<const PositronatomicReaction> d_total_reaction;

  // The total absorption reaction
  std::shared_ptr<const PositronatomicReaction> d_total_absorption_reaction;

  // The scattering reactions
  ConstReactionMap d_scattering_reactions;

  // The absorption reactions
  ConstReactionMap d_absorption_reactions;

  // The miscellaneous reactions
  ConstReactionMap d_miscellaneous_reactions;

  // The atomic relaxation model
  std::shared_ptr<const AtomicRelaxationModel> d_relaxation_model;

  // The hash-based grid searcher
  std::shared_ptr<const Utility::HashBasedGridSearcher> d_grid_searcher;
};

// Return the total reaction
inline const PositronatomicReaction& PositronatomCore::getTotalReaction() const
{
  return *d_total_reaction;
}

// Return the total absorption reaction
inline const PositronatomicReaction&
PositronatomCore::getTotalAbsorptionReaction() const
{
  return *d_total_absorption_reaction;
}

// Return the scattering reactions
inline const PositronatomCore::ConstReactionMap&
PositronatomCore::getScatteringReactions() const
{
  return d_scattering_reactions;
}

// Return the absorption reactions
inline const PositronatomCore::ConstReactionMap&
PositronatomCore::getAbsorptionReactions() const
{
  return d_absorption_reactions;
}

// Return the miscellaneous reactions
inline const PositronatomCore::ConstReactionMap&
PositronatomCore::getMiscReactions() const
{
  return d_miscellaneous_reactions;
}

// Return the atomic relaxation model
inline const AtomicRelaxationModel&
PositronatomCore::getAtomicRelaxationModel() const
{
  return *d_relaxation_model;
}

// Return the hash-based grid searcher
inline const Utility::HashBasedGridSearcher& PositronatomCore::getGridSearcher() const
{
  return *d_grid_searcher;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_PositronatomCore_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_POSITRONATOM_CORE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PositronatomCore.hpp
//---------------------------------------------------------------------------//

