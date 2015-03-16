//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroatomCore_def.hpp
//! \author Luke Kersting
//! \brief  The electroatom core class template definitions
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTROATOM_CORE_DEF_HPP
#define MONTE_CARLO_ELECTROATOM_CORE_DEF_HPP

// FRENSIE Includes
#include "Utility_ContractException.hpp"
#include "MonteCarlo_AbsorptionElectroatomicReaction.hpp"
#include "MonteCarlo_VoidAbsorptionElectroatomicReaction.hpp"

namespace MonteCarlo{

// Basic constructor
/*! \details The scattering absorption and miscellaneous reactions will be
 * organized using the standard scattering reactions, standard absorption
 * reactions and the default scattering type map. Once organized, the 
 * total and absorption reactions will be created. If there is not standard 
 * absorption reaction a void absorption reaction will be inserted for the 
 * TotalAbsorptionReaction
 */ 
template<typename InterpPolicy>
ElectroatomCore::ElectroatomCore(
	  const Teuchos::ArrayRCP<double>& energy_grid,
	  const ReactionMap& standard_scattering_reactions,
	  const ReactionMap& standard_absorption_reactions,
	  const Teuchos::RCP<AtomicRelaxationModel>& relaxation_model,
	  const bool processed_atomic_cross_sections,
	  const InterpPolicy policy )
  : d_total_reaction(),
    d_total_absorption_reaction(),
    d_scattering_reactions(),
    d_absorption_reactions(),
    d_miscellaneous_reactions(),
    d_relaxation_model( relaxation_model )
{
  // Make sure the energy grid is valid
  testPrecondition( energy_grid.size() > 1 );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
						      energy_grid.end() ) );
  // There must be at least one reaction specified
  testPrecondition( standard_scattering_reactions.size() +
		            standard_absorption_reactions.size() > 0 );
  // Make sure the relaxation model is valid
  testPrecondition( !relaxation_model.is_null() );

  // Place reactions in the appropriate group
    
  ReactionMap::const_iterator rxn_type_pointer = 
    standard_absorption_reactions.begin();

  while( rxn_type_pointer != standard_absorption_reactions.end() )
  {
    if( ElectroatomCore::scattering_reaction_types.count( rxn_type_pointer->first ) )
      d_scattering_reactions.insert( *rxn_type_pointer );
    else
      d_absorption_reactions.insert( *rxn_type_pointer );

    ++rxn_type_pointer;
  }

  rxn_type_pointer = standard_scattering_reactions.begin();

  while( rxn_type_pointer != standard_scattering_reactions.end() )
  {
    if( ElectroatomCore::scattering_reaction_types.count( rxn_type_pointer->first ) )
      d_scattering_reactions.insert( *rxn_type_pointer );
    else
      d_miscellaneous_reactions.insert( *rxn_type_pointer );

    ++rxn_type_pointer; 
  }
  // Create the total absorption and total reactions
  Teuchos::RCP<ElectroatomicReaction> total_absorption_reaction;
  Teuchos::RCP<ElectroatomicReaction> total_reaction;

  if( processed_atomic_cross_sections )
  {
    if( d_absorption_reactions.size() > 0 )
    {
      ElectroatomCore::createProcessedTotalAbsorptionReaction<InterpPolicy>( 
						 energy_grid,
						 d_absorption_reactions,
						 total_absorption_reaction );
    }
    else
    {
       // Create void absorption reaction
       total_absorption_reaction.reset(
         new VoidAbsorptionElectroatomicReaction() );
    }
    
    d_total_absorption_reaction = total_absorption_reaction;
    
    ElectroatomCore::createProcessedTotalReaction<InterpPolicy>( 
						   energy_grid,
						   d_scattering_reactions,
						   d_total_absorption_reaction,
						   total_reaction );

    d_total_reaction = total_reaction;
  }
  else
  {
    if( d_absorption_reactions.size() > 0 )
    {
      ElectroatomCore::createTotalAbsorptionReaction<InterpPolicy>( 
						 energy_grid,
						 d_absorption_reactions,
						 total_absorption_reaction );
    }
    else
    {
       // Create void absorption reaction
       total_absorption_reaction.reset(
         new VoidAbsorptionElectroatomicReaction() );
    }

    d_total_absorption_reaction = total_absorption_reaction;

    ElectroatomCore::createTotalReaction<InterpPolicy>( 
						  energy_grid,
						  d_scattering_reactions,
						  d_total_absorption_reaction,
						  total_reaction );

    d_total_reaction = total_reaction;
  }

  // Make sure the reactions have been organized appropriately
  testPostcondition( d_scattering_reactions.size() > 0 );
}

