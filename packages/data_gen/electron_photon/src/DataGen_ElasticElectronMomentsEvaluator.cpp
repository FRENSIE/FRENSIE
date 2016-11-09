//---------------------------------------------------------------------------//
//!
//! \file   DataGen_ElasticElectronMomentsEvaluator.cpp
//! \author Luke Kersting
//! \brief  Elastic electron cross section moments evaluator definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "DataGen_ElasticElectronMomentsEvaluator.hpp"
#include "Utility_LegendrePolynomial.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "MonteCarlo_ElasticElectronScatteringDistributionNativeFactory.hpp"
#include "MonteCarlo_ElectroatomicReactionNativeFactory.hpp"
#include "MonteCarlo_VoidElectroatomicReaction.hpp"

namespace DataGen{

// Initialize static member data

// cutoff angle for analytical peak
double ElasticElectronMomentsEvaluator::s_rutherford_cutoff_delta_angle_cosine = 1.0e-6;

// cutoff angle cosine for analytical peak
double ElasticElectronMomentsEvaluator::s_rutherford_cutoff_angle_cosine = 0.999999;

// Constructor
ElasticElectronMomentsEvaluator::ElasticElectronMomentsEvaluator(
    const Data::ElectronPhotonRelaxationDataContainer& data_container,
    const double cutoff_angle_cosine )
  : d_cutoff_elastic_angles( data_container.getCutoffElasticAngles() ),
    d_cutoff_angle_cosine( cutoff_angle_cosine )
{
  // Make sure the data is valid
  testPrecondition( cutoff_angle_cosine >= -1.0 );
  testPrecondition( cutoff_angle_cosine <= s_rutherford_cutoff_angle_cosine || cutoff_angle_cosine == 1.0 );

  // Extract the common energy grid used for this atom
  Teuchos::ArrayRCP<double> incoming_energy_grid;
  incoming_energy_grid.assign( data_container.getElectronEnergyGrid().begin(),
                               data_container.getElectronEnergyGrid().end() );

  // Create the analog elastic distribution (combined Cutoff and Screened Rutherford)
  MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::createAnalogElasticDistribution(
    d_analog_distribution,
    data_container );

  // Construct the hash-based grid searcher for this atom
  Teuchos::RCP<const Utility::HashBasedGridSearcher> grid_searcher(
     new Utility::StandardHashBasedGridSearcher<Teuchos::ArrayRCP<const double>, false>(
         incoming_energy_grid,
         100u ) );

  // Cutoff elastic cross section
  Teuchos::ArrayRCP<double> cutoff_cross_section;
  cutoff_cross_section.assign(
    data_container.getCutoffElasticCrossSection().begin(),
    data_container.getCutoffElasticCrossSection().end() );

  // Create the cutoff reaction
  d_cutoff_reaction.reset(
    new MonteCarlo::VoidElectroatomicReaction<Utility::LinLin, false>(
      incoming_energy_grid,
      cutoff_cross_section,
      data_container.getCutoffElasticCrossSectionThresholdEnergyIndex(),
      grid_searcher ) );

  // Screened Rutherford elastic cross section
  Teuchos::ArrayRCP<double> screened_rutherford_cross_section;
  screened_rutherford_cross_section.assign(
    data_container.getScreenedRutherfordElasticCrossSection().begin(),
    data_container.getScreenedRutherfordElasticCrossSection().end() );

  // Create the Screened Rutherford reaction
  d_screened_rutherford_reaction.reset(
    new MonteCarlo::VoidElectroatomicReaction<Utility::LinLin, false>(
      incoming_energy_grid,
      screened_rutherford_cross_section,
      data_container.getScreenedRutherfordElasticCrossSectionThresholdEnergyIndex(),
      grid_searcher ) );
}

// Constructor (without data container)
ElasticElectronMomentsEvaluator::ElasticElectronMomentsEvaluator(
    const std::map<double,std::vector<double> >& cutoff_elastic_angles,
    const Teuchos::ArrayRCP<double>& incoming_energy_grid,
    const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
    const Teuchos::ArrayRCP<double>& cutoff_cross_section,
    const Teuchos::ArrayRCP<double>& screened_rutherford_cross_section,
    const unsigned cutoff_threshold_energy_index,
    const unsigned screened_rutherford_threshold_energy_index,
    const std::shared_ptr<const MonteCarlo::AnalogElasticElectronScatteringDistribution>
        analog_distribution,
    const double cutoff_angle_cosine )
  : d_cutoff_elastic_angles( cutoff_elastic_angles ),
    d_analog_distribution( analog_distribution ),
    d_cutoff_angle_cosine( cutoff_angle_cosine )
{
  // Make sure the data is valid
  testPrecondition( cutoff_angle_cosine >= -1.0 );
  testPrecondition( cutoff_angle_cosine <= s_rutherford_cutoff_angle_cosine || cutoff_angle_cosine == 1.0 );

  // Make sure the arrays are valid
  testPrecondition( analog_distribution.use_count() > 0 );
  testPrecondition( !cutoff_elastic_angles.empty() );

  // Create the cutoff reaction
  d_cutoff_reaction.reset(
    new MonteCarlo::VoidElectroatomicReaction<Utility::LinLin, false>(
      incoming_energy_grid,
      cutoff_cross_section,
      cutoff_threshold_energy_index,
      grid_searcher ) );

  // Create the cutoff reaction
  d_screened_rutherford_reaction.reset(
    new MonteCarlo::VoidElectroatomicReaction<Utility::LinLin, false>(
      incoming_energy_grid,
      screened_rutherford_cross_section,
      screened_rutherford_threshold_energy_index,
      grid_searcher ) );
}

// Evaluate the Legnendre Polynomial expansion of the screened rutherford pdf
double ElasticElectronMomentsEvaluator::evaluateLegendreExpandedRutherford(
        const double scattering_angle_cosine,
        const double incoming_energy,
        const double eta,
        const int polynomial_order ) const
{
  // Make sure the energy and angle cosine are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= s_rutherford_cutoff_angle_cosine );
  testPrecondition( scattering_angle_cosine <= 1.0 );
  testPrecondition( eta > 0.0 );

  // Evaluate the elastic pdf value at a given energy and scattering angle cosine
  double pdf_value =
            d_analog_distribution->evaluateScreenedRutherfordPDF(
                    incoming_energy,
                    scattering_angle_cosine,
                    eta );

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
  testPrecondition( scattering_angle_cosine <= 1.0 );

  // Evaluate the elastic pdf value at a given energy and scattering angle cosine
  double pdf_value =
            d_analog_distribution->evaluatePDF( incoming_energy,
                                                scattering_angle_cosine );

  // Evaluate the Legendre Polynomial at the given angle and order
  double legendre_value =
    Utility::getLegendrePolynomial( scattering_angle_cosine, polynomial_order );

  return pdf_value*legendre_value;
}

// Evaluate the first n moments of the elastic scattering distribution at a given energy
void ElasticElectronMomentsEvaluator::evaluateElasticMoment(
            std::vector<Utility::long_float>& legendre_moments,
            const double energy,
            const int n,
            const double precision ) const
{
  // Make sure the energy, precision and order is valid
  testPrecondition( energy > 0.0 );
  testPrecondition( precision > 0.0 );
  testPrecondition( n >= 0 );

  // Get common angular grid
  std::vector<double> angular_grid;

  // resize array to the number of legendre moments wanted
  legendre_moments.resize(n+1);

  Utility::GaussKronrodIntegrator<Utility::long_float> 
    integrator( precision, 0.0, 1000 );

  // Turn of error and warning messages
  integrator.dontEstimateRoundoff();

  // Calucuate the cutoff and Rutherford component of the Legendre moment
  Utility::long_float cutoff_moment,rutherford_moment;

  // Get zeroth moments
  Utility::long_float rutherford_zero, cutoff_zero, legendre_zero;

  // if the cutoff angle cosine is above 0.999999 only the moments of the screened Rutherford are needed
  if ( d_cutoff_angle_cosine < s_rutherford_cutoff_angle_cosine )
  {
    angular_grid =
        MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGrid(
            d_cutoff_elastic_angles,
            energy,
            d_cutoff_angle_cosine );

    evaluateCutoffMoment( cutoff_zero, angular_grid, integrator, energy, 0 );
  }

    evaluateScreenedRutherfordMoment( rutherford_zero, energy, 0 );
  legendre_zero = rutherford_zero + cutoff_zero;

  // Iterate to get get all n moments
  for ( int i = 0; i <= n; i++ )
  {
    if ( d_cutoff_angle_cosine < s_rutherford_cutoff_angle_cosine )
    {
      evaluateCutoffMoment( cutoff_moment, angular_grid, integrator, energy, i );
    }
    evaluateScreenedRutherfordMoment( rutherford_moment, energy, i );


    legendre_moments[i] = (rutherford_moment + cutoff_moment)/legendre_zero;
  }
}

// Evaluate the nth cross section moment of the elastic cutoff distribution at the energy
void ElasticElectronMomentsEvaluator::evaluateCutoffMoment(
            Utility::long_float& cutoff_moment,
            const std::vector<double>& angular_grid,
            const Integrator& integrator,
            const double energy,
            const int n ) const
{
  // Make sure the energy and order is valid
  testPrecondition( energy > 0.0 );
  testPrecondition( n >= 0 );
  testPrecondition( angular_grid.size() > 1 );

  // Get the moments of the PDF
  evaluateCutoffPDFMoment(
        cutoff_moment,
        angular_grid,
        integrator,
        energy,
        n );

  // Get the cutoff cross section
  Utility::long_float cutoff_cross_section =
    d_cutoff_reaction->getCrossSection( energy );
//    MonteCarlo::getCrossSection<Utility::LinLin>(
//        energy,
//        d_incoming_energy_grid,
//        d_cutoff_cross_section,
//        d_cutoff_threshold_energy_index,
//        d_grid_searcher );

  cutoff_moment *= cutoff_cross_section;
}

// Evaluate the nth PDF moment of the cutoff distribution at the energy
void ElasticElectronMomentsEvaluator::evaluateCutoffPDFMoment(
            Utility::long_float& cutoff_moment,
            const std::vector<double>& angular_grid,
            const Integrator& integrator,
            const double energy,
            const int n ) const
{
  // Make sure the energy, anfgular grid and order are valid
  testPrecondition( energy > 0.0 );
  testPrecondition( n >= 0 );
  testPrecondition( angular_grid.size() > 1 );

  Utility::long_float abs_error, moment_k;

  // Create boost rapper function for the hard elastic differential cross section
  boost::function<double (double x)> distribution_wrapper =
    boost::bind<double>( &ElasticElectronMomentsEvaluator::evaluateLegendreExpandedPDF,
                         boost::cref( *this ),
                         _1,
                         energy,
                         n );

  std::vector<double>::const_iterator grid_point, grid_point_minus_one;
  grid_point_minus_one = angular_grid.begin();
  grid_point = ++angular_grid.begin();

  cutoff_moment = Utility::long_float(0);
  for ( grid_point; grid_point != angular_grid.end(); grid_point++ )
  {
    moment_k = Utility::long_float(0);
    abs_error = Utility::long_float(0);
    integrator.integrateAdaptively<61>(
            distribution_wrapper,
            (Utility::long_float)*grid_point_minus_one,
            (Utility::long_float)*grid_point,
            moment_k,
            abs_error );

    grid_point_minus_one = grid_point;

    cutoff_moment += moment_k;
  }
}

/* Evaluate the nth PDF moment of the screened Rutherford peak distribution
 * at the eta using the recursion relationship */
void ElasticElectronMomentsEvaluator::evaluateScreenedRutherfordPDFMomentByRecursion(
            Utility::long_float& rutherford_moment,
            const Utility::long_float& eta,
            const int& n ) const
{
  // Make sure the order and screening constant are valid
  testPrecondition( eta > 0.0 );
  testPrecondition( n >= 0 );

  Utility::long_float delta_mu, mu;

  // delta_mu = cutoff change in angle cosine = 1e-6
  delta_mu = Utility::long_float(1)/1000000;
  mu = Utility::long_float(999999)/1000000;

  rutherford_moment = Utility::long_float(1);
  Utility::long_float rutherford_moment_its = Utility::long_float(1);
  if ( n > 0 )
  {
      std::vector<Utility::long_float> coef_one( n+1 ), coef_two( n+1 );

      coef_one[0] = Utility::long_float(0);
      coef_one[1] = ( log( ( eta + delta_mu )/( eta ) ) ) -
                      delta_mu/( delta_mu + eta );

      coef_two[0] = delta_mu;
      coef_two[1] = ( Utility::long_float(1) - mu*mu )/
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
          ( i + Utility::long_float(2) )*mu*coef_two[i] -
          ( i - Utility::long_float(1) )/( i + Utility::long_float(2) )*
          coef_two[i-1];
      }

      rutherford_moment = (delta_mu - coef_one[n]*eta*( delta_mu + eta ))/delta_mu;
/*
    Utility::long_float frac_disc =
          delta_mu*( Utility::long_float(1) + eta/Utility::long_float(2) )/
      ( delta_mu + eta );

    rutherford_moment = (( frac_disc - (Utility::long_float(1) + eta/2)*eta*coef_one[n] )/frac_disc );
*/
  }
}

