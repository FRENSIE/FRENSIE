//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ScreenedRutherfordElasticElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  The electron screened Rutherford elastic scattering distribution definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_ScreenedRutherfordElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_TwoDDistributionHelpers.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_DirectionHelpers.hpp"
#include "Utility_KinematicHelpers.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_TabularDistribution.hpp"
//#include "Utility_ElasticElectronDistribution.hpp"

namespace MonteCarlo{


// Initialize static member data

// The fine structure constant squared
double ScreenedRutherfordElasticElectronScatteringDistribution::s_fine_structure_const_squared=
        Utility::PhysicalConstants::fine_structure_constant *
        Utility::PhysicalConstants::fine_structure_constant;

// A parameter for moliere's screening factor  (1/2*(fsc/0.885)**2)
double ScreenedRutherfordElasticElectronScatteringDistribution::s_screening_param1 = 
      ScreenedRutherfordElasticElectronScatteringDistribution::s_fine_structure_const_squared/
      ( 2.0*0.885*0.885 );

// Constructor without tabulated energy paramters
ScreenedRutherfordElasticElectronScatteringDistribution::ScreenedRutherfordElasticElectronScatteringDistribution(
    const ElasticDistribution& elastic_cutoff_distribution,
    const int atomic_number )
  : d_elastic_cutoff_distribution( elastic_cutoff_distribution ),
    d_atomic_number( atomic_number ),
    d_Z_two_thirds_power( pow( atomic_number, 2.0/3.0 ) ),
    d_screening_param2( 3.76*s_fine_structure_const_squared*
                              d_atomic_number*d_atomic_number )
{
  // Make sure the array is valid
  testPrecondition( !d_elastic_cutoff_distribution.is_null() );
  // Make sure the atomic number is valid
  testPrecondition( d_atomic_number > 0 );
  testPrecondition( d_atomic_number <= 100u );

  d_lower_cutoff_angle_cosine = 0.999999;
  d_upper_cutoff_delta_mu = 1.0e-6;

  d_using_endl_tables = false;
}

// Constructor with tabulated energy parameters
ScreenedRutherfordElasticElectronScatteringDistribution::ScreenedRutherfordElasticElectronScatteringDistribution(
    const ParameterArray& screened_rutherford_parameters )
  : d_screened_rutherford_parameters( screened_rutherford_parameters )
{
  // Make sure the parameter array is valid
  testPrecondition( d_screened_rutherford_parameters.size() > 0 );

  d_lower_cutoff_angle_cosine = 0.999999;
  d_upper_cutoff_delta_mu = 1.0e-6;

  d_using_endl_tables = true;
}

// Evaluate the distribution at the given energy and scattering angle cosine
double ScreenedRutherfordElasticElectronScatteringDistribution::evaluate( 
        const double incoming_energy,
        const double scattering_angle_cosine ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= d_lower_cutoff_angle_cosine );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  double delta_mu = 1.0 - scattering_angle_cosine;

  if ( d_using_endl_tables )
  {
    ParameterArray::const_iterator lower_bin_boundary, upper_bin_boundary;
    double interpolation_fraction;

    findLowerAndUpperBinBoundary( incoming_energy, 
                                  d_screened_rutherford_parameters,
                                  lower_bin_boundary, 
                                  upper_bin_boundary,
                                  interpolation_fraction );

    double lower_pdf = lower_bin_boundary->third/( 
                        ( delta_mu + lower_bin_boundary->second )*
                        ( delta_mu + lower_bin_boundary->second ) );

    double upper_pdf = upper_bin_boundary->third/( 
                         ( delta_mu + upper_bin_boundary->second )*
                         ( delta_mu + upper_bin_boundary->second ) );

    // Linearly interpolate between the upper and lower pdf values
    return interpolation_fraction*(upper_pdf - lower_pdf) + lower_pdf;
  }
  else
  {
    double cutoff_pdf = 
        d_elastic_cutoff_distribution->evaluate( 
            incoming_energy,
            d_lower_cutoff_angle_cosine );

    double eta = evaluateMoliereScreeningConstant( incoming_energy ); 

    double pdf = cutoff_pdf*
            ( d_upper_cutoff_delta_mu + eta )*( d_upper_cutoff_delta_mu + eta )/(
            ( delta_mu + eta )*( delta_mu + eta ) );

    return pdf;
  }
}


