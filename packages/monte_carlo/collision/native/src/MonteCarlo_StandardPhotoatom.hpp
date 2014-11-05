//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardPhotoatom.hpp
//! \author Alex Robinson
//! \brief  The standard photoatom class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_PHOTOATOM_HPP
#define MONTE_CARLO_STANDARD_PHOTOATOM_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_PhotoatomicReaction.hpp"
#include "MonteCarlo_AtomicRelaxationModel.hpp"
#include "MonteCarlo_PhotoatomicReactionType.hpp"

namespace MonteCarlo{

//! The standard photoatom class
template<typename InterpPolicy, bool processed_cross_sections>
class StandardPhotatom
{
  
public:
  
  //! Constructor 
  StandardPhotoatom(
	  const std::string& name,
	  const unsigned atomic_number,
	  const Teuchos::ArrayRCP<double>& energy_grid,
	  const boost::unordered_map<PhotoatomicReaction,
	                       Teuchos::RCP<PhotoatomicReaction> >& reactions,
	  const Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model );

  //! Destructor
  ~StandardPhotoatom()
  { /* ... */ }

  //! Return the total cross section at the desired energy
  double getTotalCrossSection( const double energy ) const;

  //! Return the total absorption cross section at the desired energy
  double getTotalAbsorptionCrossSection( const double energy ) const;

  //! Return the survival probability at the desired energy
  double getSurvivalProbability( const double energy ) const;

  //! Return the cross section for a specific photoatomic reaction
  double getReactionCrossSection( 
			        const double energy,
			        const PhotoatomicReactionType reaction ) const;

  //! Collide with a photon
  void collideAnalogue( PhotonState& photon, 
			ParticleBank& bank ) const;

  //! Collide with a photon and survival bias
  void collideSurvivalBias( PhotonState& photon, 
			    ParticleBank& bank ) const;

private:

  // Calculate the total absorption cross section
  void calculateTotalAbsorptionCrossSection();

  // Calculate the total cross section
  void calculateTotalCrossSection();

  // Sample an absorption reaction
  void sampleAbsorptionReaction( const double scaled_random_number,
				 PhotonState& photon,
				 ParticleBank& bank ) const;

  // Sample a scattering reaction
  void sampleScatteringReaction( const double scaled_random_number,
				 PhotonState& photon,
				 ParticleBank& bank ) const;

  // The incoming energy grid
  Teuchos::ArrayRCP<const double> d_energy_grid;

  // The microscopic total cross section
  Teuchos::Array<double> d_total_cross_section;

  // The microscopic absorption cross section
  Teuchos::Array<double> d_absorption_cross_section;

  // The scattering reactions
  boost::unordered_map<PhotoatomicReactionType,
		       Teuchos::RCP<PhotoatomicReaction> >
  d_scattering_reactions;

  // The absorption reactions
  boost::unordered_map<PhotoatomicReactionType,
		       Teuchos::RCP<PhotoatomicReaction> >
  d_absorption_reactions;

  // Miscellaneous reactions
  boost::unordered_map<PhotoatomicReactionType,
		       Teuchos::RCP<PhotoatomicReaction> >
  d_miscellaneous_reactions;  

  // The atomic relaxation model
  Teuchos::RCP<const AtomicRelaxationModel> d_relaxation_model;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_StandardPhotoatom_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_STANDARD_PHOTOATOM_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardPhotoatom.hpp
//---------------------------------------------------------------------------//