/* Evaluate the nth PDF moment of the screened Rutherford peak distribution
 * at the energy using numerical integration */
void ElasticElectronMomentsEvaluator::evaluateScreenedRutherfordPDFMomentByNumericalIntegration(
            Utility::long_float& rutherford_moment,
            const double& energy,
            const int& n ) const
{
  // Make sure the energy, anfgular grid and order are valid
  testPrecondition( energy > 0.0 );
  testPrecondition( n >= 0 );

  Utility::GaussKronrodIntegrator<Utility::long_float>
    integrator( 1e-13, 0.0, 1000 );

  // Turn of error and warning messages
  integrator.dontEstimateRoundoff();

  Utility::long_float abs_error, moment_zero;

  // Create boost rapper function for the analog elastic differential cross section
  boost::function<double (double x)> distribution_wrapper =
    boost::bind<double>( &ElasticElectronMomentsEvaluator::evaluateLegendreExpandedPDF,
                         boost::cref( *this ),
                         _1,
                         energy,
                         0 );

  rutherford_moment = Utility::long_float(0);

  abs_error = Utility::long_float(0);
  integrator.integrateAdaptively<61>(
            distribution_wrapper,
            Utility::long_float(999999)/1000000,
            Utility::long_float(1),
            moment_zero,
            abs_error );

  // Create boost rapper function for the analog elastic differential cross section
  distribution_wrapper =
    boost::bind<double>( &ElasticElectronMomentsEvaluator::evaluateLegendreExpandedPDF,
                         boost::cref( *this ),
                         _1,
                         energy,
                         n );

  rutherford_moment = Utility::long_float(0);

  abs_error = Utility::long_float(0);
  integrator.integrateAdaptively<61>(
            distribution_wrapper,
            Utility::long_float(999999)/1000000,
            Utility::long_float(1),
            rutherford_moment,
            abs_error );

  rutherford_moment /= moment_zero;
}

