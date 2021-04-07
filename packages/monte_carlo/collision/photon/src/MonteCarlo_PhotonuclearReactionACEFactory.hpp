//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotonuclearReactionACEFactory.hpp
//! \author Ryan Pease, Alex Robinson
//! \brief  Nuclear reaction factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_NUCLEAR_REACTION_ACE_FACTORY_HPP
#define MONTE_CARLO_PHOTONUCLEAR_REACTION_ACE_FACTORY_HPP

// Std Includes
#include <unordered_map>
#include <unordered_set>

// FRENSIE Includes
#include "MonteCarlo_PhotonuclearReaction.hpp"
#include "MonteCarlo_PhotonuclearReactionType.hpp"
#include "MonteCarlo_PhotonuclearNeutronScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_PhotonuclearScatteringDistributionACEFactory.hpp"
#include "Data_XSSPhotonuclearDataExtractor.hpp"
#include "Utility_ArrayView.hpp"

namespace MonteCarlo{

/*! The nuclear reaction factory class
 * \details This factory class stores all of the data blocks found in the
 * ACE tables that describe specific reactions (except for fission reactions).
 * The array parameters used in the class constructor have the same name as
 * the corresponding ACE data block.
 */
class PhotonuclearReactionACEFactory
{

public:

  //! Constructor
  PhotonuclearReactionACEFactory(
		const std::string& table_name,
                const double atomic_weight_ratio,
		const std::shared_ptr<const std::vector<double> >& energy_grid,
                const Data::XSSPhotonnuclearDataExtractor& raw_nuclide_data );

  //! Destructor
  ~PhotonuclearReactionACEFactory()
  { /* ... */ }

  //! Create the scattering reactions
  void createScatteringReactions(
      std::unordered_map<PhotonuclearReactionType,std::shared_ptr<PhotonuclearReaction> >&
      scattering_reactions ) const;

  //! Create the absorption reactions
  void createAbsorptionReactions(
      std::unordered_map<PhotonuclearReactionType,std::shared_ptr<PhotonuclearReaction> >&
      absorption_reactions ) const;


protected:

  //! Create the reaction type ordering map
  static void createReactionOrderingMap(
       const Utility::ArrayView<const double>& mtr_block,
       std::unordered_map<PhotonuclearReactionType,unsigned>& reaction_ordering );

  //! Create the reaction type Q-value map
  static void createReactionQValueMap(
   const Utility::ArrayView<const double>& lqr_block,
   const std::unordered_map<PhotonuclearReactionType,unsigned>& reaction_ordering,
   std::unordered_map<PhotonuclearReactionType,double>& reaction_q_value );

  //! Create the reaction multiplicity map
  static void createReactionMultiplicityMap(
   const std::string& table_name,
   const Utility::ArrayView<const double>& tyr_block,
   const Utility::ArrayView<const double>& dlw_block,
   const std::unordered_map<PhotonuclearReactionType,unsigned>& reaction_ordering,
   std::unordered_map<PhotonuclearReactionType,unsigned>&
   reaction_multiplicity,
   std::unordered_map<PhotonuclearReactionType,Utility::ArrayView<const double> >&
   reaction_energy_dependent_multiplicity );

  //! Create the reaction threshold index map
  static void createReactionThresholdMap(
   const Utility::ArrayView<const double>& lsig_block,
   const Utility::ArrayView<const double>& sig_block,
   const std::unordered_map<PhotonuclearReactionType,unsigned>& reaction_ordering,
   std::unordered_map<PhotonuclearReactionType,size_t>&
   reaction_threshold_index );

  //! Create the reaction cross section map
  static void createReactionCrossSectionMap(
   const Utility::ArrayView<const double>& lsig_block,
   const Utility::ArrayView<const double>& sig_block,
   const Utility::ArrayView<const double>& elastic_cross_section,
   const std::unordered_map<PhotonuclearReactionType,unsigned>& reaction_ordering,
   std::unordered_map<PhotonuclearReactionType,std::shared_ptr<std::vector<double> > >&
   reaction_cross_section );

private:

  // Initialize the scattering reactions
  void initializeScatteringReactions(
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::unordered_map<PhotonuclearReactionType,double>& reaction_q_value,
    const std::unordered_map<PhotonuclearReactionType,unsigned>&
    reaction_multiplicity,
    const std::unordered_map<PhotonuclearReactionType,Utility::ArrayView<const double> >&
    reaction_energy_dependent_multiplicity,
    const std::unordered_map<PhotonuclearReactionType,size_t>&
    reaction_threshold_index,
    const std::unordered_map<PhotonuclearReactionType,std::shared_ptr<std::vector<double> > >&
    reaction_cross_section,
    const NeutronNuclearScatteringDistributionACEFactory& scattering_dist_factory );

  // Initialize the absorption reactions
  void initializeAbsorptionReactions(
    const std::shared_ptr<const std::vector<double> >& energy_grid,
    const std::unordered_map<PhotonuclearReactionType,double>& reaction_q_value,
    const std::unordered_map<PhotonuclearReactionType,unsigned>&
    reaction_multiplicity,
    const std::unordered_map<PhotonuclearReactionType,Utility::ArrayView<const double> >&
    reaction_energy_dependent_multiplicity,
    const std::unordered_map<PhotonuclearReactionType,size_t>&
    reaction_threshold_index,
    const std::unordered_map<PhotonuclearReactionType,std::shared_ptr<std::vector<double> > >&
    reaction_cross_section );

  // A map of the scattering reactions
  std::unordered_map<PhotonuclearReactionType,std::shared_ptr<PhotonuclearReaction> >
  d_scattering_reactions;

  // A map of the absorption reactions
  std::unordered_map<PhotonuclearReactionType,std::shared_ptr<PhotonuclearReaction> >
  d_absorption_reactions;

};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHOTONUCLEAR_REACTION_ACE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonuclearReactionACEFactory.hpp
//---------------------------------------------------------------------------//
