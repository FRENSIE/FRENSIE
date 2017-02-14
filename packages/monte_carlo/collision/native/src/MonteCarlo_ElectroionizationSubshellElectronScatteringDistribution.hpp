//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroionizationSubshellElectronScatteringDistribution.hpp
//! \author Luke Kersting
//! \brief  The electron electroionization subshell scattering distribution base class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTROIONIZATION_SUBSHELL_ELECTRON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_ELECTROIONIZATION_SUBSHELL_ELECTRON_SCATTERING_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectronState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_ElectronScatteringDistribution.hpp"
#include "Utility_InterpolatedFullyTabularTwoDDistribution.hpp"

namespace MonteCarlo{

/*! The scattering distribution base class
 *  \details currently the binding energy is not taken into account when
 *  calculating the outgoing energy and direction of the original electron
 */
class ElectroionizationSubshellElectronScatteringDistribution : public ElectronScatteringDistribution
{

public:

  //! Typedef for the two d distributions
  typedef Utility::FullyTabularTwoDDistribution TwoDDist;

  //! Constructor
  ElectroionizationSubshellElectronScatteringDistribution(
    const std::shared_ptr<TwoDDist>&
      electroionization_subshell_scattering_distribution,
    const double& binding_energy,
    const bool& use_weighted_interpolation = true );

  //! Destructor
  virtual ~ElectroionizationSubshellElectronScatteringDistribution()
  { /* ... */ }

  //! Return the binding energy
  double getBindingEnergy() const;

  //! Return the max secondary (knock-on) electron energy for a given incoming electron energy
  double getMaxSecondaryEnergyAtIncomingEnergy( const double energy ) const;

  //! Evaluate the distribution
  double evaluate( const double incoming_energy,
                   const double scattering_angle ) const;

  //! Evaluate the PDF value for a given incoming and outgoing energy
  double evaluatePDF( const double incoming_energy,
                      const double outgoing_energy_1 ) const;

  //! Evaluate the CDF
  double evaluateCDF( const double incoming_energy,
                      const double scattering_angle ) const;

  //! Sample an outgoing energy and direction from the distribution
  void sample( const double incoming_energy,
               double& knock_on_energy,
               double& knock_on_angle_cosine  ) const;

  // Sample the distribution
  void sample( const double incoming_energy,
               double& outgoing_energy,
               double& knock_on_energy,
               double& scattering_angle_cosine,
               double& knock_on_angle_cosine ) const;

  //! Sample an outgoing energy and direction and record the number of trials
  void sampleAndRecordTrials( const double incoming_energy,
                              double& knock_on_energy,
                              double& knock_on_angle_cosine,
                              unsigned& trials ) const;

  //! Randomly scatter the electron
  void scatterElectron( MonteCarlo::ElectronState& electron,
                        MonteCarlo::ParticleBank& bank,
                        Data::SubshellType& shell_of_interaction ) const;

private:

  //! Sample a secondary energy from the distribution
  double sampleWeighted( const double incoming_energy ) const;

  //! Sample a secondary energy from the distribution
  double sampleExact( const double incoming_energy ) const;

  // Calculate the outgoing angle cosine
  double outgoingAngle( const double incoming_energy,
                        const double outgoing_energy ) const;

  // electroionization subshell scattering cross sections
  std::shared_ptr<TwoDDist> d_electroionization_subshell_scattering_distribution;

  // Subshell binding energy
  double d_binding_energy;

  // Bool to use a weighted interpolation routine to sample the distribution
  bool d_use_weighted_interpolation;

  // The secondary energy function pointer
  std::function<double ( const double )> d_sample_func;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELECTROIONIZATION_SUBSHELL_ELECTRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationSubshellElectronScatteringDistribution.hpp
//---------------------------------------------------------------------------//
