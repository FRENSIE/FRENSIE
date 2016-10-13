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
#include <unordered_map>
#include <memory>

// Boost Includes
#include <boost/unordered_map.hpp>

// Trilinos Includes
#include <Teuchos_ArrayRCP.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotoatomicReactionType.hpp"
#include "MonteCarlo_LineEnergyAdjointPhotoatomicReaction.hpp"
#include "MonteCarlo_AdjointPhotoatomicReaction.hpp"
#include "MonteCarlo_PhotoatomicReaction.hpp"
#include "Utility_HashBasedGridSearcher.hpp"

namespace MonteCarlo{

/*! The adjoint photoatom core class for storing adjoint photoatomic reactions
 * \details This class can be used to store all reactions associated with a
 * photoatom. Exposing this object (e.g. get method or export method) is safe
 * since it only allows access to the underlying member data in a way that
 * prohibits modification of that data. This class was created to address the
 * issue that arrises when dealing with adjoint photonuclear data - 
 * photonuclides that share the same atomic number need the same adjoint
 * photoatomic data. This class allows each photonuclide to share the same
 * adjoint photoatomic data without copying that data (even if each 
 * photonuclide has its own copy of the photoatom core object).
 */
class AdjointPhotoatomCore
{

public:

  //! Typedef for the reaction map
  typedef boost::unordered_map<AdjointPhotoatomicReactionType,
                               std::shared_ptr<AdjointPhotoatomicReaction> >
  ReactionMap;

  //! Typedef for the const reaction map
  typedef boost::unordered_map<AdjointPhotoatomicReactionType,
                               std::shared_ptr<const AdjointPhotoatomicReaction> >
  ConstReactionMap;

  //! Typedef for the line energy reaction map
  typedef boost::unordered_map<double,ReactionMap> LineEnergyReactionMap;

  //! Typedef for the const line energy reaction map
  typedef boost::unordered_map<double,ConstReactionMap> ConstLineEnergyReactionMap;

  //! Default constructor
  AdjointPhotoatomCore();

  //! Constructor
  AdjointPhotoatomCore(
      const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
      const std::shared_ptr<const PhotoatomicReaction>& total_forward_reaction,
      const ReactionMap& scattering_reactions,
      const ReactionMap& absorption_reactions,
      const LineEnergyReactionMap& line_energy_reactions );

  //! Copy constructor
  AdjointPhotoatomCore( const AdjointPhotoatomCore& instance );

  //! Assignment operator
  AdjointPhotoatomCore& operator=( const AdjointPhotoatomCore& instance );

  //! Destructor
  ~AdjointPhotoatomCore()
  { /* ... */ }

  //! Return the total forward reaction
  const PhotoatomicReaction& getTotalForwardReaction() const;

  //! Return the scattering reactions
  const ConstReactionMap& getScatteringReactions() const;

  //! Return the absorption reactions
  const ConstReactionMap& getAbsorptionReactions() const;

  //! Return the line energy reactions
  const ConstLineEnergyReactionMap& getLineEnergyReactions() const;

  //! Return the hash-based grid searcher
  const Utility::HashBasedGridSearcher& getGridSearcher() const;

  //! Test if all of the reactions share a common energy grid
  bool hasSharedEnergyGrid() const;

private:

  // The total forward reactions
  std::shared_ptr<const PhotoatomicReaction> d_total_forward_reaction;

  // The scattering reactions
  ConstReactionMap d_scattering_reactions;

  // The absorption reactions
  ConstReactionMap d_absorption_reactions;

  // The line energy reactions
  ConstLineEnergyReactionMap d_line_energy_reactions;

  // The hash-based grid searcher
  Teuchos::RCP<const Utility::HashBasedGridSearcher> d_grid_searcher;
};

// Return the total forward reaction
inline auto AdjointPhotoatomCore::getTotalForwardReaction() const -> const PhotoatomicReaction&
{
  return *d_total_forward_reaction;
}

// Return the scattering reactions
inline auto AdjointPhotoatomCore::getScatteringReactions() const -> const ConstReactionMap& 
{
  return d_scattering_reactions;
}

// Return the absorption reactions
inline auto AdjointPhotoatomCore::getAbsorptionReactions() const -> const ConstReactionMap&
{
  return d_absorption_reactions;
}

// Return the line energy reactions
inline auto AdjointPhotoatomCore::getLineEnergyReactions() const -> const ConstLineEnergyReactionMap&
{
  return d_line_energy_reactions;
}

// Return the hash-based grid searcher
inline const Utility::HashBasedGridSearcher& AdjointPhotoatomCore::getGridSearcher() const
{
  return *d_grid_searcher;
}
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ADJOINT_PHOTOATOM_CORE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointPhotoatomCore.hpp
//---------------------------------------------------------------------------//
