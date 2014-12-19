//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_Electroatom.hpp
//! \author Luke Kersting
//! \brief  The electroatom base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTROATOM_HPP
#define MONTE_CARLO_ELECTROATOM_HPP

// Std Lib Includes
#include <string>

// Boost Includes
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectroatomicReactionType.hpp"
#include "MonteCarlo_ElectronuclearReactionType.hpp"
#include "MonteCarlo_ElectroatomicReaction.hpp"
#include "MonteCarlo_AtomicRelaxationModel.hpp"
#include "MonteCarlo_ElectroatomCore.hpp"

namespace MonteCarlo{
/*
//! The atom class for electroatomic reactions
class Electroatom
{

private:

  // Typedef for Teuchos ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Typedef for the reaction map
  typedef ElectroatomCore::ReactionMap ReactionMap;

  //! Typedef for the const reaction map
  typedef ElectroatomCore::ConstReactionMap ConstReactionMap;

  //! Return the reactions that are treated as absorption
  static const boost::unordered_set<ElectroatomicReactionType>& 
  getAbsorptionReactionTypes();
					
  //! Constructor 
  template<typename InterpPolicy>
  Electroatom( 
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
  Electroatom( const std::string& name,
	     const unsigned atomic_number,
	     const double atomic_weight,
	     const ElectroatomCore& core );

  //! Destructor
  virtual ~Electroatom()
  { /* ... * }

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

  //! Return the cross section for a specific electroatomic reaction
  double getReactionCrossSection( 
			        const double energy,
			        const ElectroatomicReactionType reaction ) const;
  
  //! Return the cross section for a specific electronuclear reaction
  virtual double getReactionCrossSection(
			       const double energy,
			       const ElectronuclearReactionType reaction ) const;

  //! Collide with a electron
  virtual void collideAnalogue( ElectronState& electron, 
				                ParticleBank& bank ) const;

  //! Collide with a electron and survival bias
  virtual void collideSurvivalBias( ElectronState& electron, 
				                    ParticleBank& bank ) const;

  //! Return the core
  const ElectroatomCore& getCore() const;

private:

  // Sample an absorption reaction
  void sampleAbsorptionReaction( const double scaled_random_number,
				 ElectronState& electron,
				 ParticleBank& bank ) const;

  // Sample a scattering reaction
  void sampleScatteringReaction( const double scaled_random_number,
				 ElectronState& electron,
				 ParticleBank& bank ) const;

  // The atom name
  std::string d_name;

  // The atomic number of the atom
  unsigned d_atomic_number;

  // The atomic weight of the atom
  double d_atomic_weight;

  // The electroatom core (storing all reactions, relaxation model)
  ElectroatomCore d_core;
};

// Return the nuclide name
inline const std::string& Electroatom::getNuclideName() const
{
  return this->getAtomName();
}

// Return the atomic mass number
inline unsigned Electroatom::getAtomicMassNumber() const
{
  return 0u;
}

// Return the nuclear isomer number
inline unsigned Electroatom::getIsomerNumber() const
{
  return 0u;
}

// Return the temperature of the atom
/*! \details This information is irrelevant for electroatomic reactions. However,
 * it my be important for photonuclear reactions where Doppler broadening of
 * cross sections may be necessary.
 *
inline double Electroatom::getTemperature() const
{
  return 0.0;
}

// Return the total cross section at the desired energy
inline double Electroatom::getTotalCrossSection( const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( energy > 0.0 );
  
  return this->getAtomicTotalCrossSection( energy ) +
    this->getNuclearTotalCrossSection( energy );
}

// Return the total cross section from nuclear interactions
/*! \details By default, electronuclear reactions are not considered.
 *
inline double Electroatom::getNuclearTotalCrossSection( 
						    const double energy ) const
{
  return 0.0;
}

// Return the total absorption cross section at the desired energy
inline double Electroatom::getAbsorptionCrossSection( const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( !ST::isnaninf( energy ) );
  testPrecondition( energy > 0.0 );

  return this->getAtomicAbsorptionCrossSection( energy ) +
    this->getNuclearAbsorptionCrossSection( energy );
}

// Return the total absorption cross section from nuclear interactions
/*! \details By default, electronuclear reactions are not considered.
 *
inline double 
Electroatom::getNuclearAbsorptionCrossSection( const double energy ) const
{
  return 0.0;
} 

// Return the cross section for a specific electronuclear reaction
/*! \details By default, electronuclear reactions are not considered.
 *
inline double Electroatom::getReactionCrossSection(
			       const double energy,
			       const ElectronuclearReactionType reaction ) const
{
  return 0.0;
}

// Return the core
inline const ElectroatomCore& Electroatom::getCore() const
{
  return d_core;
}
*/
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_Electroatom_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_ELECTROATOM_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_Electroatom.hpp
//---------------------------------------------------------------------------//

