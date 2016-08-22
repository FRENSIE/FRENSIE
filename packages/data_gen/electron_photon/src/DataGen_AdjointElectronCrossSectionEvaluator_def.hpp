//---------------------------------------------------------------------------//
//!
//! \file   DataGen_AdjointElectronCrossSectionEvaluator_def.hpp
//! \author Luke Kersting
//! \brief  Adjoint electron cross section evaluator definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTRON_CROSS_SECTION_EVALUATOR_DEF_HPP
#define MONTE_CARLO_ELECTRON_CROSS_SECTION_EVALUATOR_DEF_HPP

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// FRENSIE Includes
#include "Utility_GaussKronrodIntegrator.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_SearchAlgorithms.hpp"

namespace DataGen{

// Constructor
template<typename ElectroatomicReaction>
AdjointElectronCrossSectionEvaluator<ElectroatomicReaction>::AdjointElectronCrossSectionEvaluator(
    const std::shared_ptr<ElectroatomicReaction>&
        electroatomic_reaction,
    const std::vector<double>& integration_points )
  : d_electroatomic_reaction( electroatomic_reaction ),
    d_integration_points( integration_points )
{
  // Make sure the reaction is valid
  testPrecondition( electroatomic_reaction.use_count() > 0 );

  // Make sure the integration points are valid
  testPrecondition( integration_points.size() > 0 );
  testPrecondition( Utility::Sort::isSortedAscending(
						integration_points.begin(),
						integration_points.end() ) );
}


// Evaluate the adjoint PDF
template<typename ElectroatomicReaction>
double AdjointElectronCrossSectionEvaluator<ElectroatomicReaction>::evaluateAdjointPDF(
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
template<typename ElectroatomicReaction>
double AdjointElectronCrossSectionEvaluator<ElectroatomicReaction>::evaluateAdjointPDF(
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
template<typename ElectroatomicReaction>
double AdjointElectronCrossSectionEvaluator<ElectroatomicReaction>::evaluateAdjointCrossSection(
    const double incoming_adjoint_energy,
    const double precision ) const
{
  // Make sure the energies are valid
  testPrecondition( incoming_adjoint_energy > 0.0 );

  long double cross_section = 0.0L;

  // Create boost rapper function for the adjoint electroatomic differential cross section
  boost::function<double (double y)> diff_adjoint_cs_wrapper =
    boost::bind( &ConstElectroatomicReaction::getDifferentialCrossSection,
                         boost::cref( *d_electroatomic_reaction ),
                         _1,
                         incoming_adjoint_energy );

  long double cross_section_k, abs_error;

  Utility::GaussKronrodIntegrator<long double>
    integrator( precision, 0.0, 1000 );

  // Turn of error and warning messages
  integrator.dontEstimateRoundoff();

  // Find the integration point above the given incoming_adjoint_energy
  unsigned start_index =
    Utility::Search::binaryUpperBoundIndex(
              d_integration_points.begin(),
              d_integration_points.end(),
              incoming_adjoint_energy );

  // Integrate from the given energy to the next highest energy bin (if necessary)
  if( d_integration_points[start_index] != incoming_adjoint_energy && start_index > 0)
  {
    cross_section_k = 0.0L;
    abs_error = 0.0L;

    integrator.integrateAdaptively<51>(
        diff_adjoint_cs_wrapper,
        (long double)incoming_adjoint_energy,
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

// Return the adjoint cross section value at a given energy
template<typename ElectroatomicReaction>
template <typename BoostIntegrator>
double AdjointElectronCrossSectionEvaluator<ElectroatomicReaction>::evaluateAdjointCrossSectionUsingBoost(
    const double incoming_adjoint_energy,
    const BoostIntegrator integrator ) const
{
  // Make sure the energies are valid
  testPrecondition( incoming_adjoint_energy > 0.0 );

  state_type cross_section(1);

  // Create boost rapper function for the adjoint electroatomic differential cross section
  boost::function<void (state_type& x, state_type& dxdt, double t )> diff_adjoint_cs_wrapper =
    boost::bind( &AdjointElectronCrossSectionEvaluator<ElectroatomicReaction>::getDifferentialCrossSection,
                         boost::cref( *this ),
                         _1,
                         _2,
                         _3,
                         incoming_adjoint_energy );

  state_type answer(1);

  // Find the integration point above the given incoming_adjoint_energy
  unsigned start_index =
    Utility::Search::binaryUpperBoundIndex(
              d_integration_points.begin(),
              d_integration_points.end(),
              incoming_adjoint_energy );

  // Make sure the start index is for the energy right above the incoming adjoint energy
  if( d_integration_points[start_index] == incoming_adjoint_energy )
  {
    ++start_index;
  }

  // set the first numerical integration step to 1/10 the integration distance
  double dx = 0.1*( d_integration_points[start_index] - incoming_adjoint_energy );

  
  if ( dx <= 0.0 )
  {
    return 0.0;
  }

  // threshold nudge factor
  double nudge_factor = 1e-7;

  // Make sure the nudge factor is less than the integration distance
  if( 10.0*dx < nudge_factor );
  {
    nudge_factor = dx;
  }

  // Energy slightly above the incoming adjoint energy to avoid a zero energy secondary particle
  double min_integration_energy = incoming_adjoint_energy + nudge_factor;

  // integrate from the min_integration_energy to the next highest energy bin
  boost::numeric::odeint::integrate_adaptive(
      integrator, diff_adjoint_cs_wrapper, cross_section, min_integration_energy, d_integration_points[start_index], dx );//, AdjointElectronCrossSectionEvaluator<ElectroatomicReaction>::observer );

  // Update the start index
  ++start_index;

  // Integrate through the energy bins above the given energy to the max energy
  for ( start_index; start_index < d_integration_points.size(); start_index++ )
  {
    // set the first numerical integration step to 1/10 the integration distance
    double dx = 0.1*(d_integration_points[start_index] - d_integration_points[start_index-1] );

    // Integrate    
    boost::numeric::odeint::integrate_adaptive(
      integrator, diff_adjoint_cs_wrapper, cross_section, d_integration_points[start_index-1], d_integration_points[start_index], dx );//, AdjointElectronCrossSectionEvaluator<ElectroatomicReaction>::observer );

  }

  return (double) cross_section[0];
}

// Return the differential cross section at a given energy
template<typename ElectroatomicReaction>
void AdjointElectronCrossSectionEvaluator<ElectroatomicReaction>::getDifferentialCrossSection(
        const state_type& initial_value,
        state_type& differential_cross_section,
        const double outgoing_adjoint_energy,
        const double incoming_adjoint_energy ) const
{
  differential_cross_section[0] =
    d_electroatomic_reaction->getDifferentialCrossSection( outgoing_adjoint_energy, incoming_adjoint_energy );
}

// Observer, prints time and state when called (during integration)
template<typename ElectroatomicReaction>
void AdjointElectronCrossSectionEvaluator<ElectroatomicReaction>::observer(
    const state_type& x,
    const double t )
{
  std::cout << std::setprecision(20) << t << "   " << x[0] << std::endl;
}


} // end DataGen namespace

#endif // end MONTE_CARLO_ELECTRON_CROSS_SECTION_EVALUATOR_DEF_HPP

//---------------------------------------------------------------------------//
// end DataGen_AdjointElectronCrossSectionEvaluator.cpp
//---------------------------------------------------------------------------//
