//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointPhotoatomCore.hpp
//! \author Alex Robinson
//! \brief  The adjoint photoatom core class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_PHOTOATOM_CORE_HPP
#define MONTE_CARLO_ADJOINT_PHOTOATOM_CORE_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotoatomicReactionType.hpp"
#include "MonteCarlo_LineEnergyAdjointPhotoatomicReaction.hpp"
#include "MonteCarlo_AdjointPhotoatomicReaction.hpp"
#include "MonteCarlo_PhotoatomicReaction.hpp"
#include "MonteCarlo_AdjointAtomCore.hpp"
#include "Utility_HashBasedGridSearcher.hpp"
#include "Utility_Vector.hpp"

namespace MonteCarlo{

/*! The adjoint photoatom core class for storing adjoint photoatomic reactions
 * \details This class can be used to store all reactions associated with a
 * photoatom. Exposing this object (e.g. get method or export method) is safe
 * since it only allows access to the underlying member data in a way that
 * prohibits modification of that data. This class was created to address the
 * issue that arises when dealing with adjoint photonuclear data -
 * photo-nuclides that share the same atomic number need the same adjoint
 * photoatomic data. This class allows each photo-nuclide to share the same
 * adjoint photoatomic data without copying that data (even if each
 * photo-nuclide has its own copy of the photoatom core object).
 */
  class AdjointPhotoatomCore : public AdjointAtomCore<AdjointPhotoatomicReactionType,PhotoatomicReaction,AdjointPhotoatomicReaction,AdjointPhotonState,std::unordered_map,std::unordered_set>
{
  // Typedef for the base type
  typedef AdjointAtomCore<AdjointPhotoatomicReactionType,PhotoatomicReaction,AdjointPhotoatomicReaction,AdjointPhotonState,std::unordered_map,std::unordered_set> BaseType;
  
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
  AdjointPhotoatomCore();

  //! Constructor
  template<typename InterpPolicy>
  AdjointPhotoatomCore(
     const std::shared_ptr<const std::vector<double> >& energy_grid,
     const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
     grid_searcher,
     const std::shared_ptr<const std::vector<double> >& critical_line_energies,
     const std::shared_ptr<const PhotoatomicReaction>& total_forward_reaction,
     const ConstReactionMap& scattering_reactions,
     const ConstReactionMap& absorption_reactions,
     const ConstLineEnergyReactionMap& line_energy_reactions,
     const bool processed_atomic_cross_section,
     const InterpPolicy policy );

  //! Copy constructor
  AdjointPhotoatomCore( const AdjointPhotoatomCore& instance );

  //! Assignment operator
  AdjointPhotoatomCore& operator=( const AdjointPhotoatomCore& instance );

  //! Destructor
  ~AdjointPhotoatomCore()
  { /* ... */ }
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_AdjointPhotoatomCore_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_ADJOINT_PHOTOATOM_CORE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointPhotoatomCore.hpp
//---------------------------------------------------------------------------//
