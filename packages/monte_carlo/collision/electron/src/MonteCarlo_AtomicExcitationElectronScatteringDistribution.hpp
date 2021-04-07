//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AtomicExcitationElectronScatteringDistribution.hpp
//! \author Luke Kersting
//! \brief  The electron hard elastic scattering distribution base class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ATOMIC_EXCITATION_ELECTRON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_ATOMIC_EXCITATION_ELECTRON_SCATTERING_DISTRIBUTION_HPP

// FRENSIE Includes
#include "MonteCarlo_ElectronScatteringDistribution.hpp"
#include "MonteCarlo_PositronScatteringDistribution.hpp"
#include "Utility_UnivariateDistribution.hpp"

namespace MonteCarlo{

//! The atomic excitation scattering distribution base class
class AtomicExcitationElectronScatteringDistribution : public ElectronScatteringDistribution,
                                                       public PositronScatteringDistribution
{

public:

  //! Typedef for the counter type
  typedef ElectronScatteringDistribution::Counter Counter;

  //! Typedef for the atomic excitation distribution
  typedef std::shared_ptr<const Utility::UnivariateDistribution> AtomicDistribution;

  //! Constructor
  AtomicExcitationElectronScatteringDistribution(
    const AtomicDistribution& energy_loss_distribution );

  //! Destructor
  virtual ~AtomicExcitationElectronScatteringDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  double evaluate( const double incoming_energy,
                   const double scattering_angle_cosine ) const override
  { /*...*/}

  //! Evaluate the PDF
  double evaluatePDF( const double incoming_energy,
                      const double scattering_angle_cosine ) const override
  { /*...*/}

  //! Evaluate the CDF
  double evaluateCDF( const double incoming_energy,
                      const double scattering_angle_cosine ) const override
  { /* ... */ }

  //! Sample an outgoing energy and direction from the distribution
  void sample( const double incoming_energy,
               double& outgoing_energy,
               double& scattering_angle_cosine ) const override;

  //! Sample an outgoing energy and direction and record the number of trials
  void sampleAndRecordTrials( const double incoming_energy,
                              double& outgoing_energy,
                              double& scattering_angle_cosine,
                              Counter& trials ) const override;

  //! Randomly scatter the electron
  void scatterElectron( MonteCarlo::ElectronState& electron,
                        MonteCarlo::ParticleBank& bank,
                        Data::SubshellType& shell_of_interaction ) const override;

  //! Randomly scatter the positron
  void scatterPositron( MonteCarlo::PositronState& positron,
                        MonteCarlo::ParticleBank& bank,
                        Data::SubshellType& shell_of_interaction ) const override;

private:

  // Atomic excitation energy loss table
  AtomicDistribution d_energy_loss_distribution;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ATOMIC_EXCITATION_ELECTRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AtomicExcitationElectronScatteringDistribution.hpp
//---------------------------------------------------------------------------//
