//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NuclearScatteringDistributionACEFactoryHelper.cpp
//! \author Alex Robinson
//! \brief  Nuclear scattering distribution factory helper class def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_NuclearScatteringDistributionACEFactoryHelper.hpp"
#include "MonteCarlo_ElasticNeutronNuclearScatteringDistribution.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

// Create the elastic scattering distribution
void NuclearScatteringDistributionACEFactoryHelper<NeutronState,NeutronState>::createElasticScatteringDistribution( 
		      Teuchos::RCP<NuclearScatteringDistribution<NeutronState,NeutronState> >& distribution,
		      const std::string ace_table_name,
		      const bool defined_in_cm_system,
		      const double atomic_weight_ratio,
          const Teuchos::RCP<NuclearScatteringAngularDistribution>&
		      angular_distribution )
{
  TEST_FOR_EXCEPTION( !defined_in_cm_system,
		      std::runtime_error,
		      "Error: elastic scattering in ACE table "
		      << ace_table_name << " is specified in the Lab "
		      "system. Elastic scattering must always be in the "
		      "CM system, which indicates that there is a problem "
		      "in the ACE table!" );
  
  distribution.reset( 
	new ElasticNeutronNuclearScatteringDistribution( atomic_weight_ratio,
							 angular_distribution ) );
}

// Check if elastic scattering is handled implicitly in ACE table
/*! \details In continuous-energy neutron tables an elastic scattering 
 * distribution is always given and will therefore not appear in the mtr block.
 */
bool NuclearScatteringDistributionACEFactoryHelper<NeutronState,NeutronState>::isElasticScatteringImplicit()
{
  return true;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclearScatteringDistributionACEFactoryHelper.cpp
//---------------------------------------------------------------------------//
