//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ModifiedWentzelElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  The electron modified Wentzel scattering distribution definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_ModifiedWentzelElectronScatteringDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_DirectionHelpers.hpp"

namespace MonteCarlo{

//! Constructor
ModifiedWentzelElectronScatteringDistribution::ModifiedWentzelElectronScatteringDistribution(
  const MWDistribution& modified_wentzel_parameters,
  const double& average_angle_cosine  )
  : d_modified_wentzel_parameters( modified_wentzel_parameters ),
    d_average_angle_cosine( average_angle_cosine )
{
  // Make sure the array is valid
  testPrecondition( modified_wentzel_parameters.size() > 0 );
}

//! Randomly scatter the electron
void ModifiedWentzelElectronScatteringDistribution::scatterElectron( 
                                ElectronState& electron,
			                    ParticleBank& bank) const
{
  // modified Wentzel scattering parameters A and B
  double A, B;

  // The scattering angle cosine
  double scattering_angle_cosine;

  // Get modified Wentzel scattering parameters
  if( electron.getEnergy() < d_modified_wentzel_parameters.front().first )
  {
    A = d_modified_wentzel_parameters.front().second.first;
    B = d_modified_wentzel_parameters.front().second.second;
  }
  else if( electron.getEnergy() >= d_modified_wentzel_parameters.back().first )
  {
    A = d_modified_wentzel_parameters.back().second.first;
    B = d_modified_wentzel_parameters.back().second.second;
  }
  else
  {
    MWDistribution::const_iterator lower_bin_boundary, upper_bin_boundary;
    
    lower_bin_boundary = d_modified_wentzel_parameters.begin();
    upper_bin_boundary = d_modified_wentzel_parameters.end();
    
    lower_bin_boundary = Utility::Search::binaryLowerBound<Utility::FIRST>( 
							  lower_bin_boundary,
							  upper_bin_boundary,
							  electron.getEnergy() );

    upper_bin_boundary = lower_bin_boundary;
    ++upper_bin_boundary;

    // Calculate the interpolation fraction
    double interpolation_fraction = ( electron.getEnergy() - lower_bin_boundary->first )/
      ( upper_bin_boundary->first - lower_bin_boundary->first );
    
    double random_number = Utility::RandomNumberGenerator::getRandomNumber<double>();
    
    if( random_number < interpolation_fraction )
    {
      A = upper_bin_boundary->second.first;
      B = upper_bin_boundary->second.second;
    }
    else
    {
      A = lower_bin_boundary->second.first;
      B = upper_bin_boundary->second.second;
    }
  }

  if ( B > 0 )
  {
    double random_number_parameter;
    double random_number = Utility::RandomNumberGenerator::getRandomNumber<double>();

    random_number_parameter = (1.0 - B)*(1.0 + A)*d_average_angle_cosine/
                              (A + d_average_angle_cosine); 

    if ( random_number < random_number_parameter )
    {
      scattering_angle_cosine = random_number*A/( (1.0 - B)*(1.0 + A) - random_number );
    }
    else if ( random_number < random_number_parameter + B )
    {
      scattering_angle_cosine = d_average_angle_cosine;
    }
    else
    {
      scattering_angle_cosine = (random_number-B)*A / ( (1.0-B)*(1.0+A) - (random_number - B) );
    }
  }
  else
  {
//! \todo Write sampling procedure for modified Wentzel case II (requires a composition method) 
  }
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

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ModifiedWentzelElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
