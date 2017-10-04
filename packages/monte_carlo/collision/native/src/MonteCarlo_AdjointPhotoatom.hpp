//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointPhotoatom.hpp
//! \author Alex Robinson
//! \brief  The adjoint photoatom base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_PHOTOATOM_HPP
#define MONTE_CARLO_ADJOINT_PHOTOATOM_HPP

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotoatomCore.hpp"
#include "MonteCarlo_Atom.hpp"

namespace MonteCarlo{

//! The atom class for adjoint photoatomic reactions
class AdjointPhotoatom : public Atom<AdjointPhotoatomCore>
{

private:

  // Typedef for Teuchos ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Typedef for the reaction map
  typedef AdjointPhotoatomCore::ReactionMap ReactionMap;

  //! Typedef for the const reaction map
  typedef AdjointPhotoatomCore::ConstReactionMap ConstReactionMap;

  //! Typedef for the line energy reaction map
  typedef AdjointPhotoatomCore::LineEnergyReactionMap LineEnergyReactionMap;

  //! Typedef for the const line energy reaction map
  typedef AdjointPhotoatomCore::ConstLineEnergyReactionMap
  ConstLineEnergyReactionMap;

  //! Constructor
  AdjointPhotoatom( const std::string& name,
                    const unsigned atomic_number,
                    const double atomic_weight,
                    const Teuchos::RCP<const Utility::HashBasedGridSearcher>&
                    grid_searcher,
                    const Teuchos::ArrayRCP<const double>&
                    critical_line_energies,
                    const std::shared_ptr<const PhotoatomicReaction>&
                    total_forward_reaction,
                    const ReactionMap& scattering_reactions,
                    const ReactionMap& absorption_reactions,
                    const LineEnergyReactionMap& line_energy_reactions );

  //! Constructor (from a core)
  AdjointPhotoatom( const std::string& name,
                    const unsigned atomic_number,
                    const double atomic_weight,
                    const AdjointPhotoatomCore& core )
    : Atom<AdjointPhotoatomCore>( name, atomic_number, atomic_weight, core )
  { /* ... */ }

  //! Destructor
  virtual ~AdjointPhotoatom()
  { /* ... */ }

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

  //! Return the cross section for a specific adjoint photoatomic reaction
  double getReactionCrossSection(
                         const double energy,
                         const AdjointPhotoatomicReactionType reaction ) const;

  //! Collide with an adjoint photon at a line energy
  virtual void collideAtLineEnergy( AdjointPhotonState& adjoint_photon,
                                    ParticleBank& bank ) const;

private:

  // Sample a line energy reaction
  void sampleLineEnergyReaction( const double scaled_random_number,
                                 AdjointPhotonState& adjoint_photon,
                                 ParticleBank& bank ) const;
};

// Return the total forward cross section at the desired energy
inline double AdjointPhotoatom::getTotalForwardCrossSection(
                                                    const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( energy > 0.0 );

  return this->getAtomicTotalForwardCrossSection( energy ) +
         this->getNuclearTotalCrossSection( energy );
}

// Return the total forward cross section from nuclear interactions
/*! \details By default, adjoint photonuclear reactions are not considered.
 */
inline double AdjointPhotoatom::getNuclearTotalForwardCrossSection(
                                                    const double energy ) const
{
  return 0.0;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ADJOINT_PHOTOATOM_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointPhotoatom.hpp
//---------------------------------------------------------------------------//
