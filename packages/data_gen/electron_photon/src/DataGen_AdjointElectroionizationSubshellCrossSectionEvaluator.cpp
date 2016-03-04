//---------------------------------------------------------------------------//
//!
//! \file   DataGen_AdjointElectroionizationSubshellCrossSectionEvaluator.cpp
//! \author Luke Kersting
//! \brief  Adjoint electroionization subshell cross section evaluator definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// FRENSIE Includes
#include "DataGen_AdjointElectroionizationSubshellCrossSectionEvaluator.hpp"
#include "Utility_GaussKronrodIntegrator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"
#include "MonteCarlo_TwoDDistributionHelpers.hpp"

namespace DataGen{

// Constructor
AdjointElectroionizationSubshellCrossSectionEvaluator::AdjointElectroionizationSubshellCrossSectionEvaluator(
    const double& binding_energy,
    const Teuchos::RCP<MonteCarlo::ElectroatomicReaction>& 
                                     electroionization_subshell_reaction,
    const Teuchos::RCP<const MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution>&
                                     knock_on_distribution )
  : d_binding_energy( binding_energy ),
    d_electroionization_subshell_reaction( electroionization_subshell_reaction ),
    d_knock_on_distribution( knock_on_distribution )
{
  // Make sure the data is valid
  testPrecondition( !d_electroionization_subshell_reaction.is_null() );
  testPrecondition( !d_knock_on_distribution.is_null() );
 // testPrecondition( d_knock_on_distribution.size() > 0 );
}

// Evaluate the differential adjoint electroionization subshell cross section (dc/dx)
double AdjointElectroionizationSubshellCrossSectionEvaluator::evaluateDifferentialCrossSection(
	  const double incoming_energy, 
          const double outgoing_energy ) const
{
  // Make sure the energies are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( outgoing_energy > 0.0 );

  // Evaluate the forward cross section at the incoming energy
  double forward_cs = d_electroionization_subshell_reaction->getCrossSection( 
                                                              incoming_energy );

  // Evaluate the knock on electron pdf value at a given incoming and outgoing energy
  double knock_on_pdf = d_knock_on_distribution->evaluatePDF( incoming_energy,
                                                              outgoing_energy );
                   
  /* Calculate the energy of a knock on electron from a primary electron with 
     outgoing energy = outgoing_energy */
  double knock_on_energy = incoming_energy - outgoing_energy - d_binding_energy; 

  // Evaluate the primary electron pdf value at a given incoming and outgoing energy
  double primary_pdf = d_knock_on_distribution->evaluatePDF( incoming_energy,
                                                             knock_on_energy );
 
/*                 
  // Evaluate the primary electron pdf value at a given incoming and outgoing energy
  double primary_pdf = MonteCarlo::evaluateTwoDDistributionCorrelatedPDF( 
                                     incoming_energy,
                                     knock_on_energy,
                                     d_knock_on_distribution );           
*/
  return forward_cs*( knock_on_pdf + primary_pdf );
}

// Return the cross section value at a given energy
double AdjointElectroionizationSubshellCrossSectionEvaluator::evaluateCrossSection( 
                               const double energy, 
			       const double precision ) const
{
  // Make sure the energies are valid
  testPrecondition( energy > 0.0 );

  double cross_section = 0.0;

  // Create boost rapper function for the adjoint electroionization subshell differential cross section
  boost::function<double (double x)> diff_adjoint_subshell_wrapper = 
    boost::bind<double>( &AdjointElectroionizationSubshellCrossSectionEvaluator::evaluateDifferentialCrossSection,
                         boost::cref( *this ),
                         _1,
                         energy );

    double abs_error;
    
    Utility::GaussKronrodIntegrator integrator( precision );

    integrator.integrateAdaptively<15>(
					diff_adjoint_subshell_wrapper,
					d_knock_on_distribution->getMinEnergy(),
					d_knock_on_distribution->getMaxEnergy(),
					cross_section,
					abs_error );
/*
    integrator.integrateAdaptively<15>(
					diff_adjoint_subshell_wrapper,
					d_knock_on_distribution.front().first,
					d_knock_on_distribution.back().first,
					cross_section,
					abs_error );
*/
}

// Return the max outgoing adjoint energy for a given energy
double AdjointElectroionizationSubshellCrossSectionEvaluator::getMaxOutgoingEnergyAtEnergy( 
                                const double energy )
{ 
  return d_knock_on_distribution->getMaxIncomingEnergyAtOutgoingEnergy( energy );
}


} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_AdjointElectroionizationSubshellCrossSectionEvaluator.cpp
//---------------------------------------------------------------------------//
