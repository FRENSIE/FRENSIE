//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ReactionHelpers_def.hpp
//! \author Luke Kersting
//! \brief  The reaction helper class template definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_REACTION_HELPERS_DEF_HPP
#define MONTE_CARLO_REACTION_HELPERS_DEF_HPP

namespace MonteCarlo{

// Return the cross section at a given energy
template<typename InterpPolicy>
double getCrossSection(
    const double energy,
    const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
    const Teuchos::ArrayRCP<const double>& cross_section,
    const unsigned threshold_energy_index )
{
  if( energy >= incoming_energy_grid[threshold_energy_index] &&
      energy < incoming_energy_grid[incoming_energy_grid.size()-1] )
  {
    unsigned energy_index =
      Utility::Search::binaryLowerBoundIndex( incoming_energy_grid.begin(),
                                              incoming_energy_grid.end(),
                                              energy );
    unsigned cs_index = energy_index - threshold_energy_index;

    return InterpPolicy::interpolate( incoming_energy_grid[energy_index],
                                      incoming_energy_grid[energy_index+1],
                                      energy,
                                      cross_section[cs_index],
                                      cross_section[cs_index+1] );
  }
  else if( energy < incoming_energy_grid[threshold_energy_index] )
    return 0.0;
  else if( energy == incoming_energy_grid[incoming_energy_grid.size()-1] )
  {
    return cross_section[cross_section.size()-1];
  }
  else
    return 0.0;
}

// Return the cross section at a given energy
template<typename InterpPolicy>
double getCrossSection(
    const double energy,
    const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
    const Teuchos::ArrayRCP<const double>& cross_section,
    const unsigned threshold_energy_index,
    const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher )
{
  // Make sure the energy is valid
  testPrecondition( grid_searcher->isValueWithinGridBounds( energy ) );

  double cross_section_value;

  if( energy >= incoming_energy_grid[threshold_energy_index] )
  {
    unsigned energy_index = grid_searcher->findLowerBinIndex( energy );

    unsigned cs_index = energy_index - threshold_energy_index;

    cross_section_value =
      InterpPolicy::interpolate( incoming_energy_grid[energy_index],
                                 incoming_energy_grid[energy_index+1],
                                 energy,
                                 cross_section[cs_index],
                                 cross_section[cs_index+1] );
  }
  else if( energy < cross_section[threshold_energy_index] )
    cross_section_value = 0.0;

  // Make sure the cross section is valid
  testPostcondition( cross_section_value >= 0.0 );

  return cross_section_value;
}

// Return the cross section at a given energy (efficient)
template<typename InterpPolicy>
double getCrossSection(
    const double energy,
    const unsigned bin_index,
    const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
    const Teuchos::ArrayRCP<const double>& cross_section,
    const unsigned threshold_energy_index )
{
  // Make sure the bin index is valid
  testPrecondition( incoming_energy_grid[bin_index] <= energy );
  testPrecondition( incoming_energy_grid[bin_index+1] >= energy );

  if( bin_index >= threshold_energy_index )
  {
    unsigned cs_index = bin_index - threshold_energy_index;

    return InterpPolicy::interpolate( incoming_energy_grid[bin_index],
                                      incoming_energy_grid[bin_index+1],
                                      energy,
                                      cross_section[cs_index],
                                      cross_section[cs_index+1] );
  }
  else
    return 0.0;
}

// Return the cross section at a given energy
template<typename InterpPolicy>
double getProcessedCrossSection(
    const double energy,
    const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
    const Teuchos::ArrayRCP<const double>& cross_section,
    const unsigned threshold_energy_index )
{
  if( energy >= incoming_energy_grid[threshold_energy_index] &&
      energy < incoming_energy_grid[incoming_energy_grid.size()-1] )
  {
    unsigned energy_index =
      Utility::Search::binaryLowerBoundIndex( incoming_energy_grid.begin(),
                                              incoming_energy_grid.end(),
                                              energy );
    unsigned cs_index = energy_index - threshold_energy_index;

    double processed_slope =
      (cross_section[cs_index+1]-cross_section[cs_index])/
      (incoming_energy_grid[energy_index+1]-
       incoming_energy_grid[energy_index]);

    return InterpPolicy::interpolate( incoming_energy_grid[energy_index],
                                      InterpPolicy::processIndepVar( energy ),
                                      cross_section[cs_index],
                                      processed_slope );
  }
  else if( energy < incoming_energy_grid[threshold_energy_index] )
    return 0.0;
  else if( energy == incoming_energy_grid[incoming_energy_grid.size()-1] )
  {
    return cross_section[cross_section.size()-1];
  }
  else
    return 0.0;
}

// Return the cross section at a given energy
template<typename InterpPolicy>
double getProcessedCrossSection(
    const double energy,
    const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
    const Teuchos::ArrayRCP<const double>& cross_section,
    const unsigned threshold_energy_index,
    const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher )
{
  // Make sure the energy is valid
  testPrecondition( grid_searcher->isValueWithinGridBounds( energy ) );

  double cross_section_value;

  if( energy >= incoming_energy_grid[threshold_energy_index] )
  {
    unsigned energy_index = grid_searcher->findLowerBinIndex( energy );

    unsigned cs_index = energy_index - threshold_energy_index;

    double processed_slope =
      (cross_section[cs_index+1]-cross_section[cs_index])/
      (incoming_energy_grid[energy_index+1]-
       incoming_energy_grid[energy_index]);

    cross_section_value =
        InterpPolicy::interpolate( incoming_energy_grid[energy_index],
                                   InterpPolicy::processIndepVar( energy ),
                                   cross_section[cs_index],
                                   processed_slope );
  }
  else
    cross_section_value = 0.0;

  // Make sure the cross section is valid
  testPostcondition( cross_section_value >= 0.0 );

  return cross_section_value;
}

// Return the cross section at a given energy (efficient)
template<typename InterpPolicy>
double getProcessedCrossSection(
    const double energy,
    const unsigned bin_index,
    const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
    const Teuchos::ArrayRCP<const double>& cross_section,
    const unsigned threshold_energy_index )
{
  // Make sure the bin index is valid
  testPrecondition( incoming_energy_grid[bin_index] <=
                    InterpPolicy::processIndepVar( energy ) );
  testPrecondition( incoming_energy_grid[bin_index+1] >=
                    InterpPolicy::processIndepVar( energy ) );

  if( bin_index >= threshold_energy_index )
  {
    unsigned cs_index = bin_index - threshold_energy_index;

    double processed_slope =
      (cross_section[cs_index+1]-cross_section[cs_index])/
      (incoming_energy_grid[bin_index+1]-
       incoming_energy_grid[bin_index]);

    double processed_energy = InterpPolicy::processIndepVar( energy );

    return InterpPolicy::interpolate( incoming_energy_grid[bin_index],
                                      processed_energy,
                                      cross_section[cs_index],
                                      processed_slope );
  }
  else
    return 0.0;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_REACTION_HELPERS_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ReactionHelpers_def.hpp
//---------------------------------------------------------------------------//
