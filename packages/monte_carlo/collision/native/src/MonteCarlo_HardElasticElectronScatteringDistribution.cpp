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

namespace MonteCarlo{

//! Constructor
HardElasticElectronScatteringDistribution::HardElasticElectronScatteringDistribution(
ElasticDistribution& elastic_scattering_distribution,
//const Teuchos::RCP<double>& interpolation_weights )
WeightArray& interpolation_weights )
  : d_elastic_scattering_distribution( elastic_scattering_distribution ),
    d_interpolation_weights( interpolation_weights )
{
  // Make sure the array is valid
  testPrecondition( d_elastic_scattering_distribution.size() > 0 );
}

//! Randomly scatter the electron
void HardElasticElectronScatteringDistribution::scatterElectron( 
                                ElectronState& electron,
			                    ParticleBank& bank) const
{
  double scattering_angle_cosine;

  scattering_angle_cosine = sampleTwoDDistribution( electron.getEnergy(), 
                                            d_elastic_scattering_distribution );

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
// end MonteCarlo_HardElasticElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
