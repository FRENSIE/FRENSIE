//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AtomCore_def.hpp
//! \author Alex Robinson
//! \brief  The atom core class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ATOM_CORE_DEF_HPP
#define MONTE_CARLO_ATOM_CORE_DEF_HPP

// FRENSIE Includes
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Initialize static member data
template<typename _ReactionEnumType,
         typename _ReactionType,
         typename _ParticleStateType,
         template<typename,typename,typename...> class MapType,
         template<typename,typename...> class SetType>
typename AtomCore<_ReactionEnumType,_ReactionType,_ParticleStateType,MapType,SetType>::ReactionEnumTypeSet AtomCore<_ReactionEnumType,_ReactionType,_ParticleStateType,MapType,SetType>::s_absorption_reaction_types;

// Default constructor
template<typename _ReactionEnumType,
         typename _ReactionType,
         typename _ParticleStateType,
         template<typename,typename,typename...> class MapType,
         template<typename,typename...> class SetType>
AtomCore<_ReactionEnumType,_ReactionType,_ParticleStateType,MapType,SetType>::AtomCore()
{ /* ... */ }

// Basic constructor
/*! \details This constructor will not create the total reaction and the
 * total absorption reaction. The creation of these two reactions must be
 * handled in a derived classes constructor by calling the associated
 * set and/or create methods.
 */
template<typename _ReactionEnumType,
         typename _ReactionType,
         typename _ParticleStateType,
         template<typename,typename,typename...> class MapType,
         template<typename,typename...> class SetType>
AtomCore<_ReactionEnumType,_ReactionType,_ParticleStateType,MapType,SetType>::AtomCore(
         const ConstReactionMap& standard_scattering_reactions,
         const ConstReactionMap& standard_absorption_reactions,
         const std::shared_ptr<const AtomicRelaxationModel>& relaxation_model,
         const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
         grid_searcher )
  : d_total_reaction(),
    d_total_absorption_reaction(),
    d_scattering_reactions(),
    d_absorption_reactions(),
    d_miscellaneous_reactions(),
    d_relaxation_model( relaxation_model ),
    d_grid_searcher( grid_searcher )
{
  // There must be at least one reaction specified
  testPrecondition( standard_scattering_reactions.size() +
		    standard_absorption_reactions.size() > 0 );
  // Make sure the relaxation model is valid
  testPrecondition( relaxation_model.get() );
  // Make sure the hash-based grid searcher is valid
  testPrecondition( grid_searcher.get() );

  // Place reactions in the appropriate group
  typename ConstReactionMap::const_iterator rxn_type_pointer =
    standard_scattering_reactions.begin();

  while( rxn_type_pointer != standard_scattering_reactions.end() )
  {
    if( s_absorption_reaction_types.count( rxn_type_pointer->first ) )
      d_absorption_reactions.insert( *rxn_type_pointer );
    else
      d_scattering_reactions.insert( *rxn_type_pointer );

    ++rxn_type_pointer;
  }

  rxn_type_pointer = standard_absorption_reactions.begin();

  while( rxn_type_pointer != standard_absorption_reactions.end() )
  {
    if( s_absorption_reaction_types.count( rxn_type_pointer->first ) )
      d_absorption_reactions.insert( *rxn_type_pointer );
    else
      d_miscellaneous_reactions.insert( *rxn_type_pointer );

    ++rxn_type_pointer;
  }

  // Make sure the reactions have been organized appropriately
  testPostcondition( d_scattering_reactions.size() > 0 );
  testPostcondition( d_scattering_reactions.size() +
                     d_absorption_reactions.size() +
                     d_miscellaneous_reactions.size() ==
                     standard_scattering_reactions.size() +
                     standard_absorption_reactions.size() );
}

// Advanced constructor
/*! \details It is assumed that the scattering, absorption and miscellaneous
 * reactions have already been organized appropriately. The total and total
 * absorption cross sections should have been created from the scattering
 * and absorption reactions.
 */
