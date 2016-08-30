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
template<typename ElectroatomicReaction, typename TwoDInterpPolicy>
AdjointElectronGridGenerator<ElectroatomicReaction,TwoDInterpPolicy>::AdjointElectronGridGenerator(
      const std::shared_ptr<const ElectroatomicReaction>& electroatomic_reaction,
      const std::vector<double>& primary_energy_grid,
      const double min_energy,
      const double max_energy,
      const double max_energy_nudge_value,
      const double energy_to_outgoing_energy_nudge_value,
      const double convergence_tol,
      const double absolute_diff_tol,
      const double distance_tol )
  : Utility::TwoDGridGenerator<TwoDInterpPolicy>( convergence_tol,
                                                  absolute_diff_tol,
                                                  distance_tol ),
    d_electroatomic_reaction( electroatomic_reaction ),
    d_primary_energy_grid( primary_energy_grid ),
    d_min_energy( min_energy ),
    d_max_energy( max_energy ),
    d_nudged_max_energy( max_energy + max_energy_nudge_value ),
    d_energy_to_outgoing_energy_nudge_value(  energy_to_outgoing_energy_nudge_value )
{
  // Make sure the reaction is valid
  testPrecondition( electroatomic_reaction.use_count() > 0 );

  // Make sure the primary_energy_grid is valid
  testPrecondition( primary_energy_grid.size() > 0 );
  testPrecondition( Utility::Sort::isSortedAscending(
						primary_energy_grid.begin(),
						primary_energy_grid.end() ) );

  // Make sure the min, max energies are valid
  testPrecondition( min_energy > 0.0 );
  testPrecondition( min_energy < max_energy );
  // Make sure the max energy nudge value is valid
  testPrecondition( max_energy_nudge_value > 0.0 );
  testPrecondition( max_energy + max_energy_nudge_value <= 1e5 );
  // Make sure the energy to outgoing energy nudge value is valid
  testPrecondition( energy_to_outgoing_energy_nudge_value >= 0.0 );
  testPrecondition( energy_to_outgoing_energy_nudge_value <=
                    max_energy_nudge_value );

  std::vector<double>::iterator start, end;

  if ( d_min_energy <= d_primary_energy_grid.front() )
  {
    start = d_primary_energy_grid.begin();
  }
  else
  {
    // Find the location of the first grid point that is > the min energy
    start = std::upper_bound( d_primary_energy_grid.begin(),
                              d_primary_energy_grid.end(),
                              d_min_energy );

    // iterate back to the first grid point <= the min energy
    --start;
  }

  // Find the location of the first grid point that is >= the max energy
  end = std::lower_bound( start,
                          d_primary_energy_grid.end(),
                          d_max_energy );

  // iterate forward one so the first grid point that is >= the max energy is assigned
  ++end;

  d_integration_points.assign( start, end );

  // Replace the lower and upper bins with the min and max electron energies
  d_integration_points.front() = d_min_energy;
  d_integration_points.back() = d_max_energy;

  // If neccessary add the nudged max energy to the end of the energy grid
  if ( d_nudged_max_energy != d_max_energy )
    d_integration_points.push_back( d_nudged_max_energy );
}

// Get the min energy
template<typename ElectroatomicReaction, typename TwoDInterpPolicy>
double AdjointElectronGridGenerator<ElectroatomicReaction,TwoDInterpPolicy>::getMinEnergy() const
{
  return d_min_energy;
}

// Get the max energy
template<typename ElectroatomicReaction, typename TwoDInterpPolicy>
double AdjointElectronGridGenerator<ElectroatomicReaction,TwoDInterpPolicy>::getMaxEnergy() const
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
template<typename ElectroatomicReaction, typename TwoDInterpPolicy>
void AdjointElectronGridGenerator<ElectroatomicReaction,TwoDInterpPolicy>::setMaxEnergyNudgeValue(
                                          const double max_energy_nudge_value )
{
  // Make sure the max energy nudge value is valid
  testPrecondition( max_energy_nudge_value > 0.0 );
  
  d_nudged_max_energy = d_max_energy + max_energy_nudge_value;
}

// Get the nudged max energy
template<typename ElectroatomicReaction, typename TwoDInterpPolicy>
double AdjointElectronGridGenerator<ElectroatomicReaction,TwoDInterpPolicy>::getNudgedMaxEnergy() const
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
template<typename ElectroatomicReaction, typename TwoDInterpPolicy>
void AdjointElectronGridGenerator<ElectroatomicReaction,TwoDInterpPolicy>::setEnergyToOutgoingEnergyNudgeValue(
                                const double  energy_to_outgoing_energy_nudge_value )
{
  // Make sure the energy to outgoing energy nudge value is valid
  testPrecondition(  energy_to_outgoing_energy_nudge_value >= 0.0 );
  
  d_energy_to_outgoing_energy_nudge_value =  energy_to_outgoing_energy_nudge_value;
}

