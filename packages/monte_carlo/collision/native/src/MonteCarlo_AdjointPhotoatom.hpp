//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointPhotoatom.hpp
//! \author Alex Robinson
//! \brief  The adjoint photoatom base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ADJOINT_PHOTOATOM_HPP
#define MONTE_CARLO_ADJOINT_PHOTOATOM_HPP

// Std Lib Includes
#include <string> 
#include <unordered_map>
#include <unordered_set>
#include <vector>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>
#include <Teuchos_ArrayRCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_AdjointPhotoatomCore.hpp"

namespace MonteCarlo{

//! The atom class for adjoint photoatomic reactions
class AdjointPhotoatom
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
                    const AdjointPhotoatomCore& core );

  //! Destructor
  virtual ~AdjointPhotoatom()
  { /* ... */ }

  //! Return the atom name
  const std::string& getAtomName() const;

  //! Return the nuclide name
  virtual const std::string& getNuclideName() const;

  //! Return the atomic number
  unsigned getAtomicNumber() const;

  //! Return the atomic mass number
  virtual unsigned getAtomicMassNumber() const;

  //! Return the nuclear isomer number
  virtual unsigned getIsomerNumber() const;

  //! Return the atomic weight
  double getAtomicWeight() const;

  //! Return the temperature of the atom
  virtual double getTemperature() const;

  //! Check if the energy corresponds to a line energy reaction
  virtual bool doesEnergyHaveLineEnergyReaction( const double energy ) const;

  //! Return the total cross section at the desired energy
  double getTotalCrossSection( const double energy ) const;

  //! Return the total cross section from atomic interactions
  double getAtomicTotalCrossSection( const double energy ) const;

  //! Return the total cross section from nuclear interactions
  virtual double getNuclearTotalCrossSection( const double energy ) const;

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

  //! Return the total absorption cross section at the desired energy
  double getAbsorptionCrossSection( const double energy ) const;

  //! Return the total absorption cross section from atomic interactions
  double getAtomicAbsorptionCrossSection( const double energy ) const;

  //! Return the total absorption cross section from nuclear interactions
  virtual double getNuclearAbsorptionCrossSection( const double energy ) const;

  //! Return the survival probability at the desired energy
  double getSurvivalProbability( const double energy ) const;

  //! Return the survival probability from atomic interactions
  double getAtomicSurvivalProbability( const double energy ) const;

  //! Return the survival probability from nuclear interactions
  double getNuclearSurvivalProbability( const double energy ) const;

  //! Return the cross section for a specific adjoint photoatomic reaction
  double getReactionCrossSection(
                         const double energy,
                         const AdjointPhotoatomicReactionType reaction ) const;

  //! Return the cross section for a specific photonuclear reaction
  // double getReactionCrossSection(
  //                       const double energy,
  //                       const AdjointPhotonuclearReactionType reaction ) const;

  //! Collide with an adjoint photon
  virtual void collideAnalogue( AdjointPhotonState& adjoint_photon,
                                ParticleBank& bank ) const;

  //! Collide with an adjoint photon and survival bias
  virtual void collideSurvivalBias( AdjointPhotonState& adjoint_photon,
                                    ParticleBank& bank ) const;

  //! Collide with an adjoint photon at a line energy
  virtual void collideAtLineEnergy( AdjointPhotonState& adjoint_photon,
                                    ParticleBank& bank ) const;

  //! Return the core
  const AdjointPhotoatomCore& getCore() const;

