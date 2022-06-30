//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NeutronNuclearReactionACEFactory.hpp
//! \author Alex Robinson
//! \brief  Neutron nuclear reaction factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_NEUTRON_NUCLEAR_REACTION_ACE_FACTORY_HPP
#define MONTE_CARLO_NEUTRON_NUCLEAR_REACTION_ACE_FACTORY_HPP

// Std Lib Includes
#include <memory>
#include <unordered_map>
#include <unordered_set>

// FRENSIE Includes
#include "MonteCarlo_NeutronNuclearReaction.hpp"
#include "MonteCarlo_NuclearReactionType.hpp"
#include "MonteCarlo_NeutronNuclearScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_FissionNeutronMultiplicityDistribution.hpp"
#include "MonteCarlo_SimulationNeutronProperties.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"
#include "Utility_HashBasedGridSearcher.hpp"
#include "Utility_ArrayView.hpp"
#include "Utility_Vector.hpp"

namespace MonteCarlo{

/*! The nuclear reaction factory class
 * \details This factory class stores all of the data blocks found in the
 * ACE tables that describe specific reactions (except for fission reactions).
 * The array parameters used in the class constructor have the same name as
 * the corresponding ACE data block.
 */
class NeutronNuclearReactionACEFactory
{

public:

  //! Constructor
  NeutronNuclearReactionACEFactory(
          const std::string& table_name,
          const double atomic_weight_ratio,
          const double temperature,
          const std::shared_ptr<const std::vector<double> >& energy_grid,
          const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
          grid_searcher,
          const SimulationProperties& properties,
          const Data::XSSNeutronDataExtractor& raw_nuclide_data );

  //! Destructor
  virtual ~NeutronNuclearReactionACEFactory()
  { /* ... */ }

  //! Create the scattering reactions
  void createScatteringReactions(
      std::unordered_map<NuclearReactionType,std::shared_ptr<NeutronNuclearReaction> >&
      scattering_reactions ) const;

  //! Create the absorption reactions
  void createAbsorptionReactions(
      std::unordered_map<NuclearReactionType,std::shared_ptr<NeutronNuclearReaction> >&
      absorption_reactions ) const;

  //! Create the fission reactions
  virtual void createFissionReactions(
      std::unordered_map<NuclearReactionType,std::shared_ptr<NeutronNuclearReaction> >&
      fission_reactions ) const;



protected:

  //! Create the reaction type ordering map
  static void createReactionOrderingMap(
       const Utility::ArrayView<const double>& mtr_block,
       std::unordered_map<NuclearReactionType,unsigned>& reaction_ordering );

  //! Create the reaction type Q-value map
  static void createReactionQValueMap(
   const Utility::ArrayView<const double>& lqr_block,
   const std::unordered_map<NuclearReactionType,unsigned>& reaction_ordering,
   std::unordered_map<NuclearReactionType,double>& reaction_q_value );

  //! Create the reaction multiplicity map
  static void createReactionMultiplicityMap(
   const std::string& table_name,
   const Utility::ArrayView<const double>& tyr_block,
   const Utility::ArrayView<const double>& dlw_block,
   const std::unordered_map<NuclearReactionType,unsigned>& reaction_ordering,
   std::unordered_map<NuclearReactionType,unsigned>& reaction_multiplicity,
   std::unordered_map<NuclearReactionType,Utility::ArrayView<const double> >&
   reaction_energy_dependent_multiplicity );

  //! Create the reaction threshold index map
  static void createReactionThresholdMap(
   const Utility::ArrayView<const double>& lsig_block,
   const Utility::ArrayView<const double>& sig_block,
   const std::unordered_map<NuclearReactionType,unsigned>& reaction_ordering,
   std::unordered_map<NuclearReactionType,unsigned>&
   reaction_threshold_index );

  //! Create the reaction cross section map
  static void createReactionCrossSectionMap(
   const Utility::ArrayView<const double>& lsig_block,
   const Utility::ArrayView<const double>& sig_block,
   const Utility::ArrayView<const double>& elastic_cross_section,
   const std::unordered_map<NuclearReactionType,unsigned>& reaction_ordering,
   std::unordered_map<NuclearReactionType,std::shared_ptr<std::vector<double> > >&
   reaction_cross_section );

  //! Get the reaction associated with an Reaction Type
  void getReactionFromReactionType(
          NuclearReactionType reaction_type,
          std::shared_ptr< NeutronNuclearReaction>& base_reaction );


  // A map of the scattering reactions
  std::unordered_map<NuclearReactionType,std::shared_ptr<NeutronNuclearReaction> >
  d_scattering_reactions;

  // A map of the absorption reactions
  std::unordered_map<NuclearReactionType,std::shared_ptr<NeutronNuclearReaction> >
  d_absorption_reactions;

  // A map of the fission reactions
  std::unordered_map<NuclearReactionType,std::shared_ptr<NeutronNuclearReaction> >
  d_fission_reactions;


private:

  // Initialize the scattering reactions
  void initializeScatteringReactions(
    const double temperature,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
    grid_searcher,
    const SimulationProperties& properties,
    const std::unordered_map<NuclearReactionType,double>& reaction_q_value,
    const std::unordered_map<NuclearReactionType,unsigned>&
    reaction_multiplicity,
    const std::unordered_map<NuclearReactionType,Utility::ArrayView<const double> >&
    reaction_energy_dependent_multiplicity,
    const std::unordered_map<NuclearReactionType,unsigned>&
    reaction_threshold_index,
    const std::unordered_map<NuclearReactionType,std::shared_ptr<std::vector<double> > >&
    reaction_cross_section,
    const NeutronNuclearScatteringDistributionACEFactory& scattering_dist_factory );

  // Initialize the absorption reactions
  void initializeAbsorptionReactions(
    const double temperature,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
    grid_searcher,
    const std::unordered_map<NuclearReactionType,double>& reaction_q_value,
    const std::unordered_map<NuclearReactionType,unsigned>&
    reaction_multiplicity,
    const std::unordered_map<NuclearReactionType,Utility::ArrayView<const double> >&
    reaction_energy_dependent_multiplicity,
    const std::unordered_map<NuclearReactionType,unsigned>&
    reaction_threshold_index,
    const std::unordered_map<NuclearReactionType,std::shared_ptr<std::vector<double> > >&
    reaction_cross_section );

  // Initialize the fission reactions
  void initializeFissionReactions(
    const double temperature,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
    grid_searcher,
    const SimulationProperties& properties,
    const std::unordered_map<NuclearReactionType,double>& reaction_q_value,
    const std::unordered_map<NuclearReactionType,unsigned>&
    reaction_multiplicity,
    const std::unordered_map<NuclearReactionType,unsigned>&
    reaction_threshold_index,
    const std::unordered_map<NuclearReactionType,std::shared_ptr<std::vector<double> > >&
    reaction_cross_section,
    const NeutronNuclearScatteringDistributionACEFactory& scattering_dist_factory,
    const std::shared_ptr<const FissionNeutronMultiplicityDistribution>&
    fission_neutron_multiplicity_distribution,
    const std::shared_ptr<const NuclearScatteringDistribution<NeutronState,NeutronState> >&
    delayed_neutron_emission_distribution );

};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_NEUTRON_NUCLEAR_REACTION_ACE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_NeutronNuclearReactionACEFactory.hpp
//---------------------------------------------------------------------------//
