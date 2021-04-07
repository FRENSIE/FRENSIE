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
#include "Utility_Vector.hpp"

namespace MonteCarlo{

//! The complete (all subshells) Doppler broadened photon energy dist. class
class CompleteDopplerBroadenedPhotonEnergyDistribution : public DopplerBroadenedPhotonEnergyDistribution
{

public:

  //! The counter type
  typedef DopplerBroadenedPhotonEnergyDistribution::Counter Counter;

  //! The Compton profile array
  typedef std::vector<std::shared_ptr<const ComptonProfile> >
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
  virtual double getSubshellBindingEnergy(
                                       const Data::SubshellType subshell ) const = 0;

  //! Return the occupancy of a subshell (default is the ENDF occupancy)
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
                                     const Data::SubshellType subshell,
                                     const double precision ) const = 0;

  //! Evaluate the subshell PDF with electron momentum projection
  double evaluateSubshellPDFWithElectronMomentumProjection(
                                     const double incoming_energy,
                                     const double electron_momentum_projection,
                                     const double scattering_angle_cosine,
                                     const Data::SubshellType subshell ) const;

  //! Evaluate the subshell PDF
  double evaluateSubshellPDF( const double incoming_energy,
                              const double outgoing_energy,
                              const double scattering_angle_cosine,
                              const Data::SubshellType subshell,
                              const double precision = 1e-3 ) const;

  //! Evaluate the subshell PDF
  virtual double evaluateSubshellPDFExact(const double incoming_energy,
                                          const double outgoing_energy,
                                          const double scattering_angle_cosine,
                                          const Data::SubshellType subshell,
                                          const double precision ) const = 0;

  //! Evaluate the subshell PDF
  double evaluateSubshellPDFExact( const double incoming_energy,
                                   const double outgoing_energy,
                                   const double scattering_angle_cosine,
                                   const Data::SubshellType subshell ) const;

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
  testPrecondition( this->isValidSubshell( subshell ) );

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
                                                     scattering_angle_cosine,
                                                     subshell );

  return cross_section;
}

// Evaluate the subshell PDF with electron momentum projection
/*! \details A default precision of 1e-3 will be used to evaluate the PDF
 */
inline double
CompleteDopplerBroadenedPhotonEnergyDistribution::evaluateSubshellPDFWithElectronMomentumProjection(
                                     const double incoming_energy,
                                     const double electron_momentum_projection,
                                     const double scattering_angle_cosine,
                                     const Data::SubshellType subshell ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  // Make sure the electron momentum projection is valid
  testPrecondition( electron_momentum_projection >= -1.0 );
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
inline double
CompleteDopplerBroadenedPhotonEnergyDistribution::evaluateSubshellPDFExact(
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
inline double
CompleteDopplerBroadenedPhotonEnergyDistribution::evaluateSubshellPDF(
                                      const double incoming_energy,
                                      const double outgoing_energy,
                                      const double scattering_angle_cosine,
                                      const Data::SubshellType subshell,
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
  // Make sure the subshell is valid
  testPrecondition( this->isValidSubshell( subshell ) );

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
                                                       scattering_angle_cosine,
                                                       subshell,
                                                       precision );

  return pdf;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_COMPLETE_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CompleteDopplerBroadenedPhotonEnergyDistribution.hpp
//---------------------------------------------------------------------------//
