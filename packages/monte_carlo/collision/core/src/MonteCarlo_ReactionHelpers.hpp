//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ReactionHelpers.hpp
//! \author Luke Kersting
//! \brief  The reaction helper class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_REACTION_HELPERS_HPP
#define MONTE_CARLO_REACTION_HELPERS_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "Utility_ContractException.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_Vector.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"

namespace MonteCarlo{

  // Return the cross section at a given energy
  template<typename InterpPolicy>
  double getCrossSection(
    const double energy,
    const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
    const std::shared_ptr<const std::vector<double> >& cross_section,
    const unsigned threshold_energy_index );

  // Return the cross section at a given energy
  template<typename InterpPolicy>
  double getCrossSection(
    const double energy,
    const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
    const std::shared_ptr<const std::vector<double> >& cross_section,
    const unsigned threshold_energy_index,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >& grid_searcher );

  // Return the cross section at a given energy (efficient)
  template<typename InterpPolicy>
  double getCrossSection(
    const double energy,
    const unsigned bin_index,
    const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
    const std::shared_ptr<const std::vector<double> >& cross_section,
    const unsigned threshold_energy_index );

  // Return the cross section at a given energy
  template<typename InterpPolicy>
  double getProcessedCrossSection(
    const double energy,
    const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
    const std::shared_ptr<const std::vector<double> >& cross_section,
    const unsigned threshold_energy_index );

  // Return the cross section at a given energy
  template<typename InterpPolicy>
  double getProcessedCrossSection(
    const double energy,
    const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
    const std::shared_ptr<const std::vector<double> >& cross_section,
    const unsigned threshold_energy_index,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >& grid_searcher );

  // Return the cross section at a given energy (efficient)
  template<typename InterpPolicy>
  double getProcessedCrossSection(
    const double energy,
    const unsigned bin_index,
    const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
    const std::shared_ptr<const std::vector<double> >& cross_section,
    const unsigned threshold_energy_index );

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_ReactionHelpers_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_REACTION_HELPERS_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ReactionHelpers.hpp
//---------------------------------------------------------------------------//
