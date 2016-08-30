//---------------------------------------------------------------------------//
//!
//! \file   DataGen_AdjointElectronDistributionGenerator_def.cpp
//! \author Luke Kersting
//! \brief  Adjoint electron distribution generator definition
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_ADJOINT_ELECTRON_DISTRIBUTION_GENERATOR_DEF_HPP
#define DATA_GEN_ADJOINT_ELECTRON_DISTRIBUTION_GENERATOR_DEF_HPP

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
template<typename TwoDInterpPolicy>
AdjointElectronDistributionGenerator<TwoDInterpPolicy>::AdjointElectronDistributionGenerator(
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


// Advanced Constructor
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
AdjointElectronDistributionGenerator<TwoDInterpPolicy>::AdjointElectronDistributionGenerator(
          const std::vector<double>& primary_energy_grid,
          const double max_energy,
          const double max_energy_nudge_value,
          const double energy_to_outgoing_energy_nudge_value,
          const double convergence_tol,
          const double absolute_diff_tol,
          const double distance_tol )
  : Utility::TwoDGridGenerator<TwoDInterpPolicy>( convergence_tol,
                                                  absolute_diff_tol,
                                                  distance_tol ),
    d_primary_energy_grid( primary_energy_grid ),
    d_max_energy( max_energy ),
    d_nudged_max_energy( max_energy + max_energy_nudge_value ),
    d_energy_to_outgoing_energy_nudge_value(  energy_to_outgoing_energy_nudge_value )
{
  // Make sure the primary energy grid is valid
  testPrecondition( primary_energy_grid.size() > 1 );
  // Make sure the max energy is valid
  testPrecondition( max_energy > 0.0 );
  // Make sure the max energy nudge value is valid
  testPrecondition( max_energy_nudge_value > 0.0 );
  // Make sure the energy to outgoing energy nudge value is valid
  testPrecondition(  energy_to_outgoing_energy_nudge_value >= 0.0 );
}


// Get the primary energy grid
template<typename TwoDInterpPolicy>
double AdjointElectronDistributionGenerator<TwoDInterpPolicy>::getPrimaryEnergyGrid() const
{
  return d_primary_energy_grid;
}

// Set the primary energy grid
template<typename TwoDInterpPolicy>
void AdjointElectronDistributionGenerator<TwoDInterpPolicy>::setPrimaryEnergyGrid(
  const std::vector<double> primary_energy_grid )
{
  d_primary_energy_grid = primary_energy_grid;
}

// Get the max energy
template<typename TwoDInterpPolicy>
double AdjointElectronDistributionGenerator<TwoDInterpPolicy>::getMaxEnergy() const
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
void AdjointElectronDistributionGenerator<TwoDInterpPolicy>::setMaxEnergyNudgeValue(
                                          const double max_energy_nudge_value )
{
  // Make sure the max energy nudge value is valid
  testPrecondition( max_energy_nudge_value > 0.0 );
  
  d_nudged_max_energy = d_max_energy + max_energy_nudge_value;
}

// Get the nudged max energy
template<typename TwoDInterpPolicy>
double AdjointElectronDistributionGenerator<TwoDInterpPolicy>::getNudgedMaxEnergy() const
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
void AdjointElectronDistributionGenerator<TwoDInterpPolicy>::setEnergyToOutgoingEnergyNudgeValue(
                                const double  energy_to_outgoing_energy_nudge_value )
{
  // Make sure the energy to outgoing energy nudge value is valid
  testPrecondition(  energy_to_outgoing_energy_nudge_value >= 0.0 );
  
  d_energy_to_outgoing_energy_nudge_value =  energy_to_outgoing_energy_nudge_value;
}

// Get the nudged energy
template<typename TwoDInterpPolicy>
double AdjointElectronDistributionGenerator<TwoDInterpPolicy>::getNudgedEnergy(
                                                    const double energy ) const
{
  return energy + d_energy_to_outgoing_energy_nudge_value;
}

// Generate and evaluate the distribution grid in place
/*! \details The container must have a push_back method defined. The
 * function must have the following signature: double (double,double). 
 * The first function parameter must correspond to the primary value. It is
 * acceptable to pass an empty secondary grid (it will be initialized with the
 * initializeSecondaryGrid method).
 */
template<typename TwoDInterpPolicy>
template< typename ElectroatomicReaction >
void AdjointElectronDistributionGenerator<TwoDInterpPolicy>::generateAndEvaluateDistribution(
  std::vector<double>& outgoing_energy_grid,
  std::vector<double>& evaluated_pdf,
  const std::shared_ptr<const DataGen::AdjointElectronCrossSectionEvaluator<ElectroatomicReaction> >& adjoint_evaluator,
  const double evaluation_tol,
  const double incoming_adjoint_energy,
  const double adjoint_cross_section ) const
{ 
  // Initialize the outgoing energy grid
  std::vector<double> initial_outgoing_energy_grid;

  this->initializeSecondaryGrid( initial_outgoing_energy_grid,
                                 incoming_adjoint_energy );

  typedef DataGen::AdjointElectronCrossSectionEvaluator<ElectroatomicReaction> DistType;

  // Create a function for this secondary grid
  std::function<double (double)> secondary_grid_function =
    std::bind<double>( (double(DistType::*)(double,double,double,double) const)&DistType::evaluateAdjointPDF,
                            std::cref( *adjoint_evaluator ),
                            adjoint_cross_section,
                            incoming_adjoint_energy,
                            std::placeholders::_1,
                            evaluation_tol );

  Utility::TwoDGridGenerator<TwoDInterpPolicy>::d_secondary_grid_generator.generateAndEvaluate(
              outgoing_energy_grid,
              evaluated_pdf,
              initial_outgoing_energy_grid,
              secondary_grid_function );
}

// Generate and evaluate the distribution grid in place
template<typename TwoDInterpPolicy>
template< typename ElectroatomicReaction >
void AdjointElectronDistributionGenerator<TwoDInterpPolicy>::generateAndEvaluateDistributionOnPrimaryEnergyGrid(
    std::map<double,std::vector<double> >& outgoing_energy_grid,
    std::map<double,std::vector<double> >& evaluated_pdf,
    const std::shared_ptr<const DataGen::AdjointElectronCrossSectionEvaluator<ElectroatomicReaction> >& adjoint_evaluator,
    const double evaluation_tol,
    const std::vector<double> adjoint_cross_sections,
    const unsigned threshold_index ) const
{
  testPrecondition( d_primary_energy_grid.size() > 0 );
  testPrecondition( adjoint_evaluator.use_count() > 0 );
  testPrecondition( evaluation_tol > 0.0 );
  testPrecondition( threshold_index >= 0 );
  testPrecondition( adjoint_cross_sections.size() + threshold_index == d_primary_energy_grid.size() );

  for( unsigned i = 0; i < adjoint_cross_sections.size(); ++i )
  {
    double incoming_energy = d_primary_energy_grid[i + threshold_index];

    this->generateAndEvaluateDistribution(
            outgoing_energy_grid[incoming_energy],
            evaluated_pdf[incoming_energy],
            adjoint_evaluator,
            evaluation_tol,
            incoming_energy,
            adjoint_cross_sections[i] );
  }

}


// Generate and evaluate the distribution grid in place
/*! \details The container must have a push_back method defined. The
 * function must have the following signature: double (double,double). 
 * The first function parameter must correspond to the primary value. It is
 * acceptable to pass an empty secondary grid (it will be initialized with the
 * initializeSecondaryGrid method).
 *//*
template<typename TwoDInterpPolicy>
template< typename ElectroatomicReaction >
void AdjointElectronDistributionGenerator<TwoDInterpPolicy>::generateAndEvaluateDistributionInPlace(
  std::vector<double>& outgoing_energy_grid,
  std::vector<double>& evaluated_pdf,
  const std::shared_ptr<const DataGen::AdjointElectronCrossSectionEvaluator<ElectroatomicReaction> >& adjoint_evaluator, ) const
{
  // Initialize the secondary grid
  std::vector<double> initial_secondary_grid;
  
  this->initializeSecondaryGrid( outgoing_energy_grid, incoming_adjoint_energy );

  // Create a function for this secondary grid
  return std::bind<double>( double(DistType::*)(double,double,double,double) const)&DistType::evaluateAdjointPDF,
                            std::cref( *adjoint_evaluator ),
                            cross_section,
                            incoming_adjoint_energy,
                            std::placeholders::_1,
                            cross_section_evaluation_tol );

  // Create a function for this secondary grid
  std::function<double (double)> secondary_grid_function =
    std::bind<double>( function, incoming_adjoint_energy, std::placeholders::_1 );

  d_secondary_grid_generator.generateAndEvaluate( secondary_grid,
                                                  evaluated_function,
                                                  initial_secondary_grid,
                                                  secondary_grid_function );
}
*/

// Initialize the max energy grid at an energy grid point
template<typename TwoDInterpPolicy>
void AdjointElectronDistributionGenerator<TwoDInterpPolicy>::initializeSecondaryGrid(
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

#endif // end DATA_GEN_ADJOINT_ELECTRON_DISTRIBUTION_GENERATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end DataGen_AdjointElectronDistributionGenerator_def.hpp
//---------------------------------------------------------------------------//
