//---------------------------------------------------------------------------//
//!
//! \file   ElasticNeutronScatteringDistribution.hpp
//! \author Alex Robinson
//! \brief  The elastic scattering distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef ELASTIC_NEUTRON_SCATTERING_DISTRIBUTION_HPP
#define ELASTIC_NEUTRON_SCATTERING_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FACEMC Includes
#include "NeutronNeutronScatteringDistribution.hpp"
#include "OneDDistribution.hpp"
#include "Tuple.hpp"

namespace FACEMC{

//! The elastic scattering distribution class
class ElasticNeutronScatteringDistribution : public NeutronNeutronScatteringDistribution
{

public:
  
  //! Constructor
  ElasticNeutronScatteringDistribution( 
	   const double atomic_weight_ratio,
	   const Teuchos::Array<Pair<double,Teuchos::RCP<OneDDistribution> > >&
	   angular_scattering_distribution );

  //! Destructor
  ~ElasticNeutronScatteringDistribution()
  { /* ... */ }
  
  //! Randomly scatter the neutron
  void scatterNeutron( NeutronState& neutron,
		       const double temperature ) const;

private:

  // Sample center-of-mass scattering angle cosine
  double sampleCMScatteringAngleCosine( const double energy ) const;

  // The incoming energy dependent angular scattering distribution
  Teuchos::Array<Pair<double,Teuchos::RCP<OneDDistribution> > > 
  d_angular_scattering_distribution;
};

} // end FACEMC namespace

#endif // end ELASTIC_NEUTRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end ElasticNeutronScatteringDistribution.hpp
//---------------------------------------------------------------------------//
