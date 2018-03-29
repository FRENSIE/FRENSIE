//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_Photonuclide.hpp
//! \author Alex Robinson
//! \brief  The photo-nuclide base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHOTONUCLIDE_HPP
#define MONTE_CARLO_PHOTONUCLIDE_HPP

// Std Lib Includes
#include <string>
#include <memory>

// Boost Includes
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

// FRENSIE Includes
#include "MonteCarlo_Photoatom.hpp"
#include "MonteCarlo_PhotonuclearReaction.hpp"
#include "Utility_Vector.hpp"
#include "Utility_QuantityTraits.hpp"

namespace MonteCarlo{

//! The nuclide class for photoatomic and photonuclear reactions
class Photonuclide : public Photoatom
{

private:

  // Typedef for QuantityTraits
  typedef Utility::QuantityTraits<double> QT;

public:

  //! Typedef for the reaction map
  typedef boost::unordered_map<PhotonuclearReactionType,
			       std::shared_ptr<PhotonuclearReaction> >
  NuclearReactionMap;

  //! Typedef for the const reaction map
  typedef boost::unordered_map<PhotonuclearReactionType,
			       std::shared_ptr<const PhotonuclearReaction> >
  ConstNuclearReactionMap;

  //! Return the reactions that are treated as absorption
  static const boost::unordered_set<PhotonuclideReactionType>&
  getNuclearAbsorptionReactionTypes();

  //! Constructor
  template<typename AtomicInterpPolicy>
  Photonuclide(
	  const std::string& atom_name,
	  const std::string& nuclide_name,
	  const unsigned atomic_number,
	  const unsigned atomic_mass_number,
	  const unsigned isomer_number,
	  const double temperature,
	  const double atomic_weight,
	  const std::shared_ptr<std::vector<double> >& nuclear_energy_grid,
	  const NuclearReactionMap& standard_nuclear_scattering_reactions,
	  const NuclearReactionMap& standard_nuclear_absorption_reactions,
	  const std::shared_ptr<std::vector<double> >& atomic_energy_grid,
	  const ReactionMap& standard_atomic_scattering_reactions,
	  const ReactionMap& standard_atomic_absorption_reactions,
	  const std::shared_ptr<AtomicRelaxationModel>& atomic_relaxation_model,
	  const bool processed_atomic_cross_sections,
	  const AtomicInterpPolicy policy );

  //! Constructor (from a core)
  Photonuclide(
              const std::string& atom_name,
              const std::string& nuclide_name,
              const unsigned atomic_number,
              const unsigned atomic_mass_number,
              const unsigned isomer_number,
              const double temperature,
              const double atomic_weight,
	      const std::shared_ptr<std::vector<double> >& nuclear_energy_grid,
              const NuclearReactionMap& standard_nuclear_scattering_reactions,
              const NuclearReactionMap& standard_nuclear_absorption_reactions,
              const PhotoatomCore& core );

  //! Destructor
  ~Photonuclide()
  { /* ... */ }

  //! Return the nuclide name
  const std::string& getNuclideName() const;

  //! Return the atomic mass number
  unsigned getAtomicMassNumber() const;

  //! Return the nuclear isomer number
  unsigned getIsomerNumber() const;

  //! Return the temperature of the nuclide
  double getTemperature() const;

  //! Return the total cross section from nuclear interactions
  double getNuclearTotalCrossSection( const double energy ) const;

  //! Return the total absorption cross section from nuclear interactions
  double getNuclearAbsorptionCrossSection( const double energy ) const;

  //! Return the cross section for a specific photonuclear reaction
  double getReactionCrossSection(
			       const double energy
			       const PhotonuclearReactionType reaction ) const;

  //! Collide with a photon
  void collideAnalogue( PhotonState& photon,
			ParticleBank& bank ) const;

  //! Collide with a photon and survival bias
  void collideSurvivalBias( PhotonState& photon,
			    ParticleBank& bank ) const;

private:

  // The nuclide name
  std::string d_nuclide_name;

  // The atomic mass number
  unsigned d_atomic_mass_number;

  // The isomer number
  unsigned d_isomer_number;

  // The temperature (in MeV) of the photo-nuclide
  double d_temperature;

  // The total nuclear reaction
  std::shared_ptr<PhotonuclearReaction> d_total_reaction;

  // The total absorption reaction
  std::shared_ptr<PhotonuclearReaction> d_total_absorption_reaction;

  // The nuclear scattering reactions
  NuclearReactionMap d_scattering_reactions;

  // The nuclear absorption reactions
  NuclearReactionMap d_absorption_reactions;

  // The miscellaneous reactions
  NuclearReactionMap d_miscellaneous_reactions;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHOTONUCLIDE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_Photonuclide.hpp
//---------------------------------------------------------------------------//
