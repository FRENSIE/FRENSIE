//---------------------------------------------------------------------------//
//!
//! \file   Facemc_NeutronScatteringAngularDistribution.hpp
//! \author Alex Robinson, Alex Bennett
//! \brief  The neutron scattering angular distribution base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_NEUTRON_SCATTERING_ANGULAR_DISTRIBUTION
#define FACEMC_NEUTRON_SCATTERING_ANGULAR_DISTRIBUTION

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Facemc_NeutronState.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_OneDDistribution.hpp"

namespace Facemc{

//! The angular scattering distribution base class
class NeutronScatteringAngularDistribution
{

public:

  //! Typedef for energy dependent angular distribution
  typedef Teuchos::Array<Utility::Pair<double,
			       Teuchos::RCP<Utility::OneDDistribution> > > 
  AngularDistribution;
  
  //! Constructor
  NeutronScatteringAngularDistribution( const AngularDistribution& dist,
					const bool is_cm_dist = true );

  //! Destructor
  virtual ~NeutronScatteringAngularDistribution()
  { /* ... */ }

  //! Return if the distribution is in the CM or Lab system
  bool isCMDistribution() const;
  
  //! Sample a scattering angle cosine
  virtual double sampleAngleCosine( const double energy ) const;

private:
  
  // The angular distribution
  AngularDistribution d_angular_distribution;

  // Records if the distribution is in the CM or Lab system
  bool d_is_cm_dist;
};

// Return if the distribution is in the CM or Lab system
inline bool
NeutronScatteringAngularDistribution::isCMDistribution() const
{
  return d_is_cm_dist;
}  

} // end Facemc namespace

#endif // end FACEMC_NEUTRON_SCATTERING_ANGULAR_DISTRIBUTION

//---------------------------------------------------------------------------//
// end Facemc_NeutronScatteringAngularDistribution.hpp
//---------------------------------------------------------------------------//
