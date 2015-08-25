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
#include "Utility_GaussKronrodQuadratureKernel.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_DirectionHelpers.hpp"
#include "Utility_KinematicHelpers.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_ElasticElectronDistribution.hpp"

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
    const ElasticTabularDistribution& d_elastic_cutoff_pdf,
    const int atomic_number,
    const double upper_cutoff_angle )
  : d_elastic_cutoff_pdf( d_elastic_cutoff_pdf ),
    d_atomic_number( atomic_number ),
    d_upper_cutoff_angle( upper_cutoff_angle ),
    d_Z_two_thirds_power( pow( atomic_number, 2.0/3.0 ) ),
    d_screening_param2( 3.76*s_fine_structure_const_squared*
                              d_atomic_number*d_atomic_number )
{
  // Make sure the array is valid
  testPrecondition( !d_elastic_cutoff_pdf.is_null() );
  // Make sure the atomic number is valid
  testPrecondition( d_atomic_number > 0 );
  testPrecondition( d_atomic_number <= 100u );

  d_lower_cutoff_angle_cosine = 1.0L - d_upper_cutoff_angle;

  d_using_endl_tables = false;
}

// Constructor with tabulated energy parameters
ScreenedRutherfordElasticElectronScatteringDistribution::ScreenedRutherfordElasticElectronScatteringDistribution(
    const ParameterArray& screened_rutherford_parameters,
    const double upper_cutoff_angle )
  : d_screened_rutherford_parameters( screened_rutherford_parameters ),
    d_upper_cutoff_angle( upper_cutoff_angle ) 
{
  // Make sure the parameter array is valid
  testPrecondition( d_screened_rutherford_parameters.size() > 0 );
  // Make sure the cutoff angle is valid
  testPrecondition( d_upper_cutoff_angle > 0.0 );
  testPrecondition( d_upper_cutoff_angle <= 2.0 );

  d_using_endl_tables = true;
}

// Evaluate the PDF at the given energy and scattering angle (units of pi)
double ScreenedRutherfordElasticElectronScatteringDistribution::evaluatePDF( 
        const double incoming_energy,
        const double scattering_angle ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle >= 0.0 );
  testPrecondition( scattering_angle <= d_upper_cutoff_angle );

  if ( d_using_endl_tables )
  {
    ParameterArray::const_iterator lower_bin_boundary, upper_bin_boundary;
    double interpolation_fraction;

    this->findLowerAndUpperBinBoundary( incoming_energy, 
                                        lower_bin_boundary, 
                                        upper_bin_boundary,
                                        interpolation_fraction );

    double lower_pdf = lower_bin_boundary->third/( 
                        ( scattering_angle + lower_bin_boundary->second )*
                        ( scattering_angle + lower_bin_boundary->second ) );

    double upper_pdf = upper_bin_boundary->third/( 
                         ( scattering_angle + upper_bin_boundary->second )*
                         ( scattering_angle + upper_bin_boundary->second ) );

    // Linearly interpolate between the upper and lower pdf values
    return interpolation_fraction*(upper_pdf - lower_pdf) + lower_pdf;
  }
  else
  {
    double cutoff_pdf = d_elastic_cutoff_pdf->evaluate( incoming_energy );

    double eta = evaluateMoliereScreeningConstant( incoming_energy ); 
   
    return cutoff_pdf*
            ( d_upper_cutoff_angle + eta )*( d_upper_cutoff_angle + eta )/(
            ( scattering_angle + eta )*( scattering_angle + eta ) );
  }
}

// Evaluate the CDF
double ScreenedRutherfordElasticElectronScatteringDistribution::evaluateCDF( 
                            const double incoming_energy,
                            const double scattering_angle ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle >= 0.0 );
  testPrecondition( scattering_angle <= d_upper_cutoff_angle );

  if ( d_using_endl_tables )
  {
    ParameterArray::const_iterator lower_bin_boundary, upper_bin_boundary;
    double interpolation_fraction;

    this->findLowerAndUpperBinBoundary( incoming_energy, 
                                        lower_bin_boundary, 
                                        upper_bin_boundary,
                                        interpolation_fraction );

    double max_unormalized_cdf = 
      this->evaluateIntegratedPDF( d_upper_cutoff_angle, 
                                   lower_bin_boundary, 
                                   upper_bin_boundary,
                                   interpolation_fraction );

    double unormalized_cdf = 
      this->evaluateIntegratedPDF( scattering_angle, 
                                   lower_bin_boundary, 
                                   upper_bin_boundary,
                                   interpolation_fraction );

    // Return the normalized cdf value
    return unormalized_cdf/max_unormalized_cdf;
  }
  else
  {
    double eta = evaluateMoliereScreeningConstant( incoming_energy ); 
   
    return ( d_upper_cutoff_angle + eta )/( scattering_angle + eta )*
            ( scattering_angle/d_upper_cutoff_angle );
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
				     SubshellType& shell_of_interaction ) const
{
  double scattering_angle_cosine;

  unsigned trial_dummy;

  // Sample an outgoing direction
  this->sampleAndRecordTrialsImpl( electron.getEnergy(),
				                   scattering_angle_cosine,
				                   trial_dummy );

  shell_of_interaction = UNKNOWN_SUBSHELL;

  // Set the new direction
  electron.rotateDirection( scattering_angle_cosine, 
			  this->sampleAzimuthalAngle() );
}

