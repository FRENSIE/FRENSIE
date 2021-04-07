//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotoatomCore.hpp
//! \author Alex Robinson
//! \brief  The photoatom core class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHOTOATOM_CORE_HPP
#define MONTE_CARLO_PHOTOATOM_CORE_HPP

// FRENSIE Includes
#include "MonteCarlo_PhotoatomicReactionType.hpp"
#include "MonteCarlo_PhotoatomicReaction.hpp"
#include "MonteCarlo_AtomicRelaxationModel.hpp"
#include "MonteCarlo_AtomCore.hpp"
#include "Utility_HashBasedGridSearcher.hpp"
#include "Utility_Vector.hpp"

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
class PhotoatomCore : public AtomCore<PhotoatomicReactionType,PhotoatomicReaction,PhotonState,std::map,std::set>
{
  // Typedef for the base type
  typedef AtomCore<PhotoatomicReactionType,PhotoatomicReaction,PhotonState,std::map,std::set> BaseType;

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
  PhotoatomCore();

  //! Basic constructor
  template<typename InterpPolicy>
  PhotoatomCore(
       const std::shared_ptr<const std::vector<double> >& energy_grid,
       const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
       grid_searcher,
       const ConstReactionMap& standard_scattering_reactions,
       const ConstReactionMap& standard_absorption_reactions,
       const std::shared_ptr<const AtomicRelaxationModel>& relaxation_model,
       const bool processed_atomic_cross_sections,
       const InterpPolicy policy );

  //! Advanced constructor
  PhotoatomCore(
     const std::shared_ptr<const PhotoatomicReaction>& total_reaction,
     const std::shared_ptr<const PhotoatomicReaction>& total_absorption_reaction,
     const ConstReactionMap& scattering_reactions,
     const ConstReactionMap& absorption_reactions,
     const ConstReactionMap& miscellaneous_reactions,
     const std::shared_ptr<const AtomicRelaxationModel>& relaxation_model,
     const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
     grid_searcher );

  //! Copy constructor
  PhotoatomCore( const PhotoatomCore& instance );

  //! Assignment operator
  PhotoatomCore& operator=( const PhotoatomCore& instance );

  //! Destructor
  ~PhotoatomCore()
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

#include "MonteCarlo_PhotoatomCore_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_PHOTOATOM_CORE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotoatomCore.hpp
//---------------------------------------------------------------------------//
