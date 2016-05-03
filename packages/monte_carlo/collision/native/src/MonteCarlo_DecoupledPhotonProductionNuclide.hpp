//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DecoupledPhotonProductionNuclide.hpp
//! \author Eli Moll
//! \brief  The decoupled photon production nuclide class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DECOUPLED_PHOTON_PRODUCTION_NUCLIDE_HPP
#define MONTE_CARLO_DECOUPLED_PHOTON_PRODUCTION_NUCLIDE_HPP

// Boost Includes
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <boost/scoped_ptr.hpp>

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
  typedef boost::unordered_map<unsigned,
                   Teuchos::RCP<DecoupledPhotonProductionReaction> > PhotonProductionReactionMap;

  //! Typedef for the reaction map
  typedef boost::unordered_map<unsigned,
                   Teuchos::RCP<const DecoupledPhotonProductionReaction> > ConstPhotonProductionReactionMap;

  //! Constructor
  DecoupledPhotonProductionNuclide( 
     const std::string& name,
	   const unsigned atomic_number,
	   const unsigned atomic_mass_number,
	   const unsigned isomer_number,
	   const double atomic_weight_ratio,
	   const double temperature,
	   const Teuchos::ArrayRCP<double>& energy_grid,
	   const ReactionMap& standard_scattering_reactions,
	   const ReactionMap& standard_absorption_reactions,
	   const PhotonProductionReactionMap& photon_production_reactions );  

  //! Destructor
  ~DecoupledPhotonProductionNuclide()
  { /* ... */ }
  
  //! Get the photon production reaction cross section
  double getPhotonProductionCrossSection( const double energy,
				                                  const unsigned reaction );
  
  //! Collide with a neutron
  void collideAnalogue( NeutronState& neutron, ParticleBank& bank ) const;

  //! Collide with a neutron and survival bias
  void collideSurvivalBias( NeutronState& neutron, ParticleBank& bank ) const;

  // Get total photon production cross section
  double getTotalPhotonProductionCrossSection( const double energy ) const;
  
private:

  // Sample a decoupled photon production reaction
  void samplePhotonProductionReaction( const double scaled_random_number,
				 NeutronState& neutron, 
				 ParticleBank& bank ) const;

  // Store the reaction map of photon production reactions 
  ConstPhotonProductionReactionMap d_photon_production_reactions;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_DECOUPLED_PHOTON_PRODUCTION_NUCLIDE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DecoupledPhotonProductionNuclide.hpp
//---------------------------------------------------------------------------//
