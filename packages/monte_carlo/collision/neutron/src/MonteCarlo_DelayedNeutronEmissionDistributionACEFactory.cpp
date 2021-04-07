//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DelayedNeutronEmissionDistributionACEFactory.cpp
//! \author Alex Robinson
//! \brief  Delayed neutron emission distribution factory class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_DelayedNeutronEmissionDistributionACEFactory.hpp"
#include "MonteCarlo_DelayedNeutronEmissionDistribution.hpp"
#include "MonteCarlo_NuclearScatteringEnergyDistributionACEFactory.hpp"
#include "MonteCarlo_NuclearScatteringAngularDistributionACEFactory.hpp"
#include "MonteCarlo_NuclearScatteringDistributionFactoryHelpers.hpp"
#include "MonteCarlo_IndependentEnergyAngleNuclearScatteringDistribution.hpp"
#include "MonteCarlo_LabSystemConversionPolicy.hpp"
#include "MonteCarlo_NuclearReactionType.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
DelayedNeutronEmissionDistributionACEFactory::DelayedNeutronEmissionDistributionACEFactory(
			   const std::string& table_name,
			   const double atomic_weight_ratio,
			   const Utility::ArrayView<const double>& bdd_block,
			   const Utility::ArrayView<const double>& dnedl_block,
		           const Utility::ArrayView<const double>& dned_block )
  : d_atomic_weight_ratio( atomic_weight_ratio )
{
  initializeBasicDelayedNeutronData( table_name, bdd_block );
  initializeEmissionDistributions( table_name,
				   atomic_weight_ratio,
				   dnedl_block,
				   dned_block );
}

// Create the delayed neutron emission distribution
void DelayedNeutronEmissionDistributionACEFactory::createEmissionDistribution(
       std::shared_ptr<const NuclearScatteringDistribution<NeutronState,NeutronState> >&
       distribution ) const
{
  distribution.reset( new DelayedNeutronEmissionDistribution(
				  d_atomic_weight_ratio,
				  d_precursor_group_decay_consts,
				  d_precursor_group_prob_distributions,
				  d_precursor_group_emission_distributions ) );
}

// Return the precursor group decay constants
const std::vector<double>&
DelayedNeutronEmissionDistributionACEFactory::getPrecursorGroupDecayConsts() const
{
  return d_precursor_group_decay_consts;
}

// Return the precursor group probability distributions
const std::vector<std::shared_ptr<const Utility::UnivariateDistribution> >&
DelayedNeutronEmissionDistributionACEFactory::getPrecursorGroupProbDists() const
{
  return d_precursor_group_prob_distributions;
}

// Return the precursor group emission distributions
const std::vector<std::shared_ptr<const NuclearScatteringDistribution<NeutronState,NeutronState> > >&
DelayedNeutronEmissionDistributionACEFactory::getPrecursorGroupEmissionDists() const
{
  return d_precursor_group_emission_distributions;
}

// Initialize basic delayed neutron data
void DelayedNeutronEmissionDistributionACEFactory::initializeBasicDelayedNeutronData(
			    const std::string& table_name,
			    const Utility::ArrayView<const double>& bdd_block )
{
  Utility::ArrayView<const double> precursor_prob_energy_grid;
  Utility::ArrayView<const double> precursor_prob_values;
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
			"Multiple interpolation regions found in the "
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
    std::shared_ptr<const Utility::UnivariateDistribution> group_prob_dist(
	               new Utility::TabularDistribution<Utility::LinLin>(
						    precursor_prob_energy_grid,
						    precursor_prob_values ) );

    d_precursor_group_prob_distributions.push_back( group_prob_dist );
  }
}

// Initialize the emission distributions
void
DelayedNeutronEmissionDistributionACEFactory::initializeEmissionDistributions(
			   const std::string& table_name,
			   const double atomic_weight_ratio,
			   const Utility::ArrayView<const double>& dnedl_block,
			   const Utility::ArrayView<const double>& dned_block )
{
  // Create the default (isotropic in lab system)
  std::shared_ptr<const NuclearScatteringAngularDistribution>
    default_angular_distribution;

  NuclearScatteringAngularDistributionACEFactory::createIsotropicDistribution(
						default_angular_distribution );

  // Create the energy distributions
  std::vector<unsigned> energy_dist_array_sizes;
  Utility::ArrayView<const double> energy_dist_array;

  calculateDistArraySizes( dnedl_block, dned_block, energy_dist_array_sizes );

  unsigned dist_index, ace_law;

  std::shared_ptr<const NuclearScatteringDistribution<NeutronState,NeutronState> >
    emission_distribution;
  std::shared_ptr<const NuclearScatteringEnergyDistribution> energy_distribution;

  for( unsigned i = 0u; i < dnedl_block.size(); ++i )
  {
    dist_index = static_cast<unsigned>( dnedl_block[i] ) - 1u;

    energy_dist_array = dned_block( dist_index,
				    energy_dist_array_sizes[i] );

    ace_law = static_cast<unsigned>( energy_dist_array[1] );

    if( ace_law != 44 )
    {
      NuclearScatteringEnergyDistributionACEFactory::createDistribution(
						     energy_dist_array,
						     dist_index,
						     table_name,
						     N__TOTAL_FISSION_REACTION,
						     energy_distribution );

      emission_distribution.reset(
	new IndependentEnergyAngleNuclearScatteringDistribution<NeutronState,
	                                                        NeutronState,
	                                                        LabSystemConversionPolicy>(
					      atomic_weight_ratio,
					      energy_distribution,
					      default_angular_distribution ) );
    }
    else
    {
      NuclearScatteringEnergyDistributionACEFactory::createAceLaw44Distribution(
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

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_DelayedNeutronEmissionDistributionACEFactory.cpp
//---------------------------------------------------------------------------//
