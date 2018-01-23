//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PositronScatteringDistribution.hpp
//! \author Luke Kersting
//! \brief  The positron scattering distribution base class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_POSITRON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_POSITRON_SCATTERING_DISTRIBUTION_HPP

// FRENSIE Includes
#include "MonteCarlo_PositronState.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "Data_SubshellType.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_OneDDistribution.hpp"
#include "MonteCarlo_ScatteringDistribution.hpp"

namespace MonteCarlo{

//! The scattering distribution base class
class PositronScatteringDistribution : public virtual ScatteringDistribution
{

public:

  //! Constructor
  PositronScatteringDistribution()
  { /* ... */ }

  //! Destructor
  virtual ~PositronScatteringDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  virtual double evaluate( const double incoming_energy,
                           const double scattering_angle ) const = 0;

  //! Evaluate the PDF
  virtual double evaluatePDF( const double incoming_energy,
                              const double scattering_angle ) const = 0;

  //! Evaluate the CDF
  virtual double evaluateCDF( const double incoming_energy,
                              const double scattering_angle ) const = 0;

  //! Sample an outgoing energy and direction from the distribution
  virtual void sample( const double incoming_energy,
                       double& outgoing_energy,
                       double& scattering_angle_cosine ) const = 0;

  //! Sample an outgoing energy and direction and record the number of trials
  virtual void sampleAndRecordTrials( const double incoming_energy,
                                      double& outgoing_energy,
                                      double& scattering_angle_cosine,
                                      unsigned& trials ) const = 0;

  //! Randomly scatter the positron
  virtual void scatterPositron( PositronState& positron,
                                ParticleBank& bank,
                                Data::SubshellType& shell_of_interaction ) const = 0;

protected:

  //! Annihilate the positron
  void annihilatePositron( PositronState& positron,
                          ParticleBank& bank ) const;
};

// Annihilate the positron
/*! \details The positron is assumed to be at rest when it annihilates, emitting
 *  two photons at the electron rest mass energy. These photons are emitted
 *  isotropically in opposite directions in the azimuthal direction to conserve
 *  momentum and at 90 degrees to positron polar angle.
 */
inline void
PositronScatteringDistribution::annihilatePositron( PositronState& positron,
                                                    ParticleBank& bank ) const
{
  // Create the first annihilation photon
  Teuchos::RCP<PhotonState> first_photon( new PhotonState( positron, true, true ) );
  Teuchos::RCP<PhotonState> second_photon( new PhotonState( positron, true, true ) );

  // Sample the isotropic azimuthal angle for the first photon
  double azimuthal_angle = sampleAzimuthalAngle();

  // Rotate the photons in opposite azimuthal directions
  first_photon->rotateDirection( 0.0, azimuthal_angle );
  second_photon->rotateDirection( 0.0, azimuthal_angle +
                                       Utility::PhysicalConstants::pi );

  // Bank the photons
  bank.push( first_photon );
  bank.push( second_photon );

  // Set the positron as gone
  positron.setAsGone();
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_POSITRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PositronScatteringDistribution.hpp
//---------------------------------------------------------------------------//
