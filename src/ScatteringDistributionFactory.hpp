//---------------------------------------------------------------------------//
//! 
//! \file   ScatteringDistributionFactor.hpp
//! \author Alex Robinson
//! \brief  Scattering distribution factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef SCATTERING_DISTRIBUTION_FACTORY_HPP
#define SCATTERING_DISTRIBUTION_FACTORY_HPP

// Std Lib Includes
#include <string>

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FACEMC Includes
#include "ScatteringDistribution.hpp"
#include "ElasticScatteringDistribution.hpp"
#include "NuclearReactionType.hpp"

namespace FACEMC{

//! The scattering distribution factory class
class ScatteringDistributionFactory
{
  
public:

  //! Constructor 
  ScatteringDistributionFactory( const std::string& table_name,
				 const double atomic_weight_ratio );

  //! Destructor
  ~ScatteringDistributionFactory()
  { /* ... */ }

  //! Create a scattering distribution
  Teuchos::RCP<ScatteringDistribution> 
  createElasticScatteringDistribution( 
	    const Teuchos::ArrayView<double>& raw_angular_distribution ) const;

  //! Create a scattering distribution 
  Teuchos::RCP<ScatteringDistribution> 
  createDistribution( 
		    const Teuchos::ArrayView<double>& raw_angular_distribution,
		    const Teuchos::ArrayView<double>& raw_energy_distribution,
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

#endif // end SCATTERING_DISTRIBUTION_FACTORY_HPP

//---------------------------------------------------------------------------//
// end ScatteringDistributionFactory.hpp
//---------------------------------------------------------------------------//
