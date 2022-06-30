//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_Nuclide.hpp
//! \author Alex Robinson
//! \brief  The nuclide class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_NUCLIDE_HPP
#define MONTE_CARLO_NUCLIDE_HPP

// Std Lib Includes
#include <memory>
#include <unordered_map>
#include <unordered_set>

// FRENSIE Includes
#include "MonteCarlo_NeutronNuclearReaction.hpp"
#include "Utility_HashBasedGridSearcher.hpp"
#include "Utility_Vector.hpp"
#include "Utility_Set.hpp"
#include "Utility_QuantityTraits.hpp"

namespace MonteCarlo{

/*! The nuclide class
 * \details This is the base class for all nuclides. No unresolved
 * resonance data is stored in this base class.
 */
class Nuclide
{
  // Typedef for QuantityTraits
  typedef Utility::QuantityTraits<double> QT;

public:

  //! The reaction enum type
  typedef NuclearReactionType ReactionEnumType;

  //! The reaction enum set type
  typedef std::set<ReactionEnumType> ReactionEnumTypeSet;

  //! The particle state type
  typedef NeutronState ParticleStateType;

  //! Typedef for the reaction map
  typedef std::unordered_map<NuclearReactionType,std::shared_ptr<NeutronNuclearReaction> > ReactionMap;

  //! Typedef for the const reaction map
  typedef std::unordered_map<NuclearReactionType,std::shared_ptr<NeutronNuclearReaction> >
  ConstReactionMap;

  //! Set the nuclear reaction types that will be considered as absorption
  static void setAbsorptionReactionTypes(
	const std::vector<NuclearReactionType>& absorption_reaction_types );

  //! Add nuclear reaction types that will be considered as absorption
  static void addAbsorptionReactionTypes(
	const std::vector<NuclearReactionType>& absorption_reaction_types );

  //! Create a unique id for the nuclide based on its name
  static unsigned getUniqueIdFromName( const std::string& name );

  //! Constructor
  Nuclide(
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
          const ConstReactionMap& standard_absorption_reactions );

  //! Destructor
  virtual ~Nuclide()
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

  //! Return the atomic weight
  double getAtomicWeight() const;

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

  //! Return the absorption reaction types
  void getAbsorptionReactionTypes( ReactionEnumTypeSet& reaction_types ) const;

  //! Return the scattering reaction types
  void getScatteringReactionTypes( ReactionEnumTypeSet& reaction_types ) const;

  //! Return the miscellaneous reaction types
  void getMiscReactionTypes( ReactionEnumTypeSet& reaction_types ) const;

  //! Return the reaction types
  void getReactionTypes( ReactionEnumTypeSet& reaction_types ) const;

  //! Collide with a neutron
  virtual void collideAnalogue( NeutronState& neutron, ParticleBank& bank ) const;

  //! Collide with a neutron and survival bias
  virtual void collideSurvivalBias( NeutronState& neutron, ParticleBank& bank ) const;

private:

  // Set the default absorption reaction types
  static std::unordered_set<NuclearReactionType>
  setDefaultAbsorptionReactionTypes();

  // Calculate the total absorption cross section
  void calculateTotalAbsorptionReaction(
          const std::shared_ptr<const std::vector<double> >& energy_grid,
          const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
          grid_searcher );

  // Calculate the total cross section
  void calculateTotalReaction(
          const std::shared_ptr<const std::vector<double> >& energy_grid,
          const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
          grid_searcher );

  // Sample an absorption reaction
  void sampleAbsorptionReaction( const double scaled_random_number,
				 NeutronState& neutron,
				 ParticleBank& bank ) const;

  // Sample a scattering reaction
  void sampleScatteringReaction( const double scaled_random_number,
				 NeutronState& neutron,
				 ParticleBank& bank ) const;

  // Reactions that should be treated as absorption
  static std::unordered_set<NuclearReactionType> absorption_reaction_types;

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
  std::unique_ptr<NeutronNuclearReaction> d_total_reaction;

  // The total absorption reaction
  std::unique_ptr<NeutronNuclearReaction> d_total_absorption_reaction;

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
