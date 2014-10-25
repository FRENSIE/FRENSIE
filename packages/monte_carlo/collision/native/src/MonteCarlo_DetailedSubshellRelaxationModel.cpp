//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DetailedSubshellRelaxationModel.cpp
//! \author Alex Robinson
//! \brief  Detailed subshell relaxation model class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_DetailedSubshellRelaxationModel.hpp"
#include "MonteCarlo_SimulationProperties.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_DirectionHelpers.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
DetailedSubshellRelaxationModel::DetailedSubshellRelaxationModel( 
       const SubshellType vacancy_subshell,
       const Teuchos::Array<SubshellType>& primary_transition_vacancy_shells,
       const Teuchos::Array<SubshellType>& secondary_transition_vacancy_shells,
       const Teuchos::Array<double>& outgoing_particle_energies,
       const Teuchos::Array<double>& transition_cdf )
  : SubshellRelaxationModel( vacancy_subshell ),
    d_transition_distribution(),
    d_transition_vacancy_shells( primary_transition_vacancy_shells.size() );
{
  // Make sure the arrays are valid
  testPrecondition( primary_transition_vacancy_shells.size() > 0 );
  testPrecondition( secondary_transition_vacancy_shells.size() == 
		    primary_transition_vacancy_shells.size() );
  testPrecondition( outgoing_particle_energies.size() ==
		    primary_transition_vacancy_shells.size() );
  testPrecondition( transition_cdf.size() ==
		    primary_transition_vacancy_shells.size() );

  // Create the transition distribution
  d_transition_distribution.reset( new Utility::DiscreteDistribution(
						    outgoing_particle_energies,
						    transition_cdf,
						    true ) );

  // Store the transition vacancy shells
  for( unsigned i = 0; i < primary_transition_vacancy_shells.size(); ++i )
  {
    d_transition_vacancy_shells[i].first = 
      primary_transition_vacancy_shells[i];
    d_transition_vacancy_shells[i].second = 
      secondary_transition_vacancy_shells[i];
  }
}

// Relax the shell
/*! \details The particle must be passed so that its position, history number,
 * collision number and generation number can be copied. The relaxation
 * photon or electron that is created will be banked. The new primary vacancy
 * shell corresponds to the shell that the current vacancy moves to. The
 * new secondary vacancy shell corresponds to a new vacancy that is created
 * in the transition. In a radiative transition, the vacancy only moves - no
 * new vacancies are created (the new secondary vacancy shell will always
 * be set to INVALID_SUBSHELL). In a non-radiative the secondary vacancy shell 
 * corresponds to the shell where the Auger electron is actually emitted from.
 * \todo Bank electrons that are emitted.
 * \todo Determine whether incrementing the collision number and/or generation
 * number is appropriate.
 */ 
void DetailedSubshellRelaxationModel::relaxSubshell( 
			      const ParticleState& particle,
			      ParticleBank& bank,
			      SubshellType& new_primary_vacancy_shell,
		              SubshellType& new_secondary_vacancy_shell ) const
{
  // Sample the transition that occurs
  unsigned transition_index;
  double new_particle_energy =
    d_transition_distribution->sample( transition_index );

  // Set the new vacancies shells
  new_primary_vacancy_shell = 
    d_transition_vacancy_shells[transition_index].first;
  
  new_secondary_vacancy_shell = 
    d_transition_vacancy_shells[transition_index].second;

  // Create the new particle (only photons currently)
  if( new_secondary_vacancy_shell == INVALID_SUBSHELL )
  {
    // Only create the new particle if it is above the cutoff energy
    if( new_particle_energy >= SimulationProperties::getMinPhotonEnergy() )
    {
      Teuchos::RCP<ParticleState> relaxation_particle(
				     new PhotonState( particle, true, true ) );

      // Sample an isotropic outgoing angle cosine for the relaxation particle
      double angle_cosine = -1.0 + 
	2.0*Utility::RandomNumberGenerator::getRandomNumber<double>();

      // Sample the azimuthal angle
      double azimuthal_angle = 2*Utility::PhysicalConstants::pi*
	2.0*Utility::RandomNumberGenerator::getRandomNumber<double>();

      double outgoing_direction[3];

      Utility::rotateDirectionThroughPolarAndAzimuthalAngle( 
							 angle_cosine,
							 azimuthal_angle,
							 photon.getDirection(),
							 outgoing_direction );
    
      // Set the new energy
      relaxation_particle.setEnergy( new_particle_energy );
      
      // Set the new direction
      relaxation_particle.setDirection( outgoing_direction );
      
      // Bank the relaxation particle
      bank.push( relaxation_particle );
    }
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_Detailed SubshellRelaxationModel.cpp
//---------------------------------------------------------------------------//
