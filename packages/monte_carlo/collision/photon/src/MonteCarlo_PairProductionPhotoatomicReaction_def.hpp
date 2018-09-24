//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PairProductionPhotoatomicReaction_def.hpp
//! \author Alex Robinson
//! \brief  The pair production photoatomic reaction class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PAIR_PRODUCTION_PHOTOATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_PAIR_PRODUCTION_PHOTOATOMIC_REACTION_DEF_HPP

// Std Lib Includes
#include <math.h>

// FRENSIE Includes
#include "MonteCarlo_ElectronState.hpp"
#include "MonteCarlo_PositronState.hpp"
#include "MonteCarlo_KinematicHelpers.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_EquiprobableBinDistribution.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Initialize static member data
template<typename InterpPolicy, bool processed_cross_section>
std::unique_ptr<const Utility::FullyTabularBasicBivariateDistribution>
PairProductionPhotoatomicReaction<InterpPolicy,processed_cross_section>::s_secondary_energy_distribution( PairProductionPhotoatomicReaction<InterpPolicy,processed_cross_section>::initializeSecondaryEnergyDistribution() );

// Basic constructor
template<typename InterpPolicy, bool processed_cross_section>
PairProductionPhotoatomicReaction<InterpPolicy,processed_cross_section>::PairProductionPhotoatomicReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const bool use_detailed_electron_emission_physics )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index ),
    d_detailed_electron_emission_model( use_detailed_electron_emission_physics )
{
  this->initializeInteractionModels( use_detailed_electron_emission_physics );
}

// Constructor
template<typename InterpPolicy, bool processed_cross_section>
PairProductionPhotoatomicReaction<InterpPolicy,processed_cross_section>::PairProductionPhotoatomicReaction(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index,
       const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
       grid_searcher,
       const bool use_detailed_electron_emission_physics )
  : BaseType( incoming_energy_grid,
              cross_section,
              threshold_energy_index,
              grid_searcher ),
    d_detailed_electron_emission_model( use_detailed_electron_emission_physics )
{
  this->initializeInteractionModels( use_detailed_electron_emission_physics );
}

// Return the number of photons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned PairProductionPhotoatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedPhotons( const double energy ) const
{
  if( energy >= this->getThresholdEnergy() )
  {
    if( d_detailed_electron_emission_model )
      return 0u;
    else
      return 2u;
  }
  else
    return 0u;
}

// Return the number of electrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned PairProductionPhotoatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedElectrons( const double energy ) const
{
  if( energy >= this->getThresholdEnergy() )
  {
    return 1u;
  }
  else
    return 0u;
}

// Return the number of positrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned PairProductionPhotoatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedPositrons( const double energy ) const
{
  if( energy >= this->getThresholdEnergy() )
  {
    if( d_detailed_electron_emission_model )
      return 1u;
    else
      return 0u;
  }
  else
    return 0u;
}

// Return the reaction type
template<typename InterpPolicy, bool processed_cross_section>
PhotoatomicReactionType PairProductionPhotoatomicReaction<InterpPolicy,processed_cross_section>::getReactionType() const
{
  return PAIR_PRODUCTION_PHOTOATOMIC_REACTION;
}

// Simulate the reaction
template<typename InterpPolicy, bool processed_cross_section>
void PairProductionPhotoatomicReaction<InterpPolicy,processed_cross_section>::react(
				     PhotonState& photon,
				     ParticleBank& bank,
				     Data::SubshellType& shell_of_interaction ) const
{
  // Make sure it is energetically possible for this reaction to occur
  testPrecondition( photon.getEnergy() >= this->getThresholdEnergy() );

  d_interaction_model( photon, bank );

  // The shell of interaction, which will be important for triplet production
  // is currently ignored
  shell_of_interaction = Data::UNKNOWN_SUBSHELL;
}

