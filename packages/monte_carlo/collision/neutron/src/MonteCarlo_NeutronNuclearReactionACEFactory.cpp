//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NeutronNuclearReactionACEFactory.cpp
//! \author Alex Robinson
//! \brief  Neutron nuclear reaction factory class declaration
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "MonteCarlo_NeutronNuclearReactionACEFactory.hpp"
#include "MonteCarlo_PhotonProductionNuclearScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_NeutronScatteringReaction.hpp"
#include "MonteCarlo_NeutronAbsorptionReaction.hpp"
#include "MonteCarlo_NeutronFissionReaction.hpp"
#include "MonteCarlo_DetailedNeutronFissionReaction.hpp"
#include "MonteCarlo_EnergyDependentNeutronMultiplicityReaction.hpp"
#include "MonteCarlo_FissionNeutronMultiplicityDistributionACEFactory.hpp"
#include "MonteCarlo_DelayedNeutronEmissionDistributionACEFactory.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
/*! \details All blocks from the ACE file will be stored.
 * \param[in] raw_nuclide_data The necessary data blocks will be extracted
 * using the data extractor.
 */
NeutronNuclearReactionACEFactory::NeutronNuclearReactionACEFactory(
          const std::string& table_name,
          const double atomic_weight_ratio,
          const double temperature,
          const std::shared_ptr<const std::vector<double> >& energy_grid,
          const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
          grid_searcher,
          const SimulationProperties& properties,
          const Data::XSSNeutronDataExtractor& raw_nuclide_data )
{
  // Create the scattering distribution factory
  NeutronNuclearScatteringDistributionACEFactory
    scattering_dist_factory( table_name,
			     atomic_weight_ratio,
			     raw_nuclide_data );

  // Extract the required blocks
  Utility::ArrayView<const double> elastic_cross_section =
    raw_nuclide_data.extractElasticCrossSection();
  Utility::ArrayView<const double> mtr_block =
    raw_nuclide_data.extractMTRBlock();
  Utility::ArrayView<const double> lqr_block =
    raw_nuclide_data.extractLQRBlock();
  Utility::ArrayView<const double> tyr_block =
    raw_nuclide_data.extractTYRBlock();
  Utility::ArrayView<const double> lsig_block =
    raw_nuclide_data.extractLSIGBlock();
  Utility::ArrayView<const double> sig_block =
    raw_nuclide_data.extractSIGBlock();
  Utility::ArrayView<const double> land_block =
    raw_nuclide_data.extractLANDBlock();
  Utility::ArrayView<const double> and_block =
    raw_nuclide_data.extractANDBlock();
  Utility::ArrayView<const double> ldlw_block =
    raw_nuclide_data.extractLDLWBlock();
  Utility::ArrayView<const double> dlw_block =
    raw_nuclide_data.extractDLWBlock();
  Utility::ArrayView<const double> nu_block =
    raw_nuclide_data.extractNUBlock();
  Utility::ArrayView<const double> dnu_block =
    raw_nuclide_data.extractDNUBlock();
  Utility::ArrayView<const double> bdd_block =
    raw_nuclide_data.extractBDDBlock();
  Utility::ArrayView<const double> dnedl_block =
    raw_nuclide_data.extractDNEDLBlock();
  Utility::ArrayView<const double> dned_block =
    raw_nuclide_data.extractDNEDBlock();

  // Create a map of the reaction types and their table ordering
  std::unordered_map<NuclearReactionType,unsigned> reaction_ordering;
  NeutronNuclearReactionACEFactory::createReactionOrderingMap( mtr_block,
							reaction_ordering );

  // Create a map of the reaction types and the corresponding Q-value
  std::unordered_map<NuclearReactionType,double> reaction_q_value;
  NeutronNuclearReactionACEFactory::createReactionQValueMap( lqr_block,
						      reaction_ordering,
						      reaction_q_value );

  // Create a map of the reaction types and the corresponding multiplicity
  std::unordered_map<NuclearReactionType,unsigned>
    reaction_multiplicity;
  std::unordered_map<NuclearReactionType,Utility::ArrayView<const double> >
    reaction_energy_dependent_multiplicity;
  NeutronNuclearReactionACEFactory::createReactionMultiplicityMap(
				      table_name,
				      tyr_block,
				      dlw_block,
				      reaction_ordering,
				      reaction_multiplicity,
				      reaction_energy_dependent_multiplicity );

  // Create a map of the reaction types and the corresponding threshold index
  std::unordered_map<NuclearReactionType,unsigned> reaction_threshold_index;
  NeutronNuclearReactionACEFactory::createReactionThresholdMap(
						    lsig_block,
						    sig_block,
						    reaction_ordering,
						    reaction_threshold_index );

  // Create a map of the reaction types and the corresponding cross section
  std::unordered_map<NuclearReactionType,std::shared_ptr<std::vector<double> > >
    reaction_cross_section;
  NeutronNuclearReactionACEFactory::createReactionCrossSectionMap(
						      lsig_block,
						      sig_block,
						      elastic_cross_section,
						      reaction_ordering,
						      reaction_cross_section );

  // Create the fission neutron multiplicity distribution
  std::shared_ptr<const FissionNeutronMultiplicityDistribution>
    fission_neutron_multiplicity_dist;

  if( nu_block.size() > 0 )
  {
    FissionNeutronMultiplicityDistributionACEFactory
      fission_multiplicity_factory( table_name,
				    nu_block,
				    dnu_block );

    fission_multiplicity_factory.createDistribution(
				           fission_neutron_multiplicity_dist );
  }

  // Create the delayed neutron emission distributions
  std::shared_ptr<const NuclearScatteringDistribution<NeutronState,NeutronState> >
    delayed_neutron_emission_dist;

  if( dnedl_block.size() > 0 )
  {
    DelayedNeutronEmissionDistributionACEFactory
      delayed_neutron_emission_factory( table_name,
					atomic_weight_ratio,
					bdd_block,
					dnedl_block,
					dned_block );

    delayed_neutron_emission_factory.createEmissionDistribution(
					       delayed_neutron_emission_dist );
  }

  // Create the nuclear reactions
  this->initializeScatteringReactions( temperature,
                                       energy_grid,
                                       grid_searcher,
                                       properties,
                                       reaction_q_value,
                                       reaction_multiplicity,
                                       reaction_energy_dependent_multiplicity,
                                       reaction_threshold_index,
                                       reaction_cross_section,
                                       scattering_dist_factory );

  this->initializeAbsorptionReactions( temperature,
                                       energy_grid,
                                       grid_searcher,
                                       reaction_q_value,
                                       reaction_multiplicity,
                                       reaction_energy_dependent_multiplicity,
                                       reaction_threshold_index,
                                       reaction_cross_section );

  this->initializeFissionReactions( temperature,
                                    energy_grid,
                                    grid_searcher,
                                    properties,
                                    reaction_q_value,
                                    reaction_multiplicity,
                                    reaction_threshold_index,
                                    reaction_cross_section,
                                    scattering_dist_factory,
                                    fission_neutron_multiplicity_dist,
                                    delayed_neutron_emission_dist );
}