// Create the total absorption reaction
template<typename InterpPolicy>
void ElectroatomCore::createTotalAbsorptionReaction(
		const Teuchos::ArrayRCP<double>& energy_grid,
		const ConstReactionMap& absorption_reactions,
		Teuchos::RCP<ElectroatomicReaction>& total_absorption_reaction )
{
  // Make sure the absorption cross section is sized correctly
  testPrecondition( energy_grid.size() > 1 );

  unsigned absorption_threshold_energy_index = 0u;

  Teuchos::Array<double> absorption_cross_section;
 
  ConstReactionMap::const_iterator absorption_reaction;

  for( unsigned i = 0; i < energy_grid.size(); ++i )
  {
    double raw_cross_section = 0.0;
   
    absorption_reaction = absorption_reactions.begin();
   
    while( absorption_reaction != absorption_reactions.end() )
    {
      raw_cross_section +=
        absorption_reaction->second->getCrossSection( energy_grid[i] );

      ++absorption_reaction;
    }

    if( raw_cross_section > 0.0 )
    {
      // Process the raw cross section
      absorption_cross_section.push_back( raw_cross_section );
    }
    else
    {
      // Ignore this data point
      ++absorption_threshold_energy_index;
    }
  }

  // Make sure the absorption cross section is valid
  remember( Teuchos::Array<double>::const_iterator zero_element = 
	    std::find( absorption_cross_section.begin(),
		           absorption_cross_section.end(),
		           0.0 ) );
  testPostcondition( zero_element == absorption_cross_section.end() );
  remember( Teuchos::Array<double>::const_iterator inf_element = 
	    std::find( absorption_cross_section.begin(),
		           absorption_cross_section.end(),
		           std::numeric_limits<double>::infinity() ) );
  testPostcondition( inf_element == absorption_cross_section.end() );

  Teuchos::ArrayRCP<double> absorption_cross_section_copy;
  absorption_cross_section_copy.deepCopy( absorption_cross_section() );

  total_absorption_reaction.reset(
      new AbsorptionElectroatomicReaction<InterpPolicy,false>(
				     energy_grid,
				     absorption_cross_section_copy,
				     absorption_threshold_energy_index,
				     TOTAL_ABSORPTION_ELECTROATOMIC_REACTION ) );
}

// Create the processed total absorption reaction
template<typename InterpPolicy>
void ElectroatomCore::createProcessedTotalAbsorptionReaction(
		const Teuchos::ArrayRCP<double>& energy_grid,
		const ConstReactionMap& absorption_reactions,
		Teuchos::RCP<ElectroatomicReaction>& total_absorption_reaction )
{
  // Make sure the energy grid is valid
  testPrecondition( energy_grid.size() > 1 );

  Teuchos::Array<double> absorption_cross_section;
  unsigned absorption_threshold_energy_index = 0u;

  ConstReactionMap::const_iterator absorption_reaction;

  for( unsigned i = 0; i < energy_grid.size(); ++i )
  {
    absorption_reaction = absorption_reactions.begin();

    double raw_cross_section = 0.0;
    
    const double raw_energy = 
      InterpPolicy::recoverProcessedIndepVar( energy_grid[i] );

    while( absorption_reaction != absorption_reactions.end() )
    {
      raw_cross_section += 
        absorption_reaction->second->getCrossSection( raw_energy );

      ++absorption_reaction;
    }
    
    if( raw_cross_section > 0.0 )
    {
      // Process the raw cross section
      absorption_cross_section.push_back( 
                       InterpPolicy::processDepVar( raw_cross_section ) );
    }
    else
    {
      // Ignore this data point
      ++absorption_threshold_energy_index;
    }
  }
  
  // Make sure the absorption cross section is valid
  remember( Teuchos::Array<double>::const_iterator zero_element = 
	            std::find( absorption_cross_section.begin(),
		                   absorption_cross_section.end(),
		                   0.0 ) );
  testPostcondition( zero_element == absorption_cross_section.end() );
  remember( Teuchos::Array<double>::const_iterator inf_element = 
	          std::find( absorption_cross_section.begin(),
		                 absorption_cross_section.end(),
		                 std::numeric_limits<double>::infinity() ) );
  testPostcondition( inf_element == absorption_cross_section.end() );

  Teuchos::ArrayRCP<double> absorption_cross_section_copy;
  absorption_cross_section_copy.deepCopy( absorption_cross_section() );

  total_absorption_reaction.reset(
      new AbsorptionElectroatomicReaction<InterpPolicy,true>(
				     energy_grid,
				     absorption_cross_section_copy,
				     absorption_threshold_energy_index,
				     TOTAL_ABSORPTION_ELECTROATOMIC_REACTION ) );
}