// Randomly scatter the adjoint electron
void ScreenedRutherfordElasticElectronScatteringDistribution::scatterAdjointElectron( 
				     AdjointElectronState& adjoint_electron,
				     ParticleBank& bank,
				     SubshellType& shell_of_interaction ) const
{
  double scattering_angle_cosine;

  unsigned trial_dummy;

  // Sample an outgoing direction
  this->sampleAndRecordTrialsImpl( adjoint_electron.getEnergy(),
				                   scattering_angle_cosine,
				                   trial_dummy );
  
  shell_of_interaction = UNKNOWN_SUBSHELL;

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

    this->findLowerAndUpperBinBoundary( incoming_energy, 
                                        lower_bin_boundary, 
                                        upper_bin_boundary,
                                        interpolation_fraction );

    double max_unormalized_cdf = 
      this->evaluateIntegratedPDF( d_upper_cutoff_angle, 
                                   lower_bin_boundary, 
                                   upper_bin_boundary,
                                   interpolation_fraction );

    double scaled_random_number = random_number*max_unormalized_cdf;

    double lower_angle = ( lower_bin_boundary->second*lower_bin_boundary->second 
                          *scaled_random_number )/(
                        lower_bin_boundary->third -
                        lower_bin_boundary->second*scaled_random_number );

    double upper_angle = ( upper_bin_boundary->second*upper_bin_boundary->second 
                          *scaled_random_number )/(
                          upper_bin_boundary->third -
                          upper_bin_boundary->second*scaled_random_number );


    // Linearly interpolate between the upper and lower angles
    double angle = 
            interpolation_fraction*(upper_angle - lower_angle) + lower_angle;

    scattering_angle_cosine = 1.0L - angle;
  }
  else
  {
    double eta = evaluateMoliereScreeningConstant( incoming_energy );

    scattering_angle_cosine = 
        ( ( 1.0 - random_number*( 1.0 + eta ) )*d_upper_cutoff_angle + eta )/
        ( ( 1.0 - random_number )*d_upper_cutoff_angle + eta ); 
  }

  // Make sure the scattering angle cosine is valid
  testPostcondition( scattering_angle_cosine >= 1.0 - d_upper_cutoff_angle );
  testPostcondition( scattering_angle_cosine <= 1.0 );
}

// Find the lower and upper bin boundary
void ScreenedRutherfordElasticElectronScatteringDistribution::findLowerAndUpperBinBoundary( 
        const double incoming_energy,
        ParameterArray::const_iterator& lower_bin_boundary,
        ParameterArray::const_iterator& upper_bin_boundary,
        double& interpolation_fraction ) const
{
  if( incoming_energy < d_screened_rutherford_parameters.front().first )
  {
    lower_bin_boundary = d_screened_rutherford_parameters.begin();
    upper_bin_boundary = lower_bin_boundary;
  }
  else if( incoming_energy >= d_screened_rutherford_parameters.back().first )
  {
    lower_bin_boundary = d_screened_rutherford_parameters.end();
    --lower_bin_boundary;
    upper_bin_boundary = lower_bin_boundary;
  }
  else
  {
    lower_bin_boundary = d_screened_rutherford_parameters.begin();
    upper_bin_boundary = d_screened_rutherford_parameters.end();
    
    lower_bin_boundary = Utility::Search::binaryLowerBound<Utility::FIRST>( 
							lower_bin_boundary,
							upper_bin_boundary,
							incoming_energy );
    upper_bin_boundary = lower_bin_boundary;
    ++upper_bin_boundary;

    // Calculate the interpolation fraction
    interpolation_fraction = 
      (incoming_energy - lower_bin_boundary->first)/
      (upper_bin_boundary->first - lower_bin_boundary->first);
  }
}

// evaluate the pdf integrated from 0 to angle
double ScreenedRutherfordElasticElectronScatteringDistribution::evaluateIntegratedPDF( 
        const double& scattering_angle, 
        const ParameterArray::const_iterator& lower_bin_boundary, 
        const ParameterArray::const_iterator& upper_bin_boundary,
        const double& interpolation_fraction ) const
{
  double lower_value = ( scattering_angle*lower_bin_boundary->third )/(
                       ( scattering_angle + lower_bin_boundary->second )*
                       lower_bin_boundary->second );

  double upper_value = ( scattering_angle*upper_bin_boundary->third )/(
                       ( scattering_angle + upper_bin_boundary->second )*
                       upper_bin_boundary->second );

  // Linearly interpolate between the upper and lower integrated pdf values
  return interpolation_fraction*(upper_value - lower_value) + lower_value;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ScreenedRutherfordElasticElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
