//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SAlphaBetaNuclearReactionACEFactory.cpp
//! \author Eli Moll
//! \brief  S(alpha,beta) nuclear reaction factory class definition
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_SAlphaBetaNuclearReactionACEFactory.hpp"

namespace MonteCarlo{

// Constructor
SAlphaBetaNuclearReactionACEFactory::SAlphaBetaNuclearReactionACEFactory( 
	 const std::string& table_name,
	 const double atomic_weight_ratio,
	 const double temperature,
	 const Teuchos::ArrayRCP<const double>& energy_grid,
	 const Data::XSSNeutronDataExtractor& raw_nuclide_data,
	 const Data::XSSSabDataExtractor& sab_nuclide_data ) :
	   NuclearReactionACEFactory( table_name,
	                              atomic_weight_ratio,
	                              temperature,
	                              energy_grid,
	                              raw_nuclide_data )
{
  // Create the scattering distribution factory
  SAlphaBetaNuclearScatteringDistributionACEFactory 
    scattering_dist_factory( table_name,
			                       atomic_weight_ratio,
			                       raw_nuclide_data,
			                       sab_nuclide_data );
	
  // Create a map of the reaction types and the corresponding cross section
  boost::unordered_map<NuclearReactionType,Teuchos::ArrayView<const double> >
    reaction_cross_section;
  this->setSAlphaBetaCrossSectionMap( sab_nuclide_data,
                                      reaction_cross_section );
	
	// Create a map of the reaction types and the upper energy limits
	boost::unordered_map<NuclearReactionType, double> upper_energy_limits;
	this->setSAlphaBetaUpperEnergyLimitMap( sab_nuclide_data,
	                                        upper_energy_limits );
	
	// Initialize the S(alpha,beta) reactions
	initializeSAlphaBetaReactions( temperature,
	                               sab_nuclide_data.extractInelasticEnergyGrid(),
	                               reaction_cross_section,
	                               scattering_dist_factory );
}

// Update the reaction threshold map with the new reactions
void SAlphaBetaNuclearReactionACEFactory::setSAlphaBetaCrossSectionMap( 
  const Data::XSSSabDataExtractor& sab_nuclide_data,
  boost::unordered_map<NuclearReactionType,Teuchos::ArrayView<const double> >
    reaction_cross_section )
{
  // Inelastic cross-section
  NuclearReactionType reaction_type = 1004u;
  reaction_cross_section[reaction_type] = 
    sab_nuclide_data.extractInelasticCrossSection();
  
  // Elastic cross-section
  if( sab_nuclide_data.hasElasticScatteringCrossSectionData() )
  {
    reaction_cross_section[1002u] = 
      sab_nuclide_data.extractElasticCrossSection();
  }
}

// Update the reaction upper threshold index map
void setSAlphaBetaUpperEnergyLimitMap( 
       const Data::XSSSabDataExtractor& sab_nuclide_data,
       boost::unordered_map<NuclearReactionType, double> upper_energy_limits )
{
  // Inelastic upper energy limit
  upper_energy_limits[1004u] =
    sab_nuclide_data.extractInelasticEnergyGrid().back();
    
  // Elastic upper energy limit
  if( sab_nuclide_data.hasElasticScatteringCrossSectionData() )
  {
    upper_energy_limits[1002u] =
      sab_nuclide_data.extractElasticEnergyGrid().back();
  }
}

// Initialize the S(alpha,beta) reactions
void initializeSAlphaBetaReactions(  
    const double temperature,
    Teuchos::ArrayView<const double> sab_energy_grid,
    boost::unordered_map<NuclearReactionType,Teuchos::ArrayView<const double> >&
      reaction_cross_section,
    const SAlphaBetaNuclearScatteringDistributionACEFactory& 
      scattering_dist_factory )
{
 /* ... */
}

};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_NuclearReactionACEFactory.hpp
//---------------------------------------------------------------------------//
