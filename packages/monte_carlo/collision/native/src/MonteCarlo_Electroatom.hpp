//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_Electroatom.hpp
//! \author Luke Kersting
//! \brief  The electroatom base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTROATOM_HPP
#define MONTE_CARLO_ELECTROATOM_HPP

// FRENSIE Includes
#include "MonteCarlo_ElectroatomicReactionType.hpp"
#include "MonteCarlo_ElectroatomicReaction.hpp"
#include "MonteCarlo_AtomicRelaxationModel.hpp"
#include "MonteCarlo_ElectroatomCore.hpp"
#include "MonteCarlo_Atom.hpp"

namespace MonteCarlo{

//! The atom class for electroatomic reactions
class Electroatom : public Atom<ElectroatomCore>
{

private:

  // Typedef for Teuchos ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Typedef for the reaction map
  typedef ElectroatomCore::ReactionMap ReactionMap;

  //! Typedef for the const reaction map
  typedef ElectroatomCore::ConstReactionMap ConstReactionMap;

  //! Return the reactions that are treated as scattering
  static const boost::unordered_set<ElectroatomicReactionType>&
  getScatteringReactionTypes();

  //! Constructor
  template<typename InterpPolicy>
  Electroatom(
      const std::string& name,
      const unsigned atomic_number,
      const double atomic_weight,
      const Teuchos::ArrayRCP<double>& energy_grid,
      const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
      const ReactionMap& standard_scattering_reactions,
      const ReactionMap& standard_absorption_reactions,
      const Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model,
      const bool processed_cross_sections,
      const InterpPolicy policy );

  //! Constructor (from a core)
  Electroatom( const std::string& name,
               const unsigned atomic_number,
               const double atomic_weight,
               const ElectroatomCore& core )
    : Atom<ElectroatomCore>( name, atomic_number, atomic_weight, core )
  { /* ... */ }

  //! Destructor
  virtual ~Electroatom()
  { /* ... */ }

  //! Return if the atom has an atomic relaxation model
  bool hasAtomicRelaxationModel() const;

  //! Return the cross section for a specific electroatomic reaction
  double getReactionCrossSection(
                    const double energy,
                    const ElectroatomicReactionType reaction ) const;

};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_Electroatom_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_ELECTROATOM_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_Electroatom.hpp
//---------------------------------------------------------------------------//

