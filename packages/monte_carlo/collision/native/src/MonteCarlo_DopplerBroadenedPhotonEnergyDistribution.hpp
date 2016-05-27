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

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Data_SubshellType.hpp"
#include "MonteCarlo_ModuleTraits.hpp"
#include "MonteCarlo_PhotonKinematicsHelpers.hpp"
#include "MonteCarlo_ComptonProfile.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_MeCMomentumUnit.hpp"
#include "Utility_ElectronVoltUnit.hpp"
#include "Utility_BarnUnit.hpp"
#include "Utility_UnitTraits.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

//! The Doppler broadened photon energy distribution class
class DopplerBroadenedPhotonEnergyDistribution
{

public:

  //! The energy unit
  typedef ModuleTraits::EnergyUnit EnergyUnit;

  //! The momentum unit
  typedef ComptonProfile::MomentumUnit MomentumUnit;

  //! The area unit
  typedef Utility::Units::BarnUnit AreaUnit;

  //! The area per energy unit
  typedef Utility::UnitTraits<AreaUnit>::GetMultipliedUnitType<Utility::UnitTraits<EnergyUnit>::InverseUnit>::type AreaPerEnergyUnit;

  //! The area per momentum unit
  typedef Utility::UnitTraits<AreaUnit>::GetMultipliedUnitType<Utility::UnitTraits<MomentumUnit>::InverseUnit>::type AreaPerMomentumUnit;

  //! The energy quantity type
  typedef ModuleTraits::EnergyQuantity EnergyQuantity;

  //! The inverse energy quantity type
  typedef boost::units::quantity<Utility::UnitTraits<EnergyUnit>::InverseUnit> InverseEnergyQuantity;

  //! The momentum quantity type
  typedef boost::units::quantity<MomentumUnit> MomentumQuantity;

  //! The inverse momentum quantity type
  typedef boost::units::quantity<Utility::UnitTraits<MomentumUnit>::InverseUnit> InverseMomentumQuantity;

  //! The area quantity type
  typedef boost::units::quantity<AreaUnit> AreaQuantity;

  //! The area per energy quantity type
  typedef boost::units::quantity<AreaPerEnergyUnit> AreaPerEnergyQuantity;

  //! The area per momentum quantity type
  typedef boost::units::quantity<AreaPerMomentumUnit> AreaPerMomentumQuantity;
  
  
  //! Constructor
  DopplerBroadenedPhotonEnergyDistribution()
  { /* ... */ }

  //! Destructor
  virtual ~DopplerBroadenedPhotonEnergyDistribution()
  { /* ... */ }

  //! Check if the distribution is complete (all subshells)
  virtual bool isComplete() const = 0;

  //! Evaluate the distribution with electron momentum projection
  virtual AreaPerMomentumQuantity evaluateWithElectronMomentumProjection(
                           const EnergyQuantity incoming_energy,
                           const MomentumQuantity electron_momentum_projection,
                           const double scattering_angle_cosine ) const = 0;

  //! Evaluate the distribution
  AreaPerEnergyQuantity evaluate( const EnergyQuantity incoming_energy,
                                  const EnergyQuantity outgoing_energy,
                                  const double scattering_angle_cosine ) const;

  //! Evaluate the exact distribution
  virtual AreaPerEnergyQuantity evaluateExact(
                              const EnergyQuantity incoming_energy,
                              const EnergyQuantity outgoing_energy,
                              const double scattering_angle_cosine ) const = 0;

  //! Evaluate the PDF with electron momentum projection
  virtual InverseMomentumQuantity evaluatePDFWithElectronMomentumProjection(
                           const EnergyQuantity incoming_energy,
                           const MomentumQuantity electron_momentum_projection,
                           const double scattering_angle_cosine,
                           const double precision ) const = 0;

  //! Evaluate the PDF with electron momentum projection
  InverseMomentumQuantity evaluatePDFWithElectronMomentumProjection(
                           const EnergyQuantity incoming_energy,
                           const MomentumQuantity electron_momentum_projection,
                           const double scattering_angle_cosine ) const;