// The basic pair production model
/*! \details Simplified Model: Assume that the outgoing electron is emitted at
 * the mean emission angle (theta_mean = m_e*c^2/E_mean), w.r.t the original
 * photon direction, with the mean emission energy (E_mean = E_kinetic/2).
 * The positron will also be emitted at the mean emission angle and with the
 * remaining energy (E_mean). It will be immediately annihilated but
 * the annihilation will not occur in-flight (isotropic emission of
 * annihilation photons in lab system).
 */
template<typename InterpPolicy, bool processed_cross_section>
void PairProductionPhotoatomicReaction<InterpPolicy,processed_cross_section>::basicInteraction(
							   PhotonState& photon,
							   ParticleBank& bank )
{
  std::shared_ptr<ParticleState> electron(
				     new ElectronState( photon, true, true ) );

  const double total_available_kinetic_energy = photon.getEnergy() -
    2*Utility::PhysicalConstants::electron_rest_mass_energy;

  const double mean_electron_kinetic_energy =
    total_available_kinetic_energy/2;

  double mean_emission_angle_cosine =
    cos( Utility::PhysicalConstants::electron_rest_mass_energy/
         mean_electron_kinetic_energy );

  double azimuthal_angle = 2*Utility::PhysicalConstants::pi*
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  electron->setEnergy( mean_electron_kinetic_energy );
  electron->rotateDirection( mean_emission_angle_cosine,
                             azimuthal_angle );

  bank.push( electron );

  // Change the photon's direction based on the initial direction of the
  // emitted positron (to conserve momentum we must rotate the
  // azimuthal angle by pi)
  azimuthal_angle = fmod( azimuthal_angle + Utility::PhysicalConstants::pi,
                          2*Utility::PhysicalConstants::pi );
  photon.rotateDirection( mean_emission_angle_cosine, azimuthal_angle );

  // Sample an isotropic outgoing angle for the annihilation photon
  double angle_cosine = -1.0 +
    2.0*Utility::RandomNumberGenerator::getRandomNumber<double>();

  // Sample the azimuthal angle
  azimuthal_angle = 2*Utility::PhysicalConstants::pi*
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  // Set the new energy
  photon.setEnergy( Utility::PhysicalConstants::electron_rest_mass_energy );

  // Set the new direction of the annihilation photon
  photon.rotateDirection( angle_cosine, azimuthal_angle );

  // Reset the collision number since this is technically a new photon
  photon.resetCollisionNumber();

  // Create the second annihilation photon
  std::shared_ptr<PhotonState> annihilation_photon(
				       new PhotonState( photon, true, true ) );

  // Reverse the direction of the second annihilation photon
  annihilation_photon->setDirection( -annihilation_photon->getXDirection(),
				     -annihilation_photon->getYDirection(),
				     -annihilation_photon->getZDirection() );

  // Bank the annihilation photon
  bank.push( annihilation_photon );

  // Increment the original photon generation number
  photon.incrementGenerationNumber();
}

// The detailed pair production model
/*! \todo Implement the full detailed pair production model.
 * \details Detailed Model: Sampling the outgoing electron/positron energy ratio
 * using an approximation of the Bethe-Heitler DCS which is independent of the
 * atomic number of the material (matches the MCNP sampling routine). The
 * electron/positron emission angles are sampled from a distribution based on
 * the leading term, ( 1 - beta cos(theta) )^-2, from high-energy theory.
 * Sampling the energy ratio with a random number of zero will not be allowed
 * since it return an energy ratio of zero, which is non-physical.
 */
