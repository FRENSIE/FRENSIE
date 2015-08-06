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
    d_elastic_distribution( elastic_distribution ),
    d_cutoff_angle_cosine( cutoff_angle_cosine )
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

// Evaluate the Legnendre Polynomial expansion of the screened rutherford pdf
double ElasticElectronMomentsEvaluator::evaluateLegendreExpandedRutherford(
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
            d_elastic_distribution->evaluateScreenedRutherfordPDF( incoming_energy,
                                                 scattering_angle_cosine );

  // Evaluate the Legendre Polynomial at the given angle and order
  double legendre_value =  Utility::getLegendrePolynomial(
                                                  scattering_angle_cosine,
                                                  polynomial_order );
                   
  return pdf_value*legendre_value;
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

// Evaluate the Legnendre Polynomial expansion of the elastic scttering PDF
double ElasticElectronMomentsEvaluator::evaluateLegendreExpandedPDFAtEnergyBin(
                                    const double scattering_angle_cosine,
                                    const unsigned incoming_energy_bin, 
                                    const int polynomial_order ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( incoming_energy_bin >= 0 );
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  // Evaluate the elastic pdf value at a given energy and scattering angle cosine
  double pdf_value = 
            d_elastic_distribution->evaluatePDF( incoming_energy_bin,
                                                 scattering_angle_cosine );

  // Evaluate the Legendre Polynomial at the given angle and order
  double legendre_value =  Utility::getLegendrePolynomial(
                                                  scattering_angle_cosine,
                                                  polynomial_order );
      
  return pdf_value*legendre_value;
}

// Evaluate the first n moments of the elastic scattering distribution at a given energy
void ElasticElectronMomentsEvaluator::evaluateElasticMoment( 
            Teuchos::Array<Utility::long_float>& legendre_moments,
            const double energy, 
            const int n,
            const double precision ) const
{
  // Make sure the energy and order is valid
  testPrecondition( energy > 0.0 );
  testPrecondition( n >= 0 );

  // Get common angular grid
  Teuchos::Array<double> common_angular_grid;

  MonteCarlo::HardElasticElectronScatteringDistributionACEFactory::createCommonAngularGrid(
                                        d_raw_ace_data,
                                        common_angular_grid,
                                        d_cutoff_angle_cosine );

  // remove grid point at 1.0 (outside tabular range)
  common_angular_grid.pop_back();

  // resize array to the number of legendre moments wanted
  legendre_moments.resize(n+1);

  Utility::GaussKronrodQuadratureKernel quadrature_kernel( precision );

  // Calucuate the tabular and Rutherford component of the Legendre moment
  Utility::long_float tabular_moment,rutherford_moment;

  for ( int i = 0; i <= n; i++ )
  {
    double abs_error, moment_k;
    // Calucuate the component of the moment from screened Rutherford peak
    evaluateNormalizedScreenedRutherfordMoment( rutherford_moment, energy, i );

    // Create boost rapper function for the hard elastic differential cross section
    boost::function<double (double x)> distribution_wrapper = 
      boost::bind<double>( &ElasticElectronMomentsEvaluator::evaluateLegendreExpandedPDF,
                         boost::cref( *this ),
                         _1,
                         energy,
                         i );

    Teuchos::Array<double>::iterator grid_point, grid_point_minus_one;
    grid_point_minus_one = common_angular_grid.begin();
    grid_point = ++common_angular_grid.begin();

    tabular_moment = Utility::long_float(0);
    for ( grid_point; grid_point != common_angular_grid.end(); grid_point++ )
    {
      moment_k = 0.0;
      abs_error = 0.0;
      quadrature_kernel.integrateAdaptively<61>(
					distribution_wrapper,
					*grid_point_minus_one,
					*grid_point,
					moment_k,
					abs_error );

      grid_point_minus_one = grid_point;

      tabular_moment += moment_k;
    }
    legendre_moments[i] = rutherford_moment + tabular_moment;
  }
}

// Evaluate the first n moments of the elastic scattering distribution at a given energy
void ElasticElectronMomentsEvaluator::evaluateElasticMoment( 
            Teuchos::Array<Utility::long_float>& legendre_moments,
            const unsigned energy_bin, 
            const int n,
            const double precision ) const
{
  // Make sure the energy and order is valid
  testPrecondition( energy_bin >= 0 );
  testPrecondition( n >= 0 );

  // Get common angular grid
  Teuchos::Array<double>::iterator grid_point, grid_point_minus_one;
  Teuchos::Array<double> angular_grid;

  angular_grid =
      MonteCarlo::HardElasticElectronScatteringDistributionACEFactory::getAngularGrid(
                d_raw_ace_data,
                energy_bin,
                d_cutoff_angle_cosine );

  // remove grid point at 1.0 (outside tabular range)
  angular_grid.pop_back();

  // Get the energy at the given angular energy bin
  double energy = d_elastic_distribution->getEnergy( energy_bin );

  // resize array to the number of legendre moments wanted
  legendre_moments.resize(n+1);

  Utility::GaussKronrodQuadratureKernel quadrature_kernel( precision );

  // Calucuate the tabular and Rutherford component of the Legendre moment
  Utility::long_float tabular_moment,rutherford_moment;

  for ( int i = 0; i <= n; i++ )
  {
    double abs_error, moment_k;
    // Calucuate the component of the moment from screened Rutherford peak
    evaluateNormalizedScreenedRutherfordMoment( rutherford_moment, energy, i );

    // Create boost rapper function for the hard elastic differential cross section
    boost::function<double (double x)> distribution_wrapper = 
      boost::bind<double>( &ElasticElectronMomentsEvaluator::evaluateLegendreExpandedPDFAtEnergyBin,
                         boost::cref( *this ),
                         _1,
                         energy_bin,
                         i );

    Teuchos::Array<double>::iterator grid_point, grid_point_minus_one;
    grid_point_minus_one = angular_grid.begin();
    grid_point = ++angular_grid.begin();

    tabular_moment = Utility::long_float(0);
    for ( grid_point; grid_point != angular_grid.end(); grid_point++ )
    {
      moment_k = 0.0;
      abs_error = 0.0;
      quadrature_kernel.integrateAdaptively<61>(
					distribution_wrapper,
					*grid_point_minus_one,
					*grid_point,
					moment_k,
					abs_error );

      grid_point_minus_one = grid_point;

      tabular_moment += moment_k;
    }
    legendre_moments[i] = rutherford_moment + tabular_moment;
  }
}

// Evaluate the nth normalized moment of the screened Rutherford peak distribution 
void ElasticElectronMomentsEvaluator::evaluateNormalizedScreenedRutherfordMoment( 
            Utility::long_float rutherford_moment,
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

  // Calcuate Moliere's modified screening constant (eta) 
  double eta = 
    d_elastic_distribution->evaluateMoliereScreeningConstant( energy );
    std::cout << std::setprecision(20) << "eta = \t" << eta << std::endl;

  /*!  \details If eta is small ( << 1 ) a recursion relationship can be used to 
   *! calculate the moments of the screened Rutherford peak. For larger eta the 
   *! moments will be calculated by numerical integration.
   */
  if ( eta <= 1.0e-2 )
  {
    rutherford_moment = d_elastic_distribution->
                          evaluateScreenedRutherfordCrossSectionRatio( energy );

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
          ( i - Utility::long_float(1) )/( i + Utility::long_float(2) )*
          coef_two[i-1];
      } 
      Utility::long_float frac_disc = 
          delta_cosine*( Utility::long_float(1) + eta/Utility::long_float(2) )/
        ( delta_cosine + eta );

      rutherford_moment -= eta*coef_one[n]/frac_disc;
    }
  }
  else // Numerically integrate the moment
  {
    Utility::GaussKronrodQuadratureKernel quadrature_kernel( 1e-13 );

    double abs_error, moment_n;

    // Create boost rapper function for the screened Rutherford peak
    boost::function<double (double x)> wrapper = 
      boost::bind<double>( &ElasticElectronMomentsEvaluator::evaluateLegendreExpandedRutherford,
                         boost::cref( *this ),
                         _1,
                         energy,
                         n );

    quadrature_kernel.integrateAdaptively<61>(
					wrapper,
					0.999999,
					1.0,
					moment_n,
					abs_error );

  rutherford_moment = moment_n;
  }
}

} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_ElasticElectronMomentsEvaluator.cpp
//---------------------------------------------------------------------------//
