//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CompleteDopplerBroadenedPhotonEnergyDistribution.hpp
//! \author Alex Robinson
//! \brief  The complete Doppler broadened photon energy distribution decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COMPLETE_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP
#define MONTE_CARLO_COMPLETE_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP

// FRENSIE Includes
#include "MonteCarlo_DopplerBroadenedPhotonEnergyDistribution.hpp"

namespace MonteCarlo{

//! The complete (all subshells) Doppler broadened photon energy dist. class
class CompleteDopplerBroadenedPhotonEnergyDistribution : public DopplerBroadenedPhotonEnergyDistribution
{

public:

  //! The energy unit
  typedef DopplerBroadenedPhotonEnergyDistribution::EnergyUnit EnergyUnit;

  //! The momentum unit
  typedef DopplerBroadenedPhotonEnergyDistribution::MomentumUnit MomentumUnit;

  //! The area unit
  typedef DopplerBroadenedPhotonEnergyDistribution::BarnUnit AreaUnit;

  //! The area per energy unit
  typedef DopplerBroadenedPhotonEnergyDistribution::AreaPerEnergyUnit AreaPerEnergyUnit;

  //! The area per momentum unit
  typedef DopplerBroadenedPhotonEnergyDistribution::AreaPerMomentumUnit AreaPerMomentumUnit;

  //! The energy quantity type
  typedef DopplerBroadenedPhotonEnergyDistribution::EnergyQuantity EnergyQuantity;

  //! The inverse energy quantity type
  typedef DopplerBroadenedPhotonEnergyDistribution::InverseEnergyQuantity InverseEnergyQuantity;

  //! The momentum quantity type
  typedef DopplerBroadenedPhotonEnergyDistribution::MomentumQuantity MomentumQuantity;

  //! The inverse momentum quantity type
  typedef DopplerBroadenedPhotonEnergyDistribution::InverseMomentumQuantity InverseMomentumQuantity;

  //! The area quantity type
  typedef DopplerBroadenedPhotonEnergyDistribution::AreaQuantity AreaQuantity;

  //! The area per energy quantity type
  typedef DopplerBroadenedPhotonEnergyDistribution::AreaPerEnergyQuantity AreaPerEnergyQuantity;

  //! The area per momentum quantity type
  typedef DopplerBroadenedPhotonEnergyDistribution::AreaPerMomentumQuantity AreaPerMomentumQuantity;

  //! The Compton profile array 
  typedef Teuchos::Array<std::shared_ptr<const ComptonProfile> >
  ComptonProfileArray;

  //! Constructor
  CompleteDopplerBroadenedPhotonEnergyDistribution()
  { /* ... */ }

  //! Destructor
  virtual ~CompleteDopplerBroadenedPhotonEnergyDistribution()
  { /* ... */ }

  //! Check if the distribution is complete (all subshells)
  bool isComplete() const;

  //! Check if the subshell is valid
  virtual bool isValidSubshell( const Data::SubshellType subshell ) const = 0;

  //! Return the binding energy of a subshell
  virtual EnergyQuantity getSubshellBindingEnergy( 
                                 const Data::SubshellType subshell ) const = 0;

  //! Return the occupancy of a subshell (default is the ENDF occupacy)
  virtual double getSubshellOccupancy(
                                 const Data::SubshellType subshell ) const = 0;

  //! Evaluate the subshell distribution with electron momentum projection
  virtual AreaPerMomentumQuantity
  evaluateSubshellWithElectronMomentumProjection(
                           const EnergyQuantity incoming_energy,
                           const MomentumQuantity electron_momentum_projection,
                           const double scattering_angle_cosine,
                           const Data::SubshellType subshell ) const = 0;

  //! Evaluate the subshell distribution
  AreaPerEnergyQuantity evaluateSubshell(
                                     const EnergyQuantity incoming_energy,
                                     const EnergyQuantity outgoing_energy,
                                     const double scattering_angle_cosine,
                                     const Data::SubshellType subshell ) const;

  //! Evaluate the exact subshell distribution
  virtual AreaPerEnergyQuantity evaluateSubshellExact(
                                 const EnergyQuantity incoming_energy,
                                 const EnergyQuantity outgoing_energy,
                                 const double scattering_angle_cosine,
                                 const Data::SubshellType subshell ) const = 0;

  //! Evaluate the subshell PDF with electron momentum projection
  virtual InverseMomentumQuantity
  evaluateSubshellPDFWithElectronMomentumProjection(
                           const EnergyQuantity incoming_energy,
                           const MomentumQuantity electron_momentum_projection,
                           const double scattering_angle_cosine,
                           const Data::SubshellType subshell,
                           const double precision ) const = 0;

  //! Evaluate the subshell PDF with electron momentum projection
  InverseMomentumQuantity evaluateSubshellPDFWithElectronMomentumProjection(
                           const EnergyQuantity incoming_energy,
                           const MomentumQuantity electron_momentum_projection,
                           const double scattering_angle_cosine,
                           const Data::SubshellType subshell ) const;

  //! Evaluate the subshell PDF
  InverseEnergyQuantity evaluateSubshellPDF(
                                         const EnergyQuantity incoming_energy,
                                         const EnergyQuantity outgoing_energy,
                                         const double scattering_angle_cosine,
                                         const Data::SubshellType subshell,
                                         const double precision = 1e-3 ) const;

  //! Evaluate the subshell PDF
  virtual InverseEnergyQuantity evaluateSubshellPDFExact(
                                          const EnergyQuantity incoming_energy,
                                          const EnergyQuantity outgoing_energy,
                                          const double scattering_angle_cosine,
                                          const Data::SubshellType subshell,
                                          const double precision ) const = 0;

