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
#include "MonteCarlo_HardElasticElectronScatteringDistributionACEFactory.hpp"
//#include "MonteCarlo_ElectroatomicReactionACEFactory.hpp"

namespace DataGen{

// Constructor
ElasticElectronMomentsEvaluator::ElasticElectronMomentsEvaluator(
    const Data::XSSEPRDataExtractor& raw_ace_data,
    const Teuchos::RCP<const MonteCarlo::HardElasticElectronScatteringDistribution>&
                                     elastic_distribution )
  : d_raw_ace_data ( raw_ace_data ),
    d_elastic_distribution( elastic_distribution )
{
  // Make sure the data is valid
  testPrecondition( !d_elastic_distribution.is_null() );
/*
  // Extract the common energy grid used for this atom
  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.deepCopy( raw_electroatom_data.extractElectronEnergyGrid() );

  MonteCarlo::ElectroatomicReactionACEFactory::createHardElasticReaction(
					   raw_electroatom_data,
					   energy_grid,
					   d_elastic_reaction );

  d_elastic_reaction->getCrossSection( incoming_energy );
*/

}

// Evaluate the Legnendre Polynomial expansion of the elastic scttering PDF
double ElasticElectronMomentsEvaluator::evaluateLegendreExpandedPDF(
                                    const double scattering_angle_cosine,
                                    const double incoming_energy, 
                                    const int polynomial_order ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  // Evaluate the elastic pdf value at a given energy and scattering angle cosine
  double pdf_value = 
            d_elastic_distribution->evaluatePDF( incoming_energy,
                                                 scattering_angle_cosine );

  // Evaluate the Legendre Polynomial at the given angle and order
  double legendre_value =  Utility::getLegendrePolynomial(
                                                  scattering_angle_cosine,
                                                  polynomial_order );
                   
  return pdf_value*legendre_value;
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
  boost::function<double (double x)> distribution_wrapper = 
    boost::bind<double>( &ElasticElectronMomentsEvaluator::evaluateLegendreExpandedPDF,
                         boost::cref( *this ),
                         _1,
                         energy,
                         polynomial_order );

  double abs_error, total_moment, moment_i;
    
  // Get common angular grid
  Teuchos::Array<double> common_angular_grid;

  MonteCarlo::HardElasticElectronScatteringDistributionACEFactory::createCommonAngularGrid(
                                        d_raw_ace_data,
                                        common_angular_grid );

  Utility::GaussKronrodQuadratureKernel quadrature_kernel( precision );

  for ( unsigned i = 1; i < common_angular_grid.size()-1; i++ )
  {
    quadrature_kernel.integrateAdaptively<15>(
					distribution_wrapper,
					common_angular_grid[i-1],
					common_angular_grid[i],
					moment_i,
					abs_error );
  
    total_moment += moment_i;
  }

  return 2.0*Utility::PhysicalConstants::pi*( total_moment );
}

} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_ElasticElectronMomentsEvaluator.cpp
//---------------------------------------------------------------------------//
