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
                                     Teuchos::RCP<Utility::OneDDistribution> > >
                                       ElectroionizationSubshellDistribution;

  //! Constructor 
  ElectroionizationSubshellElectronScatteringDistribution(
    ElectroionizationSubshellDistribution& 
      electroionization_subshell_scattering_distribution );

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

  // Calculate the outgoing angle cosine of the original electron
  double polarDeflectionAngle( double& incoming_energy, 
                               double& knock_on_energy ) const;

  // Calculate the outgoing angle cosine of the knock-on electron
  double knockOnDeflectionAngle( double& incoming_energy, 
                                 double& knock_on_energy ) const;

};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELECTROIONIZATION_SUBSHELL_ELECTRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationSubshellElectronScatteringDistribution.hpp
//---------------------------------------------------------------------------//