template<typename InterpPolicy, bool processed_cross_section>
void PairProductionPhotoatomicReaction<InterpPolicy,processed_cross_section>::detailedInteraction(
							   PhotonState& photon,
							   ParticleBank& bank )
{
  // Increment the photon collision number
  photon.incrementCollisionNumber();

  // Set the photon as gone
  photon.setAsGone();

  // Create the electron and positron
  std::shared_ptr<ElectronState> electron( new ElectronState( photon, true, true ) );
  std::shared_ptr<ParticleState> positron( new PositronState( photon, true, true ) );

  // Incoming photon energy in rest mass units (m_e*c^2)
  double energy_in_mec = photon.getEnergy()/electron->getRestMassEnergy();

  // Max tabulated energy
  double max_tabulated_energy =
    s_secondary_energy_distribution->getUpperBoundOfPrimaryIndepVar();

  // Make sure energy is within tabulated range
  if ( energy_in_mec > max_tabulated_energy )
    energy_in_mec = max_tabulated_energy;

  // Get the total available kinetic energy
  double kinetic_energy = photon.getEnergy() - 2.0*electron->getRestMassEnergy();

  // Sample the positron/electron emission energy ratio
  double energy_ratio =
    s_secondary_energy_distribution->sampleSecondaryConditional( energy_in_mec );

  // Make sure the energy is valid
  testPostcondition( energy_ratio >= 0.0 );

  // // Find the lower photon energy index (k)
  // unsigned k = 1;
  // for ( unsigned i = 1; i < s_photon_energy_grid.size(); ++i )
  // {
  //   if( energy_in_mec >= s_photon_energy_grid[i] )
  //   {
  //     k = i;
  //     break;
  //   }
  // }

  // // Get the upper and lower energy difference
  // double upper_energy_diff = s_photon_energy_grid[k-1] - energy_in_mec;
  // double lower_energy_diff = energy_in_mec - s_photon_energy_grid[k];

  // // Get the scaled random number
  // double random_number =
  //   20*Utility::RandomNumberGenerator::getRandomNumber<double>() + 1.0;

  // // Get the lower parameter index of the random number (l)
  // unsigned l = floor( random_number );

  // // Get the difference between the random number and parameter index
  // double diff = random_number - l;

  // // Sample an outgoing electron/positron energy
  // double energy = kinetic_energy*(
  //   ( 1.0 - diff )*lower_energy_diff*s_outgoing_energy_ratio[ l ][k-1] +
  //   (    diff    )*lower_energy_diff*s_outgoing_energy_ratio[l+1][k-1] +
  //   ( 1.0 - diff )*upper_energy_diff*s_outgoing_energy_ratio[ l ][ k ] +
  //   (    diff    )*upper_energy_diff*s_outgoing_energy_ratio[l+1][ k ] )/
  //   ( s_photon_energy_grid[k-1] - s_photon_energy_grid[k] );

  // Randomly assign the energy to the positron or electron
  double electron_energy, positron_energy;
  if( Utility::RandomNumberGenerator::getRandomNumber<double>() > 0.5 )
  {
    electron_energy = kinetic_energy*( 1.0 - energy_ratio);
    positron_energy = kinetic_energy*energy_ratio;
  }
  else
  {
    electron_energy = kinetic_energy*energy_ratio;
    positron_energy = kinetic_energy*( 1.0 - energy_ratio);
  }

  // Sample the azimuthal angle
  double azimuthal_angle = 2*Utility::PhysicalConstants::pi*
    Utility::RandomNumberGenerator::getRandomNumber<double>();

  // Sample the electron polar angle
  double electron_angle = sampleEmittedPolarAngle( electron_energy );

  // Rotate the electron
  electron->rotateDirection( electron_angle, azimuthal_angle );

  // Set the electron energy
  if ( electron_energy > 0.0 )
    electron->setEnergy( electron_energy );
  else
  {
    electron->setEnergy( 1e-15 );
    electron->setAsGone();
  }

  // Sample a second polar angle at the electron energy
  double second_angle = sampleEmittedPolarAngle( electron_energy );

  // NOTE: If the electron angle cosine is exactly 1.0 then the ratio of sines
  // with be -inf. Therefore it will be assumed that the cosine is very close to
  // 1 but never 1 exactly.
  if ( electron_angle == 1.0 )
    electron_angle = 1.0 - 1e-12;

  // Negative ratio of the polar angle sines ( -sin(theta_2)/sin(theta_1) )
  double ratio_of_sines = -sqrt( ( 1.0 - second_angle*second_angle)/
                                 ( 1.0 - electron_angle*electron_angle) );

  // Angle parameter ( cos(theta_2) + sin(theta_2)*cot(theta_1) )
  double angle_parameter = second_angle - ratio_of_sines*electron_angle;

  // Calculate the positron direction
  double positron_x_direction = angle_parameter*electron->getXDirection() +
                           ratio_of_sines*positron->getXDirection();

  double positron_y_direction = angle_parameter*electron->getYDirection() +
                           ratio_of_sines*positron->getYDirection();

  double positron_z_direction = angle_parameter*electron->getZDirection() +
                           ratio_of_sines*positron->getZDirection();

  double norm_const = 1.0/sqrt( positron_x_direction*positron_x_direction +
                                positron_y_direction*positron_y_direction +
                                positron_z_direction*positron_z_direction );

  // Normalize the direction
  positron_x_direction = positron_x_direction*norm_const;
  positron_y_direction = positron_y_direction*norm_const;
  positron_z_direction = positron_z_direction*norm_const;

  positron->setDirection( positron_x_direction,
                          positron_y_direction,
                          positron_z_direction );

  // Make sure the positron energy is valid (else set below cutoff)
  if ( positron_energy > 0.0 )
    positron->setEnergy( positron_energy );
  else
    positron->setEnergy( 1e-15 );

  // Bank the positron and electron
  bank.push( electron );
  bank.push( positron );
}

