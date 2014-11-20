//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroionizationElectronScatteringDistribution.hpp
//! \author Luke Kersting
//! \brief  The electron electroionization scattering distribution base class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTROIONIZATION_ELECTRON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_ELECTROIONIZATION_ELECTRON_SCATTERING_DISTRIBUTION_HPP

// Std Lib Includes
#include <limits>

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectronState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_ElectronScatteringDistribution.hpp"
#include "Utility_OneDDistribution.hpp"

namespace MonteCarlo{

//! The scattering distribution base class
class ElectroionizationElectronScatteringDistribution : public ElectronScatteringDistribution
{

public:

  //! Typedef for the  electroionization distribution
  typedef Teuchos::Array<Utility::Pair<double,
                                     Teuchos::RCP<Utility::OneDDistribution> > >
                                     ElectroionizationDistribution;

  //! Constructor 
  ElectroionizationElectronScatteringDistribution(
    Teuchos::RCP<Utility::OneDDistribution>& electroionization_subshell_cross_sections,
    ElectroionizationDistribution& electroionization_scattering_distribution );

  //! Destructor 
  virtual ~ElectroionizationElectronScatteringDistribution()
  { /* ... */ }

  //! Randomly sample the subshell of interaction
  unsigned sampleSubshell() const;

  //! Randomly scatter the electron
  void scatterElectron( ElectronState& electron,
	                    ParticleBank& bank,
                        unsigned& shell_of_interaction ) const;

private:

  // electroionization scattering distribution
  ElectroionizationDistribution d_electroionization_scattering_distribution;

  // electroionization subshell scattering cross sections
  Teuchos::RCP<Utility::OneDDistribution> d_electroionization_subshell_cross_sections;

  // Calculate the outgoing angle cosine of the original electron
  double polarDeflectionAngle( double& incoming_energy, double& knock_on_energy ) const;

  // Calculate the outgoing angle cosine of the knock-on electron
  double knockOnDeflectionAngle( double& incoming_energy, double& knock_on_energy ) const;

};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELECTROIONIZATION_ELECTRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroionizationElectronScatteringDistribution.hpp
//---------------------------------------------------------------------------//