/* Evaluate the nth PDF moment of the screened Rutherford peak distribution
 * at the energy using numerical integration */
void ElasticElectronMomentsEvaluator::evaluateScreenedRutherfordPDFMomentByNumericalIntegration(
            Utility::long_float& rutherford_moment,
            const Utility::long_float& eta,
            const double& energy,
            const int& n ) const
{
  // Make sure the energy and order are valid
  testPrecondition( energy > 0.0 );
  testPrecondition( n >= 0 );

  // screened Rutherford cutoff angle cosine
  Utility::long_float mu = Utility::long_float(999999)/1000000;

  Utility::GaussKronrodIntegrator<Utility::long_float>
    integrator( 1e-13, 0.0, 1000 );

  // Turn of error and warning messages
  integrator.dontEstimateRoundoff();

  Utility::long_float abs_error, moment_n, moment_zero;

  // Create boost rapper function for the screened Rutherford peak
  boost::function<double (double x)> wrapper =
        boost::bind<double>( &ElasticElectronMomentsEvaluator::evaluateLegendreExpandedRutherford,
                         boost::cref( *this ),
                         _1,
                         energy,
                         (double) eta,
                         0 );

  integrator.integrateAdaptively<61>(
					wrapper,
                    mu,
					Utility::long_float(1),
					moment_zero,
					abs_error );

  moment_n = moment_zero;

  if ( n > 0 )
  {
    // Create boost rapper function for the screened Rutherford peak
    wrapper =
        boost::bind<double>( &ElasticElectronMomentsEvaluator::evaluateLegendreExpandedRutherford,
                         boost::cref( *this ),
                         _1,
                         energy,
                         (double) eta,
                         n );

    integrator.integrateAdaptively<61>(
					wrapper,
                    mu,
					Utility::long_float(1),
					moment_n,
					abs_error );
  }
  rutherford_moment = moment_n/moment_zero;
}

