//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_Photoatom_def.hpp
//! \author Alex Robinson
//! \brief  The photoatom base class template definitions
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHOTOATOM_DEF_HPP
#define MONTE_CARLO_PHOTOATOM_DEF_HPP

// FRENSIE Includes
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

//! Create a core
template<typename InterpPolicy>
void Photoatom::createCore( 
	  const Teuchos::ArrayRCP<double>& energy_grid,
	  const ReactionMap& standard_scattering_reactions,
	  const ReactionMap& standard_absorption_reactions,
	  const Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model,
	  const bool processed_atomic_cross_sections,
	  PhotoatomCore& core )
{
  // Place reactions in the appropriate group
  ConstReactionMap scattering_reactions;
  ConstReactionMap absorption_reactions;
  ConstReactionMap miscellaneous_reactions;
  
  ReactionMap::const_iterator rxn_type_pointer = 
    standard_scattering_reactions.begin();

  while( rxn_type_pointer != standard_scattering_reactions.end() )
  {
    if( Photoatom::absorption_reaction_types.count( rxn_type_pointer->first ) )
      scattering_reactions.insert( *rxn_type_pointer );
    else
      scattering_reactions.insert( *rxn_type_pointer );

    ++rxn_type_pointer;
  }

  rxn_type_pointer = standard_absorption_reactions.begin();

  while( rxn_type_pointer != standard_absorption_reactions.end() )
  {
    if( Photoatom::absorption_reaction_types.count( rxn_type_pointer->first ) )
      absorption_reactions.insert( *rxn_type_pointer );
    else
      miscellaneous_reactions.insert( *rxn_type_pointer );

    ++rxn_type_pointer;
  }

  // Create the total absorption and total reactions
  Teuchos::RCP<PhotoatomicReaction> total_absorption_reaction, total_reaction;
    
  if( processed_atomic_cross_sections )
  {
    Photoatom::createProcessedTotalAbsorptionReaction<InterpPolicy>( 
						   energy_grid,
						   absorption_reactions,
						   total_absorption_reaction );
   Photoatom::createProcessedTotalReaction<InterpPolicy>( 
						   energy_grid,
						   scattering_reactions,
						   total_absorption_reaction,
						   total_reaction );
  }
  else
  {
    Photoatom::createTotalAbsorptionReaction<InterpPolicy>( 
						   energy_grid,
						   absorption_reactions,
						   total_absorption_reaction );
    Photoatom::createTotalReaction<InterpPolicy>( energy_grid,
						  scattering_reactions,
						  total_absorption_reaction,
						  total_reaction );
  }
  
  core = PhotoatomCore( total_reaction,
			total_absorption_reaction,
			scattering_reactions,
			absorption_reactions,
			miscellaneous_reactions,
			relaxation_model );
}

// Constructor
template<typename InterpPolicy>
Photoatom::Photoatom(
	  const std::string& name,
	  const unsigned atomic_number,
	  const double atomic_weight,
	  const Teuchos::ArrayRCP<double>& energy_grid,
	  const Photoatom::ReactionMap& standard_scattering_reactions,
	  const Photoatom::ReactionMap& standard_absorption_reactions,
	  const Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model,
	  const bool processed_atomic_cross_sections )
  : d_name( name ),
    d_atomic_number( atomic_number ),
    d_atomic_weight( atomic_weight ),
    d_core()
{
  // Make sure the atomic weight is valid
  testPrecondition( atomic_weight > 0.0 );
  // Make sure the energy grid is valid
  testPrecondition( energy_grid.size() > 1 );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
						      energy_grid.end() ) );
  // There must be at least one reaction specified
  testPrecondition( standard_scattering_reactions.size() +
		    standard_absorption_reactions.size() > 0 );
  // Make sure the atomic relaxation model is valid
  testPrecondition( !atomic_relaxation_model.is_null() );  

  // Populate the core
  Photoatom::createCore<InterPolicy>( energy_grid,
				      standard_scattering_reactions,
				      standard_absorption_reactions,
				      atomic_relaxation_model,
				      processed_atomic_cross_sections,
				      d_core );
}

// Create the total absorption reaction
template<typename InterpPolicy>
void Photoatom::createTotalAbsorptionReaction(
		const Teuchos::ArrayRCP<double>& energy_grid,
		const ConstReactionMap& absorption_reactions,
		Teuchos::RCP<PhotoatomicReaction>& total_absorption_reaction )
{
  // Make sure the absorption cross section is sized correctly
  testPrecondition( energy_grid.size() > 1 );

  Teuchos::Array<double> absorption_cross_section;
  unsigned absorption_threshold_energy_index = 0u;

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

  d_total_absorption_reaction.reset(
      new AbsorptionPhotoatomicReaction<InterpPolicy,false>(
				     energy_grid,
				     absorption_cross_section_copy,
				     absorption_threshold_energy_index,
				     TOTAL_ABSORPTION_PHOTOATOMIC_REACTION ) );
}

// Create the processed total absorption reaction
template<typename InterpPolicy>
void Photoatom::createProcessedTotalAbsorptionReaction(
		const Teuchos::ArrayRCP<double>& energy_grid,
		const ConstReactionMap& absorption_reactions,
		Teuchos::RCP<PhotoatomicReaction>& total_absorption_reaction )
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
      new AbsorptionPhotoatomicReaction<InterpPolicy,true>(
				     energy_grid,
				     absorption_cross_section_copy,
				     absorption_threshold_energy_index,
				     TOTAL_ABSORPTION_PHOTOATOMIC_REACTION ) );
}

// Create the total reaction
template<typename InterpPolicy>
void Photoatom::createTotalReaction(
	    const Teuchos::ArrayRCP<double>& energy_grid,
	    const ConstReactionMap& scattering_reactions,
	    const Teuchos::RCP<PhotoatomicReaction>& total_absorption_reaction,
	    Teuchos::RCP<PhotoatomicReaction>& total_reaction )
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
      new AbsorptionPhotoatomicReaction<InterpPolicy,false>(
				                energy_grid,
						total_cross_section_copy,
				                total_threshold_energy_index,
				                TOTAL_PHOTOATOMIC_REACTION ) );
}
  
// Calculate the processed total absorption cross section
template<typename InterpPolicy>
void Phototatom::calculateProcessedTotalCrossSection(
	    const Teuchos::ArrayRCP<double>& energy_grid,
	    const ConstReactionMap& scattering_reactions,
	    const Teuchos::RCP<PhotoatomicReaction>& total_absorption_reaction,
	    Teuchos::RCP<PhotoatomicReaction>& total_reaction )
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
      new AbsorptionPhotoatomicReaction<InterpPolicy,true>(
				                energy_grid,
						total_cross_section_copy,
				                total_threshold_energy_index,
				                TOTAL_PHOTOATOMIC_REACTION ) );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHOTOATOM_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_Photoatom_def.hpp
//---------------------------------------------------------------------------//
