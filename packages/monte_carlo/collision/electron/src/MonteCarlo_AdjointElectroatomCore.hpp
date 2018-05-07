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
class AdjointElectroatomCore
{

public:

  //! Typedef for the reaction type enum
  typedef AdjointElectroatomicReactionType ReactionEnumType;

  //! Typedef for the particle state type
  typedef AdjointElectronState ParticleStateType;

  //! Typedef for the reaction map
  typedef std::unordered_map<AdjointElectroatomicReactionType,
                               std::shared_ptr<AdjointElectroatomicReaction> >
  ReactionMap;

  //! Typedef for the const reaction map
  typedef std::unordered_map<AdjointElectroatomicReactionType,
                           std::shared_ptr<const AdjointElectroatomicReaction> >
  ConstReactionMap;

  //! Typedef for the line energy reaction map
  typedef std::unordered_map<double,ReactionMap> LineEnergyReactionMap;

  //! Typedef for the const line energy reaction map
  typedef std::unordered_map<double,ConstReactionMap> ConstLineEnergyReactionMap;

  //! Default constructor
  AdjointElectroatomCore();

  //! Constructor
  AdjointElectroatomCore(
      const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
      const std::shared_ptr<const std::vector<double> >& critical_line_energies,
      const std::shared_ptr<const ElectroatomicReaction>& total_forward_reaction,
      const ConstReactionMap& scattering_reactions,
      const ConstReactionMap& absorption_reactions,
      const ConstLineEnergyReactionMap& line_energy_reactions );

  //! Copy constructor
  AdjointElectroatomCore( const AdjointElectroatomCore& instance );

  //! Assignment operator
  AdjointElectroatomCore& operator=( const AdjointElectroatomCore& instance );

  //! Destructor
  ~AdjointElectroatomCore()
  { /* ... */ }

  //! Return the total forward reaction
  const ElectroatomicReaction& getTotalForwardReaction() const;

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
  std::shared_ptr<const ElectroatomicReaction> d_total_forward_reaction;

  // The scattering reactions
  ConstReactionMap d_scattering_reactions;

  // The absorption reactions
  ConstReactionMap d_absorption_reactions;

  // The line energy reactions
  ConstLineEnergyReactionMap d_line_energy_reactions;

  // The critical line energies
  std::shared_ptr<const std::vector<double> > d_critical_line_energies;

  // The hash-based grid searcher
  std::shared_ptr<const Utility::HashBasedGridSearcher<double>> d_grid_searcher;
};

// Return the total forward reaction
inline auto AdjointElectroatomCore::getTotalForwardReaction() const -> const ElectroatomicReaction&
{
  return *d_total_forward_reaction;
}

// Return the scattering reactions
inline auto AdjointElectroatomCore::getScatteringReactions() const -> const ConstReactionMap&
{
  return d_scattering_reactions;
}

// Return the absorption reactions
inline auto AdjointElectroatomCore::getAbsorptionReactions() const -> const ConstReactionMap&
{
  return d_absorption_reactions;
}

// Return the line energy reactions
inline auto AdjointElectroatomCore::getLineEnergyReactions() const -> const ConstLineEnergyReactionMap&
{
  return d_line_energy_reactions;
}

// Return the critical line energies
inline auto AdjointElectroatomCore::getCriticalLineEnergies() const -> const std::vector<double>&
{
  return *d_critical_line_energies;
}

// Return the hash-based grid searcher
inline const Utility::HashBasedGridSearcher<double>& AdjointElectroatomCore::getGridSearcher() const
{
  return *d_grid_searcher;
}

// Check if the line energy reactions are valid
template<typename Map>
bool AdjointElectroatomCore::areLineEnergyReactionsValid(
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

#endif // end MONTE_CARLO_ADJOINT_ELECTROATOM_CORE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectroatomCore.hpp
//---------------------------------------------------------------------------//