template<typename _ReactionEnumType,
         typename _ReactionType,
         typename _ParticleStateType,
         template<typename,typename,typename...> class MapType,
         template<typename,typename...> class SetType>
AtomCore<_ReactionEnumType,_ReactionType,_ParticleStateType,MapType,SetType>::AtomCore(
          const std::shared_ptr<const ReactionType>& total_reaction,
          const std::shared_ptr<const ReactionType>& total_absorption_reaction,
          const ConstReactionMap& scattering_reactions,
          const ConstReactionMap& absorption_reactions,
          const ConstReactionMap& miscellaneous_reactions,
          const std::shared_ptr<const AtomicRelaxationModel> relaxation_model,
          const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
          grid_searcher )
  : d_total_reaction( total_reaction ),
    d_total_absorption_reaction( total_absorption_reaction ),
    d_scattering_reactions( d_scattering_reactions ),
    d_absorption_reactions( absorption_reactions ),
    d_miscellaneous_reactions( miscellaneous_reactions ),
    d_relaxation_model( relaxation_model ),
    d_grid_searcher( grid_searcher )
{
  // Make sure the total reaction is valid
  testPrecondition( total_reaction.get() );
  // Make sure the absorption reaction is valid
  testPrecondition( total_absorption_reaction.get() );
  // Make sure the scattering reactions map is valid
  testPrecondition( scattering_reactions.size() > 0 );
  // Make sure the absorption reactions map is valid
  testPrecondition( absorption_reactions.size() > 0 );
  // Make sure the relaxation model is valid
  testPrecondition( relaxation_model.get() );
  // Make sure the grid searcher is valid
  testPrecondition( d_grid_searcher.get() );
}

// Copy constructor
template<typename _ReactionEnumType,
         typename _ReactionType,
         typename _ParticleStateType,
         template<typename,typename,typename...> class MapType,
         template<typename,typename...> class SetType>
AtomCore<_ReactionEnumType,_ReactionType,_ParticleStateType,MapType,SetType>::AtomCore( const AtomCore& instance )
  : d_total_reaction( instance.d_total_reaction ),
    d_total_absorption_reaction( instance.d_total_absorption_reaction ),
    d_scattering_reactions( instance.d_scattering_reactions ),
    d_absorption_reactions( instance.d_absorption_reactions ),
    d_miscellaneous_reactions( instance.d_miscellaneous_reactions ),
    d_relaxation_model( instance.d_relaxation_model ),
    d_grid_searcher( instance.d_grid_searcher )
{
  // Make sure the total reaction is valid
  testPrecondition( instance.d_total_reaction.get() );
  // Make sure the absorption reaction is valid
  testPrecondition( instance.d_total_absorption_reaction.get() );
  // Make sure the scattering and absorption reaction maps are valid
  testPrecondition( instance.d_scattering_reactions.size() +
		    instance.d_absorption_reactions.size() > 0 );
  // Make sure the relaxation model is valid
  testPrecondition( instance.d_relaxation_model.get() );
  // Make sure the grid searcher is valid
  testPrecondition( instance.d_grid_searcher.get() );
}

// Assignment operator
template<typename _ReactionEnumType,
         typename _ReactionType,
         typename _ParticleStateType,
         template<typename,typename,typename...> class MapType,
         template<typename,typename...> class SetType>
AtomCore<_ReactionEnumType,_ReactionType,_ParticleStateType,MapType,SetType>&
AtomCore<_ReactionEnumType,_ReactionType,_ParticleStateType,MapType,SetType>::operator=( const AtomCore& instance )
{
  // Make sure the total reaction is valid
  testPrecondition( instance.d_total_reaction.get() );
  // Make sure the absorption reaction is valid
  testPrecondition( instance.d_total_absorption_reaction.get() );
  // Make sure the scattering and absorption reaction maps are valid
  testPrecondition( instance.d_scattering_reactions.size() +
		    instance.d_absorption_reactions.size() > 0 );
  // Make sure the relaxation model is valid
  testPrecondition( instance.d_relaxation_model.get() );
  // Make sure the grid searcher is valid
  testPrecondition( instance.d_grid_searcher.get() );

  // Avoid self-assignment
  if( this != &instance )
  {
    d_total_reaction = instance.d_total_reaction;
    d_total_absorption_reaction = instance.d_total_absorption_reaction;
    d_scattering_reactions = instance.d_scattering_reactions;
    d_absorption_reactions = instance.d_absorption_reactions;
    d_miscellaneous_reactions = instance.d_miscellaneous_reactions;
    d_relaxation_model = instance.d_relaxation_model;
    d_grid_searcher = instance.d_grid_searcher;
  }

  return *this;
}

