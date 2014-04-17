//---------------------------------------------------------------------------//
//!
//! \file   ElasticScatteringDistribution.hpp
//! \author Alex Robinson
//! \brief  The elastic scattering distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef ELASTIC_SCATTERING_DISTRIBUTION_HPP
#define ELASTIC_SCATTERING_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FACEMC Includes
#include "ScatteringDistribution.hpp"
#include "OneDDistribution.hpp"
#include "Tuple.hpp"

namespace FACEMC{

//! The elastic scattering distribution class
class ElasticScatteringDistribution : public ScatteringDistribution
{

public:
  
  //! Constructor
  ElasticScatteringDistribution( 
		 const double atomic_weight_ratio,
		 Teuchos::Array<Pair<double,Teuchos::RCP<OneDDistribution> > >&
		 angular_scattering_distribution );

  //! Destructor
  ~ElasticScatterinDistribution()
  { /* ... */ }
  
  //! Randomly scatter the particle
  void scatterParticle( BasicParticleState& particle,
			const double atomic_weight_ratio,
			const double temperature ) const;

private:

  // Sample center-of-mass scattering angle cosine
  double sampleCMScatteringAngleCosine( const double energy );

  // The incoming energy dependent angular scattering distribution
  Teuchos::Array<Pair<double,Teuchos::RCP<OneDDistribution> > > 
  d_angular_scattering_distribution;
};

} // end FACEMC namespace

#endif // end ELASTIC_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end ElasticScatteringDistribution.hpp
//---------------------------------------------------------------------------//
