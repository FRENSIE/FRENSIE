//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NeutronScatteringAngularDistribution.hpp
//! \author Alex Robinson, Alex Bennett
//! \brief  The neutron scattering angular distribution base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_NEUTRON_SCATTERING_ANGULAR_DISTRIBUTION
#define MONTE_CARLO_NEUTRON_SCATTERING_ANGULAR_DISTRIBUTION

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_NeutronState.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_OneDDistribution.hpp"

namespace MonteCarlo{

//! The angular scattering distribution base class
class NeutronScatteringAngularDistribution
{

public:

  //! Typedef for energy dependent angular distribution
  typedef Teuchos::Array<Utility::Pair<double,
			       Teuchos::RCP<Utility::OneDDistribution> > > 
  AngularDistribution;
  
  //! Constructor
  NeutronScatteringAngularDistribution( const AngularDistribution& dist );

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

#endif // end MONTE_CARLO_NEUTRON_SCATTERING_ANGULAR_DISTRIBUTION

//---------------------------------------------------------------------------//
// end MonteCarlo_NeutronScatteringAngularDistribution.hpp
//---------------------------------------------------------------------------//
