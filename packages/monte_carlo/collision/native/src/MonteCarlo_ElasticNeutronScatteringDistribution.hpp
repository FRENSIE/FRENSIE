//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElasticNeutronScatteringDistribution.hpp
//! \author Alex Robinson
//! \brief  The elastic scattering distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELASTIC_NEUTRON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_ELASTIC_NEUTRON_SCATTERING_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_NeutronScatteringDistribution.hpp"
#include "MonteCarlo_NeutronScatteringAngularDistribution.hpp"
#include "Utility_OneDDistribution.hpp"
#include "Utility_Tuple.hpp"

namespace MonteCarlo{

//! The elastic scattering distribution class
class ElasticNeutronScatteringDistribution : public NeutronScatteringDistribution
{

public:
  
  //! Constructor
  ElasticNeutronScatteringDistribution( 
		      const double atomic_weight_ratio,
                      const Teuchos::RCP<NeutronScatteringAngularDistribution>&
		      angular_scattering_distribution );

  //! Destructor
  ~ElasticNeutronScatteringDistribution()
  { /* ... */ }
  
  //! Randomly scatter the neutron
  void scatterNeutron( NeutronState& neutron,
		       const double temperature ) const;

private:

  // The incoming energy dependent angular scattering distribution
  Teuchos::RCP<NeutronScatteringAngularDistribution> 
  d_angular_scattering_distribution;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELASTIC_NEUTRON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElasticNeutronScatteringDistribution.hpp
//---------------------------------------------------------------------------//