// Set the total absorption reaction
template<typename _ReactionEnumType,
         typename _ReactionType,
         typename _ParticleStateType,
         template<typename,typename,typename...> class MapType,
         template<typename,typename...> class SetType>
void AtomCore<_ReactionEnumType,_ReactionType,_ParticleStateType,MapType,SetType>::setTotalAbsorptionReaction( const std::shared_ptr<const ReactionType>& total_absorption_reaction )
{
  // Make sure that the reaction pointer is valid
  testPrecondition( total_absorption_reaction.get() );

  d_total_absorption_reaction = total_absorption_reaction;
}

// Create the total absorption reaction
template<typename _ReactionEnumType,
         typename _ReactionType,
         typename _ParticleStateType,
         template<typename,typename,typename...> class MapType,
         template<typename,typename...> class SetType>
template<typename InterpPolicy,
         template<typename,bool> class TotalAbsorptionReactionType>
void AtomCore<_ReactionEnumType,_ReactionType,_ParticleStateType,MapType,SetType>::createTotalAbsorptionReaction(
                const std::shared_ptr<const std::vector<double> >& energy_grid,
                const ReactionEnumType total_absorption_reaction_type )

{
  // Make sure the absorption cross section is sized correctly
  testPrecondition( energy_grid->size() > 1 );

  std::shared_ptr<std::vector<double> >
    absorption_cross_section( new std::vector<double> );
  
  size_t absorption_threshold_energy_index = 0u;

  typename ConstReactionMap::const_iterator absorption_reaction;

  for( size_t i = 0; i < energy_grid->size(); ++i )
  {
    double raw_cross_section = 0.0;

    absorption_reaction = d_absorption_reactions.begin();

    while( absorption_reaction != d_absorption_reactions.end() )
    {
      if( i < energy_grid->size() - 1 )
      {
        raw_cross_section +=
          absorption_reaction->second->getCrossSection( (*energy_grid)[i], i );
      }
      else
      {
        raw_cross_section +=
          absorption_reaction->second->getCrossSection( (*energy_grid)[i], i-1 );
      }

      ++absorption_reaction;
    }

    if( raw_cross_section > 0.0 )
    {
      // Process the raw cross section
      absorption_cross_section->push_back( raw_cross_section );
    }
    else
    {
      // Ignore this data point
      ++absorption_threshold_energy_index;
    }
  }

  // Make sure the absorption cross section is valid
  remember( std::vector<double>::const_iterator zero_element =
	    std::find( absorption_cross_section->begin(),
		       absorption_cross_section->end(),
		       0.0 ) );
  testPostcondition( zero_element == absorption_cross_section->end() );
  remember( std::vector<double>::const_iterator inf_element =
	    std::find( absorption_cross_section->begin(),
		       absorption_cross_section->end(),
		       std::numeric_limits<double>::infinity() ) );
  testPostcondition( inf_element == absorption_cross_section->end() );

  d_total_absorption_reaction.reset(
      new TotalAbsorptionReactionType<InterpPolicy,false>(
				     energy_grid,
				     absorption_cross_section,
				     absorption_threshold_energy_index,
                                     d_grid_searcher,
				     total_absorption_reaction_type ) );
}

// Create the processed total absorption reaction
template<typename _ReactionEnumType,
         typename _ReactionType,
         typename _ParticleStateType,
         template<typename,typename,typename...> class MapType,
         template<typename,typename...> class SetType>
