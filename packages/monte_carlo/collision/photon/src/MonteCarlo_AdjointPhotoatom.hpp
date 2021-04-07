//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointPhotoatom.hpp
//! \author Alex Robinson
//! \brief  The adjoint photoatom base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_PHOTOATOM_HPP
#define MONTE_CARLO_ADJOINT_PHOTOATOM_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotoatomCore.hpp"
#include "MonteCarlo_AdjointAtom.hpp"
#include "Utility_Vector.hpp"
#include "Utility_QuantityTraits.hpp"

namespace MonteCarlo{

//! The atom class for adjoint photoatomic reactions
class AdjointPhotoatom : public AdjointAtom<AdjointPhotoatomCore>
{
  // Typedef for QuantityTraits
  typedef Utility::QuantityTraits<double> QT;

  // Typedef for the base type
  typedef AdjointAtom<AdjointPhotoatomCore> BaseType;

public:

  //! The reaction enum type
  typedef BaseType::ReactionEnumType ReactionEnumType;

  //! The reaction enum set type
  typedef BaseType::ReactionEnumTypeSet ReactionEnumTypeSet;

  //! The particle state type
  typedef BaseType::ParticleStateType ParticleStateType;

  //! Typedef for the reaction map
  typedef BaseType::ReactionMap ReactionMap;

  //! Typedef for the const reaction map
  typedef BaseType::ConstReactionMap ConstReactionMap;

  //! Typedef for the line energy reaction map
  typedef BaseType::LineEnergyReactionMap LineEnergyReactionMap;

  //! Typedef for the const line energy reaction map
  typedef BaseType::ConstLineEnergyReactionMap
  ConstLineEnergyReactionMap;

  //! Constructor
  AdjointPhotoatom(
          const std::string& name,
          const unsigned atomic_number,
          const double atomic_weight,
          const std::shared_ptr<const std::vector<double> >& energy_grid,
          const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
          grid_searcher,
          const std::shared_ptr<const std::vector<double> >&
          critical_line_energies,
          const std::shared_ptr<const PhotoatomicReaction>&
          total_forward_reaction,
          const ConstReactionMap& scattering_reactions,
          const ConstReactionMap& absorption_reactions,
          const ConstLineEnergyReactionMap& line_energy_reactions );

  //! Constructor (from a core)
  AdjointPhotoatom( const std::string& name,
                    const unsigned atomic_number,
                    const double atomic_weight,
                    const AdjointPhotoatomCore& core )
    : BaseType( name, atomic_number, atomic_weight, core )
  { /* ... */ }

  //! Destructor
  virtual ~AdjointPhotoatom()
  { /* ... */ }

  //! Return the cross section for a specific adjoint photoatomic reaction
  double getReactionCrossSection(
                         const double energy,
                         const AdjointPhotoatomicReactionType reaction ) const;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ADJOINT_PHOTOATOM_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointPhotoatom.hpp
//---------------------------------------------------------------------------//
