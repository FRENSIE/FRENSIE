//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectroatom.cpp
//! \author Luke Kersting
//! \brief  The adjoint electroatom base class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_AdjointElectroatom.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
AdjointElectroatom::AdjointElectroatom(
      const std::string& name,
      const unsigned atomic_number,
      const double atomic_weight,
      const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
      const std::shared_ptr<const ElectroatomicReaction>& total_forward_reaction,
      const ReactionMap& scattering_reactions,
      const ReactionMap& absorption_reactions )
  : Atom<AdjointElectroatomCore>( name,
                                  atomic_number,
                                  atomic_weight,
                                  grid_searcher,
                                  scattering_reactions,
                                  absorption_reactions )
{
  // Make sure the atomic weight is valid
  testPrecondition( atomic_weight > 0.0 );
  // There must be at least one reaction specified
  testPrecondition( scattering_reactions.size() +
                    absorption_reactions.size() > 0 );
  // Make sure the grid searcher is valid
  testPrecondition( !grid_searcher.is_null() );

  // Populate the core
  Atom<AdjointElectroatomCore>::setCore(
                    AdjointElectroatomCore( grid_searcher,
                                            total_forward_reaction,
                                            scattering_reactions,
                                            absorption_reactions ) );

  // Make sure the reactions have a shared energy grid
  testPostcondition( d_core.hasSharedEnergyGrid() );
}

// Return the total forward cross section
double AdjointElectroatom::getTotalForwardCrossSection(
                                                    const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );
  
  return d_core.getTotalForwardReaction().getCrossSection( energy );
}

// Return the adjoint weight factor at the desired energy
/*! \details Generally, we do not use the weight factor for an individual atom.
 * The weight factor of an entire material is more commonly used.
 */
double AdjointElectroatom::getAdjointWeightFactor( const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  double weight_factor;
  
  double total_forward_cross_section =
    this->getTotalForwardCrossSection( energy );

  if( total_forward_cross_section > 0.0 )
  {
    weight_factor = this->getTotalCrossSection( energy )/
      total_forward_cross_section;
  }
  else
    weight_factor = 1.0;

  // Make sure the weight factor is valid
  testPrecondition( weight_factor > 0.0 );

  return weight_factor;
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
      d_core.getScatteringReactions().find( reaction );

    if( adjoint_electroatomic_reaction != d_core.getScatteringReactions().end() )
      return adjoint_electroatomic_reaction->second->getCrossSection( energy );

    adjoint_electroatomic_reaction =
        d_core.getAbsorptionReactions().find( reaction );

    if( adjoint_electroatomic_reaction != d_core.getAbsorptionReactions().end() )
      return adjoint_electroatomic_reaction->second->getCrossSection( energy );
    else // If the reaction does not exist for an atom, return 0
      return 0.0;
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectroatom.cpp
//---------------------------------------------------------------------------//


