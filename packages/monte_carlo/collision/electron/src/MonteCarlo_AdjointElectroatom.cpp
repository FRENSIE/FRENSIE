//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectroatom.cpp
//! \author Luke Kersting
//! \brief  The adjoint electroatom base class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_AdjointElectroatom.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
AdjointElectroatom::AdjointElectroatom(
      const std::string& name,
      const unsigned atomic_number,
      const double atomic_weight,
      const std::shared_ptr<const std::vector<double> >& energy_grid,
      const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>&
      grid_searcher,
      const std::shared_ptr<const std::vector<double> >&
      critical_line_energies,
      const std::shared_ptr<const ElectroatomicReaction>& total_forward_reaction,
      const ConstReactionMap& scattering_reactions,
      const ConstReactionMap& absorption_reactions,
      const ConstLineEnergyReactionMap& line_energy_reactions )
  : BaseType( name, atomic_number, atomic_weight )
{
  // Make sure the atomic weight is valid
  testPrecondition( atomic_weight > 0.0 );
  // There must be at least one reaction specified
  testPrecondition( scattering_reactions.size() +
                    absorption_reactions.size() > 0 );
  // Make sure the grid searcher is valid
  testPrecondition( grid_searcher.get() );

  // Populate the core
  BaseType::setCore( AdjointElectroatomCore( energy_grid,
                                             grid_searcher,
                                             critical_line_energies,
                                             total_forward_reaction,
                                             scattering_reactions,
                                             absorption_reactions,
                                             line_energy_reactions,
                                             false,
                                             Utility::LogLog() ) );

  // Make sure the reactions have a shared energy grid
  testPostcondition( this->getCore().hasSharedEnergyGrid() );
}

// Return the cross section for a specific adjoint electroatomic reaction
double AdjointElectroatom::getReactionCrossSection(
                    const double energy,
                    const AdjointElectroatomicReactionType reaction ) const
{
  switch( reaction )
  {
  case TOTAL_ADJOINT_ELECTROATOMIC_REACTION:
    return this->getTotalCrossSection( energy );
  default:
    ConstReactionMap::const_iterator adjoint_electroatomic_reaction =
      this->getCore().getScatteringReactions().find( reaction );

    if( adjoint_electroatomic_reaction != this->getCore().getScatteringReactions().end() )
      return adjoint_electroatomic_reaction->second->getCrossSection( energy );

    adjoint_electroatomic_reaction =
        this->getCore().getAbsorptionReactions().find( reaction );

    if( adjoint_electroatomic_reaction != this->getCore().getAbsorptionReactions().end() )
      return adjoint_electroatomic_reaction->second->getCrossSection( energy );
    else // If the reaction does not exist for an atom, return 0
      return 0.0;
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectroatom.cpp
//---------------------------------------------------------------------------//


