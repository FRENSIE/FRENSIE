//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_NuclearScatteringDistributionACEFactory.hpp
//! \author Alex Robinson
//! \brief  Nuclear scattering distribution factory base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_NUCLEAR_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP
#define MONTE_CARLO_NUCLEAR_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP

// Std Lib Includes
#include <string>
#include <memory>
#include <unordered_map>
#include <unordered_set>

// FRENSIE Includes
#include "MonteCarlo_NuclearScatteringDistribution.hpp"
#include "MonteCarlo_NuclearScatteringDistributionACEFactoryHelper.hpp"
#include "MonteCarlo_SimulationProperties.hpp"
#include "Utility_ArrayView.hpp"

namespace MonteCarlo{

//! The nuclear scattering distribution factory base class
template<typename IncomingParticleType, typename OutgoingParticleType>
class NuclearScatteringDistributionACEFactory : private NuclearScatteringDistributionACEFactoryHelper<IncomingParticleType,OutgoingParticleType>
{

public:

  //! The nuclear scattering distribution type to be created
  typedef NuclearScatteringDistribution<IncomingParticleType,
					OutgoingParticleType>
  DistributionType;

  //! Constructor
  NuclearScatteringDistributionACEFactory(
			    const std::string& table_name,
			    const double atomic_weight_ratio,
			    const Utility::ArrayView<const double> mtr_block,
			    const Utility::ArrayView<const double> tyr_block,
			    const Utility::ArrayView<const double> land_block,
			    const Utility::ArrayView<const double> and_block,
			    const Utility::ArrayView<const double> ldlw_block,
			    const Utility::ArrayView<const double> dlw_block );

  //! Constructor (no TYR block)
  NuclearScatteringDistributionACEFactory(
			    const std::string& table_name,
			    const double atomic_weight_ratio,
			    const Utility::ArrayView<const double> mtr_block,
			    const Utility::ArrayView<const double> land_block,
			    const Utility::ArrayView<const double> and_block,
			    const Utility::ArrayView<const double> ldlw_block,
			    const Utility::ArrayView<const double> dlw_block );

  //! Destructor
  virtual ~NuclearScatteringDistributionACEFactory()
  { /* ... */ }

  //! Return the reactions with scattering distributions
  void getReactionsWithScatteringDistributions(
			     std::unordered_set<unsigned>& reactions ) const;

  //! Check if a reaction has a scattering distribution
  bool doesReactionHaveScatteringDistribution( const unsigned reaction ) const;

  //! Create the scattering distribution
  void createScatteringDistribution(
                 const unsigned reaction_type,
                 const SimulationProperties& properties,
                 std::shared_ptr<const DistributionType>& distribution ) const;

protected:

  //! Basic Constructor
  NuclearScatteringDistributionACEFactory( const std::string& table_name,
					  const double atomic_weight_ratio );

  //! Initialize the factory
  void initialize( const Utility::ArrayView<const double> mtr_block,
		   const Utility::ArrayView<const double> tyr_block,
		   const Utility::ArrayView<const double> land_block,
		   const Utility::ArrayView<const double> and_block,
		   const Utility::ArrayView<const double> ldlw_block,
		   const Utility::ArrayView<const double> dlw_block );

  //! Initialize the factory (no TYR block)
  void initialize( const Utility::ArrayView<const double> mtr_block,
		   const Utility::ArrayView<const double> land_block,
		   const Utility::ArrayView<const double> and_block,
		   const Utility::ArrayView<const double> ldlw_block,
		   const Utility::ArrayView<const double> dlw_block );

  // Returns a map of the reaction types (MT #s) and their AND block ordering
  const std::unordered_map<unsigned,unsigned>&
  getReactionOrdering() const;

  // Returns a map of the reaction types (MT #s) and the scattering ref. frame
  // Note: True = center-of-mass, False = lab
  const std::unordered_map<unsigned,bool>&
  getReactionCMScattering() const;

