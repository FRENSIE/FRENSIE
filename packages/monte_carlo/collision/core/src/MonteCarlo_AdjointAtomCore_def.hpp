//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointAtomCore_def.hpp
//! \author Alex Robinson
//! \brief  The adjoint atom core class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_ATOM_CORE_DEF_HPP
#define MONTE_CARLO_ADJOINT_ATOM_CORE_DEF_HPP

// Std Lib Includes
#include <algorithm>

// FRENSIE Includes
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Default constructor
template<typename _ReactionEnumType,
         typename _ForwardReactionType,
         typename _AdjointReactionType,
         typename _ParticleStateType,
         template<typename,typename,typename...> class MapType,
         template<typename,typename...> class SetType>
AdjointAtomCore<_ReactionEnumType,_ForwardReactionType,_AdjointReactionType,_ParticleStateType,MapType,SetType>::AdjointAtomCore()
  : BaseType()
{ /* ... */ }

// Basic constructor
/*! \details Care must be taken when setting the critical line energies,
 * scattering reactions and line energy reactions. The critical line energies
 * must correspond to the critical line energies that are being used by the
 * incoherent scattering reactions. In addition, every line energy reaction
 * must have a corresponding critical line energy. Without a critical line 
 * energy the line energy reaction will never occur.
 */
template<typename _ReactionEnumType,
         typename _ForwardReactionType,
         typename _AdjointReactionType,
         typename _ParticleStateType,
         template<typename,typename,typename...> class MapType,
         template<typename,typename...> class SetType>
AdjointAtomCore<_ReactionEnumType,_ForwardReactionType,_AdjointReactionType,_ParticleStateType,MapType,SetType>::AdjointAtomCore(
     const std::shared_ptr<const std::vector<double> >& critical_line_energies,
     const std::shared_ptr<const ForwardReactionType>& total_forward_reaction,
     const ConstReactionMap& standard_scattering_reactions,
     const ConstReactionMap& standard_absorption_reactions,
     const ConstLineEnergyReactionMap& line_energy_reactions,
     const std::shared_ptr<const AtomicRelaxationModel>& relaxation_model,
     const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
     grid_searcher )
  : BaseType( standard_scattering_reactions,
              standard_absorption_reactions,
              relaxation_model,
              grid_searcher ),
    d_total_forward_reaction( total_forward_reaction ),
    d_line_energy_reactions( line_energy_reactions ),
    d_critical_line_energies( critical_line_energies )
{
  // Make sure that the critical line energy pointer is valid
  testPrecondition( critical_line_energies.get() );
  // Make sure the total forward reaction is valid
  testPrecondition( total_forward_reaction.get() );
  // Make sure the line energy reaction map is valid
  testPrecondition( this->areLineEnergyReactionsValid(
                                                   line_energy_reactions,
                                                   *critical_line_energies ) );
}

// Advanced constructor
/*! \details Care must be taken when setting the critical line energies,
 * scattering reactions and line energy reactions. The critical line energies
 * must correspond to the critical line energies that are being used by the
 * incoherent scattering reactions. In addition, every line energy reaction
 * must have a corresponding critical line energy. Without a critical line 
 * energy the line energy reaction will never occur.
 */
template<typename _ReactionEnumType,
         typename _ForwardReactionType,
         typename _AdjointReactionType,
         typename _ParticleStateType,
         template<typename,typename,typename...> class MapType,
         template<typename,typename...> class SetType>
AdjointAtomCore<_ReactionEnumType,_ForwardReactionType,_AdjointReactionType,_ParticleStateType,MapType,SetType>::AdjointAtomCore(
     const std::shared_ptr<const std::vector<double> >& critical_line_energies,
     const std::shared_ptr<const ReactionType>& total_reaction,
     const std::shared_ptr<const ReactionType>& total_absorption_reaction,
     const std::shared_ptr<const ForwardReactionType>& total_forward_reaction,
     const ConstReactionMap& scattering_reactions,
     const ConstReactionMap& absorption_reactions,
     const ConstReactionMap& miscellaneous_reactions,
     const ConstLineEnergyReactionMap& line_energy_reactions,
     const std::shared_ptr<const AtomicRelaxationModel> relaxation_model,
     const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
     grid_searcher )
  : BaseType( total_reaction,
              total_absorption_reaction,
              scattering_reactions,
              absorption_reactions,
              miscellaneous_reactions,
              relaxation_model,
              grid_searcher ),
    d_total_forward_reaction( total_forward_reaction ),
    d_line_energy_reactions( line_energy_reactions ),
    d_critical_line_energies( critical_line_energies )
{
  // Make sure that the critical line energy pointer is valid
  testPrecondition( critical_line_energies.get() );
  // Make sure the total forward reaction is valid
  testPrecondition( total_forward_reaction.get() );
  // Make sure the line energy reaction map is valid
  testPrecondition( this->areLineEnergyReactionsValid(
                                                   line_energy_reactions,
                                                   *critical_line_energies ) );
}

