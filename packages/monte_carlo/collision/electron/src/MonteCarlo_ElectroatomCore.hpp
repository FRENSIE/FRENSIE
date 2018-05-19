//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroatomCore.hpp
//! \author Luke Kersting
//! \brief  The electroatom core class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTROATOM_CORE_HPP
#define MONTE_CARLO_ELECTROATOM_CORE_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_ElectroatomicReactionType.hpp"
#include "MonteCarlo_ElectroatomicReaction.hpp"
#include "MonteCarlo_AtomicRelaxationModel.hpp"
#include "MonteCarlo_AtomCore.hpp"
#include "Utility_HashBasedGridSearcher.hpp"
#include "Utility_Vector.hpp"

namespace MonteCarlo{

/*! The electroatom core class for storing electroatomic reactions
 * \details This class can be used to store all reactions and the atomic
 * relaxation model associated with a electroatom. Exposing this object (e.g.
 * get method or export method) is safe since it only allows access to
 * the underlying member data in a way that prohibits modification of that
 * data. This class was created to address the issue that arises when dealing
 * with electro-nuclear data - electro-nuclide's that share the same atomic number
 * need the same electroatomic data. This class allows each electro-nuclide to
 * share the electroatomic data without copying that data (even if each
 * electro-nuclide has its own copy of the electroatom core object).
 */
class ElectroatomCore : public AtomCore<ElectroatomicReactionType,ElectroatomicReaction,ElectronState,boost::unordered_map,std::unordered_set>
{
  // Typedef for the base type
  typedef AtomCore<ElectroatomicReactionType,ElectroatomicReaction,ElectronState,boost::unordered_map,std::unordered_set> BaseType;

public:

  //! Typedef for the reaction type enum
  typedef BaseType::ReactionEnumType ReactionEnumType;

  //! Typedef for the reaction type enum set
  typedef BaseType::ReactionEnumTypeSet ReactionEnumTypeSet;

  //! Typedef for the reaction type
  typedef BaseType::ReactionType ReactionType;

  //! Typedef for the particle state type
  typedef BaseType::ParticleStateType ParticleStateType;

  //! Typedef for the reaction map
  typedef BaseType::ReactionMap ReactionMap;

  //! Typedef for the const reaction map
  typedef BaseType::ConstReactionMap ConstReactionMap;

  //! Default constructor
  ElectroatomCore();

  //! Basic constructor
  template<typename InterpPolicy>
  ElectroatomCore(
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
    const ConstReactionMap& standard_scattering_reactions,
    const ConstReactionMap& standard_absorption_reactions,
    const std::shared_ptr<const AtomicRelaxationModel>& relaxation_model,
    const bool processed_atomic_cross_sections,
    const InterpPolicy policy );

  //! Advanced constructor
  ElectroatomCore(
    const std::shared_ptr<const ElectroatomicReaction>& total_reaction,
    const std::shared_ptr<const ElectroatomicReaction>& total_absorption_reaction,
    const ConstReactionMap& scattering_reactions,
    const ConstReactionMap& absorption_reactions,
    const ConstReactionMap& miscellaneous_reactions,
    const std::shared_ptr<const AtomicRelaxationModel> relaxation_model,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >& grid_searcher );

  //! Copy constructor
  ElectroatomCore( const ElectroatomCore& instance );

  //! Assignment operator
  ElectroatomCore& operator=( const ElectroatomCore& instance );

  //! Destructor
  ~ElectroatomCore()
  { /* ... */ }

private:

  // Set the default absorption reaction types
  static bool setDefaultAbsorptionReactionTypes();

  // Used to set the default absorption reaction types
  static const bool s_default_absorption_reaction_types_set;
};

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

