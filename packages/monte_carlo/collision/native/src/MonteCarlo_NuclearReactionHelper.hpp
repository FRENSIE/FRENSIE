//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NuclearReactionHelper.hpp
//! \author Eli Moll
//! \brief  The nuclear reaction helper class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_NUCLEAR_REACTION_HELPER_HPP
#define MONTE_CARLO_NUCLEAR_REACTION_HELPER_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "Utility_ContractException.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_Vector.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

//! Return the cross section at a given energy
inline double getCrossSection(
       const double energy,
       const std::vector<double>& incoming_energy_grid,
       const std::vector<double>& cross_section,
       const unsigned threshold_energy_index )
{
  if( energy >= incoming_energy_grid[threshold_energy_index] &&
      energy < incoming_energy_grid.back() )
  {
    unsigned energy_index =
      Utility::Search::binaryLowerBoundIndex( incoming_energy_grid.begin(),
                                              incoming_energy_grid.end(),
                                              energy );
    unsigned cs_index = energy_index - threshold_energy_index;

    return Utility::LinLin::interpolate(incoming_energy_grid[energy_index],
                                        incoming_energy_grid[energy_index+1],
                                        energy,
                                        cross_section[cs_index],
                                        cross_section[cs_index+1] );
  }
  else if( energy < incoming_energy_grid[threshold_energy_index] )
    return 0.0;
  else if( energy == incoming_energy_grid.back() )
  {
    return cross_section.back();
  }
  else // energy > this.getThresholdEnergy()
    return 0.0;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_NUCLEAR_REACTION_HELPER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclearReactionHelper.hpp
//---------------------------------------------------------------------------//
