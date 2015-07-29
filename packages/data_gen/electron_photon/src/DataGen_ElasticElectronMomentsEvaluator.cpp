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

// Initialize static member data

// cutoff angle cosine for analytical peak
double ElasticElectronMomentsEvaluator::s_rutherford_cutoff = 0.999999;

// Difference btw cutoff angle cosine for analytical peak and foward peak (mu=1)
double ElasticElectronMomentsEvaluator::s_delta_rutherford = 1.0e-6;

// Constructor
ElasticElectronMomentsEvaluator::ElasticElectronMomentsEvaluator(
    const Data::XSSEPRDataExtractor& raw_ace_data,
    const Teuchos::RCP<const MonteCarlo::HardElasticElectronScatteringDistribution>&
                                     elastic_distribution,
    const double& cutoff_angle_cosine )
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

// Evaluate the Legnendre Polynomial expansion of the screened rutherford
double ElasticElectronMomentsEvaluator::evaluateLegendreExpandedScreenedRutherford(
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
            d_elastic_distribution->evaluateScreenedRutherfordPDF( 
                                                 incoming_energy,
                                                 scattering_angle_cosine );

  // Evaluate the Legendre Polynomial at the given angle and order
  double legendre_value =  Utility::getLegendrePolynomial(
                                                  scattering_angle_cosine,
                                                  polynomial_order );

  return pdf_value*legendre_value;
}

// Return the moment of the elastic scattering distribution at a given energy and polynomial order
double ElasticElectronMomentsEvaluator::evaluateElasticMoment( 
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

  double abs_error = 0.0, total_moment = 0.0, moment_i = 0.0;
    
  // Get common angular grid
  Teuchos::Array<double> common_angular_grid;

  MonteCarlo::HardElasticElectronScatteringDistributionACEFactory::createCommonAngularGrid(
                                        d_raw_ace_data,
                                        common_angular_grid,
                                        d_cutoff_angle_cosine );

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

  return total_moment;
}

// Evaluate the first n normalized moments of the screened Rutherford distribution above the cutoff mu
void ElasticElectronMomentsEvaluator::evaluateNormalizedScreenedRutherfordMoments( 
            Teuchos::Array<Utility::long_float>& rutherford_moments,
            const double energy,
            const int n ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( energy > 0.0 );

  double angle_cosine, delta_cosine;

  if ( d_cutoff_angle_cosine <= s_rutherford_cutoff )
  { 
    angle_cosine = 
        s_rutherford_cutoff;
    delta_cosine = 
        s_delta_rutherford;
  }
  else
  {
    angle_cosine = d_cutoff_angle_cosine;
    delta_cosine = 1.0 - angle_cosine;
  }

  double eta = 
    d_elastic_distribution->evaluateMoliereScreeningConstant( energy );

  rutherford_moments[0] = Utility::long_float(1);
        //evaluateScreenedRutherfordCrossSectionRatio( energy );

  if ( n > 0 )
  {
    Teuchos::Array<Utility::long_float> coef_one( n+1 ), coef_two( n+1 );

    coef_one[0] = Utility::long_float(0);
    coef_one[1] = ( log( ( eta + delta_cosine )/( eta ) ) ) -
                   delta_cosine/( delta_cosine + eta );

    coef_two[0] = delta_cosine;
    coef_two[1] = ( Utility::long_float(1) - angle_cosine*angle_cosine )/
                    Utility::long_float(2);

    for ( int i = 1; i < n; i++ )
    {
      coef_one[i+1] = 
        ( Utility::long_float(2) + Utility::long_float(1)/i )*
        ( Utility::long_float(1) + eta )*coef_one[i] - 
        ( Utility::long_float(1) + Utility::long_float(1)/i )*coef_one[i-1] -
        ( ( 2.0L + Utility::long_float(1)/i )/( delta_cosine + eta ) )*
        ( delta_cosine - coef_two[i]);

      coef_two[i+1] = 
        ( Utility::long_float(2)*i + Utility::long_float(1) )/
        ( i + Utility::long_float(2) )*angle_cosine*coef_two[i] - 
        ( i - Utility::long_float(1) )*( i + Utility::long_float(2) )*
        coef_two[i-1];
    } 
    Utility::long_float frac_disc = 
        delta_cosine*( Utility::long_float(1) + eta/Utility::long_float(2) )/
        ( delta_cosine + eta );

    for ( int i = 1; i <= n; i++ )
    {
      rutherford_moments[i] = 
        ( Utility::long_float(1) - 
        eta*( Utility::long_float(1) + eta/Utility::long_float(2) )*
        coef_one[i]/frac_disc );
    }
  }
}

} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_ElasticElectronMomentsEvaluator.cpp
//---------------------------------------------------------------------------//
