//---------------------------------------------------------------------------//
//!
//! \file   DataGen_AdjointIncoherentGridGenerator_def.cpp
//! \author Alex Robinson
//! \brief  Adjoint incoherent grid generator definition
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_ADJOINT_INCOHERENT_GRID_GENERATOR_DEF_HPP
#define DATA_GEN_ADJOINT_INCOHERENT_GRID_GENERATOR_DEF_HPP

// Std Lib Includes
#include <algorithm>

// FRENSIE Includes
#include "DataGen_AdjointIncoherentGridGenerator.hpp"
#include "DataGen_AdjointIncoherentCrossSectionHelpers.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_DesignByContract.hpp"

namespace DataGen{

// Constructor
/*! \details The max energy will be used to test the input energy grid (if
 * values in the input grid that are greater than the max energy are found
 * an exception will be thrown). The max energy plus the max energy nudge value
 * will be used as the upper limit for the max energy grid. The max energy
 * nudge value must be greater than 0.0 to avoid an invalid max energy grid
 * at the max energy (each max energy grid must have at least two distinct 
 * points). The energy plus the energy to max energy nudge value will be used 
 * as the lower limit for the max energy grid. Setting a value of 0.0 means 
 * that every max energy grid will start at the corresponding energy. This can 
 * be problematic for log interpolation since the adjoint incoherent cross 
 * section is zero when the energy is equal to the max energy. By pushing the 
 * first max energy slightly above the corresponding energy with this value, 
 * that problem can be avoided (usually leading to smaller grids that converge 
 * faster). Note: when generating grids for subshell incoherent distributions
 * the max energy nudge value should be greater than the binding energy and
 * the energy to max energy nudge value should be greater than or equal to
 * the binding energy since the cross section goes to zero when the energy is 
 * equal to the max energy minus the binding energy.
 */
template<typename TwoDInterpPolicy>
AdjointIncoherentGridGenerator<TwoDInterpPolicy>::AdjointIncoherentGridGenerator(
                                const double max_energy,
                                const double max_energy_nudge_value,
                                const double energy_to_max_energy_nudge_value,
                                const double convergence_tol,
                                const double absolute_diff_tol,
                                const double distance_tol )
  : Utility::TwoDGridGenerator<TwoDInterpPolicy>( convergence_tol,
                                                  absolute_diff_tol,
                                                  distance_tol ),
    d_max_energy( max_energy ),
    d_nudged_max_energy( max_energy + max_energy_nudge_value ),
    d_energy_to_max_energy_nudge_value( energy_to_max_energy_nudge_value )
{
  // Make sure the max energy is valid
  testPrecondition( max_energy > 0.0 );
  // Make sure the max energy nudge value is valid
  testPrecondition( max_energy_nudge_value > 0.0 );
  // Make sure the energy to max energy nudge value is valid
  testPrecondition( energy_to_max_energy_nudge_value >= 0.0 );
}

// Get the max energy
template<typename TwoDInterpPolicy>
double AdjointIncoherentGridGenerator<TwoDInterpPolicy>::getMaxEnergy() const
{
  return d_max_energy;
}

// Set the max energy nudge value
/*! The max energy plus the max energy nudge value
 * will be used as the upper limit for the max energy grid. The max energy
 * nudge value must be greater than 0.0 to avoid an invalid max energy grid
 * at the max energy (each max energy grid must have at least two distinct 
 * points). Note: when generating grids for subshell incoherent distributions
 * the max energy nudge value should be greater than the binding energy since 
 * the cross section goes to zero when the energy is equal to the max energy 
 * minus the binding energy.
 */
template<typename TwoDInterpPolicy>
void AdjointIncoherentGridGenerator<TwoDInterpPolicy>::setMaxEnergyNudgeValue(
                                          const double max_energy_nudge_value )
{
  // Make sure the max energy nudge value is valid
  testPrecondition( max_energy_nudge_value > 0.0 );
  
  d_nudged_max_energy = d_max_energy + max_energy_nudge_value;
}

// Get the nudged max energy
template<typename TwoDInterpPolicy>
double AdjointIncoherentGridGenerator<TwoDInterpPolicy>::getNudgedMaxEnergy() const
{
  return d_nudged_max_energy;
}

// Set the energy to max energy nudge value
/*! The energy plus the energy to max energy nudge value will be used 
 * as the lower limit for the max energy grid. Setting a value of 0.0 means 
 * that every max energy grid will start at the corresponding energy. This can 
 * be problematic for log interpolation since the adjoint incoherent cross 
 * section is zero when the energy is equal to the max energy. By pushing the 
 * first max energy slightly above the corresponding energy with this value, 
 * that problem can be avoided (usually leading to smaller grids that converge 
 * faster). Note: when generating grids for subshell incoherent distributions
 * the energy to max energy nudge value should be greater than or equal to
 * the binding energy since the cross section goes to zero when the energy is 
 * equal to the max energy minus the binding energy.
 */
template<typename TwoDInterpPolicy>
void AdjointIncoherentGridGenerator<TwoDInterpPolicy>::setEnergyToMaxEnergyNudgeValue(
                                const double energy_to_max_energy_nudge_value )
{
  // Make sure the energy to max energy nudge value is valid
  testPrecondition( energy_to_max_energy_nudge_value >= 0.0 );
  
  d_energy_to_max_energy_nudge_value = energy_to_max_energy_nudge_value;
}

// Get the nudged energy
template<typename TwoDInterpPolicy>
double AdjointIncoherentGridGenerator<TwoDInterpPolicy>::getNudgedEnergy(
                                                    const double energy ) const
{
  return energy + d_energy_to_max_energy_nudge_value;
}

// Create a cross section evaluator
/*! The std::function returned from this method can be used with the
 * generate methods to generate the two-dimensional grid.
 */
template<typename TwoDInterpPolicy>
std::function<double (double,double)>
AdjointIncoherentGridGenerator<TwoDInterpPolicy>::createCrossSectionEvaluator(
     const std::shared_ptr<const MonteCarlo::IncoherentAdjointPhotonScatteringDistribution>& adjoint_incoherent_cross_section,
     const double cross_section_evaluation_tol )
{
  // Make sure the cross section is valid
  testPrecondition( adjoint_incoherent_cross_section.get() );

  typedef MonteCarlo::IncoherentAdjointPhotonScatteringDistribution DistType;

  // The evaluateIntegratedCrossSection method that we want to bind to is
  // overloaded. We have to disambiguate it for the bind to work.
  return std::bind<double>( (double(DistType::*)(double,double,double) const)&DistType::evaluateIntegratedCrossSection,
                            std::cref( *adjoint_incoherent_cross_section ),
                            std::placeholders::_1,
                            std::placeholders::_2,
                            cross_section_evaluation_tol );
}

// Add critical energies to energy grid
template<typename TwoDInterpPolicy>
void AdjointIncoherentGridGenerator<TwoDInterpPolicy>::addCriticalValuesToPrimaryGrid(
                                        std::deque<double>& energy_grid ) const
{
  // Make sure the primary grid is sorted
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
                                                      energy_grid.end(),
                                                      true ) );

  // Add the max energy
  if( energy_grid.back() < d_max_energy )
    energy_grid.push_back( d_max_energy );
  
  // Calculate the critical energy (the energy where the cross section has
  // a max value)
  const double energy_of_max_cs =
    getEnergyOfMaxCrossSection( this->getNudgedMaxEnergy() );

  // Insert the critical energy into the grid
  if( energy_of_max_cs > energy_grid.front() )
  {
    std::deque<double>::iterator critical_position =
      std::lower_bound( energy_grid.begin(),
                        energy_grid.end(),
                        energy_of_max_cs );

    // If this is not true then the critical energy is already present
    if( *critical_position > energy_of_max_cs )
      energy_grid.insert( critical_position, energy_of_max_cs );
  }
}

