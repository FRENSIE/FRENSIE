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

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotoatomicReactionType.hpp"
#include "MonteCarlo_LineEnergyAdjointPhotoatomicReaction.hpp"
#include "MonteCarlo_AdjointPhotoatomicReaction.hpp"
#include "MonteCarlo_PhotoatomicReaction.hpp"
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
class AdjointPhotoatomCore
{

public:

  //! Typedef for the reaction type enum
  typedef AdjointPhotoatomicReactionType ReactionEnumType;

  //! Typedef for the particle state type
  typedef AdjointPhotonState ParticleStateType;

  //! Typedef for the reaction map
  typedef std::unordered_map<AdjointPhotoatomicReactionType,
                             std::shared_ptr<AdjointPhotoatomicReaction> >
  ReactionMap;

  //! Typedef for the const reaction map
  typedef std::unordered_map<AdjointPhotoatomicReactionType,
                             std::shared_ptr<const AdjointPhotoatomicReaction> >
  ConstReactionMap;

  //! Typedef for the line energy reaction map
  typedef std::unordered_map<double,ReactionMap> LineEnergyReactionMap;

  //! Typedef for the const line energy reaction map
  typedef std::unordered_map<double,ConstReactionMap> ConstLineEnergyReactionMap;

  //! Default constructor
  AdjointPhotoatomCore();

  //! Constructor
  AdjointPhotoatomCore(
     const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
     grid_searcher,
     const std::shared_ptr<const std::vector<double> >& critical_line_energies,
     const std::shared_ptr<const PhotoatomicReaction>& total_forward_reaction,
     const ConstReactionMap& scattering_reactions,
     const ConstReactionMap& absorption_reactions,
     const ConstLineEnergyReactionMap& line_energy_reactions );

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

  //! Return the critical line energies
  const std::vector<double>& getCriticalLineEnergies() const;

  //! Return the hash-based grid searcher
  const Utility::HashBasedGridSearcher<double>& getGridSearcher() const;

  //! Test if all of the reactions share a common energy grid
  bool hasSharedEnergyGrid() const;

private:

  // Check if the line energy reactions are valid
  template<typename Map>
  bool areLineEnergyReactionsValid(
         const Map& line_energy_reactions,
         const std::vector<double>& critical_line_energies ) const;

  // The total forward reactions
  std::shared_ptr<const PhotoatomicReaction> d_total_forward_reaction;

  // The scattering reactions
  ConstReactionMap d_scattering_reactions;

  // The absorption reactions
  ConstReactionMap d_absorption_reactions;

  // The line energy reactions
  ConstLineEnergyReactionMap d_line_energy_reactions;

  // The critical line energies
  std::shared_ptr<const std::vector<double> > d_critical_line_energies;

  // The hash-based grid searcher
  std::shared_ptr<const Utility::HashBasedGridSearcher<double> > d_grid_searcher;
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

// Return the critical line energies
inline const std::vector<double>&
AdjointPhotoatomCore::getCriticalLineEnergies() const
{
  return *d_critical_line_energies;
}

// Return the hash-based grid searcher
inline const Utility::HashBasedGridSearcher<double>& AdjointPhotoatomCore::getGridSearcher() const
{
  return *d_grid_searcher;
}

// Check if the line energy reactions are valid
template<typename Map>
bool AdjointPhotoatomCore::areLineEnergyReactionsValid(
          const Map& line_energy_reactions,
          const std::vector<double>& critical_line_energies ) const
{
  typename Map::const_iterator line_energies =
    line_energy_reactions.begin();

  // To be valid a line energy reaction must have an associated critical line
  // energy. Without the critical line energy the line energy reaction will
  // never occur.
  while( line_energies != line_energy_reactions.end() )
  {
    if( !std::binary_search( critical_line_energies.begin(),
                             critical_line_energies.end(),
                             line_energies->first ) )
      return false;

    ++line_energies;
  }

  return true;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ADJOINT_PHOTOATOM_CORE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointPhotoatomCore.hpp
//---------------------------------------------------------------------------//