// Create the scattering reactions
void NeutronNuclearReactionACEFactory::createScatteringReactions(
      std::unordered_map<NuclearReactionType,std::shared_ptr<NeutronNuclearReaction> >&
      scattering_reactions ) const
{
  scattering_reactions.insert( d_scattering_reactions.begin(),
			       d_scattering_reactions.end() );
}

// Create the absorption reactions
void NeutronNuclearReactionACEFactory::createAbsorptionReactions(
      std::unordered_map<NuclearReactionType,std::shared_ptr<NeutronNuclearReaction> >&
      absorption_reactions ) const
{
  absorption_reactions.insert( d_absorption_reactions.begin(),
			       d_absorption_reactions.end() );
}

// Create the fission reactions
void NeutronNuclearReactionACEFactory::createFissionReactions(
      std::unordered_map<NuclearReactionType,std::shared_ptr<NeutronNuclearReaction> >&
      fission_reactions ) const
{
  fission_reactions.insert( d_fission_reactions.begin(),
			    d_fission_reactions.end() );
}

// Create the reaction type ordering map
void NeutronNuclearReactionACEFactory::createReactionOrderingMap(
        const Utility::ArrayView<const double>& mtr_block,
        std::unordered_map<NuclearReactionType,unsigned>& reaction_ordering )

