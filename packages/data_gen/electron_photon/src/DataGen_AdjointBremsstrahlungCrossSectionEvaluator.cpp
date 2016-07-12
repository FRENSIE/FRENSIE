//---------------------------------------------------------------------------//
//!
//! \file   DataGen_AdjointBremsstrahlungCrossSectionEvaluator.cpp
//! \author Luke Kersting
//! \brief  Adjoint bremsstrahlung cross section evaluator definition
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// FRENSIE Includes
#include "DataGen_AdjointBremsstrahlungCrossSectionEvaluator.hpp"
#include "MonteCarlo_StandardElectroatomicReaction.hpp"
#include "Utility_GaussKronrodIntegrator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"

namespace DataGen{

// Constructor
AdjointBremsstrahlungCrossSectionEvaluator::AdjointBremsstrahlungCrossSectionEvaluator(
    const std::shared_ptr<MonteCarlo::BremsstrahlungElectroatomicReaction<Utility::LinLin> >&
        bremsstrahlung_reaction,
    const std::vector<double>& integration_points )
  : d_bremsstrahlung_reaction( bremsstrahlung_reaction ),
    d_integration_points( integration_points )
{
  // Make sure the reaction is valid
  testPrecondition( bremsstrahlung_reaction.use_count() > 0 );

  // Make sure the integration points are valid
  testPrecondition( integration_points.size() > 0 );
  testPrecondition( Utility::Sort::isSortedAscending(
						integration_points.begin(),
						integration_points.end() ) );
}

// Evaluate the adjoint PDF
double AdjointBremsstrahlungCrossSectionEvaluator::evaluateAdjointPDF(
        const double incoming_adjoint_energy,
        const double outgoing_adjoint_energy,
        const double precision ) const
{

  double adjoint_cross_section =
    this->evaluateAdjointCrossSection( incoming_adjoint_energy, precision );

  return this->evaluateAdjointPDF(
                    adjoint_cross_section,
                    incoming_adjoint_energy,
                    outgoing_adjoint_energy,
                    precision );
}

// Evaluate the adjoint differential bremsstrahlung cross section
double AdjointBremsstrahlungCrossSectionEvaluator::evaluateAdjointPDF(
        const double adjoint_cross_section,
        const double incoming_adjoint_energy,
        const double outgoing_adjoint_energy,
        const double precision ) const
{
  double forward_differential_cs =
    d_bremsstrahlung_reaction->getDifferentialCrossSection(
        outgoing_adjoint_energy,
        incoming_adjoint_energy );

  if ( forward_differential_cs > 0.0 )
    return forward_differential_cs/adjoint_cross_section;
  else
    return 0.0;
}

// Return the adjoint cross section value at a given energy
double AdjointBremsstrahlungCrossSectionEvaluator::evaluateAdjointCrossSection(
    const double incoming_adjoint_energy,
    const double precision ) const
{
  // Make sure the energies are valid
  testPrecondition( incoming_adjoint_energy > 0.0 );

  Utility::long_float cross_section = Utility::long_float(0);

  double const& ( MonteCarlo::BremsstrahlungElectroatomicReaction<Utility::LinLin>::*getDifferentialCrossSection ) () =
&MonteCarlo::BremsstrahlungElectroatomicReaction<Utility::LinLin>::getDifferentialCrossSection;

  // Create boost rapper function for the adjoint Bremsstahlung differential cross section
  boost::function<double (double x)> diff_adjoint_brem_wrapper =
    boost::bind( const& (MonteCarlo::BremsstrahlungElectroatomicReaction<Utility::LinLin>::getDifferentialCrossSection ),

                         boost::cref( d_bremsstrahlung_reaction ),
                         _1,
                         incoming_adjoint_energy );

  Utility::long_float cross_section_k, abs_error;

  Utility::GaussKronrodIntegrator<Utility::long_float>
    integrator( precision, 0.0, 1000, true );

  // Find the integration point above the given incoming_adjoint_energy
  unsigned start_index =
    Utility::Search::binaryUpperBoundIndex(
              d_integration_points.begin(),
              d_integration_points.end(),
              incoming_adjoint_energy );

  // Integrate from the given energy to the next highest energy bin (if necessary)
  if( d_integration_points[start_index] != incoming_adjoint_energy )
  {
    cross_section_k = Utility::long_float(0);
    abs_error = Utility::long_float(0);

    integrator.integrateAdaptively<15>(
        diff_adjoint_brem_wrapper,
        (Utility::long_float)incoming_adjoint_energy,
        (Utility::long_float)d_integration_points[start_index],
        cross_section_k,
        abs_error );

    cross_section += cross_section_k;
  }

  ++start_index;

  // Integrate through the energy bins above the given energy and below the max energy
  for ( start_index; start_index < d_integration_points.size(); start_index++ )
  {
    cross_section_k = Utility::long_float(0);
    abs_error = Utility::long_float(0);
    integrator.integrateAdaptively<15>(
        diff_adjoint_brem_wrapper,
        (Utility::long_float)d_integration_points[start_index-1],
        (Utility::long_float)d_integration_points[start_index],
        cross_section_k,
        abs_error );

    cross_section += cross_section_k;
  }

  return (double) cross_section;
}

} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_AdjointBremsstrahlungCrossSectionEvaluator.cpp
//---------------------------------------------------------------------------//
