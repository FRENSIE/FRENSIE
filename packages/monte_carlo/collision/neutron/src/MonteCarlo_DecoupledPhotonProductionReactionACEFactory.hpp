//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DecoupledPhotonProductionReactionACEFactory.hpp
//! \author Eli Moll
//! \brief  Decoupled photon production reaction factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DECOUPLED_PHOTON_PRODUCTION_REACTION_ACE_FACTORY_HPP
#define MONTE_CARLO_DECOUPLED_PHOTON_PRODUCTION_REACTION_ACE_FACTORY_HPP

// Standard Includes
#include <memory>
#include <unordered_map>
#include <unordered_set>

// FRENSIE Includes
#include "MonteCarlo_DecoupledPhotonProductionReaction.hpp"
#include "MonteCarlo_PhotonProductionNuclearScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_NeutronNuclearReactionACEFactory.hpp"
#include "MonteCarlo_NuclearReactionType.hpp"
#include "Utility_UnivariateDistribution.hpp"
#include "Utility_HashBasedGridSearcher.hpp"
#include "Utility_ArrayView.hpp"
#include "Utility_Vector.hpp"

namespace MonteCarlo{

/*! The decoupled photon production reaction factory class
 * \details This factory class stores all of the data blocks found in the
 * ACE tables that describe specific reactions (except for fission reactions).
 * The array parameters used in the class constructor have the same name as
 * the corresponding ACE data block.
 */
class DecoupledPhotonProductionReactionACEFactory : public NeutronNuclearReactionACEFactory
{

public:

  //! Constructor
  DecoupledPhotonProductionReactionACEFactory(
          const std::string& table_name,
          const double atomic_weight_ratio,
          const double temperature,
          const std::shared_ptr<const std::vector<double> >& energy_grid,
          const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
          grid_searcher,
          const SimulationProperties& properties,
          const Data::XSSNeutronDataExtractor& raw_nuclide_data );

  //! Destructor
  ~DecoupledPhotonProductionReactionACEFactory()
  { /* ... */ }

  //! Create the yield based photon production reactions
  void createPhotonProductionReactions(
      std::unordered_map<unsigned,std::shared_ptr<const DecoupledPhotonProductionReaction> >&
      yield_based_photon_production_reactions ) const;

protected:

  //! Create the reaction type ordering map
  static void createReactionOrderingMap(
       const Utility::ArrayView<const double>& mtrp_block,
       std::unordered_map<unsigned,unsigned>& reaction_ordering );

  //! Create the total reaction
  void createTotalReaction(
          const Utility::ArrayView<const double>& total_xs_block,
          const std::shared_ptr<const std::vector<double> >& energy_grid,
          const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
          grid_searcher,
          const double temperature );

  //! Parse the SIGP Block
  static void parseSIGP(
    const std::string& table_name,
    const size_t energy_grid_size,
    const Utility::ArrayView<const double>& lsigp_block,
    const Utility::ArrayView<const double>& sigp_block,
    const std::unordered_map<unsigned,unsigned>& reaction_ordering,
    std::unordered_map<unsigned,Utility::ArrayView<const double> >& yield_energy_map,
    std::unordered_map<unsigned,Utility::ArrayView<const double> >& yield_values_map,
    std::unordered_map<unsigned,std::shared_ptr<std::vector<double> > >& xs_based_map,
    std::unordered_map<unsigned,unsigned>& threshold_energy_map,
    std::unordered_map<unsigned,NuclearReactionType>& base_reaction_type_map );

  //! Construct the base reaction map
  void constructBaseReactionMap(
  std::unordered_map<unsigned,NuclearReactionType>& base_reaction_type_map,
  std::unordered_map<NuclearReactionType,std::shared_ptr<NeutronNuclearReaction> >& base_reaction_map,
  std::unordered_map<unsigned,Utility::ArrayView<const double> >& yield_energy_map  );

  // Construct a map of photon MT numbers to yield distributions
  void constructMTPYieldDistributions(
	  const std::unordered_map<unsigned,Utility::ArrayView<const double> >& yield_energy_map,
	  const std::unordered_map<unsigned,Utility::ArrayView<const double> >& yield_values_map );

  // Construct a map of base reaction types to yield distribution arrays
  void constructMTYieldArrays(
    const std::unordered_map<unsigned,NuclearReactionType>& base_reaction_type_map,
    const std::unordered_map<unsigned,Utility::ArrayView<const double> >& yield_energy_map );

private:

  // Initialize the yield based photon production reactions
  void initializeYieldBasedPhotonProductionReactions(
       const std::unordered_map<unsigned,NuclearReactionType>& base_reaction_type_map,
       const double temperature,
       const std::unordered_map<unsigned,Utility::ArrayView<const double> >& yield_energy_map,
       const std::unordered_map<NuclearReactionType,std::shared_ptr<NeutronNuclearReaction> >& base_reaction_map,
       const SimulationProperties& properties,
       PhotonProductionNuclearScatteringDistributionACEFactory& photon_production_dist_factory );

  // Initialize the yield based photon production reactions
  void initializeCrossSectionBasedPhotonProductionReactions(
       const std::unordered_map<unsigned,NuclearReactionType>& base_reaction_type_map,
       const double temperature,
       const std::unordered_map<unsigned,unsigned>& threshold_energy_map,
       const std::unordered_map<unsigned,std::shared_ptr<std::vector<double> > >& xs_based_map,
       const std::shared_ptr<const std::vector<double> >& energy_grid,
       const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
       grid_searcher,
       const SimulationProperties& properties,
       PhotonProductionNuclearScatteringDistributionACEFactory& photon_production_dist_factory );

  // A map of the photon production reactions
  std::unordered_map<unsigned,std::shared_ptr<const DecoupledPhotonProductionReaction> >
  d_photon_production_reactions;

  // A map of the nuclear reaction type to associated array of TabularDistributions
  std::unordered_map<NuclearReactionType,std::vector<std::shared_ptr<const Utility::UnivariateDistribution> > >
  d_mt_yield_distributions;

  // A map of photon production reaction MT numbers to shared pointers of
  //   Tabular distributions
  std::unordered_map<unsigned,std::shared_ptr<const Utility::UnivariateDistribution> >
  d_mtp_yield_distributions_map;

  // Total reaction
  std::shared_ptr<NeutronNuclearReaction> d_total_reaction;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLONUCLEAR_REACTION_ACE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_NeutronNuclearReactionACEFactory.hpp
//---------------------------------------------------------------------------//
