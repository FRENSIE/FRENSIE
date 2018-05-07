//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_Photoatom.hpp
//! \author Alex Robinson
//! \brief  The photoatom base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHOTOATOM_HPP
#define MONTE_CARLO_PHOTOATOM_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_PhotoatomicReactionType.hpp"
#include "MonteCarlo_PhotonuclearReactionType.hpp"
#include "MonteCarlo_PhotoatomicReaction.hpp"
#include "MonteCarlo_AtomicRelaxationModel.hpp"
#include "MonteCarlo_PhotoatomCore.hpp"
#include "MonteCarlo_Atom.hpp"
#include "Utility_Vector.hpp"
#include "Utility_QuantityTraits.hpp"

namespace MonteCarlo{

//! The atom class for photoatomic reactions
class Photoatom : public Atom<PhotoatomCore>
{
  // Typedef for QuantityTraits
  typedef Utility::QuantityTraits<double> QT;

  // Typedef for the base type
  typedef Atom<PhotoatomCore> BaseType;

public:

  //! The reaction enum type
  typedef BaseType::ReactionEnumType ReactionEnumType;

  //! The particle state type
  typedef BaseType::ParticleStateType ParticleStateType;

  //! Typedef for the reaction map
  typedef BaseType::ReactionMap ReactionMap;

  //! Typedef for the const reaction map
  typedef BaseType::ConstReactionMap ConstReactionMap;

  //! Return the reactions that are treated as absorption
  static const std::unordered_set<PhotoatomicReactionType>&
  getAbsorptionReactionTypes();

  //! Constructor
  template<typename InterpPolicy>
  Photoatom(
	 const std::string& name,
         const unsigned atomic_number,
         const double atomic_weight,
         const std::shared_ptr<const std::vector<double> >& energy_grid,
         const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
         grid_searcher,
         const ConstReactionMap& standard_scattering_reactions,
         const ConstReactionMap& standard_absorption_reactions,
	 const std::shared_ptr<const AtomicRelaxationModel>&
         atomic_relaxation_model,
         const bool processed_atomic_cross_sections,
         const InterpPolicy policy );

  //! Constructor (from a core)
  Photoatom( const std::string& name,
	     const unsigned atomic_number,
	     const double atomic_weight,
	     const PhotoatomCore& core )
    : BaseType( name, atomic_number, atomic_weight, core )
  { /* ... */ }

  //! Destructor
  virtual ~Photoatom()
  { /* ... */ }

  //! Relax the atom
  void relaxAtom( const Data::SubshellType vacancy_shell,
                  const PhotonState& photon,
                  ParticleBank& bank ) const final override;

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

// Relax the atom
inline void Photoatom::relaxAtom( const Data::SubshellType vacancy_shell,
                                  const PhotonState& photon,
                                  ParticleBank& bank ) const
{
  // Relax the atom
  this->getCore().getAtomicRelaxationModel().relaxAtom( vacancy_shell,
                                                        photon,
                                                        bank );
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
