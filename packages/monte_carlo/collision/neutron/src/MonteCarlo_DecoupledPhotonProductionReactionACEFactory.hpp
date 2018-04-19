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

// Boost Includes
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

// FRENSIE Includes
#include "MonteCarlo_DecoupledPhotonProductionReaction.hpp"
#include "MonteCarlo_PhotonProductionNuclearScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_NuclearReactionACEFactory.hpp"
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
class DecoupledPhotonProductionReactionACEFactory : public NuclearReactionACEFactory
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
      boost::unordered_map<unsigned,std::shared_ptr<const DecoupledPhotonProductionReaction> >&
      yield_based_photon_production_reactions ) const;

protected:

  //! Create the reaction type ordering map
  static void createReactionOrderingMap(
       const Utility::ArrayView<const double>& mtrp_block,
       boost::unordered_map<unsigned,unsigned>& reaction_ordering );

  //! Create the total reaction
  void createTotalReaction(
          const Utility::ArrayView<const double>& total_xs_block,
          const std::shared_ptr<const std::vector<double> >& energy_grid,
          const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
          grid_searcher,
          const double temperature );

  //! Parse the SIGP Block
  static void parseSIGP(
    const Utility::ArrayView<const double>& lsigp_block,
    const Utility::ArrayView<const double>& sigp_block,
    const boost::unordered_map<unsigned,unsigned>& reaction_ordering,
    boost::unordered_map<unsigned,Utility::ArrayView<const double> >& yield_energy_map,
    boost::unordered_map<unsigned,Utility::ArrayView<const double> >& yield_values_map,
    boost::unordered_map<unsigned,std::shared_ptr<std::vector<double> > >& xs_based_map,
    boost::unordered_map<unsigned,unsigned>& threshold_energy_map,
    boost::unordered_map<unsigned,NuclearReactionType>& base_reaction_type_map );

  //! Construct the base reaction map
  void constructBaseReactionMap(
  boost::unordered_map<unsigned,NuclearReactionType>& base_reaction_type_map,
  boost::unordered_map<NuclearReactionType,std::shared_ptr<const NuclearReaction> >& base_reaction_map,
  boost::unordered_map<unsigned,Utility::ArrayView<const double> >& yield_energy_map  );

  // Construct a map of photon MT numbers to yield distributions
  void constructMTPYieldDistributions(
	  const boost::unordered_map<unsigned,Utility::ArrayView<const double> >& yield_energy_map,
	  const boost::unordered_map<unsigned,Utility::ArrayView<const double> >& yield_values_map );

  // Construct a map of base reaction types to yield distribution arrays
  void constructMTYieldArrays(
    const boost::unordered_map<unsigned,NuclearReactionType>& base_reaction_type_map,
    const boost::unordered_map<unsigned,Utility::ArrayView<const double> >& yield_energy_map );

private:

  // Initialize the yield based photon production reactions
  void initializeYieldBasedPhotonProductionReactions(
       const boost::unordered_map<unsigned,NuclearReactionType>& base_reaction_type_map,
       const double temperature,
       const boost::unordered_map<unsigned,Utility::ArrayView<const double> >& yield_energy_map,
       const boost::unordered_map<NuclearReactionType,std::shared_ptr<const NuclearReaction> >& base_reaction_map,
       const SimulationProperties& properties,
       PhotonProductionNuclearScatteringDistributionACEFactory& photon_production_dist_factory );

  // Initialize the yield based photon production reactions
  void initializeCrossSectionBasedPhotonProductionReactions(
       const boost::unordered_map<unsigned,NuclearReactionType>& base_reaction_type_map,
       const double temperature,
       const boost::unordered_map<unsigned,unsigned>& threshold_energy_map,
       const boost::unordered_map<unsigned,std::shared_ptr<std::vector<double> > >& xs_based_map,
       const std::shared_ptr<const std::vector<double> >& energy_grid,
       std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
       grid_searcher,
       const SimulationProperties& properties,
       PhotonProductionNuclearScatteringDistributionACEFactory& photon_production_dist_factory );

  // A map of the photon production reactions
  boost::unordered_map<unsigned,std::shared_ptr<const DecoupledPhotonProductionReaction> >
  d_photon_production_reactions;

  // A map of the nuclear reaction type to associated array of TabularDistributions
  boost::unordered_map<NuclearReactionType,std::vector<std::shared_ptr<Utility::UnivariateDistribution> > >
  d_mt_yield_distributions;

  // A map of photon production reaction MT numbers to shared pointers of
  //   Tabular distributions
  boost::unordered_map<unsigned,std::shared_ptr<const Utility::UnivariateDistribution> >
  d_mtp_yield_distributions_map;

  // Total reaction
  std::shared_ptr<const NuclearReaction> d_total_reaction;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLONUCLEAR_REACTION_ACE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclearReactionACEFactory.hpp
//---------------------------------------------------------------------------//