{
  NuclearReactionType reaction;

  for( unsigned i = 0; i < mtr_block.size(); ++i )
  {
    reaction = MonteCarlo::convertMTNumberToNuclearReactionType(
				       static_cast<unsigned>( mtr_block[i] ) );

    reaction_ordering[reaction] = i;
  }

  // Elastic scattering must be handled separately: it never appears in block
  reaction_ordering[N__N_ELASTIC_REACTION] =
    std::numeric_limits<unsigned>::max();
}

// Create the reaction type Q-value map
void NeutronNuclearReactionACEFactory::createReactionQValueMap(
   const Utility::ArrayView<const double>& lqr_block,
   const std::unordered_map<NuclearReactionType,unsigned>& reaction_ordering,
   std::unordered_map<NuclearReactionType,double>& reaction_q_value )
{
  std::unordered_map<NuclearReactionType,unsigned>::const_iterator
    reaction, end_reaction;
  reaction = reaction_ordering.begin();
  end_reaction = reaction_ordering.end();

  while( reaction != end_reaction )
  {
    if( reaction->first != N__N_ELASTIC_REACTION )
    {
      reaction_q_value[reaction->first] =
	lqr_block[reaction->second];
    }
    // Elastic scattering must be handled separately: it never appears in block
    else
      reaction_q_value[reaction->first] = 0.0;

    ++reaction;
  }
}

// Create the reaction type multiplicity and scattering ref. frame map
/*! \details The reaction_multiplicity map stores the absolute values of the
 * values in the TYR block. The reaction_energy_dependent_multiplicity stores
 * the raw ACE table array that provides the energy dependent multiplicity
 */
void NeutronNuclearReactionACEFactory::createReactionMultiplicityMap(
   const std::string& table_name,
   const Utility::ArrayView<const double>& tyr_block,
   const Utility::ArrayView<const double>& dlw_block,
   const std::unordered_map<NuclearReactionType,unsigned>& reaction_ordering,
   std::unordered_map<NuclearReactionType,unsigned>& reaction_multiplicity,
   std::unordered_map<NuclearReactionType,Utility::ArrayView<const double> >&
   reaction_energy_dependent_multiplicity )
{
  std::unordered_map<NuclearReactionType,unsigned>::const_iterator
    reaction, end_reaction;
  reaction = reaction_ordering.begin();
  end_reaction = reaction_ordering.end();

  double multiplicity;

  while( reaction != end_reaction )
  {
    if( reaction->first != N__N_ELASTIC_REACTION )
    {
      multiplicity = std::fabs( tyr_block[reaction->second] );

      // Assign multiplicity to reaction type
      reaction_multiplicity[reaction->first] =
	static_cast<unsigned>( multiplicity );

      // Assign energy dependent multiplicity to reaction type
      if( multiplicity > 100 )
      {
	unsigned start_index = static_cast<unsigned>( multiplicity ) - 101;

	TEST_FOR_EXCEPTION( dlw_block[start_index] != 0,
			    std::runtime_error,
			    "multiple interpolation regions found for "
			    "energy dependent multiplicities of reaction "
			    << reaction->first << " in table "
			    << table_name << ". This is not currently "
			    "supported!\n" );

	// Add interpolation regions to size
	unsigned size = 2*(unsigned)dlw_block[start_index] + 1;

	// Add energy grid and multiplicities to size
	size += 2*(unsigned)dlw_block[start_index + size] + 1;

	reaction_energy_dependent_multiplicity[reaction->first] =
	  dlw_block( start_index, size );
      }
    }
    // Elastic scattering must be handled separately: it never appears in block
    else
      reaction_multiplicity[reaction->first] = 1u;

    ++reaction;
  }
}