  //! Evaluate the subshell PDF
  InverseEnergyQuantity evaluateSubshellPDFExact(
                                     const EnergyQuantity incoming_energy,
                                     const EnergyQuantity outgoing_energy,
                                     const double scattering_angle_cosine,
                                     const Data::SubshellType subshell ) const;

  //! Evaluate the integrated cross section (b/mu)
  virtual AreaQuantity evaluateSubshellIntegratedCrossSection( 
				          const EnergyQuantity incoming_energy,
					  const double scattering_angle_cosine,
					  const Data::SubshellType subshell,
					  const double precision ) const = 0;

  //! Evaluate the exact integrated cross section (b/mu)
  virtual AreaQuantity evaluateSubshellIntegratedCrossSectionExact( 
				          const EnergyQuantity incoming_energy,
					  const double scattering_angle_cosine,
					  const Data::SubshellType subshell,
					  const double precision ) const = 0;

  //! Sample an electron momentum from the subshell distribution
  virtual MomentumQuantity sampleSubshellMomentum( 
                                 const EnergyQuantity incoming_energy,
                                 const double scattering_angle_cosine,
                                 const Data::SubshellType subshell ) const = 0;
};

// Check if the distribution is complete (all subshells)
inline bool
CompleteDopplerBroadenedPhotonEnergyDistribution::isComplete() const
{
  return true;
}

// Evaluate the subshell distribution
inline CompleteDopplerBroadenedPhotonEnergyDistribution::AreaPerEnergyQuantity
CompleteDopplerBroadenedPhotonEnergyDistribution::evaluateSubshell(
                                      const EnergyQuantity incoming_energy,
                                      const EnergyQuantity outgoing_energy,
                                      const double scattering_angle_cosine,
                                      const Data::SubshellType subshell ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0*EnergyUnit() );
  // Make sure the outgoing energy is valid
  testPrecondition( outgoing_energy <= incoming_energy );
  testPrecondition( outgoing_energy >= 0.0*EnergyUnit() );
  // Make sure the scattering angle is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );
  // Make sure the subshell is valid
  testPrecondition( this->isValidSubshell( subshell ) );

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
    this->evaluateSubshellWithElectronMomentumProjection(
                                                       incoming_energy,
                                                       pz,
                                                       scattering_angle_cosine,
                                                       subshell );
}

// Evaluate the subshell PDF with electron momentum projection
/*! \details A default precision of 1e-3 will be used to evaluate the PDF
 */
inline CompleteDopplerBroadenedPhotonEnergyDistribution::InverseMomentumQuantity
CompleteDopplerBroadenedPhotonEnergyDistribution::evaluateSubshellPDFWithElectronMomentumProjection(
                           const EnergyQuantity incoming_energy,
                           const MomentumQuantity electron_momentum_projection,
                           const double scattering_angle_cosine,
                           const Data::SubshellType subshell ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0*EnergyUnit() );
  // Make sure the electron momentum projection is valid
  testPrecondition( electron_momentum_projection >= -1.0*MomentumUnit() );
  // Make sure the scattering angle is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );
  // Make sure the subshell is valid
  testPrecondition( this->isValidSubshell( subshell ) );

  return this->evaluateSubshellPDFWithElectronMomentumProjection(
                                                  incoming_energy,
                                                  electron_momentum_projection,
                                                  scattering_angle_cosine,
                                                  subshell,
                                                  1e-3 );
}

// Evaluate the subshell PDF
/*! \details A default precision of 1e-3 will be used to evaluate the PDF
 */
inline CompleteDopplerBroadenedPhotonEnergyDistribution::InverseEnergyQuantity
CompleteDopplerBroadenedPhotonEnergyDistribution::evaluateSubshellPDFExact(
                                      const EnergyQuantity incoming_energy,
                                      const EnergyQuantity outgoing_energy,
                                      const double scattering_angle_cosine,
                                      const Data::SubshellType subshell ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  // Make sure the outgoing energy is valid
  testPrecondition( outgoing_energy <= incoming_energy );
  testPrecondition( outgoing_energy >= 0.0 );
  // Make sure the scattering angle is valid
  testPrecondition( scattering_angle_cosine >= -1.0 );
  testPrecondition( scattering_angle_cosine <= 1.0 );
  // Make sure the subshell is valid
  testPrecondition( this->isValidSubshell( subshell ) );

  return this->evaluateSubshellPDFExact( incoming_energy,
                                         outgoing_energy,
                                         scattering_angle_cosine,
                                         subshell,
                                         1e-3 );
}

// Evaluate the subshell PDF
/*! \details The approximate PDF dependent on the outgoing energy will be 
 * evaluated by evaluating the approximate PDF dependent on the
 * electron momentum projection (pz) and doing a change of variable to
 * energy.
 */
inline CompleteDopplerBroadenedPhotonEnergyDistribution::InverseEnergyQuantity
CompleteDopplerBroadenedPhotonEnergyDistribution::evaluateSubshellPDF(
                                          const EnergyQuantity incoming_energy,
                                          const EnergyQuantity outgoing_energy,
                                          const double scattering_angle_cosine,
                                          const Data::SubshellType subshell,
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
  // Make sure the subshell is valid
  testPrecondition( this->isValidSubshell( subshell ) );

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
    this->evaluateSubshellPDFWithElectronMomentumProjection(
                                                       incoming_energy,
                                                       pz,
                                                       scattering_angle_cosine,
                                                       subshell,
                                                       precision );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_COMPLETE_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CompleteDopplerBroadenedPhotonEnergyDistribution.hpp
//---------------------------------------------------------------------------//
