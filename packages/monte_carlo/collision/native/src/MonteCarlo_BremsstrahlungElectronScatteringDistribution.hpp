//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_BremsstrahlungElectronScatteringDistribution.hpp
//! \author Luke Kersting
//! \brief  The electron bremsstrahlung scattering distribution base class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_BREMSSTRAHLUNG_ELECTRON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_BREMSSTRAHLUNG_ELECTRON_SCATTERING_DISTRIBUTION_HPP

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
class BremsstrahlungElectronScatteringDistribution : public ElectronScatteringDistribution
{

public:

  //! Typedef for the  bremsstrahlung distribution
  typedef Teuchos::Array<Utility::Pair<double,
                                     Teuchos::RCP<Utility::OneDDistribution> > >
                                     BremsstrahlungDistribution;

  //! Constructor with simple analytical photon angular distribution
  BremsstrahlungElectronScatteringDistribution(
    BremsstrahlungDistribution& bremsstrahlung_scattering_distribution );

  //! Constructor with detailed tabular photon angular distribution
  BremsstrahlungElectronScatteringDistribution(
    const BremsstrahlungDistribution& bremsstrahlung_scattering_distribution,
    const Teuchos::RCP<Utility::OneDDistribution>& angular_distribution,
    const double lower_cutoff_energy,
    const double upper_cutoff_energy );

  //! Destructor 
  virtual ~BremsstrahlungElectronScatteringDistribution()
  { /* ... */ }

  //! Randomly scatter the electron
  void scatterElectron( ElectronState& electron,
	                    ParticleBank& bank,
                        unsigned& shell_of_interaction ) const;

private:

  // upper cutoff energy for the condensed-history method
  double d_upper_cutoff_energy;

  // lower cutoff energy for the condensed-history method
  double d_lower_cutoff_energy;

  // bremsstrahlung scattering distribution
  BremsstrahlungDistribution d_bremsstrahlung_scattering_distribution;

  // bremsstrahlung angular distribution of generated photons
  Teuchos::RCP<Utility::OneDDistribution> d_angular_distribution;

  // Sample the outgoing photon angle for energies above the condensed-history limit
  inline double SampleDetailedAngle(  double& electron_energy, 
                                      double& photon_energy ) const ;

  // Sample the outgoing photon angle for energies within the condensed-history limit
  inline double SampleSimpleAngle(  double& electron_energy, 
                                    double& photon_energy ) const ;

  // The doppler broadening function pointer
  boost::function<double ( double&, double& )> d_angular_distribution_func; 

};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_BREMSSTRAHLUNG_ELECTRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_BremsstrahlungElectronScatteringDistribution.hpp
//---------------------------------------------------------------------------//
