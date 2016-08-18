//---------------------------------------------------------------------------//
//!
//! \file   DataGen_AdjointElectronGridGenerator_def.cpp
//! \author Luke Kersting
//! \brief  Adjoint electron distribution generator definition
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_ADJOINT_ELECTRON_GRID_GENERATOR_DEF_HPP
#define DATA_GEN_ADJOINT_ELECTRON_GRID_GENERATOR_DEF_HPP

// Std Lib Includes
#include <algorithm>

// FRENSIE Includes
#include "Utility_PhysicalConstants.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ContractException.hpp"

namespace DataGen{

// Constructor
/*! \details The max energy will be used to test the input incoming energy grid
 * (if values in the input grid that are greater than the max energy are found
 * an exception will be thrown). The max incoming energy plus the max energy
 * nudge value will be used as the upper limit for the outgoing energy grid.
 * The max energy nudge value must be greater than 0.0 to avoid an invalid
 * outgoing energy grid at the max incoming energy (each outgoing energy grid
 * must have at least two distinct points). The incoming energy plus the energy
 * to outgoing energy nudge value will be used as the lower limit for the
 * outgoing energy grid. Setting a value of 0.0 means that every outgoing energy
 * grid will start at the corresponding energy. This can be problematic for log
 * interpolation since the adjoint electron cross section is zero when the
 * incoming energy is equal to the outgoing energy (for inelastic reactions).
 * By pushing the first outgoing energy slightly above the corresponding energy
 * with this value, that problem can be avoided (usually leading to smaller
 * grids that converge faster). Note: when generating grids for subshell
 * electroionization distributions the max energy nudge value should be greater
 * than the binding energy and the energy to outgoing energy nudge value should
 * be greater than or equal to the binding energy since the cross section goes to
 * zero when the incoming energy is equal to the outgoing energy minus the
 * binding energy.
 */
//template<typename TwoDInterpPolicy>
//AdjointElectronGridGenerator<TwoDInterpPolicy>::AdjointElectronGridGenerator(
//          const std::vector<double>& critical_energies,
//          const double max_energy,
//          const double max_energy_nudge_value,
//          const double energy_to_outgoing_energy_nudge_value,
//          const double convergence_tol,
//          const double absolute_diff_tol,
//          const double distance_tol )
//  : AdjointElectronGridGenerator<TwoDInterpPolicy>(
//          max_energy,
//          max_energy_nudge_value,
//          energy_to_outgoing_energy_nudge_value,
//          convergence_tol,
//          absolute_diff_tol,
//          distance_tol ),
//    d_critical_energies( critical_energies )
//{
//  // Make sure the critical energies are valid
//  testPrecondition( critical_energies.size() > 0 );
//}

// Basic Constructor
/*! \details The max energy will be used to test the input incoming energy grid
 * (if values in the input grid that are greater than the max energy are found
 * an exception will be thrown). The max incoming energy plus the max energy
 * nudge value will be used as the upper limit for the outgoing energy grid.
 * The max energy nudge value must be greater than 0.0 to avoid an invalid
 * outgoing energy grid at the max incoming energy (each outgoing energy grid
 * must have at least two distinct points). The incoming energy plus the energy
 * to outgoing energy nudge value will be used as the lower limit for the
 * outgoing energy grid. Setting a value of 0.0 means that every outgoing energy
 * grid will start at the corresponding energy. This can be problematic for log
 * interpolation since the adjoint electron cross section is zero when the
 * incoming energy is equal to the outgoing energy (for inelastic reactions).
 * By pushing the first outgoing energy slightly above the corresponding energy
 * with this value, that problem can be avoided (usually leading to smaller
 * grids that converge faster). Note: when generating grids for subshell
 * electroionization distributions the max energy nudge value should be greater
 * than the binding energy and the energy to outgoing energy nudge value should
 * be greater than or equal to the binding energy since the cross section goes to
 * zero when the incoming energy is equal to the outgoing energy minus the
 * binding energy.
 */
template<typename TwoDInterpPolicy>
AdjointElectronGridGenerator<TwoDInterpPolicy>::AdjointElectronGridGenerator(
          const double max_energy,
          const double max_energy_nudge_value,
          const double energy_to_outgoing_energy_nudge_value,
          const double convergence_tol,
          const double absolute_diff_tol,
          const double distance_tol )
  : Utility::TwoDGridGenerator<TwoDInterpPolicy>( convergence_tol,
                                                  absolute_diff_tol,
                                                  distance_tol ),
    d_max_energy( max_energy ),
    d_nudged_max_energy( max_energy + max_energy_nudge_value ),
    d_energy_to_outgoing_energy_nudge_value(  energy_to_outgoing_energy_nudge_value )
{
  // Make sure the max energy is valid
  testPrecondition( max_energy > 0.0 );
  // Make sure the max energy nudge value is valid
  testPrecondition( max_energy_nudge_value > 0.0 );
  // Make sure the energy to outgoing energy nudge value is valid
  testPrecondition(  energy_to_outgoing_energy_nudge_value >= 0.0 );
}

// Get the max energy
template<typename TwoDInterpPolicy>
double AdjointElectronGridGenerator<TwoDInterpPolicy>::getMaxEnergy() const
{
  return d_max_energy;
}

// Set the max energy nudge value
/*! The max energy plus the max energy nudge value will be used as the upper
 * limit for the outgoing energy grid. The max energy nudge value must be
 * greater than 0.0 to avoid an invalid outgoing energy grid at the max incoming
 * energy (each outgoing energy grid must have at least two distinct points).
 * Note: when generating grids for subshell electroionization distributions the
 * max energy nudge value should be greater than the binding energy since the
 * cross section goes to zero when the incoming energy is equal to the outgoing
 * energy minus the binding energy.
 */
template<typename TwoDInterpPolicy>
void AdjointElectronGridGenerator<TwoDInterpPolicy>::setMaxEnergyNudgeValue(
                                          const double max_energy_nudge_value )
{
  // Make sure the max energy nudge value is valid
  testPrecondition( max_energy_nudge_value > 0.0 );
  
  d_nudged_max_energy = d_max_energy + max_energy_nudge_value;
}

// Get the nudged max energy
template<typename TwoDInterpPolicy>
double AdjointElectronGridGenerator<TwoDInterpPolicy>::getNudgedMaxEnergy() const
{
  return d_nudged_max_energy;
}

// Set the incoming energy to max outgoing energy nudge value
/*! The incoming energy plus the energy to outgoing energy nudge value will be used 
 * as the lower limit for the outgoing energy grid. Setting a value of 0.0 means
 * that every outgoing energy grid will start at the corresponding energy. This
 * can be problematic for log interpolation since the adjoint electron cross
 * section is zero when the incoming energy is equal to the outgoing energy
 * (for inelastic reactions).
 * By pushing the first outgoing energy slightly above the
 * corresponding incoming energy with this value, that problem can be avoided
 * (usually leading to smaller grids that converge faster). Note: when
 * generating grids for subshell electroionization distributions the energy to
 * max energy nudge value should be greater than or equal to the binding energy
 * since the cross section goes to zero when the energy is equal to the max
 * energy minus the binding energy.
 */
template<typename TwoDInterpPolicy>
void AdjointElectronGridGenerator<TwoDInterpPolicy>::setEnergyToOutgoingEnergyNudgeValue(
                                const double  energy_to_outgoing_energy_nudge_value )
{
  // Make sure the energy to outgoing energy nudge value is valid
  testPrecondition(  energy_to_outgoing_energy_nudge_value >= 0.0 );
  
  d_energy_to_outgoing_energy_nudge_value =  energy_to_outgoing_energy_nudge_value;
}

// Get the nudged energy
template<typename TwoDInterpPolicy>
double AdjointElectronGridGenerator<TwoDInterpPolicy>::getNudgedEnergy(
                                                    const double energy ) const
{
  return energy + d_energy_to_outgoing_energy_nudge_value;
}

// Set the critcal energies for the primary grid
template<typename TwoDInterpPolicy>
void AdjointElectronGridGenerator<TwoDInterpPolicy>::setCriticalEnergies(
  const std::vector<double> critical_energies )
{
  // Make sure the critical energies are valid
  testPrecondition( critical_energies.size() > 0 );

  d_critical_energies = critical_energies;
}
  
// Get the critcal energies for the primary grid
template<typename TwoDInterpPolicy>
std::vector<double> AdjointElectronGridGenerator<TwoDInterpPolicy>::getCriticalEnergies() const
{
  return d_critical_energies;
}

// Create a differential cross section evaluator
/*! The std::function returned from this method can be used with the
 * generate methods to generate the two-dimensional grid.
 */
template<typename TwoDInterpPolicy>
template<typename ElectroatomicReaction>
std::function<double (double,double)>
AdjointElectronGridGenerator<TwoDInterpPolicy>::createCrossSectionEvaluator(
    const std::shared_ptr<const DataGen::AdjointElectronCrossSectionEvaluator<ElectroatomicReaction> >& adjoint_diff_cross_section,
    const double cross_section_evaluation_tol )
{
  // Make sure the differential cross section is valid
  testPrecondition( adjoint_diff_cross_section.get() );

  typedef DataGen::AdjointElectronCrossSectionEvaluator<ElectroatomicReaction> DistType;

  // The evaluateIntegratedCrossSection method that we want to bind to is
  // overloaded. We have to disambiguate it for the bind to work.
  return std::bind<double>( (double(DistType::*)(double,double,double) const)&DistType::evaluateAdjointPDF,
                            std::cref( *adjoint_diff_cross_section ),
                            std::placeholders::_1,
                            std::placeholders::_2,
                            cross_section_evaluation_tol );
}


// Add critical energies to energy grid
template<typename TwoDInterpPolicy>
void AdjointElectronGridGenerator<TwoDInterpPolicy>::addCriticalValuesToPrimaryGrid(
                                        std::deque<double>& energy_grid ) const
{
  // Make sure the primary grid is sorted
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
                                                      energy_grid.end(),
                                                      true ) );

  // Add the max energy
  if( energy_grid.back() < d_max_energy )
    energy_grid.push_back( d_max_energy );
  
  // Calculate the critical energy
  std::vector<double>::const_iterator critical_energy =
    this->getCriticalEnergies().begin();

  for ( critical_energy; critical_energy != this->getCriticalEnergies().end(); ++critical_energy )
  {
    // Insert the critical energy into the grid
    if( *critical_energy > energy_grid.front() )
    {
      std::deque<double>::iterator critical_position =
        std::lower_bound( energy_grid.begin(),
                          energy_grid.end(),
                          *critical_energy );

      // If this is not true then the critical energy is already present
      if( *critical_position > *critical_energy )
        energy_grid.insert( critical_position, *critical_energy );
    }
  }
}

// Initialize the max energy grid at an energy grid point
template<typename TwoDInterpPolicy>
void AdjointElectronGridGenerator<TwoDInterpPolicy>::initializeSecondaryGrid(
                                          std::vector<double>& outgoing_energy_grid,
                                          const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( energy <= d_max_energy );

  outgoing_energy_grid.resize( 2 );

  outgoing_energy_grid[0] = this->getNudgedEnergy( energy );
  outgoing_energy_grid[1] = this->getNudgedMaxEnergy();
}

} // end DataGen namespace

#endif // end DATA_GEN_ADJOINT_ELECTRON_GRID_GENERATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end DataGen_AdjointElectronGridGenerator_def.hpp
//---------------------------------------------------------------------------//
