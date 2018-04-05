//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NeutronNuclearScatteringDistributionACEFactory.cpp
//! \author Alex Robinson
//! \brief  Neutron nuclear scattering distribution factory class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_NeutronNuclearScatteringDistributionACEFactory.hpp"

namespace MonteCarlo{

// Constructor
NeutronNuclearScatteringDistributionACEFactory::NeutronNuclearScatteringDistributionACEFactory(
		       const std::string& table_name,
		       const double atomic_weight_ratio,
		       const Data::XSSNeutronDataExtractor& raw_nuclide_data )
  : NuclearScatteringDistributionACEFactory<MonteCarlo::NeutronState,MonteCarlo::NeutronState>(
					   table_name,
					   atomic_weight_ratio,
					   raw_nuclide_data.extractMTRBlock(),
					   raw_nuclide_data.extractTYRBlock(),
					   raw_nuclide_data.extractLANDBlock(),
					   raw_nuclide_data.extractANDBlock(),
					   raw_nuclide_data.extractLDLWBlock(),
					   raw_nuclide_data.extractDLWBlock() )
{ /* ... */ }

// Create the elastic scattering distribution
void NuclearScatteringDistributionACEFactoryHelper<NeutronState,NeutronState>::createElasticScatteringDistribution(
	     std::shared_ptr<const NuclearScatteringDistribution<NeutronState,NeutronState> >& distribution,
             const std::string ace_table_name,
             const bool defined_in_cm_system,
             const double atomic_weight_ratio,
             const double free_gas_threshold,
             const std::shared_ptr<const NuclearScatteringAngularDistribution>&
             angular_distribution )
{
  TEST_FOR_EXCEPTION( !defined_in_cm_system,
		      std::runtime_error,
		      "elastic scattering in ACE table "
		      << ace_table_name << " is specified in the Lab "
		      "system. Elastic scattering must always be in the "
		      "CM system, which indicates that there is a problem "
		      "in the ACE table!" );

  distribution.reset(
	new ElasticNeutronNuclearScatteringDistribution( atomic_weight_ratio,
                                                         free_gas_threshold,
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
// end MonteCarlo_NeutronNuclearScatteringDistributionACEFactory.cpp
//---------------------------------------------------------------------------//
