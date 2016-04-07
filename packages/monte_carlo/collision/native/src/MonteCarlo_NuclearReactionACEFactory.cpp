//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NuclearReactionACEFactory.cpp
//! \author Alex Robinson
//! \brief  Nuclear reaction factory class declaration
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "MonteCarlo_NuclearReactionACEFactory.hpp"
#include "MonteCarlo_PhotonProductionNuclearScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_NeutronScatteringReaction.hpp"
#include "MonteCarlo_NeutronAbsorptionReaction.hpp"
#include "MonteCarlo_NeutronFissionReaction.hpp"
#include "MonteCarlo_DetailedNeutronFissionReaction.hpp"
#include "MonteCarlo_EnergyDependentNeutronMultiplicityReaction.hpp"
#include "MonteCarlo_FissionNeutronMultiplicityDistributionACEFactory.hpp"
#include "MonteCarlo_DelayedNeutronEmissionDistributionACEFactory.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
/*! \details All blocks from the ACE file will be stored. 
 * \param[in] raw_nuclide_data The necessary data blocks will be extracted 
 * using the data extractor.
 */
NuclearReactionACEFactory::NuclearReactionACEFactory( 
		 const std::string& table_name,
		 const double atomic_weight_ratio,
		 const double temperature,
		 const Teuchos::ArrayRCP<const double>& energy_grid,
		 const Data::XSSNeutronDataExtractor& raw_nuclide_data )
{ 
  // Create the scattering distribution factory
  NeutronNuclearScatteringDistributionACEFactory 
    scattering_dist_factory( table_name,
			     atomic_weight_ratio,
			     raw_nuclide_data );

  // Extract the required blocks
  Teuchos::ArrayView<const double> elastic_cross_section = 
    raw_nuclide_data.extractElasticCrossSection();
  Teuchos::ArrayView<const double> mtr_block = 
    raw_nuclide_data.extractMTRBlock();
  Teuchos::ArrayView<const double> lqr_block = 
    raw_nuclide_data.extractLQRBlock();
  Teuchos::ArrayView<const double> tyr_block = 
    raw_nuclide_data.extractTYRBlock();
  Teuchos::ArrayView<const double> lsig_block = 
    raw_nuclide_data.extractLSIGBlock();
  Teuchos::ArrayView<const double> sig_block = 
    raw_nuclide_data.extractSIGBlock();
  Teuchos::ArrayView<const double> land_block = 
    raw_nuclide_data.extractLANDBlock();
  Teuchos::ArrayView<const double> and_block = 
    raw_nuclide_data.extractANDBlock();
  Teuchos::ArrayView<const double> ldlw_block = 
    raw_nuclide_data.extractLDLWBlock();
  Teuchos::ArrayView<const double> dlw_block = 
    raw_nuclide_data.extractDLWBlock();
  Teuchos::ArrayView<const double> nu_block = 
    raw_nuclide_data.extractNUBlock();
  Teuchos::ArrayView<const double> dnu_block = 
    raw_nuclide_data.extractDNUBlock();
  Teuchos::ArrayView<const double> bdd_block = 
    raw_nuclide_data.extractBDDBlock();
  Teuchos::ArrayView<const double> dnedl_block = 
    raw_nuclide_data.extractDNEDLBlock();
  Teuchos::ArrayView<const double> dned_block = 
    raw_nuclide_data.extractDNEDBlock();

  // Create a map of the reaction types and their table ordering
  boost::unordered_map<NuclearReactionType,unsigned> reaction_ordering;
  NuclearReactionACEFactory::createReactionOrderingMap( mtr_block,
							reaction_ordering );

  // Create a map of the reaction types and the corresponding Q-value
  boost::unordered_map<NuclearReactionType,double> reaction_q_value;
  NuclearReactionACEFactory::createReactionQValueMap( lqr_block,
						      reaction_ordering,
						      reaction_q_value );
  
  // Create a map of the reaction types and the corresponding multiplicity
  boost::unordered_map<NuclearReactionType,unsigned> 
    reaction_multiplicity;
  boost::unordered_map<NuclearReactionType,Teuchos::ArrayView<const double> >
    reaction_energy_dependent_multiplicity;
  NuclearReactionACEFactory::createReactionMultiplicityMap(
				      table_name,
				      tyr_block,
				      dlw_block,
				      reaction_ordering,
				      reaction_multiplicity,
				      reaction_energy_dependent_multiplicity );
  
  // Create a map of the reaction types and the corresponding threshold index
  boost::unordered_map<NuclearReactionType,unsigned> reaction_threshold_index;
  NuclearReactionACEFactory::createReactionThresholdMap(
						    lsig_block,
						    sig_block,
						    reaction_ordering,
						    reaction_threshold_index );
  
  // Create a map of the reaction types and the corresponding cross section
  boost::unordered_map<NuclearReactionType,Teuchos::ArrayRCP<double> >
    reaction_cross_section;
  NuclearReactionACEFactory::createReactionCrossSectionMap(
						      lsig_block,
						      sig_block,
						      elastic_cross_section,
						      reaction_ordering,
						      reaction_cross_section );

  // Create the fission neutron multiplicity distribution
  Teuchos::RCP<FissionNeutronMultiplicityDistribution>
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
  Teuchos::RCP<NuclearScatteringDistribution<NeutronState,NeutronState> > 
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
  initializeScatteringReactions( temperature,
				 energy_grid,
				 reaction_q_value,
				 reaction_multiplicity,
				 reaction_energy_dependent_multiplicity,
				 reaction_threshold_index,
				 reaction_cross_section,
				 scattering_dist_factory );
  initializeAbsorptionReactions( temperature,
				 energy_grid,
				 reaction_q_value,
				 reaction_multiplicity,
				 reaction_energy_dependent_multiplicity,
				 reaction_threshold_index,
				 reaction_cross_section );
  initializeFissionReactions( temperature,
			      energy_grid,
			      reaction_q_value,
			      reaction_multiplicity,
			      reaction_threshold_index,
			      reaction_cross_section,
			      scattering_dist_factory,
			      fission_neutron_multiplicity_dist,
			      delayed_neutron_emission_dist );
}

