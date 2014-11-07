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
#include <string>

// Boost Includes
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "MonteCarlo_PhotoatomicReactionType.hpp"
#include "MonteCarlo_PhotoatomicReaction.hpp"
#include "MonteCarlo_AtomicRelaxationModel.hpp"

namespace MonteCarlo{

//! The atomic class for photoatomic reactions
class Photoatom
{

private:

  // Typedef for Teuchos ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Typedef for the reaction map
  typedef boost::unordered_map<PhotoatomicReactionType,
			       Teuchos::RCP<PhotoatomicReaction> >
  ReactionMap;

  //! Set the photoatomic reaction types that will be considered as absorption
  static void setAbsorptionReactionTypes(
    const Teuchos::Array<PhotoatomicReactionType>& absorption_reaction_types );
  
  //! Add a photoatomic reaction type that will be considered as absorption
  static void addAbsorptionReactionType( 
				      const PhotoatomicReactionType reaction );

  //! Return the reactions that are treated as absorption
  static const boost::unordered_set<PhotoatomicReactionType>& 
  getAbsorptionReactionTypes();
					
  //! Constructor
  Photoatom( 
	  const std::string& name,
	  const unsigned atomic_number,
	  const ReactionMap& standard_scattering_reactions,
	  const ReactionMap& standard_absorption_reactions,
	  const Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model );

  //! Destructor
  virtual ~Photoatom()
  { /* ... */ }

  //! Return the atom name
  const std::string& getName() const;

  //! Return the atomic number
  unsigned getAtomicNumber() const;

  //! Return the total cross section at the desired energy
  virtual double getTotalCrossSection( const double energy ) const = 0;

  //! Return the total absorption cross section at the desired energy
  virtual double getAbsorptionCrossSection( const double energy ) const = 0;

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

protected:

  //! Return the scattering reactions
  const ReactionMap& getScatteringReactions() const;

  //! Return the absorption reactions
  const ReactionMap& getAbsorptionReactions() const;

private:

  // Set the default absorption reaction types
  static boost::unordered_set<PhotoatomicReactionType>
  setDefaultAbsorptionReactionTypes();

  // Sample an absorption reaction
  void sampleAbsorptionReaction( const double scaled_random_number,
				 PhotonState& photon,
				 ParticleBank& bank ) const;

  // Sample a scattering reaction
  void sampleScatteringReaction( const double scaled_random_number,
				 PhotonState& photon,
				 ParticleBank& bank ) const;

  // Reactions that should be treated as absorption
  static boost::unordered_set<PhotoatomicReactionType> 
  absorption_reaction_types;

  // The atom name
  std::string d_name;

  // The atomic number of the nuclide
  unsigned d_atomic_number;

  // The scattering reactions
  ReactionMap d_scattering_reactions;

  // The absorption reactions
  ReactionMap d_absorption_reactions;

  // Miscellaneous reactions
  ReactionMap d_miscellaneous_reactions;  

  // The atomic relaxation model
  Teuchos::RCP<const AtomicRelaxationModel> d_relaxation_model;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHOTOATOM_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_Photoatom.hpp
//---------------------------------------------------------------------------//
