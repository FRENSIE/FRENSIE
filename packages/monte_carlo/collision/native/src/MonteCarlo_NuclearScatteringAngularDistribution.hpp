//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NuclearScatteringAngularDistribution.hpp
//! \author Alex Robinson, Alex Bennett
//! \brief  The nuclear scattering angular distribution base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_NUCLEAR_SCATTERING_ANGULAR_DISTRIBUTION
#define MONTE_CARLO_NUCLEAR_SCATTERING_ANGULAR_DISTRIBUTION

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"

namespace MonteCarlo{

//! The angular scattering distribution base class
/*! \todo Write unit test for nuclear scattering angular distribution class
 */
class NuclearScatteringAngularDistribution
{

public:

  //! Typedef for energy dependent angular distribution
  typedef Teuchos::Array<Utility::Pair<double,
			       Teuchos::RCP<const Utility::OneDDistribution> > > 
  AngularDistribution;
  
  //! Constructor
  NuclearScatteringAngularDistribution( const AngularDistribution& dist );

  //! Destructor
  virtual ~NuclearScatteringAngularDistribution()
  { /* ... */ }


  //! Sample a scattering angle cosine
  virtual double sampleAngleCosine( const double energy ) const;

  //! Evaluate the PDF
  double evaluatePDF( const double energy,
		      const double scattering_angle_cosine ) const;

private:

  // The angular distribution
  AngularDistribution d_angular_distribution;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_NUCLEAR_SCATTERING_ANGULAR_DISTRIBUTION

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclearScatteringAngularDistribution.hpp
//---------------------------------------------------------------------------//
