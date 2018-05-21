//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectroatomCore.hpp
//! \author Luke Kersting
//! \brief  The adjoint electroatom core class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_ELECTROATOM_CORE_HPP
#define MONTE_CARLO_ADJOINT_ELECTROATOM_CORE_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_AdjointElectroatomicReactionType.hpp"
#include "MonteCarlo_AdjointElectroatomicReaction.hpp"
#include "MonteCarlo_ElectroatomicReaction.hpp"
#include "MonteCarlo_AdjointAtomCore.hpp"
#include "Utility_HashBasedGridSearcher.hpp"
#include "Utility_Map.hpp"

namespace MonteCarlo{

/*! The adjoint electroatom core class for storing adjoint electroatomic reactions
 * \details This class can be used to store all reactions and the atomic
 * relaxation model associated with a adjoint electroatom. Exposing this object (e.g.
 * get method or export method) is safe since it only allows access to
 * the underlying member data in a way that prohibits modification of that
 * data. This class was created to address the issue that arises when dealing
 * with electro-nuclear data - electro-nuclide's that share the same atomic number
 * need the same adjoint electroatomic data. This class allows each electro-nuclide to
 * share the adjoint electroatomic data without copying that data (even if each
 * electro-nuclide has its own copy of the adjoint electroatom core object).
 */
class AdjointElectroatomCore : public AdjointAtomCore<AdjointElectroatomicReactionType,ElectroatomicReaction,AdjointElectroatomicReaction,AdjointElectronState,boost::unordered_map,std::unordered_set>
{
  // Typedef for the base type
  typedef AdjointAtomCore<AdjointElectroatomicReactionType,ElectroatomicReaction,AdjointElectroatomicReaction,AdjointElectronState,boost::unordered_map,std::unordered_set> BaseType;

public:

  //! Typedef for the reaction type enum
  typedef BaseType::ReactionEnumType ReactionEnumType;

  //! Typedef for the reaction type enum set
  typedef BaseType::ReactionEnumTypeSet ReactionEnumTypeSet;

  //! Typedef for the reaction type
  typedef BaseType::ReactionType ReactionType;

  //! Typedef for the forward reaction type
  typedef BaseType::ForwardReactionType ForwardReactionType;

  //! Typedef for the particle state type
  typedef BaseType::ParticleStateType ParticleStateType;

  //! Typedef for the reaction map
  typedef BaseType::ReactionMap ReactionMap;

  //! Typedef for the const reaction map
  typedef BaseType::ConstReactionMap ConstReactionMap;

  //! Typedef for the line energy reaction map
  typedef BaseType::LineEnergyReactionMap LineEnergyReactionMap;

  //! Typedef for the const line energy reaction map
  typedef BaseType::ConstLineEnergyReactionMap ConstLineEnergyReactionMap;

  //! Default constructor
  AdjointElectroatomCore();

  //! Constructor
  template<typename InterpPolicy>
  AdjointElectroatomCore(
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
    grid_searcher,
    const std::shared_ptr<const std::vector<double> >& critical_line_energies,
    const std::shared_ptr<const ElectroatomicReaction>& total_forward_reaction,
    const ConstReactionMap& scattering_reactions,
    const ConstReactionMap& absorption_reactions,
    const ConstLineEnergyReactionMap& line_energy_reactions,
    const bool processed_atomic_cross_section,
    const InterpPolicy policy );

  //! Copy constructor
  AdjointElectroatomCore( const AdjointElectroatomCore& instance );

  //! Assignment operator
  AdjointElectroatomCore& operator=( const AdjointElectroatomCore& instance );

  //! Destructor
  ~AdjointElectroatomCore()
  { /* ... */ }
};

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

