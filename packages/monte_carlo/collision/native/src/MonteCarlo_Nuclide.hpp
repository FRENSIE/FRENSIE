//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_Nuclide.hpp
//! \author Alex Robinson
//! \brief  The nuclide class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_NUCLIDE_HPP
#define MONTE_CARLO_NUCLIDE_HPP

// Boost Includes
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <boost/scoped_ptr.hpp>

// FRENSIE Includes
#include "MonteCarlo_NuclearReaction.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"

namespace MonteCarlo{

/*! The nuclide class
 * \details This is the base class for all nuclides. No unresolved 
 * resonance data is stored in this base class.
 */
class Nuclide
{

private:

  // Typedef for Teuchos ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Typedef for the reaction map
  typedef boost::unordered_map<NuclearReactionType,
			       Teuchos::RCP<NuclearReaction> > ReactionMap;

  //! Typedef for the const reaction map
  typedef boost::unordered_map<NuclearReactionType,
			       Teuchos::RCP<const NuclearReaction> > 
  ConstReactionMap;

  //! Set the nuclear reaction types that will be considered as absorption
  static void setAbsorptionReactionTypes( 
	const Teuchos::Array<NuclearReactionType>& absorption_reaction_types );

  //! Add nuclear reaction types that will be considered as absorption
  static void addAbsorptionReactionTypes( 
	const Teuchos::Array<NuclearReactionType>& absorption_reaction_types );

  //! Create a unique id for the nuclide based on its name
  static unsigned getUniqueIdFromName( const std::string& name );

  //! Constructor
  Nuclide( const std::string& name,
	   const unsigned atomic_number,
	   const unsigned atomic_mass_number,
	   const unsigned isomer_number,
	   const double atomic_weight_ratio,
	   const double temperature,
	   const Teuchos::ArrayRCP<double>& energy_grid,
	   const ReactionMap& standard_scattering_reactions,
	   const ReactionMap& standard_absorption_reactions );  

  //! Destructor
  ~Nuclide()
  { /* ... */ }

  //! Return the nuclide name
  const std::string& getName() const;

  //! Return the unique id used to refer to this nuclide
  unsigned getId() const;

  //! Return the atomic number of the nuclide
  unsigned getAtomicNumber() const;

  //! Return the atomic mass number of the nuclide
  unsigned getAtomicMassNumber() const;

  //! Return the nuclear isomer number of the nuclide
  unsigned getIsomerNumber() const;
  
  //! Return the atomic weight ratio
  double getAtomicWeightRatio() const;

  //! Return the temperature of the nuclide (in MeV)
  double getTemperature() const;
  
  //! Return the total cross section at the desired energy
  double getTotalCrossSection( const double energy ) const;

  //! Return the total absorption cross section at the desired energy
  double getAbsorptionCrossSection( const double energy ) const;
  
  //! Return the survival probability at the desired energy
  double getSurvivalProbability( const double energy ) const;

  //! Return the cross section for a specific nuclear reaction
  double getReactionCrossSection( const double energy,
				  const NuclearReactionType reaction ) const;

  //! Collide with a neutron
  virtual void collideAnalogue( NeutronState& neutron, ParticleBank& bank ) const;

  //! Collide with a neutron and survival bias
  virtual void collideSurvivalBias( NeutronState& neutron, ParticleBank& bank ) const;

private:

  // Set the default absorption reaction types
  static boost::unordered_set<NuclearReactionType> 
  setDefaultAbsorptionReactionTypes();

  // Calculate the total absorption cross section
  void calculateTotalAbsorptionReaction(
			        const Teuchos::ArrayRCP<double>& energy_grid );

  // Calculate the total cross section
  void calculateTotalReaction( const Teuchos::ArrayRCP<double>& energy_grid );

  // Sample an absorption reaction
  void sampleAbsorptionReaction( const double scaled_random_number,
				 NeutronState& neutron, 
				 ParticleBank& bank ) const;

  // Sample a scattering reaction
  void sampleScatteringReaction( const double scaled_random_number,
				 NeutronState& neutron,
				 ParticleBank& bank ) const;

  // Reactions that should be treated as absorption
  static boost::unordered_set<NuclearReactionType> absorption_reaction_types;

  // The nuclide name
  std::string d_name;

  // The unique id used to refer to this nuclide
  unsigned d_id;

  // The atomic number of the nuclide
  unsigned d_atomic_number;
  
  // The atomic mass number
  unsigned d_atomic_mass_number;

  // The nuclear isomer number
  unsigned d_isomer_number;

  // The weight of the nucleus in neutron masses
  double d_atomic_weight_ratio;
  
  // The temperature of the nuclide (MeV)
  double d_temperature;

  // The total reaction
  boost::scoped_ptr<const NuclearReaction> d_total_reaction;

  // The total absorption reaction
  boost::scoped_ptr<const NuclearReaction> d_total_absorption_reaction;

  // The scattering reactions
  ConstReactionMap d_scattering_reactions;

  // The absorption reactions
  ConstReactionMap d_absorption_reactions;

  // Miscellaneous reactions
  ConstReactionMap d_miscellaneous_reactions;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_NUCLIDE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_Nuclide.hpp
//---------------------------------------------------------------------------//