  //! Evaluate the PDF
  InverseEnergyQuantity evaluatePDF( const EnergyQuantity incoming_energy,
                                     const EnergyQuantity outgoing_energy,
                                     const double scattering_angle_cosine,
                                     const double precision = 1e-3 ) const;

  //! Evaluate the exact PDF
  virtual InverseEnergyQuantity evaluatePDFExact(
                                          const EnergyQuantity incoming_energy,
                                          const EnergyQuantity outgoing_energy,
                                          const double scattering_angle_cosine,
                                          const double precision ) const = 0;

  //! Evaluate the exact PDF with a precision
  InverseEnergyQuantity evaluatePDFExact(
                                  const EnergyQuantity incoming_energy,
                                  const EnergyQuantity outgoing_energy,
                                  const double scattering_angle_cosine ) const;

  //! Evaluate the integrated cross section (b/mu)
  virtual AreaQuantity evaluateIntegratedCrossSection(
                                          const EnergyQuantity incoming_energy,
                                          const double scattering_angle_cosine,
                                          const double precision ) const = 0;
  
  //! Evaluate the exact integrated cross section (b/mu)
  virtual AreaQuantity evaluateIntegratedCrossSectionExact( 
			             const EnergyQuantity incoming_energy,
                                     const double scattering_angle_cosine,
                                     const double precision ) const = 0;

  //! Sample an outgoing energy from the distribution
  virtual void sample( const EnergyQuantity incoming_energy,
		       const double scattering_angle_cosine,
		       EnergyQuantity& outgoing_energy,
		       Data::SubshellType& shell_of_interaction ) const = 0;

  //! Sample an outgoing energy and record the number of trials
  virtual void sampleAndRecordTrials( 
				const EnergyQuantity incoming_energy,
				const double scattering_angle_cosine,
				EnergyQuantity& outgoing_energy,
				Data::SubshellType& shell_of_interaction,
				unsigned& trials ) const = 0;

  //! Sample an electron momentum projection and record the number of trials
  virtual void sampleMomentumAndRecordTrials(
                                const EnergyQuantity incoming_energy,
                                const double scattering_angle_cosine,
                                MomentumQuantity& electron_momentum_projection,
                                Data::SubshellType& shell_of_interaction,
                                unsigned& trials ) const = 0;

protected:

  //! The jacobian unit
  typedef Utility::UnitTraits<MomentumUnit>::GetMultipliedUnitType<Utility::UnitTraits<EnergyUnit>::InverseUnit>::type JabobianUnit;

  //! The area unit times the jacobian unit
  typedef Utility::UnitTraits<AreaUnit>::GetMultipliedUnitType<Utility::UnitTraits<JacobianUnit> >::type AreaTimesJacobianUnit;

  //! The jacobian quantity
  typedef boost::units::quantity<JacobianUnit> JacobianQuantity;

  //! The area times jacobian quantity
  typedef boost::units::quantity<AreaTimeJacobianUnit> AreaTimeJacobianQuantity;

  //! Evaluate the cross section multiplier
  AreaQuantity evaluateMultiplier(const EnergyQuantity incoming_energy,
                                  const double scattering_angle_cosine ) const;

  //! Evaluate the exact cross section multiplier
  AreaTimeJacobianQuantity evaluateMultiplierExact(
                                  const EnergyQuantity incoming_energy,
                                  const EnergyQuantity outgoing_energy,
                                  const double scattering_angle_cosine ) const;

  //! Evaluate the relativistic term
  double evaluateRelativisticTerm(const EnergyQuantity incoming_energy,
                                  const double scattering_angle_cosine ) const;

  //! Evaluate the exact relativistic term
  double evaluateRelativisticTermExact(
                                  const EnergyQuantity incoming_energy,
                                  const EnergyQuantity outgoing_energy,
                                  const double scattering_angle_cosine ) const;