template<typename InterpPolicy,
         template<typename,bool> class TotalAbsorptionReactionType>
void AtomCore<_ReactionEnumType,_ReactionType,_ParticleStateType,MapType,SetType>::createProcessedTotalAbsorptionReaction(
       const std::shared_ptr<const std::vector<double> >& energy_grid,
       const ReactionEnumType total_absorption_reaction_type )
{
  // Make sure the energy grid is valid
  testPrecondition( energy_grid->size() > 1 );

  std::shared_ptr<std::vector<double> >
    absorption_cross_section( new std::vector<double> );
  
  size_t absorption_threshold_energy_index = 0u;

  typename ConstReactionMap::const_iterator absorption_reaction;

  for( size_t i = 0; i < energy_grid->size(); ++i )
  {
    absorption_reaction = d_absorption_reactions.begin();

    double raw_cross_section = 0.0;

    const double raw_energy =
      InterpPolicy::recoverProcessedIndepVar( (*energy_grid)[i] );

    while( absorption_reaction != d_absorption_reactions.end() )
    {
      raw_cross_section +=
        absorption_reaction->second->getCrossSection( raw_energy );

      ++absorption_reaction;
    }

    if( raw_cross_section > 0.0 )
    {
      // Process the raw cross section
      absorption_cross_section->push_back(
			    InterpPolicy::processDepVar( raw_cross_section ) );
    }
    else
    {
      // Ignore this data point
      ++absorption_threshold_energy_index;
    }
  }

  // Make sure the absorption cross section is valid
  remember( std::vector<double>::const_iterator zero_element =
	    std::find( absorption_cross_section->begin(),
		       absorption_cross_section->end(),
		       0.0 ) );
  testPostcondition( zero_element == absorption_cross_section->end() );
  remember( std::vector<double>::const_iterator inf_element =
	    std::find( absorption_cross_section->begin(),
		       absorption_cross_section->end(),
		       std::numeric_limits<double>::infinity() ) );
  testPostcondition( inf_element == absorption_cross_section->end() );

  d_total_absorption_reaction.reset(
      new TotalAbsorptionReactionType<InterpPolicy,true>(
				     energy_grid,
				     absorption_cross_section,
				     absorption_threshold_energy_index,
                                     d_grid_searcher,
				     total_absorption_reaction_type ) );
}

// Create the total reaction
template<typename _ReactionEnumType,
         typename _ReactionType,
         typename _ParticleStateType,
         template<typename,typename,typename...> class MapType,
         template<typename,typename...> class SetType>
template<typename InterpPolicy,
         template<typename,bool> class TotalReactionType>
void AtomCore<_ReactionEnumType,_ReactionType,_ParticleStateType,MapType,SetType>::createTotalReaction(
      const std::shared_ptr<const std::vector<double> >& energy_grid,
      const ReactionEnumType total_reaction_type )
{
  // Make sure the energy grid is valid
  testPrecondition( energy_grid->size() > 1 );
  // Make sure the absorption reaction has been created
  testPrecondition( d_total_absorption_reaction.get() );

  std::shared_ptr<std::vector<double> >
    total_cross_section( new std::vector<double> );
  
  size_t total_threshold_energy_index = 0u;

  typename ConstReactionMap::const_iterator scattering_reaction;

  for( size_t i = 0; i < energy_grid->size(); ++i )
  {
    scattering_reaction = d_scattering_reactions.begin();

    double raw_cross_section = 0.0;

    if( i < energy_grid->size() - 1 )
    {
      raw_cross_section =
        d_total_absorption_reaction->getCrossSection( (*energy_grid)[i], i );
    }
    else
    {
      raw_cross_section = 
        d_total_absorption_reaction->getCrossSection( (*energy_grid)[i], i-1 );
    }

    while( scattering_reaction != d_scattering_reactions.end() )
    {
      if( i < energy_grid->size() - 1 )
      {
        raw_cross_section +=
          scattering_reaction->second->getCrossSection( (*energy_grid)[i], i );
      }
      else
      {
        raw_cross_section +=
          scattering_reaction->second->getCrossSection( (*energy_grid)[i], i-1 );
      }

      ++scattering_reaction;
    }

    if( raw_cross_section > 0.0 )
    {
      // Process the raw cross section
      total_cross_section->push_back( raw_cross_section );
    }
    else
    {
      // Ignore this data point
      ++total_threshold_energy_index;
    }
  }

  // Make sure the absorption cross section is valid
  remember( std::vector<double>::const_iterator zero_element =
	    std::find( total_cross_section->begin(),
                       total_cross_section->end(),
                       0.0 ) );
  testPostcondition( zero_element == total_cross_section->end() );
  remember( std::vector<double>::const_iterator inf_element =
	    	   std::find( total_cross_section->begin(),
                              total_cross_section->end(),
                              std::numeric_limits<double>::infinity() ) );
  testPostcondition( inf_element == total_cross_section->end() );

  d_total_reaction.reset( new TotalReactionType<InterpPolicy,false>(
						  energy_grid,
                                                  total_cross_section,
						  total_threshold_energy_index,
                                                  d_grid_searcher,
                                                  total_reaction_type ) );
}