// Create the scattering reactions 
void NuclearReactionACEFactory::createScatteringReactions( 
      boost::unordered_map<NuclearReactionType,Teuchos::RCP<NuclearReaction> >&
      scattering_reactions ) const
{
  scattering_reactions.insert( d_scattering_reactions.begin(),
			       d_scattering_reactions.end() );
}

// Create the absorption reactions 
void NuclearReactionACEFactory::createAbsorptionReactions(
      boost::unordered_map<NuclearReactionType,Teuchos::RCP<NuclearReaction> >&
      absorption_reactions ) const
{
  absorption_reactions.insert( d_absorption_reactions.begin(),
			       d_absorption_reactions.end() );
}	     

// Create the fission reactions
void NuclearReactionACEFactory::createFissionReactions(
      boost::unordered_map<NuclearReactionType,Teuchos::RCP<NuclearReaction> >&
      fission_reactions ) const
{
  fission_reactions.insert( d_fission_reactions.begin(),
			    d_fission_reactions.end() );
}

// Create the reaction type ordering map
void NuclearReactionACEFactory::createReactionOrderingMap( 
        const Teuchos::ArrayView<const double>& mtr_block,
        boost::unordered_map<NuclearReactionType,unsigned>& reaction_ordering )

{  
  NuclearReactionType reaction;
  
  for( unsigned i = 0; i < mtr_block.size(); ++i )
  {
    reaction = convertUnsignedToNuclearReactionType( 
				       static_cast<unsigned>( mtr_block[i] ) );
    
    reaction_ordering[reaction] = i;
  }

  // Elastic scattering must be handled separately: it never appears in block
  reaction_ordering[N__N_ELASTIC_REACTION] = 
    std::numeric_limits<unsigned>::max();
}

