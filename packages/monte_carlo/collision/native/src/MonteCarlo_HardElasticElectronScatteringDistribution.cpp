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
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_DirectionHelpers.hpp"
#include "Utility_KinematicHelpers.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_TabularDistribution.hpp"

namespace MonteCarlo{

// Initialize static member data
double HardElasticElectronScatteringDistribution::s_cutoff_angle_cosine = 
  0.999999;

// Constructor 
HardElasticElectronScatteringDistribution::HardElasticElectronScatteringDistribution(
    const int atomic_number,
    const ElasticDistribution& elastic_scattering_distribution)
  : d_atomic_number( atomic_number ),
    d_elastic_scattering_distribution( elastic_scattering_distribution )
{
  // Make sure the array is valid
  testPrecondition( d_elastic_scattering_distribution.size() > 0 );
}

// Randomly scatter the electron
void HardElasticElectronScatteringDistribution::scatterElectron( 
                                ElectronState& electron,
			                    ParticleBank& bank,
                                SubshellType& shell_of_interaction ) const
{
  // Sample the scattering angle cosine
  double scattering_angle_cosine = 
   HardElasticElectronScatteringDistribution::sampleScatteringAngleCosine( 
                                                         electron.getEnergy() );

  // Calculate the outgoing direction
  double outgoing_electron_direction[3];

  Utility::rotateDirectionThroughPolarAndAzimuthalAngle(
	  					   scattering_angle_cosine,
		  				   sampleAzimuthalAngle(),
			  			   electron.getDirection(),
				  		   outgoing_electron_direction );

  // Make sure the scattering angle cosine is valid
  testPostcondition( scattering_angle_cosine >= -1.0 );
  testPostcondition( scattering_angle_cosine <= 1.0 );
  
  // Set the new direction
  electron.setDirection( outgoing_electron_direction );
}


// Evaluate the screening angle at the given electron energy
double HardElasticElectronScatteringDistribution::evaluateScreeningFactor(
                                              const double energy ) const
{
  // get the momentum of the electron in units of electron_rest_mass * speed of light
  double electron_momentum = Utility::calculateDimensionlessRelativisticMomentum( 
                           Utility::PhysicalConstants::electron_rest_mass_energy,
                           energy );

  // get the velocity of the electron divided by the speed of light beta = v/c
  double beta = Utility::calculateDimensionlessRelativisticSpeed( 
           Utility::PhysicalConstants::electron_rest_mass_energy,
           energy );

 double arg1 = 1.0/( Utility::PhysicalConstants::inverse_fine_structure_constant*
                     0.885 * electron_momentum );

 double arg2 = d_atomic_number/
          ( Utility::PhysicalConstants::inverse_fine_structure_constant * beta );

 // Calculate the screening angle
 return arg1*arg1/2.0 * pow(d_atomic_number, 2.0/3.0)*( 1.13 + 3.76*arg2*arg2 );
}

// Evaluate the scattering angle from the analytical function
double HardElasticElectronScatteringDistribution::evaluateScreenedScatteringAngle(
                                                  const double energy ) const                                                
{
  double random_number = 
                      Utility::RandomNumberGenerator::getRandomNumber<double>();
    
  // evaluate the screening angle at the given electron energy
  double screening_angle = evaluateScreeningFactor( energy );

 // Calculate the screened scattering angle
  double arg = (1.0 - random_number)/( screening_angle + 0.000001 );

  return screening_angle + 1.0 - 1.0/(arg + random_number/screening_angle);
}


// Sample a scattering angle cosine
double HardElasticElectronScatteringDistribution::sampleScatteringAngleCosine(
                                                      double const energy) const
{
  // angle cosine the electron scatters into
  double scattering_angle_cosine;

  // The cutoff CDF for applying the analytical screening function
  double cutoff_cdf_value;

  double random_number;

  // Energy is below the lowest grid point
  if( energy < d_elastic_scattering_distribution.front().first )
  {
    cutoff_cdf_value = 
      d_elastic_scattering_distribution.front().second->evaluateCDF( 
                                                       s_cutoff_angle_cosine );

    random_number = Utility::RandomNumberGenerator::getRandomNumber<double>();

    // Correlated sample from the distribution
    if( cutoff_cdf_value > random_number )
    {
      scattering_angle_cosine = 
        d_elastic_scattering_distribution.front().second->sample( cutoff_cdf_value );
    }
    // Sample from the analytical function
    else
    {
      scattering_angle_cosine = evaluateScreenedScatteringAngle( energy );
    }
  }
  // Energy is above the highest grid point
  else if( energy >= d_elastic_scattering_distribution.back().first )
  {
    cutoff_cdf_value = 
      d_elastic_scattering_distribution.back().second->evaluateCDF( 
                                                       s_cutoff_angle_cosine );

    random_number = Utility::RandomNumberGenerator::getRandomNumber<double>();

    // Correlated sample from the distribution
    if( cutoff_cdf_value > random_number )
    {
      scattering_angle_cosine = 
        d_elastic_scattering_distribution.back().second->sample( cutoff_cdf_value );
    }
    // Sample from the analytical function
    else
    {
      scattering_angle_cosine = evaluateScreenedScatteringAngle( energy );
    }
  }
  // Energy is inbetween two grid point
  else
  {
    ElasticDistribution::const_iterator lower_dist_boundary, upper_dist_boundary;
    
    lower_dist_boundary = d_elastic_scattering_distribution.begin();
    upper_dist_boundary = d_elastic_scattering_distribution.end();
    
    lower_dist_boundary = Utility::Search::binaryLowerBound<Utility::FIRST>( 
							  lower_dist_boundary,
							  upper_dist_boundary,
							  energy );

    upper_dist_boundary = lower_dist_boundary;
    ++upper_dist_boundary;

    // Calculate the interpolation fraction
    double interpolation_fraction = 
       ( energy - lower_dist_boundary->first )/
       ( upper_dist_boundary->first - lower_dist_boundary->first );

    // evaluate the cutoff CDF for applying the analytical screening function
    cutoff_cdf_value = evaluateCorrelatedCDF( upper_dist_boundary->second,
                                              lower_dist_boundary->second,
                                              interpolation_fraction,
                                              s_cutoff_angle_cosine );
     
    double random_number = 
      Utility::RandomNumberGenerator::getRandomNumber<double>();

    // Correlated sample from the distribution
    if( cutoff_cdf_value > random_number )
    {
    scattering_angle_cosine = correlatedSample( upper_dist_boundary->second,
                                                lower_dist_boundary->second,
                                                interpolation_fraction,
                                                cutoff_cdf_value );
    }
    // Sample from the analytical function
    else
    {
      scattering_angle_cosine = evaluateScreenedScatteringAngle( energy );
    }
  }

  // Make sure the scattering angle cosine is valid
  testPostcondition( scattering_angle_cosine >= -1.0 );
  testPostcondition( scattering_angle_cosine <= 1.0 );

  return scattering_angle_cosine;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_HardElasticElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