// Initialize the max energy grid at an energy grid point
template<typename TwoDInterpPolicy>
void AdjointIncoherentGridGenerator<TwoDInterpPolicy>::initializeSecondaryGrid(
                                          std::vector<double>& max_energy_grid,
                                          const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( energy <= d_max_energy );

  // The energy where the cross section has a max can only occur between
  // (0.0,me/2) - the upper bound is the limit of the location of the
  // max cross section as the max energy goes to infinity. The max energy grid
  // will potentially have a different structure if energy is in this range.
  if( doesEnergyCorrespondToAMaxCrossSectionValue( energy ) )
  {
    // Calculate the max energy, at this energy, where the cross section has
    // its max
    double max_energy_of_max_cs =
      getMaxEnergyResultingInMaxCrossSectionValueAtEnergy( energy );

    // The energy is inside the critical range
    if( max_energy_of_max_cs < this->getNudgedMaxEnergy() &&
        max_energy_of_max_cs > this->getNudgedEnergy( energy ) )
    {
      max_energy_grid.resize( 3 );

      max_energy_grid[0] = this->getNudgedEnergy( energy );
      max_energy_grid[1] = max_energy_of_max_cs;
      max_energy_grid[2] = this->getNudgedMaxEnergy();
    }
    // The energy is outside of the critical range
    else
    {
      max_energy_grid.resize( 2 );

      max_energy_grid[0] = this->getNudgedEnergy( energy );
      max_energy_grid[1] = this->getNudgedMaxEnergy();
    }
  }
  // The energy is outside of the critical range
  else
  {
    max_energy_grid.resize( 2 );

    max_energy_grid[0] = this->getNudgedEnergy( energy );
    max_energy_grid[1] = this->getNudgedMaxEnergy();
  }

  // Make sure the max energy grid is valid
  testPostcondition( max_energy_grid.size() >= 2 );
}

} // end DataGen namespace

#endif // end DATA_GEN_ADJOINT_INCOHERENT_GRID_GENERATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end DataGen_AdjointIncoherentGridGenerator_def.hpp
//---------------------------------------------------------------------------//
