//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectronScatteringDistribution.hpp
//! \author Luke Kersting
//! \brief  The adjoint electron scattering distribution base class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_ELECTRON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_ADJOINT_ELECTRON_SCATTERING_DISTRIBUTION_HPP

// FRENSIE Includes
#include "MonteCarlo_ScatteringDistribution.hpp"
#include "MonteCarlo_AdjointElectronState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "Data_SubshellType.hpp"
#include "Utility_DistributionTraits.hpp"

namespace MonteCarlo{

//! The adjoint electron scattering distribution base class
class AdjointElectronScatteringDistribution : public virtual ScatteringDistribution
{

public:

  //! The trials counter type
  typedef Utility::DistributionTraits::Counter Counter;

  //! Constructor
  AdjointElectronScatteringDistribution()
  { /* ... */ }

  //! Destructor
  virtual ~AdjointElectronScatteringDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  virtual double evaluate( const double incoming_energy,
                           const double scattering_angle_cosine ) const = 0;

  //! Evaluate the PDF
  virtual double evaluatePDF( const double incoming_energy,
                              const double scattering_angle_cosine ) const = 0;

  //! Sample an outgoing energy and direction from the distribution
  virtual void sample( const double incoming_energy,
                       double& outgoing_energy,
                       double& scattering_angle_cosine ) const = 0;

  //! Sample an outgoing energy and direction and record the number of trials
  virtual void sampleAndRecordTrials( const double incoming_energy,
                                      double& outgoing_energy,
                                      double& scattering_angle_cosine,
                                      Counter& trials ) const = 0;

  //! Randomly scatter the electron and return the shell that was interacted with
  virtual void scatterAdjointElectron(
                        AdjointElectronState& adjoint_electron,
                        ParticleBank& bank,
                        Data::SubshellType& shell_of_interaction ) const = 0;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ADJOINT_ELECTRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectronScatteringDistribution.hpp
//---------------------------------------------------------------------------//
