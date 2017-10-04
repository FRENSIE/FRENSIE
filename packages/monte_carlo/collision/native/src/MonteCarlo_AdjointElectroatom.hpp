//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectroatom.hpp
//! \author Luke Kersting
//! \brief  The adjoint electroatom base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_ELECTROATOM_HPP
#define MONTE_CARLO_ADJOINT_ELECTROATOM_HPP

// FRENSIE Includes
#include "MonteCarlo_AdjointElectroatomCore.hpp"
#include "MonteCarlo_Atom.hpp"

namespace MonteCarlo{

//! The atom class for adjoint electroatomic reactions
class AdjointElectroatom : public Atom<AdjointElectroatomCore>
{

private:

  // Typedef for Teuchos ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Typedef for the reaction map
  typedef AdjointElectroatomCore::ReactionMap ReactionMap;

  //! Typedef for the const reaction map
  typedef AdjointElectroatomCore::ConstReactionMap ConstReactionMap;

  //! Constructor
  AdjointElectroatom(
    const std::string& name,
    const unsigned atomic_number,
    const double atomic_weight,
    const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
    const std::shared_ptr<const ElectroatomicReaction>& total_forward_reaction,
    const ReactionMap& scattering_reactions,
    const ReactionMap& absorption_reactions );

  //! Constructor (from a core)
  AdjointElectroatom( const std::string& name,
                      const unsigned atomic_number,
                      const double atomic_weight,
                      const AdjointElectroatomCore& core )
    : Atom<AdjointElectroatomCore>( name, atomic_number, atomic_weight, core )
  { /* ... */ }

  //! Destructor
  virtual ~AdjointElectroatom()
  { /* ... */ }

  //! Return the total forward cross section at the desired energy
  double getTotalForwardCrossSection( const double energy ) const;

  //! Return the adjoint weight factor at the desired energy
  double getAdjointWeightFactor( const double energy ) const;

  // //! Return the cross section for a specific adjoint electroatomic reaction
  double getReactionCrossSection(
                    const double energy,
                    const AdjointElectroatomicReactionType reaction ) const;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ADJOINT_ELECTROATOM_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointElectroatom.hpp
//---------------------------------------------------------------------------//

