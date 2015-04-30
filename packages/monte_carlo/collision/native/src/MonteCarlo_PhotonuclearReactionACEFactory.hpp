//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotonuclearReactionACEFactory.hpp
//! \author Ryan Pease, Alex Robinson
//! \brief  Nuclear reaction factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_NUCLEAR_REACTION_ACE_FACTORY_HPP
#define MONTE_CARLO_PHOTONUCLEAR_REACTION_ACE_FACTORY_HPP

// Boost Includes
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

// FRENSIE Includes
#include "MonteCarlo_PhotonuclearReaction.hpp"
#include "MonteCarlo_PhotonuclearReactionType.hpp"
#include "MonteCarlo_PhotonuclearNeutronScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_PhotonuclearScatteringDistributionACEFactory.hpp"
#include "Data_XSSPhotonuclearDataExtractor.hpp"

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
		 const Teuchos::ArrayRCP<const double>& energy_grid,
		 const Data::XSSNeutronDataExtractor& raw_nuclide_data );
		 
  //! Destructor
  ~PhotonuclearReactionACEFactory()
  { /* ... */ }

  //! Create the scattering reactions 
  void createScatteringReactions( 
      boost::unordered_map<PhotonuclearReactionType,Teuchos::RCP<PhotonuclearReaction> >&
      scattering_reactions ) const;

  //! Create the absorption reactions 
  void createAbsorptionReactions(
      boost::unordered_map<PhotonuclearReactionType,Teuchos::RCP<PhotonuclearReaction> >&
      absorption_reactions ) const;	     


protected:

  //! Create the reaction type ordering map
  static void createReactionOrderingMap( 
       const Teuchos::ArrayView<const double>& mtr_block,
       boost::unordered_map<PhotonuclearReactionType,unsigned>& reaction_ordering );

  //! Create the reaction type Q-value map
  static void createReactionQValueMap( 
   const Teuchos::ArrayView<const double>& lqr_block,
   const boost::unordered_map<PhotonuclearReactionType,unsigned>& reaction_ordering,
   boost::unordered_map<PhotonuclearReactionType,double>& reaction_q_value );

  //! Create the reaction multiplicity map
  static void createReactionMultiplicityMap(
   const std::string& table_name,
   const Teuchos::ArrayView<const double>& tyr_block,
   const Teuchos::ArrayView<const double>& dlw_block,
   const boost::unordered_map<PhotonuclearReactionType,unsigned>& reaction_ordering,
   boost::unordered_map<PhotonuclearReactionType,unsigned>& 
   reaction_multiplicity,
   boost::unordered_map<PhotonuclearReactionType,Teuchos::ArrayView<const double> >&
   reaction_energy_dependent_multiplicity );

  //! Create the reaction threshold index map
  static void createReactionThresholdMap(
   const Teuchos::ArrayView<const double>& lsig_block,
   const Teuchos::ArrayView<const double>& sig_block,
   const boost::unordered_map<PhotonuclearReactionType,unsigned>& reaction_ordering,
   boost::unordered_map<PhotonuclearReactionType,unsigned>& 
   reaction_threshold_index );

  //! Create the reaction cross section map
  static void createReactionCrossSectionMap(
   const Teuchos::ArrayView<const double>& lsig_block,
   const Teuchos::ArrayView<const double>& sig_block,
   const Teuchos::ArrayView<const double>& elastic_cross_section,
   const boost::unordered_map<PhotonuclearReactionType,unsigned>& reaction_ordering,
   boost::unordered_map<PhotonuclearReactionType,Teuchos::ArrayRCP<double> >& 
   reaction_cross_section );

private:

  // Initialize the scattering reactions
  void initializeScatteringReactions( 
    const Teuchos::ArrayRCP<const double> energy_grid,
    const boost::unordered_map<PhotonuclearReactionType,double>& reaction_q_value,
    const boost::unordered_map<PhotonuclearReactionType,unsigned>&
    reaction_multiplicity,
    const boost::unordered_map<PhotonuclearReactionType,Teuchos::ArrayView<const double> >&
    reaction_energy_dependent_multiplicity,
    const boost::unordered_map<PhotonuclearReactionType,unsigned>&
    reaction_threshold_index,
    const boost::unordered_map<PhotonuclearReactionType,Teuchos::ArrayRCP<double> >&
    reaction_cross_section,
    const NeutronNuclearScatteringDistributionACEFactory& scattering_dist_factory );

  // Initialize the absorption reactions
  void initializeAbsorptionReactions(
    const Teuchos::ArrayRCP<const double> energy_grid,
    const boost::unordered_map<PhotonuclearReactionType,double>& reaction_q_value,
    const boost::unordered_map<PhotonuclearReactionType,unsigned>&
    reaction_multiplicity,
    const boost::unordered_map<PhotonuclearReactionType,Teuchos::ArrayView<const double> >&
    reaction_energy_dependent_multiplicity,
    const boost::unordered_map<PhotonuclearReactionType,unsigned>&
    reaction_threshold_index,
    const boost::unordered_map<PhotonuclearReactionType,Teuchos::ArrayRCP<double> >&
    reaction_cross_section );

  // A map of the scattering reactions
  boost::unordered_map<PhotonuclearReactionType,Teuchos::RCP<PhotonuclearReaction> >
  d_scattering_reactions;
  
  // A map of the absorption reactions
  boost::unordered_map<PhotonuclearReactionType,Teuchos::RCP<PhotonuclearReaction> >
  d_absorption_reactions;

};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHOTONUCLEAR_REACTION_ACE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotonuclearReactionACEFactory.hpp
//---------------------------------------------------------------------------//