// Create the reaction type Q-value map
void NuclearReactionACEFactory::createReactionQValueMap(
   const Teuchos::ArrayView<const double>& lqr_block,
   const boost::unordered_map<NuclearReactionType,unsigned>& reaction_ordering,
   boost::unordered_map<NuclearReactionType,double>& reaction_q_value )
{
  boost::unordered_map<NuclearReactionType,unsigned>::const_iterator
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
void NuclearReactionACEFactory::createReactionMultiplicityMap(
   const std::string& table_name,
   const Teuchos::ArrayView<const double>& tyr_block,
   const Teuchos::ArrayView<const double>& dlw_block,
   const boost::unordered_map<NuclearReactionType,unsigned>& reaction_ordering,
   boost::unordered_map<NuclearReactionType,unsigned>& reaction_multiplicity,
   boost::unordered_map<NuclearReactionType,Teuchos::ArrayView<const double> >&
   reaction_energy_dependent_multiplicity )
{
  boost::unordered_map<NuclearReactionType,unsigned>::const_iterator
    reaction, end_reaction;
  reaction = reaction_ordering.begin();
  end_reaction = reaction_ordering.end();

  double multiplicity;
  
  while( reaction != end_reaction )
  {
    if( reaction->first != N__N_ELASTIC_REACTION )
    {
      multiplicity = 
	Teuchos::ScalarTraits<double>::magnitude(tyr_block[reaction->second]);
      
      // Assign multiplicity to reaction type
      reaction_multiplicity[reaction->first] = 
	static_cast<unsigned>( multiplicity );
            
      // Assign energy dependent multiplicity to reaction type
      if( multiplicity > 100 )
      {
	unsigned start_index = static_cast<unsigned>( multiplicity ) - 101;
	
	TEST_FOR_EXCEPTION( dlw_block[start_index] != 0,
			    std::runtime_error,
			    "Error: multiple interpolation regions found for "
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
void NuclearReactionACEFactory::createReactionThresholdMap(
   const Teuchos::ArrayView<const double>& lsig_block,
   const Teuchos::ArrayView<const double>& sig_block,
   const boost::unordered_map<NuclearReactionType,unsigned>& reaction_ordering,
   boost::unordered_map<NuclearReactionType,unsigned>& 
   reaction_threshold_index )
{
  boost::unordered_map<NuclearReactionType,unsigned>::const_iterator
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
	static_cast<unsigned>( sig_block[cs_index] ) - 1u;
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
void NuclearReactionACEFactory::createReactionCrossSectionMap(
   const Teuchos::ArrayView<const double>& lsig_block,
   const Teuchos::ArrayView<const double>& sig_block,
   const Teuchos::ArrayView<const double>& elastic_cross_section,
   const boost::unordered_map<NuclearReactionType,unsigned>& reaction_ordering,
   boost::unordered_map<NuclearReactionType,Teuchos::ArrayRCP<double> >& 
   reaction_cross_section )
{
  boost::unordered_map<NuclearReactionType,unsigned>::const_iterator
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

      Teuchos::ArrayRCP<double>& cross_section = 
	reaction_cross_section[reaction->first];

      cross_section.deepCopy( sig_block( cs_index+2u, cs_array_size ) );
    }
    // Elastic scattering must be handled separately: it never appears in block
    else
    {
      Teuchos::ArrayRCP<double>& cross_section = 
	reaction_cross_section[reaction->first];
      
      cross_section.deepCopy( elastic_cross_section );
    }

    ++reaction;
  }
}

// Get the reaction from a reaction type 
void NuclearReactionACEFactory::getReactionFromReactionType( 
                               NuclearReactionType reaction_type, 
                               Teuchos::RCP<NuclearReaction>& base_reaction )
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
    THROW_EXCEPTION(std::runtime_error, "Error: photon production requested "
                    "MT number " << (int)reaction_type << " which was not "
                    "found amongst the neutron absorption, scattering, or "
                    "fission reactions.");
  }
}

// Initialize the scattering reactions
void NuclearReactionACEFactory::initializeScatteringReactions(
    const double temperature,
    const Teuchos::ArrayRCP<const double> energy_grid,
    const boost::unordered_map<NuclearReactionType,double>& reaction_q_value,
    const boost::unordered_map<NuclearReactionType,unsigned>&
    reaction_multiplicity,
    const boost::unordered_map<NuclearReactionType,Teuchos::ArrayView<const double> >&
    reaction_energy_dependent_multiplicity,
    const boost::unordered_map<NuclearReactionType,unsigned>&
    reaction_threshold_index,
    const boost::unordered_map<NuclearReactionType,Teuchos::ArrayRCP<double> >&
    reaction_cross_section,
    const NeutronNuclearScatteringDistributionACEFactory& scattering_dist_factory )
				
{
  // Make sure the maps have the correct number of elements
  testPrecondition( reaction_q_value.size() == reaction_multiplicity.size() );
  testPrecondition(reaction_q_value.size() == reaction_threshold_index.size());
  testPrecondition( reaction_q_value.size() == reaction_cross_section.size() );
  
  boost::unordered_map<NuclearReactionType,unsigned>::const_iterator
    reaction_type_multiplicity, end_reaction_type_multiplicity;

  reaction_type_multiplicity = reaction_multiplicity.begin();
  end_reaction_type_multiplicity = reaction_multiplicity.end();

  NuclearReactionType reaction_type;

  Teuchos::RCP<NuclearScatteringDistribution<NeutronState,NeutronState> > 
    scattering_distribution;
  
  while( reaction_type_multiplicity != end_reaction_type_multiplicity )
  {
    // Create a neutron scattering reaction
    if( reaction_type_multiplicity->second > 0u &&
	reaction_type_multiplicity->second != 19u &&
	reaction_type_multiplicity->second <= 100u )
    {
      reaction_type = reaction_type_multiplicity->first;
      
      Teuchos::RCP<NuclearReaction>& reaction = 
	d_scattering_reactions[reaction_type];
      
      scattering_dist_factory.createScatteringDistribution(
						     reaction_type,
						     scattering_distribution );
      
      reaction.reset( new NeutronScatteringReaction(
			  reaction_type,
			  temperature,
			  reaction_q_value.find(reaction_type)->second,
			  reaction_type_multiplicity->second,
			  reaction_threshold_index.find(reaction_type)->second,
			  energy_grid,
			  reaction_cross_section.find(reaction_type)->second,
			  scattering_distribution ) );	    
    }
    // Create an energy dependent neutron multiplicity reaction
    else if( reaction_type_multiplicity->second >= 100u )
    {
      reaction_type = reaction_type_multiplicity->first;

      Teuchos::RCP<NuclearReaction>& reaction = 
	d_scattering_reactions[reaction_type];

      scattering_dist_factory.createScatteringDistribution(
						   reaction_type,
						   scattering_distribution );
      
      const Teuchos::ArrayView<const double>& raw_multiplicity_array = 
	reaction_energy_dependent_multiplicity.find( reaction_type )->second;
      
      // Assume there is only one interpolation region
      unsigned number_of_energies = (unsigned)raw_multiplicity_array[1];
      
      reaction.reset( new EnergyDependentNeutronMultiplicityReaction(
	    reaction_type,
	    temperature,
	    reaction_q_value.find(reaction_type)->second,
	    raw_multiplicity_array( 1, number_of_energies ),
	    raw_multiplicity_array( 1+number_of_energies, number_of_energies ),
	    reaction_threshold_index.find(reaction_type)->second,
	    energy_grid,
	    reaction_cross_section.find(reaction_type)->second,
	    scattering_distribution ) );
    }

    ++reaction_type_multiplicity;
  }
}

// Initialize the absorption reactions
void NuclearReactionACEFactory::initializeAbsorptionReactions(
    const double temperature,
    const Teuchos::ArrayRCP<const double> energy_grid,
    const boost::unordered_map<NuclearReactionType,double>& reaction_q_value,
    const boost::unordered_map<NuclearReactionType,unsigned>&
    reaction_multiplicity,
    const boost::unordered_map<NuclearReactionType,Teuchos::ArrayView<const double> >&
    reaction_energy_dependent_multiplicity,
    const boost::unordered_map<NuclearReactionType,unsigned>&
    reaction_threshold_index,
    const boost::unordered_map<NuclearReactionType,Teuchos::ArrayRCP<double> >&
    reaction_cross_section )
{
  // Make sure the maps have the correct number of elements
  testPrecondition( reaction_q_value.size() == reaction_multiplicity.size() );
  testPrecondition(reaction_q_value.size() == reaction_threshold_index.size());
  testPrecondition( reaction_q_value.size() == reaction_cross_section.size() );
  
  boost::unordered_map<NuclearReactionType,unsigned>::const_iterator
    reaction_type_multiplicity, end_reaction_type_multiplicity;

  reaction_type_multiplicity = reaction_multiplicity.begin();
  end_reaction_type_multiplicity = reaction_multiplicity.end();

  NuclearReactionType reaction_type;
  
  while( reaction_type_multiplicity != end_reaction_type_multiplicity )
  {
    if( reaction_type_multiplicity->second == 0u )
    {
      reaction_type = reaction_type_multiplicity->first;
      
      Teuchos::RCP<NuclearReaction>& reaction = 
	d_absorption_reactions[reaction_type];

      reaction.reset( new NeutronAbsorptionReaction(
			reaction_type,
			temperature,
			reaction_q_value.find(reaction_type)->second,
			reaction_threshold_index.find(reaction_type)->second,
			energy_grid,
			reaction_cross_section.find(reaction_type)->second ) );
    }

    ++reaction_type_multiplicity;
  }
}

// Initialize the fission reactions
void NuclearReactionACEFactory::initializeFissionReactions(
    const double temperature,
    const Teuchos::ArrayRCP<const double> energy_grid,
    const boost::unordered_map<NuclearReactionType,double>& reaction_q_value,
    const boost::unordered_map<NuclearReactionType,unsigned>&
    reaction_multiplicity,
    const boost::unordered_map<NuclearReactionType,unsigned>&
    reaction_threshold_index,
    const boost::unordered_map<NuclearReactionType,Teuchos::ArrayRCP<double> >&
    reaction_cross_section,
    const NeutronNuclearScatteringDistributionACEFactory& scattering_dist_factory,
    const Teuchos::RCP<FissionNeutronMultiplicityDistribution>&
    fission_neutron_multiplicity_distribution,
    const Teuchos::RCP<NuclearScatteringDistribution<NeutronState,NeutronState> >& 
    delayed_neutron_emission_distribution )
{
  // Make sure the maps have the correct number of elements
  testPrecondition( reaction_q_value.size() == reaction_multiplicity.size() );
  testPrecondition(reaction_q_value.size() == reaction_threshold_index.size());
  testPrecondition( reaction_q_value.size() == reaction_cross_section.size() );
  
  boost::unordered_map<NuclearReactionType,unsigned>::const_iterator
    reaction_type_multiplicity, end_reaction_type_multiplicity;

  reaction_type_multiplicity = reaction_multiplicity.begin();
  end_reaction_type_multiplicity = reaction_multiplicity.end();

  NuclearReactionType reaction_type;

  Teuchos::RCP<NuclearScatteringDistribution<NeutronState,NeutronState> > 
    prompt_neutron_emission_distribution;
  
  while( reaction_type_multiplicity != end_reaction_type_multiplicity )
  {
    if( reaction_type_multiplicity->second == 19 )
    {
      // Make sure the fission neutron multiplicity distribution has been
      // created
      testPrecondition( !fission_neutron_multiplicity_distribution.is_null() );
     
      reaction_type = reaction_type_multiplicity->first;

      scattering_dist_factory.createScatteringDistribution( 
					reaction_type,
					prompt_neutron_emission_distribution );
      
      Teuchos::RCP<NuclearReaction>& reaction = 
	d_fission_reactions[reaction_type];

      // Create a basic neutron fission reaction (no delayed info)
      if( delayed_neutron_emission_distribution.is_null() )
      {
	reaction.reset( new NeutronFissionReaction(
			  reaction_type,
			  temperature,
			  reaction_q_value.find(reaction_type)->second,
			  reaction_threshold_index.find(reaction_type)->second,
			  energy_grid,
			  reaction_cross_section.find(reaction_type)->second,
			  fission_neutron_multiplicity_distribution,
			  prompt_neutron_emission_distribution ) );
      }
      // Create a detaild neutron fission reaction (with delayed info)
      else
      {
	reaction.reset( new DetailedNeutronFissionReaction(
			reaction_type,
			temperature,
			reaction_q_value.find(reaction_type)->second,
			reaction_threshold_index.find(reaction_type)->second,
			energy_grid,
			reaction_cross_section.find(reaction_type)->second,
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
// end MonteCarlo_NuclearReactionACEFactory.cpp
//---------------------------------------------------------------------------//
