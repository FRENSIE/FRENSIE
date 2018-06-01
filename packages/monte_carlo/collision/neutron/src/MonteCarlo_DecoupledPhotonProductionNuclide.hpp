//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DecoupledPhotonProductionNuclide.hpp
//! \author Eli Moll
//! \brief  The decoupled photon production nuclide class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DECOUPLED_PHOTON_PRODUCTION_NUCLIDE_HPP
#define MONTE_CARLO_DECOUPLED_PHOTON_PRODUCTION_NUCLIDE_HPP

// Std Includes
#include <unordered_map>
#include <unordered_set>

// FRENSIE Includes
#include "MonteCarlo_DecoupledPhotonProductionReaction.hpp"
#include "MonteCarlo_Nuclide.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"

namespace MonteCarlo{

/*! The decoupled photon production reaction class
 * \details This is the derived class for the decoupled photon production
 * nuclides. No unresolved resonance data is stored in this base class.
 */
class DecoupledPhotonProductionNuclide : public Nuclide
{

public:

  //! Typedef for the reaction map
  typedef std::unordered_map<unsigned,std::shared_ptr<DecoupledPhotonProductionReaction> > PhotonProductionReactionMap;

  //! Typedef for the reaction map
  typedef std::unordered_map<unsigned,std::shared_ptr<const DecoupledPhotonProductionReaction> > ConstPhotonProductionReactionMap;

  //! Constructor
  DecoupledPhotonProductionNuclide(
     const std::string& name,
     const unsigned atomic_number,
     const unsigned atomic_mass_number,
     const unsigned isomer_number,
     const double atomic_weight_ratio,
     const double temperature,
     const std::shared_ptr<const std::vector<double> >& energy_grid,
     const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
     grid_searcher,
     const ConstReactionMap& standard_scattering_reactions,
     const ConstReactionMap& standard_absorption_reactions,
     const ConstPhotonProductionReactionMap& photon_production_reactions );

  //! Destructor
  ~DecoupledPhotonProductionNuclide()
  { /* ... */ }

  //! Get the photon production reaction cross section
  double getPhotonProductionCrossSection( const double energy,
                                          const unsigned reaction );

  //! Collide with a neutron
  void collideAnalogue( NeutronState& neutron, ParticleBank& bank ) const override;

  //! Collide with a neutron and survival bias
  void collideSurvivalBias( NeutronState& neutron, ParticleBank& bank ) const override;

  // Get total photon production cross section
  double getTotalPhotonProductionCrossSection( const double energy ) const;

private:

  // Sample a decoupled photon production reaction
  void samplePhotonProductionReaction( const NeutronState& neutron,
                                       ParticleBank& bank ) const;

  // Store the reaction map of photon production reactions
  ConstPhotonProductionReactionMap d_photon_production_reactions;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_DECOUPLED_PHOTON_PRODUCTION_NUCLIDE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DecoupledPhotonProductionNuclide.hpp
//---------------------------------------------------------------------------//
