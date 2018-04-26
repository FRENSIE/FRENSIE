//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PositronatomCore_def.hpp
//! \author Luke Kersting
//! \brief  The positron-atom core class template definitions
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_POSITRONATOM_CORE_DEF_HPP
#define MONTE_CARLO_POSITRONATOM_CORE_DEF_HPP

// FRENSIE Includes
#include "Utility_ContractException.hpp"
#include "MonteCarlo_AbsorptionPositronatomicReaction.hpp"
#include "MonteCarlo_VoidAbsorptionPositronatomicReaction.hpp"

namespace MonteCarlo{

// Basic constructor
/*! \details The scattering absorption and miscellaneous reactions will be
 * organized using the standard scattering reactions, standard absorption
 * reactions and the default scattering type map. Once organized, the
 * total and absorption reactions will be created. If there is not a standard
 * absorption reaction a void absorption reaction will be inserted for the
 * TotalAbsorptionReaction
 */
template<typename InterpPolicy>
PositronatomCore::PositronatomCore(
        const std::shared_ptr<const std::vector<double> >& energy_grid,
        const std::shared_ptr<const Utility::HashBasedGridSearcher<double>>& grid_searcher,
        const ConstReactionMap& standard_scattering_reactions,
        const ConstReactionMap& standard_absorption_reactions,
        const std::shared_ptr<const AtomicRelaxationModel>& relaxation_model,
        const bool processed_atomic_cross_sections,
        const InterpPolicy policy )
  : d_total_reaction(),
    d_total_absorption_reaction(),
    d_scattering_reactions(),
    d_absorption_reactions(),
    d_miscellaneous_reactions(),
    d_relaxation_model( relaxation_model ),
    d_grid_searcher( grid_searcher )
{
  // Make sure the energy grid is valid
  testPrecondition( energy_grid->size() > 1 );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid->begin(),
                                                      energy_grid->end() ) );
  // There must be at least one reaction specified
  testPrecondition( standard_scattering_reactions.size() +
                    standard_absorption_reactions.size() > 0 );
  // Make sure the relaxation model is valid
  testPrecondition( relaxation_model.get() );
  // Make sure the hash-based grid searcher is valid
  testPrecondition( grid_searcher.get() );

  // Place reactions in the appropriate group
  ConstReactionMap::const_iterator rxn_type_pointer =
    standard_absorption_reactions.begin();

  while( rxn_type_pointer != standard_absorption_reactions.end() )
  {
    if( PositronatomCore::scattering_reaction_types.count( rxn_type_pointer->first ) )
      d_scattering_reactions.insert( *rxn_type_pointer );
    else
      d_absorption_reactions.insert( *rxn_type_pointer );

    ++rxn_type_pointer;
  }

  rxn_type_pointer = standard_scattering_reactions.begin();

  while( rxn_type_pointer != standard_scattering_reactions.end() )
  {
    if( PositronatomCore::scattering_reaction_types.count( rxn_type_pointer->first ) )
      d_scattering_reactions.insert( *rxn_type_pointer );
    else
      d_miscellaneous_reactions.insert( *rxn_type_pointer );

    ++rxn_type_pointer;
  }
  // Create the total absorption and total reactions
  if( processed_atomic_cross_sections )
  {
    if( d_absorption_reactions.size() > 0 )
    {
      PositronatomCore::createProcessedTotalAbsorptionReaction<InterpPolicy>(
                                                 energy_grid,
                                                 d_absorption_reactions,
                                                 d_total_absorption_reaction );
    }
    else
    {
       // Create void absorption reaction
       d_total_absorption_reaction.reset(
         new VoidAbsorptionPositronatomicReaction() );
    }

    PositronatomCore::createProcessedTotalReaction<InterpPolicy>(
                                                   energy_grid,
                                                   d_scattering_reactions,
                                                   d_total_absorption_reaction,
                                                   d_total_reaction );
  }
  else
  {
    if( d_absorption_reactions.size() > 0 )
    {
      PositronatomCore::createTotalAbsorptionReaction<InterpPolicy>(
                                                 energy_grid,
                                                 d_absorption_reactions,
                                                 d_total_absorption_reaction );
    }
    else
    {
      // Create void absorption reaction
      d_total_absorption_reaction.reset(
         new VoidAbsorptionPositronatomicReaction() );
    }

    PositronatomCore::createTotalReaction<InterpPolicy>(
                                                  energy_grid,
                                                  d_scattering_reactions,
                                                  d_total_absorption_reaction,
                                                  d_total_reaction );
  }

  // Make sure the reactions have been organized appropriately
  testPostcondition( d_scattering_reactions.size() > 0 );
}

