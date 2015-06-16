//---------------------------------------------------------------------------//
//!
//! \file   DataGen_AdjointBremsstrahlungCrossSectionEvaluator.cpp
//! \author Luke Kersting
//! \brief  Adjoint bremsstrahlung cross section evaluator definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// FRENSIE Includes
#include "DataGen_AdjointBremsstrahlungCrossSectionEvaluator.hpp"
#include "Utility_GaussKronrodQuadratureKernel.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"
#include "MonteCarlo_TwoDDistributionHelper.hpp"

namespace DataGen{

// Constructor
AdjointBremsstrahlungCrossSectionEvaluator::AdjointBremsstrahlungCrossSectionEvaluator(
    const Teuchos::RCP<const Utility::OneDDistribution>& forward_cross_sections,
    const BremsstrahlungDistribution& energy_loss_function )
  : d_forward_cross_sections( forward_cross_sections ),
    d_energy_loss_function( energy_loss_function )
{
  // Make sure the data is valid
  testPrecondition( d_forward_cross_sections.size() > 0 );
  testPrecondition( d_energy_loss_function.size() > 0 );
}

// Evaluate the differential adjoint bremsstrahlung cross section (dc/dx)
double AdjointBremsstrahlungCrossSectionEvaluator::evaluateDifferentialCrossSection(
	  const double incoming_energy, 
          const double outgoing_energy ) const
{
  // Evaluate the forward cross section at the incoming energy
  double forward_cs = d_forward_cross_sections.evaluate( incoming_energy );

  // Evaluate the energy loss function at a given incoming and outgoing energy
  double forward_pdf = MonteCarlo::evaluateTwoDDistributionCorrelatedPDF( 
                                     incoming_energy,
                                     outgoing_energy,
                                     d_energy_loss_function );

  return forward_cs*forward_pdf;
}

// Return the cross section value at a given energy
double AdjointBremsstrahlungCrossSectionEvaluator::evaluateCrossSection( 
                               const double energy, 
			       const double precision ) const
{

}

} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_AdjointBremsstrahlungCrossSectionEvaluator.cpp
//---------------------------------------------------------------------------//
