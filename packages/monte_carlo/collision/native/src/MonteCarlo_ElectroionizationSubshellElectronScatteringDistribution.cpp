//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroionizationSubshellElectronScatteringDistribution.cpp
//! \author Luke Kersting
//! \brief  The electron subshell electroionization scattering distribution definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistribution.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_KinematicHelpers.hpp"

namespace MonteCarlo{
// Constructor
ElectroionizationSubshellElectronScatteringDistribution::ElectroionizationSubshellElectronScatteringDistribution(
    const ElectroionizationSubshellDistribution&
      electroionization_subshell_scattering_distribution,
    const double& binding_energy )
  : d_electroionization_subshell_scattering_distribution(
      electroionization_subshell_scattering_distribution ),
    d_binding_energy( binding_energy )
{
  // Make sure the arraies are valid
  testPrecondition( d_electroionization_subshell_scattering_distribution.size() > 0 );
}

// Return the binding energy
double ElectroionizationSubshellElectronScatteringDistribution::getBindingEnergy() const
{
  return d_binding_energy;
}

// Return the max secondary (knock-on) electron energy for a given incoming electron energy
double ElectroionizationSubshellElectronScatteringDistribution::getMaxSecondaryEnergyAtIncomingEnergy(
        const double energy ) const
{
  if ( energy > this->getBindingEnergy() )
    return 0.5*( energy - this->getBindingEnergy() );
  else
    return 0.0;
}

// Evaluate the PDF value for a given incoming and outgoing energy (efficient)
/*! \details The outgoing energy can either be for the primary or secondary
 * (knock-on) electron. The primary scattered electron and secondary knock-on
 * electron are indistinguishable and by convention the one with lower energy
 * is considered the knock-on electron. To reduce space, the tabulated data
 * only gives pdf values up to the max allowable knock-on energy (+- roundoff),
 * which is given as: 1/2(incoming energy - binding energy). 
 */
double ElectroionizationSubshellElectronScatteringDistribution::evaluatePDF(
                    const unsigned lower_bin_index,
                    const double incoming_energy,
                    const double outgoing_energy_1 ) const
{
  // Make sure the energies are valid
  testPrecondition( lower_bin_index >= 0 );
  testPrecondition( lower_bin_index <
                    d_electroionization_subshell_scattering_distribution.size() );
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( outgoing_energy_1  > 0.0 );

  // calcualte the energy of the second outgoing electron
  double outgoing_energy_2 = incoming_energy - outgoing_energy_1 - this->getBindingEnergy();

  if ( outgoing_energy_2 <= 0.0 )
    return 0.0;

  // Assume the lower of the two outgoing energies is the knock-on electron
  double knock_on_energy = std::min( outgoing_energy_1, outgoing_energy_2 );

  ElectroionizationSubshellDistribution::const_iterator 
    lower_distribution = d_electroionization_subshell_scattering_distribution.begin();

  std::advance( lower_distribution, lower_bin_index );

  // get the max physically allowed knock-on energy for the lower distribution
  double physical_max_knock_on_energy =
    this->getMaxSecondaryEnergyAtIncomingEnergy( Utility::get<0>(*lower_distribution) );

  // get the max tabulated knock-on energy for the lower distribution
  double tabulated_max_knock_on_energy =
    Utility::get<1>(*lower_distribution)->sampleWithRandomNumber( 1.0 );

  /* Due to roundoff errors in the tabulated data the physically allowable max
   * knock-on energy can be slightly higher than the max tabulated one. If the
   * given knock-on energy falls between these two values it is set to the max
   * tabulated knock-on energy to ensure that an unrealistic value of zero is
   * not returned for the pdf.
   */
  double lower_knock_on_energy = knock_on_energy;
  if( knock_on_energy <= physical_max_knock_on_energy &&
      knock_on_energy > tabulated_max_knock_on_energy )
  {
    lower_knock_on_energy = tabulated_max_knock_on_energy;
  }

  if( Utility::get<0>(*lower_distribution) != incoming_energy )
  {
    ElectroionizationSubshellDistribution::const_iterator upper_distribution = lower_distribution;
    ++upper_distribution;

    // get the max physically allowed knock-on energy for the upper distribution
    physical_max_knock_on_energy =
      this->getMaxSecondaryEnergyAtIncomingEnergy( Utility::get<0>(*upper_distribution) );

    // get the max tabulated knock-on energy for the upper distribution
    tabulated_max_knock_on_energy =
      Utility::get<1>(*upper_distribution)->sampleWithRandomNumber( 1.0 );

    double upper_knock_on_energy = knock_on_energy;
    if( knock_on_energy <= physical_max_knock_on_energy &&
        knock_on_energy > tabulated_max_knock_on_energy )
    {
      upper_knock_on_energy = tabulated_max_knock_on_energy;
    }

    return InterpolationPolicy::interpolate(
      Utility::get<0>(*lower_distribution),
      Utility::get<0>(*upper_distribution),
      incoming_energy,
      Utility::get<1>(*lower_distribution)->evaluatePDF(lower_knock_on_energy),
      Utility::get<1>(*upper_distribution)->evaluatePDF(upper_knock_on_energy) );
  }
  else
    return Utility::get<1>(*lower_distribution)->evaluatePDF( lower_knock_on_energy );
}

// Evaluate the PDF value for a given incoming and outgoing energy
/*! \details The outgoing energy can either be for the primary or secondary
 * (knock-on) electron. The primary scattered electron and secondary knock-on
 * electron are indistinguishable and by convention the one with lower energy
 * is considered the knock-on electron. To reduce space, the tabulated data
 * only gives pdf values up to the max allowable knock-on energy (+- roundoff),
 * which is given as: 1/2(incoming energy - binding energy). 
 */
double ElectroionizationSubshellElectronScatteringDistribution::evaluatePDF(
                     const double incoming_energy,
                     const double outgoing_energy_1 ) const
{
  // Make sure the energies are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( outgoing_energy_1 > 0.0 );
  testPrecondition( incoming_energy > outgoing_energy_1 );

  // calcualte the energy of the second outgoing electron
  double outgoing_energy_2 = incoming_energy - outgoing_energy_1 - this->getBindingEnergy();

  if ( outgoing_energy_2 <= 0.0 )
    return 0.0;

  // Assume the lower of the two outgoing energies is the knock-on electron
  double knock_on_energy = std::min( outgoing_energy_1, outgoing_energy_2 );

  ElectroionizationSubshellDistribution::const_iterator lower_distribution,
                                                        upper_distribution;

  MonteCarlo::findLowerAndUpperBinBoundary(
    incoming_energy,
    d_electroionization_subshell_scattering_distribution,
    lower_distribution,
    upper_distribution );

  // get the max physically allowed knock-on energy for the lower distribution
  double physical_max_knock_on_energy =
    this->getMaxSecondaryEnergyAtIncomingEnergy( Utility::get<0>(*lower_distribution) );

  // get the max tabulated knock-on energy for the lower distribution
  double tabulated_max_knock_on_energy =
    Utility::get<1>(*lower_distribution)->sampleWithRandomNumber( 1.0 );

  /* Due to roundoff errors in the tabulated data the physically allowable max
   * knock-on energy can be slightly higher than the max tabulated one. If the
   * given knock-on energy falls between these two values it is set to the max
   * tabulated knock-on energy to ensure that an unrealistic value of zero is
   * not returned for the pdf.
   */
  double lower_knock_on_energy = knock_on_energy;
  if( knock_on_energy <= physical_max_knock_on_energy &&
      knock_on_energy > tabulated_max_knock_on_energy )
  {
    lower_knock_on_energy = tabulated_max_knock_on_energy;
  }

  if( lower_distribution != upper_distribution )
  {
    // get the max physically allowed knock-on energy for the upper distribution
    physical_max_knock_on_energy =
      this->getMaxSecondaryEnergyAtIncomingEnergy( Utility::get<0>(*upper_distribution) );

    // get the max tabulated knock-on energy for the upper distribution
    tabulated_max_knock_on_energy =
      Utility::get<1>(*upper_distribution)->sampleWithRandomNumber( 1.0 );

    double upper_knock_on_energy = knock_on_energy;
    if( knock_on_energy <= physical_max_knock_on_energy &&
        knock_on_energy > tabulated_max_knock_on_energy )
    {
      upper_knock_on_energy = tabulated_max_knock_on_energy;
    }

    return InterpolationPolicy::interpolate(
            Utility::get<0>(*lower_distribution),
            Utility::get<0>(*upper_distribution),
            incoming_energy,
            Utility::get<1>(*lower_distribution)->evaluatePDF( lower_knock_on_energy ),
            Utility::get<1>(*upper_distribution)->evaluatePDF( upper_knock_on_energy ) );
  }
  else
    return Utility::get<1>(*lower_distribution)->evaluatePDF( lower_knock_on_energy );

}

// Sample an knock on energy and direction from the distribution
void ElectroionizationSubshellElectronScatteringDistribution::sample(
               const double incoming_energy,
               double& knock_on_energy,
               double& knock_on_angle_cosine ) const
{
  // Sample knock-on electron energy
  knock_on_energy =
    sampleTwoDDistributionCorrelated<ElectroionizationSubshellDistribution>(
                         incoming_energy,
                         d_electroionization_subshell_scattering_distribution );

  // Calculate the outgoing angle cosine for the knock on electron
  knock_on_angle_cosine = outgoingAngle( incoming_energy,
                                         knock_on_energy );
}

// Sample an knock on energy and direction from the distribution
void ElectroionizationSubshellElectronScatteringDistribution::sample(
               const double incoming_energy,
               double& outgoing_energy,
               double& knock_on_energy,
               double& scattering_angle_cosine,
               double& knock_on_angle_cosine ) const
{
  // Sample knock-on electron energy and outgoing angle
  sample( incoming_energy, knock_on_energy, knock_on_angle_cosine );

  outgoing_energy =
        std::max( 1e-15, incoming_energy - knock_on_energy - d_binding_energy );

  // Calculate the outgoing angle cosine for the primary electron
  scattering_angle_cosine = outgoingAngle( incoming_energy,
                                           outgoing_energy );
}

// Sample an knock on energy and direction and record the number of trials
void ElectroionizationSubshellElectronScatteringDistribution::sampleAndRecordTrials(
                              const double incoming_energy,
                              double& knock_on_energy,
                              double& knock_on_angle_cosine,
                              unsigned& trials ) const
{
  trials++;

  sample( incoming_energy, knock_on_energy, knock_on_angle_cosine );
}

// Randomly scatter the electron
void ElectroionizationSubshellElectronScatteringDistribution::scatterElectron(
                                ElectronState& electron,
			                    ParticleBank& bank,
                                Data::SubshellType& shell_of_interaction ) const
{
  // The energy of the outgoing and knock-on electron
  double outgoing_energy, knock_on_energy;

  // The angle cosine of the outgoing and knock-on electron
  double scattering_angle_cosine, knock_on_angle_cosine;

  // Sample the distribution
  sample( electron.getEnergy(),
          outgoing_energy,
          knock_on_energy,
          scattering_angle_cosine,
          knock_on_angle_cosine );

  // Create new elecrton
  Teuchos::RCP<ElectronState> knock_on_electron(
                           new ElectronState( electron, true, true ) );

  // Set knock-on electron energy
  knock_on_electron->setEnergy( knock_on_energy );


  // Set the direction of the knock-on electron
  knock_on_electron->rotateDirection( knock_on_angle_cosine,
			                          this->sampleAzimuthalAngle() );

  // Bank the knock-on electron
  bank.push( knock_on_electron );


  // Set the outgoing electron energy
  electron.setEnergy( outgoing_energy );

  // Set the new direction of the primary electron
  electron.rotateDirection( scattering_angle_cosine,
                            this->sampleAzimuthalAngle() );

  // Increment the electron generation number
  electron.incrementGenerationNumber();
}

// Calculate the outgoing angle cosine
double ElectroionizationSubshellElectronScatteringDistribution::outgoingAngle(
                                            const double incoming_energy,
                                            const double outgoing_energy ) const
{
  // The normalized incoming electron energy
  double normalized_incoming_energy =
          incoming_energy/Utility::PhysicalConstants::electron_rest_mass_energy;

  // The ratio of incoming to outgoing energy
  double energy_ratio = outgoing_energy/incoming_energy;

  // Randomly select the plane of scattering
  return sqrt( energy_ratio*( normalized_incoming_energy + 2.0 )/
             ( energy_ratio*normalized_incoming_energy + 2.0 ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationElectronScatteringDistribution.cpp
//---------------------------------------------------------------------------//