// Create the total absorption reaction
template<typename InterpPolicy>
void PositronatomCore::createTotalAbsorptionReaction(
     const std::shared_ptr<const std::vector<double> >& energy_grid,
     const ConstReactionMap& absorption_reactions,
     std::shared_ptr<const PositronatomicReaction>& total_absorption_reaction )
{
  // Make sure the absorption cross section is sized correctly
  testPrecondition( energy_grid->size() > 1 );

  std::shared_ptr<std::vector<double> >
    absorption_cross_section( new std::vector<double> );
  
  unsigned absorption_threshold_energy_index = 0u;

  ConstReactionMap::const_iterator absorption_reaction;

  for( unsigned i = 0; i < energy_grid->size(); ++i )
  {
    double raw_cross_section = 0.0;

    absorption_reaction = absorption_reactions.begin();

    while( absorption_reaction != absorption_reactions.end() )
    {
      raw_cross_section +=
        absorption_reaction->second->getCrossSection( (*energy_grid)[i], i );

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

  total_absorption_reaction.reset(
      new AbsorptionPositronatomicReaction<InterpPolicy,false>(
            energy_grid,
            absorption_cross_section,
            absorption_threshold_energy_index,
            TOTAL_ABSORPTION_POSITRONATOMIC_REACTION ) );
}

// Create the processed total absorption reaction
template<typename InterpPolicy>
void PositronatomCore::createProcessedTotalAbsorptionReaction(
     const std::shared_ptr<const std::vector<double> >& energy_grid,
     const ConstReactionMap& absorption_reactions,
     std::shared_ptr<const PositronatomicReaction>& total_absorption_reaction )
{
  // Make sure the energy grid is valid
  testPrecondition( energy_grid->size() > 1 );

  std::shared_ptr<std::vector<double> >
    absorption_cross_section( new std::vector<double> );
  
  unsigned absorption_threshold_energy_index = 0u;

  ConstReactionMap::const_iterator absorption_reaction;

  for( unsigned i = 0; i < energy_grid->size(); ++i )
  {
    absorption_reaction = absorption_reactions.begin();

    double raw_cross_section = 0.0;

    const double raw_energy =
      InterpPolicy::recoverProcessedIndepVar( (*energy_grid)[i] );

    while( absorption_reaction != absorption_reactions.end() )
    {
      raw_cross_section +=
        absorption_reaction->second->getCrossSection( raw_energy, i );

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

  total_absorption_reaction.reset(
      new AbsorptionPositronatomicReaction<InterpPolicy,true>(
            energy_grid,
            absorption_cross_section,
            absorption_threshold_energy_index,
            TOTAL_ABSORPTION_POSITRONATOMIC_REACTION ) );
}

// Create the total reaction
template<typename InterpPolicy>
void PositronatomCore::createTotalReaction(
      const std::shared_ptr<const std::vector<double> >& energy_grid,
      const ConstReactionMap& scattering_reactions,
      const std::shared_ptr<const PositronatomicReaction>& total_absorption_reaction,
      std::shared_ptr<const PositronatomicReaction>& total_reaction )
{
  // Make sure the energy grid is valid
  testPrecondition( energy_grid->size() > 1 );
  // Make sure the absorption reaction has been created
  testPrecondition( total_absorption_reaction.use_count() > 0 );

  std::shared_ptr<std::vector<double> >
    total_cross_section( new std::vector<double> );
  
  unsigned total_threshold_energy_index = 0u;

  ConstReactionMap::const_iterator scattering_reaction;

  for( unsigned i = 0; i < energy_grid->size(); ++i )
  {
    scattering_reaction = scattering_reactions.begin();

    double raw_cross_section =
      total_absorption_reaction->getCrossSection( (*energy_grid)[i], i );

    while( scattering_reaction != scattering_reactions.end() )
    {
      raw_cross_section +=
        scattering_reaction->second->getCrossSection( (*energy_grid)[i], i );

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

  total_reaction.reset(
      new AbsorptionPositronatomicReaction<InterpPolicy,false>(
            energy_grid,
            total_cross_section,
            total_threshold_energy_index,
            TOTAL_POSITRONATOMIC_REACTION ) );
}

// Calculate the processed total absorption cross section
template<typename InterpPolicy>
void PositronatomCore::createProcessedTotalReaction(
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const ConstReactionMap& scattering_reactions,
    const std::shared_ptr<const PositronatomicReaction>& total_absorption_reaction,
    std::shared_ptr<const PositronatomicReaction>& total_reaction )
{
  // Make sure the energy grid is valid
  testPrecondition( energy_grid->size() > 1 );
  // Make sure the absorption reaction has been created
  testPrecondition( total_absorption_reaction.use_count() > 0 );

  std::shared_ptr<std::vector<double> >
    total_cross_section( new std::vector<double> );
  
  unsigned total_threshold_energy_index = 0u;

  ConstReactionMap::const_iterator scattering_reaction;

  for( unsigned i = 0; i < energy_grid->size(); ++i )
  {
    scattering_reaction = scattering_reactions.begin();

    const double raw_energy =
      InterpPolicy::recoverProcessedIndepVar( (*energy_grid)[i] );

    double raw_cross_section =
      total_absorption_reaction->getCrossSection( raw_energy, i );

    while( scattering_reaction != scattering_reactions.end() )
    {
      raw_cross_section +=
        scattering_reaction->second->getCrossSection( raw_energy, i );

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

  total_reaction.reset(
      new AbsorptionPositronatomicReaction<InterpPolicy,true>(
            energy_grid,
            total_cross_section,
            total_threshold_energy_index,
            TOTAL_POSITRONATOMIC_REACTION ) );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_POSITRONATOM_CORE_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PositronatomCore_def.hpp
//---------------------------------------------------------------------------//

