//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointAtomCore.hpp
//! \author Alex Robinson
//! \brief  The adjoint atom core class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_ATOM_CORE_HPP
#define MONTE_CARLO_ADJOINT_ATOM_CORE_HPP

// FRENSIE Includes
#include "MonteCarlo_AtomCore.hpp"

namespace MonteCarlo{

/*! The adjoint atom core class
 * \details This class can be used to store all reactions and the atomic
 * relaxation model associated with an adjoint atom. Exposing this object (e.g.
 * get method or export method) is safe since it only allows access to
 * the underlying member data in a way that prohibits modification of that
 * data. This class was created to address the issue that arises when dealing
 * with adjoint photonuclear data - adjoint photo-nuclides that share the same 
 * atomic number need the same adjoint photoatomic data. This class allows each
 * adjoint photo-nuclide to share the photoatomic data without copying that 
 * data (even if each adjoint photo-nuclide has its own copy of the adjoint 
 * atom core object).
 */
template<typename _ReactionEnumType,
         typename _ForwardReactionType,
         typename _AdjointReactionType,
         typename _ParticleStateType,
         template<typename,typename,typename...> class MapType = std::unordered_map,
         template<typename,typename...> class SetType = std::unordered_set>
class AdjointAtomCore : public AtomCore<_ReactionEnumType,_AdjointReactionType,_ParticleStateType,MapType,SetType>
{
  // Typedef for base type
  typedef AtomCore<_ReactionEnumType,_AdjointReactionType,_ParticleStateType,MapType,SetType> BaseType;
  
  // Typedef for this type
  typedef AdjointAtomCore<_ReactionEnumType,_ForwardReactionType,_AdjointReactionType,_ParticleStateType,MapType,SetType> ThisType;

public:

  //! Typedef for the reaction type enum
  typedef typename BaseType::ReactionEnumType ReactionEnumType;

  //! Typedef for the reaction type enum set
  typedef typename BaseType::ReactionEnumTypeSet ReactionEnumTypeSet;

  //! Typedef for the reaction type
  typedef typename BaseType::ReactionType ReactionType;

  //! Typedef for the forward reaction type
  typedef _ForwardReactionType ForwardReactionType;

  //! Typedef for the particle state type
  typedef typename BaseType::ParticleStateType ParticleStateType;

  //! Typedef for the reaction map
  typedef typename BaseType::ReactionMap ReactionMap;

  //! Typedef for the const reaction map
  typedef typename BaseType::ConstReactionMap ConstReactionMap;

  //! Typedef for the line energy reaction map
  typedef MapType<double,ReactionMap> LineEnergyReactionMap;

  //! Typedef for the const line energy reaction map
  typedef MapType<double,ConstReactionMap> ConstLineEnergyReactionMap;

  //! Return the total forward reaction
  const ForwardReactionType& getTotalForwardReaction() const;

  //! Return the line energy reactions
  const ConstLineEnergyReactionMap& getLineEnergyReactions() const;

  //! Return the critical line energies
  const std::vector<double>& getCriticalLineEnergies() const;

protected:

  //! Default constructor
  AdjointAtomCore();

  //! Basic constructor
  AdjointAtomCore(
     const std::shared_ptr<const std::vector<double> >& critical_line_energies,
     const std::shared_ptr<const ForwardReactionType>& total_forward_reaction,
     const ConstReactionMap& standard_scattering_reactions,
     const ConstReactionMap& standard_absorption_reactions,
     const ConstLineEnergyReactionMap& line_energy_reactions,
     const std::shared_ptr<const AtomicRelaxationModel>& relaxation_model,
     const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
     grid_searcher );

  //! Advanced constructor
  AdjointAtomCore(
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
     grid_searcher );

  //! Copy constructor
  AdjointAtomCore( const AdjointAtomCore& instance );

  //! Assignment operator
  AdjointAtomCore& operator=( const AdjointAtomCore& instance );

private:

  // Check if the line energy reactions are valid
  bool areLineEnergyReactionsValid(
         const ConstLineEnergyReactionMap& line_energy_reactions,
         const std::vector<double>& critical_line_energies ) const;

  // The total forward reactions
  std::shared_ptr<const ForwardReactionType> d_total_forward_reaction;

  // The line energy reactions
  ConstLineEnergyReactionMap d_line_energy_reactions;

  // The critical line energies
  std::shared_ptr<const std::vector<double> > d_critical_line_energies;
};
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_AdjointAtomCore_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_ADJOINT_ATOM_CORE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointAtomCore.hpp
//---------------------------------------------------------------------------//
