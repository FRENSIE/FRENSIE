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
#include "NeutronNeutronScatteringDistributionFactory.hpp"

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

  //! Create the elastic reaction
  void createElasticReaction( Teuchos::RCP<NuclearReaction>& reaction ) const;

  //! Create the non-elastic reactions (any reaction with multiplicity > 0)
  void createNonElasticReactions( 
	     Teuchos::Array<Teuchos::RCP<NuclearReaction> >& reactions ) const;

private:

  // Initialize the reaction type ordering map
  void initializeReactionOrderingMap( 
			   const Teuchos::ArrayView<const double>& mtr_block );

  // Initialize the reaction type Q-value map
  void initializeReactionQValueMap( 
			   const Teuchos::ArrayView<const double>& lqr_block );

  // Initialize the reaction type multiplicity and scattering ref. frame map
  void initializeReactionMultiplicityMap(
			   const Teuchos::ArrayView<const double>& tyr_block );
  
  // Initialize the reaction type threshold and cross section map
  void initializeReactionThresholdAndCrossSectionMap(
	       const Teuchos::ArrayView<const double>& lsig_block,
	       const Teuchos::ArrayView<const double>& sig_block,
	       const Teuchos::ArrayView<const double>& elastic_cross_section );

  // The table name
  std::string d_table_name;

  // The atomic weight ratio
  double d_atomic_weight_ratio;
  
  // The temperature at which the nuclear reactions will occur (MeV)
  double d_temperature;
  
  // The energy grid
  Teuchos::ArrayRCP<const double> d_energy_grid;

  // The scattering distribution factory
  NeutronNeutronScatteringDistributionFactory d_scattering_dist_factory;
  
  // A map of the reaction types (MT #s) in the table and their ordering
  boost::unordered_map<NuclearReactionType,unsigned> d_reaction_ordering;

  // A map of the reaction types (MT #s) and the corresponding Q-value
  boost::unordered_map<NuclearReactionType,double> d_reaction_q_value;
  
  // A map of the reaction types (MT #s) and the corresponding multiplicity
  boost::unordered_map<NuclearReactionType,unsigned> 
  d_reaction_multiplicity;

  // A map of the reaction types (MT #s) and the corresponding threshold index
  boost::unordered_map<NuclearReactionType,unsigned> 
  d_reaction_threshold_index;
  
  // A map of the reaction types (MT #s) and the corresponding cross section
  boost::unordered_map<NuclearReactionType,Teuchos::ArrayView<const double> >
  d_reaction_cross_section;
};

} // end FACEMC namespace

#endif // end NUCLEAR_REACTION_FACTORY_HPP

//---------------------------------------------------------------------------//
// end NuclearReactionFactory.hpp
//---------------------------------------------------------------------------//
