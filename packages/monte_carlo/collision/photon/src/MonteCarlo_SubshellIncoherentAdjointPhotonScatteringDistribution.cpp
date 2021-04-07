//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SubshellIncoherentAdjointPhotonScatteringDistribution.cpp
//! \author Alex Robinson
//! \brief  The subshell incoherent adjoint photon scattering dist. decl.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <functional>

// FRENSIE Includes
#include "MonteCarlo_SubshellIncoherentAdjointPhotonScatteringDistribution.hpp"
#include "MonteCarlo_PhotonKinematicsHelpers.hpp"
#include "Utility_GaussKronrodIntegrator.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
SubshellIncoherentAdjointPhotonScatteringDistribution::SubshellIncoherentAdjointPhotonScatteringDistribution(
      const double max_energy,
      const Data::SubshellType interaction_subshell,
      const double num_electrons_in_subshell,
      const double binding_energy,
      const std::shared_ptr<const OccupationNumber>& occupation_number,
      const AdjointKleinNishinaSamplingType sampling_type )
  : IncoherentAdjointPhotonScatteringDistribution( max_energy, sampling_type ),
    d_subshell( interaction_subshell ),
    d_num_electrons_in_subshell( num_electrons_in_subshell ),
    d_binding_energy( binding_energy ),
    d_occupation_number( occupation_number )
{
  // Make sure the binding energy is valid
  testPrecondition( binding_energy > 0.0 );
  // Make sure the max energy is valid
  testPrecondition( max_energy > binding_energy );
  // Make sure the interaction subshell is valid
  testPrecondition( interaction_subshell != Data::INVALID_SUBSHELL );
  testPrecondition( interaction_subshell != Data::UNKNOWN_SUBSHELL );
  // Make sure the subshell occupancy is valid
  testPrecondition( num_electrons_in_subshell > 0.0 );
  // Make sure the occupation number is valid
  testPrecondition( occupation_number.get() );
  testPrecondition( occupation_number->getLowerBoundOfMomentum() ==
                    -1.0*Utility::Units::mec_momentum );
}

// Return the subshell
Data::SubshellType SubshellIncoherentAdjointPhotonScatteringDistribution::getSubshell() const
{
  return d_subshell;
}

// Return the number of electrons in the subshell
double SubshellIncoherentAdjointPhotonScatteringDistribution::getSubshellOccupancy() const
{
  return d_num_electrons_in_subshell;
}

// Return the binding energy
double SubshellIncoherentAdjointPhotonScatteringDistribution::getSubshellBindingEnergy() const
{
  return d_binding_energy;
}

// Evaluate the distribution
/*! \details The adjoint incoherent cross section (b) differential in the 
 * scattering angle cosine is returned from this function.
 */
double SubshellIncoherentAdjointPhotonScatteringDistribution::evaluate(
                                   const double incoming_energy,
                                   const double max_energy,
                                   const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( incoming_energy <= max_energy );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >=
                    calculateMinScatteringAngleCosine( incoming_energy, max_energy ) );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  double cross_section;

  

  if( this->isCrossSectionNonZero( incoming_energy,
                                   max_energy,
                                   scattering_angle_cosine ) )
  {
    const double adjoint_occupation_number =
      this->evaluateAdjointOccupationNumber( incoming_energy,
                                             max_energy,
                                             scattering_angle_cosine );
    
    const double diff_kn_cross_section =
      this->evaluateAdjointKleinNishinaDist( incoming_energy,
                                             max_energy,
                                             scattering_angle_cosine );

    cross_section = d_num_electrons_in_subshell*adjoint_occupation_number*
      diff_kn_cross_section;
  }
  else
    cross_section = 0.0;

  return cross_section;
}

// Evaluate the integrated cross section (b)
double SubshellIncoherentAdjointPhotonScatteringDistribution::evaluateIntegratedCrossSectionImpl(
                                                 const double incoming_energy,
                                                 const double max_energy,
                                                 const double precision ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( incoming_energy <= max_energy );

  // Evaluate the integrated cross section
  std::function<double (double x)> diff_cs_wrapper =
    std::bind<double>( (double (ThisType::*)(double,double,double)const)(&ThisType::evaluate),
                       std::cref( *this ),
                       incoming_energy,
                       max_energy,
                       std::placeholders::_1 );

  double abs_error, integrated_cs;

  Utility::GaussKronrodIntegrator<double> quadrature_gkq_int( precision );

  const double min_scattering_angle_cosine =
    MonteCarlo::calculateMinScatteringAngleCosine( incoming_energy,
                                                   max_energy );

  quadrature_gkq_int.integrateAdaptively<15>( diff_cs_wrapper,
                                              min_scattering_angle_cosine,
                                              1.0,
                                              integrated_cs,
                                              abs_error );

  // Make sure the integrated cross section is valid
  testPostcondition( integrated_cs >= 0.0 );

  return integrated_cs;
}

// Sample an outgoing energy and direction from the distribution
void SubshellIncoherentAdjointPhotonScatteringDistribution::sample(
                                        const double incoming_energy,
                                        double& outgoing_energy,
                                        double& scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( incoming_energy <= this->getMaxEnergy()-d_binding_energy );

  Counter trial_dummy;

  return this->sampleAndRecordTrials( incoming_energy,
                                      outgoing_energy,
                                      scattering_angle_cosine,
                                      trial_dummy );
}

