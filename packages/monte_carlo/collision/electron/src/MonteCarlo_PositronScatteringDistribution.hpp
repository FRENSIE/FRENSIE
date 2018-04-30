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
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_ScatteringDistribution.hpp"
#include "Data_SubshellType.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_UnivariateDistribution.hpp"
#include "Utility_DistributionTraits.hpp"

namespace MonteCarlo{

//! The scattering distribution base class
class PositronScatteringDistribution : public virtual ScatteringDistribution
{

public:

  //! The trials counter type
  typedef Utility::DistributionTraits::Counter Counter;

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
                                      Counter& trials ) const = 0;

  //! Randomly scatter the positron
  virtual void scatterPositron( PositronState& positron,
                                ParticleBank& bank,
                                Data::SubshellType& shell_of_interaction ) const = 0;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_POSITRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PositronScatteringDistribution.hpp
//---------------------------------------------------------------------------//
