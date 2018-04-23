//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NuclearReactionACEFactory.hpp
//! \author Alex Robinson
//! \brief  Nuclear reaction factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_NUCLEAR_REACTION_ACE_FACTORY_HPP
#define MONTE_CARLO_NUCLEAR_REACTION_ACE_FACTORY_HPP

// Std Lib Includes
#include <memory>

// Boost Includes
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

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
class NuclearReactionACEFactory
{

public:

  //! Constructor
  NuclearReactionACEFactory(
          const std::string& table_name,
          const double atomic_weight_ratio,
          const double temperature,
          const std::shared_ptr<const std::vector<double> >& energy_grid,
          const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
          grid_searcher,
          const SimulationProperties& properties,
          const Data::XSSNeutronDataExtractor& raw_nuclide_data );

  //! Destructor
  virtual ~NuclearReactionACEFactory()
  { /* ... */ }

  //! Create the scattering reactions
  void createScatteringReactions(
      boost::unordered_map<NuclearReactionType,std::shared_ptr<const NeutronNuclearReaction> >&
      scattering_reactions ) const;

  //! Create the absorption reactions
  void createAbsorptionReactions(
      boost::unordered_map<NuclearReactionType,std::shared_ptr<const NeutronNuclearReaction> >&
      absorption_reactions ) const;

  //! Create the fission reactions
  virtual void createFissionReactions(
      boost::unordered_map<NuclearReactionType,std::shared_ptr<const NeutronNuclearReaction> >&
      fission_reactions ) const;

protected:

  //! Create the reaction type ordering map
  static void createReactionOrderingMap(
       const Utility::ArrayView<const double>& mtr_block,
       boost::unordered_map<NuclearReactionType,unsigned>& reaction_ordering );

  //! Create the reaction type Q-value map
  static void createReactionQValueMap(
   const Utility::ArrayView<const double>& lqr_block,
   const boost::unordered_map<NuclearReactionType,unsigned>& reaction_ordering,
   boost::unordered_map<NuclearReactionType,double>& reaction_q_value );

  //! Create the reaction multiplicity map
  static void createReactionMultiplicityMap(
   const std::string& table_name,
   const Utility::ArrayView<const double>& tyr_block,
   const Utility::ArrayView<const double>& dlw_block,
   const boost::unordered_map<NuclearReactionType,unsigned>& reaction_ordering,
   boost::unordered_map<NuclearReactionType,unsigned>&
   reaction_multiplicity,
   boost::unordered_map<NuclearReactionType,Utility::ArrayView<const double> >&
   reaction_energy_dependent_multiplicity );

  //! Create the reaction threshold index map
  static void createReactionThresholdMap(
   const Utility::ArrayView<const double>& lsig_block,
   const Utility::ArrayView<const double>& sig_block,
   const boost::unordered_map<NuclearReactionType,unsigned>& reaction_ordering,
   boost::unordered_map<NuclearReactionType,unsigned>&
   reaction_threshold_index );

  //! Create the reaction cross section map
  static void createReactionCrossSectionMap(
   const Utility::ArrayView<const double>& lsig_block,
   const Utility::ArrayView<const double>& sig_block,
   const Utility::ArrayView<const double>& elastic_cross_section,
   const boost::unordered_map<NuclearReactionType,unsigned>& reaction_ordering,
   boost::unordered_map<NuclearReactionType,std::shared_ptr<std::vector<double> > >&
   reaction_cross_section );

  //! Get the reaction associated with an Reaction Type
  void getReactionFromReactionType(
          NuclearReactionType reaction_type,
          std::shared_ptr<const NeutronNuclearReaction>& base_reaction );

private:

  // Initialize the scattering reactions
  void initializeScatteringReactions(
    const double temperature,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
    grid_searcher,
    const SimulationProperties& properties,
    const boost::unordered_map<NuclearReactionType,double>& reaction_q_value,
    const boost::unordered_map<NuclearReactionType,unsigned>&
    reaction_multiplicity,
    const boost::unordered_map<NuclearReactionType,Utility::ArrayView<const double> >&
    reaction_energy_dependent_multiplicity,
    const boost::unordered_map<NuclearReactionType,unsigned>&
    reaction_threshold_index,
    const boost::unordered_map<NuclearReactionType,std::shared_ptr<std::vector<double> > >&
    reaction_cross_section,
    const NeutronNuclearScatteringDistributionACEFactory& scattering_dist_factory );

  // Initialize the absorption reactions
  void initializeAbsorptionReactions(
    const double temperature,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
    grid_searcher,
    const boost::unordered_map<NuclearReactionType,double>& reaction_q_value,
    const boost::unordered_map<NuclearReactionType,unsigned>&
    reaction_multiplicity,
    const boost::unordered_map<NuclearReactionType,Utility::ArrayView<const double> >&
    reaction_energy_dependent_multiplicity,
    const boost::unordered_map<NuclearReactionType,unsigned>&
    reaction_threshold_index,
    const boost::unordered_map<NuclearReactionType,std::shared_ptr<std::vector<double> > >&
    reaction_cross_section );

  // Initialize the fission reactions
  void initializeFissionReactions(
    const double temperature,
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
    grid_searcher,
    const SimulationProperties& properties,
    const boost::unordered_map<NuclearReactionType,double>& reaction_q_value,
    const boost::unordered_map<NuclearReactionType,unsigned>&
    reaction_multiplicity,
    const boost::unordered_map<NuclearReactionType,unsigned>&
    reaction_threshold_index,
    const boost::unordered_map<NuclearReactionType,std::shared_ptr<std::vector<double> > >&
    reaction_cross_section,
    const NeutronNuclearScatteringDistributionACEFactory& scattering_dist_factory,
    const std::shared_ptr<const FissionNeutronMultiplicityDistribution>&
    fission_neutron_multiplicity_distribution,
    const std::shared_ptr<const NuclearScatteringDistribution<NeutronState,NeutronState> >&
    delayed_neutron_emission_distribution );

  // A map of the scattering reactions
  boost::unordered_map<NuclearReactionType,std::shared_ptr<const NeutronNuclearReaction> >
  d_scattering_reactions;

  // A map of the absorption reactions
  boost::unordered_map<NuclearReactionType,std::shared_ptr<const NeutronNuclearReaction> >
  d_absorption_reactions;

  // A map of the fission reactions
  boost::unordered_map<NuclearReactionType,std::shared_ptr<const NeutronNuclearReaction> >
  d_fission_reactions;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLONUCLEAR_REACTION_ACE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclearReactionACEFactory.hpp
//---------------------------------------------------------------------------//
