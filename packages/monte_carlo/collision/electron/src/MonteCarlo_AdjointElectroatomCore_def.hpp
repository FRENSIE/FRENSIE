//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectroatomCore_def.hpp
//! \author Luke Kersting
//! \brief  The adjoint electroatom core template definitions
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_ELECTROATOM_CORE_DEF_HPP
#define MONTE_CARLO_ADJOINT_ELECTROATOM_CORE_DEF_HPP

// FRENSIE Includes
#include "MonteCarlo_AbsorptionAdjointElectroatomicReaction.hpp"
#include "MonteCarlo_VoidAbsorptionAdjointElectroatomicReaction.hpp"
#include "MonteCarlo_VoidAtomicRelaxationModel.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
/*! \details Care must be taken when setting the critical line energies and
 * scattering reactions. The critical line energies must correspond to the
 * critical line energies that are being used by the scattering reactions.
 */
template<typename InterpPolicy>
AdjointElectroatomCore::AdjointElectroatomCore(
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
    grid_searcher,
    const std::shared_ptr<const std::vector<double> >& critical_line_energies,
    const std::shared_ptr<const ElectroatomicReaction>& total_forward_reaction,
    const ConstReactionMap& scattering_reactions,
    const ConstReactionMap& absorption_reactions,
    const ConstLineEnergyReactionMap& line_energy_reactions,
    const bool processed_atomic_cross_section,
    const InterpPolicy policy )
  : BaseType( critical_line_energies,
              total_forward_reaction,
              scattering_reactions,
              absorption_reactions,
              line_energy_reactions,
              std::make_shared<VoidAtomicRelaxationModel>(),
              grid_searcher )
{
  // Make sure the energy grid is valid
  testPrecondition( energy_grid->size() > 1 );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid->begin(),
						      energy_grid->end() ) );

  // Create the total absorption and total reactions
  if( processed_atomic_cross_section )
  {
    if( this->getAbsorptionReactions().size() > 0 )
    {
      this->createProcessedTotalAbsorptionReaction<InterpPolicy,AbsorptionAdjointElectroatomicReaction>(
                             energy_grid,
                             TOTAL_ABSORPTION_ADJOINT_ELECTROATOMIC_REACTION );
    }
    else
    {
      // Create void absorption reaction
      this->setTotalAbsorptionReaction( std::make_shared<VoidAbsorptionAdjointElectroatomicReaction>() );
    }

    this->createProcessedTotalReaction<InterpPolicy,AbsorptionAdjointElectroatomicReaction>(
                                        energy_grid,
                                        TOTAL_ADJOINT_ELECTROATOMIC_REACTION );
  }
  else
  {
    if( this->getAbsorptionReactions().size() > 0 )
    {
      this->createTotalAbsorptionReaction<InterpPolicy,AbsorptionAdjointElectroatomicReaction>(
                             energy_grid,
                             TOTAL_ABSORPTION_ADJOINT_ELECTROATOMIC_REACTION );
    }
    else
    {
       // Create void absorption reaction
      this->setTotalAbsorptionReaction( std::make_shared<VoidAbsorptionAdjointElectroatomicReaction>() );
    }

    this->createTotalReaction<InterpPolicy,AbsorptionAdjointElectroatomicReaction>(
                                        energy_grid,
                                        TOTAL_ADJOINT_ELECTROATOMIC_REACTION );
  }
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ADJOINT_ELECTROATOM_CORE_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectroatomCore_def.hpp
//---------------------------------------------------------------------------//
