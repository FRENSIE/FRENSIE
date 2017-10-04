//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_Photoatom.hpp
//! \author Alex Robinson
//! \brief  The photoatom base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHOTOATOM_HPP
#define MONTE_CARLO_PHOTOATOM_HPP

// FRENSIE Includes
#include "MonteCarlo_PhotoatomicReactionType.hpp"
#include "MonteCarlo_PhotonuclearReactionType.hpp"
#include "MonteCarlo_PhotoatomicReaction.hpp"
#include "MonteCarlo_AtomicRelaxationModel.hpp"
#include "MonteCarlo_PhotoatomCore.hpp"
#include "MonteCarlo_Atom.hpp"

namespace MonteCarlo{

//! The atom class for photoatomic reactions
class Photoatom : public Atom<PhotoatomCore>
{

private:

  // Typedef for Teuchos ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Typedef for the reaction map
  typedef PhotoatomCore::ReactionMap ReactionMap;

  //! Typedef for the const reaction map
  typedef PhotoatomCore::ConstReactionMap ConstReactionMap;

  //! Return the reactions that are treated as absorption
  static const boost::unordered_set<PhotoatomicReactionType>&
  getAbsorptionReactionTypes();

  //! Constructor
  template<typename InterpPolicy>
  Photoatom(
	  const std::string& name,
	  const unsigned atomic_number,
	  const double atomic_weight,
	  const Teuchos::ArrayRCP<double>& energy_grid,
	  const Teuchos::RCP<const Utility::HashBasedGridSearcher>&
	  grid_searcher,
	  const ReactionMap& standard_scattering_reactions,
	  const ReactionMap& standard_absorption_reactions,
	  const Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model,
	  const bool processed_atomic_cross_sections,
	  const InterpPolicy policy );

  //! Constructor (from a core)
  Photoatom( const std::string& name,
	     const unsigned atomic_number,
	     const double atomic_weight,
	     const PhotoatomCore& core )
    : Atom<PhotoatomCore>( name, atomic_number, atomic_weight, core )
  { /* ... */ }

  //! Destructor
  virtual ~Photoatom()
  { /* ... */ }

  //! Return if the atom has an atomic relaxation model
  bool hasAtomicRelaxationModel() const;

  //! Return the cross section for a specific photoatomic reaction
  double getReactionCrossSection(
			        const double energy,
			        const PhotoatomicReactionType reaction ) const;

  //! Return the cross section for a specific photonuclear reaction
  virtual double getReactionCrossSection(
			       const double energy,
			       const PhotonuclearReactionType reaction ) const;
};

// Return the cross section for a specific photonuclear reaction
/*! \details By default, photonuclear reactions are not considered.
 */
inline double Photoatom::getReactionCrossSection(
			       const double energy,
			       const PhotonuclearReactionType reaction ) const
{
  return 0.0;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_Photoatom_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_PHOTOATOM_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_Photoatom.hpp
//---------------------------------------------------------------------------//