// Calculate the processed total absorption cross section
template<typename _ReactionEnumType,
         typename _ReactionType,
         typename _ParticleStateType,
         template<typename,typename,typename...> class MapType,
         template<typename,typename...> class SetType>
template<typename InterpPolicy,
         template<typename,bool> class TotalReactionType>
void AtomCore<_ReactionEnumType,_ReactionType,_ParticleStateType,MapType,SetType>::createProcessedTotalReaction(
      const std::shared_ptr<const std::vector<double> >& energy_grid,
      const ReactionEnumType total_reaction_type )
{
  // Make sure the energy grid is valid
  testPrecondition( energy_grid->size() > 1 );
  // Make sure the absorption reaction has been created
  testPrecondition( d_total_absorption_reaction.get() );

  std::shared_ptr<std::vector<double> >
    total_cross_section( new std::vector<double> );
  
  size_t total_threshold_energy_index = 0u;

  typename ConstReactionMap::const_iterator scattering_reaction;

  for( size_t i = 0; i < energy_grid->size(); ++i )
  {
    scattering_reaction = d_scattering_reactions.begin();

    const double raw_energy =
      InterpPolicy::recoverProcessedIndepVar( (*energy_grid)[i] );

    double raw_cross_section =
      d_total_absorption_reaction->getCrossSection( raw_energy );

    while( scattering_reaction != d_scattering_reactions.end() )
    {
      raw_cross_section +=
        scattering_reaction->second->getCrossSection( raw_energy );

      ++scattering_reaction;
    }

    if( raw_cross_section > 0.0 )
    {
      // Process the raw cross section
      total_cross_section->push_back(
			    InterpPolicy::processDepVar( raw_cross_section ) );
    }
    else
    {
      // Ignore this data point
      ++total_threshold_energy_index;
    }
  }

  // Make sure the absorption cross section is valid
  remember( std::vector<double>::const_iterator zero_element =
	    std::find( total_cross_section->begin(),
		       total_cross_section->end(),
		       0.0 ) );
  testPostcondition( zero_element == total_cross_section->end() );
  remember( std::vector<double>::const_iterator inf_element =
	    std::find( total_cross_section->begin(),
		       total_cross_section->end(),
		       std::numeric_limits<double>::infinity() ) );
  testPostcondition( inf_element == total_cross_section->end() );

  d_total_reaction.reset( new TotalReactionType<InterpPolicy,true>(
                                                  energy_grid,
                                                  total_cross_section,
                                                  total_threshold_energy_index,
                                                  d_grid_searcher,
                                                  total_reaction_type ) );
}

// Set the absorption reaction types
template<typename _ReactionEnumType,
         typename _ReactionType,
         typename _ParticleStateType,
         template<typename,typename,typename...> class MapType,
         template<typename,typename...> class SetType>