// Copy constructor
template<typename _ReactionEnumType,
         typename _ForwardReactionType,
         typename _AdjointReactionType,
         typename _ParticleStateType,
         template<typename,typename,typename...> class MapType,
         template<typename,typename...> class SetType>
AdjointAtomCore<_ReactionEnumType,_ForwardReactionType,_AdjointReactionType,_ParticleStateType,MapType,SetType>::AdjointAtomCore( const AdjointAtomCore& instance )
  : BaseType( instance ),
    d_total_forward_reaction( instance.d_total_forward_reaction ),
    d_line_energy_reactions( instance.d_line_energy_reactions ),
    d_critical_line_energies( instance.d_critical_line_energies )
{
  // Make sure that the critical line energy pointer is valid
  testPrecondition( instance.d_critical_line_energies.get() );
  // Make sure the total forward reaction is valid
  testPrecondition( instance.d_total_forward_reaction.get() );
  // Make sure the line energy reaction map is valid
  testPrecondition( this->areLineEnergyReactionsValid(
                                              instance.d_line_energy_reactions,
                                              *d_critical_line_energies ) );
}

// Assignment operator
template<typename _ReactionEnumType,
         typename _ForwardReactionType,
         typename _AdjointReactionType,
         typename _ParticleStateType,
         template<typename,typename,typename...> class MapType,
         template<typename,typename...> class SetType>
AdjointAtomCore<_ReactionEnumType,_ForwardReactionType,_AdjointReactionType,_ParticleStateType,MapType,SetType>&
AdjointAtomCore<_ReactionEnumType,_ForwardReactionType,_AdjointReactionType,_ParticleStateType,MapType,SetType>::operator=( const AdjointAtomCore& instance )
{
  // Make sure that the critical line energy pointer is valid
  testPrecondition( instance.d_critical_line_energies.get() );
  // Make sure the total forward reaction is valid
  testPrecondition( instance.d_total_forward_reaction.get() );
  // Make sure the line energy reaction map is valid
  testPrecondition( this->areLineEnergyReactionsValid(
                                        instance.d_line_energy_reactions,
                                        *instance.d_critical_line_energies ) );

  // Avoid self assignment
  if( this != &instance )
  {
    BaseType::operator=( instance );

    d_total_forward_reaction = instance.d_total_forward_reaction;
    d_line_energy_reactions = instance.d_line_energy_reactions;
    d_critical_line_energies = instance.d_critical_line_energies;
  }

  return *this;
}

// Return the total forward reaction
template<typename _ReactionEnumType,
         typename _ForwardReactionType,
         typename _AdjointReactionType,
         typename _ParticleStateType,
         template<typename,typename,typename...> class MapType,
         template<typename,typename...> class SetType>
auto AdjointAtomCore<_ReactionEnumType,_ForwardReactionType,_AdjointReactionType,_ParticleStateType,MapType,SetType>::getTotalForwardReaction() const -> const ForwardReactionType&
{
  return *d_total_forward_reaction;
}

// Return the line energy reactions
template<typename _ReactionEnumType,
         typename _ForwardReactionType,
         typename _AdjointReactionType,
         typename _ParticleStateType,
         template<typename,typename,typename...> class MapType,
         template<typename,typename...> class SetType>
auto AdjointAtomCore<_ReactionEnumType,_ForwardReactionType,_AdjointReactionType,_ParticleStateType,MapType,SetType>::getLineEnergyReactions() const -> const ConstLineEnergyReactionMap&
{
  return d_line_energy_reactions;
}

// Return the critical line energies
template<typename _ReactionEnumType,
         typename _ForwardReactionType,
         typename _AdjointReactionType,
         typename _ParticleStateType,
         template<typename,typename,typename...> class MapType,
         template<typename,typename...> class SetType>
const std::vector<double>& AdjointAtomCore<_ReactionEnumType,_ForwardReactionType,_AdjointReactionType,_ParticleStateType,MapType,SetType>::getCriticalLineEnergies() const
{
  return *d_critical_line_energies;
}

// Check if the line energy reactions are valid
template<typename _ReactionEnumType,
         typename _ForwardReactionType,
         typename _AdjointReactionType,
         typename _ParticleStateType,
         template<typename,typename,typename...> class MapType,
         template<typename,typename...> class SetType>
bool AdjointAtomCore<_ReactionEnumType,_ForwardReactionType,_AdjointReactionType,_ParticleStateType,MapType,SetType>::areLineEnergyReactionsValid(
                      const ConstLineEnergyReactionMap& line_energy_reactions,
                      const std::vector<double>& critical_line_energies ) const
{
  typename ConstLineEnergyReactionMap::const_iterator line_energies =
    line_energy_reactions.begin();

  // To be valid a line energy reaction must have an associated critical line
  // energy. Without the critical line energy the line energy reaction will
  // never occur.
  while( line_energies != line_energy_reactions.end() )
  {
    if( !std::binary_search( critical_line_energies.begin(),
                             critical_line_energies.end(),
                             line_energies->first ) )
      return false;

    ++line_energies;
  }

  return true;
}
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ADJOINT_ATOM_CORE_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointAtomCore_def.hpp
//---------------------------------------------------------------------------//
