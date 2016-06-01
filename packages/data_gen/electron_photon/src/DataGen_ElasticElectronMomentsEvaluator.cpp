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
#include "Utility_GaussKronrodIntegrator.hpp"
#include "Utility_LegendrePolynomial.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"
#include "MonteCarlo_TwoDDistributionHelpers.hpp"
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_ElectroatomicReactionNativeFactory.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"

namespace DataGen{

// Initialize static member data

// cutoff angle for analytical peak
double ElasticElectronMomentsEvaluator::s_rutherford_cutoff_delta_angle_cosine = 1.0e-6;

// cutoff angle cosine for analytical peak
double ElasticElectronMomentsEvaluator::s_rutherford_cutoff_angle_cosine = 0.999999;

// Constructor
ElasticElectronMomentsEvaluator::ElasticElectronMomentsEvaluator(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double& cutoff_angle_cosine )
  : d_data_container ( data_container ),
    d_cutoff_angle_cosine( cutoff_angle_cosine )
{
  // Make sure the data is valid
  testPrecondition( cutoff_angle_cosine >= -1.0 );
  testPrecondition( cutoff_angle_cosine <= s_rutherford_cutoff_angle_cosine );

  // Extract the common energy grid used for this atom
  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.assign( data_container.getElectronEnergyGrid().begin(),
                      data_container.getElectronEnergyGrid().end() );

  // Create the hard elastic distributions ( both Cutoff and Screened Rutherford ) 
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createHardElasticDistributions(
    d_cutoff_distribution,
    d_rutherford_distribution,
    data_container,
    cutoff_angle_cosine );

  // Construct the hash-based grid searcher for this atom
  Teuchos::RCP<Utility::HashBasedGridSearcher> grid_searcher(
     new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>, false>(
						     energy_grid,
						     100u ) );

  MonteCarlo::ElectroatomicReactionNativeFactory::createScreenedRutherfordElasticReaction(
					   data_container,
					   energy_grid,
                       grid_searcher,
					   d_rutherford_reaction );

  MonteCarlo::ElectroatomicReactionNativeFactory::createCutoffElasticReaction(
					   data_container,
					   energy_grid,
                       grid_searcher,
					   d_cutoff_reaction );
}

// Evaluate the Legnendre Polynomial expansion of the screened rutherford pdf
double ElasticElectronMomentsEvaluator::evaluateLegendreExpandedRutherford(
                                    const double scattering_angle_cosine,
                                    const double incoming_energy, 
                                    const int polynomial_order ) const
{
  // Make sure the energy and angle cosine are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= s_rutherford_cutoff_angle_cosine );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  // Evaluate the elastic pdf value at a given energy and scattering angle cosine
  double pdf_value = 
            d_rutherford_distribution->evaluate( incoming_energy,
                                                  scattering_angle_cosine );

  // Evaluate the Legendre Polynomial at the given angle and order
  double legendre_value =  
    Utility::getLegendrePolynomial( scattering_angle_cosine, polynomial_order );
                   
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
  testPrecondition( scattering_angle_cosine <= s_rutherford_cutoff_angle_cosine );

  // Evaluate the elastic pdf value at a given energy and scattering angle cosine
  double pdf_value = 
            d_cutoff_distribution->evaluatePDF( incoming_energy,
                                             scattering_angle_cosine );

  // Evaluate the Legendre Polynomial at the given angle and order
  double legendre_value =  
    Utility::getLegendrePolynomial( scattering_angle_cosine, polynomial_order );
     
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
  testPrecondition( scattering_angle_cosine <= s_rutherford_cutoff_angle_cosine );

  // Evaluate the elastic pdf value at a given energy and scattering angle cosine
  double pdf_value = 
            d_cutoff_distribution->evaluatePDF( incoming_energy_bin,
                                             scattering_angle_cosine );

  // Evaluate the Legendre Polynomial at the given angle and order
  double legendre_value =  
    Utility::getLegendrePolynomial( scattering_angle_cosine, polynomial_order );
      
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
  Teuchos::Array<double> angular_grid;

  angular_grid =
    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGrid(
        d_data_container,
        energy,
        d_cutoff_angle_cosine );

  // resize array to the number of legendre moments wanted
  legendre_moments.resize(n+1);

  Utility::GaussKronrodIntegrator integrator( precision );

  // Calucuate the tabular and Rutherford component of the Legendre moment
  Utility::long_float tabular_moment,rutherford_moment;

  for ( int i = 0; i <= n; i++ )
  {
    double abs_error, moment_k;

    // Get the cutoff cross section
    double cutoff_cross_section = 
        d_cutoff_reaction->getCrossSection( energy ); 

    // Calucuate the component of the moment from screened Rutherford peak
    evaluateScreenedRutherfordMoment( rutherford_moment, energy, i );

    // Create boost rapper function for the hard elastic differential cross section
    boost::function<double (double x)> distribution_wrapper = 
      boost::bind<double>( &ElasticElectronMomentsEvaluator::evaluateLegendreExpandedPDF,
                         boost::cref( *this ),
                         _1,
                         energy,
                         i );

    Teuchos::Array<double>::iterator grid_point, grid_point_minus_one;
    grid_point_minus_one = angular_grid.begin();
    grid_point = ++angular_grid.begin();

    tabular_moment = Utility::long_float(0);
    for ( grid_point; grid_point != angular_grid.end(); grid_point++ )
    {
      moment_k = 0.0;
      abs_error = 0.0;
      integrator.integrateAdaptively<61>(
					distribution_wrapper,
					*grid_point_minus_one,
					*grid_point,
					moment_k,
					abs_error );

      grid_point_minus_one = grid_point;

      tabular_moment += moment_k;
    }
    legendre_moments[i] =
        rutherford_moment + tabular_moment*cutoff_cross_section;
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

  // Get the energy at the given angular energy bin
  double energy = d_cutoff_distribution->getEnergy( energy_bin );

  // Get angular grid
  Teuchos::Array<double> angular_grid;

  angular_grid =
    MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGrid(
        d_data_container,
        energy,
        d_cutoff_angle_cosine );

  // resize array to the number of legendre moments wanted
  legendre_moments.resize(n+1);

  Utility::GaussKronrodIntegrator integrator( precision );

  // Calucuate the tabular and Rutherford component of the Legendre moment
  Utility::long_float tabular_moment,rutherford_moment;

  for ( int i = 0; i <= n; i++ )
  {
    double abs_error, moment_k;

    // Get the cutoff cross section
    double cutoff_cross_section = 
        d_cutoff_reaction->getCrossSection( energy ); 

    // Calucuate the component of the moment from screened Rutherford peak
    evaluateScreenedRutherfordMoment( rutherford_moment, energy, i );

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
      integrator.integrateAdaptively<61>(
					distribution_wrapper,
					*grid_point_minus_one,
					*grid_point,
					moment_k,
					abs_error );

      grid_point_minus_one = grid_point;

      tabular_moment += moment_k;
    }
    legendre_moments[i] = 
        rutherford_moment + tabular_moment*cutoff_cross_section;
  }
}

// Evaluate the nth cross section moment of the screened Rutherford peak distribution 
void ElasticElectronMomentsEvaluator::evaluateScreenedRutherfordMoment( 
            Utility::long_float& rutherford_moment,
            const double energy,
            const int n ) const
{
  // Make sure the energy is valid
  testPrecondition( energy > 0.0 );

  Utility::long_float delta_mu;

  delta_mu = Utility::long_float(1)/1000000;

  // Calcuate Moliere's modified screening constant (eta) 
  Utility::long_float eta = Utility::long_float(
    d_rutherford_distribution->evaluateMoliereScreeningConstant( energy ) );

  /*!  \details If eta is small ( << 1 ) a recursion relationship can be used to 
   *! calculate the moments of the screened Rutherford peak. For larger eta the 
   *! moments will be calculated by numerical integration.
   */
  if ( eta <= 1.0e-2 )
  {
    rutherford_moment = d_rutherford_reaction->getCrossSection( energy );

    if ( n > 0 )
    {
      Teuchos::Array<Utility::long_float> coef_one( n+1 ), coef_two( n+1 );

      coef_one[0] = Utility::long_float(0);
      coef_one[1] = ( log( ( eta + delta_mu )/( eta ) ) ) -
                     delta_mu/( delta_mu + eta );

      coef_two[0] = delta_mu;
      coef_two[1] = ( Utility::long_float(2) - delta_mu )*delta_mu/
                      Utility::long_float(2);

      for ( int i = 1; i < n; i++ )
      {
        coef_one[i+1] = 
          ( Utility::long_float(2) + Utility::long_float(1)/i )*
          ( Utility::long_float(1) + eta )*coef_one[i] - 
          ( Utility::long_float(1) + Utility::long_float(1)/i )*coef_one[i-1] -
          ( ( Utility::long_float(2) + Utility::long_float(1)/i )/
          ( delta_mu + eta ) )*( delta_mu - coef_two[i] );

        coef_two[i+1] = 
          ( Utility::long_float(2)*i + Utility::long_float(1) )/
          ( i + Utility::long_float(2) )*( Utility::long_float(1) - delta_mu )*
          coef_two[i] - 
          ( i - Utility::long_float(1) )/( i + Utility::long_float(2) )*
          coef_two[i-1];
      } 
      Utility::long_float frac_disc = 
          delta_mu*( Utility::long_float(1) + eta/Utility::long_float(2) )/
        ( delta_mu + eta );

      rutherford_moment *= (1.0 - eta*coef_one[n]/frac_disc );
    }
  }
  else // Numerically integrate the moment
  {
    Utility::GaussKronrodIntegrator integrator( 1e-13 );

    Utility::long_float abs_error, moment_n;

    Utility::long_float cutoff_mu = Utility::long_float(999999)/1000000;

    Utility::long_float rutherford_cross_section = 
        Utility::long_float( d_rutherford_reaction->getCrossSection( energy ) ); 

    Utility::long_float moment_zero = 
        Utility::long_float( d_rutherford_distribution->evaluateIntegratedPDF( energy ) );
 
    if ( n == 0 )
    {
      moment_n = moment_zero;
    }
    else
    {
      // Create boost rapper function for the screened Rutherford peak
      boost::function<double (double x)> wrapper = 
        boost::bind<double>( &ElasticElectronMomentsEvaluator::evaluateLegendreExpandedRutherford,
                         boost::cref( *this ),
                         _1,
                         energy,
                         n );

      integrator.integrateAdaptively<61>(
					wrapper,
                    cutoff_mu,
					Utility::long_float(1),
					moment_n,
					abs_error );
    }
    rutherford_moment = moment_n/moment_zero*rutherford_cross_section;
  }
}

} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_ElasticElectronMomentsEvaluator.cpp
//---------------------------------------------------------------------------//