  // Returns a set of the reaction types (MT #s) with isotropic scattering only
  const std::unordered_set<unsigned>&
  getReactionsWithIsotropicScatteringOnly() const;

  // Returns a set of the reaction types (MT #s) with coupled energy-angle dist
  const std::unordered_set<unsigned>&
  getReactionsWithCoupledEnergyAngleDist() const;

  // Returns a map of the reaction types (MT #s) and the corresp. angular dist
  const std::unordered_map<unsigned,Utility::ArrayView<const double> >&
  getReactionAngularDist() const;

  // Returns a map of the reaction types (MT #s) and angular dist start index
  const std::unordered_map<unsigned,unsigned>&
  getReactionAngularDistStartIndex() const;

  // Returns a map of the reaction types (MT #s) and the corresp. energy dist
  const std::unordered_map<unsigned,Utility::ArrayView<const double> >&
  getReactionEnergyDist() const;

  // Returns a map of the reaction types (MT #s) and energy dist start index
  const std::unordered_map<unsigned,unsigned>&
  getReactionEnergyDistStartIndex() const;

  // Initialize the reaction type ordering map
  void initializeReactionOrderingMap(
			   const Utility::ArrayView<const double>& mtr_block,
			   const Utility::ArrayView<const double>& tyr_block );

  // Initialize the reaction type scattering ref. frame map
  void initializeReactionRefFrameMap(
			   const Utility::ArrayView<const double>& mtr_block,
			   const Utility::ArrayView<const double>& tyr_block );

  // Initialize the reaction type angular distribution start index map
  void initializeReactionAngularDistStartIndexMap(
			  const Utility::ArrayView<const double>& land_block );

  // Initialize the reaction type angular distribution map
  void initializeReactionAngularDistMap(
			   const Utility::ArrayView<const double>& land_block,
			   const Utility::ArrayView<const double>& and_block );

  // Initialize the reaction type energy distribution start index map
  void initializeReactionEnergyDistStartIndexMap(
			  const Utility::ArrayView<const double>& ldlw_block );

  // Initialize the reaction type energy distribution map
  void initializeReactionEnergyDistMap(
			   const Utility::ArrayView<const double>& ldlw_block,
			   const Utility::ArrayView<const double>& dlw_block );

  // The table name
  std::string d_table_name;

  // The atomic weight ratio
  double d_atomic_weight_ratio;

  // A map of the reaction types (MT #s) and their AND block ordering
  std::unordered_map<unsigned,unsigned> d_reaction_ordering;

  // A map of the reaction types (MT #s) and the scattering reference frame
  // Note: True = center-of-mass, False = lab
  std::unordered_map<unsigned,bool> d_reaction_cm_scattering;

  // A set of the reaction types (MT #s) with isotropic scattering only
  std::unordered_set<unsigned>
  d_reactions_with_isotropic_scattering_only;

  // A set of the reaction types (MT #s) with coupled energy-angle dist
  std::unordered_set<unsigned>
  d_reactions_with_coupled_energy_angle_dist;

  // A map of the reaction types (MT #s) and the corresponding angular dist
  std::unordered_map<unsigned,Utility::ArrayView<const double> >
  d_reaction_angular_dist;

  // A map of the reaction types (MT #s) and the angular dist start index
  std::unordered_map<unsigned,unsigned>
  d_reaction_angular_dist_start_index;

  // A map of the reaction types (MT #s) and the energy dist start index
  std::unordered_map<unsigned,unsigned>
  d_reaction_energy_dist_start_index;

  // A map of the reaction types (MT #s) and the corresponding energy dist
  std::unordered_map<unsigned,Utility::ArrayView<const double> >
  d_reaction_energy_dist;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_NuclearScatteringDistributionACEFactory_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_NUCLEAR_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclearScatteringDistributionACEFactory.hpp
//---------------------------------------------------------------------------//
