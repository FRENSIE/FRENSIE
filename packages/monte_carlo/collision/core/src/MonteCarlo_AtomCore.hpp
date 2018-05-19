//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AtomCore.hpp
//! \author Alex Robinson
//! \brief  The atom core class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ATOM_CORE_HPP
#define MONTE_CARLO_ATOM_CORE_HPP

// Std Lib Includes
#include <memory>

// Boost Includes
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

// FRENSIE Includes
#include "MonteCarlo_AtomicRelaxationModel.hpp"
#include "Utility_HashBasedGridSearcher.hpp"
#include "Utility_Vector.hpp"
#include "Utility_Map.hpp"
#include "Utility_Set.hpp"

namespace MonteCarlo{

/*! The atom core class
 * \details This class can be used to store all reactions and the atomic
 * relaxation model associated with an atom. Exposing this object (e.g.
 * get method or export method) is safe since it only allows access to
 * the underlying member data in a way that prohibits modification of that
 * data. This class was created to address the issue that arises when dealing
 * with photonuclear data - photo-nuclides that share the same atomic number
 * need the same photoatomic data. This class allows each photo-nuclide to
 * share the photoatomic data without copying that data (even if each
 * photo-nuclide has its own copy of the atom core object).
 */
template<typename _ReactionEnumType,
         typename _ReactionType,
         typename _ParticleStateType,
         template<typename,typename,typename...> class MapType = std::unordered_map,
         template<typename,typename...> class SetType = std::unordered_set>
class AtomCore
{
  // Typedef for this type
  typedef AtomCore<_ReactionEnumType,_ReactionType,_ParticleStateType,MapType,SetType> ThisType;

public:

  //! Typedef for the reaction type enum
  typedef _ReactionEnumType ReactionEnumType;

  //! Typedef for the reaction type enum set
  typedef SetType<ReactionEnumType> ReactionEnumTypeSet;

  //! Typedef for the reaction type
  typedef _ReactionType ReactionType;

  //! Typedef for the particle state type
  typedef _ParticleStateType ParticleStateType;

  //! Typedef for the reaction map
  typedef MapType<ReactionEnumType,std::shared_ptr<ReactionType> > ReactionMap;

  //! Typedef for the const reaction map
  typedef MapType<ReactionEnumType,std::shared_ptr<const ReactionType> > ConstReactionMap;

  //! Destructor
  virtual ~AtomCore()
  { /* ... */ }

  //! Get the reaction types that are treated as absorption
  static const ReactionEnumTypeSet& getAbsorptionReactionTypes();

  //! Return the total reaction
  const ReactionType& getTotalReaction() const;

  //! Return the total absorption reaction
  const ReactionType& getTotalAbsorptionReaction() const;

  //! Return the scattering reactions
  const ConstReactionMap& getScatteringReactions() const;

  //! Return the scattering reaction types
  void getScatteringReactionTypes( ReactionEnumTypeSet& reaction_types ) const;

  //! Return the absorption reactions
  const ConstReactionMap& getAbsorptionReactions() const;

  //! Return the absorption reaction types
  void getAbsorptionReactionTypes( ReactionEnumTypeSet& reaction_types ) const;

  //! Return the miscellaneous reactions
  const ConstReactionMap& getMiscReactions() const;

  //! return the miscellaneous reaction types
  void getMiscReactionTypes( ReactionEnumTypeSet& reaction_types ) const;

  //! Return the reaction types
  void getReactionTypes( ReactionEnumTypeSet& reaction_types ) const;

  //! Return the atomic relaxation model
  const AtomicRelaxationModel& getAtomicRelaxationModel() const;

  //! Return the hash-based grid searcher
  const Utility::HashBasedGridSearcher<double>& getGridSearcher() const;

  //! Test if all of the reactions share a common energy grid
  bool hasSharedEnergyGrid() const;

protected:

  //! Default constructor
  AtomCore();

  //! Basic constructor
  AtomCore(
          const ConstReactionMap& standard_scattering_reactions,
          const ConstReactionMap& standard_absorption_reactions,
          const std::shared_ptr<const AtomicRelaxationModel>& relaxation_model,
          const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
          grid_searcher );

  //! Advanced constructor
  AtomCore(
          const std::shared_ptr<const ReactionType>& total_reaction,
          const std::shared_ptr<const ReactionType>& total_absorption_reaction,
          const ConstReactionMap& scattering_reactions,
          const ConstReactionMap& absorption_reactions,
          const ConstReactionMap& miscellaneous_reactions,
          const std::shared_ptr<const AtomicRelaxationModel> relaxation_model,
          const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
          grid_searcher );

  //! Copy constructor
  AtomCore( const AtomCore& instance );

  //! Assignment operator
  AtomCore& operator=( const AtomCore& instance );

  //! Set the absorption reaction types
  static void setAbsorptionReactionTypes(
                             const ReactionEnumTypeSet& absorption_reactions );

  //! Set the total absorption reaction
  void setTotalAbsorptionReaction( const std::shared_ptr<const ReactionType>& total_absorption_reaction );

  //! Create the total absorption reaction
  template<typename InterpPolicy,
           template<typename,bool> class TotalAbsorptionReactionType>
  void createTotalAbsorptionReaction(
                const std::shared_ptr<const std::vector<double> >& energy_grid,
                const ReactionEnumType total_absorption_reaction_type );

  //! Create the processed total reaction
  template<typename InterpPolicy,
           template<typename,bool> class TotalAbsorptionReactionType>
  void createProcessedTotalAbsorptionReaction(
                const std::shared_ptr<const std::vector<double> >& energy_grid,
                const ReactionEnumType total_absorption_reaction_type );
  
  //! Set the total reaction
  void setTotalReaction( const std::shared_ptr<const ReactionType>& total_reaction );
  
  //! Create the total reaction
  template<typename InterpPolicy,
           template<typename,bool> class TotalReactionType>
  void createTotalReaction(
                const std::shared_ptr<const std::vector<double> >& energy_grid,
                const ReactionEnumType total_reaction_type );

  //! Create the processed total reaction
  template<typename InterpPolicy,
           template<typename,bool> class TotalReactionType>
  void createProcessedTotalReaction(
                const std::shared_ptr<const std::vector<double> >& energy_grid,
                const ReactionEnumType total_reaction_type );
  
private:

  // The reaction types that will be treated as absorption
  static ReactionEnumTypeSet s_absorption_reaction_types;

  // The total reaction
  std::shared_ptr<const ReactionType> d_total_reaction;

  // The total absorption reaction
  std::shared_ptr<const ReactionType> d_total_absorption_reaction;

  // The scattering reactions
  ConstReactionMap d_scattering_reactions;

  // The absorption reactions
  ConstReactionMap d_absorption_reactions;

  // The miscellaneous reactions
  ConstReactionMap d_miscellaneous_reactions;

  // The atomic relaxation model
  std::shared_ptr<const AtomicRelaxationModel> d_relaxation_model;

  // The hash-based grid searcher
  std::shared_ptr<const Utility::HashBasedGridSearcher<double> > d_grid_searcher;
};
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_AtomCore_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_ATOM_CORE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AtomCore.hpp
//---------------------------------------------------------------------------//