// Sample the polar angle of the emitted electron/positron
/*! \details The sampling equation ( derived from Heitler, 1954; Motz et al.,
 *  1969 ) is given as:
 *  cos(theta) = ( 2 xi - 1 + beta )/( (2 xi - 1)beta + 1 )
 *  where xi is the random number and beta is the relativistic speed (v/c).
 *  MCNP modifies this by substituting (1 - xi) in for xi which gives:
 *  cos(theta) = ( 2 xi - 1 - beta )/( (2 xi - 1)beta - 1 )
 *  The MCNP version will be used for now.
 */
template<typename InterpPolicy, bool processed_cross_section>
double PairProductionPhotoatomicReaction<InterpPolicy,processed_cross_section>::sampleEmittedPolarAngle(
          const double energy )
{
  // Make sure the energy and random number are valid
  testPrecondition( energy >= 0.0 );

  // Get a random number
  double random_number = Utility::RandomNumberGenerator::getRandomNumber<double>();

  // Calculate beta of the electron/positron
  double beta;
  if( energy == 0.0 )
    beta = 0.0;
  else
  {
    beta = MonteCarlo::calculateDimensionlessRelativisticSpeed(
                Utility::PhysicalConstants::electron_rest_mass_energy, energy );
  }

  // Sample the polar angle cosine of the electron/positron
  double angle_cosine = ( 2.0*random_number      - 1.0 - beta )/
                        ( 2.0*random_number*beta - 1.0 - beta);

  // Make sure the angle cosine is within valid limits
  if ( angle_cosine < -1.0 )
    return -1.0;
  // Don't allow cos(theta) = 1 because it causes error when sampling the positron angle.
  if ( angle_cosine >= 1.0 )
    return 1.0;
  else
    return angle_cosine;
}

// Initialize interaction models
template<typename InterpPolicy, bool processed_cross_section>
void PairProductionPhotoatomicReaction<InterpPolicy,processed_cross_section>::initializeInteractionModels(
                            const bool use_detailed_electron_emission_physics )
{
  if( use_detailed_electron_emission_physics )
    d_interaction_model = detailedInteraction;
  else
    d_interaction_model = basicInteraction;
}

// Create the secondary energy distribution
/*! \details The outgoing electron/positron ratio of energy to max available
 * energy. The ratio is symmetric and thus is only given to 1/2 and is
 * independent of electron or positron. The ratios are found using
 * the Bethe-Heitler DCS which is fitted to be independent of the atomic
 * number of the material.
 */
