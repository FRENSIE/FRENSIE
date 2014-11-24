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
#include "MonteCarlo_PhotonuclearReactionType.hpp"
#include "MonteCarlo_PhotoatomicReaction.hpp"
#include "MonteCarlo_AtomicRelaxationModel.hpp"
#include "MonteCarlo_PhotoatomCore.hpp"

namespace MonteCarlo{

//! The atomic class for photoatomic reactions
class Photoatom
{

private:

  // Typedef for Teuchos ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Typedef for the reaction map
  typedef PhotoatomCore::ReactionMap ReactionMap;

  //! Typedef for the const reaction map
  typedef PhotoatomCore::ConstReactionMap ConstReactionMap;

  //! Return the reactions that are treated as absorption
  static const boost::unordered_set<PhotoatomicReactionType>& 
  getAbsorptionReactionTypes();
					
  //! Constructor 
  template<typename InterpPolicy>
  Photoatom( 
	  const std::string& name,
	  const unsigned atomic_number,
	  const double atomic_weight,
	  const Teuchos::ArrayRCP<double>& energy_grid,
	  const ReactionMap& standard_scattering_reactions,
	  const ReactionMap& standard_absorption_reactions,
	  const Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model,
	  const bool processed_atomic_cross_sections,
	  const InterpPolicy policy );

  //! Constructor (from a core)
  Photoatom( const std::string& name,
	     const unsigned atomic_number,
	     const double atomic_weight,
	     const PhotoatomCore& core );

  //! Destructor
  virtual ~Photoatom()
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

  //! Return the total cross section at the desired energy
  double getTotalCrossSection( const double energy ) const;

  //! Return the total cross section from atomic interactions 
  double getAtomicTotalCrossSection( const double energy ) const;

  //! Return the total cross section from nuclear interactions
  virtual double getNuclearTotalCrossSection( const double energy ) const;

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

  //! Return the cross section for a specific photoatomic reaction
  double getReactionCrossSection( 
			        const double energy,
			        const PhotoatomicReactionType reaction ) const;
  
  //! Return the crosss ection for a specific photonuclear reaction
  virtual double getReactionCrossSection(
			       const double energy,
			       const PhotonuclearReactionType reaction ) const;

  //! Collide with a photon
  virtual void collideAnalogue( PhotonState& photon, 
				ParticleBank& bank ) const;

  //! Collide with a photon and survival bias
  virtual void collideSurvivalBias( PhotonState& photon, 
				    ParticleBank& bank ) const;

  //! Return the core
  const PhotoatomCore& getCore() const;

private:

  // Sample an absorption reaction
  void sampleAbsorptionReaction( const double scaled_random_number,
				 PhotonState& photon,
				 ParticleBank& bank ) const;

  // Sample a scattering reaction
  void sampleScatteringReaction( const double scaled_random_number,
				 PhotonState& photon,
				 ParticleBank& bank ) const;

  // The atom name
  std::string d_name;

  // The atomic number of the atom
  unsigned d_atomic_number;

  // The atomic weight of the atom
  double d_atomic_weight;

  // The photoatom core (storing all reactions, relaxation model)
  PhotoatomCore d_core;
};

// Return the nuclide name
inline const std::string& Photoatom::getNuclideName() const
{
  return this->getAtomName();
}

// Return the atomic mass number
inline unsigned Photoatom::getAtomicMassNumber() const
{
  return 0u;
}

// Return the nuclear isomer number
inline unsigned Photoatom::getIsomerNumber() const
{
  return 0u;
}

// Return the temperature of the atom
/*! \details This information is irrelevant for photoatomic reactions. However,
 * it my be important for photonuclear reactions where Doppler broadening of
 * cross sections may be necessary.
 */ 
inline double Photoatom::getTemperature() const
{
  return 0.0;
}

// Return the total cross section at the desired energy
inline double Photoatom::getTotalCrossSection( const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( energy > 0.0 );
  
  return this->getAtomicTotalCrossSection( energy ) +
    this->getNuclearTotalCrossSection( energy );
}

// Return the total cross section from nuclear interactions
/*! \details By default, photonuclear reactions are not considered.
 */
inline double Photoatom::getNuclearTotalCrossSection( 
						    const double energy ) const
{
  return 0.0;
}

// Return the total absorption cross section at the desired energy
inline double Photoatom::getAbsorptionCrossSection( const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  return this->getAtomicAbsorptionCrossSection( energy ) +
    this->getNuclearAbsorptionCrossSection( energy );
}

// Return the total absorption cross section from nuclear interactions
/*! \details By default, photonuclear reactions are not considered.
 */
inline double 
Photoatom::getNuclearAbsorptionCrossSection( const double energy ) const
{
  return 0.0;
} 

// Return the crosss ection for a specific photonuclear reaction
/*! \details By default, photonuclear reactions are not considered.
 */
inline double Photoatom::getReactionCrossSection(
			       const double energy,
			       const PhotonuclearReactionType reaction ) const
{
  return 0.0;
}

// Return the core
inline const PhotoatomCore& Photoatom::getCore() const
{
  return d_core;
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