// Evaluate the PDF at the given energy and scattering angle cosine
double ScreenedRutherfordElasticElectronScatteringDistribution::evaluatePDF( 
        const double incoming_energy,
        const double scattering_angle_cosine ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= d_lower_cutoff_angle_cosine );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  double delta_mu = 1.0 - scattering_angle_cosine;

  if ( d_using_endl_tables )
  {
    ParameterArray::const_iterator lower_bin_boundary, upper_bin_boundary;
    double interpolation_fraction;

    findLowerAndUpperBinBoundary( incoming_energy, 
                                  d_screened_rutherford_parameters,
                                  lower_bin_boundary, 
                                  upper_bin_boundary,
                                  interpolation_fraction );

    double lower_pdf = lower_bin_boundary->third/( 
                        ( delta_mu + lower_bin_boundary->second )*
                        ( delta_mu + lower_bin_boundary->second ) );

    double upper_pdf = upper_bin_boundary->third/( 
                         ( delta_mu + upper_bin_boundary->second )*
                         ( delta_mu + upper_bin_boundary->second ) );

    // Linearly interpolate between the upper and lower pdf values
    return interpolation_fraction*(upper_pdf - lower_pdf) + lower_pdf;
  }
  else
  {
    double cutoff_pdf = 
        d_elastic_cutoff_distribution->evaluatePDF( incoming_energy, 0.999999 );

    double eta = evaluateMoliereScreeningConstant( incoming_energy ); 
   
    return cutoff_pdf*
            ( d_upper_cutoff_delta_mu + eta )*( d_upper_cutoff_delta_mu + eta )/(
            ( delta_mu + eta )*( delta_mu + eta ) );
  }
}

// Evaluate the integrated PDF at the given energy
double ScreenedRutherfordElasticElectronScatteringDistribution::evaluateIntegratedPDF( 
        const double incoming_energy ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( incoming_energy > 0.0 );

  if ( d_using_endl_tables )
  {
    ParameterArray::const_iterator lower_bin_boundary, upper_bin_boundary;
    double interpolation_fraction;

    findLowerAndUpperBinBoundary( incoming_energy, 
                                  d_screened_rutherford_parameters,
                                  lower_bin_boundary, 
                                  upper_bin_boundary,
                                  interpolation_fraction );

    double lower_value = d_upper_cutoff_delta_mu*lower_bin_boundary->third/( 
                        ( lower_bin_boundary->second )*
                        ( d_upper_cutoff_delta_mu + lower_bin_boundary->second ) );

    double upper_value = d_upper_cutoff_delta_mu*upper_bin_boundary->third/( 
                        ( upper_bin_boundary->second )*
                        ( d_upper_cutoff_delta_mu + upper_bin_boundary->second ) );

    // Linearly interpolate between the upper and lower values
    return interpolation_fraction*(upper_value - lower_value) + lower_value;
  }
  else
  {
    double cutoff_pdf = 
        d_elastic_cutoff_distribution->evaluatePDF( incoming_energy, 0.999999 );

    double eta = evaluateMoliereScreeningConstant( incoming_energy ); 
   
    return cutoff_pdf*d_upper_cutoff_delta_mu*
            ( d_upper_cutoff_delta_mu + eta )/( eta );
  }
}

