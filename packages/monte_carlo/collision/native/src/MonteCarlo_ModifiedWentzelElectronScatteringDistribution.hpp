//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ModifiedWentzelElectronScatteringDistribution.hpp
//! \author Luke Kersting
//! \brief  The electron modified Wentzel scattering distribution base class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_MODIFIED_WENTZEL_ELECTRON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_MODIFIED_WENTZEL_ELECTRON_SCATTERING_DISTRIBUTION_HPP

// Std Lib Includes
#include <limits>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectronState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "MonteCarlo_ElectronScatteringDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_OneDDistribution.hpp"

namespace MonteCarlo{

//! The scattering distribution base class
class ModifiedWentzelElectronScatteringDistribution : public ElectronScatteringDistribution
{

public:

  //! Typedef for energy dependent modified Wentzel parameter distribution
  typedef Teuchos::Array<  Utility::Pair< double, Utility::Pair<double,double> >  >
//  typedef Teuchos::RCP<double>
                              MWDistribution;

  //! Constructor
  ModifiedWentzelElectronScatteringDistribution(
  const MWDistribution& modified_wentzel_parameters,
  const double& average_angle_cosine  );

/*
  //! Constructor
  ModifiedWentzelElectronScatteringDistribution(
  const MWDistribution& parameter_A,
  const MWDistribution& parameter_B,
  const double& average_angle_cosine  );
*/
  //! Destructor
  virtual ~ModifiedWentzelElectronScatteringDistribution()
  { /* ... */ }

  //! Randomly scatter the electron
  void scatterElectron( ElectronState& electron,
	                    ParticleBank& bank) const;

private:

  MWDistribution d_modified_wentzel_parameters;

/*
  // Parameter B in modified Wentzel cdf
  Teuchos::RCP<double> d_parameter_A;

  // Parameter B in modified Wentzel cdf
  Teuchos::RCP<double> d_parameter_B;
*/
  // Average cosine of modified Wentzel distribution
  double d_average_angle_cosine;

};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_MODIFIED_WENTZEL_ELECTRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ModifiedWentzelElectronScatteringDistribution.hpp
//---------------------------------------------------------------------------//