// Create the reaction type threshold and cross section map
// NOTE: All LSIG block indices correspond to FORTRAN arrays. Subtract 1 from
// the value to get the index in a C/C++ array.
void NeutronNuclearReactionACEFactory::createReactionThresholdMap(
   const Utility::ArrayView<const double>& lsig_block,
   const Utility::ArrayView<const double>& sig_block,
   const std::unordered_map<NuclearReactionType,unsigned>& reaction_ordering,
   std::unordered_map<NuclearReactionType,unsigned>&
   reaction_threshold_index )
{
  std::unordered_map<NuclearReactionType,unsigned>::const_iterator
    reaction, end_reaction;
  reaction = reaction_ordering.begin();
  end_reaction = reaction_ordering.end();

  unsigned cs_index;

  while( reaction != end_reaction )
  {
    if( reaction->first != N__N_ELASTIC_REACTION )
    {
      cs_index = static_cast<unsigned>( lsig_block[reaction->second] ) - 1u;

      reaction_threshold_index[reaction->first] =
	static_cast<unsigned>( sig_block[cs_index] );

      // Convert to C-style index
      if( reaction_threshold_index[reaction->first] > 0u )
        --reaction_threshold_index[reaction->first];
    }
    // Elastic scattering must be handled separately: it never appears in block
    else
      reaction_threshold_index[reaction->first] = 0;

    ++reaction;
  }
}

// Create the reaction type threshold and cross section map
// NOTE: All LSIG block indices correspond to FORTRAN arrays. Subtract 1 from
// the value to get the index in a C/C++ array.
void NeutronNuclearReactionACEFactory::createReactionCrossSectionMap(
   const Utility::ArrayView<const double>& lsig_block,
   const Utility::ArrayView<const double>& sig_block,
   const Utility::ArrayView<const double>& elastic_cross_section,
   const std::unordered_map<NuclearReactionType,unsigned>& reaction_ordering,
   std::unordered_map<NuclearReactionType,std::shared_ptr<std::vector<double> > >&
   reaction_cross_section )
{
  std::unordered_map<NuclearReactionType,unsigned>::const_iterator
    reaction, end_reaction;
  reaction = reaction_ordering.begin();
  end_reaction = reaction_ordering.end();

  unsigned cs_index;
  unsigned cs_array_size;

  while( reaction != end_reaction )
  {
    if( reaction->first != N__N_ELASTIC_REACTION )
    {
      cs_index = static_cast<unsigned>( lsig_block[reaction->second] ) - 1u;

      cs_array_size = static_cast<unsigned>( sig_block[cs_index+1u] );

      std::shared_ptr<std::vector<double> >& cross_section =
	reaction_cross_section[reaction->first];

      cross_section.reset(
          new std::vector<double>( sig_block( cs_index+2u, cs_array_size ) ) );
    }
    // Elastic scattering must be handled separately: it never appears in block
    else
    {
      std::shared_ptr<std::vector<double> >& cross_section =
	reaction_cross_section[reaction->first];

      cross_section.reset( new std::vector<double>( elastic_cross_section ) );
    }

    ++reaction;
  }
}

// Get the reaction from a reaction type
void NeutronNuclearReactionACEFactory::getReactionFromReactionType(
           NuclearReactionType reaction_type,
           std::shared_ptr<NeutronNuclearReaction>& base_reaction )
{
  // Check for the reaction amongst the absorptions, scatters, and fissions
  if ( d_absorption_reactions.find(reaction_type) != d_absorption_reactions.end() )
  {
    base_reaction = d_absorption_reactions[reaction_type];
  }
  else if ( d_scattering_reactions.find(reaction_type) != d_scattering_reactions.end() )
  {
    base_reaction = d_scattering_reactions[reaction_type];
  }
  else if ( d_fission_reactions.find(reaction_type) != d_fission_reactions.end() )
  {
    base_reaction = d_fission_reactions[reaction_type];
  }
  else
  {
    THROW_EXCEPTION(std::runtime_error, "photon production requested "
                    "MT number " << (int)reaction_type << " which was not "
                    "found among the neutron absorption, scattering, or "
                    "fission reactions.");
  }
}

// Initialize the scattering reactions
void NeutronNuclearReactionACEFactory::initializeScatteringReactions(
    const double temperature,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
    grid_searcher,
    const SimulationProperties& properties,
    const std::unordered_map<NuclearReactionType,double>& reaction_q_value,
    const std::unordered_map<NuclearReactionType,unsigned>&
    reaction_multiplicity,
    const std::unordered_map<NuclearReactionType,Utility::ArrayView<const double> >&
    reaction_energy_dependent_multiplicity,
    const std::unordered_map<NuclearReactionType,unsigned>&
    reaction_threshold_index,
    const std::unordered_map<NuclearReactionType,std::shared_ptr<std::vector<double> > >&
    reaction_cross_section,
    const NeutronNuclearScatteringDistributionACEFactory& scattering_dist_factory )

