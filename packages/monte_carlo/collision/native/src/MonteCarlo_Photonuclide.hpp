//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_Photonuclide.hpp
//! \author Alex Robinson
//! \brief  The photonuclide class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHOTONUCLIDE_HPP
#define MONTE_CARLO_PHOTONUCLIDE_HPP

// Boost Includes
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "MonteCarlo_PhotonuclearReactionType.hpp"

namespace MonteCarlo{

/*! The photonuclide class
 * \todo implement this class.
 */
class Photonuclide
{

public:

  //! Return the photonuclide name
  const std::string& getName() const;

  //! Return the atomic number of the photonuclide
  unsigned getAtomicNumber() const;

  //! Return the atomic mass number of the photonuclide
  unsigned getAtomicMassNumber() const;

  //! Return the nuclear isomer number of the photonuclide
  unsigned getIsomerNumber() const;
  
  //! Return the atomic weight ratio
  double getAtomicWeightRatio() const;

  //! Return the temperature of the photonuclide (in MeV)
  double getTemperature() const;

  //! Return the total cross section at the desired energy
  double getTotalCrossSection( const double energy ) const;

  //! Return the total absorption cross section at the desired energy
  double getAbsorptionCrossSection( const double energy ) const;
  
  //! Return the survival probability at the desired energy
  double getSurvivalProbability( const double energy ) const;

  //! Return the cross section for a specific photonuclear reaction
  double getReactionCrossSection( const double energy,
				  const PhotonuclearReactionType reaction ) const;

  //! Collide with a photon
  void collideAnalogue( PhotonState& photon, ParticleBank& bank ) const;

  //! Collide with a photon and survival bias
  void collideSurvivalBias( PhotonState& photon, ParticleBank& bank ) const;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHOTONUCLIDE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_Photonuclide.hpp
//---------------------------------------------------------------------------//
