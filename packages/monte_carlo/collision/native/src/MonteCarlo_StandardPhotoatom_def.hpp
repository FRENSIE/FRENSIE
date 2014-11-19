//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardPhotoatom.hpp
//! \author Alex Robinson
//! \brief  The standard photoatom class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_PHOTOATOM_DEF_HPP
#define MONTE_CARLO_STANDARD_PHOTOATOM_DEF_HPP

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "Utility_SortAlgorithms.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
template<typename InterpPolicy, bool processed_cross_section>
StandardPhotoatom<InterpPolicy,processed_cross_section>::StandardPhotoatom(
	  const std::string& name,
	  const unsigned atomic_number,
	  const double atomic_weight,
	  const Teuchos::ArrayRCP<double>& energy_grid,
	  const Photoatom::ReactionMap& standard_scattering_reactions,
	  const Photoatom::ReactionMap& standard_absorption_reactions,
	  const Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model )
  : Photoatom( name,
	       atomic_number,
	       atomic_weight,
	       standard_scattering_reactions,
	       standard_absorption_reactions,
	       atomic_relaxation_model ),
    d_total_reaction(),
    d_total_absorption_reaction()
{
  // Make sure the atomic weight is valid
  testPrecondition( atomic_weight > 0.0 );
  // Make sure the energy grid is valid
  testPrecondition( energy_grid.size() > 1 );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
						      energy_grid.end() ) );

  // Calculate the total absorption and total cross sections
  if( processed_cross_section )
  {
    calculateProcessedTotalAbsorptionCrossSection( energy_grid );
    calculateProcessedTotalCrossSection( energy_grid );
  }
  else
  {
    calculateTotalAbsorptionCrossSection( energy_grid );
    calculateTotalCrossSection( energy_grid );  
  }

  // Make sure the total and absorption cross sections have been created
  testPostcondition( !d_total_reaction.is_null() );
  testPostcondition( !d_total_absorption_reaction.is_null() );
}

// Return the total cross section at the desired energy
template<typename InterpPolicy, bool processed_cross_section>
double StandardPhotoatom<InterpPolicy,processed_cross_section>::getTotalCrossSection( const double energy ) const
{
  return d_total_reaction->getCrossSection( energy );
}

// Return the total absorption cross section at the desired energy
template<typename InterpPolicy, bool processed_cross_section>
double StandardPhotoatom<InterpPolicy,processed_cross_section>::getAbsorptionCrossSection( const double energy ) const
{
  return d_total_absorption_reaction->getCrossSection( energy );
}

// Calculate the total absorption cross section
template<typename InterpPolicy, bool processed_cross_section>
void StandardPhotoatom<InterpPolicy,processed_cross_section>::calculateProcessedTotalAbsorptionCrossSection(
				 const Teuchos::ArrayRCP<double>& energy_grid )
{
  // Make sure the energy grid is valid
  testPrecondition( energy_grid.size() > 1 );
    
  Teuchos::Array<double> absorption_cross_section;
  unsigned absorption_threshold_energy_index = 0u;

  Photoatom::ReactionMap::const_iterator absorption_reaction;

  for( unsigned i = 0; i < energy_grid.size(); ++i )
  {
    absorption_reaction = getAbsorptionReactions().begin();

    double raw_cross_section = 0.0;
    
    const double raw_energy = 
      InterpPolicy::recoverProcessedIndepVar( energy_grid[i] );

    while( absorption_reaction != getAbsorptionReactions().end() )
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

  d_total_absorption_reaction.reset(
      new AbsorptionPhotoatomicReaction<InterpPolicy,true>(
				     energy_grid,
				     absorption_cross_section_copy,
				     absorption_threshold_energy_index,
				     TOTAL_ABSORPTION_PHOTOATOMIC_REACTION ) );
}

// Calculate the total absorption cross section
template<typename InterpPolicy, bool processed_cross_section>
void StandardPhotoatom<InterpPolicy,processed_cross_section>::calculateTotalAbsorptionCrossSection(
				 const Teuchos::ArrayRCP<double>& energy_grid )
{
  // Make sure the absorption cross section is sized correctly
  testPrecondition( energy_grid.size() > 1 );

  Teuchos::Array<double> absorption_cross_section;
  unsigned absorption_threshold_energy_index = 0u;

  Photoatom::ReactionMap::const_iterator absorption_reaction;

  for( unsigned i = 0; i < energy_grid.size(); ++i )
  {
    double raw_cross_section = 0.0;
    
    absorption_reaction = getAbsorptionReactions().begin();
    
    while( absorption_reaction != getAbsorptionReactions().end() )
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

// Calculate the total cross section
template<typename InterpPolicy, bool processed_cross_section>
void StandardPhotoatom<InterpPolicy,processed_cross_section>::calculateProcessedTotalCrossSection(
				 const Teuchos::ArrayRCP<double>& energy_grid )
{
  // Make sure the energy grid is valid
  testPrecondition( energy_grid.size() > 1 );
  // Make sure the absorption reaction has been created
  testPrecondition( !d_total_absorption_reaction.is_null() );
  
  Teuchos::Array<double> total_cross_section;
  unsigned total_threshold_energy_index = 0u;

  Photoatom::ReactionMap::const_iterator scattering_reaction;

  for( unsigned i = 0; i < energy_grid.size(); ++i )
  {
    scattering_reaction = getScatteringReactions().begin(); 
    
    const double raw_energy = 
      InterpPolicy::recoverProcessedIndepVar( energy_grid[i] );

    double raw_cross_section = 
      d_total_absorption_reaction->getCrossSection( raw_energy );
    
    while( scattering_reaction != getScatteringReactions().end() )
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

  d_total_reaction.reset(
      new AbsorptionPhotoatomicReaction<InterpPolicy,true>(
				                energy_grid,
						total_cross_section_copy,
				                total_threshold_energy_index,
				                TOTAL_PHOTOATOMIC_REACTION ) );
}

// Calculate the total cross section
template<typename InterpPolicy, bool processed_cross_section>
void StandardPhotoatom<InterpPolicy,processed_cross_section>::calculateTotalCrossSection(
				 const Teuchos::ArrayRCP<double>& energy_grid )
{
  // Make sure the energy grid is valid
  testPrecondition( energy_grid.size() > 1 );
  // Make sure the absorption reaction has been created
  testPrecondition( !d_total_absorption_reaction.is_null() );
  
  Teuchos::Array<double> total_cross_section;
  unsigned total_threshold_energy_index = 0u;

  Photoatom::ReactionMap::const_iterator scattering_reaction;

  for( unsigned i = 0; i < energy_grid.size(); ++i )
  {
    scattering_reaction = getScatteringReactions().begin(); 

    double raw_cross_section = 
      d_total_absorption_reaction->getCrossSection( energy_grid[i] );
    
    while( scattering_reaction != getScatteringReactions().end() )
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

  d_total_reaction.reset(
      new AbsorptionPhotoatomicReaction<InterpPolicy,false>(
				                energy_grid,
						total_cross_section_copy,
				                total_threshold_energy_index,
				                TOTAL_PHOTOATOMIC_REACTION ) );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_PHOTOATOM_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardPhotoatom_def.hpp
//---------------------------------------------------------------------------//