// Get the nudged energy
template<typename ElectroatomicReaction, typename TwoDInterpPolicy>
double AdjointElectronGridGenerator<ElectroatomicReaction,TwoDInterpPolicy>::getNudgedEnergy(
                                                    const double energy ) const
{
  return energy + d_energy_to_outgoing_energy_nudge_value;
}

// Evaluate the adjoint PDF
template<typename ElectroatomicReaction, typename TwoDInterpPolicy>
double AdjointElectronGridGenerator<ElectroatomicReaction,TwoDInterpPolicy>::evaluateAdjointPDF(
        const double incoming_adjoint_energy,
        const double outgoing_adjoint_energy,
        const double precision ) const
{

  double adjoint_cross_section =
    this->evaluateAdjointCrossSection(
        incoming_adjoint_energy, precision );

  return this->evaluateAdjointPDF(
                    adjoint_cross_section,
                    incoming_adjoint_energy,
                    outgoing_adjoint_energy,
                    precision );
}

// Evaluate the adjoint PDF
template<typename ElectroatomicReaction, typename TwoDInterpPolicy>
double AdjointElectronGridGenerator<ElectroatomicReaction,TwoDInterpPolicy>::evaluateAdjointPDF(
        const double adjoint_cross_section,
        const double incoming_adjoint_energy,
        const double outgoing_adjoint_energy,
        const double precision ) const
{
  double forward_differential_cs =
    d_electroatomic_reaction->getDifferentialCrossSection(
        outgoing_adjoint_energy,
        incoming_adjoint_energy );

  if ( forward_differential_cs > 0.0 )
    return forward_differential_cs/adjoint_cross_section;
  else
    return 0.0;
}

// Return the adjoint cross section value at a given energy
template<typename ElectroatomicReaction, typename TwoDInterpPolicy>
double AdjointElectronGridGenerator<ElectroatomicReaction,TwoDInterpPolicy>::evaluateAdjointCrossSection(
    const double incoming_adjoint_energy,
    const double precision ) const
{
  // Make sure the energies are valid
  testPrecondition( incoming_adjoint_energy > 0.0 );

  long double cross_section = 0.0L;

  // The nudged incoming energy
  double nudged_start_energy = this->getNudgedEnergy( incoming_adjoint_energy );

  // If the nudge_incoming_energy >= d_nudged_max_energy return 0.0
  if ( nudged_start_energy >= d_nudged_max_energy )
  {
    return 0.0L;
  }

  // Create boost rapper function for the adjoint electroatomic differential cross section
  boost::function<double (double y)> diff_adjoint_cs_wrapper =
    boost::bind( &ConstElectroatomicReaction::getDifferentialCrossSection,
                         boost::cref( *d_electroatomic_reaction ),
                         _1,
                         incoming_adjoint_energy );

  long double cross_section_k, abs_error;

  Utility::GaussKronrodIntegrator<long double>
    integrator( precision, 0.0, 5000 );

  // Turn of error and warning messages
  integrator.dontEstimateRoundoff();

  // Find the integration point above the nudged incoming adjoint energy
  unsigned start_index =
    Utility::Search::binaryUpperBoundIndex(
              d_integration_points.begin(),
              d_integration_points.end(),
              nudged_start_energy );

  // Integrate from the nudged_start_energy to the next highest energy bin (if necessary)
  if( d_integration_points[start_index] != nudged_start_energy && start_index > 0)
  {
    cross_section_k = 0.0L;
    abs_error = 0.0L;

    integrator.integrateAdaptively<51>(
        diff_adjoint_cs_wrapper,
        (long double)nudged_start_energy,
        (long double)d_integration_points[start_index],
        cross_section_k,
        abs_error );

    cross_section += cross_section_k;
  }
  
  unsigned lower_bin_index = start_index;
  ++start_index;

  // Integrate through the energy bins above the given energy and below the max energy
  for ( start_index; start_index < d_integration_points.size(); start_index++ )
  {
    cross_section_k = 0.0L;
    abs_error = 0.0L;

    if ( d_integration_points[lower_bin_index] < d_integration_points[start_index-1] )
      ++lower_bin_index;

    integrator.integrateAdaptively<51>(
        diff_adjoint_cs_wrapper,
        (long double)d_integration_points[start_index-1],
        (long double)d_integration_points[start_index],
        cross_section_k,
        abs_error );

    cross_section += cross_section_k;
  }
  return (double) cross_section;
}

