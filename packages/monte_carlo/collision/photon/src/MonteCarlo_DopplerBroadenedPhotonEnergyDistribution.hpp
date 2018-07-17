//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DopplerBroadenedPhotonEnergyDistribution.hpp
//! \author Alex Robinson
//! \brief  The Doppler broadened photon energy distribution declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP
#define MONTE_CARLO_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "Data_SubshellType.hpp"
#include "MonteCarlo_PhotonKinematicsHelpers.hpp"
#include "MonteCarlo_ComptonProfile.hpp"
#include "Utility_DistributionTraits.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_MeCMomentumUnit.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

//! The Doppler broadened photon energy distribution class
class DopplerBroadenedPhotonEnergyDistribution
{

public:

  //! The trials counter type
  typedef Utility::DistributionTraits::Counter Counter;
  
  //! Constructor
  DopplerBroadenedPhotonEnergyDistribution()
  { /* ... */ }

  //! Destructor
  virtual ~DopplerBroadenedPhotonEnergyDistribution()
  { /* ... */ }

  //! Check if the distribution is complete (all subshells)
  virtual bool isComplete() const = 0;

  //! Evaluate the distribution with electron momentum projection
  virtual double evaluateWithElectronMomentumProjection(
                              const double incoming_energy,
                              const double electron_momentum_projection,
                              const double scattering_angle_cosine ) const = 0;

  //! Evaluate the distribution
  double evaluate( const double incoming_energy,
                   const double outgoing_energy,
                   const double scattering_angle_cosine ) const;

  //! Evaluate the exact distribution
  virtual double evaluateExact(
                              const double incoming_energy,
                              const double outgoing_energy,
                              const double scattering_angle_cosine ) const = 0;

  //! Evaluate the PDF with electron momentum projection
  virtual double evaluatePDFWithElectronMomentumProjection(
                                     const double incoming_energy,
                                     const double electron_momentum_projection,
                                     const double scattering_angle_cosine,
                                     const double precision ) const = 0;

  //! Evaluate the PDF with electron momentum projection
  double evaluatePDFWithElectronMomentumProjection(
                                  const double incoming_energy,
                                  const double electron_momentum_projection,
                                  const double scattering_angle_cosine ) const;

  //! Evaluate the PDF
  double evaluatePDF( const double incoming_energy,
                      const double outgoing_energy,
                      const double scattering_angle_cosine,
                      const double precision = 1e-3 ) const;

  //! Evaluate the exact PDF
  virtual double evaluatePDFExact( const double incoming_energy,
                                   const double outgoing_energy,
                                   const double scattering_angle_cosine,
                                   const double precision ) const = 0;

  //! Evaluate the exact PDF with a precision
  double evaluatePDFExact( const double incoming_energy,
                           const double outgoing_energy,
                           const double scattering_angle_cosine ) const;

  //! Evaluate the integrated cross section (b/mu)
  virtual double evaluateIntegratedCrossSection(
                                          const double incoming_energy,
                                          const double scattering_angle_cosine,
                                          const double precision ) const = 0;
  
  //! Evaluate the exact integrated cross section (b/mu)
  virtual double evaluateIntegratedCrossSectionExact( 
			             const double incoming_energy,
                                     const double scattering_angle_cosine,
                                     const double precision ) const = 0;

  //! Sample an outgoing energy from the distribution
  virtual void sample( const double incoming_energy,
		       const double scattering_angle_cosine,
		       double& outgoing_energy,
		       Data::SubshellType& shell_of_interaction ) const = 0;

  //! Sample an outgoing energy and record the number of trials
  virtual void sampleAndRecordTrials(
				const double incoming_energy,
				const double scattering_angle_cosine,
				double& outgoing_energy,
				Data::SubshellType& shell_of_interaction,
				Counter& trials ) const = 0;

  //! Sample an electron momentum projection and record the number of trials
  virtual void sampleMomentumAndRecordTrials(
                                      const double incoming_energy,
                                      const double scattering_angle_cosine,
                                      double& electron_momentum_projection,
                                      Data::SubshellType& shell_of_interaction,
                                      Counter& trials ) const = 0;

protected:

  //! Evaluate the cross section multiplier
  double evaluateMultiplier( const double incoming_energy,
			     const double scattering_angle_cosine ) const;

  //! Evaluate the exact cross section multiplier
  double evaluateMultiplierExact( const double incoming_energy,
                                  const double outgoing_energy,
                                  const double scattering_angle_cosine ) const;

  //! Evaluate the relativistic term
  double evaluateRelativisticTerm(const double incoming_energy,
                                  const double scattering_angle_cosine ) const;

