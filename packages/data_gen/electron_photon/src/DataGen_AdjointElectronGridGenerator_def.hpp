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
#include "Utility_GaussKronrodIntegrator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_DesignByContract.hpp"

namespace DataGen{

// Constructor
/*! \details The Adjoint Electron Grid Generator should only be used for adjoint
 * bremsstrahlung and electroionization subshell reactions and requires
 * functions for evaluating the forward cross section and pdf as well as a
 * function to evaluate the minimum outgoing adjoint energy given an incoming
 * adjoint energy. The forward cross section evaluator function should take the
 * forward incoming energy. The forward pdf evaluator function should take the
 * forward incoming energy and the forward outgoing electron energy. The minimum
 * outgoing adjoint energy evaluator function should take the adjoint incoming
 * energy. The primary energy grid should be the incoming energy grid for the
 * 2-D distributions. The max energy will be used to test the input incoming
 * energy grid (if values in the input grid that are greater than the max energy
 * are found an exception will be thrown). The min_energy_gain_function
 * functor minus the min energy nudge value will be used to determine the
 * lowering limits of integration when evaluating the adjoint cross section as
 * well as set the minumum nudged outgoing energy for secondary distributions.
 * The max energy nudge value must be greater than zero to avoid an invalid
 * outgoing energy grid at the max incoming energy (each outgoing energy grid
 * must have at least two distinct points).
 */
template<typename TwoDInterpPolicy>
AdjointElectronGridGenerator<TwoDInterpPolicy>::AdjointElectronGridGenerator(
      const std::function<double(const double&)>& forward_cs_evaluator,
      const std::function<double(const double&, const double&)>& forward_pdf_evaluator,
      const std::function<double(const double&)>& min_energy_gain_function,
      const std::vector<double>& primary_energy_grid,
      const double min_energy,
      const double max_energy,
      const double min_energy_nudge_value,
      const double max_energy_nudge_value,
      const double convergence_tol,
      const double absolute_diff_tol,
      const double distance_tol,
      const bool electron_scatter_above_max_energy_mode )
  : Utility::TwoDGridGenerator<TwoDInterpPolicy>( convergence_tol,
                                                  absolute_diff_tol,
                                                  distance_tol ),
    d_forward_cs_evaluator( forward_cs_evaluator ),
    d_forward_pdf_evaluator( forward_pdf_evaluator ),
    d_min_energy_gain_function( min_energy_gain_function ),
    d_primary_energy_grid( primary_energy_grid ),
    d_min_incoming_energy( min_energy ),
    d_max_incoming_energy( 0.0 ),
    d_min_outgoing_energy( min_energy + d_min_energy_gain_function(min_energy) + min_energy_nudge_value ),
    d_max_outgoing_energy( 0.0 ),
    d_min_energy_nudge_value( min_energy_nudge_value ),
    d_max_energy_nudge_value( min_energy_nudge_value ),
    d_electron_scatter_above_max_energy_mode(electron_scatter_above_max_energy_mode)
{
  // // Make sure the forward evaluators are valid
  testPrecondition( forward_cs_evaluator );
  testPrecondition( forward_pdf_evaluator );

  // Make sure the primary_energy_grid is valid
  testPrecondition( primary_energy_grid.size() > 0 );
  testPrecondition( Utility::Sort::isSortedAscending(
                                                primary_energy_grid.begin(),
                                                primary_energy_grid.end() ) );

  // Make sure the min, max energies are valid
  testPrecondition( min_energy > 0.0 );
  testPrecondition( max_energy <= 1e5 );
  testPrecondition( min_energy < max_energy );
  // Make sure the min, max energy nudge value is valid
  testPrecondition( min_energy_nudge_value > 0.0 );
  testPrecondition( max_energy_nudge_value > 0.0 );

  // Set the max energy
  if( electron_scatter_above_max_energy_mode )
  {
    d_max_incoming_energy = max_energy;
    d_max_outgoing_energy = max_energy + d_min_energy_gain_function(max_energy) + max_energy_nudge_value;
  }
  else
  {
    d_max_incoming_energy = max_energy - d_min_energy_gain_function(max_energy) - max_energy_nudge_value;
    d_max_outgoing_energy = max_energy;
  }

  testPostcondition( d_max_outgoing_energy <= 1e5 );

  std::vector<double>::iterator start, end;

  if ( d_min_outgoing_energy <= d_primary_energy_grid.front() )
  {
    start = d_primary_energy_grid.begin();
  }
  else
  {
    // Find the location of the first grid point that is > the min_outgoing_energy
    start = std::upper_bound( d_primary_energy_grid.begin(),
                              d_primary_energy_grid.end(),
                              d_min_outgoing_energy );

    // iterate back to the first grid point <= the min_outgoing_energy
    --start;
  }

  // Find the location of the first grid point that is >= the max outgoing energy
  end = std::lower_bound( start,
                          d_primary_energy_grid.end(),
                          d_max_outgoing_energy );

  // iterate forward one to the first grid point that is >= the max outgoing energy is assigned
  ++end;

  d_integration_points.assign( start, end );

  // Replace the lower and upper bins with the min and max electron energies
  d_integration_points.front() = d_min_outgoing_energy;
  d_integration_points.back() = d_max_outgoing_energy;
}

// Get the min incoming energy
template<typename TwoDInterpPolicy>
double AdjointElectronGridGenerator<TwoDInterpPolicy>::getMinIncomingEnergy() const
{
  return d_min_incoming_energy;
}

// Get the max incoming energy
template<typename TwoDInterpPolicy>
double AdjointElectronGridGenerator<TwoDInterpPolicy>::getMaxIncomingEnergy() const
{
  return d_max_incoming_energy;
}

// Get the min outgoing energy
template<typename TwoDInterpPolicy>
double AdjointElectronGridGenerator<TwoDInterpPolicy>::getMinOutgoingEnergy() const
{
  return d_min_outgoing_energy;
}

// Get the max outgoing energy
template<typename TwoDInterpPolicy>
double AdjointElectronGridGenerator<TwoDInterpPolicy>::getMaxOutgoingEnergy() const
{
  return d_max_outgoing_energy;
}

// Get the nudged energy
template<typename TwoDInterpPolicy>
double AdjointElectronGridGenerator<TwoDInterpPolicy>::getNudgedMinEnergy(
                                                    const double energy ) const
{
  // Calculate the min energy
  double min_energy = energy + d_min_energy_gain_function(energy);

  // Refine the min energy
  double refined_min_energy = min_energy;
  // double min_pdf = d_forward_pdf_evaluator( refined_min_energy, energy );

  // while ( min_pdf > 0.0 && refined_min_energy > energy )
  // {
  //   min_energy = refined_min_energy;
  //   refined_min_energy *= 0.99999;

  //   if( refined_min_energy <= energy )
  //   {
  //     refined_min_energy = energy;
  //     min_pdf = 0.0;
  //     break;
  //   }

  //   min_pdf = d_forward_pdf_evaluator( refined_min_energy, energy );
  // }

  // while ( min_pdf <= 0.0 )
  // {
  //   refined_min_energy *= 1.00001;

  //   min_pdf = d_forward_pdf_evaluator( refined_min_energy, energy );
  // }

  // testPostcondition( d_forward_pdf_evaluator( refined_min_energy, energy ) > 0.0 );

  // if( refined_min_energy > min_energy )
  //   refined_min_energy = min_energy;

  return refined_min_energy + d_min_energy_nudge_value;
}

// Evaluate the adjoint PDF
template<typename TwoDInterpPolicy>
double AdjointElectronGridGenerator<TwoDInterpPolicy>::evaluateAdjointPDF(
        const double incoming_adjoint_energy,
        const double outgoing_adjoint_energy,
        const double precision ) const
{
  testPrecondition( outgoing_adjoint_energy > incoming_adjoint_energy );

  if( outgoing_adjoint_energy > this->getMaxOutgoingEnergy() ||
      incoming_adjoint_energy > this->getMaxIncomingEnergy() )
  {
    return 0.0;
  }

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
template<typename TwoDInterpPolicy>
double AdjointElectronGridGenerator<TwoDInterpPolicy>::evaluateAdjointPDF(
        const double adjoint_cross_section,
        const double incoming_adjoint_energy,
        const double outgoing_adjoint_energy,
        const double ) const
{
  double forward_differential_cs =
    this->evaluateAdjointDifferentialCrossSection(
        incoming_adjoint_energy,
        outgoing_adjoint_energy );

  if ( forward_differential_cs > 0.0 && adjoint_cross_section > 0.0 )
    return forward_differential_cs/adjoint_cross_section;
  else
    return 0.0;
}

// Return the differential cross section value at a given energy
template<typename TwoDInterpPolicy>
double AdjointElectronGridGenerator<TwoDInterpPolicy>::evaluateAdjointDifferentialCrossSection(
      const double adjoint_incoming_energy,
      const double adjoint_outgoing_energy ) const
{
  // Get the forward cross section at the adjoint outgoing energy
  double forward_cs = d_forward_cs_evaluator( adjoint_outgoing_energy );

  // Get the forward PDF
  double forward_pdf = d_forward_pdf_evaluator( adjoint_outgoing_energy,
                                                adjoint_incoming_energy );

  return forward_cs*forward_pdf;
}

// Return the adjoint cross section value at a given energy
/*/! \details The adjoint cross section is evaluating by integrating the adjoint
 *   differential cross section from the min outgoing adjoint energy to the
 *   nudged max adjoint energy. If the nudged max adjoint energy is not larger
 *   than the min outgoing adjoint energy a cross section of zero will be
 *   returned.
 */
template<typename TwoDInterpPolicy>
double AdjointElectronGridGenerator<TwoDInterpPolicy>::evaluateAdjointCrossSection(
    const double incoming_adjoint_energy,
    const double precision ) const
{
  // Make sure the energies are valid
  testPrecondition( incoming_adjoint_energy >= this->getMinIncomingEnergy() );

  long double cross_section = 0.0;

  // The start energy for integrating
  double start_energy = this->getNudgedMinEnergy( incoming_adjoint_energy );

  // If the start_energy > d_max_energy return 0.0
  if ( start_energy > this->getMaxOutgoingEnergy() )
  {
    return 0.0;
  }

  // Create rapper function for the adjoint electroatomic differential cross section
  std::function<double (double y)> diff_adjoint_cs_wrapper =
    [this, &incoming_adjoint_energy](double y){return this->evaluateAdjointDifferentialCrossSection(incoming_adjoint_energy, y);};

  long double cross_section_k, abs_error;

  Utility::GaussKronrodIntegrator<long double>
    integrator( precision, 0.0, 5000 );

  // Turn of error and warning messages
  integrator.dontEstimateRoundoff();

  // Find the integration point above the start_energy
  unsigned start_index =
    Utility::Search::binaryUpperBoundIndex(
              d_integration_points.begin(),
              d_integration_points.end(),
              start_energy );

  // Integrate from the start_energy to the next highest energy bin (if necessary)
  if( d_integration_points[start_index] != start_energy && start_index > 0)
  {
    cross_section_k = 0.0;
    abs_error = 0.0;

    integrator.integrateAdaptively<51>(
        diff_adjoint_cs_wrapper,
        (long double)start_energy,
        (long double)d_integration_points[start_index],
        cross_section_k,
        abs_error );

    cross_section += cross_section_k;
    abs_error += abs_error;
  }

  ++start_index;

  // Integrate through the energy bins above the given energy and below the max energy
  for ( start_index; start_index < d_integration_points.size(); ++start_index )
  {
    cross_section_k = 0.0;
    abs_error = 0.0;

    integrator.integrateAdaptively<51>(
        diff_adjoint_cs_wrapper,
        (long double)d_integration_points[start_index-1],
        (long double)d_integration_points[start_index],
        cross_section_k,
        abs_error );

    cross_section += cross_section_k;
    abs_error += abs_error;
  }

  return (double) cross_section;
}

// Create a differential cross section evaluator
/*! The std::function returned from this method can be used with a grid
 * generator to generate the primary energy grid.
 */
template<typename TwoDInterpPolicy>
std::function<double (double)>
AdjointElectronGridGenerator<TwoDInterpPolicy>::createAdjointCrossSectionFunction(
    const double cross_section_evaluation_tol ) const
{
  // Make sure the cross_section_evaluation_tol is valid
  testPrecondition( cross_section_evaluation_tol > 0.0 );

  typedef DataGen::AdjointElectronGridGenerator<TwoDInterpPolicy> DistType;

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
template<typename TwoDInterpPolicy>
void AdjointElectronGridGenerator<TwoDInterpPolicy>::generateAndEvaluateDistribution(
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

  typedef DataGen::AdjointElectronGridGenerator<TwoDInterpPolicy> DistType;

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
/*! \details If the nudged min energy of a primary energy is greater than or
 *  equal to the max energy then it is assumed the distribution is zero and it
 *  is not included in the distribution.
 */
template<typename TwoDInterpPolicy>
void AdjointElectronGridGenerator<TwoDInterpPolicy>::generateAndEvaluateDistributionOnPrimaryEnergyGrid(
    std::map<double,std::vector<double> >& outgoing_energy_grid,
    std::map<double,std::vector<double> >& evaluated_pdf,
    const double evaluation_tol,
    const std::vector<double>& primary_energy_grid,
    const std::vector<double>& adjoint_cross_sections,
    const unsigned threshold_index ) const
{
  testPrecondition( primary_energy_grid.size() > 0 );
  testPrecondition( evaluation_tol > 0.0 );
  testPrecondition( threshold_index >= 0 );
  testPrecondition( adjoint_cross_sections.size() + threshold_index == primary_energy_grid.size() );

  for( unsigned i = 0; i < adjoint_cross_sections.size(); ++i )
  {
    double incoming_energy = primary_energy_grid[i + threshold_index];

    if( this->getNudgedMinEnergy( incoming_energy ) < this->getMaxOutgoingEnergy() )
    {
      this->generateAndEvaluateDistribution(
              outgoing_energy_grid[incoming_energy],
              evaluated_pdf[incoming_energy],
              evaluation_tol,
              incoming_energy,
              adjoint_cross_sections[i] );
    }
  }
}

// Initialize the secondary energy grid at an energy grid point
/*! \details The getNudgedMinEnergy as the lower bound of the
 * secondary grid is used to ensure a non-zero pdf value at the lower bound.
 */
template<typename TwoDInterpPolicy>
void AdjointElectronGridGenerator<TwoDInterpPolicy>::initializeSecondaryGrid(
                                          std::vector<double>& outgoing_energy_grid,
                                          const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( energy <= this->getMaxIncomingEnergy() );

  outgoing_energy_grid.resize( 2 );

  outgoing_energy_grid[0] = this->getNudgedMinEnergy( energy );
  outgoing_energy_grid[1] = this->getMaxOutgoingEnergy();

  testPostcondition( outgoing_energy_grid[0] < outgoing_energy_grid[1] )
}

} // end DataGen namespace

#endif // end DATA_GEN_ADJOINT_ELECTRON_GRID_GENERATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end DataGen_AdjointElectronGridGenerator_def.hpp
//---------------------------------------------------------------------------//