// Evaluate the CDF
double ScreenedRutherfordElasticElectronScatteringDistribution::evaluateCDF( 
                            const double incoming_energy,
        const double scattering_angle_cosine ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= d_lower_cutoff_angle_cosine );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  double delta_mu = 1.0 - scattering_angle_cosine;

  if ( d_using_endl_tables )
  {
    ParameterArray::const_iterator lower_bin_boundary, upper_bin_boundary;
    double interpolation_fraction;

    findLowerAndUpperBinBoundary( incoming_energy, 
                                  d_screened_rutherford_parameters,
                                  lower_bin_boundary, 
                                  upper_bin_boundary,
                                  interpolation_fraction );

    double max_unormalized_cdf = 
      this->evaluateIntegratedPDF( d_upper_cutoff_delta_mu, 
                                   lower_bin_boundary, 
                                   upper_bin_boundary,
                                   interpolation_fraction );

    double unormalized_cdf = 
      this->evaluateIntegratedPDF( delta_mu, 
                                   lower_bin_boundary, 
                                   upper_bin_boundary,
                                   interpolation_fraction );

    // Return the normalized cdf value
    return unormalized_cdf/max_unormalized_cdf;
  }
  else
  {
    double eta = evaluateMoliereScreeningConstant( incoming_energy ); 
   
    return ( d_upper_cutoff_delta_mu + eta )/( delta_mu + eta )*
            ( delta_mu/d_upper_cutoff_delta_mu );
  }
}

// Sample an outgoing energy and direction from the distribution
void ScreenedRutherfordElasticElectronScatteringDistribution::sample( 
				     const double incoming_energy,
				     double& outgoing_energy,
				     double& scattering_angle_cosine ) const
{
  // The outgoing energy is always equal to the incoming energy
  outgoing_energy = incoming_energy;

  unsigned trial_dummy;

  // Sample an outgoing direction
  this->sampleAndRecordTrialsImpl( incoming_energy,
                                   scattering_angle_cosine,
                                   trial_dummy );
}

// Sample an outgoing energy and direction and record the number of trials
void ScreenedRutherfordElasticElectronScatteringDistribution::sampleAndRecordTrials( 
					    const double incoming_energy,
					    double& outgoing_energy,
					    double& scattering_angle_cosine,
					    unsigned& trials ) const
{
  // The outgoing energy is always equal to the incoming energy
  outgoing_energy = incoming_energy;
  
  // Sample an outgoing direction
  this->sampleAndRecordTrialsImpl( incoming_energy,
                                   scattering_angle_cosine,
                                   trials );
}

// Randomly scatter the electron
void ScreenedRutherfordElasticElectronScatteringDistribution::scatterElectron( 
				     ElectronState& electron,
				     ParticleBank& bank,
				     Data::SubshellType& shell_of_interaction ) const
{
  double scattering_angle_cosine;

  unsigned trial_dummy;

  // Sample an outgoing direction
  this->sampleAndRecordTrialsImpl( electron.getEnergy(),
				                   scattering_angle_cosine,
				                   trial_dummy );

  shell_of_interaction =Data::UNKNOWN_SUBSHELL;

  // Set the new direction
  electron.rotateDirection( scattering_angle_cosine, 
			  this->sampleAzimuthalAngle() );
}

// Randomly scatter the adjoint electron
void ScreenedRutherfordElasticElectronScatteringDistribution::scatterAdjointElectron( 
				     AdjointElectronState& adjoint_electron,
				     ParticleBank& bank,
				     Data::SubshellType& shell_of_interaction ) const
{
  double scattering_angle_cosine;

  unsigned trial_dummy;

  // Sample an outgoing direction
  this->sampleAndRecordTrialsImpl( adjoint_electron.getEnergy(),
				                   scattering_angle_cosine,
				                   trial_dummy );
  
  shell_of_interaction = Data::UNKNOWN_SUBSHELL;

  // Set the new direction
  adjoint_electron.rotateDirection( scattering_angle_cosine, 
				                    this->sampleAzimuthalAngle() );
}