void AtomCore<_ReactionEnumType,_ReactionType,_ParticleStateType,MapType,SetType>::setAbsorptionReactionTypes(
                              const ReactionEnumTypeSet& absorption_reactions )
{
  s_absorption_reaction_types = absorption_reactions;
}

// Get the reaction types that are treated as absorption
template<typename _ReactionEnumType,
         typename _ReactionType,
         typename _ParticleStateType,
         template<typename,typename,typename...> class MapType,
         template<typename,typename...> class SetType>
auto AtomCore<_ReactionEnumType,_ReactionType,_ParticleStateType,MapType,SetType>::getAbsorptionReactionTypes() -> const ReactionEnumTypeSet&
{
  return s_absorption_reaction_types;
}

// Return the total reaction
template<typename _ReactionEnumType,
         typename _ReactionType,
         typename _ParticleStateType,
         template<typename,typename,typename...> class MapType,
         template<typename,typename...> class SetType>
inline auto AtomCore<_ReactionEnumType,_ReactionType,_ParticleStateType,MapType,SetType>::getTotalReaction() const -> const ReactionType&
{
  return *d_total_reaction;
}

// Return the total absorption reaction
template<typename _ReactionEnumType,
         typename _ReactionType,
         typename _ParticleStateType,
         template<typename,typename,typename...> class MapType,
         template<typename,typename...> class SetType>
inline auto AtomCore<_ReactionEnumType,_ReactionType,_ParticleStateType,MapType,SetType>::getTotalAbsorptionReaction() const -> const ReactionType&
{
  return *d_total_absorption_reaction;
}

// Return the scattering reactions
template<typename _ReactionEnumType,
         typename _ReactionType,
         typename _ParticleStateType,
         template<typename,typename,typename...> class MapType,
         template<typename,typename...> class SetType>
inline auto AtomCore<_ReactionEnumType,_ReactionType,_ParticleStateType,MapType,SetType>::getScatteringReactions() const -> const ConstReactionMap&
{
  return d_scattering_reactions;
}

// Return the scattering reaction types
template<typename _ReactionEnumType,
         typename _ReactionType,
         typename _ParticleStateType,
         template<typename,typename,typename...> class MapType,
         template<typename,typename...> class SetType>
void AtomCore<_ReactionEnumType,_ReactionType,_ParticleStateType,MapType,SetType>::getScatteringReactionTypes( ReactionEnumTypeSet& reaction_types ) const
{
  typename ConstReactionMap::const_iterator reaction_it =
    d_scattering_reactions.begin();

  while( reaction_it != d_scattering_reactions.end() )
  {
    reaction_types.insert( reaction_it->first );

    ++reaction_it;
  }
}

// Return the absorption reactions
template<typename _ReactionEnumType,
         typename _ReactionType,
         typename _ParticleStateType,
         template<typename,typename,typename...> class MapType,
         template<typename,typename...> class SetType>
inline auto AtomCore<_ReactionEnumType,_ReactionType,_ParticleStateType,MapType,SetType>::getAbsorptionReactions() const -> const ConstReactionMap&
{
  return d_absorption_reactions;
}

// Return the absorption reaction types
template<typename _ReactionEnumType,
         typename _ReactionType,
         typename _ParticleStateType,
         template<typename,typename,typename...> class MapType,
         template<typename,typename...> class SetType>
void AtomCore<_ReactionEnumType,_ReactionType,_ParticleStateType,MapType,SetType>::getAbsorptionReactionTypes( ReactionEnumTypeSet& reaction_types ) const
{
  typename ConstReactionMap::const_iterator reaction_it =
    d_absorption_reactions.begin();

  while( reaction_it != d_absorption_reactions.end() )
  {
    reaction_types.insert( reaction_it->first );

    ++reaction_it;
  }
}

// Return the miscellaneous reactions
template<typename _ReactionEnumType,
         typename _ReactionType,
         typename _ParticleStateType,
         template<typename,typename,typename...> class MapType,
         template<typename,typename...> class SetType>
inline auto AtomCore<_ReactionEnumType,_ReactionType,_ParticleStateType,MapType,SetType>::getMiscReactions() const -> const ConstReactionMap&
{
  return d_miscellaneous_reactions;
}

