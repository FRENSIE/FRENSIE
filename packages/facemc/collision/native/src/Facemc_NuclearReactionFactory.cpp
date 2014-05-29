//---------------------------------------------------------------------------//
//!
//! \file   Facemc_NuclearReactionFactory.cpp
//! \author Alex Robinson
//! \brief  Nuclear reaction factory class declaration
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Facemc_NuclearReactionFactory.hpp"
#include "Facemc_NeutronScatteringReaction.hpp"
#include "Facemc_NeutronAbsorptionReaction.hpp"
#include "Utility_ContractException.hpp"

namespace Facemc{

// Constructor
/*! \details All blocks from the ACE file will be stored. 
 * \param[in] mtr_block The MTR block stores the ENDF reactions available for 
 * the nuclide.
 * \param[in] lqr_block The LQR block stores the Q-values for each ENDF 
 * reaction. 
 * \param[in] tyr_block The TYR block stores the number of neutrons released 
 * for each ENDF reaction. If the value is negative, scattering takes place in 
 * the CM system. If the value is positive, scattering takes place in the LAB 
 * system. A value of 19 indicates fission. A value of 0 indicates absorption. 
 * A value > 100 indicates non-fission reactions with energy-dependent neutron 
 * multiplicities. 
 * \param[in] lsig_block The LSIG block stores the location of the cross 
 * section for each ENDF reaction in the SIG block. 
 * \param[in] sig_block The SIG block stores the cross section for each ENDF 
 * reaction. 
 * \param[in] land_block The LAND block stores the location of the angular 
 * distribution in the AND block for each ENDF reaction. 
 * \param[in] and_block The AND block stores the angular distribution for each 
 * ENDF reaction. 
 * \param[in] ldlw_block The LDLW block stores the location of the energy 
 * distribution for each ENDF reaction.
 * \param[in] dlw_block The DLW block stores the energy distribution for each 
 * ENDF reaction.
 */
NuclearReactionFactory::NuclearReactionFactory( 
		 const std::string& table_name,
		 const double atomic_weight_ratio,
		 const double temperature,
		 const Teuchos::ArrayRCP<const double>& energy_grid,
		 const Teuchos::ArrayView<const double>& elastic_cross_section,
		 const Teuchos::ArrayView<const double>& mtr_block, 
		 const Teuchos::ArrayView<const double>& lqr_block,
		 const Teuchos::ArrayView<const double>& tyr_block,
		 const Teuchos::ArrayView<const double>& lsig_block,
		 const Teuchos::ArrayView<const double>& sig_block,
		 const Teuchos::ArrayView<const double>& land_block,
		 const Teuchos::ArrayView<const double>& and_block,
		 const Teuchos::ArrayView<const double>& ldlw_block,
		 const Teuchos::ArrayView<const double>& dlw_block )
{ 
  // Make sure there is at least one MT # present
  testPrecondition( mtr_block.size() > 0 );
  // Make sure there is a Q-value for every reaction type
  testPrecondition( lqr_block.size() == mtr_block.size() );
  // Make sure there is a multiplicity value for every reaction type
  testPrecondition( tyr_block.size() == mtr_block.size() );
  // Make sure there is a cross section array index for every reaction type
  testPrecondition( lsig_block.size() == mtr_block.size() );
  // Make sure there is an angular distribution index for every reaction type
  // with outgoing neutrons (plus elastic)
  testPrecondition( land_block.size() <= mtr_block.size()+1 );
  // Make sure there is an energy distribution index for every reaction type
  // with outgoing neutrons
  testPrecondition( ldlw_block.size() <= mtr_block.size() );

  // Create the scattering distribution factory
  NeutronScatteringDistributionFactory 
    scattering_dist_factory( table_name,
			     atomic_weight_ratio,
			     mtr_block,
			     tyr_block,
			     land_block,
			     and_block,
			     ldlw_block,
			     dlw_block );

  // Create a map of the reaction types and their table ordering
  boost::unordered_map<NuclearReactionType,unsigned> reaction_ordering;
  NuclearReactionFactory::createReactionOrderingMap( mtr_block,
						     reaction_ordering );

  // Create a map of the reaction types and the corresponding Q-value
  boost::unordered_map<NuclearReactionType,double> reaction_q_value;
  NuclearReactionFactory::createReactionQValueMap( lqr_block,
						   reaction_ordering,
						   reaction_q_value );
  
  // Create a map of the reaction types and the corresponding multiplicity
  boost::unordered_map<NuclearReactionType,unsigned> reaction_multiplicity;
  NuclearReactionFactory::createReactionMultiplicityMap(tyr_block,
							reaction_ordering,
							reaction_multiplicity);
  
  // Create a map of the reaction types and the corresponding threshold index
  boost::unordered_map<NuclearReactionType,unsigned> reaction_threshold_index;
  NuclearReactionFactory::createReactionThresholdMap(lsig_block,
						     sig_block,
						     reaction_ordering,
						     reaction_threshold_index);
  
  // Create a map of the reaction types and the corresponding cross section
  boost::unordered_map<NuclearReactionType,Teuchos::ArrayRCP<double> >
    reaction_cross_section;
  NuclearReactionFactory::createReactionCrossSectionMap(
						      lsig_block,
						      sig_block,
						      elastic_cross_section,
						      reaction_ordering,
						      reaction_cross_section );
  
  // Create the nuclear reactions
  initializeScatteringReactions( temperature,
				 energy_grid,
				 reaction_q_value,
				 reaction_multiplicity,
				 reaction_threshold_index,
				 reaction_cross_section,
				 scattering_dist_factory );
  initializeAbsorptionReactions( temperature,
				 energy_grid,
				 reaction_q_value,
				 reaction_multiplicity,
				 reaction_threshold_index,
				 reaction_cross_section );
  //initializeFissionReactions();
}

// Create the scattering reactions 
void NuclearReactionFactory::createScatteringReactions( 
      boost::unordered_map<NuclearReactionType,Teuchos::RCP<NuclearReaction> >&
      scattering_reactions ) const
{
  scattering_reactions.insert( d_scattering_reactions.begin(),
			       d_scattering_reactions.end() );
}

// Create the absorption reactions 
void NuclearReactionFactory::createAbsorptionReactions(
      boost::unordered_map<NuclearReactionType,Teuchos::RCP<NuclearReaction> >&
      absorption_reactions ) const
{
  absorption_reactions.insert( d_absorption_reactions.begin(),
			       d_absorption_reactions.end() );
}	     

// Create the fission reactions
void NuclearReactionFactory::createFissionReactions(
      boost::unordered_map<NuclearReactionType,Teuchos::RCP<NuclearReaction> >&
      fission_reactions ) const
{
  fission_reactions.insert( d_fission_reactions.begin(),
			    d_fission_reactions.end() );
}

// Create the reaction type ordering map
void NuclearReactionFactory::createReactionOrderingMap( 
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
void NuclearReactionFactory::createReactionQValueMap(
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
void NuclearReactionFactory::createReactionMultiplicityMap(
   const Teuchos::ArrayView<const double>& tyr_block,
   const boost::unordered_map<NuclearReactionType,unsigned>& reaction_ordering,
   boost::unordered_map<NuclearReactionType,unsigned>& reaction_multiplicity )
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
      multiplicity = tyr_block[reaction->second];
      
      reaction_multiplicity[reaction->first] = 
	static_cast<unsigned>( 
		    Teuchos::ScalarTraits<double>::magnitude( multiplicity ) );
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
void NuclearReactionFactory::createReactionThresholdMap(
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
void NuclearReactionFactory::createReactionCrossSectionMap(
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

// Initialize the scattering reactions
void NuclearReactionFactory::initializeScatteringReactions(
    const double temperature,
    const Teuchos::ArrayRCP<const double> energy_grid,
    const boost::unordered_map<NuclearReactionType,double>& reaction_q_value,
    const boost::unordered_map<NuclearReactionType,unsigned>&
    reaction_multiplicity,
    const boost::unordered_map<NuclearReactionType,unsigned>&
    reaction_threshold_index,
    const boost::unordered_map<NuclearReactionType,Teuchos::ArrayRCP<double> >&
    reaction_cross_section,
    const NeutronScatteringDistributionFactory& scattering_dist_factory )
				
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
    if( reaction_type_multiplicity->second > 0u &&
	reaction_type_multiplicity->second != 19u )
    {
      reaction_type = reaction_type_multiplicity->first;
      
      Teuchos::RCP<NuclearReaction>& reaction = 
	d_scattering_reactions[reaction_type];

      Teuchos::RCP<NeutronScatteringDistribution> scattering_distribution;
      
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

    ++reaction_type_multiplicity;
  }
}

// Initialize the absorption reactions
void NuclearReactionFactory::initializeAbsorptionReactions(
    const double temperature,
    const Teuchos::ArrayRCP<const double> energy_grid,
    const boost::unordered_map<NuclearReactionType,double>& reaction_q_value,
    const boost::unordered_map<NuclearReactionType,unsigned>&
    reaction_multiplicity,
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
void NuclearReactionFactory::initializeFissionReactions(
    const double temperature,
    const Teuchos::ArrayRCP<const double> energy_grid,
    const boost::unordered_map<NuclearReactionType,double>& reaction_q_value,
    const boost::unordered_map<NuclearReactionType,unsigned>&
    reaction_multiplicity,
    const boost::unordered_map<NuclearReactionType,unsigned>&
    reaction_threshold_index,
    const boost::unordered_map<NuclearReactionType,Teuchos::ArrayRCP<double> >&
    reaction_cross_section,
    const NeutronScatteringDistributionFactory& scattering_dist_factory )
{

}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_NuclearReactionFactory.cpp
//---------------------------------------------------------------------------//