// Create the total reaction
template<typename InterpPolicy>
void ElectroatomCore::createTotalReaction(
      const Teuchos::ArrayRCP<double>& energy_grid,
      const ConstReactionMap& scattering_reactions,
      const Teuchos::RCP<const ElectroatomicReaction>& total_absorption_reaction,
      Teuchos::RCP<ElectroatomicReaction>& total_reaction )
{
  // Make sure the energy grid is valid
  testPrecondition( energy_grid.size() > 1 );
  // Make sure the absorption reaction has been created
  testPrecondition( !total_absorption_reaction.is_null() );
  
  Teuchos::Array<double> total_cross_section;
  unsigned total_threshold_energy_index = 0u;

  ConstReactionMap::const_iterator scattering_reaction;

  for( unsigned i = 0; i < energy_grid.size(); ++i )
  {
    scattering_reaction = scattering_reactions.begin(); 

    double raw_cross_section = 
      total_absorption_reaction->getCrossSection( energy_grid[i] );
    
    while( scattering_reaction != scattering_reactions.end() )
    {
      raw_cross_section += 
	scattering_reaction->second->getCrossSection( energy_grid[i] );

      ++scattering_reaction;
    }
    
    if( raw_cross_section > 0.0 )
    {
      // Process the raw cross section
      total_cross_section.push_back( raw_cross_section );
    }
    else
{
      // Ignore this data point
      ++total_threshold_energy_index;
    }
  }
  
  // Make sure the absorption cross section is valid
  remember( Teuchos::Array<double>::const_iterator zero_element = 
	    std::find( total_cross_section.begin(),
		           total_cross_section.end(),
		      	   0.0 ) );
  testPostcondition( zero_element == total_cross_section.end() );
  remember( Teuchos::Array<double>::const_iterator inf_element = 
	    	   std::find( total_cross_section.begin(),
		       total_cross_section.end(),
		       std::numeric_limits<double>::infinity() ) );
  testPostcondition( inf_element == total_cross_section.end() );

  Teuchos::ArrayRCP<double> total_cross_section_copy;
  total_cross_section_copy.deepCopy( total_cross_section() );

  total_reaction.reset(
      new AbsorptionElectroatomicReaction<InterpPolicy,false>(
						energy_grid,
						total_cross_section_copy,
						total_threshold_energy_index,
						TOTAL_ELECTROATOMIC_REACTION ) );
}
  
// Calculate the processed total absorption cross section
template<typename InterpPolicy>
void ElectroatomCore::createProcessedTotalReaction(
      const Teuchos::ArrayRCP<double>& energy_grid,
      const ConstReactionMap& scattering_reactions,
      const Teuchos::RCP<const ElectroatomicReaction>& total_absorption_reaction,
      Teuchos::RCP<ElectroatomicReaction>& total_reaction )
{
  // Make sure the energy grid is valid
  testPrecondition( energy_grid.size() > 1 );
  // Make sure the absorption reaction has been created
  testPrecondition( !total_absorption_reaction.is_null() );
  
  Teuchos::Array<double> total_cross_section;
  unsigned total_threshold_energy_index = 0u;

  ConstReactionMap::const_iterator scattering_reaction;

  for( unsigned i = 0; i < energy_grid.size(); ++i )
  {
    scattering_reaction = scattering_reactions.begin(); 
    
    const double raw_energy = 
      InterpPolicy::recoverProcessedIndepVar( energy_grid[i] );

    double raw_cross_section = 
      total_absorption_reaction->getCrossSection( raw_energy );
    
    while( scattering_reaction != scattering_reactions.end() )
    {
      raw_cross_section += 
	scattering_reaction->second->getCrossSection( raw_energy );

      ++scattering_reaction;
    }
    
    if( raw_cross_section > 0.0 )
    {
      // Process the raw cross section
      total_cross_section.push_back( 
			    InterpPolicy::processDepVar( raw_cross_section ) );
    }
    else
    {
      // Ignore this data point
      ++total_threshold_energy_index;
    }
  }
  
  // Make sure the absorption cross section is valid
  remember( Teuchos::Array<double>::const_iterator zero_element = 
	    std::find( total_cross_section.begin(),
		       total_cross_section.end(),
		       0.0 ) );
  testPostcondition( zero_element == total_cross_section.end() );
  remember( Teuchos::Array<double>::const_iterator inf_element = 
	    std::find( total_cross_section.begin(),
		       total_cross_section.end(),
		       std::numeric_limits<double>::infinity() ) );
  testPostcondition( inf_element == total_cross_section.end() );

  Teuchos::ArrayRCP<double> total_cross_section_copy;
  total_cross_section_copy.deepCopy( total_cross_section() );

  total_reaction.reset(
      new AbsorptionElectroatomicReaction<InterpPolicy,true>(
				                energy_grid,
						        total_cross_section_copy,
				                total_threshold_energy_index,
				                TOTAL_ELECTROATOMIC_REACTION ) );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELECTROATOM_CORE_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroatomCore_def.hpp
//---------------------------------------------------------------------------//