// Evaluate Moliere's atomic screening constant (modified by Seltzer) at the given electron energy
double ScreenedRutherfordElasticElectronScatteringDistribution::evaluateMoliereScreeningConstant(
                                              const double energy ) const
{
  // get the momentum**2 of the electron in units of electron_rest_mass_energy
  double electron_momentum_squared = 
           Utility::calculateDimensionlessRelativisticMomentumSquared( 
                          Utility::PhysicalConstants::electron_rest_mass_energy,
                          energy );

  // get the velocity of the electron divided by the speed of light beta = v/c
  double beta_squared = Utility::calculateDimensionlessRelativisticSpeedSquared( 
           Utility::PhysicalConstants::electron_rest_mass_energy,
           energy );

  double screening_param3 = 1.0/beta_squared*sqrt( energy/
            ( energy + Utility::PhysicalConstants::electron_rest_mass_energy) );

 // Calculate Moliere's atomic screening constant
 return s_screening_param1 * 1.0/electron_momentum_squared * 
        d_Z_two_thirds_power * ( 1.13 + d_screening_param2*screening_param3 );
}

// Sample an outgoing direction from the distribution
void ScreenedRutherfordElasticElectronScatteringDistribution::sampleAndRecordTrialsImpl( 
                                                const double incoming_energy,
                                                double& scattering_angle_cosine,
                                                unsigned& trials ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );

  // Increment the number of trials
  ++trials;

  double random_number = 
              Utility::RandomNumberGenerator::getRandomNumber<double>();

  if ( d_using_endl_tables )
  {
    ParameterArray::const_iterator lower_bin_boundary, upper_bin_boundary;
    double interpolation_fraction;

    findLowerAndUpperBinBoundary( incoming_energy, 
                                  d_screened_rutherford_parameters,
                                  lower_bin_boundary, 
                                  upper_bin_boundary,
                                  interpolation_fraction );

    double max_unormalized_cdf = 
      this->evaluateIntegratedPDF( d_lower_cutoff_angle_cosine, 
                                   lower_bin_boundary, 
                                   upper_bin_boundary,
                                   interpolation_fraction );

    double scaled_random_number = random_number*max_unormalized_cdf;

    double lower_delta_mu =
        ( lower_bin_boundary->second*lower_bin_boundary->second 
            *scaled_random_number )/
        ( lower_bin_boundary->third -
            lower_bin_boundary->second*scaled_random_number );

    double upper_delta_mu =
        ( upper_bin_boundary->second*upper_bin_boundary->second 
            *scaled_random_number )/
        ( upper_bin_boundary->third -
            upper_bin_boundary->second*scaled_random_number );

    // Linearly interpolate between the upper and lower delta_mus
    double delta_mu = 
            interpolation_fraction*(upper_delta_mu - lower_delta_mu) + lower_delta_mu;

    scattering_angle_cosine = 1.0L - delta_mu;
  }
  else
  {
    double eta = evaluateMoliereScreeningConstant( incoming_energy );

    scattering_angle_cosine =
        ( ( 1.0 - random_number*( 1.0 + eta ) )*d_upper_cutoff_delta_mu + eta )/
        ( ( 1.0 - random_number )*d_upper_cutoff_delta_mu + eta );
  }

  // Make sure the scattering angle cosine is valid
  testPostcondition( scattering_angle_cosine >= d_lower_cutoff_angle_cosine );
  testPostcondition( scattering_angle_cosine <= 1.0 );
}

// evaluate the pdf integrated from 0 to delta_mu
double ScreenedRutherfordElasticElectronScatteringDistribution::evaluateIntegratedPDF( 
        const double& delta_mu, 
        const ParameterArray::const_iterator& lower_bin_boundary, 
        const ParameterArray::const_iterator& upper_bin_boundary,
        const double& interpolation_fraction ) const
{
  double lower_value = ( delta_mu*lower_bin_boundary->third )/(
                       ( delta_mu + lower_bin_boundary->second )*
                       lower_bin_boundary->second );

  double upper_value = ( delta_mu*upper_bin_boundary->third )/(
                       ( delta_mu + upper_bin_boundary->second )*
                       upper_bin_boundary->second );

  // Linearly interpolate between the upper and lower integrated pdf values
  return interpolation_fraction*(upper_value - lower_value) + lower_value;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ScreenedRutherfordElasticElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
