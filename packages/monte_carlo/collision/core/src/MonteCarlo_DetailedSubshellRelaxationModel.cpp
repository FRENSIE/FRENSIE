//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DetailedSubshellRelaxationModel.cpp
//! \author Alex Robinson
//! \brief  Detailed subshell relaxation model class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_DetailedSubshellRelaxationModel.hpp"
#include "MonteCarlo_SimulationElectronProperties.hpp"
#include "MonteCarlo_SimulationPhotonProperties.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
DetailedSubshellRelaxationModel::DetailedSubshellRelaxationModel(
       const Data::SubshellType vacancy_subshell,
       const std::vector<Data::SubshellType>& primary_transition_vacancy_shells,
       const std::vector<Data::SubshellType>& secondary_transition_vacancy_shells,
       const std::vector<double>& outgoing_particle_energies,
       const std::vector<double>& transition_pdf_or_cdf,
       const bool interpret_as_cdf )
  : SubshellRelaxationModel( vacancy_subshell ),
    d_transition_distribution(),
    d_outgoing_particle_energies( outgoing_particle_energies ),
    d_transition_vacancy_shells( primary_transition_vacancy_shells.size() )
{
  // Make sure the vacancy subshell is valid
  testPrecondition( vacancy_subshell != Data::INVALID_SUBSHELL );
  testPrecondition( vacancy_subshell !=Data::UNKNOWN_SUBSHELL );
  // Make sure the arrays are valid
  testPrecondition( primary_transition_vacancy_shells.size() > 0 );
  testPrecondition( secondary_transition_vacancy_shells.size() ==
		    primary_transition_vacancy_shells.size() );
  testPrecondition( outgoing_particle_energies.size() ==
		    primary_transition_vacancy_shells.size() );
  testPrecondition( transition_pdf_or_cdf.size() ==
		    primary_transition_vacancy_shells.size() );

  // Create the transition distribution
  std::vector<double> dummy_indep_values( transition_pdf_or_cdf.size() );

  d_transition_distribution.reset( new Utility::DiscreteDistribution(
						         dummy_indep_values,
						         transition_pdf_or_cdf,
							 interpret_as_cdf ) );

  // Store the transition vacancy shells
  for( unsigned i = 0; i < primary_transition_vacancy_shells.size(); ++i )
  {
    Utility::get<0>( d_transition_vacancy_shells[i] ) =
      primary_transition_vacancy_shells[i];
    Utility::get<1>( d_transition_vacancy_shells[i] ) =
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
 * be set to Data::INVALID_SUBSHELL). In a non-radiative the secondary vacancy shell
 * corresponds to the shell where the Auger electron is actually emitted from.
 * \todo Determine whether incrementing the collision number and/or generation
 * number is appropriate.
 */
void DetailedSubshellRelaxationModel::relaxSubshell(
			const ParticleState& particle,
                        const double min_photon_energy,
                        const double min_electron_energy,
                        ParticleBank& bank,
                        Data::SubshellType& new_primary_vacancy_shell,
		        Data::SubshellType& new_secondary_vacancy_shell ) const
{
  // Sample the transition that occurs
  size_t transition_index;

  d_transition_distribution->sampleAndRecordBinIndex( transition_index );

  double new_particle_energy = d_outgoing_particle_energies[transition_index];

  // Set the new vacancies shells
  new_primary_vacancy_shell =
    Utility::get<0>( d_transition_vacancy_shells[transition_index] );

  new_secondary_vacancy_shell =
    Utility::get<1>( d_transition_vacancy_shells[transition_index] );

  // A secondary transition will only occur with Auger electron emission
  if( new_secondary_vacancy_shell == Data::INVALID_SUBSHELL ||
      new_secondary_vacancy_shell == Data::UNKNOWN_SUBSHELL )
  {
    if( new_particle_energy >= min_photon_energy )
      this->generateFluorescencePhoton( particle, new_particle_energy, bank );
  }
  else
  {
    if( new_particle_energy >= min_electron_energy )
      this->generateAugerElectron( particle, new_particle_energy, bank );
  }
}

// Generate a fluorescence photon
void DetailedSubshellRelaxationModel::generateFluorescencePhoton(
						const ParticleState& particle,
					        const double new_photon_energy,
						ParticleBank& bank ) const
{
  // Make sure the new energy is valid
  testPrecondition( new_photon_energy > 0.0 );

  std::shared_ptr<ParticleState> fluorescence_photon(
				     new PhotonState( particle, true, true ) );

  // Set the new energy
  fluorescence_photon->setEnergy( new_photon_energy );
  
  double angle_cosine, azimuthal_angle;
  
  this->sampleEmissionDirection( angle_cosine, azimuthal_angle );
  
  // Set the new direction
  fluorescence_photon->rotateDirection( angle_cosine, azimuthal_angle );
  
  // Bank the relaxation particle
  bank.push( fluorescence_photon );
}

// Generate an Auger electron
void DetailedSubshellRelaxationModel::generateAugerElectron(
					      const ParticleState& particle,
					      const double new_electron_energy,
					      ParticleBank& bank ) const
{
  // Make sure the new energy is valid - surprisingly, 0.0 can appear in the
  // table
  testPrecondition( new_electron_energy >= 0.0 );

  std::shared_ptr<ParticleState> auger_electron(
				   new ElectronState( particle, true, true ) );

  // Set the new energy
  auger_electron->setEnergy( new_electron_energy );
  
  double angle_cosine, azimuthal_angle;
  
  this->sampleEmissionDirection( angle_cosine, azimuthal_angle );
  
  // Set the new direction
  auger_electron->rotateDirection( angle_cosine, azimuthal_angle );
  
  // Bank the relaxation particle
  bank.push( auger_electron );
}

// Sample emission direction
void DetailedSubshellRelaxationModel::sampleEmissionDirection(
					        double& angle_cosine,
						double& azimuthal_angle ) const
{
  // Sample an isotropic outgoing angle cosine for the relaxation particle
  angle_cosine = -1.0 +
    2.0*Utility::RandomNumberGenerator::getRandomNumber<double>();

  // Sample the azimuthal angle
  azimuthal_angle = 2.0*Utility::PhysicalConstants::pi*
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  // Make sure the scattering angle cosine is valid
  testPostcondition( angle_cosine >= -1.0 );
  testPostcondition( angle_cosine <= 1.0 );
  // Make sure the azimuthal angle is valid
  testPostcondition( azimuthal_angle >= 0.0 );
  testPostcondition( azimuthal_angle <= 2*Utility::PhysicalConstants::pi );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_Detailed SubshellRelaxationModel.cpp
//---------------------------------------------------------------------------//