  //! Evaluate the approximate jacobian for a change of variables from pz to E
  JacobianQuantity evaluateJacobian(
                                  const EnergyQuantity incoming_energy,
                                  const EnergyQuantity outgoing_energy,
                                  const double scattering_angle_cosine ) const;
};

// Evaluate the approximate jacobian for a change of variables from pz to E
/*! \details The approximate jacobian can be used to convert from the 
 * approximate double differential cross section as a function of electron
 * momentum projection (in me*c units) to outgoing energy.
 */
inline DopplerBroadenedPhotonEnergyDistribution::JacobianQuantity
DopplerBroadenedPhotonEnergyDistribution::evaluateJacobian(
                                   const EnergyQuantity incoming_energy,
                                   const EnergyQuantity outgoing_energy,
                                   const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0*EnergyUnit() );
  // Make sure the outgoing energy is valid
  testPrecondition( outgoing_energy <= incoming_energy );
  testPrecondition( outgoing_energy >= 0.0*EnergyUnit() );
  // Make sure the scattering angle is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );
  
  // Calculate the unitless incoming energy
  const double incoming_alpha = incoming_energy/
    Utility::PhysicalConstants::electron_rest_mass_energy_q;

  // Calculate the unitless outgoing energy
  const double outgoing_alpha = outgoing_energy/
    Utility::PhysicalConstants::electron_rest_mass_energy_q;
  
  // Calculate the Jacobian
  const JacobianQuantity jacobian =
    (1.0+incoming_alpha*(1-scattering_angle_cosine))*MomentumUnit()/
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
inline DopplerBroadenedPhotonEnergyDistribution::AreaPerEnergyQuantity
DopplerBroadenedPhotonEnergyDistribution::evaluate(
                                   const EnergyQuantity incoming_energy,
                                   const EnergyQuantity outgoing_energy,
                                   const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0*EnergyUnit() );
  // Make sure the outgoing energy is valid
  testPrecondition( outgoing_energy <= incoming_energy );
  testPrecondition( outgoing_energy >= 0.0*EnergyUnit() );
  // Make sure the scattering angle is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  // Calculate the electron momentum projection corresponding to the
  // outgoing energy
  const MomentumQuantity pz = calculateElectronMomentumProjectionQuantity(
                                                     incoming_energy,
                                                     outgoing_energy,
                                                     scattering_angle_cosine );
  
  // Calculate the cross section
  return this->evaluateJacobian( incoming_energy,
                                 outgoing_energy,
                                 scattering_angle_cosine )*
    this->evaluateWithElectronMomentumProjection( incoming_energy,
                                                  pz,
                                                  scattering_angle_cosine );
}

// Evaluate the PDF with electron momentum projection
/*! \details A default precision of 1e-3 will be used to evaluate the PDF
 */
