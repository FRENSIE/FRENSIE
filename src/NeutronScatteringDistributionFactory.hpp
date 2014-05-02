//---------------------------------------------------------------------------//
//! 
//! \file   NeutronScatteringDistributionFactor.hpp
//! \author Alex Robinson
//! \brief  Neutron scattering distribution factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef NEUTRON_SCATTERING_DISTRIBUTION_FACTORY_HPP
#define NEUTRON_SCATTERING_DISTRIBUTION_FACTORY_HPP

// Std Lib Includes
#include <string>

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FACEMC Includes
#include "NeutronScatteringDistribution.hpp"
#include "ElasticNeutronScatteringDistribution.hpp"
#include "NuclearReactionType.hpp"

namespace FACEMC{

//! The scattering distribution factory class
class NeutronScatteringDistributionFactory
{
  
public:

  //! Constructor 
  NeutronScatteringDistributionFactory( const std::string& table_name,
					const double atomic_weight_ratio );

  //! Destructor
  ~NeutronScatteringDistributionFactory()
  { /* ... */ }

  //! Create a scattering distribution
  Teuchos::RCP<NeutronScatteringDistribution> 
  createElasticNeutronScatteringDistribution( 
      const Teuchos::ArrayView<const double>& raw_angular_distribution ) const;

  //! Create a scattering distribution 
  Teuchos::RCP<NeutronScatteringDistribution> 
  createDistribution( 
	      const Teuchos::ArrayView<const double>& raw_angular_distribution,
	      const Teuchos::ArrayView<const double>& raw_energy_distribution,
	      const NuclearReactionType reaction_type ) const;

private:

  // The default (isotropic) angle cosine distribution
  static Teuchos::RCP<OneDDistribution> isotropic_angle_cosine_dist;

  // The table name
  std::string d_table_name;

  // The atomic weight ratio
  double d_atomic_weight_ratio;
};

} // end FACEMC namespace

#endif // end NEUTRON_SCATTERING_DISTRIBUTION_FACTORY_HPP

//---------------------------------------------------------------------------//
// end NeutronScatteringDistributionFactory.hpp
//---------------------------------------------------------------------------//
