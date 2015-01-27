//---------------------------------------------------------------------------//
//! 
//! \file   MonteCarlo_NeutronScatteringDistributionACEFactory.hpp
//! \author Alex Robinson
//! \brief  Neutron scattering distribution factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_NEUTRON_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP
#define MONTE_CARLO_NEUTRON_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP

// Std Lib Includes
#include <string>

// Boost Includes
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_NeutronScatteringDistribution.hpp"
#include "MonteCarlo_ElasticNeutronScatteringDistribution.hpp"
#include "MonteCarlo_NuclearReactionType.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"

namespace MonteCarlo{

//! The scattering distribution factory class
class NeutronScatteringDistributionACEFactory
{
  
public:

  //! Constructor 
  NeutronScatteringDistributionACEFactory( 
		       const std::string& table_name,
		       const double atomic_weight_ratio,
		       const Data::XSSNeutronDataExtractor& raw_nuclide_data );
			
  //! Destructor
  ~NeutronScatteringDistributionACEFactory()
  { /* ... */ }

  //! Create a scattering distribution 
  void createScatteringDistribution( 
	      const NuclearReactionType reaction_type,
	      Teuchos::RCP<NeutronScatteringDistribution>& distribution) const;

protected:

  // Returns a map of the reaction types (MT #s) and their AND block ordering
  const boost::unordered_map<NuclearReactionType,unsigned>& 
  getReactionOrdering() const;

  // Returns a map of the reaction types (MT #s) and the scattering ref. frame
  // Note: True = center-of-mass, False = lab
  const boost::unordered_map<NuclearReactionType,bool>& 
  getReactionCMScattering() const;
  
  // Returns a set of the reaction types (MT #s) with isotropic scattering only
  const boost::unordered_set<NuclearReactionType>& 
  getReactionsWithIsotropicScatteringOnly() const;

  // Returns a set of the reaction types (MT #s) with coupled energy-angle dist
  const boost::unordered_set<NuclearReactionType>& 
  getReactionsWithCoupledEnergyAngleDist() const;

  // Returns a map of the reaction types (MT #s) and the corresp. angular dist
  const boost::unordered_map<NuclearReactionType,
			     Teuchos::ArrayView<const double> >&
  getReactionAngularDist() const;

  // Returns a map of the reaction types (MT #s) and angular dist start index
  const boost::unordered_map<NuclearReactionType,unsigned>& 
  getReactionAngularDistStartIndex() const;
  
  // Returns a map of the reaction types (MT #s) and the corresp. energy dist
  const boost::unordered_map<NuclearReactionType,
			     Teuchos::ArrayView<const double> >&
  getReactionEnergyDist() const;

  // Returns a map of the reaction types (MT #s) and energy dist start index
  const boost::unordered_map<NuclearReactionType,unsigned>& 
  getReactionEnergyDistStartIndex() const;
  
private:

  // Initialize the reaction type ordering map
  void initializeReactionOrderingMap( 
			   const Teuchos::ArrayView<const double>& mtr_block,
			   const Teuchos::ArrayView<const double>& tyr_block );

  // Initialize the reaction type scattering ref. frame map
  void initializeReactionRefFrameMap( 
			   const Teuchos::ArrayView<const double>& mtr_block,
			   const Teuchos::ArrayView<const double>& tyr_block );

  // Initialize the reaction type angular distribution start index map
  void initializeReactionAngularDistStartIndexMap(
			  const Teuchos::ArrayView<const double>& land_block );

  // Initialize the reaction type angular distribution map
  void initializeReactionAngularDistMap(
			   const Teuchos::ArrayView<const double>& land_block,
			   const Teuchos::ArrayView<const double>& and_block );

  // Initialize the reaction type energy distribution start index map
  void initializeReactionEnergyDistStartIndexMap(
			  const Teuchos::ArrayView<const double>& ldlw_block );

  // Initialize the reaction type energy distribution map
  void initializeReactionEnergyDistMap(
			   const Teuchos::ArrayView<const double>& ldlw_block,
			   const Teuchos::ArrayView<const double>& dlw_block );

  // The table name
  std::string d_table_name;

  // The atomic weight ratio
  double d_atomic_weight_ratio;

  // A map of the reaction types (MT #s) and their AND block ordering
  boost::unordered_map<NuclearReactionType,unsigned> d_reaction_ordering;

  // A map of the reaction types (MT #s) and the scattering reference frame
  // Note: True = center-of-mass, False = lab
  boost::unordered_map<NuclearReactionType,bool> d_reaction_cm_scattering;
  
  // A set of the reaction types (MT #s) with isotropic scattering only
  boost::unordered_set<NuclearReactionType>
  d_reactions_with_isotropic_scattering_only;

  // A set of the reaction types (MT #s) with coupled energy-angle dist
  boost::unordered_set<NuclearReactionType>
  d_reactions_with_coupled_energy_angle_dist;

  // A map of the reaction types (MT #s) and the corresponding angular dist
  boost::unordered_map<NuclearReactionType,Teuchos::ArrayView<const double> >
  d_reaction_angular_dist;

  // A map of the reaction types (MT #s) and the angular dist start index
  boost::unordered_map<NuclearReactionType,unsigned> 
  d_reaction_angular_dist_start_index;
  
  // A map of the reaction types (MT #s) and the energy dist start index
  boost::unordered_map<NuclearReactionType,unsigned> 
  d_reaction_energy_dist_start_index;
  
  // A map of the reaction types (MT #s) and the corresponding energy dist
  boost::unordered_map<NuclearReactionType,Teuchos::ArrayView<const double> >
  d_reaction_energy_dist;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_NEUTRON_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_NeutronScatteringDistributionACEFactory.hpp
//---------------------------------------------------------------------------//