inline DopplerBroadenedPhotonEnergyDistribution::InverseMomentumQuantity
DopplerBroadenedPhotonEnergyDistribution::evaluatePDFWithElectronMomentumProjection(
                           const EnergyQuantity incoming_energy,
                           const MomentumQuantity electron_momentum_projection,
                           const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0*EnergyUnit() );
  // Make sure the electron momentum projection is valid
  testPrecondition( electron_momentum_projection >= -1.0*MomentumUnit() );
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
inline DopplerBroadenedPhotonEnergyDistribution::InverseEnergyQuantity
DopplerBroadenedPhotonEnergyDistribution::evaluatePDFExact(
                                   const EnergyQuantity incoming_energy,
                                   const EnergyQuantity outgoing_energy,
                                   const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0*EnergyUnit() );
  // Make sure the outgoing energy is valid
  testPrecondition( outgoing_energy <= incoming_energy );
  testPrecondition( outgoing_energy >= 0.0*EnergyUnit() );
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
inline DopplerBroadenedPhotonEnergyDistribution::InverseEnergyQuantity
DopplerBroadenedPhotonEnergyDistribution::evaluatePDF(
                                   const EnergyQuantity incoming_energy,
                                   const EnergyQuantity outgoing_energy,
                                   const double scattering_angle_cosine,
                                   const double precision ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0*EnergyUnit() );
  // Make sure the outgoing energy is valid
  testPrecondition( outgoing_energy <= incoming_energy );
  testPrecondition( outgoing_energy >= 0.0*EnergyUnit() );
  // Make sure the scattering angle is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );
  // Make sure the precision is valid
  testPrecondition( precision > 0.0 );
  testPrecondition( precision < 1.0 );

  // Calculate the electron momentum projection corresponding to the
  // outgoing energy
  const MomentumQuantity pz = calculateElectronMomentumProjectionQuantity(
                                                     incoming_energy,
                                                     outgoing_energy,
                                                     scattering_angle_cosine );
  
  // Calculate the cross section
  return this->evaluateJacobian( incoming_energy,
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
                                   const EnergyQuantity incoming_energy,
                                   const EnergyQuantity outgoing_energy,
                                   const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0*EnergyUnit() );
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
                                   const EnergyQuantity incoming_energy,
                                   const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  // Make sure the scattering angle is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  const EnergyQuantity compton_line_energy = 
    calculateComptonLineEnergyQuantity( incoming_energy,
                                        scattering_angle_cosine );

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
inline DopplerBroadenedPhotonEnergyDistribution::AreaTimesJacobianQuantity
DopplerBroadenedPhotonEnergyDistribution::evaluateMultiplierExact(
                                   const EnergyQuantity incoming_energy,
                                   const EnergyQuantity outgoing_energy,
                                   const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0*EnergyUnit() );
  // Make sure the outgoing energy is valid
  testPrecondition( outgoing_energy <= incoming_energy );
  // Make sure the scattering angle is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  const AreaQuantity term_1(
                     Utility::PhysicalConstants::pi*
                     Utility::PhysicalConstants::classical_electron_radius_q*
                     Utility::PhysicalConstants::classical_electron_radius_q );

  const double term_2 =
    Utility::PhysicalConstants::electron_rest_mass_energy_q/
    std::sqrt( incoming_energy*incoming_energy +
               outgoing_energy*outgoing_energy -
               2.0*incoming_energy*outgoing_energy*
               scattering_angle_cosine );

  const double term_3 = outgoing_energy/incoming_energy;

  // This quantity is used to ensure that the units of the cross section will
  // be correct units (b/MeV) when this multiplier is multiplied by the Compton
  // profile value
  const JacobianQuantity unit_conversion_term = 1.0*JacobianUnit();

  return term_1*term_2*term_3*unit_conversion_term;
}

// Evaluate the cross section multiplier
/*! \details This multiplier term is for the double differential cross section
 * that is a function of scattering angle cosine and electron momentum 
 * projection in me*c units (unitless). It has units of barns
 * (this assumes that the Compton profile in inverse me*c units will be used to
 * evaluate the cross section).
 */
inline DopplerBroadenedPhotonEnergyDistribution::AreaQuantity
DopplerBroadenedPhotonEnergyDistribution::evaluateMultiplier(
                                   const EnergyQuantity incoming_energy,
                                   const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0*EnergyUnit() );
  // Make sure the scattering angle is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  const AreaQuantity term_1(
                     Utility::PhysicalConstants::pi*
                     Utility::PhysicalConstants::classical_electron_radius_q*
                     Utility::PhysicalConstants::classical_electron_radius_q );
  
  const EnergyQuantity compton_line_energy = 
    calculateComptonLineEnergyQuantity( incoming_energy,
                                        scattering_angle_cosine );

  double term_2 = (compton_line_energy/incoming_energy);
  term_2 = term_2*term_2;
  
  return term_1*term_2;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DopplerBroadenedPhotonEnergyDistribution.hpp
//---------------------------------------------------------------------------//