// return the miscellaneous reaction types
template<typename _ReactionEnumType,
         typename _ReactionType,
         typename _ParticleStateType,
         template<typename,typename,typename...> class MapType,
         template<typename,typename...> class SetType>
void AtomCore<_ReactionEnumType,_ReactionType,_ParticleStateType,MapType,SetType>::getMiscReactionTypes( ReactionEnumTypeSet& reaction_types ) const
{
  typename ConstReactionMap::const_iterator reaction_it =
    d_miscellaneous_reactions.begin();

  while( reaction_it != d_miscellaneous_reactions.end() )
  {
    reaction_types.insert( reaction_it->first );

    ++reaction_it;
  }
}

// Return the reaction types
template<typename _ReactionEnumType,
         typename _ReactionType,
         typename _ParticleStateType,
         template<typename,typename,typename...> class MapType,
         template<typename,typename...> class SetType>
void AtomCore<_ReactionEnumType,_ReactionType,_ParticleStateType,MapType,SetType>::getReactionTypes( ReactionEnumTypeSet& reaction_types ) const
{
  this->getScatteringReactionTypes( reaction_types );
  this->getAbsorptionReactionTypes( reaction_types );
  this->getMiscReactionTypes( reaction_types );

  // Add the special reaction types
  reaction_types.insert( d_total_reaction->getReactionType() );

  if( d_absorption_reactions.size() > 0 )
    reaction_types.insert( d_total_absorption_reaction->getReactionType() );
}

// Return the atomic relaxation model
template<typename _ReactionEnumType,
         typename _ReactionType,
         typename _ParticleStateType,
         template<typename,typename,typename...> class MapType,
         template<typename,typename...> class SetType>
inline const AtomicRelaxationModel& AtomCore<_ReactionEnumType,_ReactionType,_ParticleStateType,MapType,SetType>::getAtomicRelaxationModel() const
{
  return *d_relaxation_model;
}

// Return the hash-based grid searcher
template<typename _ReactionEnumType,
         typename _ReactionType,
         typename _ParticleStateType,
         template<typename,typename,typename...> class MapType,
         template<typename,typename...> class SetType>
inline const Utility::HashBasedGridSearcher<double>& AtomCore<_ReactionEnumType,_ReactionType,_ParticleStateType,MapType,SetType>::getGridSearcher() const
{
  return *d_grid_searcher;
}

// Test if all of the reactions share a common energy grid
template<typename _ReactionEnumType,
         typename _ReactionType,
         typename _ParticleStateType,
         template<typename,typename,typename...> class MapType,
         template<typename,typename...> class SetType>
bool AtomCore<_ReactionEnumType,_ReactionType,_ParticleStateType,MapType,SetType>::hasSharedEnergyGrid() const
{
  // Because the absorption reaction is sometimes a "void" reaction, which
  // can be used safely with any energy grid but will not pass the default
  // check, we will must use it for this check
  if( !d_total_absorption_reaction->isEnergyGridShared( *d_total_reaction ) )
    return false;

  typename ConstReactionMap::const_iterator reaction_it =
    d_scattering_reactions.begin();

  while( reaction_it != d_scattering_reactions.end() )
  {
    if( !d_total_reaction->isEnergyGridShared( *reaction_it->second ) )
      return false;

    ++reaction_it;
  }

  reaction_it = d_absorption_reactions.begin();

  while( reaction_it != d_absorption_reactions.end() )
  {
    if( !d_total_reaction->isEnergyGridShared( *reaction_it->second ) )
      return false;

    ++reaction_it;
  }

  reaction_it = d_miscellaneous_reactions.begin();

  while( reaction_it != d_miscellaneous_reactions.end() )
  {
    if( !d_total_reaction->isEnergyGridShared( *reaction_it->second ) )
      return false;

    ++reaction_it;
  }

  return true;
}
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ATOM_CORE_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AtomCore_def.hpp
//---------------------------------------------------------------------------//
