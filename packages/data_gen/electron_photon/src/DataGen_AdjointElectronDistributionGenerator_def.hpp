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
/*! \details The max incoming energy (max energy) will be used to test the input
 * incoming energy grid (if values in the input grid that are greater than the
 * max incoming energy are found an exception will be thrown). The max incoming
 * energy plus the max energy nudge value will be used as the upper limit for
 * the outgoing energy grid. The max energy nudge value must be greater than 0.0
 * to avoid an invalid outgoing energy grid at the max incoming energy (each
 * outgoing energy grid must have at least two distinct points). The incoming
 * energy plus the energy to outgoing energy nudge value will be used as the
 * lower limit for the outgoing energy grid. Setting a value of 0.0 means that
 * every outgoing energy grid will start at the corresponding energy. This can
 * be problematic for log interpolation since the adjoint electron cross section
 * is zero when the incoming energy is equal to the outgoing energy (for
 * inelastic reactions).
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
    d_ energy_to_outgoing_energy_nudge_value(  energy_to_outgoing_energy_nudge_value )
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
  
  d_ energy_to_outgoing_energy_nudge_value =  energy_to_outgoing_energy_nudge_value;
}

// Get the nudged energy
template<typename TwoDInterpPolicy>
double AdjointElectronDistributionGenerator<TwoDInterpPolicy>::getNudgedEnergy(
                                                    const double energy ) const
{
  return energy + d_energy_to_outgoing_energy_nudge_value;
}

// Create an cross section evaluator
/*! The std::function returned from this method can be used with the
 * generateAndEvaluateSecondaryInPlace methods to generate the
 * pdf-outgoing energy distributions on the adjoint electron union energy grid.
 */
template<typename TwoDInterpPolicy>
template< typename ElectroatomicReaction >
std::function<double (double,double)>
AdjointElectronDistributionGenerator<TwoDInterpPolicy>::createAdjointPDFEvaluator(
     const std::shared_ptr<const DataGen::AdjointElectronCrossSectionEvaluator<ElectroatomicReaction> >& adjoint_evaluator,
     const double cross_section_evaluation_tol )
{
  // Make sure the adjoint evaluator is valid
  testPrecondition( adjoint_evaluator.get() );

  typedef DataGen::AdjointElectronCrossSectionEvaluator<ElectroatomicReaction> > DistType;

  // The evaluateIntegratedCrossSection method that we want to bind to is
  // overloaded. We have to disambiguate it for the bind to work.
  return std::bind<double>( double(DistType::*)(double,double,double,double) const)&DistType::evaluateAdjointPDF,
                            std::cref( *adjoint_evaluator ),
                            std::placeholders::_1,
                            std::placeholders::_2,
                            std::placeholders::_3,
                            cross_section_evaluation_tol );
}

// Initialize the outgoing energy grid at an incoming energy grid point
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

  // Make sure the outgoing energy grid is valid
  testPostcondition( outgoing_energy_grid.size() >= 2 );
}

} // end DataGen namespace

#endif // end DATA_GEN_ADJOINT_ELECTRON_DISTRIBUTION_GENERATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end DataGen_AdjointElectronDistributionGenerator_def.hpp
//---------------------------------------------------------------------------//
