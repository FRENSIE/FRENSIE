//---------------------------------------------------------------------------//
//!
//! \file MonteCarlo_ElectronScatteringAngularDistribution.hpp
//! \author Luke Kersting
//! \brief The Electron scattering angular distribution base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTRON_SCATTERING_ANGULAR_DISTRIBUTION_HPP
#define MONTE_CARLO_ELECTRON_SCATTERING_ANGULAR_DISTRIBUTION_HPP

// Trilinos Includse
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectronState.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_OneDDistribution.hpp"

namespace MonteCarlo{

//! The scattering angular distribution base class
class ElectronScatteringAngularDistribution
{

public:

  //! Typedef for energy dependent angular distribution
  typedef Teuchos::Array<Utility::Pair<double,
			       Teuchos::RCP<Utility::OneDDistribution> > > 
  AngularDistribution;
  
  //! Constructor
  ElectronScatteringAngularDistribution( const AngularDistribution& dist );

  //! Destructor
  virtual ~NeutronScatteringAngularDistribution()
  { /* ... */ }

  //! Sample a scattering angle cosine
  virtual double sampleAngleCosine( const double energy ) const;

  //! Evaluate the PDF
  double evaluatePDF( const double energy,
		      const double cm_scattering_angle_cosine ) const;

private:

  // The angular distribution
  AngularDistribution d_angular_distribution;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELECTRON_SCATTERING_ANGULAR_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectronScatteringAngularDistribution.hpp
//---------------------------------------------------------------------------//