{
  // Make sure the maps have the correct number of elements
  testPrecondition( reaction_q_value.size() == reaction_multiplicity.size() );
  testPrecondition(reaction_q_value.size() == reaction_threshold_index.size());
  testPrecondition( reaction_q_value.size() == reaction_cross_section.size() );

  std::unordered_map<NuclearReactionType,unsigned>::const_iterator
    reaction_type_multiplicity, end_reaction_type_multiplicity;

  reaction_type_multiplicity = reaction_multiplicity.begin();
  end_reaction_type_multiplicity = reaction_multiplicity.end();

  NuclearReactionType reaction_type;

  std::shared_ptr<const NuclearScatteringDistribution<NeutronState,NeutronState> >
    scattering_distribution;

  while( reaction_type_multiplicity != end_reaction_type_multiplicity )
  {
    // Create a neutron scattering reaction
    if( reaction_type_multiplicity->second > 0u &&
	reaction_type_multiplicity->second != 19u &&
	reaction_type_multiplicity->second <= 100u )
    {
      reaction_type = reaction_type_multiplicity->first;

      std::shared_ptr<NeutronNuclearReaction>& reaction =
	d_scattering_reactions[reaction_type];

      scattering_dist_factory.createScatteringDistribution(
						     reaction_type,
                                                     properties,
						     scattering_distribution );

      reaction.reset( new NeutronScatteringReaction(
                          energy_grid,
                          reaction_cross_section.find(reaction_type)->second,
                          reaction_threshold_index.find(reaction_type)->second,
                          grid_searcher,
                          reaction_type,
                          reaction_q_value.find(reaction_type)->second,
                          temperature,
                          reaction_type_multiplicity->second,
                          scattering_distribution ) );
    }
    // Create an energy dependent neutron multiplicity reaction
    else if( reaction_type_multiplicity->second >= 100u )
    {
      reaction_type = reaction_type_multiplicity->first;

      std::shared_ptr<NeutronNuclearReaction>& reaction =
	d_scattering_reactions[reaction_type];

      scattering_dist_factory.createScatteringDistribution(
						   reaction_type,
                                                   properties,
						   scattering_distribution );

      const Utility::ArrayView<const double>& raw_multiplicity_array =
	reaction_energy_dependent_multiplicity.find( reaction_type )->second;

      // Assume there is only one interpolation region
      unsigned number_of_energies = (unsigned)raw_multiplicity_array[1];

      reaction.reset( new EnergyDependentNeutronMultiplicityReaction(
        energy_grid,
        reaction_cross_section.find(reaction_type)->second,
        reaction_threshold_index.find(reaction_type)->second,
        grid_searcher,
        reaction_type,
        reaction_q_value.find(reaction_type)->second,
        temperature,
        scattering_distribution,
        raw_multiplicity_array( 1, number_of_energies ),
        raw_multiplicity_array( 1+number_of_energies, number_of_energies ) ) );
    }

    ++reaction_type_multiplicity;
  }
}

// Initialize the absorption reactions
void NeutronNuclearReactionACEFactory::initializeAbsorptionReactions(
    const double temperature,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
    grid_searcher,
    const std::unordered_map<NuclearReactionType,double>& reaction_q_value,
    const std::unordered_map<NuclearReactionType,unsigned>&
    reaction_multiplicity,
    const std::unordered_map<NuclearReactionType,Utility::ArrayView<const double> >&
    reaction_energy_dependent_multiplicity,
    const std::unordered_map<NuclearReactionType,unsigned>&
    reaction_threshold_index,
    const std::unordered_map<NuclearReactionType,std::shared_ptr<std::vector<double> > >&
    reaction_cross_section )
{
  // Make sure the maps have the correct number of elements
  testPrecondition( reaction_q_value.size() == reaction_multiplicity.size() );
  testPrecondition(reaction_q_value.size() == reaction_threshold_index.size());
  testPrecondition( reaction_q_value.size() == reaction_cross_section.size() );

  std::unordered_map<NuclearReactionType,unsigned>::const_iterator
    reaction_type_multiplicity, end_reaction_type_multiplicity;

  reaction_type_multiplicity = reaction_multiplicity.begin();
  end_reaction_type_multiplicity = reaction_multiplicity.end();

  NuclearReactionType reaction_type;

  while( reaction_type_multiplicity != end_reaction_type_multiplicity )
  {
    if( reaction_type_multiplicity->second == 0u )
    {
      reaction_type = reaction_type_multiplicity->first;

      std::shared_ptr<NeutronNuclearReaction>& reaction =
	d_absorption_reactions[reaction_type];

      reaction.reset( new NeutronAbsorptionReaction(
                        energy_grid,
                        reaction_cross_section.find(reaction_type)->second,
                        reaction_threshold_index.find(reaction_type)->second,
                        grid_searcher,
                        reaction_type,
                        reaction_q_value.find(reaction_type)->second,
                        temperature ) );
    }

    ++reaction_type_multiplicity;
  }
}

