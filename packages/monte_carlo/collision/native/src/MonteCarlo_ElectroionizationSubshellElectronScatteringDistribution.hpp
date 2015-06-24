//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroionizationSubshellElectronScatteringDistribution.hpp
//! \author Luke Kersting
//! \brief  The electron electroionization subshell scattering distribution base class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTROIONIZATION_SUBSHELL_ELECTRON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_ELECTROIONIZATION_SUBSHELL_ELECTRON_SCATTERING_DISTRIBUTION_HPP

// Std Lib Includes
#include <limits>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectronState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_ElectronScatteringDistribution.hpp"
#include "Utility_TabularOneDDistribution.hpp"

namespace MonteCarlo{

/*! The scattering distribution base class
 *  \details currently the binding energy is not taken into account when 
 *  calculating the outgoing energy and direction of the original electron
 */
class ElectroionizationSubshellElectronScatteringDistribution : public ElectronScatteringDistribution
{

public:

  //! Typedef for the  electroionization subshell distribution
  typedef Teuchos::Array<Utility::Pair<double,
		       Teuchos::RCP<const Utility::TabularOneDDistribution> > >
  ElectroionizationSubshellDistribution;

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

  //! Return the min incoming energy
  double getMinEnergy() const;

  //! Return the Max incoming energy
  double getMaxEnergy() const;

  //! Return the max incoming electron energy for a given knock-on electron energy
  double getMaxIncomingEnergyAtOutgoingEnergy( const double energy ) const;

  //! Evaluate the PDF value for a given incoming and knock-on energy
  double evaluatePDF( const double incoming_energy, 
                      const double knock_on_energy ) const;

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
                        SubshellType& shell_of_interaction ) const;
                        
private:

  // electroionization subshell scattering cross sections
  ElectroionizationSubshellDistribution 
     d_electroionization_subshell_scattering_distribution;

  // Subshell binding energy
  double d_binding_energy;

  // Calculate the outgoing angle cosine
  double outgoingAngle( const double incoming_energy,
                        const double energy ) const;

};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELECTROIONIZATION_SUBSHELL_ELECTRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationSubshellElectronScatteringDistribution.hpp
//---------------------------------------------------------------------------//
