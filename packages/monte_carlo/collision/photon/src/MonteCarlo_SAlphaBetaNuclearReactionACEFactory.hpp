//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SAlphaBetaNuclearReactionACEFactory.hpp
//! \author Eli Moll
//! \brief  S(alpha,beta) nuclear reaction factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_S_ALPHA_BETA_NUCLEAR_REACTION_ACE_FACTORY_HPP
#define MONTE_CARLO_S_ALPHA_BETA_NUCLEAR_REACTION_ACE_FACTORY_HPP

// std Includes
#include <map>

// FRENSIE Includes
#include "MonteCarlo_NeutronNuclearReactionACEFactory.hpp"
#include "MonteCarlo_NeutronScatteringReaction.hpp"
#include "MonteCarlo_SAlphaBetaNuclearScatteringDistributionACEFactory.hpp"
#include "Data_XSSSabDataExtractor.hpp"

namespace MonteCarlo{

/*! The nuclear reaction factory class
 * \details This factory class stores all of the data blocks found in the 
 * ACE tables that describe specific reactions (except for fission reactions). 
 * The array parameters used in the class constructor have the same name as 
 * the corresponding ACE data block.
 */
class SAlphaBetaNuclearReactionACEFactory : public NeutronNuclearReactionACEFactory
{

public:

  //! Constructor
  SAlphaBetaNuclearReactionACEFactory( 
		 const std::string& table_name,
		 const double atomic_weight_ratio,
		 const double temperature,
		 const std::shared_ptr<const std::vector<double> >& energy_grid,
		 const Data::XSSNeutronDataExtractor& raw_nuclide_data,
		 const Data::XSSSabDataExtractor& sab_nuclide_data,
     const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
     grid_searcher,
     const SimulationProperties& properties );
		 
  //! Destructor
  ~SAlphaBetaNuclearReactionACEFactory()
  { /* ... */ }

  //! Create the scattering reactions 
  void createSAlphaBetaReactions( 
      std::unordered_map<NuclearReactionType,std::shared_ptr<NeutronNuclearReaction> >&
      sab_reactions ) const;

protected:

  //! Update the reaction threshold index map
  static void setSAlphaBetaUpperEnergyLimitMap( 
       const Data::XSSSabDataExtractor& sab_nuclide_data,
       std::unordered_map<NuclearReactionType, double>& upper_energy_limits );

  //! Update the reaction cross section map
  static void setSAlphaBetaCrossSectionMap( 
    const Data::XSSSabDataExtractor& sab_nuclide_data,
    std::unordered_map<NuclearReactionType,Utility::ArrayView<const double> >&
      reaction_cross_section  );

private:

  // Initialize the scattering reactions
  void initializeSAlphaBetaReactions( 
    const double temperature,
    const Data::XSSSabDataExtractor& sab_nuclide_data,
    std::unordered_map<NuclearReactionType,Utility::ArrayView<const double> >&
      reaction_cross_section,
    const SAlphaBetaNuclearScatteringDistributionACEFactory& 
      scattering_dist_factory );
      
  // S(alpha,beta) reactions
  // A map of the scattering reactions
  std::unordered_map<NuclearReactionType,std::shared_ptr<NeutronNuclearReaction> >
  d_s_alpha_beta_reactions;

};

} // end MonteCarlo namespace

#endif // end MONTE_CARLONUCLEAR_REACTION_ACE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclearReactionACEFactory.hpp
//---------------------------------------------------------------------------//