template<typename InterpPolicy, bool processed_cross_section>
Utility::FullyTabularBasicBivariateDistribution*
PairProductionPhotoatomicReaction<InterpPolicy,processed_cross_section>::initializeSecondaryEnergyDistribution()
{
  // Set the energy grid
  std::vector<double> photon_energy_grid(
                       { 2.0, 3.0, 4.0, 6.0, 10.0, 20.0, 40.0, 80.0, 200.0 } );
  
  // Set the secondary distributions
  std::vector<std::shared_ptr<const Utility::TabularUnivariateDistribution> >
    secondary_dists( photon_energy_grid.size() );

  secondary_dists[0].reset( new Utility::EquiprobableBinDistribution(
                { .00000, .04245, .06816, .09196, .11495, .13762, .16023,
                  .18287, .20568, .22872, .25210, .27581, .29982, .32410,
                  .34863, .37338, .39836, .42358, .44894, .47443, .50000 } ) );

  secondary_dists[1].reset( new Utility::EquiprobableBinDistribution(
                { .00000, .04614, .07446, .10011, .12443, .14807, .17135,
                  .19441, .21735, .24027, .26323, .28629, .30944, .33274,
                  .35621, .37982, .40359, .42753, .45159, .47577, .50000 } ) );

  secondary_dists[2].reset( new Utility::EquiprobableBinDistribution(
                { .00000, .05237, .08217, .10857, .13336, .15727, .18069,
                  .20379, .22670, .24948, .27218, .29485, .31753, .34020,
                  .36288, .38560, .40838, .43123, .45413, .47705, .50000 } ) );

  secondary_dists[3].reset( new Utility::EquiprobableBinDistribution(
                { .00000, .05895, .09064, .11897, .14517, .16996, .19381,
                  .21699, .23967, .26204, .28417, .30614, .32793, .34962,
                  .37125, .39280, .41431, .43578, .45720, .47861, .50000 } ) );

  secondary_dists[4].reset( new Utility::EquiprobableBinDistribution(
                { .00000, .06325, .09752, .12696, .15390, .17918, .20330,
                  .22657, .24920, .27137, .29318, .31465, .33583, .35676,
                  .37751, .39813, .41864, .43907, .45943, .47973, .50000 } ) );

  secondary_dists[5].reset( new Utility::EquiprobableBinDistribution(
                { .00000, .06173, .09608, .12622, .15363, .17930, .20390,
                  .22764, .25049, .27275, .29454, .31587, .33692, .35772,
                  .37830, .39864, .41892, .43919, .45946, .47973, .50000 } ) );

  secondary_dists[6].reset( new Utility::EquiprobableBinDistribution(
                { .00000, .06496, .10020, .13011, .15717, .18221, .20625,
                  .22932, .25155, .27329, .29451, .31545, .33635, .35718,
                  .37777, .39812, .41850, .43887, .45925, .47962, .50000 } ) );

  secondary_dists[7].reset( new Utility::EquiprobableBinDistribution(
                { .00000, .05931, .09134, .12050, .14770, .17326, .19878,
                  .22301, .24600, .26904, .29120, .31248, .33318, .35403,
                  .37489, .39574, .41659, .43744, .45830, .47915, .50000 } ) );

  secondary_dists[8].reset( new Utility::EquiprobableBinDistribution(
                { .00000, .02500, .05000, .07500, .10000, .12500, .15000,
                  .17500, .20000, .22500, .25000, .27500, .30000, .32500,
                  .35000, .37500, .40000, .42500, .45000, .47500, .50000 } ) );
  
  // Create the distribution
  return new Utility::InterpolatedFullyTabularBasicBivariateDistribution<Utility::Correlated<Utility::LinLinLin> >(
                                                          photon_energy_grid,
                                                          secondary_dists );
}

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( PairProductionPhotoatomicReaction<Utility::LinLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( PairProductionPhotoatomicReaction<Utility::LinLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( PairProductionPhotoatomicReaction<Utility::LinLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( PairProductionPhotoatomicReaction<Utility::LinLog,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( PairProductionPhotoatomicReaction<Utility::LogLin,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( PairProductionPhotoatomicReaction<Utility::LogLin,true> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( PairProductionPhotoatomicReaction<Utility::LogLog,false> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( PairProductionPhotoatomicReaction<Utility::LogLog,true> );

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PAIR_PRODUCTION_PHOTOATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PairProductionPhotoatomicReaction_def.hpp
//---------------------------------------------------------------------------//
