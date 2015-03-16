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
#include "Utility_OneDDistribution.hpp"

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
                         Teuchos::RCP<const Utility::OneDDistribution> > >
                            ElectroionizationSubshellDistribution;

  //! Constructor 
  ElectroionizationSubshellElectronScatteringDistribution(
    const ElectroionizationSubshellDistribution& 
      electroionization_subshell_scattering_distribution,
    const double& binding_energy );

  //! Destructor 
  virtual ~ElectroionizationSubshellElectronScatteringDistribution()
  { /* ... */ }

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

  // Calculate the outgoing angle cosine of the original electron
  double polarDeflectionAngle( double& incoming_momentum_squared,
                               double& outgoing_momentum_squared,
                               double& knock_on_energy ) const;

  // Calculate the outgoing angle cosine of the knock-on electron
  double knockOnDeflectionAngle( double& incoming_momentum_squared,
                                 double& outgoing_momentum_squared,
                                 double& outgoing_cosine ) const;

};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELECTROIONIZATION_SUBSHELL_ELECTRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationSubshellElectronScatteringDistribution.hpp
//---------------------------------------------------------------------------//
