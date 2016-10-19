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
#include "MonteCarlo_TwoDDistributionHelpers.hpp"

namespace MonteCarlo{

/*! The scattering distribution base class
 *  \details currently the binding energy is not taken into account when
 *  calculating the outgoing energy and direction of the original electron
 */
class ElectroionizationSubshellElectronScatteringDistribution : public ElectronScatteringDistribution
{

public:

  //! Typedef for the  electroionization subshell distribution
  typedef MonteCarlo::TwoDDistribution ElectroionizationSubshellDistribution;

  //! Typedef for interpolation policy
  typedef Utility::LinLin InterpolationPolicy;

  //! Constructor
  ElectroionizationSubshellElectronScatteringDistribution(
    const ElectroionizationSubshellDistribution&
      electroionization_subshell_scattering_distribution,
    const double& binding_energy );

  //! Destructor
  virtual ~ElectroionizationSubshellElectronScatteringDistribution()
  { /* ... */ }

  //! Return the binding energy
  double getBindingEnergy() const;

  //! Return the max secondary (knock-on) electron energy for a given incoming electron energy
  double getMaxSecondaryEnergyAtIncomingEnergy( const double energy ) const;

  //! Evaluate the distribution
  double evaluate( const double incoming_energy,
                   const double scattering_angle ) const
  { /* ... */ }

  //! Evaluate the PDF value for a given incoming and outgoing energy (efficient)
  double evaluatePDF( const unsigned lower_bin_index,
                      const double incoming_energy,
                      const double outgoing_energy_1 ) const;

  //! Evaluate the PDF value for a given incoming and outgoing energy
  double evaluatePDF( const double incoming_energy,
                      const double outgoing_energy_1 ) const;

  //! Evaluate the CDF
  double evaluateCDF( const double incoming_energy,
                      const double scattering_angle ) const
  { /* ... */ }

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
  void scatterElectron( ElectronState& electron,
	                    ParticleBank& bank,
                        Data::SubshellType& shell_of_interaction ) const;

private:

  // electroionization subshell scattering cross sections
  ElectroionizationSubshellDistribution
     d_electroionization_subshell_scattering_distribution;

  // Subshell binding energy
  double d_binding_energy;

  // Calculate the outgoing angle cosine
  double outgoingAngle( const double incoming_energy,
                        const double outgoing_energy ) const;

};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELECTROIONIZATION_SUBSHELL_ELECTRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationSubshellElectronScatteringDistribution.hpp
//---------------------------------------------------------------------------//
