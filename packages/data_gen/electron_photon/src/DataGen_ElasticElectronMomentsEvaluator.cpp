//---------------------------------------------------------------------------//
//!
//! \file   DataGen_ElasticElectronMomentsEvaluator.cpp
//! \author Luke Kersting
//! \brief  Elastic electron cross section moments evaluator definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// FRENSIE Includes
#include "DataGen_ElasticElectronMomentsEvaluator.hpp"
#include "Utility_GaussKronrodQuadratureKernel.hpp"
#include "Utility_LegendrePolynomial.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"
#include "MonteCarlo_TwoDDistributionHelpers.hpp"

namespace DataGen{

// Constructor
ElasticElectronMomentsEvaluator::ElasticElectronMomentsEvaluator(
    const Teuchos::RCP<MonteCarlo::ElectroatomicReaction>& 
                                     elastic_reaction,
    const Teuchos::RCP<const MonteCarlo::HardElasticElectronScatteringDistribution>&
                                     elastic_distribution )
  : d_elastic_reaction( elastic_reaction ),
    d_elastic_distribution( elastic_distribution )
{
  // Make sure the data is valid
  testPrecondition( !d_elastic_reaction.is_null() );
  testPrecondition( !d_elastic_distribution.is_null() );
}

// Evaluate the differential hard elastic cross section (dc/dx)
double ElasticElectronMomentsEvaluator::evaluateDifferentialCrossSection(
                                    const double scattering_angle_cosine,
                                    const double incoming_energy ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  // Evaluate the forward cross section at the incoming energy
  double cross_section = d_elastic_reaction->getCrossSection( incoming_energy );

  // Evaluate the elastic pdf value at a given energy and scattering angle cosine
  double pdf_value = 
            d_elastic_distribution->evaluatePDF( incoming_energy,
                                                 scattering_angle_cosine );
                   
  return cross_section*pdf_value;
}

// Evaluate the Legnendre Polynomial expansion of the differential hard elastic cross section (dc/dx)
double ElasticElectronMomentsEvaluator::evaluateLegendreExpandedDifferentialCrossSection(
                                    const double scattering_angle_cosine,
                                    const double incoming_energy, 
                                    const int polynomial_order ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  // Evaluate the forward cross section at the incoming energy
  double cross_section = d_elastic_reaction->getCrossSection( incoming_energy );

  // Evaluate the elastic pdf value at a given energy and scattering angle cosine
  double pdf_value = 
            d_elastic_distribution->evaluatePDF( incoming_energy,
                                                 scattering_angle_cosine );

  // Evaluate the Legendre Polynomial at the given angle and order
  double legendre_value =  Utility::getLegendrePolynomial(
                                                  scattering_angle_cosine,
                                                  polynomial_order );
                   
  return cross_section*pdf_value*legendre_value;
}

// Return the cross section moment at a given energy and polynomial order
double ElasticElectronMomentsEvaluator::evaluateCrossSectionMoment( 
                               const double energy, 
                               const int polynomial_order,
                               const double precision ) const
{
  // Make sure the energy and order is valid
  testPrecondition( energy > 0.0 );
  testPrecondition( polynomial_order >= 0 );

  // Create boost rapper function for the hard elastic differential cross section
  boost::function<double (double x)> function_wrapper = 
    boost::bind<double>( &ElasticElectronMomentsEvaluator::evaluateDifferentialCrossSection,
                         boost::cref( *this ),
                         _1,
                         energy );

  double abs_error, distribution_moment, screened_rutherford_moment;
    
  Utility::GaussKronrodQuadratureKernel quadrature_kernel( precision );

  quadrature_kernel.integrateAdaptively<15>(
					function_wrapper,
					-1.0,
					0.999999,
					distribution_moment,
					abs_error );

  quadrature_kernel.integrateAdaptively<15>(
					function_wrapper,
					0.999999,
					1.0,
					screened_rutherford_moment,
					abs_error );

  return 2.0*Utility::PhysicalConstants::pi*(distribution_moment+screened_rutherford_moment);
}

} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_ElasticElectronMomentsEvaluator.cpp
//---------------------------------------------------------------------------//
