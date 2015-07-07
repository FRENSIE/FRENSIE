//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_HardElasticElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  The electron hard elastic scattering distribution definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_HardElasticElectronScatteringDistribution.hpp"
#include "MonteCarlo_TwoDDistributionHelpers.hpp"
#include "Utility_GaussKronrodQuadratureKernel.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_DirectionHelpers.hpp"
#include "Utility_KinematicHelpers.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_HistogramDistribution.hpp"

namespace MonteCarlo{

// Initialize static member data

// cutoff angle cosine for analytical peak
double HardElasticElectronScatteringDistribution::s_mu_cutoff = 0.999999;

// Difference btw cutoff angle cosine for analytical peak and foward peak (mu=1)
double HardElasticElectronScatteringDistribution::s_delta_cutoff = 
  1.0 - s_mu_cutoff;

// The fine structure constant squared
double HardElasticElectronScatteringDistribution::s_fine_structure_const_squared=
        Utility::PhysicalConstants::fine_structure_constant *
        Utility::PhysicalConstants::fine_structure_constant;

// A parameter for moliere's screening factor  (1/2*(fsc/0.885)**2)
double HardElasticElectronScatteringDistribution::s_screening_param1 = 
      HardElasticElectronScatteringDistribution::s_fine_structure_const_squared/
      ( 2.0*0.885*0.885 );

// Constructor 
HardElasticElectronScatteringDistribution::HardElasticElectronScatteringDistribution(
    const int atomic_number,
    const ElasticDistribution& elastic_scattering_distribution)
  : d_atomic_number( atomic_number ),
    d_Z_two_thirds_power( pow( atomic_number, 2.0/3.0 ) ),
    d_screening_param2( 3.76*s_fine_structure_const_squared*
                              d_atomic_number*d_atomic_number ),
    d_elastic_scattering_distribution( elastic_scattering_distribution )
{
  // Make sure the array is valid
  testPrecondition( d_elastic_scattering_distribution.size() > 0 );
}

// Evaluate the PDF
double HardElasticElectronScatteringDistribution::evaluatePDF( 
                            const double incoming_energy,
                            const double scattering_angle_cosine ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  if ( scattering_angle_cosine <= s_mu_cutoff )
  {
    return MonteCarlo::evaluateTwoDDistributionCorrelatedPDF( 
                         incoming_energy,
                         scattering_angle_cosine,
                         d_elastic_scattering_distribution );
  }
  else
  {
    return evaluateScreenedRutherfordPDF( incoming_energy, 
                                          scattering_angle_cosine );
  }
}

// Sample an outgoing energy and direction from the distribution
void HardElasticElectronScatteringDistribution::sample( 
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
void HardElasticElectronScatteringDistribution::sampleAndRecordTrials( 
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
void HardElasticElectronScatteringDistribution::scatterElectron( 
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
void HardElasticElectronScatteringDistribution::scatterAdjointElectron( 
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

// Evaluate the PDF
double HardElasticElectronScatteringDistribution::evaluateScreenedRutherfordPDF( 
                            const double incoming_energy,
                            const double scattering_angle_cosine ) const
{
  // Make sure the energy and angle are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  double cutoff_pdf_value = MonteCarlo::evaluateTwoDDistributionCorrelatedPDF( 
                                incoming_energy,
                                s_mu_cutoff,
                                d_elastic_scattering_distribution );

  double screening_factor = evaluateScreeningFactor( incoming_energy );

  double delta_cosine = 1.0 - scattering_angle_cosine;
  if ( delta_cosine < 1e-10)
  {
    delta_cosine = 0.0;
  }

  double ratio = ( screening_factor + s_delta_cutoff )/
                  ( screening_factor + delta_cosine );

  double ratio_squared = ratio*ratio;

  return cutoff_pdf_value*ratio_squared;
}


// Evaluate the screening factor at the given electron energy
double HardElasticElectronScatteringDistribution::evaluateScreeningFactor(
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

 // Calculate the screening factor
 return s_screening_param1 * 1.0/electron_momentum_squared * 
        d_Z_two_thirds_power * ( 1.13 + d_screening_param2/beta_squared );
}

// Evaluate the scattering angle from the analytical screend Rutherford function
double HardElasticElectronScatteringDistribution::evaluateScreenedScatteringAngle(
                                                  const double energy ) const 
{
  double random_number = 
                      Utility::RandomNumberGenerator::getRandomNumber<double>();
    
  // evaluate the screening angle at the given electron energy
  double screening_factor = evaluateScreeningFactor( energy );

  // Calculate the screened scattering angle
  double arg = random_number*s_delta_cutoff;

  return ( screening_factor*s_mu_cutoff + 
           arg*( screening_factor + 1.0 ) ) /
         ( screening_factor + arg );
}


// Sample an outgoing direction from the distribution
void HardElasticElectronScatteringDistribution::sampleAndRecordTrialsImpl( 
                                                const double incoming_energy,
                                                double& scattering_angle_cosine,
                                                unsigned& trials ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );

  // Increment the number of trials
  ++trials;

  // The cutoff CDF for applying the analytical screening function
  double cutoff_cdf_value;

  double random_number;

  // Energy is below the lowest grid point
  if( incoming_energy < d_elastic_scattering_distribution.front().first )
  {
    cutoff_cdf_value = 
      d_elastic_scattering_distribution.front().second->evaluateCDF( s_mu_cutoff );

    random_number = Utility::RandomNumberGenerator::getRandomNumber<double>();

    // Sample from the lower energy value of the distribution
    if( cutoff_cdf_value > random_number )
    {
      scattering_angle_cosine = 
        d_elastic_scattering_distribution.front().second->sampleInSubrange( 
						       s_mu_cutoff );
    }
    // Sample from the analytical screend Rutherford function
    else
      scattering_angle_cosine = evaluateScreenedScatteringAngle( 
                                                              incoming_energy );
  }
  // Energy is above the highest grid point
  else if( incoming_energy >= d_elastic_scattering_distribution.back().first )
  {
    cutoff_cdf_value = 
      d_elastic_scattering_distribution.back().second->evaluateCDF( s_mu_cutoff );

    random_number = Utility::RandomNumberGenerator::getRandomNumber<double>();

    // Sample from the upper energy value of the distribution
    if( cutoff_cdf_value > random_number )
    {
      scattering_angle_cosine = 
        d_elastic_scattering_distribution.back().second->sampleInSubrange( 
						       s_mu_cutoff );
    }
    // Sample from the analytical screend Rutherford function
    else
      scattering_angle_cosine = evaluateScreenedScatteringAngle( 
                                                              incoming_energy );
  }
  // Energy is inbetween two grid point
  else
  {
    ElasticDistribution::const_iterator lower_dist_boundary, upper_dist_boundary;
    double interpolation_fraction;

    // Find upper and lower bin and calculate the interpolation fraction
    findLowerAndUpperBinBoundary( incoming_energy,
                                  d_elastic_scattering_distribution,
                                  lower_dist_boundary,
                                  upper_dist_boundary,
                                  interpolation_fraction );

    // evaluate the cutoff CDF for applying the analytical screening function
    cutoff_cdf_value = evaluateCorrelatedCDF( upper_dist_boundary->second,
                                              lower_dist_boundary->second,
                                              interpolation_fraction,
                                              s_mu_cutoff );

    double cutoff_pdf_value;
    // evaluate the cutoff PDF for applying the analytical screening function
    cutoff_pdf_value = evaluateCorrelatedPDF( upper_dist_boundary->second,
                                              lower_dist_boundary->second,
                                              interpolation_fraction,
                                              s_mu_cutoff );

    // evaluate the screening angle at the given electron energy
    double screening_factor = evaluateScreeningFactor( incoming_energy );
/*
    double analytical_cdf = cutoff_pdf_value/screening_factor*
     ( s_delta_cutoff + screening_factor )*( s_delta_cutoff );

    double alternative_cutoff_cdf = cutoff_cdf_value/( cutoff_cdf_value + analytical_cdf );
*/  
    double random_number = 
      Utility::RandomNumberGenerator::getRandomNumber<double>();

    // Correlated sample from the distribution
    if( cutoff_cdf_value > random_number )
    {
    scattering_angle_cosine = correlatedSample( upper_dist_boundary->second,
                                                lower_dist_boundary->second,
                                                interpolation_fraction,
                                                s_mu_cutoff );
    }
    // Sample from the analytical screend Rutherford function
    else
    {
      scattering_angle_cosine = evaluateScreenedScatteringAngle( incoming_energy );
    }
  }

  // Make sure the scattering angle cosine is valid
  testPostcondition( scattering_angle_cosine >= -1.0 );
  testPostcondition( scattering_angle_cosine <= 1.0 );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_HardElasticElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
