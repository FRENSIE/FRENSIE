//---------------------------------------------------------------------------//
//!
//! \file   Facemc_DelayedNeutronEmissionDistributionFactory.cpp
//! \author Alex Robinson
//! \brief  Delayed neutron emission distribution factory class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Facemc_DelayedNeutronEmissionDistributionFactory.hpp"
#include "Facemc_DelayedNeutronEmissionDistribution.hpp"
#include "Facemc_NeutronScatteringEnergyDistributionFactory.hpp"
#include "Facemc_NeutronScatteringAngularDistributionFactory.hpp"
#include "Facemc_NeutronScatteringDistributionFactoryHelpers.hpp"
#include "Facemc_IndependentEnergyAngleNeutronScatteringDistribution.hpp"
#include "Facemc_LabSystemConversionPolicy.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Facemc{

// Constructor
DelayedNeutronEmissionDistributionFactory::DelayedNeutronEmissionDistributionFactory(
			   const std::string& table_name,
			   const double atomic_weight_ratio,
			   const Teuchos::ArrayView<const double>& bdd_block,
			   const Teuchos::ArrayView<const double>& dnedl_block,
		           const Teuchos::ArrayView<const double>& dned_block )
  : d_atomic_weight_ratio( atomic_weight_ratio )
{
  initializeBasicDelayedNeutronData( table_name, bdd_block );
  initializeEmissionDistributions( table_name,
				   atomic_weight_ratio,
				   dnedl_block,
				   dned_block );
}

// Create the delayed neutron emission distribution
void DelayedNeutronEmissionDistributionFactory::createEmissionDistribution(
	      Teuchos::RCP<NeutronScatteringDistribution>& distribution ) const
{
  distribution.reset( new DelayedNeutronEmissionDistribution(
				  d_atomic_weight_ratio,
				  d_precursor_group_decay_consts,
				  d_precursor_group_prob_distributions,
				  d_precursor_group_emission_distributions ) );
}

// Return the precursor group decay constants
const Teuchos::Array<double>& 
DelayedNeutronEmissionDistributionFactory::getPrecursorGroupDecayConsts() const
{
  return d_precursor_group_decay_consts;
}

// Return the precursor group probability distributions
const Teuchos::Array<Teuchos::RCP<Utility::OneDDistribution> >&
DelayedNeutronEmissionDistributionFactory::getPrecursorGroupProbDists() const
{
  return d_precursor_group_prob_distributions;
}

// Return the precursor group emission distributions
const Teuchos::Array<Teuchos::RCP<NeutronScatteringDistribution> >&
DelayedNeutronEmissionDistributionFactory::getPrecursorGroupEmissionDists() const
{
  return d_precursor_group_emission_distributions;
}

// Initialize basic delayed neutron data
void DelayedNeutronEmissionDistributionFactory::initializeBasicDelayedNeutronData( 
			    const std::string& table_name,
			    const Teuchos::ArrayView<const double>& bdd_block )
{
  Teuchos::ArrayView<const double> precursor_prob_energy_grid;
  Teuchos::ArrayView<const double> precursor_prob_values;
  double group_decay_const;
  unsigned number_of_interp_regions, number_of_energies;
  
  unsigned bdd_loc = 0u;

  while( bdd_loc < bdd_block.size() )
  {
    // Extract the group decay constant
    group_decay_const = bdd_block[bdd_loc];

    // The group decay constants have units of inverse shakes in ACE files - 
    // convert to units of inverse seconds
    group_decay_const *= 1e8;

    d_precursor_group_decay_consts.push_back( group_decay_const );

    ++bdd_loc;

    // Extract the number of interpolation regions
    number_of_interp_regions = static_cast<unsigned>( bdd_block[bdd_loc] );

    TEST_FOR_EXCEPTION( number_of_interp_regions != 0u,
			std::runtime_error,
			"Error: Multiple interpolation regions found in the "
			"BDD block of ace table " << table_name << ", which "
			"is not currently supported!" );

    ++bdd_loc;
    
    // Extract the number of energies
    number_of_energies = static_cast<unsigned>( bdd_block[bdd_loc] );

    ++bdd_loc;
    
    // Extract the energy grid
    precursor_prob_energy_grid = bdd_block( bdd_loc, number_of_energies );
    
    bdd_loc += number_of_energies;

    // Extract the probabilities
    precursor_prob_values = bdd_block( bdd_loc, number_of_energies );

    bdd_loc += number_of_energies;
    
    // Create the group probability distribution
    Teuchos::RCP<Utility::OneDDistribution> group_prob_dist(
	               new Utility::TabularDistribution<Utility::LinLin>( 
						    precursor_prob_energy_grid,
						    precursor_prob_values ) );
    
    d_precursor_group_prob_distributions.push_back( group_prob_dist );
  }
}

// Initialize the emission distributions
void 
DelayedNeutronEmissionDistributionFactory::initializeEmissionDistributions(
			   const std::string& table_name,
			   const double atomic_weight_ratio,
			   const Teuchos::ArrayView<const double>& dnedl_block,
			   const Teuchos::ArrayView<const double>& dned_block )
{
  // Create the default (isotropic in lab system)
  Teuchos::RCP<NeutronScatteringAngularDistribution> 
    default_angular_distribution;

  NeutronScatteringAngularDistributionFactory::createIsotropicDistribution(
						default_angular_distribution );

  // Create the energy distributions
  Teuchos::Array<unsigned> energy_dist_array_sizes;
  Teuchos::ArrayView<const double> energy_dist_array;

  calculateDistArraySizes( dnedl_block, dned_block, energy_dist_array_sizes );

  unsigned dist_index, ace_law;
  
  Teuchos::RCP<NeutronScatteringDistribution> emission_distribution;
  Teuchos::RCP<NeutronScatteringEnergyDistribution> energy_distribution;
  
  for( unsigned i = 0u; i < dnedl_block.size(); ++i )
  {
    dist_index = static_cast<unsigned>( dnedl_block[i] ) - 1u;
    
    energy_dist_array = dned_block( dist_index, 
				    energy_dist_array_sizes[i] );
    
    ace_law = static_cast<unsigned>( energy_dist_array[1] );

    if( ace_law != 44 )
    {
      NeutronScatteringEnergyDistributionFactory::createDistribution( 
						     energy_dist_array,
						     dist_index,
						     table_name,
						     N__TOTAL_FISSION_REACTION,
						     energy_distribution );

      emission_distribution.reset( 
	  new IndependentEnergyAngleNeutronScatteringDistribution<LabSystemConversionPolicy>( 
					      atomic_weight_ratio,
					      energy_distribution,
					      default_angular_distribution ) );
    }
    else
    {
      NeutronScatteringEnergyDistributionFactory::createAceLaw44Distribution(
						     atomic_weight_ratio,
						     energy_dist_array,
						     dist_index,
						     table_name,
						     N__TOTAL_FISSION_REACTION,
						     false,
						     emission_distribution );
    }

    d_precursor_group_emission_distributions.push_back( emission_distribution);
  }
}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_DelayedNeutronEmissionDistributionFactory.cpp
//---------------------------------------------------------------------------//
