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
  virtual double getSubshellBindingEnergy( 
                                       const Data::SubshellType subshell ) const = 0;

  //! Return the occupancy of a subshell (default is the ENDF occupacy)
  virtual double getSubshellOccupancy( const Data::SubshellType subshell ) const = 0;

  //! Evaluate the subshell distribution with electron momentum projection
  virtual double evaluateSubshellWithElectronMomentumProjection(
                                 const double incoming_energy,
                                 const double electron_momentum_projection,
                                 const double scattering_angle_cosine,
                                 const Data::SubshellType subshell ) const = 0;

  //! Evaluate the subshell distribution
  double evaluateSubshell( const double incoming_energy,
                           const double outgoing_energy,
                           const double scattering_angle_cosine,
                           const Data::SubshellType subshell ) const;

  //! Evaluate the exact subshell distribution
  virtual double evaluateSubshellExact(
                                 const double incoming_energy,
                                 const double outgoing_energy,
                                 const double scattering_angle_cosine,
                                 const Data::SubshellType subshell ) const = 0;

  //! Evaluate the subshell PDF with electron momentum projection
  virtual double evaluateSubshellPDFWithElectronMomentumProjection(
                                 const double incoming_energy,
                                 const double electron_momentum_projection,
                                 const double scattering_angle_cosine,
                                 const Data::SubshellType subshell ) const = 0;

  //! Evaluate the subshell PDF
  double evaluateSubshellPDF( const double incoming_energy,
                              const double outgoing_energy,
                              const double scattering_angle_cosine,
                              const Data::SubshellType subshell ) const;

  //! Evaluate the subshell PDF
  virtual double evaluateSubshellPDFExact(
                                 const double incoming_energy,
                                 const double outgoing_energy,
                                 const double scattering_angle_cosine,
                                 const Data::SubshellType subshell ) const = 0;

  //! Evaluate the integrated cross section (b/mu)
  virtual double evaluateSubshellIntegratedCrossSection( 
				          const double incoming_energy,
					  const double scattering_angle_cosine,
					  const Data::SubshellType subshell,
					  const double precision ) const = 0;

  //! Evaluate the exact integrated cross section (b/mu)
  virtual double evaluateSubshellIntegratedCrossSectionExact( 
				          const double incoming_energy,
					  const double scattering_angle_cosine,
					  const Data::SubshellType subshell,
					  const double precision ) const = 0;

  //! Sample an electron momentum from the subshell distribution
  virtual double sampleSubshellMomentum( 
                                 const double incoming_energy,
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
inline double
CompleteDopplerBroadenedPhotonEnergyDistribution::evaluateSubshell(
                                      const double incoming_energy,
                                      const double outgoing_energy,
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
  testPrecondition( this->isSubshellValid( subshell ) );

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
    this->evaluateSubshellWithElectronMomentumProjection(
                                                     incoming_energy,
                                                     pz,
                                                     scattering_angle_cosine );

  return cross_section;
}

// Evaluate the subshell PDF
/*! \details The approximate PDF dependent on the outgoing energy will be 
 * evaluated by evaluating the approximate PDF dependent on the
 * electron momentum projection (pz) and doing a change of variable to
 * energy.
 */
inline double
CompleteDopplerBroadenedPhotonEnergyDistribution::evaluateSubshellPDF(
                                      const double incoming_energy,
                                      const double outgoing_energy,
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
  testPrecondition( this->isSubshellValid( subshell ) );

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
    this->evaluateSubshellPDFWithElectronMomentumProjection(
                                                     incoming_energy,
                                                     pz,
                                                     scattering_angle_cosine );

  return pdf;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_COMPLETE_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CompleteDopplerBroadenedPhotonEnergyDistribution.hpp
//---------------------------------------------------------------------------//