// Create a differential cross section evaluator
/*! The std::function returned from this method can be used with the
 * generate methods to generate the two-dimensional grid.
 */
template<typename ElectroatomicReaction, typename TwoDInterpPolicy>
std::function<double (double)>
AdjointElectronGridGenerator<ElectroatomicReaction,TwoDInterpPolicy>::createAdjointCrossSectionFunction(
    const double cross_section_evaluation_tol ) const
{
  // Make sure the cross_section_evaluation_tol is valid
  testPrecondition( cross_section_evaluation_tol > 0.0 );

  typedef DataGen::AdjointElectronGridGenerator<ElectroatomicReaction,TwoDInterpPolicy> DistType;

  // The evaluateAdjointCrossSection method that we want to bind to is
  // overloaded. We have to disambiguate it for the bind to work.
  return std::bind<double>( (double(DistType::*)(double,double) const)&DistType::evaluateAdjointCrossSection,
                            std::cref( *this ),
                            std::placeholders::_1,
                            cross_section_evaluation_tol );
}

// Generate and evaluate the distribution grid in place
/*! \details The container must have a push_back method defined. The
 * function must have the following signature: double (double,double). 
 * The first function parameter must correspond to the primary value. It is
 * acceptable to pass an empty secondary grid (it will be initialized with the
 * initializeSecondaryGrid method).
 */
template<typename ElectroatomicReaction, typename TwoDInterpPolicy>
void AdjointElectronGridGenerator<ElectroatomicReaction,TwoDInterpPolicy>::generateAndEvaluateDistribution(
  std::vector<double>& outgoing_energy_grid,
  std::vector<double>& evaluated_pdf,
  const double evaluation_tol,
  const double incoming_adjoint_energy,
  const double adjoint_cross_section ) const
{ 
  // Initialize the outgoing energy grid
  std::vector<double> initial_outgoing_energy_grid;

  this->initializeSecondaryGrid( initial_outgoing_energy_grid,
                                 incoming_adjoint_energy );

  typedef DataGen::AdjointElectronGridGenerator<ElectroatomicReaction,TwoDInterpPolicy> DistType;

  // Create a function for this secondary grid
  std::function<double (double)> secondary_grid_function =
    std::bind<double>( (double(DistType::*)(double,double,double,double) const)&DistType::evaluateAdjointPDF,
                            std::cref( *this ),
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
template<typename ElectroatomicReaction, typename TwoDInterpPolicy>
void AdjointElectronGridGenerator<ElectroatomicReaction,TwoDInterpPolicy>::generateAndEvaluateDistributionOnPrimaryEnergyGrid(
    std::map<double,std::vector<double> >& outgoing_energy_grid,
    std::map<double,std::vector<double> >& evaluated_pdf,
    const double evaluation_tol,
    const std::vector<double> primary_energy_grid,
    const std::vector<double> adjoint_cross_sections,
    const unsigned threshold_index ) const
{
  testPrecondition( primary_energy_grid.size() > 0 );
  testPrecondition( evaluation_tol > 0.0 );
  testPrecondition( threshold_index >= 0 );
  testPrecondition( adjoint_cross_sections.size() + threshold_index == primary_energy_grid.size() );

  for( unsigned i = 0; i < adjoint_cross_sections.size(); ++i )
  {
    double incoming_energy = primary_energy_grid[i + threshold_index];

    this->generateAndEvaluateDistribution(
            outgoing_energy_grid[incoming_energy],
            evaluated_pdf[incoming_energy],
            evaluation_tol,
            incoming_energy,
            adjoint_cross_sections[i] );
  }
}

// Initialize the max energy grid at an energy grid point
/*! \details The min energy on the secondary grid should be slightly higher than
 * the NudgedEnergy to ensure a non-zero pdf value at the min energy.
 */
template<typename ElectroatomicReaction, typename TwoDInterpPolicy>
void AdjointElectronGridGenerator<ElectroatomicReaction,TwoDInterpPolicy>::initializeSecondaryGrid(
                                          std::vector<double>& outgoing_energy_grid,
                                          const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( energy <= d_max_energy );

  outgoing_energy_grid.resize( 2 );

  
  outgoing_energy_grid[0] = this->getNudgedEnergy( energy ) + 1e-9;
  outgoing_energy_grid[1] = this->getNudgedMaxEnergy();
}

} // end DataGen namespace

#endif // end DATA_GEN_ADJOINT_ELECTRON_GRID_GENERATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end DataGen_AdjointElectronGridGenerator_def.hpp
//---------------------------------------------------------------------------//
