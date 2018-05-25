//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointAtom.hpp
//! \author Alex Robinson
//! \brief  The adjoint atom base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_ATOM_HPP
#define MONTE_CARLO_ADJOINT_ATOM_HPP

// FRENSIE Includes
#include "MonteCarlo_Atom.hpp"

namespace MonteCarlo{

/*! The adjoint atom class
 * \details This class stores the desired core and implements some standard
 * features that are used by adjoint atom classes 
 * (e.g. MonteCarlo::AdjointPhotoatom, MonteCarlo::AdjointElectroatom).
 */
template<typename AtomCore>
class AdjointAtom : public Atom<AtomCore>
{
  // Typedef for QuantityTraits
  typedef Utility::QuantityTraits<double> QT;
  
  // Typedef for the base type
  typedef Atom<AtomCore> BaseType;

public:

  //! The reaction enum type
  typedef typename BaseType::ReactionEnumType ReactionEnumType;

  //! The reaction enum set type
  typedef typename BaseType::ReactionEnumTypeSet ReactionEnumTypeSet;

  //! Typedef for the particle state type
  typedef typename BaseType::ParticleStateType ParticleStateType;

  //! Typedef for the reaction map
  typedef typename BaseType::ReactionMap ReactionMap;

  //! Typedef for the const reaction map
  typedef typename BaseType::ConstReactionMap ConstReactionMap;

  //! Typedef for the line energy reaction map
  typedef typename AtomCore::LineEnergyReactionMap LineEnergyReactionMap;

  //! Typedef for the const line energy reaction map
  typedef typename AtomCore::ConstLineEnergyReactionMap
  ConstLineEnergyReactionMap;

  //! Return the critical line energies
  const std::vector<double>& getCriticalLineEnergies() const;

  //! Check if the energy corresponds to a line energy reaction
  virtual bool doesEnergyHaveLineEnergyReaction( const double energy ) const;

  //! Return the total cross section at the desired line energy
  virtual double getTotalLineEnergyCrossSection( const double energy ) const;

  //! Return the total forward cross section at the desired energy
  double getTotalForwardCrossSection( const double energy ) const;

  //! Return the total forward cross section from atomic interactions
  double getAtomicTotalForwardCrossSection( const double energy ) const;

  //! Return the total forward cross section from nuclear interactions
  virtual double getNuclearTotalForwardCrossSection( const double energy ) const;

  //! Return the adjoint weight factor at the desired energy
  double getAdjointWeightFactor( const double energy ) const;

  //! Return the adjoint weight factor from atomic interactions
  double getAtomicAdjointWeightFactor( const double energy ) const;

  //! Return the adjoint weight factor from nuclear interactions
  double getNuclearAdjointWeightFactor( const double energy ) const;

  //! Return the adjoint line energy weight factor at the desired energy
  virtual double getAdjointLineEnergyWeightFactor( const double energy ) const;

  //! Collide with an adjoint photon at a line energy
  void collideAtLineEnergy( ParticleStateType& adjoint_photon,
                            ParticleBank& bank ) const;

  //! Relax the atom
  void relaxAtom( const Data::SubshellType vacancy_shell,
                  const ParticleStateType& particle,
                  ParticleBank& bank ) const final override;

protected:

  //! Constructors
  using Atom<AtomCore>::Atom;

private:

  // Sample a line energy reaction
  void sampleLineEnergyReaction( const double scaled_random_number,
                                 ParticleStateType& adjoint_photon,
                                 ParticleBank& bank ) const;
};
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_AdjointAtom_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_ADJOINT_ATOM_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointAtom.hpp
//---------------------------------------------------------------------------//
