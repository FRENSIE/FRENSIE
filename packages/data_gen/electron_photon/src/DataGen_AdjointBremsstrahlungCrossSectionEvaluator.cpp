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
#include "Utility_GaussKronrodIntegrator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"

namespace DataGen{

// Constructor
AdjointBremsstrahlungCrossSectionEvaluator::AdjointBremsstrahlungCrossSectionEvaluator(
    const Teuchos::RCP<MonteCarlo::ElectroatomicReaction>& bremsstrahlung_reaction,
    const BremsstrahlungDistribution& energy_loss_distribution )
  : d_bremsstrahlung_reaction( bremsstrahlung_reaction ),
    d_energy_loss_distribution( energy_loss_distribution )
{
  // Make sure the data is valid
  testPrecondition( !d_bremsstrahlung_reaction.is_null() );
  testPrecondition( d_energy_loss_distribution.size() > 0 );
}

// Evaluate the differential adjoint bremsstrahlung cross section (dc/dx)
double AdjointBremsstrahlungCrossSectionEvaluator::evaluateDifferentialCrossSection(
	  const double incoming_energy,
          const double outgoing_energy ) const
{
  // Make sure the energies are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( outgoing_energy > 0.0 );

  // Evaluate the forward cross section at the incoming energy
  double forward_cs = d_bremsstrahlung_reaction->getCrossSection( incoming_energy );

  // Evaluate the energy loss distribution at a given incoming and outgoing energy
  double forward_pdf = MonteCarlo::evaluateTwoDDistributionCorrelatedPDF(
                                     incoming_energy,
                                     outgoing_energy,
                                     d_energy_loss_distribution );

  return forward_cs*forward_pdf;
}

// Return the cross section value at a given energy
double AdjointBremsstrahlungCrossSectionEvaluator::evaluateCrossSection(
                               const double energy,
			       const double precision ) const
{
  // Make sure the energies are valid
  testPrecondition( energy > 0.0 );

  double cross_section = 0.0;

  // Create boost rapper function for the adjoint Bremsstahlung differential cross section
  boost::function<double (double x)> diff_adjoint_brem_wrapper =
    boost::bind<double>( &AdjointBremsstrahlungCrossSectionEvaluator::evaluateDifferentialCrossSection,
                         boost::cref( *this ),
                         _1,
                         energy );

    double abs_error;

    Utility::GaussKronrodIntegrator<double> integrator( precision );

    integrator.integrateAdaptively<15>(
					diff_adjoint_brem_wrapper,
					d_energy_loss_distribution.front().first,
					d_energy_loss_distribution.back().first,
					cross_section,
					abs_error );
}

} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_AdjointBremsstrahlungCrossSectionEvaluator.cpp
//---------------------------------------------------------------------------//
