//---------------------------------------------------------------------------//
//!
//! \file   NuclearReactionFactory.hpp
//! \author Alex Robinson
//! \brief  Nuclear reaction factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef NUCLEAR_REACTION_FACTORY_HPP
#define NUCLEAR_REACTION_FACTORY_HPP

// Std Lib Includes
#include "NuclearReaction.hpp"
#include "NuclearReactionType.hpp"

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
		       const Teuchos::ArrayView<const double>& energy_grid,
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
  Teuchos::RCP<NuclearReaction> createElasticReaction() const;

  //! Create the non-elastic reactions (any reaction with multiplicity > 0)
  Teuchos::Array<Teuchos::RCP<NuclearReaction> > 
  createNonElasticReactions() const;

private:

  // Initialize the reaction type ordering map
  void initializeReactionTypeOrderingMap( 
				 const Teuchos::ArrayView<double>& mtr_block );

  // Initialize the reaction type Q-value map
  void initializeReactionTypeQValueMap( 
				 const Teuchos::ArrayView<double>& lqr_block );

  // Initialize the reaction type multiplicity and scattering ref. frame map
  void initializeReactionTypeMultiplicityAndRefFrameMap(
				 const Teuchos::ArrayView<double>& tyr_block );
  
  // Initialize the reaction type threshold and cross section map
  void initializeReactionTypeThresholdAndCrossSectionMap(
		     const Teuchos::ArrayView<double>& lsig_block,
		     const Teuchos::ArrayView<double>& sig_block,
		     const Teuchos::ArrayView<double>& elastic_cross_section );

  // Initialize the reaction type and block ordering map
  void initializeReactionTypeANDBlockOrdering(
			        const Teuchos::ArrayView<double>& mtr_block,
				const Teuchos::ArrayView<double>& tyr_block,
				const Teuchos::ArrayView<double>& land_block );

  // Initialize the reaction type angular distribution map
  void initializeReactionTypeAngularDistMap(
				 const Teuchos::ArrayView<double>& land_block,
				 const Teuchos::ArrayView<double>& and_block );

  // Initialize the reaction type energy distribution map
  void initializeReactionTypeEnergyDistMap(
				 const Teuchos::ArrayView<double>& ldlw_block,
				 const Teuchos::ArrayView<double>& dlw_block );

  // Calculate the AND block angular distribution array sizes
  void calculateAngularDistArraySizes( 
                    const Teuchos::ArrayView<double>& land_block,
		    const Teuchos::ArrayView<double>& and_block,
                    Teuchos::Array<unsigned>& angular_dist_array_sizes ) const;

  // The table name
  std::string d_table_name;

  // The atomic weight ratio
  double d_atomic_weight_ratio;
  
  // The energy grid
  Teuchos::ArrayView<double> d_energy_grid;

  // The scattering distribution factory
  ScatteringDistributionFactory d_scattering_dist_factory;
  
  // A map of the reaction types (MT #s) in the table and their ordering
  boost::unordered_map<NuclearReactionType,unsigned> d_reaction_ordering;

  // A map of the reaction types (MT #s) and the corresponding Q-value
  boost::unordered_map<NuclearReactionType,double> d_reaction_q_value;
  
  // A map of the reaction types (MT #s) and the corresponding multiplicity
  boost::unordered_map<NuclearReactionType,unsigned> 
  d_reaction_multiplicity;

  // A map of the reaction types (MT #s) and the scattering reference frame
  // Note: True = center-of-mass, False = lab
  boost::unordered_map<NuclearReactionType,bool> d_reaction_cm_scattering;
  
  // A map of the reaction types (MT #s) and the corresponding threshold index
  boost::unordered_map<NuclearReactionType,unsigned> 
  d_reaction_threshold_index;
  
  // A map of the reaction types (MT #s) and the corresponding cross section
  boost::unordered_map<NuclearReactionType,Teuchos::ArrayView<double> >
  d_reaction_cross_section;

  // A map of the reaction types (MT #s) and their AND block ordering
  boost::unordered_map<NuclearReactionType,unsigned> 
  d_reaction_and_block_ordering;

  // A set of the reaction types (MT #s) with isotropic scattering only
  boost::unordered_set<NuclearReactionType>
  d_reactions_with_isotropic_scattering_only;

  // A set of the reaction types (MT #s) with coupled energy-angle dist
  boost::unordered_set<NuclearReactionType>
  d_reactions_with_coupled_energy_angle_dist;

  // A map of the reaction types (MT #s) and the corresponding angular dist
  boost::unordered_map<NuclearReactionType,Teuchos::ArrayView<double> >
  d_reaction_angular_dist;
  
  // A map of the reaction types (MT #s) and the corresponding energy dist
  boost::unordered_map<NuclearReactionType,Teuchos::ArrayView<double> >
  d_reaction_energy_dist;
};

} // end FACEMC namespace

#endif // end NUCLEAR_REACTION_FACTORY_HPP

//---------------------------------------------------------------------------//
// end NuclearReactionFactory.hpp
//---------------------------------------------------------------------------//
