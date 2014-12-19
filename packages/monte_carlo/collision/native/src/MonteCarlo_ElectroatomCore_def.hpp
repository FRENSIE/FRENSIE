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

namespace MonteCarlo{
/*
// Basic constructor
/*! \details The scattering and miscellaneous reactions will be
 * organized using the standard scattering reactions. Once organized, the 
 * total and absorption reactions will be created.
 *
template<typename InterpPolicy>
ElectroatomCore::ElectroatomCore(
	  const Teuchos::ArrayRCP<double>& energy_grid,
	  const ReactionMap& standard_scattering_reactions,
	  const Teuchos::RCP<AtomicRelaxationModel>& relaxation_model,
	  const bool processed_atomic_cross_sections,
	  const InterpPolicy policy )
  : d_total_reaction(),
    d_scattering_reactions(),
    d_miscellaneous_reactions(),
    d_relaxation_model( relaxation_model )
{
  // Make sure the energy grid is valid
  testPrecondition( energy_grid.size() > 1 );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
						                              energy_grid.end() ) );
  // There must be at least one reaction specified
  testPrecondition( standard_scattering_reactions.size() > 0 );
  // Make sure the relaxation model is valid
  testPrecondition( !relaxation_model.is_null() );

  // Place reactions in the appropriate group
    
  ReactionMap::const_iterator rxn_type_pointer = 
    standard_scattering_reactions.begin();

  while( rxn_type_pointer != standard_scattering_reactions.end() )
  {
    if( ElectroatomCore::scattering_reaction_types.count( rxn_type_pointer->first ) )
      d_scattering_reactions.insert( *rxn_type_pointer );
    else
      d_miscellaneous_reactions.insert( *rxn_type_pointer );

    ++rxn_type_pointer;
  }
  
  // Create the total reactions
  Teuchos::RCP<ElectroatomicReaction> total_reaction;

  if( processed_atomic_cross_sections )
  {
    ElectroatomCore::createProcessedTotalReaction<InterpPolicy>( 
						   energy_grid,
						   d_total_scattering_reaction,
						   total_reaction );

    d_total_reaction = total_reaction;
  }
  else
  {   
    ElectroatomCore::createTotalReaction<InterpPolicy>( 
						  energy_grid,
						  d_total_scattering_reaction,
						  total_reaction );

    d_total_reaction = total_reaction;
  }

  // Make sure the reactions have been organized appropriately
  testPostcondition( d_scattering_reactions.size() > 0 );
}

// Create the total reaction
template<typename InterpPolicy>
void ElectroatomCore::createTotalReaction(
      const Teuchos::ArrayRCP<double>& energy_grid,
      const ConstReactionMap& scattering_reactions,
      Teuchos::RCP<ElectroatomicReaction>& total_reaction )
{
  // Make sure the energy grid is valid
  testPrecondition( energy_grid.size() > 1 );
  
  Teuchos::Array<double> total_cross_section;
  unsigned total_threshold_energy_index = 0u;

  ConstReactionMap::const_iterator scattering_reaction;

  for( unsigned i = 0; i < energy_grid.size(); ++i )
  {
    scattering_reaction = scattering_reactions.begin();
    
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
  
  // Make sure the cross section is valid
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
      new StandardElectroatomicReaction<InterpPolicy,false>(
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
      new StandardElectroatomicReaction<InterpPolicy,true>(
				                energy_grid,
						        total_cross_section_copy,
				                total_threshold_energy_index,
				                TOTAL_ELECTROATOMIC_REACTION ) );
}
*/
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELECTROATOM_CORE_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroatomCore_def.hpp
//---------------------------------------------------------------------------//

