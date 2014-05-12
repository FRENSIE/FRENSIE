//---------------------------------------------------------------------------//
//!
//! \file   NuclearReactionFactory.hpp
//! \author Alex Robinson
//! \brief  Nuclear reaction factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef NUCLEAR_REACTION_FACTORY_HPP
#define NUCLEAR_REACTION_FACTORY_HPP

// Boost Includes
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

// Std Lib Includes
#include "NuclearReaction.hpp"
#include "NuclearReactionType.hpp"
#include "NeutronScatteringDistributionFactory.hpp"

namespace FACEMC{

/*! The nuclear reaction factory class
 * \details This factory class stores all of the data blocks found in the 
 * ACE tables. The array parameters used in the class constructor have the
 * same name as the corresponding ACE data block.
 */
class NuclearReactionFactory
{

public:

  //! Constructor
  NuclearReactionFactory( 
		 const std::string& table_name,
		 const double atomic_weight_ratio,
		 const double temperature,
		 const Teuchos::ArrayRCP<const double>& energy_grid,
		 const Teuchos::ArrayView<const double>& elastic_cross_section,
		 const Teuchos::ArrayView<const double>& mtr_block, 
		 const Teuchos::ArrayView<const double>& lqr_block,
		 const Teuchos::ArrayView<const double>& tyr_block,
		 const Teuchos::ArrayView<const double>& lsig_block,
		 const Teuchos::ArrayView<const double>& sig_block,
		 const Teuchos::ArrayView<const double>& land_block,
		 const Teuchos::ArrayView<const double>& and_block,
		 const Teuchos::ArrayView<const double>& ldlw_block,
		 const Teuchos::ArrayView<const double>& dlw_block );

  //! Destructor
  ~NuclearReactionFactory()
  { /* ... */ }

  //! Create the scattering reactions 
  void createScatteringReactions( 
      boost::unordered_map<NuclearReactionType,Teuchos::RCP<NuclearReaction> >&
      scattering_reactions ) const;

  //! Create the absorption reactions 
  void createAbsorptionReactions(
      boost::unordered_map<NuclearReactionType,Teuchos::RCP<NuclearReaction> >&
      absorption_reactions ) const;	     

  //! Create the fission reactions
  void createFissionReactions(
      boost::unordered_map<NuclearReactionType,Teuchos::RCP<NuclearReaction> >&
      fission_reactions ) const;

protected:

  //! Create the reaction type ordering map
  static void createReactionOrderingMap( 
       const Teuchos::ArrayView<const double>& mtr_block,
       boost::unordered_map<NuclearReactionType,unsigned>& reaction_ordering );

  //! Create the reaction type Q-value map
  static void createReactionQValueMap( 
   const Teuchos::ArrayView<const double>& lqr_block,
   const boost::unordered_map<NuclearReactionType,unsigned>& reaction_ordering,
   boost::unordered_map<NuclearReactionType,double>& reaction_q_value );

  //! Create the reaction multiplicity map
  static void createReactionMultiplicityMap(
   const Teuchos::ArrayView<const double>& tyr_block,
   const boost::unordered_map<NuclearReactionType,unsigned>& reaction_ordering,
   boost::unordered_map<NuclearReactionType,unsigned>& reaction_multiplicity );

  //! Create the reaction threshold index map
  static void createReactionThresholdMap(
   const Teuchos::ArrayView<const double>& lsig_block,
   const Teuchos::ArrayView<const double>& sig_block,
   const boost::unordered_map<NuclearReactionType,unsigned>& reaction_ordering,
   boost::unordered_map<NuclearReactionType,unsigned>& 
   reaction_threshold_index );

  //! Create the reaction cross section map
  static void createReactionCrossSectionMap(
   const Teuchos::ArrayView<const double>& lsig_block,
   const Teuchos::ArrayView<const double>& sig_block,
   const Teuchos::ArrayView<const double>& elastic_cross_section,
   const boost::unordered_map<NuclearReactionType,unsigned>& reaction_ordering,
   boost::unordered_map<NuclearReactionType,Teuchos::ArrayRCP<double> >& 
   reaction_cross_section );

private:

  // Initialize the scattering reactions
  void initializeScatteringReactions( 
    const double temperature,
    const Teuchos::ArrayRCP<const double> energy_grid,
    const boost::unordered_map<NuclearReactionType,double>& reaction_q_value,
    const boost::unordered_map<NuclearReactionType,unsigned>&
    reaction_multiplicity,
    const boost::unordered_map<NuclearReactionType,unsigned>&
    reaction_threshold_index,
    const boost::unordered_map<NuclearReactionType,Teuchos::ArrayRCP<double> >&
    reaction_cross_section,
    const NeutronScatteringDistributionFactory& scattering_dist_factory );

  // Initialize the absorption reactions
  void initializeAbsorptionReactions(
    const double temperature,
    const Teuchos::ArrayRCP<const double> energy_grid,
    const boost::unordered_map<NuclearReactionType,double>& reaction_q_value,
    const boost::unordered_map<NuclearReactionType,unsigned>&
    reaction_multiplicity,
    const boost::unordered_map<NuclearReactionType,unsigned>&
    reaction_threshold_index,
    const boost::unordered_map<NuclearReactionType,Teuchos::ArrayRCP<double> >&
    reaction_cross_section );

  // Initialize the fission reactions
  void initializeFissionReactions(
    const double temperature,
    const Teuchos::ArrayRCP<const double> energy_grid,
    const boost::unordered_map<NuclearReactionType,double>& reaction_q_value,
    const boost::unordered_map<NuclearReactionType,unsigned>&
    reaction_multiplicity,
    const boost::unordered_map<NuclearReactionType,unsigned>&
    reaction_threshold_index,
    const boost::unordered_map<NuclearReactionType,Teuchos::ArrayRCP<double> >&
    reaction_cross_section,
    const NeutronScatteringDistributionFactory& scattering_dist_factory );
				    

  // A map of the scattering reactions
  boost::unordered_map<NuclearReactionType,Teuchos::RCP<NuclearReaction> >
  d_scattering_reactions;
  
  // A map of the absorption reactions
  boost::unordered_map<NuclearReactionType,Teuchos::RCP<NuclearReaction> >
  d_absorption_reactions;

  // A map of the fission reactions
  boost::unordered_map<NuclearReactionType,Teuchos::RCP<NuclearReaction> >
  d_fission_reactions;
};

} // end FACEMC namespace

#endif // end NUCLEAR_REACTION_FACTORY_HPP

//---------------------------------------------------------------------------//
// end NuclearReactionFactory.hpp
//---------------------------------------------------------------------------//
