//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_Electroatom_def.hpp
//! \author Alex Robinson
//! \brief  The electroatom base class template definitions
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTROATOM_DEF_HPP
#define MONTE_CARLO_ELECTROATOM_DEF_HPP

// FRENSIE Includes
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
template<typename InterpPolicy>
Electroatom::Electroatom(
      const std::string& name,
      const unsigned atomic_number,
      const double atomic_weight,
      const std::shared_ptr<std::vector<double> >& energy_grid,
      const std::shared_ptr<const Utility::HashBasedGridSearcher>& grid_searcher,
      const Electroatom::ReactionMap& standard_scattering_reactions,
      const Electroatom::ReactionMap& standard_absorption_reactions,
      const std::shared_ptr<const AtomicRelaxationModel>& atomic_relaxation_model,
      const bool processed_cross_sections,
      const InterpPolicy policy )
  : Atom<ElectroatomCore>( name,
                           atomic_number,
                           atomic_weight,
                           grid_searcher,
                           standard_scattering_reactions,
                           standard_absorption_reactions )
{
  // Make sure the atomic weight is valid
  testPrecondition( atomic_weight > 0.0 );
  // Make sure the energy grid is valid
  testPrecondition( energy_grid.size() > 1 );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
                                                      energy_grid.end() ) );
  // There must be at least one reaction specified
  testPrecondition( standard_scattering_reactions.size() +
                    standard_absorption_reactions.size() > 0 );
  // Make sure the atomic relaxation model is valid
  testPrecondition( !atomic_relaxation_model.is_null() );
  // Make sure the grid searcher is valid
  testPrecondition( !grid_searcher.is_null() );

  // Populate the core
  Atom<ElectroatomCore>::setCore(
                      ElectroatomCore( energy_grid,
                                       grid_searcher,
                                       standard_scattering_reactions,
                                       standard_absorption_reactions,
                                       atomic_relaxation_model,
                                       processed_cross_sections,
                                       policy ) );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELECTROATOM_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_Electroatom_def.hpp
//---------------------------------------------------------------------------//