// Evaluate the nth PDF moment of the screened Rutherford peak distribution
void ElasticElectronMomentsEvaluator::evaluateScreenedRutherfordPDFMoment(
            Utility::long_float& rutherford_moment,
            const double& energy,
            const int& n ) const
{
  // Make sure the energy and order are valid
  testPrecondition( energy > 0.0 );
  testPrecondition( n >= 0 );

  // Calcuate Moliere's modified screening constant (eta)
  Utility::long_float eta = Utility::long_float(
    d_analog_distribution->evaluateMoliereScreeningConstant( energy ) );

  /*! \details The recursion relationship has been able to calculated the
      Rutherford moment faster and more accurately than numerical integration.
      Numerical integration has been left in in case there is an exception
      which the recursion relationship cannot calcuate.
   */
  evaluateScreenedRutherfordPDFMomentByRecursion(
    rutherford_moment,
    eta,
    n);
}

// Evaluate the nth cross section moment of the screened Rutherford peak distribution
void ElasticElectronMomentsEvaluator::evaluateScreenedRutherfordMoment(
            Utility::long_float& rutherford_moment,
            const double& energy,
            const int& n ) const
{
  // Make sure the energy and order are valid
  testPrecondition( energy > 0.0 );
  testPrecondition( n >= 0 );

  // Get the moments of the PDF
  evaluateScreenedRutherfordPDFMoment( rutherford_moment, energy, n);

  rutherford_moment *= d_screened_rutherford_reaction->getCrossSection( energy );
//    MonteCarlo::getCrossSection<Utility::LinLin>(
//        energy,
//        d_incoming_energy_grid,
//        d_screened_rutherford_cross_section,
//        d_screened_rutherford_threshold_energy_index,
//        d_grid_searcher );
}

// Return the angular integration points
void ElasticElectronMomentsEvaluator::getAngularIntegrationPoints(
        std::vector<double>& angular_integration_points,
        const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( energy > 0.0 );

  if( d_cutoff_elastic_angles.count( energy ) > 0 )
  {
    angular_integration_points =
        MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGrid(
            d_cutoff_elastic_angles.find( energy )->second,
            d_cutoff_angle_cosine );
  }
  else
  {
    std::map<double,std::vector<double>>::const_iterator lower_bin, upper_bin;
    lower_bin = d_cutoff_elastic_angles.lower_bound( energy );
    upper_bin = d_cutoff_elastic_angles.upper_bound( energy );

    // Use the angular grid for the energy bin closes to the energy
    if ( energy - lower_bin->first <= upper_bin->first - energy )
    {
      angular_integration_points =
        MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGrid(
            lower_bin->second,
            d_cutoff_angle_cosine );
    }
    else
    {
      angular_integration_points =
        MonteCarlo::ElasticElectronScatteringDistributionNativeFactory::getAngularGrid(
            upper_bin->second,
            d_cutoff_angle_cosine );
    }
  }
}


} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_ElasticElectronMomentsEvaluator.cpp
//---------------------------------------------------------------------------//
