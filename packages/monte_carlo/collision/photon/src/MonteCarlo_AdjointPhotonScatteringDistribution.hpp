//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointPhotonScatteringDistribution.hpp
//! \author Alex Robinson
//! \brief  The adjoint photon scattering distribution base class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_HPP

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotonState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_ScatteringDistribution.hpp"
#include "Data_SubshellType.hpp"
#include "Utility_DistributionTraits.hpp"

namespace MonteCarlo{

//! The adjoint photon scattering distribution base class
class AdjointPhotonScatteringDistribution : public virtual ScatteringDistribution
{

public:

  //! The trials counter type
  typedef Utility::DistributionTraits::Counter Counter;

  //! Constructor
  AdjointPhotonScatteringDistribution()
  { /* ... */ }

  //! Destructor
  virtual ~AdjointPhotonScatteringDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  virtual double evaluate( const double incoming_energy,
                           const double scattering_angle_cosine ) const = 0;

  //! Evaluate the PDF
  virtual double evaluatePDF( const double incoming_energy,
                              const double scattering_angle_cosine ) const = 0;

  //! Evaluate the integrated cross section (b)
  virtual double evaluateIntegratedCrossSection(
                                            const double incoming_energy,
                                            const double precision ) const = 0;

  //! Sample an outgoing energy and direction from the distribution
  virtual void sample( const double incoming_energy,
                       double& outgoing_energy,
                       double& scattering_angle_cosine ) const = 0;

  //! Sample an outgoing energy and direction and record the number of trials
  virtual void sampleAndRecordTrials( const double incoming_energy,
                                      double& outgoing_energy,
                                      double& scattering_angle_cosine,
                                      Counter& trials ) const = 0;

  //! Randomly scatter the photon and return the shell that was interacted with
  virtual void scatterAdjointPhoton(
                          AdjointPhotonState& adjoint_photon,
                          ParticleBank& bank,
                          Data::SubshellType& shell_of_interaction ) const = 0;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointPhotonScatteringDistribution.hpp
//---------------------------------------------------------------------------//