// Initialize the fission reactions
void NeutronNuclearReactionACEFactory::initializeFissionReactions(
    const double temperature,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
    grid_searcher,
    const SimulationProperties& properties,
    const std::unordered_map<NuclearReactionType,double>& reaction_q_value,
    const std::unordered_map<NuclearReactionType,unsigned>&
    reaction_multiplicity,
    const std::unordered_map<NuclearReactionType,unsigned>&
    reaction_threshold_index,
    const std::unordered_map<NuclearReactionType,std::shared_ptr<std::vector<double> > >&
    reaction_cross_section,
    const NeutronNuclearScatteringDistributionACEFactory& scattering_dist_factory,
    const std::shared_ptr<const FissionNeutronMultiplicityDistribution>&
    fission_neutron_multiplicity_distribution,
    const std::shared_ptr<const NuclearScatteringDistribution<NeutronState,NeutronState> >&
    delayed_neutron_emission_distribution )
{
  // Make sure the maps have the correct number of elements
  testPrecondition( reaction_q_value.size() == reaction_multiplicity.size() );
  testPrecondition(reaction_q_value.size() == reaction_threshold_index.size());
  testPrecondition( reaction_q_value.size() == reaction_cross_section.size() );

  std::unordered_map<NuclearReactionType,unsigned>::const_iterator
    reaction_type_multiplicity, end_reaction_type_multiplicity;

  reaction_type_multiplicity = reaction_multiplicity.begin();
  end_reaction_type_multiplicity = reaction_multiplicity.end();

  NuclearReactionType reaction_type;

  std::shared_ptr<const NuclearScatteringDistribution<NeutronState,NeutronState> >
    prompt_neutron_emission_distribution;

  while( reaction_type_multiplicity != end_reaction_type_multiplicity )
  {
    if( reaction_type_multiplicity->second == 19 )
    {
      // Make sure the fission neutron multiplicity distribution has been
      // created
      testPrecondition( fission_neutron_multiplicity_distribution.get() );

      reaction_type = reaction_type_multiplicity->first;

      scattering_dist_factory.createScatteringDistribution(
					reaction_type,
                                        properties,
					prompt_neutron_emission_distribution );

      std::shared_ptr<NeutronNuclearReaction>& reaction =
	d_fission_reactions[reaction_type];

      // Create a basic neutron fission reaction (no delayed info)
      if( !delayed_neutron_emission_distribution.get() )
      {
	reaction.reset( new NeutronFissionReaction(
                          energy_grid,
                          reaction_cross_section.find(reaction_type)->second,
                          reaction_threshold_index.find(reaction_type)->second,
                          grid_searcher,
                          reaction_type,
                          reaction_q_value.find(reaction_type)->second,
                          temperature,
                          fission_neutron_multiplicity_distribution,
			  prompt_neutron_emission_distribution ) );
      }
      // Create a detailed neutron fission reaction (with delayed info)
      else
      {
	reaction.reset( new DetailedNeutronFissionReaction(
                          energy_grid,
                          reaction_cross_section.find(reaction_type)->second,
                          reaction_threshold_index.find(reaction_type)->second,
                          grid_searcher,
                          reaction_type,
                          reaction_q_value.find(reaction_type)->second,
                          temperature,
                          fission_neutron_multiplicity_distribution,
                          prompt_neutron_emission_distribution,
                          delayed_neutron_emission_distribution ) );
      }
    }

    ++reaction_type_multiplicity;
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_NeutronNuclearReactionACEFactory.cpp
//---------------------------------------------------------------------------//