// Sample an outgoing energy and direction and record the number of trials
void SubshellIncoherentAdjointPhotonScatteringDistribution::sampleAndRecordTrials(
                                               const double incoming_energy,
                                               double& outgoing_energy,
                                               double& scattering_angle_cosine,
                                               Counter& trials ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( incoming_energy <= this->getMaxEnergy()-d_binding_energy );
  remember( double min_scattering_angle_cosine =
            calculateMinScatteringAngleCosine( incoming_energy, this->getMaxEnergy() ) );

  const double max_adjoint_occupation_number =
    this->evaluateMaxAdjointOccupationNumber( incoming_energy,
                                              this->getMaxEnergy() );
  
  while( true )
  {
    this->sampleAndRecordTrialsAdjointKleinNishina( incoming_energy,
                                                    outgoing_energy,
                                                    scattering_angle_cosine,
                                                    trials );

    const double adjoint_occupation_number =
      this->evaluateAdjointOccupationNumber( incoming_energy,
                                             this->getMaxEnergy(),
                                             scattering_angle_cosine );

    const double scaled_random_number = max_adjoint_occupation_number*
      Utility::RandomNumberGenerator::getRandomNumber<double>();

    if( scaled_random_number <= adjoint_occupation_number )
      break;
  }

  // Make sure the scattering angle cosine is valid
  testPostcondition( scattering_angle_cosine >= min_scattering_angle_cosine );
  testPostcondition( scattering_angle_cosine <= 1.0 );
  // Make sure the adjoint Compton line energy is valid
  testPostcondition( outgoing_energy >= incoming_energy );
}

// Randomly scatter the photon and return the shell that was interacted with
void SubshellIncoherentAdjointPhotonScatteringDistribution::scatterAdjointPhoton(
                               AdjointPhotonState& adjoint_photon,
                               ParticleBank& bank,
                               Data::SubshellType& shell_of_interaction ) const
{
  // Make sure the adjoint photon energy is valid
  testPrecondition( adjoint_photon.getEnergy() <= this->getMaxEnergy() - d_binding_energy );

  // Generate probe particles
  this->createProbeParticles( adjoint_photon, bank );

  // Scattering the adjoint photon
  double outgoing_energy, scattering_angle_cosine;

  this->sample( adjoint_photon.getEnergy(),
                outgoing_energy,
                scattering_angle_cosine );

  shell_of_interaction = d_subshell;

  adjoint_photon.setEnergy( outgoing_energy );
  adjoint_photon.rotateDirection( scattering_angle_cosine,
                                  this->sampleAzimuthalAngle() );
}

// Check if an energy is above the scattering window
/*! \details An adjoint incoherent interaction can only occur when enough
 * energy is transferred to the electron to free it from its subshell. This
 * sets an upper limit for the window to energy_of_interest - binding_energy.
 */
bool SubshellIncoherentAdjointPhotonScatteringDistribution::isEnergyAboveScatteringWindow(
                                            const double energy_of_interest,
                                            const double initial_energy ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( initial_energy > 0.0 );
  // Make sure the energy of interest is valid
  testPrecondition( energy_of_interest >= 0.0 );
  testPrecondition( energy_of_interest <= this->getMaxEnergy() );

  return initial_energy > energy_of_interest - d_binding_energy;
}

// Check if the cross section is non-zero
bool SubshellIncoherentAdjointPhotonScatteringDistribution::isCrossSectionNonZero(
                                   const double incoming_energy,
                                   const double max_energy,
                                   const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( incoming_energy <= max_energy );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >=
                    calculateMinScatteringAngleCosine( incoming_energy, max_energy ) );
  testPrecondition( scattering_angle_cosine <= 1.0 );
  
  const double outgoing_energy =
    MonteCarlo::calculateAdjointComptonLineEnergy( incoming_energy,
                                                   scattering_angle_cosine );
  
  return outgoing_energy > d_binding_energy;
}    

// Evaluate the adjoint occupation number
double SubshellIncoherentAdjointPhotonScatteringDistribution::evaluateAdjointOccupationNumber(
                                   const double incoming_energy,
                                   const double max_energy,
                                   const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( incoming_energy <= max_energy );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >=
                    calculateMinScatteringAngleCosine( incoming_energy, max_energy ) );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  const double final_energy =
    MonteCarlo::calculateAdjointComptonLineEnergy( incoming_energy,
                                                   scattering_angle_cosine );

  if( final_energy < d_binding_energy )
  {
    FRENSIE_LOG_WARNING( "final energy " << final_energy << " less than "
                         "binding energy " << d_binding_energy << "!" );
    
    return 0.0;
  }
  else
  {
    const double pz_max =
      MonteCarlo::calculateMaxElectronMomentumProjection( final_energy,
                                                          d_binding_energy,
                                                          scattering_angle_cosine );
  
    return this->evaluateOccupationNumber( pz_max );
  }
}

// Evaluate the max adjoint occupation number
double SubshellIncoherentAdjointPhotonScatteringDistribution::evaluateMaxAdjointOccupationNumber(
                                                const double incoming_energy,
                                                const double max_energy ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( incoming_energy <= max_energy );

  const double min_scattering_angle_cosine = 
    MonteCarlo::calculateMinScatteringAngleCosine( incoming_energy,
                                                   max_energy );

  return this->evaluateAdjointOccupationNumber( incoming_energy,
                                                max_energy,
                                                min_scattering_angle_cosine );
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_SubshellIncoherentAdjointPhotonScatteringDistribution.cpp
//---------------------------------------------------------------------------//
