//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DecoupledPhotonProductionReactionACEFactory.hpp
//! \author Eli Moll
//! \brief  Decoupled photon production reaction factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DECOUPLED_PHOTON_PRODUCTION_REACTION_ACE_FACTORY_HPP
#define MONTE_CARLO_DECOUPLED_PHOTON_PRODUCTION_REACTION_ACE_FACTORY_HPP

// Boost Includes
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

// FRENSIE Includes
#include "MonteCarlo_DecoupledPhotonProductionReaction.hpp"
#include "MonteCarlo_PhotonProductionNuclearScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_NuclearReactionACEFactory.hpp"
#include "MonteCarlo_NuclearReactionType.hpp"

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
		 const Teuchos::ArrayRCP<const double>& energy_grid,
		 const Data::XSSNeutronDataExtractor& raw_nuclide_data );
		 
  //! Destructor
  ~DecoupledPhotonProductionReactionACEFactory()
  { /* ... */ }

  //! Create the yield based photon production reactions 
  void createPhotonProductionReactions( 
      boost::unordered_map<unsigned,Teuchos::RCP<DecoupledPhotonProductionReaction> >&
      yield_based_photon_production_reactions ) const;

protected:

  //! Create the reaction type ordering map
  static void createReactionOrderingMap( 
       const Teuchos::ArrayView<const double>& mtrp_block,
       boost::unordered_map<unsigned,unsigned>& reaction_ordering );
   
  //! Create the total reaction
  void createTotalReaction(
                       const Teuchos::ArrayView<const double>& total_xs_block,
                       const Teuchos::ArrayRCP<const double>& energy_grid,
                       const double temperature );
                       
  //! Parse the SIGP Block            
  static void parseSIGP(
    const Teuchos::ArrayView<const double>& lsigp_block,
    const Teuchos::ArrayView<const double>& sigp_block,
    const boost::unordered_map<unsigned,unsigned>& reaction_ordering,
    boost::unordered_map<unsigned,Teuchos::ArrayView<const double> >& yield_energy_map,
    boost::unordered_map<unsigned,Teuchos::ArrayView<const double> >& yield_values_map,
    boost::unordered_map<unsigned,Teuchos::ArrayRCP<double> >& xs_based_map,
    boost::unordered_map<unsigned,unsigned>& threshold_energy_map,
    boost::unordered_map<unsigned,NuclearReactionType>& base_reaction_type_map );   
                       
  //! Construct the base reaction map 
  void constructBaseReactionMap(
  boost::unordered_map<unsigned,NuclearReactionType>& base_reaction_type_map,
  boost::unordered_map<NuclearReactionType,Teuchos::RCP<NuclearReaction> >& base_reaction_map );                     
                       
private:

  // Initialize the yield based photon production reactions
  void initializeYieldBasedPhotonProductionReactions( 
       const boost::unordered_map<unsigned,NuclearReactionType>& base_reaction_type_map,
	     const double temperature,
	     const boost::unordered_map<unsigned,Teuchos::ArrayView<const double> >& yield_energy_map,
	     const boost::unordered_map<unsigned,Teuchos::ArrayView<const double> >& yield_values_map,
	     const boost::unordered_map<NuclearReactionType,Teuchos::RCP<NuclearReaction> >& base_reaction_map,
	     PhotonProductionNuclearScatteringDistributionACEFactory photon_production_dist_factory );

  // Initialize the yield based photon production reactions
  void initializeCrossSectionBasedPhotonProductionReactions( 
       const boost::unordered_map<unsigned,NuclearReactionType>& base_reaction_type_map,
	     const double temperature,
	     const boost::unordered_map<unsigned,unsigned>& threshold_energy_map,
	     const boost::unordered_map<unsigned,Teuchos::ArrayRCP<double> >& xs_based_map,
	     const Teuchos::ArrayRCP<const double>& energy_grid,
	     PhotonProductionNuclearScatteringDistributionACEFactory photon_production_dist_factory );

  // A map of the yield based photon production reactions
  boost::unordered_map<unsigned,Teuchos::RCP<DecoupledPhotonProductionReaction> >
  d_photon_production_reactions;
  
  // Total reaction 
  Teuchos::RCP<NuclearReaction> d_total_reaction;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLONUCLEAR_REACTION_ACE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclearReactionACEFactory.hpp
//---------------------------------------------------------------------------//