  //! Evaluate the exact relativistic term
  double evaluateRelativisticTermExact(
                                  const double incoming_energy,
                                  const double outgoing_energy,
                                  const double scattering_angle_cosine ) const;

  //! Evaluate the approximate jacobian for a change of variables from pz to E
  double evaluateJacobian( const double incoming_energy,
                           const double outgoing_energy,
                           const double scattering_angle_cosine ) const;
};

// Evaluate the approximate jacobian for a change of variables from pz to E
/*! \details The approximate jacobian can be used to convert from the 
 * approximate double differential cross section as a function of electron
 * momentum projection (in me*c units) to outgoing energy.
 */
inline double DopplerBroadenedPhotonEnergyDistribution::evaluateJacobian(
                                   const double incoming_energy,
                                   const double outgoing_energy,
                                   const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  // Make sure the outgoing energy is valid
  testPrecondition( outgoing_energy <= incoming_energy );
  testPrecondition( outgoing_energy >= 0.0 );
  // Make sure the scattering angle is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );
  
  // Calculate the unitless incoming energy
  const double incoming_alpha = incoming_energy/
    Utility::PhysicalConstants::electron_rest_mass_energy;

  // Calculate the unitless outgoing energy
  const double outgoing_alpha = outgoing_energy/
    Utility::PhysicalConstants::electron_rest_mass_energy;
  
  // Calculate the Jacobian
  const double jacobian = (1.0+incoming_alpha*(1-scattering_angle_cosine))/
    (Utility::PhysicalConstants::electron_rest_mass_energy*
     std::sqrt(incoming_alpha*incoming_alpha + outgoing_alpha*outgoing_alpha -
               2.0*incoming_alpha*outgoing_alpha*scattering_angle_cosine));

  return jacobian;
}

// Evaluate the distribution
/*! \details The approximate double differential cross section
 * (d^2 sigma)/(dmu dE) will be evaluated by evaluating the 
 * approximate double differential cross section dependent on the
 * electron momentum projection (pz) and doing a change of variable to
 * energy.
 */  
inline double DopplerBroadenedPhotonEnergyDistribution::evaluate(
                                   const double incoming_energy,
                                   const double outgoing_energy,
                                   const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  // Make sure the outgoing energy is valid
  testPrecondition( outgoing_energy <= incoming_energy );
  testPrecondition( outgoing_energy >= 0.0 );
  // Make sure the scattering angle is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  // Calculate the electron momentum projection corresponding to the
  // outgoing energy
  const double pz = calculateElectronMomentumProjection(
                                                     incoming_energy,
                                                     outgoing_energy,
                                                     scattering_angle_cosine );
  
  // Calculate the cross section
  const double cross_section =
    this->evaluateJacobian( incoming_energy,
                            outgoing_energy,
                            scattering_angle_cosine )*
    this->evaluateWithElectronMomentumProjection( incoming_energy,
                                                  pz,
                                                  scattering_angle_cosine );

  return cross_section;    
}

// Evaluate the PDF with electron momentum projection
/*! \details A default precision of 1e-3 will be used to evaluate the PDF
 */
inline double DopplerBroadenedPhotonEnergyDistribution::evaluatePDFWithElectronMomentumProjection(
                                  const double incoming_energy,
                                  const double electron_momentum_projection,
                                  const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  // Make sure the electron momentum projection is valid
  testPrecondition( electron_momentum_projection >= -1.0 );
  // Make sure the scattering angle is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  return this->evaluatePDFWithElectronMomentumProjection(
                                                  incoming_energy,
                                                  electron_momentum_projection,
                                                  scattering_angle_cosine,
                                                  1e-3 );
}

// Evaluate the exact PDF with a precision
/*! \details A default precision of 1e-3 will be used to evaluate the PDF
 */  
inline double DopplerBroadenedPhotonEnergyDistribution::evaluatePDFExact(
                                   const double incoming_energy,
                                   const double outgoing_energy,
                                   const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  // Make sure the outgoing energy is valid
  testPrecondition( outgoing_energy <= incoming_energy );
  testPrecondition( outgoing_energy >= 0.0 );
  // Make sure the scattering angle is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  return this->evaluatePDFExact( incoming_energy,
                                 outgoing_energy,
                                 scattering_angle_cosine,
                                 1e-3 );
}

// Evaluate the PDF
/*! \details The approximate PDF dependent on the outgoing energy will be 
 * evaluated by evaluating the approximate PDF dependent on the
 * electron momentum projection (pz) and doing a change of variable to
 * energy.
 */
