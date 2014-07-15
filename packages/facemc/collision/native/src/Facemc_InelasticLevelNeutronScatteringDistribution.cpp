//---------------------------------------------------------------------------//
//!
//! \file   Facemc_InelasticLevelNeutronScatteringDistribution.cpp
//! \author Alex Bennett
//! \brief  The inelastic level scattering distribution class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <math.h>

// FRENSIE Includes
#include "Facemc_InelasticLevelNeutronScatteringDistribution.hpp"
#include "Utility_DirectionHelpers.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_SortAlgorithms.hpp"

namespace Facemc{

// Constructor
/*! \details param_a = (A+1)/A * |Q| and param_b = (A/(A+1))^2
 */
InelasticLevelNeutronScatteringDistribution::InelasticLevelNeutronScatteringDistribution( 
                      const double atomic_weight_ratio,
		      const double param_a,
		      const double param_b,
		      const Teuchos::RCP<NeutronScatteringAngularDistribution>&
		      angular_scattering_distribution )
   : NeutronScatteringDistribution( atomic_weight_ratio ),
     d_param_a( param_a ),
     d_param_b( param_b ),
     d_angular_scattering_distribution( angular_scattering_distribution )
{
  // Check to make sure param_a and param b are greater then 0
  testPrecondition( param_a > 0 );
  testPrecondition( param_b > 0 );
  // Check to make sure the angular distribution pointer is valid
  testPrecondition( !angular_scattering_distribution.is_null() );
  // Make sure the angular distribution is in the CM
  testPrecondition( angular_scattering_distribution->isCMDistribution() );    
}

// Randomly scatter the neutron
void InelasticLevelNeutronScatteringDistribution::scatterNeutron(NeutronState& neutron,
                                                                 const double temperature ) const
{

   // Calculate the outgoing energy for the center of mass frame
   double cm_energy = d_param_b * ( neutron.getEnergy() - d_param_a);

   // Sample the scattering angle for the center of mass frame
   double cm_scatter_angle_cosine = 
     d_angular_scattering_distribution->sampleAngleCosine( neutron.getEnergy());
   
   // Get the atomic ratio
   double atom_ratio_plus_1 = 1.0 + getAtomicWeightRatio(); 

   // Calculate the outgoing energy for the lab frame
   double energy = cm_energy + ( neutron.getEnergy() + 
				 2.0 * cm_scatter_angle_cosine * 
				 ( atom_ratio_plus_1 ) *
				 sqrt( neutron.getEnergy() * cm_energy ) ) / 
     ( atom_ratio_plus_1 * atom_ratio_plus_1 );

   // Calculate the scattering angle for the lab frame
   double scatter_angle_cosine = cm_scatter_angle_cosine * 
     sqrt( cm_energy / energy ) +
     1.0/( atom_ratio_plus_1 ) * sqrt( neutron.getEnergy() / energy );

   // Rotate the neutron to the new angle
   double outgoing_neutron_direction[3];

   Utility::rotateDirectionThroughPolarAndAzimuthalAngle(
						  scatter_angle_cosine,
						  sampleAzimuthalAngle(),
						  neutron.getDirection(),
						  outgoing_neutron_direction );

   // Store the new energy
   neutron.setEnergy( energy );

   // Store the new direction
   neutron.setDirection( outgoing_neutron_direction );
}

} // End Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_ElasticNeutronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