private:

  // Return the scatt. cross section from atomic interactions with a bin index
  double getAtomicScatteringCrossSection(
                                        const double energy,
                                        const unsigned energy_grid_bin ) const;

  // Return the abs. cross section from atomic interactions with a bin index
  double getAtomicAbsorptionCrossSection(
                                        const double energy,
                                        const unsigned energy_grid_bin ) const;

  // Sample an absorption reaction
  void sampleAbsorptionReaction( const double scaled_random_number,
                                 const unsigned energy_grid_bin,
                                 AdjointPhotonState& adjoint_photon,
                                 ParticleBank& bank ) const;

  // Sample a scattering reaction
  void sampleScatteringReaction( const double scaled_random_number,
                                 const unsigned energy_grid_bin,
                                 AdjointPhotonState& adjoint_photon,
                                 ParticleBank& bank ) const;

  // Sample a line energy reaction
  void sampleLineEnergyReaction( const double scaled_random_number,
                                 AdjointPhotonState& adjoint_photon,
                                 ParticleBank& bank ) const;
  
  // The atom name
  std::string d_name;

  // The atomic number of the atom
  unsigned d_atomic_number;

  // The atomic weight of the atom
  double d_atomic_weight;

  // The adjoint photoatom core( storing all reactions)
  AdjointPhotoatomCore d_core;
};

// Return the nuclide name
inline const std::string& AdjointPhotoatom::getNuclideName() const
{
  return this->getAtomName();
}

// Return the atomic mass number
inline unsigned AdjointPhotoatom::getAtomicMassNumber() const
{
  return 0u;
}

// Return the nuclear isomer number
inline unsigned AdjointPhotoatom::getIsomerNumber() const
{
  return 0u;
}

// Return the temperature of the atom
/*! \details This information is irrelevant for photoatomic reactions. However,
 * it my be important for photonuclear reactions where Doppler broadening of
 * cross sections may be necessary.
 */
inline double AdjointPhotoatom::getTemperature() const
{
  return 0.0;
}

// Return the total cross section at the desired energy
inline double AdjointPhotoatom::getTotalCrossSection( const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( energy > 0.0 );

  return this->getAtomicTotalCrossSection( energy ) +
    this->getNuclearTotalCrossSection( energy );
}

// Return the total cross section from nuclear interactions
/*! \details By default, adjoint photonuclear reactions are not considered.
 */
inline double AdjointPhotoatom::getNuclearTotalCrossSection(
						    const double energy ) const
{
  return 0.0;
}

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

// Return the total absorption cross section at the desired energy
inline double AdjointPhotoatom::getAbsorptionCrossSection(
                                                    const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( energy > 0.0 );

  return this->getAtomicAbsorptionCrossSection( energy ) +
    this->getNuclearAbsorptionCrossSection( energy );
}

// Return the total absorption cross section from nuclear interactions
/*! \details By default, adjoint photonuclear reactions are not considered.
 */
inline double AdjointPhotoatom::getNuclearAbsorptionCrossSection(
                                                    const double energy ) const
{
  return 0.0;
}

// Return the core
inline const AdjointPhotoatomCore& AdjointPhotoatom::getCore() const
{
  return d_core;
}

// Return the scatt. cross section from atomic interactions with a bin index
inline double AdjointPhotoatom::getAtomicScatteringCrossSection(
                                         const double energy,
                                         const unsigned energy_grid_bin ) const
{
  double cross_section = 0.0;

  ConstReactionMap::const_iterator adjoint_photoatomic_reaction =
    d_core.getScatteringReactions().begin();

  while( adjoint_photoatomic_reaction != d_core.getScatteringReactions().end() )
  {
    cross_section +=
      adjoint_photoatomic_reaction->second->getCrossSection( energy, energy_grid_bin );

    ++adjoint_photoatomic_reaction;
  }

  return cross_section;
}

// Return the abs. cross section from atomic interactions with a bin index
inline double AdjointPhotoatom::getAtomicAbsorptionCrossSection(
                                         const double energy,
                                         const unsigned energy_grid_bin ) const
{
  double cross_section = 0.0;

  ConstReactionMap::const_iterator adjoint_photoatomic_reaction =
    d_core.getAbsorptionReactions().begin();

  while( adjoint_photoatomic_reaction != d_core.getAbsorptionReactions().end() )
  {
    cross_section +=
      adjoint_photoatomic_reaction->second->getCrossSection( energy, energy_grid_bin );

    ++adjoint_photoatomic_reaction;
  }

  return cross_section;
}
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ADJOINT_PHOTOATOM_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AdjointPhotoatom.hpp
//---------------------------------------------------------------------------//