inline double DopplerBroadenedPhotonEnergyDistribution::evaluatePDF(
                                   const double incoming_energy,
                                   const double outgoing_energy,
                                   const double scattering_angle_cosine,
                                   const double precision ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  // Make sure the outgoing energy is valid
  testPrecondition( outgoing_energy <= incoming_energy );
  testPrecondition( outgoing_energy >= 0.0 );
  // Make sure the scattering angle is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );
  // Make sure the precision is valid
  testPrecondition( precision > 0.0 );
  testPrecondition( precision < 1.0 );

  // Calculate the electron momentum projection corresponding to the
  // outgoing energy
  const double pz = calculateElectronMomentumProjection(
                                                     incoming_energy,
                                                     outgoing_energy,
                                                     scattering_angle_cosine );
  
  // Calculate the cross section
  const double pdf =
    this->evaluateJacobian( incoming_energy,
                            outgoing_energy,
                            scattering_angle_cosine )*
    this->evaluatePDFWithElectronMomentumProjection( incoming_energy,
                                                     pz,
                                                     scattering_angle_cosine,
                                                     precision );

  return pdf;
}

// Evaluate the exact relativistic term
/*! \details The relativistic term is unitless
 */
inline double
DopplerBroadenedPhotonEnergyDistribution::evaluateRelativisticTermExact(
                                   const double incoming_energy,
                                   const double outgoing_energy,
                                   const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  // Make sure the outgoing energy is valid
  testPrecondition( outgoing_energy <= incoming_energy );
  // Make sure the scattering angle is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  const double term = incoming_energy/outgoing_energy +
    outgoing_energy/incoming_energy - 1.0 +
    scattering_angle_cosine*scattering_angle_cosine;

  // Make sure the relativistic term is valid
  testPostcondition( term >= 0.0 );

  return term;
}

// Evaluate the approximate relativistic term
/*! \details the relativistic term is unitless
 */
inline double
DopplerBroadenedPhotonEnergyDistribution::evaluateRelativisticTerm(
                                   const double incoming_energy,
                                   const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  // Make sure the scattering angle is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  const double compton_line_energy = 
    calculateComptonLineEnergy( incoming_energy, scattering_angle_cosine );

  const double term = incoming_energy/compton_line_energy +
    compton_line_energy/incoming_energy - 1.0 +
    scattering_angle_cosine*scattering_angle_cosine;

  // Make sure the relativistic term is valid
  testPostcondition( term >= 0.0 );

  return term;
}

// Evaluate the exact cross section multiplier
/*! \details This multiplier term is for the double differential cross section
 * that is a function of scattering angle cosine and outgoing energy 
 * (not the electron momentum projection). It has units of barns/MeV 
 * (this assumes that the Compton profile in inverse me*c units will be used to
 * evaluate the cross section).
 */
inline double
DopplerBroadenedPhotonEnergyDistribution::evaluateMultiplierExact(
                                   const double incoming_energy,
                                   const double outgoing_energy,
                                   const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  // Make sure the outgoing energy is valid
  testPrecondition( outgoing_energy <= incoming_energy );
  // Make sure the scattering angle is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  const double term_1 =
    Utility::PhysicalConstants::pi*1e24*
    Utility::PhysicalConstants::classical_electron_radius*
    Utility::PhysicalConstants::classical_electron_radius;

  const double term_2 =
    1.0/std::sqrt( incoming_energy*incoming_energy +
                   outgoing_energy*outgoing_energy -
                   2.0*incoming_energy*outgoing_energy*
                   scattering_angle_cosine );

  const double term_3 = outgoing_energy/incoming_energy;

  return term_1*term_2*term_3;
}

// Evaluate the cross section multiplier
/*! \details This multiplier term is for the double differential cross section
 * that is a function of scattering angle cosine and electron momentum 
 * projection in me*c units (unitless). It has units of barns
 * (this assumes that the Compton profile in inverse me*c units will be used to
 * evaluate the cross section).
 */
inline double DopplerBroadenedPhotonEnergyDistribution::evaluateMultiplier(
                                   const double incoming_energy,
                                   const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  // Make sure the scattering angle is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  const double term_1 =
    Utility::PhysicalConstants::pi*1e24*
    Utility::PhysicalConstants::classical_electron_radius*
    Utility::PhysicalConstants::classical_electron_radius;

  const double compton_line_energy =
    calculateComptonLineEnergy( incoming_energy, scattering_angle_cosine );

  double term_2 = (compton_line_energy/incoming_energy);
  term_2 = term_2*term_2;
  
  return term_1*term_2;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DopplerBroadenedPhotonEnergyDistribution.hpp
//---------------------------------------------------------------------------//
